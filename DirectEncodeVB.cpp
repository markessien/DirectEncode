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
