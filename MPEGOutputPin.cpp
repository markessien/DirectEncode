// MPEGOutputPin.cpp: implementation of the CMPEGOutputPin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MPEGOutputPin.h"
#include "MPEGFilterInterface.h"
#include "MPEGObj.h"
#include "mpegfilter.h"
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMPEGOutputPin::CMPEGOutputPin(TCHAR *pName,
                               CMPEGObj *pObj,
                               HRESULT *phr,
                               LPCWSTR pPinName,
                               int PinNumber) : 

								m_cOurRef(0), 
								m_pObj(pObj), 
								m_nPinNumber(PinNumber),
								CBaseOutputPin(pName, (CBaseFilter*)pObj->m_pFilter, pObj->m_pFilter->m_pLock, phr, pPinName)
{  
	m_pEnumMediaTypes = new CEnumMediaTypes(this, NULL);
	m_bInsideCheckMediaType = FALSE;
	m_mediaType.SetType(&MEDIATYPE_Stream);
	m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG1System);
	m_nByteOffset = 0;
	m_bIsExposed = false;

	char szPath[1024];
	GetTempPath(1024, szPath);
	GetTempFileName(szPath, "erd", 0, m_szTempFile);
}

CMPEGOutputPin::~CMPEGOutputPin()
{
	SAFE_DELETE(m_pEnumMediaTypes);

	DeleteFile(m_szTempFile);
}


HRESULT CMPEGOutputPin::Active(void)
{
	m_lpOutputFileName = NULL;
	m_pFileSinkConnectedFilter = NULL;
	m_nByteOffset = 0;
	m_nFileHandle = -1;

	if (GetConnected() && m_pFileSinkConnectedFilter == NULL)
	{
		TraceVerbose("GetConnected()->QueryPinInfo\n");

		PIN_INFO info;
		HRESULT hr = GetConnected()->QueryPinInfo(&info);

		if (info.pFilter)
		{
			TraceVerbose("Query for m_pFileSinkConnectedFilter\n");
			info.pFilter->QueryInterface(IID_IFileSinkFilter2, (void**)&m_pFileSinkConnectedFilter);
			
			info.pFilter->Release();
			info.pFilter = NULL;

			if (m_pFileSinkConnectedFilter != NULL && m_lpOutputFileName == NULL)
			{
				hr = m_pFileSinkConnectedFilter->GetCurFile(&m_lpOutputFileName, NULL);
				if (FAILED(hr) || m_lpOutputFileName == NULL)
				{
					TraceVerbose("No Filename\n");
				//	return hr;
				}
			}
		}
	}

	return CBaseOutputPin::Active();
}

HRESULT CMPEGOutputPin::Inactive(void)
{
	TraceVerbose("Output Pin going Inactive!!\n");
	if (m_nFileHandle != -1)
	{
		TraceVerbose("File being closed\n");

		_close(m_nFileHandle);
		m_nFileHandle = -1;

		if (m_pFileSinkConnectedFilter)
			m_pFileSinkConnectedFilter->SetFileName(m_lpOutputFileName, NULL);
	}


	if (m_lpOutputFileName)
		CoTaskMemFree(m_lpOutputFileName);
	m_lpOutputFileName = NULL;
	m_pFileSinkConnectedFilter = NULL;

	DeleteFile(m_szTempFile);

	return CBaseOutputPin::Inactive();
}

//
// NonDelegatingQueryInterface
//
// This function is overwritten to expose IMediaPosition and IMediaSelection
// Note that only one output stream can be allowed to expose this to avoid
// conflicts, the other pins will just return E_NOINTERFACE and therefore
// appear as non seekable streams. We have a LONG value that if exchanged to
// produce a TRUE means that we have the honor. If it exchanges to FALSE then
// someone is already in. If we do get it and error occurs then we reset it
// to TRUE so someone else can get it.
//
STDMETHODIMP CMPEGOutputPin::NonDelegatingQueryInterface(REFIID riid, void **ppv)
{
    CheckPointer(ppv,E_POINTER);
    ASSERT(ppv);

    *ppv = NULL;
    HRESULT hr = NOERROR;

    return CBaseOutputPin::NonDelegatingQueryInterface(riid, ppv);

} // NonDelegatingQueryInterface

