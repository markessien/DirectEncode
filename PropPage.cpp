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

// PropPage.cpp: implementation of the CMPEGPropsGeneral class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PropPage.h"
#include "resource.h"
#include <stdio.h>

CMPEGProperties::CMPEGProperties(LPUNKNOWN punk, UINT nID, UINT nTitle) : CBasePropertyPage(NAME("Standard Mpeg Property Page"), punk, nID, nTitle)
{
}

HRESULT CMPEGProperties::OnApplyChanges() {


	return NOERROR;
}

HRESULT CMPEGProperties::OnTimer(UINT nID)
{
	return E_NOTIMPL;
}

HRESULT CMPEGProperties::OnConnect(IUnknown *pUnknown) {
    HRESULT hr = pUnknown->QueryInterface(IID_IStandardMpegEncoder, (void **) &m_pFilter);
    if (FAILED(hr)) {
        return E_NOINTERFACE;
    }
    ASSERT(m_pFilter);
    m_bIsInitialized = FALSE ;

	m_pUnknown = pUnknown;
	m_pUnknown->QueryInterface(IID_IPersistStream, (void **) &m_pPersistStream);

	GetFilterInterfaces();

    return NOERROR;
}

HRESULT CMPEGProperties::OnDisconnect() {
	if (m_pFilter) m_pFilter = NULL;
	m_pFilter = NULL;
    return NOERROR;
}

HRESULT CMPEGProperties::OnActivate() {
	m_bIsInitialized = TRUE;
    return NOERROR;
}

HRESULT CMPEGProperties::OnDeactivate(void) {
    m_bIsInitialized = FALSE;
    return NOERROR;
}

void CMPEGProperties::SetDirty() {
    m_bDirty = TRUE;
    if (m_pPageSite)
        m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
}


void CMPEGProperties::AddToCombo(UINT nID, char *pstrString)
{
	::SendMessage(GetDlgItem(m_Dlg, nID), CB_ADDSTRING, 0, (LPARAM) (LPCTSTR)pstrString);
}

int CMPEGProperties::GetComboSel(UINT nID)
{
	return ComboBox_GetCurSel(GetDlgItem(m_Dlg, nID));
}

void CMPEGProperties::SelectComboItem(UINT nID, int iIndex)
{
	ComboBox_SetCurSel(GetDlgItem(m_Dlg, nID), iIndex);
}

void CMPEGProperties::GetTextboxVal(UINT nID, long* pVal)
{
	*pVal = GetTextboxVal(nID);
}

long CMPEGProperties::GetTextboxVal(UINT nID)
{
	char sz[50] = {0};
	Edit_GetText(GetDlgItem(m_Dlg, nID), sz, 50);
	return atol(sz);
}

double CMPEGProperties::GetTextboxDbl(UINT nID)
{
	char sz[50] = {0};
	Edit_GetText(GetDlgItem(m_Dlg, nID), sz, 50);
	return atof(sz);
}

void CMPEGProperties::SetTextboxText(UINT nID, char *pstrText)
{
    Edit_SetText(GetDlgItem(m_Dlg, nID), pstrText);
}

void CMPEGProperties::CheckButton(UINT nID, bool bCheck)
{
	CheckDlgButton(m_Dlg, nID, bCheck ? BST_CHECKED : BST_UNCHECKED);
}

void CMPEGProperties::SetTextboxVal(UINT nID, long nVal, bool bReformat)
{
	char sz[60];
    sprintf(sz, "%lu", nVal);

	if (nVal == 0 && bReformat)
		SetTextboxText(nID, "Source");
	else
		SetTextboxText(nID, sz);
}


void CMPEGProperties::SetTextboxVal(UINT nID, double dVal, bool bReformat)
{
	char sz[60];
    sprintf(sz, "%.3f", dVal);

	if (dVal == 0.0f && bReformat)
		SetTextboxText(nID, "Source");
	else
		SetTextboxText(nID, sz);
}

