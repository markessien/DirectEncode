#include "stdafx.h"
#include "muxlib.h"
#include "mplex.h"
#include "locals.h"

/*************************************************************************
	Create_Sector
	creates a complete sector.
	Also copies Pack and Sys_Header informations into the
	sector buffer, then reads a packet full of data from
	the input stream into the sector buffer.
*************************************************************************/

static unsigned char data_buffer[MAX_SECTOR_SIZE];

int create_sector (
Sector_struc 	 *sector,
Pack_struc	 *pack,
Sys_header_struc *sys_header,
unsigned int 	 packet_size,
unsigned int     partial_packet_size,
HANDLE		 inputstream,
unsigned char 	 type,
unsigned char    subtype,
unsigned char 	 buffer_scale,
unsigned int 	 buffer_size,
unsigned char 	 buffers,
Timecode_struc   *PTS,
Timecode_struc   *DTS,
unsigned char 	 timestamps,
unsigned int     which_streams,
unsigned int     sector_pad,
unsigned int     svcd_offset,
unsigned int     write_broken_link,
unsigned int     write_seq_end,
unsigned int     write_seq_hdr,
unsigned int     sh_length,
unsigned char    *seq_hdr)
{
  int i, j, data_bytes, numFound, syncFound, firstOffset, pad_size;
  unsigned char *index, *tmpPtr;
  unsigned int data_size, stuff_size, k;
  DWORD l;

  index = sector->buf;
  sector->length_of_sector=0;

  /* Should we copy Pack Header information ? */

  if (pack != NULL)
  {
    if (ml_mplex_type > MPEG_VCD)
      i = MPEG2_PACK_HEADER_SIZE;
    else
      i = MPEG1_PACK_HEADER_SIZE;
    memcpy (index, pack->buf, i);
    index += i;
    sector->length_of_sector += i;
  }

  /* Should we copy System Header information ? */

  if (sys_header != NULL)
  {
    i = sizeof(sys_header->buf);

    /* only one stream? 3 to 6 bytes less in sys header */
    if (!(which_streams & STREAMS_VIDEO))
      i -= 3;
    if (!(which_streams & STREAMS_AUDIO))
      i -= 3;
    if (!(which_streams & STREAMS_AUDIO1))
      i -= 3;

    memcpy (index, sys_header->buf, i);
    index += i;
    sector->length_of_sector += i;
  }

  /* write constant packet header data */

  *(index++) = (unsigned char)(PACKET_START)>>16;
  *(index++) = (unsigned char)(PACKET_START & 0x00ffff)>>8;
  *(index++) = (unsigned char)(PACKET_START & 0x0000ff);
  *(index++) = type;

  /* if it's a padding packet handle it here */

  if (type == PADDING_STR)
  {
    i = 0;
    if (which_streams == STREAMS_AUDIO)
      i = 5;
    if (ml_mplex_type > MPEG_VCD)
      data_bytes = packet_size + MPEG2_AFTER_PACKET_LENGTH - i;
    else
      data_bytes = packet_size + MPEG1_AFTER_PACKET_LENGTH - i;
    *(index++) = (unsigned char)(data_bytes >> 8);
    *(index++) = (unsigned char)(data_bytes & 0xff);
    if (ml_mplex_type < MPEG_MPEG2)
    {
      *(index++) = 0x0F;
      for (j = 0; j < data_bytes - 1; j++)
        *(index++) = (unsigned char) STUFFING_BYTE;
    }
    else
      for (j = 0; j < data_bytes; j++)
        *(index++)=(unsigned char) STUFFING_BYTE;
  }
  else
  {
    /* if partial_packet_size != packet_data_size then write a padding packet after */
    /* the data packet to keep the sector length constant. This is done as long as  */
    /* there is enough room for a padding packet (at least 7 bytes), if not, put in */
    /* stuff_size stuffing bytes                                                    */

    if (packet_size != partial_packet_size)
    {
      data_size = partial_packet_size;
      pad_size = packet_size - partial_packet_size;
    }
    else
    {
      data_size = packet_size;
      pad_size = 0;
    }

    /* check if we have enough data, if not increase stuffing/padding */
    i = data_size;

    if (write_seq_hdr && sh_length)
    {
      data_bytes = sh_length;
      for (j = 0; j < data_bytes; j++)
        data_buffer[j] = seq_hdr[j];
    }
    else
      data_bytes = 0;

    if (svcd_offset)
    {
      if (!ReadFile(inputstream, &data_buffer[data_bytes], svcd_offset, &l, NULL))
      {
		MuxLibDisplayError("Error reading from an input file.");
		return FALSE;
	  }
      data_bytes += l;
      if (l != svcd_offset)
        pad_size += i - l;
      else
      {
        j = data_bytes;
        data_buffer[j++] = 0;
        data_buffer[j++] = 0;
        data_buffer[j++] = 1;
        data_buffer[j++] = 0xB2;  /* user_data_start_code */
        data_buffer[j++] = 0x10;  /* tag_name = scan information */
        data_buffer[j++] = 0x0E;  /* U_length */
        data_buffer[j++] = 0x00;
        data_buffer[j++] = 0x80;
        data_buffer[j++] = 0x80;  /* Previous_I_offset */
        data_buffer[j++] = 0x00;
        data_buffer[j++] = 0x80;
        data_buffer[j++] = 0x80;  /* Next_I_offset */
        data_buffer[j++] = 0x00;
        data_buffer[j++] = 0x80;
        data_buffer[j++] = 0x80;  /* Backward_offset */
        data_buffer[j++] = 0x00;
        data_buffer[j++] = 0x80;
        data_buffer[j++] = 0x80;  /* Forward_offset */
        data_bytes += 18;
      }
    }
    if (!ReadFile(inputstream, &data_buffer[data_bytes], i - data_bytes, &l, NULL))
    {
      MuxLibDisplayError("Error reading from an input file.");
	  return FALSE;
	}
	data_bytes += l;
    if (data_bytes != i)
      pad_size += i - data_bytes;

    if (write_seq_end && pad_size > 4)
    {
      data_buffer[data_bytes++] = 0;
      data_buffer[data_bytes++] = 0;
      data_buffer[data_bytes++] = 1;
      data_buffer[data_bytes++] = 0xB7; /* write in a sequence end code */
      pad_size -= 4;
    }

    if (write_broken_link)
    {
      i = 0;
      k = 0xFFFFFFFF;
      while ((k != GROUP_START) && (i < data_bytes))
        k = (k << 8) | data_buffer[i++];
      if (k == GROUP_START)
        data_buffer[i + 3] = data_buffer[i + 3] | 0x20;
    }

    if (type == PRIVATE_STREAM1)
      data_bytes += 4;

    if (pad_size < 7)
    {
      stuff_size = pad_size;
      pad_size = 0;
    }
    else
      stuff_size = 0;

    if (ml_mplex_type > MPEG_VCD)
    {
      i = 0;
      if (type != 0xE0)
        i = 5;
      *(index++) = (unsigned char)((data_bytes + stuff_size + MPEG2_AFTER_PACKET_LENGTH - i) >> 8);
      *(index++) = (unsigned char)((data_bytes + stuff_size + MPEG2_AFTER_PACKET_LENGTH - i) & 0xff);
      if (ml_mplex_type == MPEG_SVCD)
        *(index++) = 0x81; /* set the original bit */
      else
        *(index++) = 0x80;
      if (timestamps == TIMESTAMPS_NO)
        *(index++) = TIMESTAMPS_NO | buffers;
      else
        *(index++) = (timestamps << 6) | buffers;

      if (type == 0xE0)
        *(index++) = 13 + stuff_size; /* PES_header_data_length */
      else
        *(index++) = 8 + stuff_size; /* PES_header_data_length without DTS's */

      /* should we write PTS, PTS & DTS or nothing at all ? */

      switch (timestamps)
      {
        case MPEG2_TIMESTAMPS_PTS:
          buffer_timecode(PTS, MARKER_JUST_PTS, &index);
          copy_timecode(PTS, &sector->TS);
          break;

        case MPEG2_TIMESTAMPS_PTS_DTS:
          buffer_timecode(PTS, MARKER_PTS, &index);
          buffer_timecode(DTS, MPEG2_MARKER_DTS, &index);
          copy_timecode(DTS, &sector->TS);
          break;
      }

      /* should we write buffer info ? */

      if (buffers)
      {
        *(index++) = 0x1E;
        *(index++) = (unsigned char) (0x40 | (buffer_scale << 5) | (buffer_size >> 8));
        *(index++) = (unsigned char) (buffer_size & 0xff);
      }

      i = stuff_size;
      if (timestamps == TIMESTAMPS_NO)
      {
        if (type == 0xE0)
          i += 10;
        else
          i += 5;
      }
      else
        if ((timestamps == MPEG2_TIMESTAMPS_PTS) && (type == 0xE0))
          i += 5;
      if (!buffers)
        i += 3;
      for (j = 0; j < i; j++)
        *(index++)=(unsigned char) STUFFING_BYTE;
    }
    else
    {
      i = 0;
      if (type != 0xE0)
        i = 5;
      *(index++) = (unsigned char)((data_bytes + stuff_size + MPEG1_AFTER_PACKET_LENGTH - i) >> 8);
      *(index++) = (unsigned char)((data_bytes + stuff_size + MPEG1_AFTER_PACKET_LENGTH - i) & 0xff);

      i = stuff_size;
      if (!buffers)
        i += 2;
      if (timestamps == TIMESTAMPS_NO)
      {
        if (type != 0xE0)
          i += 4;
        else
          i += 9;
      }
      else
        if ((timestamps == MPEG1_TIMESTAMPS_PTS) && (type == 0xE0))
          i += 5;

      for (j = 0; j < i; j++)
        *(index++) = STUFFING_BYTE;

      /* soll Buffer Info angegeben werden ? */
      /* should we write buffer info ? */

      if (buffers)
      {
        *(index++) = (unsigned char) (0x40 | (buffer_scale << 5) | (buffer_size >> 8));
        *(index++) = (unsigned char) (buffer_size & 0xff);
      }
      /* should we write PTS, PTS & DTS or the no timestamp marker ? */

      switch (timestamps)
      {
        case TIMESTAMPS_NO:
          *(index++) = MARKER_NO_TIMESTAMPS;
          break;

        case MPEG1_TIMESTAMPS_PTS:
          buffer_timecode(PTS, MARKER_JUST_PTS, &index);
          copy_timecode(PTS, &sector->TS);
          break;

        case MPEG1_TIMESTAMPS_PTS_DTS:
          buffer_timecode(PTS, MARKER_PTS, &index);
          buffer_timecode(DTS, MPEG1_MARKER_DTS, &index);
          copy_timecode(DTS, &sector->TS);
          break;
      }
    }

    if (type == PRIVATE_STREAM1)
    {
      *(index++) = subtype;
      tmpPtr = index; // remember for AC3 data
      *(index++) = 0; // num of AC3 syncwords in packet
      *(index++) = 0; // hi offset of first AC3 syncword
      *(index++) = 0; // lo offset of first AC3 syncword (starting at 1)
      data_bytes -= 4;
    }

    memcpy(index, data_buffer, data_bytes);
    if (type == PRIVATE_STREAM1)
    {
      numFound = 0;
      syncFound = 0;
      firstOffset = 0;
      for (j = 0; j < data_bytes; j++)
      {
        switch (syncFound)
        {
          case 0:
            if (index[j] == 0x0b)
              syncFound = 1;
            break;
          case 1:
            if (index[j] == 0x77)
            {
              numFound++;
              if (numFound == 1)
                firstOffset = j;
            }
            syncFound = 0;
        }
      }
      tmpPtr[0] = (unsigned char) numFound;
      tmpPtr[1] = (unsigned char) (firstOffset >> 8);
      tmpPtr[2] = (unsigned char) (firstOffset & 0xff);
    }
    index += data_bytes;

    if (type == PRIVATE_STREAM1)
    {
      packet_size += 4;
      data_bytes += 4;
    }

    if (pad_size) /* write a padding packet */
    {
      *(index++) = (unsigned char)(PACKET_START)>>16;
      *(index++) = (unsigned char)(PACKET_START & 0x00ffff)>>8;
      *(index++) = (unsigned char)(PACKET_START & 0x0000ff);
      *(index++) = PADDING_STR;
      *(index++) = (unsigned char)((pad_size - 6) >> 8);
      *(index++) = (unsigned char)((pad_size - 6) & 0xff);
      if (ml_mplex_type < MPEG_MPEG2)
      {
        *(index++) = 0x0F;
        for (i = 0; i < pad_size - 7; i++)
          *(index++) = (unsigned char) STUFFING_BYTE;
      }
      else
        for (i = 0; i < pad_size - 6; i++)
          *(index++) = (unsigned char) STUFFING_BYTE;
    }
  }

  if (sector_pad)
  {
    for (k = 0; k < sector_pad; k++)
      *(index++) = 0;
  }

  /* write other struct data */
  i = 0;
  if (((type != 0xE0) && (type != PADDING_STR)) || (which_streams == STREAMS_AUDIO))
    i = 5;
  if (ml_mplex_type > MPEG_VCD)
    sector->length_of_sector += packet_size + sector_pad + PACKET_HEADER_SIZE + MPEG2_AFTER_PACKET_LENGTH - i;
  else
    sector->length_of_sector += packet_size + sector_pad + PACKET_HEADER_SIZE + MPEG1_AFTER_PACKET_LENGTH - i;
  sector->length_of_packet_data = data_bytes;
  return TRUE;
}