HRESULT CMPEGOutputPin::InitAllocator(IMemAllocator **ppAlloc)
{
    HRESULT hr = S_OK;
    m_pAlloc = new CMPEGAllocator(&hr);
    if (!m_pAlloc)
    {
        return E_OUTOFMEMORY;
    }
    if (FAILED(hr))
    {
        delete m_pAlloc;
		m_pAlloc = NULL;
        return hr;
    }
    // Return the IMemAllocator interface.
    return m_pAlloc->QueryInterface(IID_IMemAllocator, (void**)ppAlloc);
}

HRESULT CMPEGOutputPin::DecideAllocator(IMemInputPin *pPin, IMemAllocator **ppAlloc)
{
    HRESULT hr = NOERROR;
    *ppAlloc = NULL;

    // get downstream prop request
    // the derived class may modify this in DecideBufferSize, but
    // we assume that he will consistently modify it the same way,
    // so we only get it once
    ALLOCATOR_PROPERTIES prop;
    ZeroMemory(&prop, sizeof(prop));

    // whatever he returns, we assume prop is either all zeros
    // or he has filled it out.
    pPin->GetAllocatorRequirements(&prop);

    // if he doesn't care about alignment, then set it to 1
    if (prop.cbAlign == 0) {
        prop.cbAlign = 1;
    }

    /* Try the allocator provided by the input pin */

    hr = pPin->GetAllocator(ppAlloc);
    if (SUCCEEDED(hr)) {

        hr = DecideBufferSize(*ppAlloc, &prop);
        if (SUCCEEDED(hr)) {
            hr = pPin->NotifyAllocator(*ppAlloc, FALSE);
            if (SUCCEEDED(hr)) {
                return NOERROR;
            }
        }
    }

    /* If the GetAllocator failed we may not have an interface */

    if (*ppAlloc) {
        (*ppAlloc)->Release();
        *ppAlloc = NULL;
    }

    /* Try the output pin's allocator by the same method */

    hr = InitAllocator(ppAlloc);
    if (SUCCEEDED(hr)) {

        // note - the properties passed here are in the same
        // structure as above and may have been modified by
        // the previous call to DecideBufferSize
        hr = DecideBufferSize(*ppAlloc, &prop);
        if (SUCCEEDED(hr)) {
            hr = pPin->NotifyAllocator(*ppAlloc, FALSE);
            if (SUCCEEDED(hr)) {
                return NOERROR;
            }
        }
    }

    /* Likewise we may not have an interface to release */

    if (*ppAlloc) {
        (*ppAlloc)->Release();
        *ppAlloc = NULL;
    }
    return hr;
}

//
// DecideBufferSize
//
// This has to be present to override the PURE virtual class base function
//
HRESULT CMPEGOutputPin::DecideBufferSize(IMemAllocator *pAlloc,
                                        ALLOCATOR_PROPERTIES * pProperties)
{
    HRESULT hr = NOERROR;

	m_nByteOffset = 0;

    // Is the input pin connected
   // if(m_pInput->IsConnected() == FALSE)
    {
     //   return E_UNEXPECTED;
    }

    CheckPointer(pAlloc,E_POINTER);
    CheckPointer(pProperties,E_POINTER);

    pProperties->cBuffers = 1;
    pProperties->cbAlign  = 1;
    pProperties->cbBuffer = 1024 * 40; // 40 kb , TODO, smaller for smaller frame sizes
      
    ASSERT(pProperties->cbBuffer);

    // Ask the allocator to reserve us some sample memory, NOTE the function
    // can succeed (that is return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties, &Actual);
    if(FAILED(hr))
    {
		_ASSERT(FALSE);
        return hr;
    }

    ASSERT(Actual.cBuffers == 1);

    if (pProperties->cBuffers > Actual.cBuffers ||
        pProperties->cbBuffer > Actual.cbBuffer)
    {
		_ASSERT(FALSE);
        return E_FAIL;
    }

    return NOERROR;
} // DecideBufferSize


