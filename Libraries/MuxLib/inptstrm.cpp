#include "stdafx.h"
#include "consts1.h"
#include "muxlib.h"
#include "mplex.h"
#include <math.h>
#include "consts.h"
#include "locals.h"

/*************************************************************************
    File found?
*************************************************************************/

int open_file(char *name, double *bytes)
{
  HANDLE datei;
  BY_HANDLE_FILE_INFORMATION fileInfo;
  char tmpStr[MAX_PATH];

  datei = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL,
	                 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (datei == INVALID_HANDLE_VALUE)
  {
    sprintf(tmpStr, "Input file %s was not found.", name);
    MuxLibDisplayError(tmpStr);
    return TRUE;
  }
  if (!GetFileInformationByHandle(datei, &fileInfo))
  {
    sprintf(tmpStr, "Error getting size of input file %s.", name);
    CloseHandle(datei);
    MuxLibDisplayError(tmpStr);
    return TRUE;
  }
  CloseHandle(datei);
  *bytes = (double)fileInfo.nFileSizeHigh * FOUR_GB + (double)fileInfo.nFileSizeLow;
  return FALSE;
}

/*************************************************************************
    Basic Checks on MPEG Streams
*************************************************************************/

int marker_bit (bitstream *bs, unsigned int what)
{
  unsigned int retval;
  char tmpStr[132];

  if (!get1bit(bs, &retval))
    return FALSE;
  if (what != retval)
  {
    sprintf(tmpStr, "Error in MPEG stream at offset (bits) %.0f: supposed marker bit not found.", bitcount(bs));
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  return TRUE;
}



/*************************************************************************
    Check if files are valid MPEG streams
*************************************************************************/

int ml_check_files (
double *audio_bytes,
double *audio1_bytes,
double *video_bytes,
unsigned int which_streams)
{
  double bytes_1, bytes_2, bytes_3;
  unsigned int retval;
  int exiterror;
  char tmpStr[80];
  bitstream bs;

  exiterror = TRUE;
  if (which_streams & STREAMS_VIDEO)
  {
    if (open_file(ml_VideoFilename, &bytes_1))
      return FALSE;

    if (!init_getbits(&bs, ml_VideoFilename))
      goto exit1;

    if (!getbits(&bs, &retval, 32))
      goto exit1;
    if (retval != 0x1b3)
    {
      sprintf(tmpStr, "File %s is not a 11172-2 or 13818-2 Video stream.", ml_VideoFilename);
      MuxLibDisplayError(tmpStr);
      goto exit1;
    }
    else
      *video_bytes = bytes_1;
    finish_getbits(&bs);
  }
  if (which_streams & STREAMS_AUDIO)
  {
    if (open_file(ml_AudioFilename, &bytes_2))
      goto exit1;

    if (!init_getbits(&bs, ml_AudioFilename))
      goto exit1;

    if (!getbits(&bs, &retval, 12))
      goto exit1;
    if (retval != 0xfff)
    {
      finish_getbits(&bs);
      if (!init_getbits(&bs, ml_AudioFilename))
        goto exit1;
      if (seek_sync(&bs, AC3_SYNCWORD, 16))
        *audio_bytes = bytes_2;
      else
      {
	sprintf(tmpStr, "File %s is not an AC3 or MPEG Audio stream.", ml_AudioFilename);
        MuxLibDisplayError(tmpStr);
        goto exit1;
      }
    }
    else
      *audio_bytes = bytes_2;
  }

  if (which_streams & STREAMS_AUDIO1)
  {
    if (open_file(ml_Audio1Filename, &bytes_3))
      goto exit1;

    if (!init_getbits(&bs, ml_Audio1Filename))
      goto exit1;

    if (!getbits(&bs, &retval, 12))
      goto exit1;
    if (retval != 0xfff)
    {
      finish_getbits(&bs);
      if (!init_getbits(&bs, ml_Audio1Filename))
        goto exit1;
      if (seek_sync(&bs, AC3_SYNCWORD, 16))
        *audio1_bytes = bytes_3;
      else
      {
	sprintf(tmpStr, "File %s is not an AC3 or MPEG Audio stream.", ml_Audio1Filename);
        MuxLibDisplayError(tmpStr);
        goto exit1;
      }
    }
    else
      *audio1_bytes = bytes_3;
  }

  exiterror = FALSE;

exit1:
  finish_getbits(&bs);
  return !exiterror;
}


static int scan_video(char *video_file, Video_struc *video_info)
{
  bitstream bs;
  unsigned int retval, i, j, mpeg2flag, exiterror;
  unsigned int pulldown = 0, first_pulldown = 0;
  unsigned int syncword, temporal_reference;

  exiterror = TRUE;
  mpeg2flag = 0;
  video_info->pulldown = PULLDOWN_NONE;
  video_info->sh_length = 0;
  MuxLibDisplayInfo(" ");
  if (ml_mplex_pulldown_flag == PULLDOWN_AUTO)
    MuxLibDisplayInfo("  Scanning video stream for a sequence header and pulldown type ...");
  else
    MuxLibDisplayInfo("  Scanning video stream for a sequence header ...");
  if (!init_getbits(&bs, video_file))
    goto scanexit;

  if (!getbits(&bs, &retval, 32))
    goto scanexit;

  if (retval == SEQUENCE_HEADER)
  {
    j = 0;
    video_info->seq_hdr[j++] = 0;
    video_info->seq_hdr[j++] = 0;
    video_info->seq_hdr[j++] = 1;

    retval = 0xFFFFFFB3;
    while ((retval != GROUP_START) && (j < 256))
    {
      video_info->seq_hdr[j++] = (unsigned char)(retval & 0xff);
      if (!getbits(&bs, &i, 8))
        goto scanexit;
      retval = (retval << 8) | i;
      if (retval == EXT_START_CODE)
        mpeg2flag = 1;
    }
    if (retval == GROUP_START)
      video_info->sh_length = j - 3;

    /* see if the repeat first flag is set in any frame in the first GOP */
    if (mpeg2flag)
    {
      j = 0;
      while (!j)
      {
        if (!seek_sync(&bs, SYNCWORD_START, 24))
          j = 1;
        else
        {
          if (!getbits(&bs, &retval, 8))
            j = 1;
          else
          {
            syncword = (SYNCWORD_START << 8) + retval;
            switch (syncword)
            {
              case SEQUENCE_HEADER:
              case GROUP_START:
                j = 1;
                break;

              case PICTURE_START:
                j = 1;
                if (!getbits(&bs, &retval, 10))
                  break;
                temporal_reference = retval;

                if (!seek_sync(&bs, EXT_START_CODE, 32))
                  break;
                if (!getbits(&bs, &retval, 4))
                  break;
                if (retval != CODING_ID)
                  break;
                if (!getbits(&bs, &retval, 18))
                  break;
                if (!getbits(&bs, &retval, 2)) /* picture structure type */
                  break;
                if (retval != FRAME_PICTURE)
                  break;

                /* see if repeat flag is set for auto pulldown detection */
                if (!getbits(&bs, &retval, 7))
                  break;
                if (retval & 0x01)
                {
                  pulldown = 1;
                  if (!temporal_reference)
                    first_pulldown = 1;
                }
                j = 0;
                break;
            }
          }
        }
      }
      if (pulldown)
      {
        if (first_pulldown)
          video_info->pulldown = PULLDOWN_32;
        else
          video_info->pulldown = PULLDOWN_23;
      }
    }
    if (ml_mplex_pulldown_flag == PULLDOWN_AUTO)
    {
      switch (video_info->pulldown)
      {
        case PULLDOWN_32:
          MuxLibDisplayInfo("    3:2 pulldown detected ...");
          break;
        case PULLDOWN_23:
          MuxLibDisplayInfo("    2:3 pulldown detected ...");
          break;
        default:
          MuxLibDisplayInfo("    no pulldown detected ...");
      }
    }
    exiterror = FALSE;
  }
  else
  {
    MuxLibDisplayError("Invalid MPEG Video stream header.");
    goto scanexit;
  }

scanexit:
  finish_getbits(&bs);
  return !exiterror;
}

/*************************************************************************
	Get_Info_Video
	holt Informationen zu den einzelnen Access-Units (Frames) des
	Videofiles ein und speichert sie in einer temporaeren Datei
	ab. Wird spaeter zum Aufbau der gemultiplexten Datei gebraucht.

	Gets informations on the single access units (frames) of the
	video stream and saves them in a tmp file for further
	processing. We need it for building the multiplex file.
*************************************************************************/

int ml_get_info_video (
char *video_file,
char *video_units,
Video_struc *video_info,
double *startup_delay,
unsigned int *video_total,
double length)
{
  FILE* info_file;
  double prev_offset=0.0;
  double pict_offset, hdr_offset, mb_offset, ud_offset, tmp_offset;
  Vaunit_struc access_unit;
  unsigned long syncword, max_bits_in_sec, frame_count, f_rate;
  unsigned long decoding_order=0;
  unsigned long group_order=0;
  unsigned long temporal_reference;
  unsigned int picture_type;
  double secs_per_frame, secs_per_one_field, secs_per_three_fields;
  unsigned short pict_rate;
  double DTS, PTS;
  int i, pulldown_flag;
  unsigned int retval, video_count, frame_num, firstField;
  int percent, oldPercent;
  char tmpStr[80];
  int exiterror, mpeg2flag, seq_header_found = 0, gop_header_found = 0;
  bitstream bs;

  exiterror = TRUE;
  video_count = 0;
  oldPercent = -1;
  max_bits_in_sec = 0;
  mb_offset = 0.0;
  ud_offset = -1.0;
  hdr_offset = -1.0;

  if (!scan_video(video_file, video_info))
    return FALSE;

  pulldown_flag = ml_mplex_pulldown_flag;
  if ((ml_mplex_type > MPEG_VCD) && (ml_mplex_pulldown_flag == PULLDOWN_AUTO))
    pulldown_flag = video_info->pulldown;

  MuxLibDisplayInfo(" ");
  MuxLibDisplayInfo("  Scanning video stream for pictures ...");
  info_file = fopen(video_units, "wb");
  if (info_file == NULL)
  {
    sprintf(tmpStr, "Unable to create temporary video units file %s.", video_units);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  if (!init_getbits(&bs, video_file))
    goto exit2;

  if (!getbits(&bs, &retval, 32))
    goto exit2;

  if (retval==SEQUENCE_HEADER)
  {
    hdr_offset = bitcount(&bs) - 32.0; /* remember position of sequence_header */
    seq_header_found = 1;
    video_info->num_sequence++;
    if (!getbits(&bs, &retval, 12))
      goto exit2;

    video_info->horizontal_size = retval;
    if (!getbits(&bs, &retval, 12))
      goto exit2;

    video_info->vertical_size = retval;
    if (!getbits(&bs, &retval, 4))
      goto exit2;

    video_info->aspect_ratio = retval;
    if (!getbits(&bs, &retval, 4))
      goto exit2;

    pict_rate = retval;
    video_info->picture_rate = pict_rate;
    if (!getbits(&bs, &retval, 18))
      goto exit2;

    video_info->bit_rate = retval;
    if (!marker_bit(&bs, 1))
      goto exit2;

    if (!getbits(&bs, &retval, 10))
      goto exit2;

    video_info->vbv_buffer_size	= retval;
    if (!get1bit(&bs, &retval))
      goto exit2;

    video_info->CSPF = retval;
  }
  else
  {
    MuxLibDisplayError("Invalid MPEG Video stream header.");
    goto exit2;
  }

  empty_vaunit_struc (&access_unit);
  *startup_delay = 2 * MAX_FFFFFFFF;

  if (pict_rate > 0 && pict_rate < 9)
  {
    f_rate = (unsigned int)ceil(picture_rates[pict_rate]);
    secs_per_frame = 1.0 / picture_rates[pict_rate];
  }
  else
  {
    f_rate = 25;
    secs_per_frame = 1.0 / 25.0;	/* invalid pict_rate info */
  }
  if (f_rate == 30 && ((pulldown_flag == PULLDOWN_32) || (pulldown_flag == PULLDOWN_23)))
    f_rate = 24;
  secs_per_one_field = secs_per_frame / 2.0;
  secs_per_three_fields = secs_per_frame + secs_per_one_field;

  frame_count = f_rate + 1;
  mpeg2flag = FALSE;
  firstField = 0;
  do
  {
    MuxLibYieldTime();
    if (ml_AbortMPEG)
      break;

    percent = (int)floor(((bitcount(&bs) / 8.0) / length) * 100.0);
    if (percent != oldPercent)
    {
      sprintf(tmpStr, "Scanning video stream: %d%% - byte offset %.0f of %.0f.", percent, bitcount(&bs) / 8.0, length);
      MuxLibDisplayProgress(tmpStr, percent);
      oldPercent = percent;
    }

    if (seek_sync(&bs, SYNCWORD_START, 24))
    {
      if (!getbits(&bs, &retval, 8))
        goto exit2;

      syncword = (SYNCWORD_START << 8) + retval;
      switch (syncword)
      {
        case SEQUENCE_HEADER:
	  video_info->num_sequence++;
          hdr_offset = bitcount(&bs) - 32.0; /* remember position of sequence_header */
          seq_header_found = 1;
	  break;

        case EXT_START_CODE:
          mpeg2flag = TRUE;
          break;

	case GROUP_START:
	  video_info->num_groups++;
	  group_order = 0;
          if (hdr_offset < 0)
            hdr_offset = bitcount(&bs) - 32.0; /* remember position of GOP header */
          gop_header_found = 1;
	  break;

	case PICTURE_START:
          /* just in case this is the second field of a frame */
          tmp_offset = bitcount(&bs) - 32.0;
          if (!getbits(&bs, &retval, 10))
            goto exit2;
	  temporal_reference = retval;

          if (!getbits(&bs, &retval, 3))
            goto exit2;
	  picture_type = retval;

          if (mpeg2flag)
          {
            if (!seek_sync(&bs, EXT_START_CODE, 32))
              goto exit2;
            if (!getbits(&bs, &retval, 4))
              goto exit2;
            if (retval != CODING_ID)
            {
	      MuxLibDisplayError("Invalid MPEG2 Video stream, no picture coding extension present.");
              goto exit2;
            }
            if (!getbits(&bs, &retval, 18))
              goto exit2;
            if (!getbits(&bs, &retval, 2)) /* picture structure type */
              goto exit2;
            if (retval != FRAME_PICTURE)
            {
              if (!firstField)
                firstField = retval;
              else
                if (firstField != retval)
                  break;      /* second field, do not process */
            }
          }

          pict_offset = tmp_offset;
          if (hdr_offset < 0)
            tmp_offset = pict_offset;
          else
            tmp_offset = hdr_offset;

          if (frame_count > f_rate)
          {
            if (tmp_offset - mb_offset > max_bits_in_sec)
              max_bits_in_sec = (int)(tmp_offset - mb_offset);
            mb_offset = tmp_offset;
            frame_count = 0;
          }
          frame_count++;

	  /* skip access unit number 0 */
	  if (access_unit.type != 0)
	  {
            access_unit.length += (unsigned long) ceil((tmp_offset - prev_offset) / 8.0);
            prev_offset = tmp_offset;
	    if (fwrite (&access_unit, sizeof (Vaunit_struc), 1, info_file) != 1)
            {
              sprintf(tmpStr, "Error writing to temporary video units file %s.", video_units);
              MuxLibDisplayError(tmpStr);
              goto exit2;
            }
	    video_info->avg_frames[access_unit.type-1] += access_unit.length;
	  }

          access_unit.svcd_offset = 0;
          access_unit.length = 0;

          if (ml_mux_SVCD_scan_offsets && picture_type == IFRAME)
          {
            retval = 0xff;
            while ((retval != 0xb2) && (retval != 1))
            {
              if (!seek_sync(&bs, SYNCWORD_START, 24))
                goto exit2;
              if (!getbits(&bs, &retval, 8))
                goto exit2;
            }
            if (retval == 1)
              ud_offset = bitcount(&bs) - 32.0; /* remember position for the scan offset */
            else
            {
              if (!getbits(&bs, &retval, 16))
                goto exit2;
              if (retval != 0x100E)
                ud_offset = bitcount(&bs) - 48.0; /* remember position for scan offset */
              else
                ud_offset = -1; /* there is already a scan offset there */
            }

            if (ud_offset > 0)
            {
              access_unit.svcd_offset = (unsigned short) ceil((ud_offset - tmp_offset) / 8.0);
              access_unit.length = 18; // size of an SVCD scan offset user data block
            }
            ud_offset = -1;
          }

          video_count++;
	  access_unit.type = picture_type;
          if (hdr_offset >= 0)
            access_unit.pict_hdr_offset = (unsigned short int) ceil((pict_offset - hdr_offset) / 8.0);
          else
            access_unit.pict_hdr_offset = 0;
          access_unit.flags = 0;
          if (seq_header_found)
            access_unit.flags |= SEQHDR_FLAG;
          if (gop_header_found)
            access_unit.flags |= GOPHDR_FLAG;

          hdr_offset = -1;
          seq_header_found = 0;
          gop_header_found = 0;

          if ((pulldown_flag == PULLDOWN_NONE) ||
              (pulldown_flag == PULLDOWN_AUTO))
          {
	        DTS = decoding_order * secs_per_frame*CLOCKS;
	        PTS = (temporal_reference - group_order + 1 +
	           decoding_order) * secs_per_frame*CLOCKS;
            if (!group_order)
              access_unit.first_frame_offset = temporal_reference * (int)(secs_per_frame * CLOCKS);
            else
              access_unit.first_frame_offset = 0;
          }
          else
          {
            DTS = (decoding_order / 2) * secs_per_frame + (decoding_order / 2) * secs_per_three_fields;
            if (decoding_order % 2)
            {
              if (pulldown_flag == PULLDOWN_32)
                DTS += secs_per_frame;
              else
                DTS += secs_per_three_fields;
            }
            if ((pulldown_flag == PULLDOWN_23) && decoding_order)
              DTS -= secs_per_one_field;
            DTS *= CLOCKS;

            PTS = secs_per_frame;
            frame_num = temporal_reference - group_order + decoding_order;
	        PTS += (frame_num / 2) * secs_per_frame + (frame_num / 2) * secs_per_three_fields;
            if (frame_num % 2)
            {
              if (pulldown_flag == PULLDOWN_32)
                PTS += secs_per_three_fields;
              else
                PTS += secs_per_frame;
            }
            PTS = ceil(PTS * CLOCKS);
            if (!group_order)
            {
              access_unit.first_frame_offset = (temporal_reference / 2) * (unsigned int)(secs_per_frame * CLOCKS) +
                                               (temporal_reference / 2) * (unsigned int)(secs_per_three_fields * CLOCKS);
              if (temporal_reference % 2)
                if (pulldown_flag == PULLDOWN_32)
                  access_unit.first_frame_offset += (unsigned int)(secs_per_three_fields * CLOCKS);
                else
                  access_unit.first_frame_offset += (unsigned int)(secs_per_frame * CLOCKS);
            }
            else
              access_unit.first_frame_offset = 0;
          }

	  *startup_delay=(PTS < *startup_delay ? PTS : *startup_delay);

	  make_timecode (DTS, &access_unit.DTS);
	  make_timecode (PTS, &access_unit.PTS);
          if (!comp_timecode(&access_unit.PTS, &video_info->last_PTS))
            copy_timecode(&access_unit.PTS, &video_info->last_PTS);
	  decoding_order++;
	  group_order++;

	  if ((access_unit.type > 0) && (access_unit.type < 5))
	    video_info->num_frames[access_unit.type-1]++;

	  video_info->num_pictures++;
	  break;

	case SEQUENCE_END:
	  pict_offset = bitcount(&bs);
          access_unit.length = (unsigned long) ceil((pict_offset - prev_offset) / 8.0);
          if (fwrite (&access_unit, sizeof (Vaunit_struc), 1, info_file) != 1)
          {
            sprintf(tmpStr, "Error writing to temporary video file %s.", video_units);
            MuxLibDisplayError(tmpStr);
            goto exit2;
          }
	  video_info->avg_frames[access_unit.type-1]+= access_unit.length;
	  prev_offset = pict_offset;
	  video_info->num_seq_end++;
          video_count++;
	  break;
      }
    }
    else
      break;
  } while (!end_bs(&bs));

  if (!ml_AbortMPEG)
  {
    sprintf(tmpStr, "  Found %d picture headers.", video_info->num_pictures);
    MuxLibDisplayInfo(tmpStr);

    video_info->stream_length = prev_offset / 8.0;
    for (i=0; i<4; i++)
      if (video_info->num_frames[i]!=0)
	video_info->avg_frames[i] /= video_info->num_frames[i];

    if (secs_per_frame >0.)
    {
      if (f_rate == 30 && ((pulldown_flag == PULLDOWN_32) || (pulldown_flag == PULLDOWN_23)))
      {
	    if (pict_rate == 4)
		  secs_per_frame = 1.0 / 23.976;
		else
		  secs_per_frame = 1.0 / 24.0;
	  }
	  else
		secs_per_frame = 1.0 / picture_rates[pict_rate];
      // set max computed bitrate to max over any one second
      video_info->comp_max_bit_rate = (unsigned int)ceil((double)max_bits_in_sec/400.);
      // set avg computed bitrate to avg over any one second
      video_info->comp_avg_bit_rate = (unsigned int)ceil (video_info->stream_length/
	   (double)(video_info->num_pictures)/secs_per_frame/1250.)*25;
    }
    else
    {
      video_info->comp_max_bit_rate = 0;
      video_info->comp_avg_bit_rate = 0;
    }
    exiterror = FALSE;
    *video_total = video_count;
  }

exit2:
  finish_getbits(&bs);
  fclose(info_file);
  if (exiterror)
    unlink(video_units);
  else
    output_info_video(video_info);
  return !exiterror;
}

/*************************************************************************
	Output_Info_Video
	gibt Ubersicht ueber gesammelte Informationen aus

	Prints information on video access units
*************************************************************************/

void output_info_video (
Video_struc *video_info)
{
  char tmpStr[132];

  MuxLibDisplayInfo("  Video stream information");
  sprintf(tmpStr, "    Stream length : %.0f",video_info->stream_length);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    Total time (seconds) : %u",(unsigned int)(get_timecode(&video_info->last_PTS) / CLOCKS));
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    Sequence start : %u",video_info->num_sequence);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    Sequence end : %u",video_info->num_seq_end);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    No. Pictures : %u",video_info->num_pictures);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    No. Groups : %u",video_info->num_groups);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    No. I Frames : %u avg. size %u bytes",
	video_info->num_frames[0],video_info->avg_frames[0]);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    No. P Frames : %u avg. size %u bytes",
	video_info->num_frames[1],video_info->avg_frames[1]);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    No. B Frames : %u avg. size %u bytes",
	video_info->num_frames[2],video_info->avg_frames[2]);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    No. D Frames : %u avg. size %u bytes",
	video_info->num_frames[3],video_info->avg_frames[3]);
  MuxLibDisplayInfo(tmpStr);

  sprintf(tmpStr, "    Horizontal size : %u",video_info->horizontal_size);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    Vertical size : %u",video_info->vertical_size);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    Aspect ratio : %1.4f",ratio[video_info->aspect_ratio]);
  MuxLibDisplayInfo(tmpStr);

  if (video_info->picture_rate == 0)
    MuxLibDisplayInfo("    Picture rate : forbidden");
  else
  {
    if (video_info->picture_rate <9)
    {
       sprintf(tmpStr, "    Picture rate : %2.3f frames/sec", picture_rates[video_info->picture_rate]);
       switch (video_info->pulldown)
       {
         case PULLDOWN_32:
           strcat(tmpStr, ",  3:2 pulldown detected");
           break;
         case PULLDOWN_23:
           strcat(tmpStr, ",  2:3 pulldown detected");
           break;
       }
    }
    else
       sprintf(tmpStr, "    Picture rate : %x reserved",video_info->picture_rate);
    MuxLibDisplayInfo(tmpStr);
  }

  if (video_info->bit_rate == 0x3ffff)
  {
    video_info->bit_rate = 0;
    MuxLibDisplayInfo("    Bit rate : variable");
  }
  else

    if (video_info->bit_rate == 0)
	   MuxLibDisplayInfo("    Bit rate : forbidden");
    else
    {
	   sprintf(tmpStr, "    Bit rate : %u bytes/sec (%u bits/sec)",
	       video_info->bit_rate*50,video_info->bit_rate*400);
      MuxLibDisplayInfo(tmpStr);
    }

  sprintf(tmpStr, "    Computed avg rate : %u bytes/sec (%u bits/sec)",
          video_info->comp_avg_bit_rate*50, video_info->comp_avg_bit_rate*400);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    Computed max rate : %u bytes/sec (%u bits/sec)",
          video_info->comp_max_bit_rate*50, video_info->comp_max_bit_rate*400);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    Vbv buffer size : %u bytes",video_info->vbv_buffer_size*2048);
  MuxLibDisplayInfo(tmpStr);
  sprintf(tmpStr, "    CSPF : %u",video_info->CSPF);
  MuxLibDisplayInfo(tmpStr);
  if ((ml_mplex_type == MPEG_SVCD) && (video_info->picture_rate != 3) && (video_info->picture_rate != 4))
    MuxLibDisplayInfo("  WARNING: SVCD frame rate should be either 25 fps or 29.97 fps");
}

