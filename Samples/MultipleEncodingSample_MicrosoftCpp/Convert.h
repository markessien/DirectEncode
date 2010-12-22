// Convert.h: interface for the CConvert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONVERT_H__156339FF_9A7C_4894_9684_91790317E9B5__INCLUDED_)
#define AFX_CONVERT_H__156339FF_9A7C_4894_9684_91790317E9B5__INCLUDED_

#pragma once

// The headers for the mpeg encoder are included in stdafx.h

// ISampleGrabberCB is only neccesary when you are 
// capturing the output to a sample grabber

class CConvert
				 
{
public:
	CConvert();
	virtual ~CConvert();

	void StopConversion();
	HRESULT StartConversion();
	HRESULT WaitForCompletion();
	void SetOutputFormat(SystemsOutputFormat systemsFormat, Constraint constraint, VideoOutputFormat videoFormat, AudioOutputFormat audioFormat);
	void SetFiles(BSTR strSourceFile, BSTR strOutputFile);

private:	
	HRESULT CreateFilterGraph(IGraphBuilder **pGraph);
	HRESULT RenderOutputToFile(IBaseFilter* pSourceFilter);
	
	HRESULT LoadMPEGCodec();
	HRESULT GetFileInfo(BSTR Filename, double *pFramerate, double *pDuration, BOOL *pVideoStreamAvailable, BOOL *pAudioStreamAvailable, long *pWidth, long *pHeight);
	double GetDuration();
	double GetProgress();


private:
	// directshow filters
	CComPtr<IGraphBuilder> m_pGraph;
	CComPtr<IMediaEventEx> m_pEvent;
	CComPtr<IMediaSeeking> m_pSeeking;
	CComPtr<IMediaControl> m_pMediaControl;
	CComPtr<ICaptureGraphBuilder2> m_pBuilder;

	// mpeg objects
	CComPtr<IBaseFilter> m_pMPEGWriter; // main encoder filter
	CComPtr<IStandardMpegEncoder> m_pIMPEGEncoder; // encoder interface
	CComPtr<IStandardMpegEncoderProfile> m_pIMPEGEncoderProfile; // interface to current profile

	SystemsOutputFormat m_systemsFormat;
	Constraint m_constraint;
	VideoOutputFormat m_videoFormat;
	AudioOutputFormat m_audioFormat;

	CComBSTR m_strTargetFile;
	CComBSTR m_strSourceFile;
};

#endif // !defined(AFX_CONVERT_H__156339FF_9A7C_4894_9684_91790317E9B5__INCLUDED_)
