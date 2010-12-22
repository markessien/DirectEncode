#include "stdafx.h"
#include "consts1.h"
#include <sys\stat.h>
#include "mplex.h"
#include "muxlib.h"
#include <math.h>
#include "locals.h"

/******************************************************************
	Main multiplex iteration.
	Opens and closes all needed files and manages the correct
	call to the respective Video- and Audio- packet routines.
	The basic multiplexing is done here. Buffer capacity and
	Timestamp checking is also done here, decision is taken
	wether we should genereate a Video-, Audio- or Padding-
	packet.
******************************************************************/

#define CLOCK_TICKS_100MS   2700000.0
#define CLOCK_TICKS_250MS   6750000.0
#define CLOCK_TICKS_500MS  13500000.0
#define CLOCK_TICKS_700MS  18900000.0 

static double bytes_output;
static int fileCount;
static char programFilename[MAX_PATH], *pFileNumPtr;
static HANDLE programFile;
static Sector_struc sector;
static double extra_clock_cycles;
static int output_sys_header;
static unsigned int vcd_sys_header;
static unsigned long video_buffer_size;
static unsigned char audio_id, audio1_id;
static unsigned char audio_buffer_scale, audio1_buffer_scale;
static unsigned int audio_buffer_size1, audio1_buffer_size1;
static unsigned char video_PSTD;
static unsigned int video_counter;
static unsigned int video_underflows;
/* the following is used to generate SVCD scan info */
static unsigned int current_sector;
static FILE *svcd_info;
static char *svcd_name;
static double max_file_size_GOP;
static unsigned int start_time, stop_time;
static char start_new_file;
static char restart_output;
static char stop_output;
static char output_on;
static char do_broken_link;
static char do_sequence_header;
static double start_video_PTS;

static int embed_svcd_scan_info(Video_struc *video_info);
static int open_next_file();
static int end_program_stream(double clock_cycles, unsigned long packet_data_size,
                              unsigned int mux_rate, Video_struc *video_info,
                              unsigned int audio_underflows, unsigned int audio1_underflows,
                              unsigned int nsec_a, unsigned int nsec_a1,
                              unsigned int nsec_v, unsigned int nsec_p,
                              HANDLE outputFile, Buffer_struc *video_buffer,
                              Buffer_struc *audio_buffer, Buffer_struc *audio1_buffer,
                              int last_file);

