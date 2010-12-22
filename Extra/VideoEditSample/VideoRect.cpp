// VideoRect.cpp : Implementierung von CVideoRect
#include "stdafx.h"
#include "VideoEdit.h"
#include "VideoRect.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoRect


STDMETHODIMP CVideoRect::get_Right(long *pVal)
{
	*pVal = nRight;

	return S_OK;
}

STDMETHODIMP CVideoRect::put_Right(long newVal)
{
	nRight = newVal;

	return S_OK;
}

STDMETHODIMP CVideoRect::get_Top(long *pVal)
{
	*pVal = nTop;

	return S_OK;
}

STDMETHODIMP CVideoRect::put_Top(long newVal)
{
	nTop = newVal;

	return S_OK;
}

STDMETHODIMP CVideoRect::get_Left(long *pVal)
{
	*pVal = nLeft;

	return S_OK;
}

STDMETHODIMP CVideoRect::put_Left(long newVal)
{
	nLeft = newVal;

	return S_OK;
}

STDMETHODIMP CVideoRect::get_Bottom(long *pVal)
{
	*pVal = nBottom;

	return S_OK;
}

STDMETHODIMP CVideoRect::put_Bottom(long newVal)
{
	nBottom = newVal;

	return S_OK;
}

STDMETHODIMP CVideoRect::get_Width(long *pVal)
{
	*pVal = nRight - nLeft;

	return S_OK;
}

STDMETHODIMP CVideoRect::put_Width(long newVal)
{
	nRight = nLeft + newVal;

	return S_OK;
}

STDMETHODIMP CVideoRect::get_Height(long *pVal)
{
	*pVal = nBottom - nTop;

	return S_OK;
}

STDMETHODIMP CVideoRect::put_Height(long newVal)
{
	nBottom = nTop + newVal;

	return S_OK;
}
