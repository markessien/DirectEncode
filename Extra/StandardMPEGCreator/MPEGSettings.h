// MPEGSettings.h: interface for the CMPEGSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPEGSETTINGS_H__693219C7_C0E3_4F15_8759_39C5F4DFC5DE__INCLUDED_)
#define AFX_MPEGSETTINGS_H__693219C7_C0E3_4F15_8759_39C5F4DFC5DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMPEGSettings  
{
public:
	CMPEGSettings();
	virtual ~CMPEGSettings();

	void LoadSettingsFromFilter(CComPtr<IBaseFilter> pFilter);
	void ApplySettingsToFilter(CComPtr<IBaseFilter> pFilter);
	void SaveSettings(CComBSTR strPath);
	void LoadSettings(CComBSTR strPath);

	CComBSTR strGOPStructure;
	CComBSTR strInputFile;
	CComBSTR strOutputFile;
	VideoOutputFormat videoOutputFormat;
	AudioOutputFormat audioOutputFormat;
	SystemsOutputFormat systemsOutputFormat;
	Constraint constraint;
	BitrateMode bitrateMode;
	EncodeMode encodeMode;
	AspectRatio aspectRatio;
	LONG nEncodePass;
	LONG nAudioBitrate;
	LONG nAudioChannels;
	LONG nAudioSampleRate;
	BOOL bShowPreview;
	DOUBLE dOutputFramerate;
	LONG nOutputHeight;
	LONG nOutputWidth;
	LONG nVideoBitrate;
	LONG nVideoBitrateMax;
	LONG nVideoBitrateMin;
	LONG nVideoQuality;
	BOOL bPerformMultiplex;
	BOOL bClosedGOP;
	DOUBLE dStartTime;
	DOUBLE dEndTime;
};

#endif // !defined(AFX_MPEGSETTINGS_H__693219C7_C0E3_4F15_8759_39C5F4DFC5DE__INCLUDED_)
