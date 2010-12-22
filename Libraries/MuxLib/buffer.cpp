#include "stdafx.h"
#include "muxlib.h"
#include "mplex.h"
#include <malloc.h>
#include "locals.h"

/******************************************************************
	Buffer_Empty

	Remove all entries from FIFO buffer list.
******************************************************************/

void buffer_empty(Buffer_struc *buffer)
{
  Buffer_queue *pointer;

  while (buffer->first != NULL)
  {
    pointer = buffer->first;
    buffer->first = buffer->first->next;
    if (pointer)
      free (pointer);
  }
}

/******************************************************************
	Buffer_Clean

	Remove entries from FIFO buffer list, if their DTS is
	less than actual SCR. These packet data have been already
	decoded and have been removed from the system target
	decoder's elementary stream buffer.
******************************************************************/

void buffer_clean(Buffer_struc *buffer, Timecode_struc *SCR)
{
  Buffer_queue *pointer;

  while ((buffer->first != NULL) &&
	(comp_timecode(&buffer->first->DTS, SCR)))
  {
    pointer = buffer->first;
    buffer->first = buffer->first->next;
    if (pointer)
      free (pointer);
  }
}

/******************************************************************
	Buffer_Space

	returns free space in the buffer
******************************************************************/

int buffer_space(Buffer_struc *buffer)
{
  unsigned int used_bytes;
  Buffer_queue *pointer;

  pointer=buffer->first;
  used_bytes = 0;

  while (pointer != NULL)
  {
    used_bytes += pointer->size;
    pointer = pointer->next;
  }

  return (buffer->max_size - used_bytes);
}

/******************************************************************
	Queue_Buffer

	adds entry into the buffer FIFO queue
******************************************************************/

int queue_buffer(Buffer_struc *buffer, unsigned int bytes, Timecode_struc *TS)
{
  Buffer_queue *pointer;

  pointer = buffer->first;
  if (pointer == NULL)
  {
    buffer->first = (Buffer_queue*) malloc (sizeof (Buffer_queue));
    if (buffer->first == NULL)
    {
      MuxLibDisplayError("Unable to allocate memory for queue_buffer.");
      return FALSE;
    }
    buffer->first->size = bytes;
    buffer->first->next=NULL;
    copy_timecode (TS, &buffer->first->DTS);
  }
  else
  {
    while ((pointer->next)!=NULL)
      pointer = pointer->next;

    pointer->next = (Buffer_queue*) malloc (sizeof (Buffer_queue));
    if (pointer->next == NULL)
    {
      MuxLibDisplayError("Unable to allocate memory for queue_buffer.");
      return FALSE;
    }
    pointer->next->size = bytes;
    pointer->next->next = NULL;
    copy_timecode (TS, &pointer->next->DTS);
  }
  return TRUE;
}
