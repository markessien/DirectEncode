// MPEGConverter.cpp : Implementation of CMPEGConverter

#include "stdafx.h"
#include "StandardMPEGCreator.h"
#include "MPEGConverter.h"

/////////////////////////////////////////////////////////////////////////////
// CMPEGConverter


STDMETHODIMP CMPEGConverter::PassThruCmd(BSTR Param1)
{
	MessageBox(Param1);

	return S_OK;
}


STDMETHODIMP CMPEGConverter::get_SourceFile(BSTR *pVal)
{
	m_Settings.strInputFile.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMPEGConverter::put_SourceFile(BSTR newVal)
{
	m_Settings.strInputFile = newVal;

	return S_OK;
}

STDMETHODIMP CMPEGConverter::get_TargetFile(BSTR *pVal)
{
	m_Settings.strOutputFile.CopyTo(pVal);

	return S_OK;
}

STDMETHODIMP CMPEGConverter::put_TargetFile(BSTR newVal)
{
	m_Settings.strOutputFile = newVal;

	return S_OK;
}

STDMETHODIMP CMPEGConverter::StartConversion()
{

	HWND hwndAx = NULL;
    m_spInPlaceSite->GetWindow(&hwndAx);
	m_pConvert->SetParentWindow(hwndAx);

	m_pConvert->StartConversion();

	return S_OK;
}

STDMETHODIMP CMPEGConverter::StopConversion()
{
	m_pConvert->StopConversion();

	return S_OK;
}


STDMETHODIMP CMPEGConverter::LoadPreset(BSTR PresetName)
{
	SystemsOutputFormat sys = SYSTEMSFORMAT_MPEG1;
	Constraint c = CONSTRAINT_NONE;
	if (wcsicmp(L"mpeg1-standard", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MPEG1;
		c = CONSTRAINT_NONE;
	}
	else if (wcsicmp(L"mpeg1-vcd-pal", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_VCD;
		c = CONSTRAINT_PAL;
	}
	else if (wcsicmp(L"mpeg2-standard", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MPEG2;
		c = CONSTRAINT_NONE;
	}
	else if (wcsicmp(L"mpeg2-svcd-pal", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_SVCD;
		c = CONSTRAINT_PAL;
	}
	else if (wcsicmp(L"mpeg2-dvd-pal", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_DVD;
		c = CONSTRAINT_PAL;
	}
	else if (wcsicmp(L"mpeg1-vcd-ntsc", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_VCD;
		c = CONSTRAINT_NTSC;
	}
	else if (wcsicmp(L"mpeg2-svcd-ntsc", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_SVCD;
		c = CONSTRAINT_NTSC;
	}
	else if (wcsicmp(L"mpeg2-dvd-ntsc", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_DVD;
		c = CONSTRAINT_NTSC;
	}
	else if (wcsicmp(L"mpeg4-standard", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MP4;
		c = CONSTRAINT_NONE;
	}
	else if (wcsicmp(L"mpeg4-ipod", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MP4;
		c = CONSTRAINT_IPOD;
	}
	else if (wcsicmp(L"mpeg4-qt", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MOV;
		c = CONSTRAINT_NONE;
	}
	else if (wcsicmp(L"mpeg4-avi", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_AVI;
		c = CONSTRAINT_NONE;
	}
	else if (wcsicmp(L"mpeg1-vcd-still-ntsc", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_VCD_STILL;
		c = CONSTRAINT_NTSC;
	}	
	else if (wcsicmp(L"mpeg1-vcd-still-pal", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_VCD_STILL;
		c = CONSTRAINT_PAL;
	}
	else if (wcsicmp(L"mpeg2-svcd-still-ntsc", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_SVCD_STILL;
		c = CONSTRAINT_NTSC;
	}
	else if (wcsicmp(L"mpeg2-svcd-still-pal", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_SVCD_STILL;
		c = CONSTRAINT_PAL;
	}
	else if (wcsicmp(L"flv", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_FLV;
		c = CONSTRAINT_NONE;
	}
	else if (wcsicmp(L"dvb", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_DVB;
		c = CONSTRAINT_NONE;
	}
	else if (wcsicmp(L"mpeg2-hd", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MPEG2;
		c = CONSTRAINT_HD;
	}
	else if (wcsicmp(L"mpeg4-ipod-nano", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MP4;
		c = CONSTRAINT_IPOD_NANO;
	}
	else if (wcsicmp(L"mpeg4-iphone", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_MP4;
		c = CONSTRAINT_IPHONE;
	}
	else if (wcsicmp(L"rm", PresetName) == 0)
	{
		sys = SYSTEMSFORMAT_RM;
		c = CONSTRAINT_NONE;
	}
	else
		_ASSERT(FALSE);

	m_pConvert->SelectFormat(sys, c);

	return S_OK;
}

STDMETHODIMP CMPEGConverter::get_Statistics(IStatistics **pVal)
{
	m_pStatistics.CopyTo(pVal);

	return S_OK;
}
