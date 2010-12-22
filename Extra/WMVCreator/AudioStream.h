#pragma once

#include "stream.h"

class CAudioStream : public CStream
{
public:
	CAudioStream(void);
	~CAudioStream(void);

	HRESULT Load(IWMProfile* pWMProfile);
	BSTR GetLanguage(void);
	void SetLanguage(BSTR str);
	void SetAudioCodec(long nIndex);
	void SelectNearestFormat(bool bVBR, long nBitrate, long nPasses);
	int GetTransportType(void);
	HRESULT CreateNew(IWMProfile* pWMProfile);
	HRESULT SetCBRSettings(IWMStreamConfig* pStreamConfig);

private:
	long m_nCodecFormat;
	long m_nCodec;
public:
	void DestroyObjects(void);
};