BOOL CMPEGProperties::OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
	case WM_TIMER:
		{
			OnTimer(0);
		}
		break;

	case WM_COMMAND:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE &&
				LOWORD(wParam) == IDC_CMB_FORMAT)
			{
				OnApplyChanges();
			}

			if (m_bIsInitialized)
			{
				m_bDirty = TRUE;
				if (m_pPageSite)
					m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);

				return (LRESULT) 1;
			}
		}
		break;
	}

    return (BOOL) CBasePropertyPage::OnReceiveMessage(hwnd,uMsg,wParam,lParam);
}

/////////////////////////////////////////////////////
////////////////////////////////////////////////////

CMPEGPropsAudio::CMPEGPropsAudio(LPUNKNOWN punk) : CMPEGProperties(punk, IDD_PROPS_AUDIO, IDS_TITLE_AUDIO)
{
}

CMPEGPropsAudio::~CMPEGPropsAudio()
{
}

CUnknown * WINAPI CMPEGPropsAudio::CreateInstance(LPUNKNOWN punk, HRESULT *phr) {
	*phr = S_OK;
    CMPEGPropsAudio *pNewObject = new CMPEGPropsAudio(punk);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;
}

HRESULT CMPEGPropsAudio::OnApplyChanges()
{
	if (m_bIsInitialized == FALSE)
		return S_OK;

	long nVal = 0;
	double dVal = 0;
	nVal = GetComboSel(IDC_CMB_AUDIOSTREAM);
	m_pProfile->SetAudioFormat((AudioOutputFormat)nVal);

	GetTextboxVal(IDC_CMB_SAMPLERATE, &nVal);
	m_pProfile->SetAudioSampleRate(nVal);

	nVal = GetComboSel(IDC_CMB_CHANNELMODE);
	m_pProfile->SetAudioChannels(nVal + 1);

	GetTextboxVal(IDC_CMB_AUDIO_BITRATE, &nVal);
	m_pProfile->SetAudioBitrate(nVal * 1000);

	return NOERROR;
}

HRESULT CMPEGPropsAudio::OnActivate() {
	
	CMPEGProperties::OnActivate();

	GetFilterInterfaces();

	long nVal = 0;
	double dVal = 0;

	AddToCombo(IDC_CMB_AUDIOSTREAM, "None");
	AddToCombo(IDC_CMB_AUDIOSTREAM, "MP3");
	AddToCombo(IDC_CMB_AUDIOSTREAM, "MP2");
	AddToCombo(IDC_CMB_AUDIOSTREAM, "AC3");
	AddToCombo(IDC_CMB_AUDIOSTREAM, "PCM");
	AddToCombo(IDC_CMB_AUDIOSTREAM, "WAV");
	AddToCombo(IDC_CMB_AUDIOSTREAM, "AAC");

	m_pProfile->GetAudioFormat((AudioOutputFormat*)&nVal);
	SelectComboItem(IDC_CMB_AUDIOSTREAM, nVal);
	
	AddToCombo(IDC_CMB_SAMPLERATE, "32000");
	AddToCombo(IDC_CMB_SAMPLERATE, "44100");
	AddToCombo(IDC_CMB_SAMPLERATE, "48000");

	m_pProfile->GetAudioSampleRate(&nVal);
	SetTextboxVal(IDC_CMB_SAMPLERATE, nVal);
	
	AddToCombo(IDC_CMB_CHANNELMODE, "Mono");
	AddToCombo(IDC_CMB_CHANNELMODE, "Stereo");
	
	m_pProfile->GetAudioChannels(&nVal);
	SelectComboItem(IDC_CMB_CHANNELMODE, nVal - 1);

	m_pProfile->GetAudioBitrate(&nVal);
	SetTextboxVal(IDC_CMB_AUDIO_BITRATE, long(nVal / 1000));

    return NOERROR;
}