/*************************************************************************
	Output_Info_Audio
	gibt gesammelte Informationen zu den Audio Access Units aus.

	Prints information on audio access units
*************************************************************************/

void output_info_audio (
Audio_struc *audio_info)
{
  unsigned int layer;
  unsigned long bitrate;
  char tmpStr[132];

  if (audio_info->layer)
  {                                   /* MPEG */
    layer = 3 - audio_info->layer;
    bitrate = bitrate_index[layer][audio_info->bit_rate];

    MuxLibDisplayInfo("  MPEG audio stream information");
    sprintf(tmpStr, "    Stream length : %.0f",audio_info->stream_length);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Syncwords : %u",audio_info->num_syncword);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Frames : %u size %u bytes",
    	audio_info->num_frames[0],audio_info->size_frames[0]);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Frames : %u size %u bytes",
	   audio_info->num_frames[1],audio_info->size_frames[1]);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Layer : %u",1+layer);
    MuxLibDisplayInfo(tmpStr);

    if (audio_info->protection == 0)
      MuxLibDisplayInfo("    CRC checksums : yes");
    else
      MuxLibDisplayInfo("    CRC checksums : no");

    if (audio_info->bit_rate == 0)
	   MuxLibDisplayInfo("    Bit rate : free");
    else
      if (audio_info->bit_rate == 0xf)
	     MuxLibDisplayInfo("    Bit rate : reserved");
      else
      {
	     sprintf(tmpStr, "    Bit rate : %u bytes/sec (%u kbit/sec)",
		    bitrate*125, bitrate);
        MuxLibDisplayInfo(tmpStr);
      }

    if (audio_info->frequency == 3)
	   MuxLibDisplayInfo("    Frequency : reserved");
    else
    {
	   sprintf(tmpStr, "    Frequency : %2.1f kHz",
		  frequency[audio_info->frequency]);
      MuxLibDisplayInfo(tmpStr);
    }

    sprintf(tmpStr, "    Mode : %u %s",
	   audio_info->mode, modetxt[audio_info->mode]);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Mode extension : %u",audio_info->mode_extension);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Copyright bit : %u %s",
	   audio_info->copyright,copyrighttxt[audio_info->copyright]);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Original/Copy : %u %s",
	   audio_info->original_copy,originaltxt[audio_info->original_copy]);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Emphasis : %u %s",
	   audio_info->emphasis,emphasistxt[audio_info->emphasis]);
    MuxLibDisplayInfo(tmpStr);
  }
  else
  {               /* AC3 */
    bitrate = audio_info->bit_rate;

    MuxLibDisplayInfo("  AC3 audio stream information");
    sprintf(tmpStr, "    Stream length : %.0f",audio_info->stream_length);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Syncwords : %u",audio_info->num_syncword);
    MuxLibDisplayInfo(tmpStr);
    sprintf(tmpStr, "    Frames : %u size %u bytes",
    	audio_info->num_frames[0],audio_info->size_frames[0]);
    MuxLibDisplayInfo(tmpStr);

	 sprintf(tmpStr, "    Bit rate : %u bytes/sec (%u kbit/sec)",
		 bitrate*128, bitrate);
    MuxLibDisplayInfo(tmpStr);

	 sprintf(tmpStr, "    Frequency : %2.1f kHz",
		ac3_frequency[audio_info->frequency]);
    MuxLibDisplayInfo(tmpStr);
  }
}