HRESULT CMPEGOutputPin::GetMediaType(int iPosition, CMediaType *pMediaType)
{
	CAutoLock lock_it(m_pLock);

	m_mediaType.InitMediaType();

	if (iPosition > 2)
	{
		return S_FALSE;
	}
	else if (iPosition == 2)
	{
		m_mediaType.SetType(&MEDIATYPE_Stream);
		m_mediaType.SetSubtype(&MEDIASUBTYPE_NULL);
	}
	else if (iPosition == 1)
	{
		// MPEG-1 Native Video Stream 
		m_mediaType.SetType(&MEDIATYPE_Stream);
		m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG1Video);
		m_mediaType.SetFormatType(&GUID_NULL);
	}
	else
	{

		if (m_nPinNumber == 0) //systems
		{
			/*
			SystemsOutputFormat sysFormat;
			m_pObj->GetCurrentSettingsProfile().GetSystemsFormat(&sysFormat);

			switch (sysFormat)
			{
			case SYSTEMSFORMAT_NONE:
			case SYSTEMSFORMAT_MPEG1:
			case SYSTEMSFORMAT_VCD_STILL:
			case SYSTEMSFORMAT_VCD:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG1System);
				break;
			case SYSTEMSFORMAT_MPEG2:
			case SYSTEMSFORMAT_DVD:
			case SYSTEMSFORMAT_SVCD_STILL:
			case SYSTEMSFORMAT_SVCD:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG2_PROGRAM);
				break;
			default:
			*/
				m_mediaType.SetSubtype(&MEDIASUBTYPE_NULL);
			//}
		}
		else if (m_nPinNumber == 1) // video
		{
			CMPEGProfile& profile = m_pObj->GetCurrentSettingsProfile();
			VideoOutputFormat vidFormat;
			profile.GetVideoFormat(&vidFormat);
			

			CMPEGInputPin* pVideoPin = m_pObj->m_pFilter->GetVideoPin();
			CMediaType* pInMediaType = pVideoPin->GetMediaType();

				
			if (pVideoPin->IsConnected())
			{
				m_mediaType.Set(*pInMediaType);
			}
			
			m_mediaType.SetType(&MEDIATYPE_Video);
			m_mediaType.SetSampleSize(0);
			m_mediaType.SetVariableSize();
			m_mediaType.SetTemporalCompression(TRUE);

			switch (vidFormat)
			{
			case VIDEOFORMAT_MPEG1:
				{
					m_mediaType.SetType(&MEDIATYPE_Stream);
					m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG1Video);
					m_mediaType.SetFormatType(&FORMAT_MPEGVideo);
					
					MPEG1VIDEOINFO mvf;
					memset(&mvf, 0, sizeof(MPEG1VIDEOINFO));

					// width and height
					long nWidth, nHeight;
					profile.GetWidth(&nWidth);
					profile.GetHeight(&nHeight);

					RECT rc;
					rc.left = 0;
					rc.top = 0;
					rc.right = nWidth;
					rc.bottom = nHeight;

					mvf.hdr.bmiHeader.biWidth = nWidth;
					mvf.hdr.bmiHeader.biHeight = nHeight;
					mvf.hdr.rcSource = rc;
					mvf.hdr.rcTarget = rc;

					// bitrate
					long nBitrate;
					profile.GetVideoBitrate(&nBitrate);
					mvf.hdr.dwBitRate = nBitrate;
					mvf.hdr.dwBitErrorRate = 0;

					// framerate
					double fps;
					profile.GetFramerate(&fps);
					mvf.hdr.AvgTimePerFrame = (LONGLONG)((1.0f / fps) * UNITS);
					
					mvf.hdr.bmiHeader.biSize = sizeof(BITMAPINFOHEADER );
					mvf.hdr.bmiHeader.biPlanes = 1;
					mvf.hdr.bmiHeader.biCompression = MAKEFOURCC('M','P','E','G');
					mvf.hdr.bmiHeader.biSizeImage = 0;
					mvf.hdr.bmiHeader.biClrImportant = 0;
					mvf.cbSequenceHeader = sizeof(MpegSeqHdr);

					MpegSeqHdr seqHdr;
					memset(&seqHdr, 0, sizeof(MpegSeqHdr));
//					seqHdr.height = nHeight;
//					seqHdr.width = nWidth;
					seqHdr.bitrate = nBitrate / 400;
					seqHdr.picture_rate = 3;
					seqHdr.default_qt = 3;
					seqHdr.pel_aspect_ratio = 1;
					seqHdr.vbv_buffer_size = 40 * 1024;
					seqHdr.mb_height = nHeight / 16;
					seqHdr.mb_width = nWidth / 16;

					
					BYTE* pFormat = m_mediaType.AllocFormatBuffer(sizeof(MPEG1VIDEOINFO) + sizeof(MpegSeqHdr));
					CopyMemory(pFormat, (unsigned char*)&mvf, sizeof(MPEG1VIDEOINFO));
					CopyMemory(pFormat + sizeof(MPEG1VIDEOINFO), (unsigned char*)&seqHdr, sizeof(MpegSeqHdr));

				}
				break;
			case VIDEOFORMAT_MPEG2:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG2_VIDEO);
				break;
			default:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_NULL);
			}
		}
		else if (m_nPinNumber == 2) // audio
		{
			AudioOutputFormat audFormat;
			m_pObj->GetCurrentSettingsProfile().GetAudioFormat(&audFormat);
			
			m_mediaType.SetType(&MEDIATYPE_Audio);
			m_mediaType.SetSubtype(&MEDIASUBTYPE_NULL);
			/*
			switch (audFormat)
			{
			case AUDIOFORMAT_MP3:
			case AUDIOFORMAT_MP2:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG2_AUDIO);
				m_mediaType.Set
				break;
			case AUDIOFORMAT_WAV:
			case AUDIOFORMAT_PCM:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_MPEG2_VIDEO);
				break;
			case AUDIOFORMAT_AC3:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_DOLBY_AC3);
				break;
			default:
				m_mediaType.SetSubtype(&MEDIASUBTYPE_NULL);
			}
			*/
		}
	}

	if (pMediaType)
		*pMediaType = m_mediaType; // copy operator

	return S_OK;
}


