// NotifyWindow.h: interface for the CNotifyWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTIFYWINDOW_H__57CC5597_906E_4E6B_A8DD_3ED4444FE08A__INCLUDED_)
#define AFX_NOTIFYWINDOW_H__57CC5597_906E_4E6B_A8DD_3ED4444FE08A__INCLUDED_

#pragma once

class CNotifyWindow : public CWindowImpl< CNotifyWindow >
{
public:
	
	CNotifyWindow() {m_lParam= 0;}
	virtual ~CNotifyWindow(){ if(IsWindow()) DestroyWindow(); }
	
	BEGIN_MSG_MAP( CNotifyWindow )
	  MESSAGE_RANGE_HANDLER(0, 0xBFFF, MessageHandler)
	END_MSG_MAP()
	
	void SetDrainFunction(BOOL (*CallBackFunc)(HWND, UINT, WPARAM, LPARAM, long), long lParam)
	{
		_ASSERT(lParam); // You need to pass a pointer to your class here!
		m_CallBackFunc = CallBackFunc;
		m_lParam = lParam;
	}

protected:
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		switch (uMsg)
		{
		case WM_ERASEBKGND:
			bHandled = true;
			break;
		case WM_PAINT:
			bHandled = false;
			break;
		default:
			bHandled = false;
		}
		
		_ASSERT(m_CallBackFunc);
		return (*m_CallBackFunc)(m_hWnd, uMsg, wParam, lParam, m_lParam);
	}

private:
	BOOL (*m_CallBackFunc)(HWND, UINT, WPARAM, LPARAM, long);
	long m_lParam;
};

#endif // !defined(AFX_NOTIFYWINDOW_H__57CC5597_906E_4E6B_A8DD_3ED4444FE08A__INCLUDED_)