/////////////////////////////////////////////////////
////////////////////////////////////////////////////

CMPEGPropsVideo::CMPEGPropsVideo(LPUNKNOWN punk) : CMPEGProperties(punk, IDD_PROPS_VIDEO, IDS_TITLE_VIDEO)
{
}

CMPEGPropsVideo::~CMPEGPropsVideo()
{
}

CUnknown * WINAPI CMPEGPropsVideo::CreateInstance(LPUNKNOWN punk, HRESULT *phr) {
	*phr = S_OK;
    CMPEGPropsVideo *pNewObject = new CMPEGPropsVideo(punk);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;
}

HRESULT CMPEGPropsVideo::OnApplyChanges()
{
	if (!m_bIsInitialized)
		return S_OK;

	long nVal = 0;
	double dVal = 0;
	nVal = GetComboSel(IDC_CMB_VIDEO_FORMAT);
	m_pProfile->SetVideoFormat((VideoOutputFormat)nVal);

	GetTextboxVal(IDC_EDIT_X, &nVal);
	m_pProfile->SetWidth(nVal);

	GetTextboxVal(IDC_EDIT_Y, &nVal);
	m_pProfile->SetHeight(nVal);

	nVal = GetComboSel(IDC_CMB_ASPECT_RATIO);
	m_pProfile->SetAspectRatio((AspectRatio)nVal);

	dVal = GetTextboxDbl(IDC_CMB_FRAMERATE);
	m_pProfile->SetFramerate(dVal);
	
	GetTextboxVal(IDC_CMB_TARGET_BITRATE, (long*)&nVal);
	m_pProfile->SetVideoBitrate(nVal * 1000);
	
	nVal = GetComboSel(IDC_CMB_BITRATEMODE);
	m_pProfile->SetVideoVBRMode((_BitrateMode)nVal);
	
	GetTextboxVal(IDC_CMB_BITRATE_MIN, &nVal);
	m_pProfile->SetVideoBitrateMin(nVal * 1000);

	GetTextboxVal(IDC_CMB_BITRATE_MAX, &nVal);
	m_pProfile->SetVideoBitrateMax(nVal * 1000);
	
	return NOERROR;
}