//
// CheckMediaType
//
HRESULT CMPEGOutputPin::CheckMediaType(const CMediaType *pmt)
{
    CAutoLock lock_it(m_pLock);

    if(m_bInsideCheckMediaType == TRUE)
        return NOERROR;

    m_bInsideCheckMediaType = TRUE;
    HRESULT hr = NOERROR;

	if (*(pmt->Type()) == *m_mediaType.Type())
    {
		hr = NOERROR;
    }


    m_bInsideCheckMediaType = FALSE;
    return NOERROR;

} // CheckMediaType


//
// EnumMediaTypes
//
STDMETHODIMP CMPEGOutputPin::EnumMediaTypes(IEnumMediaTypes **ppEnum)
{
    CAutoLock lock_it(m_pLock);
    ASSERT(ppEnum);

	return m_pEnumMediaTypes->Clone(ppEnum);
} // EnumMediaTypes


//
// SetMediaType
//
HRESULT CMPEGOutputPin::SetMediaType(const CMediaType *pmt)
{
    CAutoLock lock_it(m_pLock);

    // Make sure that the base class likes it
    HRESULT hr = NOERROR;
    hr = CBaseOutputPin::SetMediaType(pmt);
    if(FAILED(hr))
        return hr;

    return NOERROR;

} // SetMediaType

