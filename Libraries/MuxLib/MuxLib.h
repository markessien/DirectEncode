
#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MUXLIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MUXLIB_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

//#define MUXLIB_EXPORTS

#define MUXLIB_API
/*
#ifdef MUXLIB_EXPORTS
#define MUXLIB_API __declspec(dllexport)
#else
#define MUXLIB_API __declspec(dllimport)
#endif
*/

extern "C" MUXLIB_API int AVMux(char* pstrAudioFile, char* pstrVideoFile, char* pstrOutputFile, int nMuxType, long nMuxRate, bool bVBR, int nPullDown);
extern "C" MUXLIB_API int GetProgressPercent();
extern "C" MUXLIB_API int GetMuxState();
extern "C" MUXLIB_API int AbortMux();

#ifdef MPEGMAIN
#define EXTERN
#else
#define EXTERN extern
#endif

#define MPEG_MPEG1  0
#define MPEG_VCD    1
#define MPEG_MPEG2  2
#define MPEG_SVCD   3
#define MPEG_DVD    4

#define COMPBITRATE_NONE 0
#define COMPBITRATE_AVG  1
#define COMPBITRATE_MAX  2

#define TIMESTAMPS_ALL    0
#define TIMESTAMPS_IPONLY 1
#define TIMESTAMPS_IONLY  2

#define STREAMS_VIDEO           1
#define STREAMS_AUDIO           2
#define STREAMS_V_A             3
#define STREAMS_AUDIO1          4
#define STREAMS_V_A1            5
#define STREAMS_A_A1            6
#define STREAMS_V_A_A1          7

#define AUDIO_SYNCWORD		0xfff
#define AC3_SYNCWORD            0x0b77

// bitstream
#define BUFFER_SIZE    256*1024
#define FOUR_GB        4294967296

#define PULLDOWN_NONE 0
#define PULLDOWN_23   1
#define PULLDOWN_32   2
#define PULLDOWN_AUTO 3

#define PICTURE_START_CODE 0x100L
#define SLICE_MIN_START    0x101L
#define SLICE_MAX_START    0x1AFL
#define USER_START_CODE    0x1B2L
#define SEQ_START_CODE     0x1B3L
#define EXT_START_CODE     0x1B5L
#define SEQ_END_CODE       0x1B7L
#define GOP_START_CODE     0x1B8L
#define ISO_END_CODE       0x1B9L
#define PACK_START_CODE    0x1BAL
#define SYSTEM_START_CODE  0x1BBL

/* extension start code IDs */
#define SEQ_ID       1
#define DISP_ID      2
#define QUANT_ID     3
#define SEQSCAL_ID   5
#define PANSCAN_ID   7
#define CODING_ID    8
#define SPATSCAL_ID  9
#define TEMPSCAL_ID 10

/* picture structure */
#define TOP_FIELD     1
#define BOTTOM_FIELD  2
#define FRAME_PICTURE 3


EXTERN unsigned long ml_sectors_delay;
EXTERN unsigned long ml_video_delay_ms;
EXTERN unsigned long ml_audio_delay_ms;
EXTERN unsigned long ml_audio1_delay_ms;
EXTERN unsigned long ml_sector_size;
EXTERN unsigned long ml_packets_per_pack;
EXTERN unsigned long ml_init_audio_buffer_size;
EXTERN unsigned long ml_init_audio1_buffer_size;
EXTERN unsigned long ml_init_video_buffer_size;
EXTERN int ml_always_sys_header;
EXTERN int ml_use_computed_bitrate;
EXTERN int ml_mplex_type;
EXTERN int ml_vcd_audio_pad;
EXTERN int ml_mplex_pulldown_flag;
EXTERN int ml_align_sequence_headers;
EXTERN int ml_user_mux_rate;
EXTERN int ml_put_private2;
EXTERN int ml_frame_timestamps; /* which frames to timestamp */
EXTERN int ml_VBR_multiplex;
EXTERN int ml_write_pec; /* write a program end code */
EXTERN int ml_mux_SVCD_scan_offsets;
EXTERN unsigned int ml_max_file_size;
EXTERN unsigned int ml_mux_start_time;
EXTERN unsigned int ml_mux_stop_time;
EXTERN int ml_reset_clocks;
EXTERN int ml_write_end_codes; /* write program end codes in split files */
EXTERN int ml_set_broken_link;

EXTERN int ml_OutputStats;
EXTERN int ml_AbortMPEG;
EXTERN int ml_verbose;
EXTERN char ml_VideoFilename[255];
EXTERN char ml_AudioFilename[255];
EXTERN char ml_Audio1Filename[255];
EXTERN char ml_ProgramFilename[255];
EXTERN FILE *ml_statfile; /* file descriptors */

EXTERN int ml_currentState;

struct bitstream {
  unsigned char *bfr;
  unsigned char outbyte;
  int byteidx;
  int bitidx;
  int bufcount;
  DWORD actposlo;
  LONG actposhi;
  double totbits;
  HANDLE bitfile;
  int eobs;
  int fileOutError;
};

EXTERN unsigned char *ml_ubuffer;
int init_putbits(bitstream *bs, char *bs_filename);
void finish_putbits(bitstream *bs);
int init_getbits(bitstream *bs, char *bs_filename);
void finish_getbits(bitstream *bs);
int get1bit(bitstream *bs, unsigned int *retval);
int getbits(bitstream *bs, unsigned int *retval, int N);
void putbits(bitstream *bs, int val, int n);
void put1bit(bitstream *bs, int val);
void alignbits(bitstream *bs);
void prepareundo(bitstream *bs, bitstream *undo);
void undochanges(bitstream *bs, bitstream *old);
double bitcount(bitstream *bs);
int end_bs(bitstream *bs);
int seek_sync(bitstream *bs, unsigned int sync, int N);
int ml_domplex(int mplex_video, int mplex_audio, int mplex_type);

void MuxLibDisplayError(char *txt);
void MuxLibDisplayProgress(char *txt, int percent);
void MuxLibDisplayInfo(char *txt);
void MuxLibYieldTime();