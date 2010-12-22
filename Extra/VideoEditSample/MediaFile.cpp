// MediaFile.cpp : Implementierung von CMediaFile
#include "stdafx.h"
#include "VideoEdit.h"
#include "videoeditobj.h"
#include "MediaFile.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// CMediaFile

STDMETHODIMP CMediaFile::get_PosterFrame(IPictureDisp **pVal)
{
	m_pictureDisp.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::get_Duration(double *pVal)
{
	*pVal = (m_dDuration);

	return S_OK;
}

STDMETHODIMP CMediaFile::get_Transition(BSTR *pVal)
{
	m_strTransitionGuid.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_Transition(BSTR newVal)
{
	m_strTransitionGuid = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::get_StartOffset(double *pVal)
{
	*pVal = (m_dStartOffset);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_StartOffset(double newVal)
{
	m_dStartOffset = newVal;

	return S_OK;
}


STDMETHODIMP CMediaFile::get_FilePath(BSTR *pVal)
{
	m_strFilePath.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_FilePath(BSTR newVal)
{
	m_strFilePath = newVal;
	m_strFileTitle = m_strFilePath;
	
	wchar_t* pwszTitle = wcsrchr(newVal, '\\');
	if (pwszTitle)
		m_strFileTitle = (wchar_t*)(pwszTitle + 1);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_Duration(double newVal)
{
	m_dDuration = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::get_FileTitle(BSTR *pVal)
{
	m_strFileTitle.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMediaFile::put_FileTitle(BSTR newVal)
{
	m_strFileTitle = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::put_PosterFramePath(BSTR newVal)
{
	// USES_CONVERSION;
	HBITMAP hbm = (HBITMAP)::LoadImageW(NULL, newVal, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//ASSERT(hbm);
	
	if (hbm == NULL)
		hbm = (HBITMAP)::LoadImage(_Module.m_hInstResource, (LPCTSTR)IDB_PREVIEW, IMAGE_BITMAP, 0, 0, LR_LOADTRANSPARENT);

	PICTDESC pdesc;
	pdesc.cbSizeofstruct = sizeof(pdesc);
	pdesc.picType = PICTYPE_BITMAP;
	pdesc.bmp.hbitmap = hbm;
	pdesc.bmp.hpal = NULL;

	::OleCreatePictureIndirect(&pdesc, IID_IPicture, true, (LPVOID*)&m_picture);
	m_picture->QueryInterface(IID_IPictureDisp, (void**)&m_pictureDisp);
	ASSERT(m_pictureDisp);
	ASSERT(m_picture);

	return S_OK;
}

STDMETHODIMP CMediaFile::get_IsImage(VARIANT_BOOL *pVal)
{
	*pVal = m_bIsImage;

	return S_OK;
}

STDMETHODIMP CMediaFile::put_IsImage(VARIANT_BOOL newVal)
{
	m_bIsImage = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::get_TransitionLength(double *pVal)
{
	*pVal = m_dTransitionLength;

	return S_OK;
}

STDMETHODIMP CMediaFile::put_TransitionLength(double newVal)
{
	m_dTransitionLength = newVal;

	return S_OK;
}

STDMETHODIMP CMediaFile::OverlayText(BSTR Text, long xPos, long yPos, long Width, long Height, BSTR FontFace, long FontHeight)
{
	this->m_bDoOverlay = VARIANT_TRUE;
	m_overlayText.strFontFace = FontFace;
	m_overlayText.nFontHeight = FontHeight;
	m_overlayText.xPos = xPos;
	m_overlayText.yPos = yPos;
	m_overlayText.strText = Text;
	m_overlayText.nWidth = Width;
	m_overlayText.nHeight = Height;
	return S_OK;
}

//DEL STDMETHODIMP CMediaFile::Process()
//DEL {
//DEL 
//DEL 
//DEL 	return S_OK;
//DEL }

STDMETHODIMP CMediaFile::get_DoTextOverlay(VARIANT_BOOL *pVal)
{
	*pVal = m_bDoOverlay;

	return S_OK;
}

STDMETHODIMP CMediaFile::put_DoTextOverlay(VARIANT_BOOL newVal)
{
	m_bDoOverlay = newVal;

	return S_OK;
}

//DEL STDMETHODIMP CMediaFile::get_WorkFileCount(long *pVal)
//DEL {
//DEL 	*pVal = m_nWorkListCount;
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CMediaFile::get_WorkFilePath(long Index, BSTR *pVal, double * pdDuration)
//DEL {
//DEL 	*pVal = m_workFileList[Index];
//DEL 	*pdDuration = m_workDurations[Index];
//DEL 	
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CMediaFile::DeleteWorkFiles()
//DEL {
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	if (m_bDoOverlay == VARIANT_TRUE ||
//DEL 		m_zoomInfo.bPerformZoom == true)
//DEL 	{
//DEL 		for (int i=0;i<m_nWorkListCount;i++)
//DEL 		{
//DEL 			DeleteFile(W2A(m_workFileList[i]));
//DEL 		}
//DEL 	}
//DEL 
//DEL 	return S_OK;
//DEL }

//DEL STDMETHODIMP CMediaFile::ApplyZoomEffect(double dDuration, long fps, long x, long y, long width, long height)
//DEL {
//DEL 	m_zoomInfo.bPerformZoom = true;
//DEL 	m_zoomInfo.dDuration = dDuration;
//DEL 	m_zoomInfo.fps = fps;
//DEL 	m_zoomInfo.height = height;
//DEL 	m_zoomInfo.width = width;
//DEL 	m_zoomInfo.x = x;
//DEL 	m_zoomInfo.y = y;
//DEL 
//DEL 	return S_OK;
//DEL }



HRESULT CMediaFile::SaveBitmapToFile(char* pstrFile, HDC hdc, HBITMAP hbm, BITMAP& bmp)
{
	long nSize = bmp.bmWidthBytes * bmp.bmHeight;
	BYTE* pBuffer = new BYTE[nSize + sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER )];

	// write out the file header
	BITMAPFILEHEADER bfh;
	memset( &bfh, 0, sizeof(bfh) );
	bfh.bfType = 'MB';
	bfh.bfSize = nSize + sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );
	bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );
	
	
	memcpy(pBuffer, &bfh, sizeof(bfh));

	// and the bitmap format
	//
	BITMAPINFOHEADER bih;
	memset( &bih, 0, sizeof( bih ) );
	bih.biSize = sizeof( bih );
	bih.biWidth = bmp.bmWidth;
	bih.biHeight = bmp.bmHeight;
	bih.biPlanes = bmp.bmPlanes;
	bih.biBitCount = bmp.bmBitsPixel;
	
	memcpy(&pBuffer[sizeof(bfh)], &bih, sizeof( bih ));
	
	BITMAPINFO info;
	memset(&info, 0, sizeof(info));
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

	GetDIBits(hdc, hbm, 0, bmp.bmHeight, 
			  NULL, &info, DIB_RGB_COLORS);

	GetDIBits(hdc, hbm, 0, bmp.bmHeight, 
			  &pBuffer[sizeof(bfh) + sizeof(bih)],
			  &info, DIB_RGB_COLORS);

	HANDLE hFile = ::CreateFile(pstrFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	if (hFile  != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritten = 0;
		WriteFile(hFile, pBuffer, nSize + sizeof(bfh) + sizeof(bih), &dwWritten, 0);
		ASSERT(dwWritten);

		CloseHandle(hFile);
		delete [] pBuffer;

		return S_OK;
	}

	delete [] pBuffer;
	return HRESULT_FROM_WIN32(GetLastError());
}

void CMediaFile::SetCallback(CVideoEditObj *pCallback)
{
	m_pCallback = pCallback;
}

//DEL void CMediaFile::GetLargestRectangleFit(RECT &rcSource, RECT &rcTarget, RECT &rcResult)
//DEL {
//DEL 		// The thing with a zoom is that it has got to maintain aspect ratio
//DEL 	// to prevent the zoomed in picture from stretching or squashing
//DEL 
//DEL 	int nWidth = rcSource.right - rcSource.left;
//DEL 	int nHeight = rcSource.bottom - rcSource.top;
//DEL 	float fAspect = (float)nWidth / (float)nHeight;
//DEL 
//DEL 	if (nWidth * fAspect > nHeight)
//DEL 		nWidth = nHeight * fAspect;
//DEL 	else
//DEL 		nHeight = nWidth * fAspect;
//DEL 
//DEL 	// At this point nWidth and nHeight are the width and height of the
//DEL 	// zoom out rectangle. We still have to figure out the positions
//DEL 
//DEL 
//DEL }

STDMETHODIMP CMediaFile::GetZoomOutRect(IVideoRect **rcSource, IVideoRect **rcZoomIn, IVideoRect **ppResult)
{
	long nLeft = 0, nTop = 0, nRight = 0, nBottom = 0;
	long nLeftZoom = 0, nTopZoom = 0, nRightZoom = 0, nBottomZoom = 0;
	long nWidthZoom = 0, nHeightZoom = 0, nWidth = 0, nHeight = 0;
	
	(*rcSource)->AddRef();
	(*rcZoomIn)->AddRef();
	(*ppResult)->AddRef();

	(*rcSource)->get_Left(&nLeft);
	(*rcSource)->get_Right(&nRight);
	(*rcSource)->get_Bottom(&nBottom);
	(*rcSource)->get_Top(&nTop);
	(*rcSource)->get_Width(&nWidth);
	(*rcSource)->get_Height(&nHeight);

	(*rcZoomIn)->get_Left(&nLeftZoom);
	(*rcZoomIn)->get_Right(&nRightZoom);
	(*rcZoomIn)->get_Bottom(&nBottomZoom);
	(*rcZoomIn)->get_Top(&nTopZoom);
	(*rcZoomIn)->get_Width(&nWidthZoom);
	(*rcZoomIn)->get_Height(&nHeightZoom);

	float fAspectRatioZoomRect = (float)nWidth / (float)nHeight;

	long nMiddleH = nLeftZoom + (nWidthZoom / 2);
	long nMiddleV = nTopZoom + (nHeightZoom / 2);

	if (nWidth * fAspectRatioZoomRect > nHeight)
	{
		nHeightZoom = nHeight;
		nWidthZoom = (long)(nHeightZoom * fAspectRatioZoomRect);
	}
	else
	{
		nWidthZoom = nWidth;
		nHeightZoom = (long)(nWidthZoom * fAspectRatioZoomRect);
	}

	nLeftZoom = nMiddleH - (nWidthZoom / 2);
	nRightZoom = nLeftZoom + nWidthZoom;
	nTopZoom = nMiddleV - (nHeightZoom / 2);
	nBottomZoom = nTopZoom + nHeightZoom;

	(*ppResult)->put_Left(nLeftZoom + 1);
	(*ppResult)->put_Right(nRightZoom - 1);
	(*ppResult)->put_Bottom(nBottomZoom - 1);
	(*ppResult)->put_Top(nTopZoom + 1);

	return S_OK;
}

IVideoRect* CMediaFile::CreateVideoRect(RECT rc)
{
	IVideoRect* pRect =  NULL;
 	HRESULT hr = CoCreateInstance(CLSID_VideoRect, NULL, 
 								  CLSCTX_INPROC, 
 								  IID_IVideoRect, 
								  (void **)&pRect);

	ASSERT(pRect);
	pRect->AddRef();

	pRect->put_Left(rc.left);
	pRect->put_Right(rc.right);
	pRect->put_Top(rc.top);
	pRect->put_Bottom(rc.bottom);

	return pRect;
 
}

//DEL STDMETHODIMP CMediaFile::ApplyPanEffect(double dDuration, long fps, long x, long y, long width, long height, long endpos)
//DEL {
//DEL 	m_panInfo.dDuration = dDuration;
//DEL 	m_panInfo.bPerformPan = true;
//DEL 	m_panInfo.endpos = endpos;
//DEL 	m_panInfo.fps = fps;
//DEL 	m_panInfo.height = height;
//DEL 	m_panInfo.width = width;
//DEL 	m_panInfo.x = x;
//DEL 	m_panInfo.y = y;
//DEL 
//DEL 	return S_OK;
//DEL }


int CMediaFile::LoadPicture(char* pstrPath, IPicture** ppPicture)
{
	HANDLE hFile = CreateFile(pstrPath, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	DWORD dwSize = GetFileSize(hFile, 0);
	if (dwSize == 0)
		return NULL;

	DWORD dwRead;
	BYTE* pBuff = new BYTE[dwSize];
	ReadFile(hFile, pBuff, dwSize, &dwRead, 0);

	if (dwRead == 0)
		return NULL;

	dwSize = dwRead;
	
	CloseHandle(hFile);

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwSize);
	void* pData = GlobalLock(hGlobal);
	memcpy(pData, pBuff, dwSize);
	GlobalUnlock(hGlobal);

	IStream* pStream = NULL;
	
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK)
	{
		HRESULT hr;
		if ((hr = OleLoadPicture(pStream, dwSize, FALSE, IID_IPicture,
		                         (LPVOID *)ppPicture)) == S_OK)
		{
			return 1;
		}
		else
			return NULL;

		pStream->Release();
	}
	else
		return NULL;

	return NULL;
}

STDMETHODIMP CMediaFile::ApplyMotionEffect(long hwnd, IVideoRect **rcReferenceRect, IVideoRect **rcStart, IVideoRect **rcEnd, long fps, long duration)
{
	m_motionInfo.bPerformMotion = true;
	m_motionInfo.rcEnd = VideoRectToRect(rcEnd);
	m_motionInfo.rcStart = VideoRectToRect(rcStart);
	m_motionInfo.rcReference = VideoRectToRect(rcReferenceRect);
	m_motionInfo.fps = fps;
	m_motionInfo.dDuration = duration;

	return S_OK;
}

FRECT CMediaFile::VideoRectToFRect(IVideoRect **rc)
{
	RECT rcResult;
	(*rc)->get_Left(&rcResult.left);
	(*rc)->get_Right(&rcResult.right);
	(*rc)->get_Top(&rcResult.top);
	(*rc)->get_Bottom(&rcResult.bottom);

	FRECT frcResult;
	frcResult.left = (float)rcResult.left;
	frcResult.right = (float)rcResult.right;
	frcResult.top = (float)rcResult.top;
	frcResult.bottom = (float)rcResult.bottom;

	return frcResult;
}


RECT CMediaFile::VideoRectToRect(IVideoRect **rc)
{
	RECT rcResult;
	(*rc)->get_Left(&rcResult.left);
	(*rc)->get_Right(&rcResult.right);
	(*rc)->get_Top(&rcResult.top);
	(*rc)->get_Bottom(&rcResult.bottom);

	return rcResult;
}

CMediaFile::MotionInfo& CMediaFile::GetMotionInfo(long nScreenWidth, long nScreenHeight)
{
	m_motionInfoCorrected = m_motionInfo;
	
	// Calculate the corrected rects
	
	CorrectRect(m_motionInfoCorrected.rcReference, m_motionInfo.rcStart, m_motionInfoCorrected.rcStart, nScreenWidth, nScreenHeight);
	CorrectRect(m_motionInfoCorrected.rcReference, m_motionInfo.rcEnd, m_motionInfoCorrected.rcEnd, nScreenWidth, nScreenHeight);

	return m_motionInfoCorrected;
}


void CMediaFile::CorrectRect(RECT & rcReference, RECT & rcToCorrect, RECT & rcCorrected, long nScreenWidth, long nScreenHeight)
{
	long nLeftOffset = rcToCorrect.left - rcReference.left;
	long nRightOffset = rcReference.right - rcToCorrect.right;
	long nTopOffset = rcToCorrect.top - rcReference.top ;
	long nBotOffset = rcReference.bottom - rcToCorrect.bottom;

	long nReferenceWidth = rcReference.right - rcReference.left;
	long nReferenceHeight = rcReference.bottom - rcReference.top;

	if (nReferenceWidth && nReferenceHeight)
	{
		float fLeftRatio  = (float)nLeftOffset / (float)nReferenceWidth;
		float fRightRatio = (float)nRightOffset / (float)nReferenceWidth;

		float fTopRatio = (float)nTopOffset / (float)nReferenceHeight;
		float fBotRatio = (float)nBotOffset / (float)nReferenceHeight;

		rcCorrected.left = (long)(nScreenWidth * fLeftRatio);
		rcCorrected.right = nScreenWidth - (long)(nScreenWidth * fRightRatio);
		rcCorrected.top = (long)(nScreenHeight * fTopRatio);
		rcCorrected.bottom = nScreenHeight - (long)(nScreenHeight * fBotRatio);
	}
}