/*************************************************************************
	Create_Pack
	erstellt in einem Buffer die spezifischen Pack-Informationen.
	Diese werden dann spaeter von der Sector-Routine nochmals
	in dem Sektor kopiert.

	writes specifical pack header information into a buffer
	later this will be copied from the sector routine into
	the sector buffer
*************************************************************************/

void create_pack (
Pack_struc	 *pack,
Timecode_struc   *SCR,
unsigned int 	 mux_rate)
{
    unsigned char *index;

    index = pack->buf;

    *(index++) = (unsigned char)((PACK_START)>>24);
    *(index++) = (unsigned char)((PACK_START & 0x00ff0000)>>16);
    *(index++) = (unsigned char)((PACK_START & 0x0000ff00)>>8);
    *(index++) = (unsigned char)(PACK_START & 0x000000ff);
    if (ml_mplex_type > MPEG_VCD)
    {
      buffer_timecode(SCR, MPEG2_MARKER_SCR, &index);
      *(index++) = (unsigned char)(mux_rate >> 14);
      *(index++) = (unsigned char)(0xff & (mux_rate >> 6));
      *(index++) = (unsigned char)(0x03 | ((mux_rate & 0x3f) << 2));
      *(index++) = (unsigned char)(RESERVED_BYTE << 3);
    }
    else
    {
      buffer_timecode(SCR, MPEG1_MARKER_SCR, &index);
      *(index++) = (unsigned char)(0x80 | (mux_rate >> 15));
      *(index++) = (unsigned char)(0xff & (mux_rate >> 7));
      *(index++) = (unsigned char)(0x01 | ((mux_rate & 0x7f) << 1));
    }
    copy_timecode(SCR, &pack->SCR);
}