HRESULT CMPEGOutputPin::WriteSampleDirectlyToFile(unsigned char * pBuf, int nBufLen)
{
	TraceVerbose("Entering WriteSampleDirectlyToFile\n");

	HRESULT hr;
	if (GetConnected() && m_pFileSinkConnectedFilter == NULL)
	{
		TraceVerbose("GetConnected()->QueryPinInfo\n");

		PIN_INFO info;
		hr = GetConnected()->QueryPinInfo(&info);

		if (info.pFilter)
		{
			TraceVerbose("Query for m_pFileSinkConnectedFilter\n");
			info.pFilter->QueryInterface(IID_IFileSinkFilter2, (void**)&m_pFileSinkConnectedFilter);

			if (m_pFileSinkConnectedFilter != NULL && m_lpOutputFileName == NULL)
			{
				hr = m_pFileSinkConnectedFilter->GetCurFile(&m_lpOutputFileName, NULL);
				if (FAILED(hr) || m_lpOutputFileName == NULL)
				{
					TraceVerbose("No Filename\n");
					return hr;
				}
			}
		}

	}

	if (m_nFileHandle == -1)
	{
		if (m_pFileSinkConnectedFilter)
		{
//			hr = m_pFileSinkConnectedFilter->SetFileName(CComBSTR(m_szTempFile), NULL);
//			ASSERT(SUCCEEDED(hr));

			USES_CONVERSION;
			m_nFileHandle = _open(W2A(m_lpOutputFileName), _O_WRONLY);
			ASSERT(m_nFileHandle != -1);
			if (m_nFileHandle == -1)
			{
				OutputDebugString("File could not be opened\n");
				return E_FAIL;
			}
		}
	}

	if (m_pFileSinkConnectedFilter == NULL || m_nFileHandle == -1)
	{
		OutputDebugString("Failure: When bypassing DirectShow to write file trailer directly.\n");
	//	_ASSERT(FALSE);
		return E_FAIL;
	}

	// at this point, we should have a filename, and the old file should be closed
	if (m_nFileHandle != -1)
	{
		Trace("Writing sample directly to file: Length = %lu\n", nBufLen);

		_lseek(m_nFileHandle, (long)m_nByteOffset, SEEK_SET);
		int nWritten = _write(m_nFileHandle, pBuf, nBufLen);
		ASSERT(nWritten == nBufLen);
		if (nWritten == -1)
			return E_FAIL;

		m_nByteOffset += nWritten;
	}

	return S_OK;
}

HRESULT CMPEGOutputPin::SendSample(unsigned char *pBuf, long nBufLen)
{
	TraceVerbose("XX    Sample to File. Start=%lu, Length=%lu \n", m_nByteOffset, nBufLen);

	HRESULT hr = S_OK;

	LONGLONG llStart = m_nByteOffset;
	LONGLONG llEnd = m_nByteOffset + nBufLen;

	if (this->IsConnected() == FALSE || nBufLen == 0)
	{
		TraceVerbose("Not connected, or Buffer length = 0\n");
		return S_OK;
	}

	ASSERT(m_pAllocator); // if NULL, not connected

	TraceVerbose("XX    About to get buffer\n");


	CComPtr<IMediaSample> pSample;
	hr = GetDeliveryBuffer(&pSample, &llStart, &llEnd, 0);
	if (FAILED(hr) || pSample == NULL)
	{
	//	ASSERT(FALSE);

//		hr = m_pAlloc->Commit();
//		hr = GetDeliveryBuffer(&pSample, &llStart, &llEnd, 0);
//		if (FAILED(hr) || pSample == NULL)
		{
			// TraceVerbose("\nGetDeliveryBuffer did not return a mediasample\n");
			// return WriteSampleDirectlyToFile(pBuf, nBufLen);
		}
		//return hr;
		return S_FALSE;
	}

	hr = pSample->SetTime(&llStart, &llEnd);
	hr = pSample->SetMediaTime(&llStart, &llEnd);

	long nLeftOver = 0;

	BYTE* pBuffer = NULL;
	hr = pSample->GetPointer(&pBuffer);
	if (pSample->GetSize() < nBufLen)
	{
		nLeftOver = nBufLen - pSample->GetSize();

		Trace("SendSample Buffer Size Error\n");
		_ASSERT(FALSE);
		return E_POINTER;
	}

	long nActualSize = nBufLen - nLeftOver;
	memcpy(pBuffer, pBuf, nActualSize);
	hr = pSample->SetActualDataLength(nActualSize);
	if (FAILED(hr)) 
	{
		_ASSERT(FALSE);
		return hr;
	}

	TraceVerbose("XX    About to Deliver to Output Pin\n");

	hr = Deliver(pSample);
	if (FAILED(hr))
	{
		Trace("Sample could not be delivered\n");
		_ASSERT(FALSE);
	}

	m_nByteOffset += nActualSize;

	_ASSERT(nLeftOver >= 0);
	if (nLeftOver)
	{
		_ASSERT(FALSE);
		SendSample(pBuf + nActualSize, nLeftOver);
	}

	TraceVerbose("XX    Exited SendSample Function\n");

	return hr;
}


