// PropPage.h: interface for the CMPEGProps class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPPAGE_H__260273EB_E70A_4944_8AE4_D005760DED6D__INCLUDED_)
#define AFX_PROPPAGE_H__260273EB_E70A_4944_8AE4_D005760DED6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMPEGProperties : public CBasePropertyPage
{
protected:
	CMPEGProperties(LPUNKNOWN punk, UINT nID, UINT nTitle);
	
	virtual HRESULT OnConnect(IUnknown *pUnknown);
    virtual HRESULT OnDisconnect();
    virtual HRESULT OnDeactivate();
	virtual HRESULT OnApplyChanges();
	virtual HRESULT OnActivate();
	virtual HRESULT OnTimer(UINT nID);

	void   SetDirty();
	BOOL   OnReceiveMessage(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	

	void   SetTextboxText(UINT nID, char* pstrText);
	void   SelectComboItem(UINT nID, int iIndex);
	void   AddToCombo(UINT nID, char* pstrString);
	void   SetTextboxVal(UINT nID, long nVal, bool bReformat = true);
	void   SetTextboxVal(UINT nID, double dVal, bool bReformat = true);
	void   CheckButton(UINT nID, bool bCheck);

	int    GetComboSel(UINT nID);
	long   GetTextboxVal(UINT nID);
	void   GetTextboxVal(UINT nID, long* pVal);
	double GetTextboxDbl(UINT nID);

	void GetFilterInterfaces();
	bool IsBtnChecked(UINT nID);

protected:
	BOOL m_bIsInitialized;      // Used to ignore startup messages
	CComPtr<IUnknown> m_pUnknown;
	CComPtr<IPersistStream> m_pPersistStream;
	CComPtr<IStandardMpegEncoder> m_pFilter;
	CComPtr<IStandardMpegEncoderProfile> m_pProfile;
	CComPtr<IStandardMpegMultiplexerProfile> m_pMuxProfile;	
	CComPtr<IStandardMpegEncoderStats> m_pStats;
};

class CMPEGPropsVideo : public CMPEGProperties
{
public:
	CMPEGPropsVideo(LPUNKNOWN punk);
	virtual ~CMPEGPropsVideo();

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

private:
	HRESULT OnApplyChanges();
	HRESULT OnActivate();
};

class CMPEGPropsAudio : public CMPEGProperties
{
public:
	CMPEGPropsAudio(LPUNKNOWN punk);
	virtual ~CMPEGPropsAudio();

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

private:
	HRESULT OnActivate();
	HRESULT OnApplyChanges();
};

class CMPEGPropsGeneral : public CMPEGProperties
{
public:
	CMPEGPropsGeneral(LPUNKNOWN punk);
	virtual ~CMPEGPropsGeneral();

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);

private:
    HRESULT OnActivate();
	HRESULT OnApplyChanges();
	HRESULT OnDeactivate();
	HRESULT OnTimer(UINT nID);
};

#endif // !defined(AFX_PROPPAGE_H__260273EB_E70A_4944_8AE4_D005760DED6D__INCLUDED_)
