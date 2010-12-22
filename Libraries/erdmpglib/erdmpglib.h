// Export library for the erdlib. (c) 2008 Standard Mpeg

#pragma once

#ifdef ERDMPGLIB_EXPORTS
#define ERDMPGLIB_API __declspec(dllexport)
#else
#define ERDMPGLIB_API __declspec(dllimport)
#endif

#if defined(DECLARE_OUTPUT_FORMAT)
	typedef enum EnumVideoOutputFormat
	{
		VIDEOFORMAT_NONE,
		VIDEOFORMAT_MPEG1,
		VIDEOFORMAT_MPEG2,
		VIDEOFORMAT_MPEG4,
		VIDEOFORMAT_H263,
		VIDEOFORMAT_H264,
		VIDEOFORMAT_FLV,
		VIDEOFORMAT_VP6
	} VideoOutputFormat;

	typedef enum EnumAudioOutputFormat
	{
		AUDIOFORMAT_NONE,
		AUDIOFORMAT_MP3,
		AUDIOFORMAT_MP2,
		AUDIOFORMAT_AC3,
		AUDIOFORMAT_PCM,
		AUDIOFORMAT_WAV,
		AUDIOFORMAT_AAC,
		AUDIOFORMAT_AMRNB
	} AudioOutputFormat;

	typedef enum EnumSystemsOutputFormat
	{
		SYSTEMSFORMAT_NONE,
		SYSTEMSFORMAT_MPEG1,
		SYSTEMSFORMAT_MPEG2,
		SYSTEMSFORMAT_VCD,
		SYSTEMSFORMAT_SVCD,
		SYSTEMSFORMAT_DVD,
		SYSTEMSFORMAT_VCD_STILL,
		SYSTEMSFORMAT_SVCD_STILL,
		SYSTEMSFORMAT_MP4,
		SYSTEMSFORMAT_3GP,
		SYSTEMSFORMAT_MOV,
		SYSTEMSFORMAT_3G2,
		SYSTEMSFORMAT_PSP,
		SYSTEMSFORMAT_AVI,
		SYSTEMSFORMAT_RM,
		SYSTEMSFORMAT_KVCD,
		SYSTEMSFORMAT_FLV,
		SYSTEMSFORMAT_DVB
	} SystemsOutputFormat;
	
	typedef enum EnumConstraint
	{
		CONSTRAINT_NONE,
		CONSTRAINT_NTSC,
		CONSTRAINT_FILM,
		CONSTRAINT_PAL,
		CONSTRAINT_IPOD,
		CONSTRAINT_IPOD_NANO,
		CONSTRAINT_IPHONE,
		CONSTRAINT_HD,
		CONSTRAINT_H264
	} Constraint;

	typedef enum EnumBitrateMode
	{
		BITRATEMODE_CBR,
		BITRATEMODE_VBR_2PASS,
		BITRATEMODE_MVBR,
		BITRATEMODE_CQ_VBR,
		BITRATEMODE_CQ
	} BitrateMode;

	typedef enum EnumEncodeMode
	{
		ENCODEMODE_NOINTERLACE,
		ENCODEMODE_INTERLACE,
		ENCODEMODE_32PULLDOWN,
		ENCODEMODE_32PULLDOWN_INVERSE,
	} EncodeMode;

	typedef enum EnumAspectRatio
	{
		ASPECTRATIO_1TO1,
		ASPECTRATIO_4TO3,
		ASPECTRATIO_16TO9,
		ASPECTRATIO_2D11TO1,
	} AspectRatio;
#endif