int ml_outputstream (
HANDLE          outputFile,
char 		*video_units,
Video_struc 	*video_info,
char 		*audio_units,
Audio_struc 	*audio_info,
char 		*audio1_units,
Audio_struc 	*audio1_info,
unsigned int video_total,
unsigned int audio_total,
unsigned int audio1_total,
unsigned int    which_streams)
{
  HANDLE istream_v;			/* Inputstream Video	*/
  HANDLE istream_a;			/* Inputstream Audio	*/
  HANDLE istream_a1;                     /* Second audio stream  */
  FILE *vunits_info;			/* Input Video Units	*/
  FILE *aunits_info;			/* Input Audio Units	*/
  FILE *aunits1_info;                   /* Input Audio1 units   */

  Vaunit_struc video_au;		/* Video Access Unit	*/
  Aaunit_struc audio_au;		/* Audio Access Unit	*/
  Aaunit_struc audio1_au;               /* Audio1 Access Unit   */

  unsigned int data_rate=0;		/* AudioVideo Byterate	*/
  unsigned int video_rate=0;
  unsigned int audio_rate=0;
  unsigned int audio1_rate = 0;
  double delay,audio_delay,audio1_delay,video_delay;
  double clock_cycles, temp_cycles;
  double audio_next_clock_cycles;
  double audio1_next_clock_cycles;
  double video_next_clock_cycles;
  int dmux_rate, mux_rate;
  unsigned char picture_start;
  unsigned char audio_frame_start;
  unsigned char audio1_frame_start;
  unsigned int audio_state, audio1_state, video_state;

  unsigned int nsec_a=0;
  unsigned int nsec_a1=0;
  unsigned int nsec_v=0;
  unsigned int nsec_p=0;

  Timecode_struc SCR_audio_delay;
  Timecode_struc SCR_audio1_delay;
  Timecode_struc SCR_video_delay;
  Timecode_struc current_SCR;
  double audio_PTS, audio1_PTS, video_DTS, video_PTS;

  Buffer_struc video_buffer;
  Buffer_struc audio_buffer;
  Buffer_struc audio1_buffer;

  Pack_struc 		pack;
  Sys_header_struc 	sys_header;

  unsigned int audio_buffer_size, audio1_buffer_size;
  unsigned char audio_PSTD, audio1_PSTD;
  unsigned int audio_counter, audio1_counter;
  unsigned char audio_subid, audio1_subid;
  unsigned int audio_underflows, audio1_underflows;
  unsigned long min_packet_data;
  unsigned long write_pack;
  unsigned char marker_pack;
  int vpacket_data_size, apacket_data_size, a1packet_data_size;
  unsigned long i, total_counter, rearm_sys_header;
  int percent, oldPercent;
  char tmpStr[132];
  int exiterror = FALSE;
  int second_data_packet;
  double sectors_per_sec, clock_inc, clock_inc_2;
  double audio_frame_clocks, audio1_frame_clocks;
  double first_audio_PTS, first_audio1_PTS, first_video_PTS, first_video_DTS;
  double org_video_delay, org_audio_delay, org_audio1_delay;
  int first_audio, first_audio1, k;
  char audio_restart_output, audio1_restart_output;

  output_sys_header = TRUE;
  audio_PSTD = TRUE;
  audio1_PSTD = TRUE;
  video_PSTD = TRUE;

  istream_v = NULL;
  istream_a = NULL;
  istream_a1 = NULL;
  vunits_info = NULL;
  aunits_info = NULL;
  aunits1_info = NULL;
  programFile = NULL;
  exiterror = TRUE;
  video_counter = 0;
  audio_counter = 0;
  audio1_counter = 0;
  audio_buffer_scale = 0;
  audio1_buffer_scale = 0;
  vcd_sys_header = 0;
  video_underflows = 0;
  audio_underflows = 0;
  audio1_underflows = 0;
  audio_id = 0;
  audio1_id = 0;
  audio_subid = 0;
  audio1_subid = 0;
  first_audio = 1;
  first_audio1 = 1;
  start_new_file = 0;
  restart_output = 0;
  audio_restart_output = 0;
  audio1_restart_output = 0;
  start_video_PTS = 0;
  output_on = 1;
  do_broken_link = 0;
  do_sequence_header = 0;
  stop_output = 0;
  memset(&video_buffer, 0, sizeof(video_buffer));
  memset(&audio_buffer, 0, sizeof(audio_buffer));
  memset(&audio1_buffer, 0, sizeof(audio1_buffer));
  /* svcd stuff */
  current_sector = 0;
  svcd_info = NULL;

  /* Open in- and outputstream				*/
  if (which_streams & STREAMS_VIDEO)
  {
    istream_v = CreateFile(ml_VideoFilename, GENERIC_READ, FILE_SHARE_READ, NULL,
		                   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (istream_v == INVALID_HANDLE_VALUE)
    {
      sprintf(tmpStr, "Unable to open video file %s.", ml_VideoFilename);
      MuxLibDisplayError(tmpStr);
      return FALSE;
    }
  }
  if (which_streams & STREAMS_AUDIO)
  {
    istream_a = CreateFile(ml_AudioFilename, GENERIC_READ, FILE_SHARE_READ, NULL,
		                   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (istream_a == INVALID_HANDLE_VALUE)
    {
      sprintf(tmpStr, "Unable to open audio file %s.", ml_AudioFilename);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
  }
  if (which_streams & STREAMS_AUDIO1)
  {
    istream_a1 = CreateFile(ml_Audio1Filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		                   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (istream_a1 == INVALID_HANDLE_VALUE)
    {
      sprintf(tmpStr, "Unable to open secondary audio file %s.", ml_Audio1Filename);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
  }

  if (which_streams & STREAMS_VIDEO)
  {
    if ((vunits_info = fopen (video_units, "rb")) == NULL)
    {
      sprintf(tmpStr, "Unable to open video units file %s.", video_units);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
  }
  if (which_streams & STREAMS_AUDIO)
  {
    if ((aunits_info = fopen (audio_units, "rb")) == NULL)
    {
      sprintf(tmpStr, "Unable to open audio units file %s.", audio_units);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
  }
  if (which_streams & STREAMS_AUDIO1)
  {
    if ((aunits1_info = fopen (audio1_units, "rb")) == NULL)
    {
      sprintf(tmpStr, "Unable to open secondary audio units file %s.", audio1_units);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
  }

  if (ml_mux_SVCD_scan_offsets)
  {
    svcd_name = tempnam("./","tmp_s");
    if ((svcd_info = fopen(svcd_name, "wb")) == NULL)
    {
      sprintf(tmpStr, "Unable to open SVCD scan offsets temporary file %s.", svcd_name);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
  }

  strcpy(programFilename, ml_ProgramFilename);
 // c(programFilename); strlwr, sofink like that
  fileCount = 1;
  pFileNumPtr = NULL;

  if (ml_max_file_size || !outputFile)
  {
    if (ml_max_file_size)
    {
      pFileNumPtr = strstr(programFilename, "00");
      if (!pFileNumPtr)
      {
        pFileNumPtr = strrchr(programFilename, '.');
        if (pFileNumPtr)
        {
          pFileNumPtr[0] = '0';
          pFileNumPtr[1] = '0';
          pFileNumPtr[2] = 0;
          pFileNumPtr = strrchr(ml_ProgramFilename, '.');
          strcat(programFilename, pFileNumPtr);
        }
        else
          strcat(programFilename, "00");
        pFileNumPtr = strstr(programFilename, "00");
      }
    }
    programFile = CreateFile(programFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                             CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (programFile == INVALID_HANDLE_VALUE)
    {
      sprintf(tmpStr, "Unable to open program file %s.", programFilename);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
  }
  else
    programFile = outputFile;

  /* read in first access unit information			*/

  picture_start     = FALSE;
  audio_frame_start = FALSE;
  audio1_frame_start = FALSE;
  empty_vaunit_struc (&video_au);
  empty_aaunit_struc (&audio_au);
  empty_aaunit_struc (&audio1_au);

  if (which_streams & STREAMS_AUDIO)
  {
    if (fread (&audio_au, sizeof(Aaunit_struc), 1, aunits_info) != 1)
    {
      sprintf(tmpStr, "Unable to read from audio units file %s.", audio_units);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
    audio_frame_start = TRUE;
    audio_counter++;
  }

  if (which_streams & STREAMS_AUDIO1)
  {
    if (fread (&audio1_au, sizeof(Aaunit_struc), 1, aunits1_info) != 1)
    {
      sprintf(tmpStr, "Unable to read from secondary audio units file %s.", audio1_units);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
    audio1_frame_start = TRUE;
    audio1_counter++;
  }

  if (which_streams & STREAMS_VIDEO)
  {
    if (fread (&video_au, sizeof(Vaunit_struc), 1, vunits_info) != 1)
    {
      sprintf(tmpStr, "Unable to read from video units file %s.", video_units);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
    picture_start = TRUE;
    video_counter++;
  }

  write_pack = ml_packets_per_pack;
  video_buffer_size = ml_init_video_buffer_size * 1024;
  audio_buffer_size = ml_init_audio_buffer_size * 1024;
  audio1_buffer_size = ml_init_audio1_buffer_size * 1024;

  /* initialize buffer structure				*/

  init_buffer_struc (&video_buffer,video_buffer_size);
  init_buffer_struc (&audio_buffer,audio_buffer_size);
  init_buffer_struc (&audio1_buffer,audio1_buffer_size);

  if (which_streams & STREAMS_VIDEO)
  {
    switch (ml_use_computed_bitrate)
    {
      case COMPBITRATE_NONE:
        video_rate = video_info->bit_rate * 50;
        if (video_rate)
          break;

      case COMPBITRATE_MAX:
        video_rate = video_info->comp_max_bit_rate * 50;
        break;

      case COMPBITRATE_AVG:
        video_rate = video_info->comp_avg_bit_rate * 50;
        break;

    }
  }
//  if (ml_VBR_multiplex && !ml_user_mux_rate)
//    video_rate = (int)ceil((double)video_rate * 1.25);

  audio_frame_clocks = 0.0;
  audio1_frame_clocks = 0.0;

  if (which_streams & STREAMS_AUDIO)
  {
    if (audio_info->layer)
    {                                /* MPEG */
      audio_id = AUDIO_STR_0;
      audio_rate = bitrate_index[3-audio_info->layer][audio_info->bit_rate]*125;
      audio_buffer_size1 = audio_buffer_size / 128;
      audio_frame_clocks = (double)samples[3 - audio_info->layer] / (double)frequency[audio_info->layer] * 27000.0;
    }
    else
    {                               /* AC3 */
      audio_id = PRIVATE_STREAM1;
      audio_subid = AC3_STREAM1;
      audio_rate = audio_info->bit_rate*128;
      audio_buffer_size1 = audio_buffer_size / 1024;
      audio_buffer_scale = 1;
      audio_frame_clocks = 1536.0 / (double)ac3_frequency[audio_info->frequency] * 27000.0;
    }
  }

  if (which_streams & STREAMS_AUDIO1)
  {
    if (audio1_info->layer)
    {                                /* MPEG */
      audio1_id = AUDIO_STR_1;
      audio1_rate = bitrate_index[3-audio1_info->layer][audio1_info->bit_rate]*125;
      audio1_buffer_size1 = audio1_buffer_size / 128;
      audio1_frame_clocks = (double)samples[3 - audio1_info->layer] / (double)frequency[audio1_info->layer] * 27000.0;
    }
    else
    {                               /* AC3 */
      audio1_id = PRIVATE_STREAM1;
      if (!audio_subid)
        audio1_subid = AC3_STREAM1;
      else
        audio1_subid = AC3_STREAM2;
      audio1_rate = audio1_info->bit_rate*128;
      audio1_buffer_size1 = audio1_buffer_size / 1024;
      audio1_buffer_scale = 1;
      audio1_frame_clocks = 1536.0 / (double)ac3_frequency[audio1_info->frequency] * 27000.0;
    }
  }

  data_rate = video_rate + audio_rate + audio1_rate;

  if (ml_always_sys_header)
  {
    if (ml_mplex_type > MPEG_VCD)
      min_packet_data = ml_sector_size - MPEG2_PACK_HEADER_SIZE - SYS_HEADER_SIZE -
        	                      PACKET_HEADER_SIZE - MPEG2_AFTER_PACKET_LENGTH;
    else
      min_packet_data = ml_sector_size - MPEG1_PACK_HEADER_SIZE - SYS_HEADER_SIZE -
        	                      PACKET_HEADER_SIZE - MPEG1_AFTER_PACKET_LENGTH;

    /* if we do not have all streams, we have 3 or 6 more bytes in the sys header free */

    if (!(which_streams & STREAMS_VIDEO))
      min_packet_data += 3;
    if (!(which_streams & STREAMS_AUDIO))
      min_packet_data += 3;
    if (!(which_streams & STREAMS_AUDIO1))
      min_packet_data += 3;
  }
  else
  {
    if (ml_mplex_type > MPEG_VCD)
      min_packet_data = ml_sector_size - MPEG2_PACK_HEADER_SIZE -
  	                ((PACKET_HEADER_SIZE + MPEG2_AFTER_PACKET_LENGTH) * ml_packets_per_pack);
    else
      min_packet_data = ml_sector_size - MPEG1_PACK_HEADER_SIZE -
  	                ((PACKET_HEADER_SIZE + MPEG1_AFTER_PACKET_LENGTH) * ml_packets_per_pack);
  }
  vpacket_data_size = min_packet_data / ml_packets_per_pack;
  if (ml_mplex_type == MPEG_VCD)
    apacket_data_size = vpacket_data_size - 15; // allow 5 more for no DTS fields
  else
    apacket_data_size = vpacket_data_size + 5;  // allow 5 more for no DTS fields
  a1packet_data_size = apacket_data_size;

  if (audio_id == PRIVATE_STREAM1)
    apacket_data_size -= 4; // 4 bytes less for AC3
  if (audio1_id == PRIVATE_STREAM1)
    a1packet_data_size -= 4; // 4 bytes less for AC3

  dmux_rate =  (int)ceil((double)(data_rate) *
      ((double)(ml_sector_size)/(double)(min_packet_data)));
  mux_rate = (int)ceil(dmux_rate / 50.);
  if (ml_user_mux_rate)
  {
    if (ml_user_mux_rate < mux_rate)
      MuxLibDisplayInfo("    NOTE: Mux rate may be too low for data rate, watch for PTS/DTS underflows.");
    mux_rate = ml_user_mux_rate;
  }

  dmux_rate = mux_rate * 50;
  if ((ml_mplex_type == MPEG_VCD) &&  (mux_rate == 3528))
	sectors_per_sec = 75;
  else
    sectors_per_sec = floor((double)dmux_rate / ml_sector_size);
  clock_inc = CLOCKS / sectors_per_sec;
  clock_inc_2 = clock_inc * 2.0;

  if (which_streams & STREAMS_VIDEO)
  {
    if (ml_max_file_size)
      max_file_size_GOP = ml_max_file_size * 1048576.0 - dmux_rate;
    else
      max_file_size_GOP = 0.0;
    if (ml_mux_start_time)
    {
      start_time = ml_mux_start_time * 1000;
      if (start_time > get_timecode(&video_info->last_PTS) / 27000)
      {
        sprintf(tmpStr, "Mux start time is greater than the total time %u seconds.",
                         (unsigned int)(get_timecode(&video_info->last_PTS) / CLOCKS));
        MuxLibDisplayError(tmpStr);
        goto exit1;
      }
      if (start_time > (unsigned int)(get_timecode(&video_au.PTS) / 27000))
        output_on = 0;
    }
    else
      start_time = 0;
    if (ml_mux_stop_time)
      stop_time = ml_mux_stop_time * 1000;
    else
      stop_time = 0;
  }


  /*  DTS of the first units is supposed to be zero. To avoid
	Buffer underflow, we have to compute how long it takes for
	all first Video and Audio access units to arrive at the
	system standard decoder buffer. This delay is added as a
	kind of startup delay to all of the TimeStamps. We compute
	a ceiling based on the number of sectors we will have
	to transport for the first access units */

  video_delay = ceil(((double)video_au.length / (double)vpacket_data_size) +
                     ((double)audio_au.length / (double)apacket_data_size) +
                     ((double)audio1_au.length / (double)a1packet_data_size)) *
                      (double)ml_sector_size / dmux_rate * (double)CLOCKS;
  if (!ml_always_sys_header)
    video_delay += clock_inc; // account for a padding packet with the system header
  audio_delay = audio1_delay = video_delay;

  if (ml_video_delay_ms)
    video_delay = (double)ml_video_delay_ms*(double)(CLOCKS / 1000);
  if (ml_audio_delay_ms)
    audio_delay = (double)ml_audio_delay_ms*(double)(CLOCKS / 1000);
  if (ml_audio1_delay_ms)
    audio1_delay = (double)ml_audio1_delay_ms*(double)(CLOCKS / 1000);

  delay = (double)ml_sectors_delay*(double)(CLOCKS / 1000);
  bytes_output = ml_sector_size * sectors_per_sec * ml_sectors_delay / 1000.0;
  clock_cycles = delay;
  extra_clock_cycles = 0.0;

  audio_delay += delay;
  audio1_delay += delay;
  video_delay += delay;

  make_timecode(audio_delay, &SCR_audio_delay);
  make_timecode(audio1_delay, &SCR_audio1_delay);
  make_timecode(video_delay, &SCR_video_delay);

  if ((max_file_size_GOP != 0) || start_time || stop_time)
  {
    org_audio_delay = audio_delay;
    org_audio1_delay = audio1_delay;
    org_video_delay = video_delay;
    first_audio_PTS = get_timecode(&audio_au.PTS);
    first_audio1_PTS = get_timecode(&audio1_au.PTS);
    first_video_PTS = get_timecode(&video_au.PTS);
    first_video_DTS = get_timecode(&video_au.DTS);
  }

  add_to_timecode(&SCR_video_delay, &video_au.DTS);
  add_to_timecode(&SCR_video_delay, &video_au.PTS);
  add_to_timecode(&SCR_audio_delay, &audio_au.PTS);
  add_to_timecode(&SCR_audio1_delay, &audio1_au.PTS);

  /*  Let's try to read in unit after unit and to write it out into
	the outputstream. The only difficulty herein lies into the
	buffer management, and into the fact the the actual access
	unit *has* to arrive in time, that means the whole unit
	(better yet, packet data), has to arrive before arrival of
	DTS. If both buffers are full we'll generate a padding packet */

  MuxLibDisplayInfo(" ");
  MuxLibDisplayInfo("  Multiplexing information");
  if (which_streams & STREAMS_VIDEO)
  {
    sprintf(tmpStr, "    Video stream data rate : %d bytes/sec (%d bits/sec)", video_rate, video_rate << 3);
    MuxLibDisplayInfo(tmpStr);
  }
  if (which_streams & STREAMS_AUDIO)
  {
    sprintf(tmpStr, "    Audio stream 1 data rate : %d bytes/sec (%d bits/sec)", audio_rate, audio_rate << 3);
    MuxLibDisplayInfo(tmpStr);
  }
  if (which_streams & STREAMS_AUDIO1)
  {
    sprintf(tmpStr, "    Audio stream 2 data rate : %d bytes/sec (%d bits/sec)", audio1_rate, audio1_rate << 3);
    MuxLibDisplayInfo(tmpStr);
  }
  if (!ml_user_mux_rate)
  {
    sprintf(tmpStr, "    Overhead data rate : %d bytes/sec (%d bits/sec)", dmux_rate - data_rate, (dmux_rate - data_rate) << 3);
    MuxLibDisplayInfo(tmpStr);
  }
  sprintf(tmpStr, "    Total data rate : %d bytes/sec (%d bits/sec)", dmux_rate, dmux_rate << 3);
  MuxLibDisplayInfo(tmpStr);
  MuxLibDisplayInfo(" ");
  sprintf(tmpStr, "  Multiplexing file %s", programFilename);
  MuxLibDisplayInfo(tmpStr);
  if (ml_OutputStats)
    status_header(programFilename);

  rearm_sys_header = FALSE;
  second_data_packet = FALSE;
  total_counter = audio_total + audio1_total + video_total;
  oldPercent = -1;

  while ((video_au.length + audio_au.length + audio1_au.length) > 0)
  {
    if ((start_new_file || restart_output) &&
       (audio_restart_output || !audio_au.length) &&
       (audio1_restart_output || !audio1_au.length))
    {
      if (start_new_file)
      {
        if (!end_program_stream(clock_cycles + clock_inc + extra_clock_cycles, vpacket_data_size,
                                mux_rate, video_info, audio_underflows, audio1_underflows,
                                nsec_a, nsec_a1, nsec_v, nsec_p, outputFile, &video_buffer,
                                &audio_buffer, &audio1_buffer, FALSE))
          goto exit1;
        if (!open_next_file())
          goto exit1;

        bytes_output = ml_sector_size * sectors_per_sec * ml_sectors_delay / 1000.0;
        MuxLibDisplayInfo(" ");
        sprintf(tmpStr, "  Multiplexing file %s", programFilename);
        MuxLibDisplayInfo(tmpStr);
        if (ml_OutputStats)
          status_header(programFilename);
      }
      else
        output_on = 1;

      if (ml_reset_clocks)
      {
        clock_cycles = delay;
        extra_clock_cycles = 0.0;

        if (which_streams & STREAMS_AUDIO)
        {
          audio_PTS = get_timecode(&audio_au.PTS);
          audio_delay = (audio_PTS - start_video_PTS) - (audio_PTS - first_audio_PTS - org_audio_delay);
          audio_PTS += audio_delay;
          make_timecode(audio_delay, &SCR_audio_delay);
          make_timecode(audio_PTS, &audio_au.PTS);
        }
        if (which_streams & STREAMS_AUDIO1)
        {
          audio1_PTS = get_timecode(&audio1_au.PTS);
          audio1_delay = (audio1_PTS - start_video_PTS) - (audio1_PTS - first_audio1_PTS - org_audio1_delay);
          audio1_PTS += audio1_delay;
          make_timecode(audio1_delay, &SCR_audio1_delay);
          make_timecode(audio1_PTS, &audio1_au.PTS);
        }

        video_DTS = get_timecode(&video_au.DTS);
        video_PTS = get_timecode(&video_au.PTS);
        video_delay = -(video_DTS - first_video_DTS - org_video_delay);
        video_DTS += video_delay;
        video_PTS += video_delay;
        make_timecode(video_delay, &SCR_video_delay);
        make_timecode(video_DTS, &video_au.DTS);
        make_timecode(video_PTS, &video_au.PTS);
        buffer_empty(&video_buffer);
        buffer_empty(&audio_buffer);
        buffer_empty(&audio1_buffer);
      }
      else
      {
        add_to_timecode(&SCR_video_delay, &video_au.DTS);
        add_to_timecode(&SCR_video_delay, &video_au.PTS);
        add_to_timecode(&SCR_audio_delay, &audio_au.PTS);
        add_to_timecode(&SCR_audio1_delay, &audio1_au.PTS);
        clock_cycles += clock_inc;        
      }
      vcd_sys_header = 0;
      video_underflows = 0;
      audio_underflows = 0;
      audio1_underflows = 0;
      first_audio = 1;
      first_audio1 = 1;
      current_sector = 0;
      rearm_sys_header = FALSE;
      second_data_packet = FALSE;
      nsec_a = 0;
      nsec_a1 = 0;
      nsec_v = 0;
      nsec_p = 0;
      output_sys_header = TRUE;
      audio_PSTD = TRUE;
      audio1_PSTD = TRUE;
      video_PSTD = TRUE;
      write_pack = ml_packets_per_pack;
      do_broken_link = ml_set_broken_link;
      if (((video_au.flags & SEQHDR_FLAG) == 0) && (video_info->sh_length))
      {
        video_au.length += video_info->sh_length;
        video_au.pict_hdr_offset += video_info->sh_length;
        do_sequence_header = 1;
      }

      start_new_file = 0;
      restart_output = 0;
      audio_restart_output = 0;
      audio1_restart_output = 0;
    }

    MuxLibYieldTime();
    if (ml_AbortMPEG)
      goto exit1;

    i = video_counter + audio_counter + audio1_counter;
    percent = (int)floor(((double) (i)) / ((double) total_counter) * 100.0);
    if (percent != oldPercent)
    {
      sprintf(tmpStr, "Multiplexing: %d%% - %d of %d  A/V units.", percent, i, total_counter);
      MuxLibDisplayProgress(tmpStr, percent);
      oldPercent = percent;
    }

    if (ml_mplex_type == MPEG_VCD)
      second_data_packet = (current_sector == 3);

    if (ml_mplex_type == MPEG_DVD)
    {
      if (video_au.type != IFRAME)
        rearm_sys_header = TRUE;
    }

    if (write_pack-- == ml_packets_per_pack)
      marker_pack = TRUE;
    else
      marker_pack = FALSE;

    if (write_pack == 0)
      write_pack = ml_packets_per_pack;

    if (current_sector)
    {
      clock_cycles += clock_inc;
      if (ml_VBR_multiplex)
      {
        if (extra_clock_cycles > 0.0)
        {
          k = (int)floor(extra_clock_cycles / clock_inc) - 1;
          if (k > 0)
            extra_clock_cycles = (double)k * clock_inc;
          else
            extra_clock_cycles = 0.0;
        }
      }
    }

    audio_PTS = get_timecode(&audio_au.PTS);
    if (!audio_frame_start)
      audio_PTS += audio_frame_clocks;
    audio1_PTS = get_timecode(&audio1_au.PTS);
    if (!audio1_frame_start)
      audio1_PTS += audio1_frame_clocks;
    video_DTS = get_timecode(&video_au.DTS);

    if (ml_VBR_multiplex)
    {
      if (extra_clock_cycles > 0.0)
      {
        temp_cycles = extra_clock_cycles;
        switch (which_streams)
        {
          case STREAMS_V_A:
            if (audio_au.length)
              if (clock_cycles + temp_cycles > audio_PTS - CLOCK_TICKS_100MS)
              {
                while (clock_cycles + temp_cycles > audio_PTS - CLOCK_TICKS_100MS)
                  temp_cycles -= clock_inc;
                temp_cycles += clock_inc;
              }
              break;
          case STREAMS_V_A1:
            if (audio1_au.length)
              if (clock_cycles + temp_cycles > audio1_PTS - CLOCK_TICKS_100MS)
              {
                while (clock_cycles + temp_cycles > audio1_PTS - CLOCK_TICKS_100MS)
                  temp_cycles -= clock_inc;
                temp_cycles += clock_inc;
              }
            break;
          case STREAMS_V_A_A1:
            if (audio_au.length)
              if (clock_cycles + temp_cycles > audio_PTS - CLOCK_TICKS_100MS)
              {
                while (clock_cycles + temp_cycles > audio_PTS - CLOCK_TICKS_100MS)
                  temp_cycles -= clock_inc;
                temp_cycles += clock_inc;
              }
            if (audio1_au.length)
              if (clock_cycles + temp_cycles > audio1_PTS - CLOCK_TICKS_100MS)
              {
                while (clock_cycles + temp_cycles > audio1_PTS - CLOCK_TICKS_100MS)
                  temp_cycles -= clock_inc;
                temp_cycles += clock_inc;
              }
            break;
        }
        if (temp_cycles > 0.0)
        {
         clock_cycles += temp_cycles;
         extra_clock_cycles -= temp_cycles;
        }
        else
          extra_clock_cycles = 0.0;
      }
    }

    audio_next_clock_cycles = clock_cycles;
    audio1_next_clock_cycles = clock_cycles;
    video_next_clock_cycles = clock_cycles;

    audio_state = 0;
    audio1_state = 0;
    video_state = 0;

    if (start_new_file || restart_output || stop_output)
    {
      make_timecode(clock_cycles + CLOCK_TICKS_100MS, &current_SCR);
      if (which_streams & STREAMS_AUDIO)
        buffer_clean(&audio_buffer, &current_SCR);
      if (which_streams & STREAMS_AUDIO1)
        buffer_clean(&audio1_buffer, &current_SCR);
      if (which_streams & STREAMS_VIDEO)
        buffer_clean(&video_buffer, &current_SCR);
      make_timecode(clock_cycles, &current_SCR);
      if ((which_streams & STREAMS_AUDIO) && (audio_au.length) &&
          (!audio_restart_output) &&
          (buffer_space(&audio_buffer) >= apacket_data_size))
        audio_state = 1;
      if ((which_streams & STREAMS_AUDIO1) && (audio1_au.length) &&
          (!audio1_restart_output) &&
          (buffer_space(&audio1_buffer) >= a1packet_data_size))
        audio1_state = 1;
    }
    else
    {
      make_timecode(clock_cycles, &current_SCR);
      if (which_streams & STREAMS_AUDIO)
        buffer_clean(&audio_buffer, &current_SCR);
      if (which_streams & STREAMS_AUDIO1)
        buffer_clean(&audio1_buffer, &current_SCR);
      if (which_streams & STREAMS_VIDEO)
        buffer_clean(&video_buffer, &current_SCR);

      if ((buffer_space(&video_buffer) >= vpacket_data_size) &&
          (video_au.length > 0) &&
          (video_DTS - video_next_clock_cycles < CLOCK_TICKS_700MS))
        video_state = 1;

      if ((which_streams & STREAMS_AUDIO) && (audio_au.length) &&
          (buffer_space(&audio_buffer) >= apacket_data_size) &&
         ((audio_PTS - audio_next_clock_cycles < CLOCK_TICKS_100MS) ||
         ((audio_next_clock_cycles > CLOCK_TICKS_100MS) && (first_audio))))
      {
        first_audio = 0;
        audio_state = 1;
      }

      if ((which_streams & STREAMS_AUDIO1) && (audio1_au.length) &&
          (buffer_space(&audio1_buffer) >= a1packet_data_size) &&
         ((audio1_PTS - audio1_next_clock_cycles < CLOCK_TICKS_100MS) ||
         ((audio1_next_clock_cycles > CLOCK_TICKS_100MS) && (first_audio1))))
      {
        first_audio1 = 0;
        audio1_state = 1;
      }
    }

    if ((!ml_always_sys_header) && (output_sys_header))
    {
      if (ml_mplex_type == MPEG_DVD)
      {
        /* write out private stream 2 packet with the one and only system header */
        if (!output_private2(&current_SCR, mux_rate))
          goto exit1;
      }
      else
      {
        if ((ml_mplex_type == MPEG_VCD) && (current_sector == 1))
          i = apacket_data_size;
        else
          i = vpacket_data_size;
        /* write out padding packet with the one and only system header */
        if (!output_padding(&current_SCR, &pack, &sys_header, mux_rate,
                            i - SYS_HEADER_SIZE, marker_pack, which_streams))
          goto exit1;
      }

      /* status info */
      if (ml_OutputStats && output_on)
        status_info(nsec_a, nsec_a1, nsec_v, ++nsec_p, bytes_output,
                    buffer_space(&video_buffer),
                    buffer_space(&audio_buffer),
                    buffer_space(&audio1_buffer));
      write_pack = ml_packets_per_pack;
      current_sector++;
    }
    else
      /* CASE: Video Buffer OK, Video Data ready		*/
      /*       Audio Data will arrive on time			*/

      if (video_state && !audio_state && !audio1_state && !second_data_packet)
      {
        if (rearm_sys_header && picture_start && (video_au.type == IFRAME))
        {
          rearm_sys_header = FALSE;
          if (ml_put_private2)
          {
            /* write out private stream 2 packet with the one and only system header */
            if (!output_private2(&current_SCR, mux_rate))
              goto exit1;
          }
          else
          {
            /* write out padding packet with the one and only system header */
            if (!output_padding(&current_SCR, &pack, &sys_header, mux_rate,
                                vpacket_data_size - SYS_HEADER_SIZE,
                                marker_pack, which_streams))
              goto exit1;
          }

          /* status info */
          if (ml_OutputStats && output_on)
            status_info(nsec_a, nsec_a1, nsec_v, ++nsec_p, bytes_output,
                        buffer_space(&video_buffer),
                        buffer_space(&audio_buffer),
                        buffer_space(&audio1_buffer));
          write_pack = ml_packets_per_pack;
        }
        else
        {
          /* write out video packet */
          if (!output_video(&current_SCR, &SCR_video_delay, vunits_info,
                            istream_v, &pack, &sys_header,
                            &video_buffer, &video_au, &picture_start,
                            mux_rate, vpacket_data_size,
                            marker_pack, which_streams,
                            video_info->sh_length, &video_info->seq_hdr[0]))
            goto exit1;
          if ((ml_mplex_type != MPEG_VCD) && (ml_mplex_type != MPEG_SVCD))
            video_PSTD = FALSE;

          /* status info */
          if (ml_OutputStats && output_on)
            status_info(nsec_a, nsec_a1, ++nsec_v, nsec_p, bytes_output,
                        buffer_space(&video_buffer),
                        buffer_space(&audio_buffer),
                        buffer_space(&audio1_buffer));
        }
        current_sector++;
      }
      /* CASE: Audio Buffer OK, Audio Data ready		*/
      /*	 Video Data will arrive on time			*/
      else
        if ((audio_state || second_data_packet) && !audio1_state)
        {
          /* write out audio packet */
          if (!output_audio(&current_SCR, &SCR_audio_delay, aunits_info,
                            istream_a, &pack, &sys_header,
                            &audio_buffer, &audio_au, &audio_frame_start,
                            &audio_counter, &audio_underflows, audio_PSTD,
                            audio_id, audio_subid,
                            audio_buffer_scale, audio_buffer_size1, mux_rate,
                            apacket_data_size, marker_pack, which_streams, &audio_restart_output))
            goto exit1;
          if ((ml_mplex_type != MPEG_VCD) && (ml_mplex_type != MPEG_SVCD))
            audio_PSTD = FALSE;
          /* status info */
          if (ml_OutputStats && output_on)
            status_info(++nsec_a, nsec_a1, nsec_v, nsec_p, bytes_output,
                        buffer_space(&video_buffer),
                        buffer_space(&audio_buffer),
                        buffer_space(&audio1_buffer));
          current_sector++;
        }

        /* CASE: Audio1 Buffer OK, Audio1 Data ready		*/
        /*	 Video Data will arrive on time			*/
        else
          if (audio1_state)
          {
            /* write out audio packet */
            if (!output_audio(&current_SCR, &SCR_audio1_delay, aunits1_info,
                              istream_a1, &pack, &sys_header,
                              &audio1_buffer, &audio1_au, &audio1_frame_start,
                              &audio1_counter, &audio1_underflows, audio1_PSTD,
                              audio1_id, audio1_subid,
                              audio1_buffer_scale, audio1_buffer_size1, mux_rate,
                              a1packet_data_size, marker_pack, which_streams, &audio1_restart_output))
              goto exit1;
            if ((ml_mplex_type != MPEG_VCD) && (ml_mplex_type != MPEG_SVCD))
              audio1_PSTD = FALSE;
            /* status info */
            if (ml_OutputStats && output_on)
              status_info(nsec_a, ++nsec_a1, nsec_v, nsec_p, bytes_output,
                          buffer_space(&video_buffer),
                          buffer_space(&audio_buffer),
                          buffer_space(&audio1_buffer));
            current_sector++;
          }
          /* CASE: Audio Buffer NOT OK				*/
          /*	 Video Buffer NOT OK				*/
          else
          {
            if (!ml_VBR_multiplex)
            {
              /* write out padding packet */
              if (!output_padding(&current_SCR, &pack, &sys_header, mux_rate,
                         vpacket_data_size, marker_pack, which_streams))
                goto exit1;

              /* status info */
              if (ml_OutputStats && output_on)
                status_info(nsec_a, nsec_a1, nsec_v, ++nsec_p, bytes_output,
                            buffer_space(&video_buffer),
                            buffer_space(&audio_buffer),
                            buffer_space(&audio1_buffer));
              current_sector++;
            }
          }

    if (stop_output &
       (!(which_streams & STREAMS_AUDIO) || audio_restart_output) &&
       (!(which_streams & STREAMS_AUDIO1) || audio1_restart_output))
      audio_au.length = audio1_au.length = video_au.length = 0;
  }

  if (!end_program_stream(clock_cycles + clock_inc + extra_clock_cycles, vpacket_data_size,
                          mux_rate, video_info, audio_underflows, audio1_underflows,
                          nsec_a, nsec_a1, nsec_v, nsec_p, outputFile, &video_buffer,
                          &audio_buffer, &audio1_buffer, TRUE))
    goto exit1;

  sprintf(tmpStr, "Multiplexing: 100%% - %d of %d  A/V units.", total_counter, total_counter);
  MuxLibDisplayProgress(tmpStr, 100);
  exiterror = FALSE;

exit1:

  buffer_empty(&video_buffer);
  buffer_empty(&audio_buffer);
  buffer_empty(&audio1_buffer);

  /* close all In- and Outputfiles				*/
  if (!outputFile || fileCount > 1)
    if (programFile)
      CloseHandle(programFile);

  if ((which_streams & STREAMS_AUDIO) && (aunits_info))
    fclose (aunits_info);
  if ((which_streams & STREAMS_AUDIO1) && (aunits1_info))
    fclose (aunits1_info);
  if ((which_streams & STREAMS_VIDEO) && (vunits_info))
    fclose (vunits_info);
  if ((which_streams & STREAMS_AUDIO) && (istream_a))
    CloseHandle(istream_a);
  if ((which_streams & STREAMS_AUDIO1) && (istream_a1))
    CloseHandle(istream_a1);
  if ((which_streams & STREAMS_VIDEO) && (istream_v))
    CloseHandle(istream_v);

  /* delete tmp files	*/
  if (ml_mux_SVCD_scan_offsets && svcd_info)
  {
    fclose(svcd_info);
    unlink (svcd_name);
  }

  if (which_streams & STREAMS_VIDEO)
    unlink (video_units);
  if (which_streams & STREAMS_AUDIO)
    unlink (audio_units);

  return !exiterror;
}


static int open_next_file()
{
  char tmpStr[MAX_PATH];

  pFileNumPtr[1] += 1;
  if (pFileNumPtr[1] > '9')
  {
    pFileNumPtr[0] += 1;
    pFileNumPtr[1] = '0';
  }

  programFile = CreateFile(programFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                           CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (programFile == INVALID_HANDLE_VALUE)
  {
    sprintf(tmpStr, "Unable to open program file %s.", programFilename);
    MuxLibDisplayError(tmpStr);
    return 0;
  }

  if (ml_mux_SVCD_scan_offsets)
  {
    if ((svcd_info = fopen(svcd_name, "wb")) == NULL)
    {
      sprintf(tmpStr, "Unable to open SVCD scan offsets temporary file %s.", svcd_name);
      MuxLibDisplayError(tmpStr);
      return 0;
    }
  }
  fileCount++;
  return 1;
}

static int end_program_stream(double clock_cycles, unsigned long packet_data_size,
                              unsigned int mux_rate, Video_struc *video_info,
                              unsigned int audio_underflows, unsigned int audio1_underflows,
                              unsigned int nsec_a, unsigned int nsec_a1,
                              unsigned int nsec_v, unsigned int nsec_p,
                              HANDLE outputFile, Buffer_struc *video_buffer,
                              Buffer_struc *audio_buffer, Buffer_struc *audio1_buffer,
                              int last_file)
{
  unsigned long i, j;
  unsigned char* index;
  Timecode_struc current_SCR;
  char tmpStr[MAX_PATH];

  if (ml_write_pec && (last_file || ml_write_end_codes))
  {
    /* write out END CODE	*/

    index = sector.buf;
    if ((ml_mplex_type == MPEG_VCD) ||
        (ml_mplex_type > MPEG_MPEG2))
    {
      make_timecode(clock_cycles, &current_SCR);

	  // This is just flipping the msb lsb stuff. 4 bytes for pack start code
      *(index++) = (unsigned char)((PACK_START)>>24);
      *(index++) = (unsigned char)((PACK_START & 0x00ff0000)>>16);
      *(index++) = (unsigned char)((PACK_START & 0x0000ff00)>>8);
      *(index++) = (unsigned char)(PACK_START & 0x000000ff);

      if (ml_mplex_type > MPEG_VCD)
      {
        buffer_timecode(&current_SCR, MPEG2_MARKER_SCR, &index);
        *(index++) = (unsigned char)(mux_rate >> 14);
        *(index++) = (unsigned char)(0xff & (mux_rate >> 6));
        *(index++) = (unsigned char)(0x03 | ((mux_rate & 0x3f) << 2));
        *(index++) = (unsigned char)(RESERVED_BYTE << 3);
      }
      else
      {
        buffer_timecode(&current_SCR, MPEG1_MARKER_SCR, &index);
        *(index++) = (unsigned char)(0x80 | (mux_rate >> 15));
        *(index++) = (unsigned char)(0xff & (mux_rate >> 7));
        *(index++) = (unsigned char)(0x01 | ((mux_rate & 0x7f) << 1));
      }
      *(index++) = (unsigned char)(PACKET_START) >> 16;
      *(index++) = (unsigned char)(PACKET_START & 0x00ffff) >> 8;
      *(index++) = (unsigned char)(PACKET_START & 0x0000ff);
      *(index++) = PADDING_STR;
      if (ml_mplex_type > MPEG_VCD)
        i = packet_data_size + MPEG2_AFTER_PACKET_LENGTH - 4;
      else
        i = packet_data_size + MPEG1_AFTER_PACKET_LENGTH - 4;
      *(index++) = (unsigned char)(i >> 8);
      *(index++) = (unsigned char)(i & 0xff);
      if (ml_mplex_type < MPEG_MPEG2)
      {
        *(index++) = 0x0F;
        for (j = 0; j < i - 1; j++)
          *(index++) = (unsigned char) STUFFING_BYTE;
      }
      else
        for (j = 0; j < i; j++)
          *(index++) = (unsigned char) STUFFING_BYTE;
      i = ml_sector_size;
    }
    else
      i = 4;

    *(index++) = (unsigned char)((PROGRAM_END)>>24);
    *(index++) = (unsigned char)((PROGRAM_END & 0x00ff0000)>>16);
    *(index++) = (unsigned char)((PROGRAM_END & 0x0000ff00)>>8);
    *(index) = (unsigned char)(PROGRAM_END & 0x000000ff);

    if (!WriteFile(programFile, sector.buf, i, &j, NULL))
    {
      sprintf(tmpStr, "Unable to write to program file %s.", programFilename);
      MuxLibDisplayError(tmpStr);
      return 0;
    }
    bytes_output += i;
  }
  
  if (ml_OutputStats)
  {
    /* status info*/
    status_info(nsec_a, nsec_a1, nsec_v, nsec_p, bytes_output,
    	        buffer_space(video_buffer), buffer_space(audio_buffer),
                buffer_space(audio1_buffer));
    status_footer ();
  }

  if (video_underflows || audio_underflows || audio1_underflows)
  {
    if (video_underflows)
    {
      sprintf(tmpStr, "    %u video underflows (SCR >= PTS or DTS)", video_underflows);
      MuxLibDisplayInfo(tmpStr);
    }
    if (audio_underflows)
    {
      sprintf(tmpStr, "    %u audio 1 underflows (SCR >= PTS)", audio_underflows);
      MuxLibDisplayInfo(tmpStr);
    }
    if (audio1_underflows)
    {
      sprintf(tmpStr, "    %u audio 2 underflows (SCR >= PTS)", audio1_underflows);
      MuxLibDisplayInfo(tmpStr);
    }
  }

  if (video_underflows || audio_underflows || audio1_underflows)
  {
    MuxLibDisplayInfo(" ");
    MuxLibDisplayInfo("    NOTE: The resulting file may not play back correctly.");
    if ((ml_mplex_type == MPEG_VCD) || (ml_mplex_type == MPEG_SVCD))
    {
      MuxLibDisplayInfo("    Try reducing the video bitrate or increasing the video and");
      MuxLibDisplayInfo("    audio startup delays.");
    }
    else
      MuxLibDisplayInfo("    Try increasing the mux rate.");
  }

  sprintf(tmpStr, "  Finished multiplexing %s", programFilename);
  MuxLibDisplayInfo(tmpStr);

  if (ml_mux_SVCD_scan_offsets)
  {
    if (!FlushFileBuffers(programFile))
	{
      sprintf(tmpStr, "Unable to flush the buffers of program file %s.", programFilename);
      MuxLibDisplayError(tmpStr);
      return 0;
	}
 
    if (!SetEndOfFile(programFile))
	{
      sprintf(tmpStr, "Unable to set the end of file for program file %s.", programFilename);
      MuxLibDisplayError(tmpStr);
      return 0;
	}

    if (!embed_svcd_scan_info(video_info))
      return 0;
    if (svcd_info)
    {
      fclose(svcd_info);
      svcd_info = NULL;
    }
  }

  /* close the output */
  if (!outputFile || fileCount > 1)
    if (programFile)
    {
      CloseHandle(programFile);
      programFile = NULL;
    }

  return 1;
}


static int sector_to_timecode(unsigned char *ptr, unsigned int frame)
{
  unsigned int i, j;
  char tmpStr[MAX_PATH];

  if (fseek(svcd_info, frame << 2, SEEK_SET))
  {
    sprintf(tmpStr, "Unable to seek position in SVCD temporary file %s", svcd_name);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  if (fread(&j, 1, 4, svcd_info) != 4)
  {
    struct stat statbuf;

    if (stat(svcd_name, &statbuf))
      sprintf(tmpStr, "Unable to get size of SVCD temporary file %s", svcd_name);
    else
      sprintf(tmpStr, "Unable to read from SVCD temporary file %s, offset = %u, size = %u", svcd_name, frame << 2, statbuf.st_size);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  i = j / 4500;
  if (i)
  {
    ptr[0] = (unsigned char) (((i / 10) << 4) | (i % 10));
    j %= 4500;
  }
  else
    ptr[0] = 0;
  i = j / 75;
  if (i)
  {
    ptr[1] = (unsigned char) (0x80 | ((i / 10) << 4) | (i % 10));
    j %= 75;
  }
  else
    ptr[1] = 0x80;
  ptr[2] = (unsigned char) (0x80 | ((j / 10) << 4) | (j % 10));
  return TRUE;
}

static int embed_svcd_scan_info(Video_struc *video_info)
{
  char tmpStr[MAX_PATH];
  int percent, oldPercent;
  int i, totIFrames, iFrames7s, errorexit, gop_size;
  unsigned int j;
  unsigned long k;
  unsigned char info_data[12];
  bitstream bs;
  DWORD ret, loSeek;
  LONG hiSeek;
  double bytCount;
  struct stat statbuf;

  if ((video_info->picture_rate < 1) || (video_info->picture_rate > 8))
  {
    MuxLibDisplayInfo("  SVCD scan offsets aborted, invalid frame rate");
    return TRUE;
  }

  if (!video_info->num_groups)
  {
    MuxLibDisplayInfo("  SVCD scan offsets aborted, no GOP headers found");
    return TRUE;
  }

  errorexit = TRUE;
  fclose(svcd_info);
  svcd_info = NULL;
  if (stat(svcd_name, &statbuf))
  {
    sprintf("Unable to get the size of the SVCD temporary file %s.", svcd_name);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }

  svcd_info = fopen(svcd_name, "rb");
  if (!svcd_info)
  {
    sprintf("Unable to open SVCD temporary file %s.", svcd_name);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }

  totIFrames = statbuf.st_size >> 2;
  sprintf(tmpStr, "  Calculating %d SVCD user data scan offsets for file %s", totIFrames, programFilename);
  MuxLibDisplayInfo(tmpStr);

  if (!init_getbits(&bs, programFilename))
    return FALSE;

  i = 0;
  oldPercent = -1;
  gop_size = (int)floor((double)video_info->num_pictures / (double)video_info->num_groups + 0.5);
 
  /* calculate how may I frames in 7 seconds */
  if (video_info->pulldown)
    iFrames7s = (int)ceil(168.0 / (double)gop_size);
  else
    iFrames7s = (int)ceil((7.0 * picture_rates[video_info->picture_rate]) / gop_size);

  while ((i < totIFrames) && !end_bs(&bs))
  {
    MuxLibYieldTime();
    if (ml_AbortMPEG)
      goto exit2;

    percent = (int)floor(((double) (i)) / ((double) totIFrames) * 100.0);
    if (percent != oldPercent)
    {
      sprintf(tmpStr, "SVCD Scan Offsets: %d%% - %d of %d  I-Frames.", percent, i, totIFrames);
      MuxLibDisplayProgress(tmpStr, percent);
      oldPercent = percent;
    }

    if (seek_sync(&bs, USER_DATA_START, 32))
    {
      if (!getbits(&bs, &j, 8))
      {
        sprintf(tmpStr, "Unable to read from program file %s.", programFilename);
        MuxLibDisplayError(tmpStr);
        goto exit2;
      }
      if (j == 0x10)
      {
        if (!getbits(&bs, &j, 8))
        {
          sprintf(tmpStr, "Unable to read from program file %s.", programFilename);
          MuxLibDisplayError(tmpStr);
          goto exit2;
        }
        if (j == 0x0E)
        {
		  bytCount = bitcount(&bs) / 8;
		  if (bytCount > FOUR_GB)
		  {
		    hiSeek = (LONG)(bytCount / FOUR_GB);
			bytCount -= hiSeek * FOUR_GB;
		  }
		  else
			hiSeek = 0;
          loSeek = (DWORD)bytCount;

          ret = SetFilePointer(programFile, loSeek, &hiSeek, FILE_BEGIN);
          if ((ret == 0xFFFFFFFF) && (GetLastError() != NO_ERROR))
          {
            sprintf(tmpStr, "Unable to seek position in program file %s.", programFilename);
            MuxLibDisplayError(tmpStr);
            goto exit2;
          }

          /* fill in previous_I_offset */
          if (i)
          {
            if (!sector_to_timecode(&info_data[0], i - 1))
              goto exit2;
          }
          else
            info_data[0] = info_data[1] = info_data[2] = 0xFF;

          /* fill in next_I_offset */
          if (i < totIFrames - 1)
          {
            if (!sector_to_timecode(&info_data[3], i + 1))
              goto exit2;
          }
          else
            info_data[3] = info_data[4] = info_data[5] = 0xFF;

          /* fill in backward_offset */
          if (i > iFrames7s - 1)
            j = i - iFrames7s;
          else
            j = 0;
          if (!sector_to_timecode(&info_data[6], j))
            goto exit2;

          /* fill in forward_offset */
          if (i < (totIFrames - iFrames7s - 1))
            j = i + iFrames7s;
          else
            j = totIFrames - 1;
          if (!sector_to_timecode(&info_data[9], j))
            goto exit2;

          if (ml_verbose)
          {
            sprintf(tmpStr, "  i frame: %d", i);
            MuxLibDisplayInfo(tmpStr);
            sprintf(tmpStr, "    Prev I Offset: %02X:%02X:%02X", info_data[0], info_data[1] & 0x7f, info_data[2] & 0x7f);
            MuxLibDisplayInfo(tmpStr);
            sprintf(tmpStr, "    Next I Offset: %02X:%02X:%02X", info_data[3], info_data[4] & 0x7f, info_data[5] & 0x7f);
            MuxLibDisplayInfo(tmpStr);
            sprintf(tmpStr, "    Back I Offset: %02X:%02X:%02X", info_data[6], info_data[7] & 0x7f, info_data[8] & 0x7f);
            MuxLibDisplayInfo(tmpStr);
            sprintf(tmpStr, "    Forw I Offset: %02X:%02X:%02X", info_data[9], info_data[10] & 0x7f, info_data[11] & 0x7f);
            MuxLibDisplayInfo(tmpStr);
          }
          if (!WriteFile(programFile, &info_data[0], 12L, &k, NULL))
          {
            sprintf(tmpStr, "Unable to write to program file %s.", programFilename);
            MuxLibDisplayError(tmpStr);
            goto exit2;
          }
          i++;
        }
      }
    }
  }
  if (i == totIFrames)
  {
    errorexit = FALSE;
    sprintf(tmpStr, "SVCD Scan Offsets: 100%% - %d of %d  I-Frames.", totIFrames, totIFrames);
    MuxLibDisplayProgress(tmpStr, 100);

    sprintf(tmpStr, "  Finished calculating SVCD scan offsets for file %s", programFilename);
    MuxLibDisplayInfo(tmpStr);
  }
  else
  {
    sprintf(tmpStr, "Could not find User Data at I-frame %d in file %s.", i, programFilename);
    MuxLibDisplayError(tmpStr);
  }

exit2:
  finish_getbits(&bs);
  return !errorexit;
}

static int doTimestamps(
Timecode_struc *SCR,
Timecode_struc *PTS,
Timecode_struc *DTS,
int frame_type)
{
  int timestamps;
  double i;
  char tmpStr[MAX_PATH];

  timestamps = TIMESTAMPS_NO;
  i = -1.0;
  switch (frame_type)
  {
    case BFRAME:
      if (ml_frame_timestamps == TIMESTAMPS_ALL)
      {
        timestamps = (ml_mplex_type > MPEG_VCD) ? MPEG2_TIMESTAMPS_PTS : MPEG1_TIMESTAMPS_PTS;
        i = get_timecode(SCR) - get_timecode(PTS);
      }
      break;
    case PFRAME:
      if (ml_frame_timestamps != TIMESTAMPS_IONLY)
      {
        timestamps = (ml_mplex_type > MPEG_VCD) ? MPEG2_TIMESTAMPS_PTS_DTS : MPEG1_TIMESTAMPS_PTS_DTS;
        i = get_timecode(SCR) - get_timecode(DTS);
      }
      break;
    case IFRAME:
      timestamps = (ml_mplex_type > MPEG_VCD) ? MPEG2_TIMESTAMPS_PTS_DTS : MPEG1_TIMESTAMPS_PTS_DTS;
      i = get_timecode(SCR) - get_timecode(DTS);
      break;
  }
  if (i > 0)
  {
    if (frame_type == BFRAME)
      sprintf(tmpStr, "    video PTS (%.02fms) underflow at pack %u by %.02fms", get_timecode(PTS) / 27000.0, current_sector, i / 27000.0);
    else
      sprintf(tmpStr, "    video DTS (%.02fms) underflow at pack %u by %.02fms", get_timecode(DTS) / 27000.0, current_sector, i / 27000.0);
    MuxLibDisplayInfo(tmpStr);
    video_underflows++;
  }
  if (i < -27000000.0)
  {
    sprintf(tmpStr, "    video DTS (%.02fms) > 1 second from SCR (%.02f) at pack %u by %.02fms",
                    get_timecode(DTS) / 27000.0, get_timecode(SCR) / 27000.0, current_sector, (i + 27000000.0) / -27000.0);
    MuxLibDisplayInfo(tmpStr);
  }
  return timestamps;
}

/******************************************************************
	Output_Video
	generates Pack/Sys_Header/Packet information from the
	video stream and writes out the new sector
******************************************************************/

int output_video (
Timecode_struc *SCR,
Timecode_struc *SCR_delay,
FILE *vunits_info,
HANDLE istream_v,
Pack_struc *pack,
Sys_header_struc *sys_header,
Buffer_struc *buffer,
Vaunit_struc *video_au,
unsigned char *picture_start,
unsigned int mux_rate,
unsigned long packet_data_size,
unsigned char marker_pack,
unsigned int which_streams,
unsigned int sh_length,
unsigned char *seq_hdr)
{
  unsigned int temp;
  unsigned long i = 1, j, k, l;
  Pack_struc *pack_ptr;
  Sys_header_struc *sys_header_ptr;
  unsigned char timestamps;
  char tmpStr[MAX_PATH];
  Timecode_struc PTSsave, DTSsave;
  int eos, alignI, tcfound, Ipresent;

  if (marker_pack)
  {
    /* let's generate pack header					*/
    create_pack(pack, SCR, mux_rate);

    if (output_sys_header || ml_always_sys_header)
    {
      /* let's generate system header					*/
      if (ml_mplex_type > MPEG_VCD)
        create_sys_header(sys_header, mux_rate, 1, 0, 0, 0, 0, 1,
		   	  audio_id, audio_buffer_scale, audio_buffer_size1,
                          audio1_id, audio1_buffer_scale, audio1_buffer_size1,
			  VIDEO_STR_0, 1, video_buffer_size/1024, which_streams);
      else
        create_sys_header(sys_header, mux_rate, 1, 0, 1, 1, 1, 1,
		   	  audio_id, audio_buffer_scale, audio_buffer_size1,
		   	  audio1_id, audio1_buffer_scale, audio1_buffer_size1,
			  VIDEO_STR_0, 1, video_buffer_size/1024, which_streams);
      output_sys_header = FALSE;
      sys_header_ptr = sys_header;
    }
    else
      sys_header_ptr = NULL;
    pack_ptr = pack;
  }
  else
  {
    pack_ptr = NULL;
    sys_header_ptr = NULL;
  }

  /* let's generate a video packet */
  timestamps = TIMESTAMPS_NO;
  tcfound = 0;
  eos = 0;
  alignI = 0;
  Ipresent = 0;

  if ((max_file_size_GOP != 0) && (bytes_output >= max_file_size_GOP))
    j = 1;
  else
    j = 0;

  /* packet starts with new access unit, use its PTS/DTS for the timestamp */
  if (*picture_start)
  {
    if (video_au->type == IFRAME)
      Ipresent = 1;
    if (ml_align_sequence_headers && Ipresent &&
       ((video_au->flags & SEQHDR_FLAG) == 0) &&
        sh_length && !do_sequence_header)
    {
      video_au->length += sh_length;
      video_au->pict_hdr_offset += sh_length;
      do_sequence_header = 1;
    }
    timestamps = doTimestamps(SCR, &video_au->PTS, &video_au->DTS, video_au->type);
    if (timestamps != TIMESTAMPS_NO)
    {
      PTSsave = video_au->PTS;
      DTSsave = video_au->DTS;
      tcfound = 1;
    }
    if (ml_VBR_multiplex)
    {
      extra_clock_cycles = get_timecode(&video_au->DTS) - get_timecode(SCR) - CLOCK_TICKS_500MS;
      if (extra_clock_cycles < 0.0)
        extra_clock_cycles = 0.0;
    }
  }

  if (video_au->length >= packet_data_size)
  {
    temp = packet_data_size;
    video_au->length -= packet_data_size;
    if (!queue_buffer (buffer, packet_data_size, &video_au->DTS))
      return FALSE;
  }
  else
  {
    temp = video_au->length;
    if (!queue_buffer (buffer, temp, &video_au->DTS))
      return FALSE;

    /* can we fill the sector? */
    while ((temp < packet_data_size) && !eos && !alignI)
    {
      if (fread(video_au, sizeof(Vaunit_struc), 1, vunits_info)==1)
      {
        *picture_start = TRUE;
        video_counter++;
        k = 0;
        l = 0;
        if (start_time)
          k = (start_time <= (unsigned int)(get_timecode(&video_au->PTS) / 27000)) && !output_on;
        if (stop_time)
          l = (stop_time <= (unsigned int)(get_timecode(&video_au->PTS) / 27000)) && output_on;
        if ((!j && !k && !l && !ml_align_sequence_headers) || (video_au->type != IFRAME))
        {
          add_to_timecode(SCR_delay, &video_au->DTS);
          add_to_timecode(SCR_delay, &video_au->PTS);
          if (!tcfound && (temp + video_au->pict_hdr_offset + 1 <= packet_data_size))
          {
            timestamps = doTimestamps(SCR, &video_au->PTS, &video_au->DTS, video_au->type);
            if (timestamps != TIMESTAMPS_NO)
            {
              PTSsave = video_au->PTS;
              DTSsave = video_au->DTS;
              tcfound = 1;
            }
          }
          if (video_au->type == IFRAME)
            Ipresent = 1;
          if (ml_VBR_multiplex)
          {
            extra_clock_cycles = get_timecode(&video_au->DTS) - get_timecode(SCR) - CLOCK_TICKS_500MS;
            if (extra_clock_cycles < 0.0)
              extra_clock_cycles = 0.0;
          }
          if (temp + video_au->length > packet_data_size)
          {
            if (!queue_buffer (buffer, packet_data_size - temp, &video_au->DTS))
              return FALSE;
            video_au->length -= packet_data_size - temp;
            temp = packet_data_size;
          }
          else
          {
            temp += video_au->length;
            if (!queue_buffer (buffer, video_au->length, &video_au->DTS))
              return FALSE;
            video_au->length = 0;
          }
        }
        else
        {
          if (j || k || l)
          {
            if (l)
              stop_output = 1;
            else
            {
              if (j)
                start_new_file = 1;
              restart_output = 1;
            }
            start_video_PTS = get_timecode(&video_au->PTS);
            if (video_au->first_frame_offset)
              start_video_PTS -= video_au->first_frame_offset;
          }
          else
          {
            add_to_timecode(SCR_delay, &video_au->DTS);
            add_to_timecode(SCR_delay, &video_au->PTS);
          }
          alignI = 1;
        }
      }
      else
        eos = 1;
    }
  }

  if (ml_mux_SVCD_scan_offsets && Ipresent && output_on)
  {
    if (fwrite(&current_sector, sizeof(unsigned int), 1, svcd_info) != 1)
    {
      sprintf("Unable to write to SVCD temporary file %s.", svcd_name);
      MuxLibDisplayError(tmpStr);
      return FALSE;
    }
  }

  if (eos && ml_OutputStats && output_on)
    status_message(STATUS_VIDEO_END);

  if (ml_mux_SVCD_scan_offsets && Ipresent && video_au->svcd_offset)
    i = video_au->svcd_offset;
  else
    i = 0;

  /* make the sector */
  if (!create_sector(&sector, pack_ptr, sys_header_ptr, packet_data_size, temp,
                    istream_v, VIDEO_STR_0, 0, 1, video_buffer_size/1024,
                    video_PSTD, &PTSsave, &DTSsave, timestamps, which_streams, 0, i,
                    do_broken_link, (start_new_file || stop_output) && ml_write_end_codes,
                    do_sequence_header, sh_length, seq_hdr))
    return FALSE;


  if (do_broken_link)
    do_broken_link = 0;
  if (do_sequence_header)
    do_sequence_header = 0;

  *picture_start = FALSE;
  if (eos || alignI)
  {
    if (eos)
      empty_vaunit_struc (video_au);
    else
      *picture_start = TRUE;
  }
  else
  {
    if (!video_au->length)
    {
      if (fread(video_au, sizeof(Vaunit_struc), 1, vunits_info)==1)
      {
        *picture_start = TRUE;
        video_counter++;
        k = 0;
        l = 0;
        if (start_time)
          k = (start_time <= (unsigned int)(get_timecode(&video_au->PTS) / 27000)) && !output_on;
        if (stop_time)
          l = (stop_time <= (unsigned int)(get_timecode(&video_au->PTS) / 27000)) && output_on;
        if ((j || k || l) && (video_au->type == IFRAME))
        {
          if (l)
            stop_output = 1;
          else
          {
            if (j)
              start_new_file = 1;
            restart_output = 1;
          }
          start_video_PTS = get_timecode(&video_au->PTS);
          if (video_au->first_frame_offset)
            start_video_PTS -= video_au->first_frame_offset;
        }
        else
        {
          add_to_timecode(SCR_delay, &video_au->DTS);
          add_to_timecode(SCR_delay, &video_au->PTS);
        }
      }
      else
      {
        if (ml_OutputStats && output_on)
          status_message(STATUS_VIDEO_END);
        empty_vaunit_struc (video_au);
      }
    }
  }

  if (output_on)
  {
    /* write out sector						*/
    if (!WriteFile(programFile, sector.buf, sector.length_of_sector, &i, NULL))
    {
      MuxLibDisplayError("Unable to write to output file.");
      return FALSE;
    }
    bytes_output += sector.length_of_sector;
  }
  return TRUE;
}


/******************************************************************
	Output_Audio
	generates Pack/Sys Header/Packet information from the
	audio stream and saves them into the sector
******************************************************************/

int output_audio (
Timecode_struc *SCR,
Timecode_struc *SCR_delay,
FILE *aunits_info,
HANDLE istream_a,
Pack_struc *pack,
Sys_header_struc *sys_header,
Buffer_struc *buffer,
Aaunit_struc *audio_au,
unsigned char *audio_frame_start,
unsigned int *audio_counter,
unsigned int *audio_underflows,
unsigned char audio_PSTD,
unsigned char aid,
unsigned char audio_subid,
unsigned char abuffer_scale,
unsigned int abuffer_size,
unsigned int mux_rate,
unsigned long packet_data_size,
unsigned char marker_pack,
unsigned int which_streams,
char *audio_restart_output)
{
  unsigned int temp;
  unsigned long i, k;
  Pack_struc *pack_ptr;
  Sys_header_struc *sys_header_ptr;
  unsigned char timestamps;
  Timecode_struc PTSsave;
  int eos, tcfound;
  char tmpStr[100];

  if (marker_pack)
  {
    /* let's generate pack header					*/
    create_pack (pack, SCR, mux_rate);

    if (output_sys_header || ml_always_sys_header)
    {
      /* let's generate system header					*/
      if (ml_mplex_type > MPEG_VCD)
        create_sys_header(sys_header, mux_rate, 1, 0, 0, 0, 0, 1,
			  audio_id, audio_buffer_scale, audio_buffer_size1,
			  audio1_id, audio1_buffer_scale, audio1_buffer_size1,
			  VIDEO_STR_0, 1, video_buffer_size/1024, which_streams );
      else
        create_sys_header(sys_header, mux_rate, 1, 0, 1, 1, 1, 1,
			  audio_id, audio_buffer_scale, audio_buffer_size1,
			  audio1_id, audio1_buffer_scale, audio1_buffer_size1,
			  VIDEO_STR_0, 1, video_buffer_size/1024, which_streams );
      output_sys_header = FALSE;
      sys_header_ptr = sys_header;
    }
    else
      sys_header_ptr = NULL;
    pack_ptr = pack;
  }
  else
  {
    pack_ptr = NULL;
    sys_header_ptr = NULL;
  }
  timestamps = TIMESTAMPS_NO;
  if (ml_vcd_audio_pad)
    k = 20;
  else
    k = 0;

  tcfound = 0;
  eos = 0;
  /* Let's generate packet					*/

  /* does a audio frame start in this packet?			*/

  /* CASE: packet starts with new access unit			*/
  if (*audio_frame_start)
  {
    timestamps = (ml_mplex_type > MPEG_VCD) ? MPEG2_TIMESTAMPS_PTS : MPEG1_TIMESTAMPS_PTS;
    PTSsave = audio_au->PTS;
    tcfound = 1;
    if (get_timecode(SCR) - get_timecode(&audio_au->PTS) > 0)
    {
      sprintf(tmpStr, "    audio PTS underflow at pack %u by %.02fms", current_sector,
		                  (get_timecode(SCR) - get_timecode(&audio_au->PTS)) / 27000.0);
      MuxLibDisplayInfo(tmpStr);
      *audio_underflows += 1;
    }
  }

  if (audio_au->length >= packet_data_size)
  {
    temp = packet_data_size;
    audio_au->length -= packet_data_size;
    if (!queue_buffer(buffer, packet_data_size, &audio_au->PTS))
      return FALSE;
  }
  else
  {
    temp = audio_au->length;
    if (!queue_buffer(buffer, audio_au->length, &audio_au->PTS))
      return FALSE;

    /* can we fill the sector? */
    while ((temp < packet_data_size) && !eos && !*audio_restart_output)
    {
      if (fread(audio_au, sizeof(Aaunit_struc), 1, aunits_info)==1)
      {
        *audio_frame_start = TRUE;
        *audio_counter = *audio_counter + 1;
        if ((!restart_output && !stop_output) || (get_timecode(&audio_au->PTS) < start_video_PTS))
        {
          add_to_timecode(SCR_delay, &audio_au->PTS);
          if (temp + audio_au->length > packet_data_size)
          {
            if (!queue_buffer(buffer, packet_data_size - temp, &audio_au->PTS))
              return FALSE;
            audio_au->length -= packet_data_size - temp;
            temp = packet_data_size;
          }
          else
          {
            temp += audio_au->length;
            if (!queue_buffer(buffer, audio_au->length, &audio_au->PTS))
              return FALSE;
            audio_au->length = 0;
          }
          if (!tcfound)
          {
            timestamps = (ml_mplex_type > MPEG_VCD) ? MPEG2_TIMESTAMPS_PTS : MPEG1_TIMESTAMPS_PTS;
            PTSsave = audio_au->PTS;
            tcfound = 1;
            if (get_timecode(SCR) - get_timecode(&audio_au->PTS) > 0)
            {
              sprintf(tmpStr, "    audio PTS underflow at pack %u by %.02fms", current_sector,
				      (get_timecode(SCR) - get_timecode(&audio_au->PTS)) / 27000.0);
              MuxLibDisplayInfo(tmpStr);
              *audio_underflows += 1;
            }
          }
        }
        else
          *audio_restart_output = 1;
      }
      else
        eos = 1;
    }
  }

  if (eos && ml_OutputStats && output_on)
    status_message(STATUS_AUDIO_END);

  if (!create_sector(&sector, pack_ptr, sys_header_ptr,
		packet_data_size, temp,
		istream_a, aid, audio_subid, abuffer_scale, abuffer_size,
		audio_PSTD, &PTSsave, NULL, timestamps, which_streams, k, 0, 0, 0, 0, 0, NULL))
    return FALSE;

  *audio_frame_start = FALSE;
  if (eos || *audio_restart_output)
  {
    if (eos)
      empty_aaunit_struc(audio_au);
    else
      *audio_frame_start = TRUE;
  }
  else
  {
    if (!audio_au->length)
    {
      if (fread(audio_au, sizeof(Aaunit_struc), 1, aunits_info)==1)
      {
        if ((!restart_output && !stop_output) || (get_timecode(&audio_au->PTS) < start_video_PTS))
          add_to_timecode(SCR_delay, &audio_au->PTS);
        else
          *audio_restart_output = 1;
        *audio_frame_start = TRUE;
        *audio_counter = *audio_counter + 1;
      }
      else
      {
        if (ml_OutputStats && output_on)
          status_message(STATUS_AUDIO_END);
        empty_aaunit_struc(audio_au);
      }
    }
  }

  if (output_on)
  {
    /* write out sector onto disk				*/
    if (!WriteFile(programFile, sector.buf, sector.length_of_sector, &i, NULL))
    {
      MuxLibDisplayError("Unable to write to output file.");
      return FALSE;
    }
    bytes_output += sector.length_of_sector;
  }
  return TRUE;
}

/******************************************************************
	Output_Padding
	generates Pack/Sys Header/Packet information for a
	padding stream and saves the sector
******************************************************************/

int output_padding (
Timecode_struc *SCR,
Pack_struc *pack,
Sys_header_struc *sys_header,
unsigned int mux_rate,
unsigned long packet_data_size,
unsigned char marker_pack,
unsigned int which_streams)
{
  unsigned long i, j, k;
  Pack_struc *pack_ptr;
  Sys_header_struc *sys_header_ptr;

  j = which_streams;
  if (marker_pack)
  {
    /* let's generate the pack header				*/
    create_pack (pack, SCR, mux_rate);

    if (output_sys_header || ml_always_sys_header)
    {
      /* let's generate the system header				*/
      if (ml_mplex_type > MPEG_VCD)
      {
        if (ml_mplex_type == MPEG_SVCD)
          i = 1;
        else
          i = 0;
        create_sys_header(sys_header, mux_rate, 1, 0, 0, (unsigned char)i, (unsigned char)i, 1,
	    		  audio_id, audio_buffer_scale, audio_buffer_size1,
	    		  audio1_id, audio1_buffer_scale, audio1_buffer_size1,
			      VIDEO_STR_0, 1, video_buffer_size/1024, j );
        output_sys_header = FALSE;
      }
      else
      {
        if (ml_mplex_type == MPEG_VCD)
        {
          if (vcd_sys_header)
          {
            vcd_sys_header = 0;
            j = STREAMS_AUDIO;
            output_sys_header = FALSE;
          }
          else
          {
            if (which_streams & STREAMS_VIDEO)
            {
              j = STREAMS_VIDEO;
              if (which_streams & STREAMS_AUDIO)
                vcd_sys_header++;
              else
                output_sys_header = FALSE;
            }
            else
            {
              j = STREAMS_AUDIO;
              output_sys_header = FALSE;
            }
          }
          create_sys_header(sys_header, mux_rate, 1, 0, 1, 1, 1, 1,
                            audio_id, audio_buffer_scale, audio_buffer_size1,
                            audio1_id, audio1_buffer_scale, audio1_buffer_size1,
                            VIDEO_STR_0, 1, video_buffer_size/1024, j );
        }
        else
        {
          create_sys_header(sys_header, mux_rate, 1, 0, 1, 1, 1, 1,
    			    audio_id, audio_buffer_scale, audio_buffer_size1,
    			    audio1_id, audio1_buffer_scale, audio1_buffer_size1,
			    VIDEO_STR_0, 1, video_buffer_size/1024, j);
          output_sys_header = FALSE;
        }
      }
      sys_header_ptr = sys_header;
    }
    else
      sys_header_ptr = NULL;
    pack_ptr = pack;
  }
  else
  {
    pack_ptr = NULL;
    sys_header_ptr = NULL;
  }

  i = packet_data_size;
  if (sys_header_ptr)
  {
    if (!(which_streams & STREAMS_VIDEO))
      i += 3;
    if (!(which_streams & STREAMS_AUDIO))
      i += 3;
    if (!(which_streams & STREAMS_AUDIO1))
      i += 3;
  }
  k = 0;
  if ((ml_mplex_type == MPEG_VCD) && sys_header_ptr)
  {
    if ((j == STREAMS_AUDIO) && ml_vcd_audio_pad)
      k = 20;
    i += 3;
  }

  /* let's generate the packet				*/
  create_sector(&sector, pack_ptr, sys_header_ptr,
		i, i,
		NULL, PADDING_STR, 0, 0, 0,
		FALSE, NULL, NULL,
		TIMESTAMPS_NO, j, k, 0, 0, 0, 0, 0, NULL);

  if (output_on)
  {
    if (!WriteFile(programFile, sector.buf, sector.length_of_sector * sizeof (unsigned char), &i, NULL))
    {
      MuxLibDisplayError("Unable to write to output file.");
      return FALSE;
    }
    bytes_output += sector.length_of_sector;
  }
  return TRUE;
}


/******************************************************************
	Output_Private2
	generates Pack/Sys Header/Packet information for a
	DVD type private 2 stream and saves the sector
        WARNING: only call for a MPEG-2 program stream
******************************************************************/

int output_private2 (
Timecode_struc *SCR,
unsigned int mux_rate)
{
  unsigned char *index;
  unsigned long i, packet_size;
  unsigned char	 audio_bound = 1;
  unsigned char	 fixed = 0;
  unsigned char	 CSPS = 0;
  unsigned char	 audio_lock = 1;
  unsigned char	 video_lock = 1;
  unsigned char	 video_bound = 1;
  unsigned int   rate_restriction_flag = 0;

  sector.length_of_sector = ml_sector_size;
  packet_size = ml_sector_size - MPEG2_PACK_HEADER_SIZE;
  index = sector.buf;

  /* let's generate the pack header				*/
  *(index++) = (unsigned char)((PACK_START)>>24);
  *(index++) = (unsigned char)((PACK_START & 0x00ff0000)>>16);
  *(index++) = (unsigned char)((PACK_START & 0x0000ff00)>>8);
  *(index++) = (unsigned char)(PACK_START & 0x000000ff);
  buffer_timecode(SCR, MPEG2_MARKER_SCR, &index);
  *(index++) = (unsigned char)(mux_rate >>14);
  *(index++) = (unsigned char)(0xff & (mux_rate >> 6));
  *(index++) = (unsigned char)(0x03 | ((mux_rate & 0x3f)<<2));
  *(index++) = (unsigned char)(RESERVED_BYTE << 3);

  /* let's generate a DVD style system header */

  *(index++) = (unsigned char)((SYS_HEADER_START)>>24);
  *(index++) = (unsigned char)((SYS_HEADER_START & 0x00ff0000)>>16);
  *(index++) = (unsigned char)((SYS_HEADER_START & 0x0000ff00)>>8);
  *(index++) = (unsigned char)(SYS_HEADER_START & 0x000000ff);

  *(index++) = (unsigned char)((SYS_HEADER_LENGTH + 3) >> 8);
  *(index++) = (unsigned char)((SYS_HEADER_LENGTH + 3) & 0xff);
  packet_size -= (SYS_HEADER_SIZE + 3);

  *(index++) = (unsigned char)(0x80 | (mux_rate >>15));
  *(index++) = (unsigned char)(0xff & (mux_rate >> 7));
  *(index++) = (unsigned char)(0x01 | ((mux_rate & 0x7f)<<1));
  *(index++) = (unsigned char)((audio_bound << 2)|(fixed << 1)|CSPS);
  *(index++) = (unsigned char)((audio_lock << 7)|
		 (video_lock << 6)|0x20|video_bound);
  *(index++) = (unsigned char)((rate_restriction_flag << 7) | (RESERVED_BYTE >> 1));

  *(index++) = 0xB9;
  *(index++) = (unsigned char) (0xc0 |
	       (1 << 5) | (232 >> 8));
  *(index++) = (unsigned char) (232 & 0xff);

  *(index++) = 0xB8;
  *(index++) = (unsigned char) (0xc0 |
	       (0 << 5) | (32 >> 8));
  *(index++) = (unsigned char) (32 & 0xff);

  *(index++) = 0xBD;
  *(index++) = (unsigned char) (0xc0 |
	       (1 << 5) | (58 >> 8));
  *(index++) = (unsigned char) (58 & 0xff);

  *(index++) = 0xBF;
  *(index++) = (unsigned char) (0xc0 |
	       (1 << 5) | (2 >> 8));
  *(index++) = (unsigned char) (2 & 0xff);

  output_sys_header = FALSE;

  /* write constant packet header data */

  *(index++) = (unsigned char)(PACKET_START)>>16;
  *(index++) = (unsigned char)(PACKET_START & 0x00ffff)>>8;
  *(index++) = (unsigned char)(PACKET_START & 0x0000ff);
  packet_size -= 6;

  if (ml_put_private2)
  {
    *(index++) = PRIVATE_STREAM2;

    if (packet_size > 980)
    {
      *(index++) = (unsigned char)((980)>>8);
      *(index++) = (unsigned char)((980)&0xff);

      for (i = 0; i < 980; i++)
        *(index++) = 0;

      packet_size -= 986;

      *(index++) = (unsigned char)(PACKET_START)>>16;
      *(index++) = (unsigned char)(PACKET_START & 0x00ffff)>>8;
      *(index++) = (unsigned char)(PACKET_START & 0x0000ff);
      *(index++) = PRIVATE_STREAM2;

      *(index++) = (unsigned char)((packet_size)>>8);
      *(index++) = (unsigned char)((packet_size)&0xff);
    }
    else
    {
      *(index++) = (unsigned char)((packet_size)>>8);
      *(index++) = (unsigned char)((packet_size)&0xff);
    }

    for (i = 0; i < packet_size; i++)
      *(index++) = 0;
  }
  else
  { /* put a padding packet instead */
    *(index++) = PADDING_STR;
    *(index++) = (unsigned char)((packet_size)>>8);
    *(index++) = (unsigned char)((packet_size)&0xff);
    for (i = 0; i < packet_size; i++)
      *(index++) = STUFFING_BYTE;
  }

  if (output_on)
  {
    if (!WriteFile(programFile, sector.buf, sector.length_of_sector * sizeof (unsigned char), &i, NULL))
    {
      MuxLibDisplayError("Unable to write to output file.");
      return FALSE;
    }
    bytes_output += ml_sector_size;
  }
  return TRUE;
}




