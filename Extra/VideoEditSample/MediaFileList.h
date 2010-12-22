// MediaFileList.h: Schnittstelle für die Klasse CMediaFileList.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAFILELIST_H__BB262604_D2E6_47B8_BF69_385415058B0E__INCLUDED_)
#define AFX_MEDIAFILELIST_H__BB262604_D2E6_47B8_BF69_385415058B0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MediaFile.h"

class CMediaFileList  
{
public:
	HRESULT AddAudioFile(IMediaFile **ppResult);
	void SetAllImageDurations(double dDuration, bool bConsiderTransitions);
	void SpaceImages(int iStartAudioItem, int iEndAudioItem);
	void VerifyVisualMediaOffsets();
	long GetVideoFileCount();
	HRESULT AddVideoFile(BSTR FilePath, IMediaFile ** ppResult);
	CMediaFileList();
	virtual ~CMediaFileList();

	HRESULT AddAudioFile(BSTR FilePath, IMediaFile **ppResult);
	IMediaFile* GetAudioItem(long nIndex);
	IMediaFile* GetVideoItem(long nIndex);
	long   GetAudioFileCount();
	double GetCurrentAudioLength();
	double GetCurrentVideoLength();
private:
	HRESULT GetFileInfo(BSTR Filename, double *pFramerate, double *pDuration, VARIANT_BOOL *pVideoStreamAvailable, VARIANT_BOOL *pAudioStreamAvailable, long *pWidth, long *pHeight, long *pBitrate, BSTR *pPosterFramePath);
private:
	CGenericList<IMediaFile> m_audioList;
	CGenericList<IMediaFile> m_videoList;
};

#endif // !defined(AFX_MEDIAFILELIST_H__BB262604_D2E6_47B8_BF69_385415058B0E__INCLUDED_)