typedef struct EncodeParameters
{
	char szOutputFile[1024]; // The name of the output file. This parameter is not used
	long nOutputX; // The dimensions of the output file. The encoder will rescale to this dimension if it does not match the input dimension
	long nOutputY; // Same as above
	long nInputX; // The dimensions of the input bitmaps. Have to be set accurately!
	long nInputY; // "
	long nOutputXHiResStill; // When creating a high resolution MPEG Still, this dimensions are used
	long nOutputYHiResStill; // "
	VideoOutputFormat videoOutputFormat; // The format of the video stream of the output file. Some containers allow different video streams, and this specifies them
	AudioOutputFormat audioOutputFormat; // The format of the audio stream of the output file.
	SystemsOutputFormat systemsOutputFormat; // The containing format. Has to be set. Sensible defaults are chosen for video and audio when this is set
	SystemsOutputFormat multiplexFormat; // The multiplex format. Can differ from systems format sometimes, but should usually be the same
	Constraint systemsConstraint; // Pre-defined profiles, which may need special handling internally (e.g VCD or DVD)
	long nOutputAudioBitrate; // The bitrate of the output audio file in Bytes Per Second. Some audio formats only allow specific bitrates. In this case, the next closest will be chosen
	long nOutputAudioSampleRate; // The sample rate of the output audio. The encoder will resample to this sample rate
	long nOutputAudioChannels; // The number of channels the output audio should have. The encoder will resample to this
	long nOutputVideoBitrate; // The bitrate the output file should have in kbs. This valid in CBR mode
	long nOutputVideoGOPSize; // The length of each Group Of Pictures
	long nOutputVideoQuality; // The quality of the output file in VBR. Value from 0 to 100, with 0 being highest quality
	long nOutputVideoBitrateMax; // The maximum bitrate of the output video in VBR mode
	long nOutputVideoBitrateMin; // The minimum bitrate of the output video in VBR mode
	long nOutputAudioBitrateMax; // The maximum bitrate of the audio in VBR mode
	long nOutputAudioBitrateMin; // The minimum bitrate of the audio in VBR mode
	long nOutputVideoBufferSize; // The buffer for the output video. This is selected automatically internally
	float fPixelAspectRatio; // The aspect ratio of each pixel. Set to a fraction between 0 and 1
	double dInputFPS; // The framerate of the input file. Set if you wish to convert to another framerate
	double dOutputFPS; // The framerate the output file should have. MPEG-1,2 only allows certain framerates
	long nOutputFPSDen; // The denominator of the framerate
	long nOutputFPSNum; // The numerator of the framerate
	long nMuxPacketSize; // The packet size for the multiplexor. This will be set internally
	long nMuxRate; // The mux rate for the multiplexor. This will be set internally
	float fMuxPreload; // The mux preload time for the multiplexor. This will be set internally
	float fMuxMaxDelay; // The mux delay for the multiplexor. This will be set internally
	AspectRatio aspectRatio; // The aspect ratio of the output file
	bool bUseScanOffset; // 
	BitrateMode vbrVideo; // The bitrate mode. VBR, CBR, MVBR
	BitrateMode vbrAudio; // The bitrate mode for the audio
	bool bWriteVideoStream; // Specifies if the video stream should be written. Otherwise, mpeg will be audio only
	bool bWriteAudioStream; // Specifies if the audio stream should be written. Otherwise mpeg will be video only
	bool bWriteSystemsFile; // If the systems file should be written. The systems file is the container, and is created by the multiplexer
	bool bErrorProtection; // Error protection bit for the audio
	bool bOriginal; // Original bit for the audio
	bool bCopyright; // Copyright bit for the audio
	bool bPrivate; // Private bit for the audio
	bool bMultiplex; // Says if the output should be multiplexed or not. If it is not multiplexed, two separate files will be created
	EncodeMode encodeMode; // Specifies the interlacing flags
	bool bDirectMultiplexing; // If set to false, the multiplexing will happen in a second step after elementary video and audio streams have been created
	bool bUseVideoBitrates; // if false, will use default bitrates
	bool bUseAudioBitrates; // if false, will use default bitrates
	bool bDeleteTmpAfterMultiplex; // If not doing a direct multiplex, should the temporary files be deleted?
	WAVEFORMATEX wfexAudioSrc; // reference <Mmreg.h> for this
	bool bAutoSelectDimensions; // Will select proper output dimensions based of the systemsformat parameter
	bool bAutoSelectBitrate; // Will select best bitrate for quality, size trade-off
	bool bInputHasAudio; // Indicates to encoder that it should not expect audio
	bool bInputHasVideo; // Indicates to encoder that it should not expect video
	bool bDeInterlace; // de-interlace the input video before encoding
    bool bForceInterlaceME; // Force interlace using motion estimation
	bool bForceInterlaceDCT; // Force interlace using direct cosine transformation
	bool bClosedGOP; // Should GOP be closed or open?
	long nAdditionalFlags; // Set to 0
	int nVideoCodecTag; // Set to 0
	bool bVideoStreamCopy; // Not supported
    long nVideoBitRateTolerance; // Not supported
    bool bIntraOnly; // Only I frames. 
	long nGlobalQuality; // Not supported
	__int64 nIntraMatrix; // Not supported
	__int64 nInterMatrix; // Not supported
	bool bShowMessageBox; // Should a messagebox be displayed when errors happen`?
	long nQualityMin; // Lowest quality allowed 
	long nQualityMax; // Highest quality allowed
	long nProfile; // Set profile and level bits to this in the output MPEG file
	long nLevel;
} EncodeParameters;


