#pragma once

#include "codec.h"

class CStream
{
public:
	CStream(void);
	~CStream(void);

	void SetCodecArray(CCodecArray* pCodecArray);

protected:
	HRESULT GetStreamConfig(IWMProfile* pWMProfile, GUID guidMediaType, IWMStreamConfig** ppStreamConfig);
	HRESULT GetStreamMediaType(IWMStreamConfig* pStreamConfig, IWMVideoMediaProps** ppProps, WM_MEDIA_TYPE **ppmt);
	void MapCodec(WM_MEDIA_TYPE *pMT);
	HRESULT SetStreamBasics(IWMStreamConfig *pIWMStreamConfig, WORD wStreamNum, 
                                       LPWSTR pwszStreamName, LPWSTR pwszConnectionName,
                                       DWORD dwBitrate, WM_MEDIA_TYPE *pmt);

	HRESULT SetDWORDProperty(IWMPropertyVault* pPropertyVault, const WCHAR* pstrSetting, DWORD dwVal);

public:
	DWORD GetBitrate(void);
	CCodec* GetCodec(void);
	void CodecFromGuid(void);

protected:
	DWORD m_dwBitrate;
	CCodec* m_pCodec;

public:
	CCodecArray* m_pCodecArray;
	void SetBitrate(long nBitrate);
};