/*************************************************************************
	Get_Info_Audio
	holt Informationen zu den einzelnen Audio Access Units
	(Audio frames) ein und speichert sie in einer temporaeren
	Datei ab.

	gets information on the single audio access units (audio frames)
	and saves them into a tmp file for further processing.
*************************************************************************/

int ml_get_info_audio (
char *audio_file,
char *audio_units,
Audio_struc *audio_info,
double *startup_delay,
unsigned int *audio_total,
double length)
{
  FILE* info_file;
  double offset_bits = 0.0;
  unsigned int framesize;
  unsigned int padding_bit;
  unsigned int skip;
  unsigned int decoding_order=0;
  double PTS;
  double samples_per_second;
  Aaunit_struc access_unit;
  unsigned int i;
  unsigned int retval, audio_count;
  int percent, oldPercent;
  int exiterror;
  char tmpStr[132];
  bitstream bs;

  exiterror = TRUE;
  audio_count = 0;
  oldPercent = -1;

  MuxLibDisplayInfo(" ");
  MuxLibDisplayInfo("  Scanning audio stream for access units information");
  info_file = fopen (audio_units, "wb");
  if (info_file == NULL)
  {
    sprintf(tmpStr, "Unable to create temporary audio units file %s.", audio_units);
    MuxLibDisplayInfo(tmpStr);
    return FALSE;
  }
  if (!init_getbits(&bs, audio_file))
    goto exit3;

  empty_aaunit_struc (&access_unit);

  if (!getbits(&bs, &retval, 12))
    goto exit3;

  if (retval==AUDIO_SYNCWORD)
  {
    if (!marker_bit(&bs, 1))
      goto exit3;
    audio_info->num_syncword++;
    if (!getbits(&bs, &retval, 2))
      goto exit3;
    audio_info->layer = retval;
    if (!get1bit(&bs, &retval))
      goto exit3;
    audio_info->protection = retval;
    if (!getbits(&bs, &retval, 4))
      goto exit3;
    audio_info->bit_rate = retval;
    if (!getbits(&bs, &retval, 2))
      goto exit3;
    audio_info->frequency = retval;
    if (!get1bit(&bs, &retval))
      goto exit3;
    padding_bit = retval;
    if (!get1bit(&bs, &retval))
      goto exit3;
    if (!getbits(&bs, &retval, 2))
      goto exit3;
    audio_info->mode = retval;
    if (!getbits(&bs, &retval, 2))
      goto exit3;
    audio_info->mode_extension = retval;
    if (!get1bit(&bs, &retval))
      goto exit3;
    audio_info->copyright = retval;
    if (!get1bit(&bs, &retval))
      goto exit3;
    audio_info->original_copy = retval;
    if (!getbits(&bs, &retval, 2))
      goto exit3;
    audio_info->emphasis = retval;

    framesize = (unsigned int)(bitrate_index[3-audio_info->layer][audio_info->bit_rate] /
	    frequency[audio_info->frequency] * slots [3-audio_info->layer]);
    audio_info->size_frames[0] = framesize;
    audio_info->size_frames[1] = framesize+1;

    access_unit.length = audio_info->size_frames[padding_bit];

    samples_per_second = (double)frequency [audio_info->frequency];

    PTS = decoding_order * samples [3-audio_info->layer] /
	      samples_per_second * 27000. + *startup_delay;
    make_timecode (PTS, &access_unit.PTS);
    decoding_order++;

    if (fwrite (&access_unit, sizeof (Aaunit_struc),1, info_file) != 1)
    {
      sprintf(tmpStr, "Error writing to temporary audio units file %s.", audio_units);
      MuxLibDisplayError(tmpStr);
      goto exit3;
    }
    audio_count++;
    audio_info->num_frames[padding_bit]++;

    do
    {
      MuxLibYieldTime();
      if (ml_AbortMPEG)
        break;

      percent = (int)floor(((bitcount(&bs) / 8.0) / length) * 100.0);
      if (percent != oldPercent)
      {
        sprintf(tmpStr, "Scanning audio stream: %d%% - byte offset %.0f of %.0f.", percent, bitcount(&bs) / 8.0, length);
        MuxLibDisplayProgress(tmpStr, percent);
        oldPercent = percent;
      }

      skip=access_unit.length-4;
      if (skip & 0x1)
        if (!getbits(&bs, &retval, 8))
          goto exit3;

      if (skip & 0x2)
        if (!getbits(&bs, &retval, 16))
          goto exit3;

      skip = skip >> 2;

      for (i = 0; i < skip; i++)
	if (!getbits(&bs, &retval, 32))
          if (end_bs(&bs))
            break;
          else
            goto exit3;

      offset_bits = bitcount(&bs);

      if (!getbits(&bs, &retval, 12))
      {
        if (!end_bs(&bs))
          goto exit3;
        else
          break;
      }

      if (retval == AUDIO_SYNCWORD)
      {
	if (!marker_bit(&bs, 1))
          goto exit3;
	audio_info->num_syncword++;
	if (!getbits(&bs, &retval, 9))
          goto exit3;

        if (!get1bit(&bs, &retval))
          goto exit3;
	padding_bit = retval;
	access_unit.length = audio_info->size_frames[padding_bit];

	PTS = decoding_order * samples [3-audio_info->layer] /
		    samples_per_second * 27000. + *startup_delay;
	make_timecode (PTS, &access_unit.PTS);

	decoding_order++;

	if (fwrite (&access_unit, sizeof (Aaunit_struc),1, info_file) != 1)
        {
          sprintf(tmpStr, "Error writing to temporary audio units file %s.", audio_units);
          MuxLibDisplayError(tmpStr);
          goto exit3;
        }
        audio_count++;
	audio_info->num_frames[padding_bit]++;

	if (!getbits(&bs, &retval, 9))
          goto exit3;
      }
      else
        break;
    } while (!end_bs(&bs));
  }
  else
  {
    finish_getbits(&bs);
    if (!init_getbits(&bs, audio_file))
      goto exit3;
    if (seek_sync(&bs, AC3_SYNCWORD, 16))
    {
      audio_info->layer = 0;          /* let'em know it's AC3 */
      audio_info->num_syncword++;

      if (!getbits(&bs, &retval, 16)) /* CRC field */
        goto exit3;

      if (!getbits(&bs, &retval, 2))  /* sample rate code */
        goto exit3;
      audio_info->frequency = retval;

      if (!getbits(&bs, &retval, 6))  /* frame size code */
        goto exit3;
      framesize = ac3_frame_size[audio_info->frequency][retval >> 1];
      if ((retval & 1) && (audio_info->frequency == 1))
        framesize++;
      framesize = framesize << 1;

      audio_info->bit_rate = ac3_bitrate_index[retval >> 1];

      audio_info->protection = 0;
      audio_info->mode = 0;
      audio_info->mode_extension = 0;
      audio_info->copyright = 0;
      audio_info->original_copy = 0;
      audio_info->emphasis = 0;

      audio_info->size_frames[0] = framesize;

      access_unit.length = framesize;

      samples_per_second = (double)ac3_frequency [audio_info->frequency];

      PTS = decoding_order * 1536 /
           samples_per_second * 27000. + *startup_delay;
      make_timecode (PTS, &access_unit.PTS);
      decoding_order++;

      if (fwrite (&access_unit, sizeof (Aaunit_struc),1, info_file) != 1)
      {
        sprintf(tmpStr, "Error writing to temporary audio units file %s.", audio_units);
        MuxLibDisplayError(tmpStr);
        goto exit3;
      }
      audio_count++;
      audio_info->num_frames[0]++;

      do
      {
        MuxLibYieldTime();
        if (ml_AbortMPEG)
          break;

        percent = (int)floor(((bitcount(&bs) / 8.0) / length) * 100.0);
        if (percent != oldPercent)
        {
          sprintf(tmpStr, "Scanning audio stream: %d%% - byte offset %.0f of %.0f.", percent, bitcount(&bs) / 8.0, length);
          MuxLibDisplayProgress(tmpStr, percent);
          oldPercent = percent;
        }

        skip = framesize - 5;
        for (i = 0; i < skip; i++)
        {
          if (!getbits(&bs, &retval, 8))
            break;
        }

        offset_bits = bitcount(&bs);

        if (seek_sync(&bs, AC3_SYNCWORD, 16))
        {
          audio_info->num_syncword++;

          if (!getbits(&bs, &retval, 16)) /* CRC field */
            goto exit3;

          if (!getbits(&bs, &retval, 2))  /* sample rate code */
            goto exit3;

          if (!getbits(&bs, &retval, 6))  /* frame size code */
            goto exit3;
          framesize = ac3_frame_size[audio_info->frequency][retval >> 1];
          if ((retval & 1) && (audio_info->frequency == 1))
            framesize++;
          framesize = framesize << 1;

          access_unit.length = framesize;

          PTS = decoding_order * 1536 /
            samples_per_second * 27000. + *startup_delay;
          make_timecode (PTS, &access_unit.PTS);

          decoding_order++;

          if (fwrite (&access_unit, sizeof (Aaunit_struc),1, info_file) != 1)
          {
            sprintf(tmpStr, "Error writing to temporary audio units file %s.", audio_units);
            MuxLibDisplayError(tmpStr);
            goto exit3;
          }
          audio_count++;
          audio_info->num_frames[0]++;
        }
        else
          break;
      } while (!end_bs(&bs));
    }
    else
    {
      MuxLibDisplayError("Only MPEG and AC3 audio stream formats are supported.");
      goto exit3;
    }
  }

  if (!ml_AbortMPEG)
  {
    sprintf(tmpStr, "  Found %d audio frame headers.", audio_info->num_syncword);
    MuxLibDisplayInfo(tmpStr);

    audio_info->stream_length = offset_bits / 8.0;
    exiterror = FALSE;
    *audio_total = audio_count;
  }

exit3:
  finish_getbits(&bs);
  fclose(info_file);
  if (exiterror)
    unlink(audio_units);
  else
    output_info_audio(audio_info);
  return !exiterror;
}

