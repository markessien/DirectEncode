#include "stdafx.h"
#include "muxlib.h"
#include "mplex.h"
#include <math.h>

/*************************************************************************
    Functions for Time_Code computations in System Clock Reference Format
*************************************************************************/

double get_timecode(Timecode_struc *timestamp)
{
  double temp_ts;

  if (timestamp->msb)
    temp_ts = MSB_TIMECODE;
  else
    temp_ts = 0.0;
  temp_ts += timestamp->lsb * 300.0 + timestamp->reference_ext;
  if (timestamp->negative)
    return -temp_ts;
  return temp_ts;
}


void empty_timecode_struc (
Timecode_struc *timecode)
{
    timecode->msb = 0;
    timecode->lsb = 0;
    timecode->reference_ext = 0;
    timecode->negative = 0;
}

void copy_timecode (
Timecode_struc *time_original, Timecode_struc *time_copy)
{
    time_copy->lsb = time_original->lsb;
    time_copy->msb = time_original->msb;
    time_copy->reference_ext = time_original->reference_ext;
    time_copy->negative = time_original->negative;
}

void make_timecode (
double timestamp,
Timecode_struc *pointer)
{
  double temp_ts;

  if (timestamp < 0.0)
  {
    pointer->negative = 1;
    timestamp = -timestamp;
  }
  else
    pointer->negative = 0;
  temp_ts = floor(timestamp / 300.0);
  if (temp_ts > MAX_FFFFFFFF)
  {
    pointer->msb=1;
    temp_ts -= MAX_FFFFFFFF;
    pointer->lsb=(unsigned long)temp_ts;
  }
  else
  {
    pointer->msb=0;
    pointer->lsb=(unsigned long)temp_ts;
  }
  if (ml_mplex_type > MPEG_VCD)
    pointer->reference_ext = (unsigned long)(timestamp - (floor(timestamp / 300.0) * 300.0));
  else
    pointer->reference_ext = 0;
}


void add_to_timecode (
Timecode_struc *add,
Timecode_struc *to)
{
  double timestamp = get_timecode(to) + get_timecode(add);

  make_timecode(timestamp, to);
}


/*************************************************************************
    Kopiert einen TimeCode in einen Bytebuffer. Dabei wird er nach
    MPEG-Verfahren in bits aufgesplittet.

    Makes a Copy of a TimeCode in a Buffer, splitting it into bitfields
    according to MPEG-System
*************************************************************************/

void buffer_timecode (
Timecode_struc *pointer,
unsigned char  marker,
unsigned char **buffer)

{
    unsigned char temp;
  if (ml_mplex_type > MPEG_VCD)
  {
    if (marker == MPEG2_MARKER_SCR)
    {
      temp = (unsigned char)((marker << 6) | (pointer->msb << 5) |
		  ((pointer->lsb >> 27) & 0x18) | 0x4 | ((pointer->lsb >> 28) & 0x3));
      *((*buffer)++)=temp;
      temp = (unsigned char)((pointer->lsb & 0x0ff00000) >> 20);
      *((*buffer)++)=temp;
      temp = (unsigned char)(((pointer->lsb & 0x000f8000) >> 12) | 0x4 |
             ((pointer->lsb & 0x00006000) >> 13));
      *((*buffer)++)=temp;
      temp = (unsigned char)((pointer->lsb & 0x00001fe0) >> 5);
      *((*buffer)++)=temp;
      temp = (unsigned char)(((pointer->lsb & 0x0000001f) << 3) | 0x4 |
             ((pointer->reference_ext & 0x00000180) >> 7));
      *((*buffer)++)=temp;
      temp = (unsigned char)(((pointer->reference_ext & 0x0000007F) << 1) | 1);
      *((*buffer)++)=temp;
    }
    else
    {
      if (marker == MPEG2_MARKER_DTS)
        marker = 1;

      temp = (unsigned char)((marker << 4) | (pointer->msb <<3) |
             ((pointer->lsb >> 29) & 0x6) | 1);
      *((*buffer)++)=temp;
      temp = (unsigned char)((pointer->lsb & 0x3fc00000) >> 22);
      *((*buffer)++)=temp;
      temp = (unsigned char)(((pointer->lsb & 0x003f8000) >> 14) | 1);
      *((*buffer)++)=temp;
      temp = (unsigned char)((pointer->lsb & 0x7f80) >> 7);
      *((*buffer)++)=temp;
      temp = (unsigned char)(((pointer->lsb & 0x007f) << 1) | 1);
      *((*buffer)++)=temp;
    }
  }
  else
  {
    temp = (unsigned char)((marker << 4) | (pointer->msb << 3) |
                ((pointer->lsb >> 29) & 0x6) | 1);
    *((*buffer)++) = temp;
    temp = (unsigned char)((pointer->lsb & 0x3fc00000) >> 22);
    *((*buffer)++) = temp;
    temp = (unsigned char)(((pointer->lsb & 0x003f8000) >> 14) | 1);
    *((*buffer)++) = temp;
    temp = (unsigned char)((pointer->lsb & 0x7f80) >> 7);
    *((*buffer)++) = temp;
    temp = (unsigned char)(((pointer->lsb & 0x007f) << 1) | 1);
    *((*buffer)++) = temp;
  }
}

/******************************************************************
	Comp_Timecode
	liefert TRUE zurueck, wenn TS1 <= TS2 ist.

	Yields TRUE, if TS1 <= TS2.
******************************************************************/

int comp_timecode (
Timecode_struc *TS1,
Timecode_struc *TS2)
{
  return (get_timecode(TS1) <= get_timecode(TS2));

//    double Time1;
//    double Time2;

//    Time1 = (TS1->msb * MAX_FFFFFFFF) + (TS1->lsb);
//    Time2 = (TS2->msb * MAX_FFFFFFFF) + (TS2->lsb);

//   return (Time1 <= Time2);
}
