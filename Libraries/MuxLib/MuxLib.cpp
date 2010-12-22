// MuxLib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#define MPEGMAIN
#include "MuxLib.h"
#undef MPEGMAIN

int progress_percent = 0;

// mux callback
void MuxLibDisplayProgress(char *txt, int percent)
{
	OutputDebugString(txt);
	OutputDebugString("\n");

	progress_percent = percent;
}

void MuxLibDisplayError(char *txt)
{
	OutputDebugString(txt);
	OutputDebugString("\n");
}

void MuxLibDisplayInfo(char *txt)
{
	OutputDebugString(txt);
	OutputDebugString("\n");
}

void MuxLibYieldTime()
{
}

/*
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
*/

MUXLIB_API int GetProgressPercent()
{
	return progress_percent;
}

MUXLIB_API int GetMuxState()
{
	return ml_currentState;
}

MUXLIB_API int AVMux(char* pstrAudioFile, char* pstrVideoFile, char* pstrOutputFile, int nMuxType, long nMuxRate, bool bVBR, int nPulldown)
{
	ml_currentState = 0;
	ml_sectors_delay = 0;
	ml_video_delay_ms = 180;
	ml_audio_delay_ms = 180;
	ml_audio1_delay_ms = 180;
	ml_sector_size = 2048;
	ml_packets_per_pack = 1;
	ml_init_audio_buffer_size = 4;
	ml_init_audio1_buffer_size = 4;
	ml_init_video_buffer_size = 46;
	ml_always_sys_header = FALSE;
	ml_use_computed_bitrate = COMPBITRATE_MAX;
	ml_mplex_type = nMuxType;
	ml_vcd_audio_pad = FALSE;
	ml_mplex_pulldown_flag = nPulldown;
	ml_align_sequence_headers = 0;
	ml_user_mux_rate = nMuxRate; // 30000 found through experimentation
	ml_put_private2 = 0;
	ml_frame_timestamps = TIMESTAMPS_ALL; /* which frames to timestamp */
	ml_VBR_multiplex = bVBR;
	ml_write_pec = 1; /* write a program end code */
	ml_mux_SVCD_scan_offsets = 0;
	ml_max_file_size = 0;
	ml_mux_start_time = 0;
	ml_mux_stop_time = 0;
	ml_reset_clocks = 1;
	ml_write_end_codes = 1; /* write program end codes in split files */
	ml_set_broken_link = 1;

	switch (nMuxType)
	{
	//case MPEG_MPEG1:
	case MPEG_VCD:
		ml_sector_size = 2324;
		ml_video_delay_ms = 344;
		ml_audio_delay_ms = 344;
		ml_audio1_delay_ms = 344;
		ml_sectors_delay = 400;
		break;
	case MPEG_MPEG2:
		ml_init_video_buffer_size = 224;
		break;
	case MPEG_SVCD:
		ml_sector_size = 2324;
		ml_init_video_buffer_size = 230;
		ml_mux_SVCD_scan_offsets = 1;
		break;
	case MPEG_DVD:
		ml_frame_timestamps = TIMESTAMPS_IONLY;
		ml_align_sequence_headers = 1;
		ml_init_video_buffer_size = 232;
		ml_put_private2 = 1;
		break;
	}

	ml_OutputStats = false;
	ml_AbortMPEG = false;
	ml_verbose = 1;
	ml_statfile = 0;

	strcpy(ml_VideoFilename, pstrVideoFile);

	bool bPlexAudio = false;
	if (pstrAudioFile)
	{
		strcpy(ml_AudioFilename, pstrAudioFile);
		bPlexAudio = true;
	}
	
	strcpy(ml_Audio1Filename, "");
	strcpy(ml_ProgramFilename, pstrOutputFile);
	
	BOOL bResult = ml_domplex(1, bPlexAudio, nMuxType);
	
	ml_currentState = 0;
	progress_percent = 0;

	return bResult;
}


MUXLIB_API int AbortMux()
{
	ml_AbortMPEG = true;
	return 0;
}
