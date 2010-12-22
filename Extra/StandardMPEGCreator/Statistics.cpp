// Statistics.cpp : Implementation of CStatistics
#include "stdafx.h"
#include "StandardMPEGCreator.h"
#include "Statistics.h"

/////////////////////////////////////////////////////////////////////////////
// CStatistics


STDMETHODIMP CStatistics::get_Progress(double *pVal)
{
	if (m_pConvert)
		*pVal = m_pConvert->GetProgress();

	return S_OK;
}

STDMETHODIMP CStatistics::get_Duration(double *pVal)
{
	if (m_pConvert)
		*pVal = m_pConvert->GetDuration();

	return S_OK;
}

STDMETHODIMP CStatistics::SetInstance(long Ptr)
{
	m_pConvert = (CConvert*)Ptr;

	return S_OK;
}

STDMETHODIMP CStatistics::get_FramesEncoded(long *pVal)
{
	if (m_pConvert)
		*pVal = m_pConvert->GetFramesEncoded();

	return S_OK;
}

STDMETHODIMP CStatistics::get_EncodeFramerate(long *pVal)
{
	if (m_pConvert)
		*pVal = m_pConvert->GetEncodeFramerate();

	return S_OK;
}

STDMETHODIMP CStatistics::get_TimeElapsed(double *pVal)
{
	if (m_pConvert)
		*pVal = m_pConvert->GetTimeElapsed();

	return S_OK;
}
