/** This file is part of The Standard Mpeg Encoder.

The Standard Mpeg Encoder is free software: you can redistribute it 
and/or modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation, either version 3 of 
the License, or (at your option) any later version.

The Standard Mpeg Encoder is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Standard Mpeg Encoder.  
 
If not, see <http://www.gnu.org/licenses/>.
**/

// MPEGOutputPin.h: interface for the CMPEGOutputPin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPEGOUTPUTPIN_H__9B003DB0_C056_46B3_AEF9_9879D21EF274__INCLUDED_)
#define AFX_MPEGOUTPUTPIN_H__9B003DB0_C056_46B3_AEF9_9879D21EF274__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMPEGObj;

class CMPEGAllocator : public CMemAllocator
{
public:
	CMPEGAllocator(HRESULT* phr) : CMemAllocator("Alloc", NULL, phr)
	{
	}

};

class CMPEGOutputPin : public CBaseOutputPin  
{
public:

	typedef struct MpegSeqHdr {
        short width;
        short height;
        short mb_width;
        short mb_height;
        int bitrate;
        int vbv_buffer_size;
        char pel_aspect_ratio;
        char picture_rate;
        char constrained;
        char default_qt;
        unsigned char iqt[64];
        unsigned char niqt[64];
    } MpegSeqHdr;   

	CMPEGOutputPin(TCHAR *pObjName,
                   CMPEGObj *pObj,
                   HRESULT *phr,
                   LPCWSTR pPinName,
                   INT PinNumber);
	virtual ~CMPEGOutputPin();


	HRESULT DecideAllocator(IMemInputPin *pPin, IMemAllocator **pAlloc);
	HRESULT Inactive(void);
	HRESULT Active(void);
	HRESULT InitAllocator(IMemAllocator **ppAlloc);

	HRESULT WriteSampleDirectlyToFile(unsigned char * pBuf, int nBufLen);
	signed __int64 Seek(signed __int64 newPos);
	HRESULT SendSample(unsigned char* pBuf, long nBufLen);

    // Override to expose IMediaPosition
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppvoid);

    // Override to enumerate media types
    STDMETHODIMP EnumMediaTypes(IEnumMediaTypes **ppEnum);

    // Check that we can support an output type
    HRESULT CheckMediaType(const CMediaType *pmt);
    HRESULT SetMediaType(const CMediaType *pmt);

    // Negotiation to use our input pins allocator
    HRESULT DecideBufferSize(IMemAllocator *pMemAllocator,
                             ALLOCATOR_PROPERTIES * ppropInputRequest);

	HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);

	    // Override since the life time of pins and filters are not the same
    STDMETHODIMP_(ULONG) NonDelegatingAddRef();
    STDMETHODIMP_(ULONG) NonDelegatingRelease();

	void SetExposed(bool b) {m_bIsExposed = b;}
	bool IsExposed() {return m_bIsExposed;}

private:
	CMPEGAllocator* m_pAlloc;
	CComPtr<IFileSinkFilter2> m_pFileSinkConnectedFilter;
	int m_nPinNumber;
	signed __int64 m_nByteOffset;
	CEnumMediaTypes* m_pEnumMediaTypes;
	CMPEGObj* m_pObj;
	BOOL m_bInsideCheckMediaType;
	CMediaType m_mediaType;
	LONG m_cOurRef;                // We maintain reference counting
	LPOLESTR m_lpOutputFileName;
	int m_nFileHandle;
	char m_szTempFile[1024];
	bool m_bIsExposed;
};

#endif // !defined(AFX_MPEGOUTPUTPIN_H__9B003DB0_C056_46B3_AEF9_9879D21EF274__INCLUDED_)
