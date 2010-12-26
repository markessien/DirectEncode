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

// DirectEncodeVB.h : Declaration of the CDirectEncodeVB

#ifndef __DIRECTENCODEVB_H_
#define __DIRECTENCODEVB_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirectEncodeVB
class ATL_NO_VTABLE CDirectEncodeVB : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDirectEncodeVB, &CLSID_DirectEncodeVB>,
	public IDispatchImpl<IDirectEncodeVB, &IID_IDirectEncodeVB, &LIBID_StandardMpegEncoderLib>
{
public:
	CDirectEncodeVB()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DIRECTENCODEVB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDirectEncodeVB)
	COM_INTERFACE_ENTRY(IDirectEncodeVB)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDirectEncodeVB
public:
	STDMETHOD(PassThru)(/*[in]*/ long nVal);
};

#endif //__DIRECTENCODEVB_H_