//
// NonDelegatingAddRef
//
// We need override this method so that we can do proper reference counting
// on our output pin. The base class CBasePin does not do any reference
// counting on the pin in RETAIL.
//
// Please refer to the comments for the NonDelegatingRelease method for more
// info on why we need to do this.
//
STDMETHODIMP_(ULONG) CMPEGOutputPin::NonDelegatingAddRef()
{
    CAutoLock lock_it(m_pLock);

#ifdef DEBUG
    // Update the debug only variable maintained by the base class
    m_cRef++;
    ASSERT(m_cRef > 0);
#endif

    // Now update our reference count
    m_cOurRef++;
    ASSERT(m_cOurRef > 0);
    return m_cOurRef;

} // NonDelegatingAddRef

//
// NonDelegatingRelease
//
// CMPEGOutputPin overrides this class so that we can take the pin out of our
// output pins list and delete it when its reference count drops to 1 and there
// is atleast two free pins.
//
// Note that CreateNextOutputPin holds a reference count on the pin so that
// when the count drops to 1, we know that no one else has the pin.
//
// Moreover, the pin that we are about to delete must be a free pin(or else
// the reference would not have dropped to 1, and we must have atleast one
// other free pin(as the filter always wants to have one more free pin)
//
// Also, since CBasePin::NonDelegatingAddRef passes the call to the owning
// filter, we will have to call Release on the owning filter as well.
//
// Also, note that we maintain our own reference count m_cOurRef as the m_cRef
// variable maintained by CBasePin is debug only.
//
STDMETHODIMP_(ULONG) CMPEGOutputPin::NonDelegatingRelease()
{
    CAutoLock lock_it(m_pLock);

	if (m_cOurRef == 0)
		return S_OK;

#ifdef DEBUG
    // Update the debug only variable in CBasePin
    m_cRef--;
    ASSERT(m_cRef >= 0);
#endif

    // Now update our reference count
    m_cOurRef--;
    ASSERT(m_cOurRef >= 0);

    // if the reference count on the object has gone to one, remove
    // the pin from our output pins list and physically delete it
    // provided there are atealst two free pins in the list(including
    // this one)

    // Also, when the ref count drops to 0, it really means that our
    // filter that is holding one ref count has released it so we
    // should delete the pin as well.

    if(m_cOurRef == 0)
    {
        {
            m_cOurRef = 0;
#ifdef DEBUG
            m_cRef = 0;
#endif
			delete this;

            // m_pObj->DeleteOutputPin(this);
            return(ULONG) 0;
        }
    }

    return(ULONG) m_cOurRef;

} // NonDelegatingRelease

signed __int64 CMPEGOutputPin::Seek(__int64 newPos)
{
	TraceVerbose("Seeking in output stream to position %lu\n", (long)newPos);
	m_nByteOffset = newPos;
	return m_nByteOffset;
}