#ifdef  __cplusplus
extern "C" {
#endif


#if defined(VARFUNCS)
#define DECLAREFUNC(x) *x
#define VARTYPEDEF typedef
#else
#define DECLAREFUNC(x) x
#define VARTYPEDEF
#endif

VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileCreate))();
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileClose))();
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileSetEncodeParameters)) (EncodeParameters* params);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileWriteVideoBGR24))(unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileWriteVideoRGB24))(unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileWriteVideoYUV420))(unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileWriteAudio))(unsigned char *audDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileGetLibraryID))();
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFilePassThruCmd))(char* p1, unsigned char* p2, __int64 n);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileSetBufferCallback))(unsigned char* pUserData, signed __int64 (__cdecl *p)(unsigned char* pUserData, unsigned char* ptr, int buflen, int flags, signed __int64 seekPos, int nID));
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileMultiplex))(char* pstrFile1, char* pstrFile2, char* pstrOutputFile, int nFormat, int nExtra);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileLoadPreset))(char* pstrPresetName, EncodeParameters* pTargetEncodeParameters);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileInitialize))();
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileUninitialize))();
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileEndOfStream))();
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileSetParameter))(char* pstrParameterName, char* pstrParameterValue);
VARTYPEDEF long (__cdecl DECLAREFUNC(MediaFileSetFormat))(char* pstrPresetName);

// Multithreaded functions
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileCreate_MT))(__int64 contextID);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileClose_MT))(__int64 contextID);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileSetEncodeParameters_MT)) (__int64 contextID, EncodeParameters* params);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileWriteVideoRGB24_MT))(__int64 contextID, unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileWriteAudio_MT))(__int64 contextID, unsigned char *audDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFilePassThruCmd_MT))(__int64 contextID, char* p1, unsigned char* p2, __int64 n);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileSetBufferCallback_MT))(__int64 contextID, unsigned char* pUserData, signed __int64 (__cdecl *p)(unsigned char* pUserData, unsigned char* ptr, int buflen, int flags, signed __int64 seekPos, int nID));
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileInitialize_MT))(); // returns context id
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileUninitialize_MT))(__int64 contextID);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileEndOfStream_MT))(__int64 contextID);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileSetParameter_MT))(__int64 contextID, char* pstrParameterName, char* pstrParameterValue);
VARTYPEDEF __int64 (__cdecl DECLAREFUNC(MediaFileSetFormat_MT))(__int64 contextID, char* pstrPresetName);

#ifdef DECLARE_FUNC_VARIABLES
static MediaFileCreate mediaFileCreate;
static MediaFileClose mediaFileClose;
static MediaFileSetEncodeParameters mediaFileSetEncodeParameters;
static MediaFileWriteVideoBGR24 mediaFileWriteVideoBGR24;
static MediaFileWriteVideoRGB24 mediaFileWriteVideoRGB24;
static MediaFileWriteVideoYUV420 mediaFileWriteVideoYUV420;
static MediaFileWriteAudio mediaFileWriteAudio;
static MediaFileGetLibraryID mediaFileGetLibraryID;
static MediaFilePassThruCmd mediaFilePassThruCmd;
static MediaFileSetBufferCallback mediaFileSetBufferCallback;
static MediaFileMultiplex mediaFileMultiplex;
static MediaFileLoadPreset mediaFileLoadPreset;
static MediaFileInitialize mediaFileInitialize;
static MediaFileEndOfStream mediaFileEndOfStream;
static MediaFileSetParameter mediaFileSetParameter;
static MediaFileSetFormat mediaFileSetFormat;
static MediaFileUninitialize mediaFileUninitialize;

static MediaFileCreate_MT mediaFileCreate_MT;
static MediaFileClose_MT mediaFileClose_MT;
static MediaFileSetEncodeParameters_MT mediaFileSetEncodeParameters_MT;
static MediaFileWriteVideoRGB24_MT mediaFileWriteVideoRGB24_MT;
static MediaFileWriteAudio_MT mediaFileWriteAudio_MT;
static MediaFilePassThruCmd_MT mediaFilePassThruCmd_MT;
static MediaFileSetBufferCallback_MT mediaFileSetBufferCallback_MT;
static MediaFileInitialize_MT mediaFileInitialize_MT; // returns context id
static MediaFileUninitialize_MT mediaFileUninitialize_MT;
static MediaFileEndOfStream_MT mediaFileEndOfStream_MT;
static MediaFileSetParameter_MT mediaFileSetParameter_MT;
static MediaFileSetFormat_MT mediaFileSetFormat_MT;


#endif

#ifdef __cplusplus
}
#endif