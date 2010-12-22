/* bits.c */

#include "stdafx.h"
#include "muxlib.h"
#include "mplex.h"
#include <malloc.h>
#include <math.h>
#include "locals.h"

/* initialize buffer, call once before first putbits or alignbits */
static int init_putbits(bitstream *bs, char *bs_filename)
{
  char tmpStr[MAX_PATH];

  bs->bitfile = CreateFile(bs_filename, GENERIC_WRITE, FILE_SHARE_READ,
	                       NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (bs->bitfile == INVALID_HANDLE_VALUE)
  {
    sprintf(tmpStr, "Unable to open file %s for writing.", bs_filename);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  bs->bfr = (unsigned char*)malloc(BUFFER_SIZE);
  if (!bs->bfr)
  {
    CloseHandle(bs->bitfile);
    sprintf(tmpStr, "Unable to allocate memory for bitstream file %s.", bs_filename);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  bs->bitidx = 8;
  bs->byteidx = 0;
  bs->totbits = 0.0;
  bs->outbyte = 0;
  bs->fileOutError = FALSE;
  return TRUE;
}

static void finish_putbits(bitstream *bs)
{
  DWORD bytesWritten;

  if (bs->bitfile)
  {
    if ((bs->byteidx) && (!bs->fileOutError))
      WriteFile(bs->bitfile, bs->bfr, bs->byteidx, &bytesWritten, NULL);
    CloseHandle(bs->bitfile);
    bs->bitfile = NULL;
  }
  if (bs->bfr)
  {
    free(bs->bfr);
    bs->bfr = NULL;
  }
}

static void putbyte(bitstream *bs)
{
  DWORD bytesWritten;
  BOOL ret;

  if (!bs->fileOutError)
  {
    bs->bfr[bs->byteidx++] = bs->outbyte;
    if (bs->byteidx == BUFFER_SIZE)
    {
      ret = WriteFile(bs->bitfile, bs->bfr, BUFFER_SIZE, &bytesWritten, NULL);
	  if (!ret || (bytesWritten != BUFFER_SIZE))
        bs->fileOutError = TRUE;
      bs->byteidx = 0;
    }
  }
  bs->bitidx = 8;
}

/* write rightmost n (0<=n<=32) bits of val to outfile */
static void putbits(bitstream *bs, int val, int n)
{
  int i;
  unsigned int mask;

  mask = 1 << (n - 1); /* selects first (leftmost) bit */
  for (i = 0; i < n; i++)
  {
    bs->totbits += 1;
    bs->outbyte <<= 1;
    if (val & mask)
      bs->outbyte |= 1;
    mask >>= 1; /* select next bit */
    bs->bitidx--;
    if (bs->bitidx == 0) /* 8 bit buffer full */
      putbyte(bs);
  }
}

/* write rightmost bit of val to outfile */
void put1bit(bitstream *bs, int val)
{
  bs->totbits += 1;
  bs->outbyte <<= 1;
  if (val & 0x1)
    bs->outbyte |= 1;
  bs->bitidx--;
  if (bs->bitidx == 0) /* 8 bit buffer full */
    putbyte(bs);
}

/* Prepare a upcoming undo at the beginning of a GOP */
void prepareundo(bitstream *bs, bitstream *undo)
{
  memcpy(ml_ubuffer, bs->bfr, BUFFER_SIZE);
  bs->actposhi = 0;
  bs->actposlo = SetFilePointer(bs->bitfile, 0, &bs->actposhi, FILE_CURRENT);
  if (bs->actposlo == 0xFFFFFFFF)
  {
	if (GetLastError() != NO_ERROR)
      bs->fileOutError = TRUE;
  }
  *undo = *bs;
}

/* Reset old status, undo all changes made up to a point */
void undochanges(bitstream *bs, bitstream *old)
{
  memcpy(bs->bfr, ml_ubuffer, BUFFER_SIZE);
  bs->actposlo = SetFilePointer(bs->bitfile, bs->actposlo, &bs->actposhi, FILE_BEGIN);
  if (bs->actposlo == 0xFFFFFFFF)
  {
	if (GetLastError() != NO_ERROR)
      bs->fileOutError = TRUE;
  }
  *bs = *old;
}

/* zero bit stuffing to next byte boundary (5.2.3, 6.2.1) */
void alignbits(bitstream *bs)
{
  if (bs->bitidx != 8)
    putbits(bs, 0, bs->bitidx);
}

/* return total number of generated bits */
double bitcount(bitstream *bs)
{
  return bs->totbits;
}

static int refill_buffer(bitstream *bs)
{
  DWORD bytesRead;
  BOOL ret;

  ret = ReadFile(bs->bitfile, bs->bfr, BUFFER_SIZE, &bytesRead, NULL);
  if (!ret || !bytesRead)
  {
    bs->eobs = TRUE;
    return FALSE;
  }
  bs->bufcount = bytesRead;
  return TRUE;
}

/* open the device to read the bit stream from it */
int init_getbits(bitstream *bs, char *bs_filename)
{
  char tmpStr[MAX_PATH];

  bs->bitfile = CreateFile(bs_filename, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL,
	                       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (bs->bitfile == INVALID_HANDLE_VALUE)
  {
    sprintf(tmpStr, "Unable to open file %s for reading.", bs_filename);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  bs->bfr = (unsigned char*)malloc(BUFFER_SIZE);
  if (!bs->bfr)
  {
    CloseHandle(bs->bitfile);
    sprintf(tmpStr, "Unable to allocate memory for bitstream file %s.", bs_filename);
    MuxLibDisplayError(tmpStr);
    return FALSE;
  }
  bs->byteidx = 0;
  bs->bitidx = 8;
  bs->totbits = 0.0;
  bs->bufcount = 0;
  bs->eobs = FALSE;
  if (!refill_buffer(bs))
  {
    if (bs->eobs)
    {
      sprintf(tmpStr, "Unable to read from file %s.", bs_filename);
      MuxLibDisplayError(tmpStr);
      return FALSE;
    }
  }
  return TRUE;
}

/*close the device containing the bit stream after a read process*/
void finish_getbits(bitstream *bs)
{
  if (bs->bitfile)
    CloseHandle(bs->bitfile);
  bs->bitfile = NULL;
}

int masks[8]={0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};

/*read 1 bit from the bit stream */
int get1bit(bitstream *bs, unsigned int *retval)
{
  unsigned int bit;

  if (bs->eobs)
    return FALSE;

  bit = (bs->bfr[bs->byteidx] & masks[bs->bitidx - 1]) >> (bs->bitidx - 1);
  bs->totbits += 1;
  bs->bitidx--;
  if (!bs->bitidx)
  {
    bs->bitidx = 8;
    bs->byteidx++;
    if (bs->byteidx == bs->bufcount)
    {
      if (bs->bufcount == BUFFER_SIZE)
        refill_buffer(bs);
      else
        bs->eobs = TRUE;
      bs->byteidx = 0;
    }
  }
  *retval = bit;
  return TRUE;
}

/*read N bits from the bit stream */
int getbits(bitstream *bs, unsigned int *retval, int N)
{
  unsigned int val = 0;
  int i = N;
  unsigned int j;

  // Optimize: we are on byte boundary and want to read multiple of bytes!
  if ((bs->bitidx == 8) && ((N & 7) == 0))
  {
    i = N >> 3;
    while (i > 0)
    {
      if (bs->eobs)
        return FALSE;
      val = (val << 8) | bs->bfr[bs->byteidx];
      bs->byteidx++;
      bs->totbits += 8;
      if (bs->byteidx == bs->bufcount)
      {
        if (bs->bufcount == BUFFER_SIZE)
          refill_buffer(bs);
        else
          bs->eobs = TRUE;
        bs->byteidx = 0;
      }
      i--;
    }
  }
  else
  {
    while (i > 0)
    {
      if (bs->eobs)
        return FALSE;

      j = (bs->bfr[bs->byteidx] & masks[bs->bitidx - 1]) >> (bs->bitidx - 1);
      bs->totbits += 1;
      bs->bitidx--;
      if (!bs->bitidx)
      {
        bs->bitidx = 8;
        bs->byteidx++;
        if (bs->byteidx == bs->bufcount)
        {
          if (bs->bufcount == BUFFER_SIZE)
            refill_buffer(bs);
          else
            bs->eobs = TRUE;
          bs->byteidx = 0;
        }
      }
      val = (val << 1) | j;
      i--;
    }
  }
  *retval = val;
  return TRUE;
}

/*return the status of the bit stream*/
/* returns 1 if end of bit stream was reached */
/* returns 0 if end of bit stream was not reached */

int end_bs(bitstream *bs)
{
  return bs->eobs;
}

/*this function seeks for a byte aligned sync word (max 32 bits) in the bit stream and
  places the bit stream pointer right after the sync.
  This function returns 1 if the sync was found otherwise it returns 0  */

int seek_sync(bitstream *bs, unsigned int sync, int N)
{
  unsigned int val, val1;
  unsigned int maxi = (int)pow(2.0, (double)N) - 1;

  while (bs->bitidx != 8)
    if (!get1bit(bs, &val))
      return FALSE;
  if (!getbits(bs, &val, N))
    return FALSE;

  while ((val & maxi) != sync)
  {
    val <<= 8;
    if (!getbits(bs, &val1, 8))
      return FALSE;
    val |= val1;
  }
  return TRUE;
}
