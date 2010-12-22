/* domplex.cpp */

//#include "main.h"
#include "stdafx.h"
#include "mplex.h"
#include "muxlib.h"
#include <crtdbg.h>
#include "locals.h"

int ml_domplex(int mplex_video, int mplex_audio, int mplex_type)
{
  char	*video_units = NULL;
  char	*audio_units = NULL;
  char  *audio1_units = NULL;

  Video_struc video_info;
  Audio_struc audio_info;
  Audio_struc audio1_info;
  unsigned int audio_total, audio1_total, video_total;
  double audio_bytes, audio1_bytes, video_bytes;
  unsigned int which_streams=0;
  double	startup_delay=0;

  if (mplex_video)
    which_streams |= STREAMS_VIDEO;
  if (mplex_audio && strlen(ml_AudioFilename))
    which_streams |= STREAMS_AUDIO;
//  if (mplex_audio && (mplex_type != MPEG_VCD) && AudioFilename1)
//    which_streams |= STREAMS_AUDIO1;

  if (!ml_check_files(&audio_bytes, &audio1_bytes, &video_bytes, which_streams))
    return FALSE;

  empty_video_struc(&video_info);
  empty_audio_struc(&audio_info);
  empty_audio_struc(&audio1_info);

  if (which_streams & STREAMS_VIDEO)
  {
	  ml_currentState = 1;
    video_units = tempnam("./","tmp_v");
    if (!ml_get_info_video (ml_VideoFilename, video_units, &video_info, &startup_delay,
			&video_total, video_bytes))
      return FALSE;
   MuxLibDisplayProgress("", 0);
  }
  else
    video_total = 0;

  if (which_streams & STREAMS_AUDIO)
  {
	  ml_currentState = 2;
    audio_units = tempnam ("./","tmp_a");
    if (!ml_get_info_audio (ml_AudioFilename, audio_units, &audio_info, &startup_delay,
			&audio_total, audio_bytes))
      return FALSE;
    MuxLibDisplayProgress("", 0);
  }
  else
    audio_total = 0;

  if (which_streams & STREAMS_AUDIO1)
  {
	  _ASSERT(FALSE);
	  /*
    audio1_units = tempnam ("./","tmpa1");
    if (!get_info_audio (AudioFilename1, audio1_units, &audio1_info, &startup_delay,
			&audio1_total, audio1_bytes))
      return FALSE;
    MuxLibDisplayProgress("", 0);
	*/
  }
  else
    audio1_total = 0;
/*
  return outputstream (doCompileRecSave->outputFileRef, video_units,
                       &video_info, audio_units, &audio_info, audio1_units, &audio1_info,
                       video_total, audio_total, audio1_total, which_streams );
					   */
	ml_currentState = 3;
  return ml_outputstream (0, video_units,
                       &video_info, audio_units, &audio_info, audio1_units, &audio1_info,
                       video_total, audio_total, audio1_total, which_streams );

}