/*************************************************************************
	Create_Sys_Header
	erstelle in einem Buffer die spezifischen Sys_Header
	Informationen. Diese werden spaeter von der Sector-Routine
	nochmals zum Sectorbuffer kopiert.

	writes specifical system header information into a buffer
	later this will be copied from the sector routine into
	the sector buffer
*************************************************************************/

void create_sys_header (
Sys_header_struc *sys_header,
unsigned int	 rate_bound,
unsigned char	 audio_bound,
unsigned char	 fixed,
unsigned char	 CSPS,
unsigned char	 audio_lock,
unsigned char	 video_lock,
unsigned char	 video_bound,

unsigned char 	 stream1,
unsigned char 	 buffer1_scale,
unsigned int 	 buffer1_size,
unsigned char 	 stream2,
unsigned char 	 buffer2_scale,
unsigned int 	 buffer2_size,
unsigned char 	 stream3,
unsigned char 	 buffer3_scale,
unsigned int 	 buffer3_size,
unsigned int     which_streams)
{
  unsigned char *index;
  unsigned int rate_restriction_flag = 0;

  index = sys_header->buf;

  /* see which streams we are using */

  if ((which_streams & STREAMS_AUDIO) && (which_streams & STREAMS_AUDIO1))
    audio_bound = 2;
  if (!(which_streams & STREAMS_AUDIO) && !(which_streams & STREAMS_AUDIO1))
    audio_bound = 0;
  if (!(which_streams & STREAMS_VIDEO))
    video_bound = 0;

  // write the sys header code in flipped msb/lsb
  *(index++) = (unsigned char)((SYS_HEADER_START)>>24);
  *(index++) = (unsigned char)((SYS_HEADER_START & 0x00ff0000)>>16);
  *(index++) = (unsigned char)((SYS_HEADER_START & 0x0000ff00)>>8);
  *(index++) = (unsigned char)(SYS_HEADER_START & 0x000000ff);

  // after the header comes the length of the packet. This is dependent on
  // the streams we have.

  // if whe have both a1 and a, the packet has SYS_HEADER_LENGTH
  if (which_streams == STREAMS_V_A_A1)
  {
    *(index++) = (unsigned char)(SYS_HEADER_LENGTH >> 8);
    *(index++) = (unsigned char)(SYS_HEADER_LENGTH & 0xff);
  }
  else
  {
	//if just STREAMS_V_A without a1, then we have SYS_HEADER_LENGTH-3
    if (which_streams == STREAMS_V_A)
    {
      *(index++) = (unsigned char)((SYS_HEADER_LENGTH-3) >> 8);
      *(index++) = (unsigned char)((SYS_HEADER_LENGTH-3) & 0xff);
    }
    else
    {
		// otherwise, we have SYS_HEADER_LENGTH-6. It appears only
		// a single video stream. When we add a high res video still
		// it will appear different, since we can have two video streams
      *(index++) = (unsigned char)((SYS_HEADER_LENGTH-6) >> 8);
      *(index++) = (unsigned char)((SYS_HEADER_LENGTH-6) & 0xff);
    }
  }

  // so we have dedicated 2 bytes for th length of the header. Now we
  // write the rest of the stuff. From analysis, we see that
  // switch (MPEG_START_CODE_PATTERN | buf[pos + 6])  will give us the
  // mpeg type. pos + 6 may give us either 9 bytes or 6 bytes
  // #define MPEG_START_CODE_PATTERN  ((uint32_t) 0x00000100). Note that
  // it is a 32bit int

  *(index++) = (unsigned char)(0x80 | (rate_bound >>15));
  *(index++) = (unsigned char)(0xff & (rate_bound >> 7));
  *(index++) = (unsigned char)(0x01 | ((rate_bound & 0x7f)<<1));
  *(index++) = (unsigned char)((audio_bound << 2)|(fixed << 1)|CSPS);
  *(index++) = (unsigned char)((audio_lock << 7)|
               (video_lock << 6)|0x20|video_bound);

  if (ml_mplex_type > MPEG_VCD)
    *(index++) = (unsigned char)((rate_restriction_flag << 7) | (RESERVED_BYTE >> 1));
  else
    *(index++) = (unsigned char) RESERVED_BYTE;

  if (which_streams & STREAMS_VIDEO)
  {
    *(index++) = stream3;
    *(index++) = (unsigned char) (0xc0 |
                 (buffer3_scale << 5) | (buffer3_size >> 8));
    *(index++) = (unsigned char) (buffer3_size & 0xff);
  }

  if (which_streams & STREAMS_AUDIO)
  {
    *(index++) = stream1;
    *(index++) = (unsigned char) (0xc0 |
                 (buffer1_scale << 5) | (buffer1_size >> 8));
    *(index++) = (unsigned char) (buffer1_size & 0xff);
  }

  if (which_streams & STREAMS_AUDIO1)
  {
    *(index++) = stream2;
    *(index++) = (unsigned char) (0xc0 |
                 (buffer2_scale << 5) | (buffer2_size >> 8));
    *(index) = (unsigned char) (buffer2_size & 0xff);
  }
}