HRESULT CMPEGPropsVideo::OnActivate()
{
	CMPEGProperties::OnActivate();

	GetFilterInterfaces();

	long nVal = 0;
	double dVal = 0;

	AddToCombo(IDC_CMB_VIDEO_FORMAT, "No Video Stream");
	AddToCombo(IDC_CMB_VIDEO_FORMAT, "MPEG-1 Video");
	AddToCombo(IDC_CMB_VIDEO_FORMAT, "MPEG-2 Video");
	AddToCombo(IDC_CMB_VIDEO_FORMAT, "MPEG-4 Video");

	m_pProfile->GetVideoFormat((VideoOutputFormat*)&nVal);
	SelectComboItem(IDC_CMB_VIDEO_FORMAT, nVal);

	m_pProfile->GetWidth(&nVal);
	SetTextboxVal(IDC_EDIT_X, nVal);

	m_pProfile->GetHeight(&nVal);
	SetTextboxVal(IDC_EDIT_Y, nVal);

	AddToCombo(IDC_CMB_ASPECT_RATIO, "1:1 VGA");
	AddToCombo(IDC_CMB_ASPECT_RATIO, "4:3 Display");
	AddToCombo(IDC_CMB_ASPECT_RATIO, "16:9 Display");
	AddToCombo(IDC_CMB_ASPECT_RATIO, "2.21:1 Display");
	
	m_pProfile->GetAspectRatio((AspectRatio*)&nVal);
	SelectComboItem(IDC_CMB_ASPECT_RATIO, nVal);

	AddToCombo(IDC_CMB_FRAMERATE, "23.979");
	AddToCombo(IDC_CMB_FRAMERATE, "24");
	AddToCombo(IDC_CMB_FRAMERATE, "25");
	AddToCombo(IDC_CMB_FRAMERATE, "29.97");
	AddToCombo(IDC_CMB_FRAMERATE, "30");
	AddToCombo(IDC_CMB_FRAMERATE, "50");
	AddToCombo(IDC_CMB_FRAMERATE, "59.94");
	AddToCombo(IDC_CMB_FRAMERATE, "60");
	m_pProfile->GetFramerate(&dVal);
	SetTextboxVal(IDC_CMB_FRAMERATE, dVal);

	m_pProfile->GetVideoBitrate(&nVal);
	SetTextboxVal(IDC_CMB_TARGET_BITRATE, long(nVal / 1000));
	
	AddToCombo(IDC_CMB_BITRATEMODE, "Constant Bitrate");
	AddToCombo(IDC_CMB_BITRATEMODE, "2-Pass VBR [calculates peak bitrates in 1st pass]");
	AddToCombo(IDC_CMB_BITRATEMODE, "Manual VBR [with bitrate range]");
	AddToCombo(IDC_CMB_BITRATEMODE, "Automatic VBR [guesses the bitrate range]");
	m_pProfile->GetVideoVBRMode((_BitrateMode*)&nVal);
	SelectComboItem(IDC_CMB_BITRATEMODE, nVal);
	
	m_pProfile->GetVideoBitrateMin(&nVal);
	SetTextboxVal(IDC_CMB_BITRATE_MIN, long(nVal / 1000), false);
	
	m_pProfile->GetVideoBitrateMax(&nVal);
	SetTextboxVal(IDC_CMB_BITRATE_MAX, long(nVal / 1000), false);

	AddToCombo(IDC_CMB_INTERLACE, "Non-Interlace");
	AddToCombo(IDC_CMB_INTERLACE, "Interlace");
	AddToCombo(IDC_CMB_INTERLACE, "3:2 Pulldown");
	AddToCombo(IDC_CMB_INTERLACE, "Inverse 3:2 Pulldown");
	SelectComboItem(IDC_CMB_INTERLACE, 0);

	return NOERROR;
}

/////////////////////////////////////////////////////
////////////////////////////////////////////////////

CMPEGPropsGeneral::CMPEGPropsGeneral(LPUNKNOWN punk) : CMPEGProperties(punk, IDD_PROPS_GENERAL, IDS_TITLE_GENERAL)
{
}

CMPEGPropsGeneral::~CMPEGPropsGeneral()
{
}

CUnknown * WINAPI CMPEGPropsGeneral::CreateInstance(LPUNKNOWN punk, HRESULT *phr)
{
	*phr = S_OK;
    CMPEGPropsGeneral *pNewObject = new CMPEGPropsGeneral(punk);
    if (pNewObject == NULL) {
        *phr = E_OUTOFMEMORY;
    }
    return pNewObject;

}

HRESULT CMPEGPropsGeneral::OnApplyChanges()
{
	if (m_bIsInitialized == FALSE)
		return S_OK;

	if (IsBtnChecked(IDC_RADIO_SINGLE))
		m_pFilter->ActivateAudioVideoOutputPins(FALSE);
	else
		m_pFilter->ActivateAudioVideoOutputPins(TRUE);

	long nVal = 0;

	nVal = GetComboSel(IDC_CMB_FORMAT);
	m_pFilter->SelectFormat((SystemsOutputFormat)nVal, CONSTRAINT_NONE);
	
	GetFilterInterfaces();

	if (IsBtnChecked(IDC_CHK_MUX))
		m_pMuxProfile->SetMultiplexStreams(TRUE);
	else
		m_pMuxProfile->SetMultiplexStreams(FALSE);

	return NOERROR;
}

HRESULT CMPEGPropsGeneral::OnDeactivate()
{
	KillTimer(m_Dlg, 333);
	return CMPEGProperties::OnDeactivate();;
}

