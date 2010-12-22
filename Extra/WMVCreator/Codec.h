#pragma once

class CCodec
{
	typedef struct tagFormatSettings {
		tagFormatSettings() { 
			m_bSupportsCBR_1Pass = false; m_bSupportsCBR_2Pass = false; m_bSupportsVBR_1Pass = false;
			m_bSupportsVBR_2Pass_Constrained = false; m_bSupportsVBR_2Pass_Unconstrained = false;
		}
		bool m_bSupportsCBR_1Pass;
		bool m_bSupportsCBR_2Pass;
		bool m_bSupportsVBR_1Pass;
		bool m_bSupportsVBR_2Pass_Constrained;
		bool m_bSupportsVBR_2Pass_Unconstrained;
	} FormatSettings;
	
	typedef struct tagFormat {
		CComBSTR strName;
		int nFormatIndex;
		DWORD dwBitrate;
	} Format;

	friend class CWMVCodec;
public:
	CCodec(void);
	~CCodec(void);

	HRESULT SupportedVBRModes(BOOL* CBR1Pass, BOOL* CBR2Pass, BOOL* VBR1Pass, BOOL* VBR2Pass, LONG* ConstrainValue);
	HRESULT Load(IWMCodecInfo2* pCodecInfo, GUID guidType, int nIndex);
	HRESULT GetStreamMediaType(IWMStreamConfig* pStreamConfig, IWMVideoMediaProps** ppProps, WM_MEDIA_TYPE **ppmt);
	HRESULT LoadMediaProps(IWMStreamConfig* pStreamConfig);
	GUID GetMajorType(void);
	CComBSTR GetCodecGuid(void);
	long GetMaxPasses(void);
	HRESULT LoadPassAndVBRSettings(IWMCodecInfo3* pICodecInfo3, GUID guidType, int nIndex);
	HRESULT QueryPropertySupported(IWMCodecInfo3* pICodecInfo3, GUID guidType, int nIndex, WMT_ATTR_DATATYPE dtype, LPCWSTR wszQuery, DWORD dwValue);
	DWORD GetDWordProperty(IWMCodecInfo3* pICodecInfo3, GUID guidType, int nIndex, LPCWSTR wszQuery);
	HRESULT LoadFormats(IWMCodecInfo2* pICodecInfo, GUID guidType, int nIndex);
	void ClearFormats(void);
	CFormatArray* GetFormats(void);
	long GetIndex(void);
	void SetPreference(long n);
	long GetPreference(void);
	void DeterminePreference(GUID g);
	long GetIdealFormat(void);

private:
	


	CFormatArray m_arrFormats;
	long m_nMaxPasses;
	GUID m_codecGuid;
	GUID m_majorType;
	CComBSTR m_strCodecGuid;
	CComBSTR m_strCodecName;
	long m_nComplexityMax;
	long m_nComplexityLive;
	long m_nComplexityOffline;
	long m_nComplexity;
	long m_nIndex;
	bool m_bIsVBRSupported;
	long m_nCodecFormat;
	FormatSettings m_formatSettings;
	long m_nPreference;
	long m_nIdealCodecFormat;
};
