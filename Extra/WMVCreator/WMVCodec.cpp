// WMVCodec.cpp : Implementation of CWMVCodec

#include "stdafx.h"
#include "WMVCodec.h"
#include "codec.h"

// CWMVCodec

STDMETHODIMP CWMVCodec::get_CodecName(BSTR* pVal)
{
	CComBSTR str = m_pCodec->m_strCodecName;
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_CodecName(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_CodecDescription(BSTR* pVal)
{
	CComBSTR str = m_pCodec->m_strCodecGuid;
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_CodecDescription(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_MajorType(long* pVal)
{
	if (m_pCodec->GetMajorType() == WMMEDIATYPE_Video)
		*pVal = 1;
	else
		*pVal = 0;

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_MaxPasses(long* pVal)
{
	*pVal = m_pCodec->m_nMaxPasses;

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_Passes(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_Passes(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_Quality(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_Quality(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_Bitrate(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_Bitrate(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_VBRMode(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_VBRMode(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_KeyframeFrequency(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_KeyframeFrequency(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_Framerate(DOUBLE* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_Framerate(DOUBLE newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_Complexity(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_Complexity(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_FormatIndex(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::put_FormatIndex(LONG newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_CodecGuid(BSTR* pVal)
{
	CComBSTR str = m_pCodec->GetCodecGuid();
	str.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_ComplexityMax(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_ComplexityOffline(LONG* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_ComplexityLive(long* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_IsVBRSupported(VARIANT_BOOL* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::SupportedVBRModes(VARIANT_BOOL* CBR1Pass, VARIANT_BOOL* CBR2Pass, VARIANT_BOOL* VBR1Pass, VARIANT_BOOL* VBR2Pass, LONG* ConstrainValue)
{
	BOOL bCBR1Pass = FALSE;
	BOOL bCBR2Pass = FALSE;
	BOOL bVBR1Pass = FALSE;
	BOOL bVBR2Pass = FALSE;
	LONG nConstrainValue = 0;

	m_pCodec->SupportedVBRModes(&bCBR1Pass, &bCBR2Pass, &bVBR1Pass, &bVBR2Pass, &nConstrainValue);

	if (CBR1Pass) *CBR1Pass = bCBR1Pass ? VARIANT_TRUE : VARIANT_FALSE;
	if (CBR2Pass) *CBR2Pass = bCBR2Pass ? VARIANT_TRUE : VARIANT_FALSE;
	if (VBR1Pass) *VBR1Pass = bVBR1Pass ? VARIANT_TRUE : VARIANT_FALSE;
	if (VBR2Pass) *VBR2Pass = bVBR2Pass ? VARIANT_TRUE : VARIANT_FALSE;
	if (ConstrainValue) *ConstrainValue = nConstrainValue;

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_FormatCount(long* pVal)
{
	*pVal = (long)m_pCodec->GetFormats()->GetCount();

	return S_OK;
}

STDMETHODIMP CWMVCodec::LoadCodecFormats(void)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CWMVCodec::get_FormatName(LONG Index, BSTR* pVal)
{
	CComBSTR str = m_pCodec->GetFormats()->GetAt(Index)->strName;
	str.CopyTo(pVal);
	return S_OK;
}

STDMETHODIMP CWMVCodec::get_CodecIndex(LONG* pVal)
{
	*pVal = m_pCodec->GetIndex();

	return S_OK;
}
