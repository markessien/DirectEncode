#pragma once

#include "stream.h"

class CVideoStream : public CStream
{
public:
	CVideoStream(void);
	~CVideoStream(void);
	
public:
	HRESULT Load(IWMProfile* pWMProfile);
	long GetVideoWidth(void);
	long GetVideoHeight(void);
	long GetKeyFrameFreq(void);
	long GetQuality(void);
	double GetFramerate(void);
	CComBSTR GetDescription(void);
	HRESULT CreateNew(IWMProfile* pWMProfile);
	void SetVideoCodec(long nIndex);
	void SetVideoDimensions(int cx, int cy);
	void SetVBR(bool bVBR);
	void SetQuality(long nQuality);
	void SetFramerate(double dFPS);
	void SetKeyFramerate(long nRate);
	void SetPasses(long nPasses);
	void SetBestVideoCodec(long nIndex);
	void SetSourceInfo(double fps, long cx, long cy);
	void SetAutoDimensions(bool bVal);
	void SetAutoBitrate(bool bVal);
	void SetDimensionsFromSrc(bool bVal);
	bool GetDimensionsFromSrc(void);
	bool GetAutoDimensions();
	bool GetAutoBitrate();

private:
	HRESULT SetCBRSettings(IWMStreamConfig* pStreamConfig);
	HRESULT SetVBRSettings(IWMStreamConfig* pStreamConfig);

private:
	CComBSTR m_strDescription;
	bool m_bDimFromSrc;
	double m_dFramerate;
	int m_nVideoX;
    int m_nVideoY;
	int m_nKeyframe;
    int m_nQuality;
	bool m_bAutoDimensions; // auto reduce dim if src smaller
	bool m_bAutoFramerate; // same with fps
	bool m_bSrcFramerate;
	bool m_bAutoBitrate;
	bool m_bVBR;
	long m_nMinVideoBitrate;
	long m_nMaxVideoBitrate;
	long m_nVideoCodec;
	long m_nBestVideoCodec;
	double m_nKeyFramerate;
	long m_nSrcX;
	long m_nSrcY;
	double m_fSrcFramerate;
	long m_nVBRConstrain;// 0 = quality based, 1 = unconstrained, 2 = constrained
public:

	bool GetAutomaticFramerate(void);
	void SetAutoFramerate(bool bVal);
	void SetFramerateFromSrc(bool bVal);
	bool GetFramerateFromSrc(void);
	void DestroyObjects(void);
};
