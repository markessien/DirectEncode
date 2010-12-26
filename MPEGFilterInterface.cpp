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

// MPEGFilterInterface.cpp: implementation of the CMPEGFilterInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MPEGFilterInterface.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMPEGFilterInterface::CMPEGFilterInterface() : CUnknown(NAME("CMPEGFilterInterface"), NULL)
{

}

CMPEGFilterInterface::~CMPEGFilterInterface()
{

}

STDMETHODIMP CMPEGFilterInterface::GetProfile(SystemsOutputFormat systemsFormat, Constraint constraint, IStandardMpegEncoderProfile** pProfile)
{
	(m_pObj->GetSettingsProfile(systemsFormat, constraint)).AddRef();
	*pProfile = &m_pObj->GetSettingsProfile(systemsFormat, constraint);
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::ActivateAudioVideoOutputPins(BOOL bVal)
{
	// ActivateAudioVideoOutputPins -> don't multiplex
	m_pObj->SetShouldMultiplex(!bVal);
	m_pObj->SetDirty(TRUE);
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::GetAudioVideoOutputPinsActivated(BOOL* bVal)
{
	*bVal = m_pObj->GetShouldMultiplex();
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::EnableFramerateCorrection(BOOL bCorrectVideo, BOOL bCorrectAudio)
{
	return S_OK;
}


STDMETHODIMP CMPEGFilterInterface::GetSelectedProfile(IStandardMpegEncoderProfile** pProfile)
{
	if (pProfile)
	{
		m_pObj->GetCurrentSettingsProfile().AddRef();
		*pProfile = &m_pObj->GetCurrentSettingsProfile();
	}
	else 
		return E_POINTER;
	
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::SelectProfile(IStandardMpegEncoderProfile* pProfile)
{
	m_pObj->m_pCurrentProfile = (CMPEGProfile*)pProfile;
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::SelectFormat(SystemsOutputFormat systemsFormat, Constraint constraint)
{
	m_pObj->SetDirty(TRUE);
	return m_pObj->SelectFormat(systemsFormat, constraint);
}

STDMETHODIMP CMPEGFilterInterface::SetFilterLicenseKey(BSTR strLicense)
{
	if (strLicense == NULL || wcslen(strLicense) > 100)
		return E_FAIL;

	wcscpy_s(m_pObj->m_szLicense, 1024, strLicense);
	return S_OK;
}

bool CMPEGFilterInterface::IsFrameRateSupported(double dFPS)
{
	if (FLOAT_EQ(dFPS, 24) || FLOAT_EQ(dFPS, 25) || 
		FLOAT_EQ(dFPS, 30) || FLOAT_EQ(dFPS, 50) || 
		FLOAT_EQ(dFPS, 60) || FLOAT_EQ(dFPS, 23.976) ||
		FLOAT_EQ(dFPS, 29.97) || FLOAT_EQ(dFPS, 59.94))
	{
		return true;
	}

	return false;
}

STDMETHODIMP CMPEGFilterInterface::SaveSettings(BSTR strKey)
{
	return m_pObj->SaveSettings(strKey);
}

STDMETHODIMP CMPEGFilterInterface::LoadSettings(BSTR strKey)
{
	return m_pObj->LoadSettings(strKey);
}

STDMETHODIMP CMPEGFilterInterface::PassThruCmd(BSTR strCmd, long nCmd, double dCmd, BYTE* pCmd)
{
	return m_pObj->PassThruCmd(strCmd, nCmd, dCmd, pCmd);
}

STDMETHODIMP CMPEGFilterInterface::SetErrorBoxDisplay(BOOL bVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGFilterInterface::SetPass(long n)
{
	return E_NOTIMPL;
}

STDMETHODIMP CMPEGFilterInterface::SetSourceFramerate(double dSourceFramerate, double * dRequiredInputFramerate)
{
	// in this function, the client tells us what the input fps is
	// and we tell him what framerate we want to receive.

	CMPEGProfile& profile = m_pObj->GetCurrentSettingsProfile();
	
	double dProfileFPS = 0.0f;
	profile.GetFramerate(&dProfileFPS);

	if (dProfileFPS == 0.0f) // profile does not have particular fps
	{
		if (IsFrameRateSupported(dSourceFramerate))
		{
			*dRequiredInputFramerate = dSourceFramerate;
			m_pObj->GetEncodeLib()->GetSourceInfo().dSourceFPS = dSourceFramerate;
		}
		else
		{
			// the source framerate is not supported. We are going to
			// have to suggest he changes the input fps
			*dRequiredInputFramerate = 25;
			m_pObj->GetEncodeLib()->GetSourceInfo().dSourceFPS = 25;
		}
	}
	else // the profile needs a particular fps
	{
		*dRequiredInputFramerate = dProfileFPS;
		m_pObj->GetEncodeLib()->GetSourceInfo().dSourceFPS = dProfileFPS;
	}
	
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::GetFramesEncoded(long * pllFramesEncoded)
{
	if (pllFramesEncoded)
	{
		*pllFramesEncoded = (long)m_pObj->m_nVideoFramesReceived;
	}
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::GetVideoFramesDropped(long * lFramesDropped)
{
	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::GetAudioTimeCorrected(double * dTimeCorrected)
{
	return S_OK;
}


STDMETHODIMP CMPEGFilterInterface::GetWrittenBytes(long * pllBytesWritten)
{
	if (pllBytesWritten && m_pObj->GetEncodeLib()) 
	{
		*pllBytesWritten = m_pObj->GetEncodeLib()->GetWrittenBytes();
	}

	return S_OK;
}

STDMETHODIMP CMPEGFilterInterface::GetStatusString(BSTR* pstrValue)
{
	return E_NOTIMPL;
}