HRESULT CMPEGPropsGeneral::OnTimer(UINT nID)
{
	if (m_pFilter->PassThruCmd(L"IsConnected", 0, 0, 0) == S_OK)
	{
		long nVal = 0;
		m_pStats->GetFramesEncoded(&nVal);

		char sz[128];
		sprintf(sz, "Frames encoded: %lu", nVal);
		SetTextboxText(IDC_STATISTICS, sz);
	}
	else
		SetTextboxText(IDC_STATISTICS, "Not connected at the moment. Please connect and start encoding to view the statistics.");

	return NOERROR;
}


HRESULT CMPEGPropsGeneral::OnActivate()
{
	CMPEGProperties::OnActivate();

	GetFilterInterfaces();

	long nVal = 0;
	double dVal = 0;
	BOOL bVal = FALSE;

	AddToCombo(IDC_CMB_FORMAT, "None");
	AddToCombo(IDC_CMB_FORMAT, "MPEG-1");
	AddToCombo(IDC_CMB_FORMAT, "MPEG-2");
	AddToCombo(IDC_CMB_FORMAT, "MPEG-1 Video CD");
	AddToCombo(IDC_CMB_FORMAT, "MPEG-2 Super Video CD");
	AddToCombo(IDC_CMB_FORMAT, "MPEG-2 DVD");
	AddToCombo(IDC_CMB_FORMAT, "Video CD Still");
	AddToCombo(IDC_CMB_FORMAT, "Super Video CD Still");
	AddToCombo(IDC_CMB_FORMAT, "MPEG-4");
	AddToCombo(IDC_CMB_FORMAT, "3GP");
	AddToCombo(IDC_CMB_FORMAT, "Quicktime MOV");
	AddToCombo(IDC_CMB_FORMAT, "3G2");
	AddToCombo(IDC_CMB_FORMAT, "PSP");
	AddToCombo(IDC_CMB_FORMAT, "AVI (as MPEG-4 Container)");
	AddToCombo(IDC_CMB_FORMAT, "Real Media Format");
	AddToCombo(IDC_CMB_FORMAT, "KVCD (Not Implemented)");
	AddToCombo(IDC_CMB_FORMAT, "Flash Video (FLV)");
	AddToCombo(IDC_CMB_FORMAT, "MPEG-2 Transport Stream (DVB)");

	m_pProfile->GetSystemsFormat((SystemsOutputFormat*)&nVal);
	SelectComboItem(IDC_CMB_FORMAT, nVal);

	m_pMuxProfile->GetMultiplexStreams(&bVal);
	CheckButton(IDC_CHK_MUX, bVal != FALSE);

	m_pFilter->GetAudioVideoOutputPinsActivated(&bVal);
	if (bVal)
		CheckRadioButton(m_Dlg, IDC_RADIO_SINGLE, IDC_RADIO_DOUBLE, IDC_RADIO_SINGLE);
	else
		CheckRadioButton(m_Dlg, IDC_RADIO_SINGLE, IDC_RADIO_DOUBLE, IDC_RADIO_DOUBLE);

	SetTimer(m_Dlg, 333, 1000, NULL);

    return NOERROR;

} // OnActivate


bool CMPEGProperties::IsBtnChecked(UINT nID)
{
	return (IsDlgButtonChecked(m_Dlg, nID) == BST_CHECKED);
}

void CMPEGProperties::GetFilterInterfaces()
{
	m_pProfile = NULL;
	m_pMuxProfile = NULL;
	m_pStats = NULL;
	m_pUnknown->QueryInterface(IID_IStandardMpegEncoderProfile, (void**)&m_pProfile);
	m_pProfile->QueryInterface(IID_IStandardMpegMultiplexerProfile, (void**)&m_pMuxProfile);
	m_pUnknown->QueryInterface(IID_IStandardMpegEncoderStats, (void**)&m_pStats);
}
