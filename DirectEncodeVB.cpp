#include "stdafx.h"
#include "DirectEncodeVB.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_DirectEncodeVB, CDirectEncodeVB)
END_OBJECT_MAP()


STDMETHODIMP CDirectEncodeVB::PassThru(long nVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
