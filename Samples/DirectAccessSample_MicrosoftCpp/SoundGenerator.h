// SoundGenerator.h: interface for the CSoundGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDGENERATOR_H__FAB88780_6163_46F5_8DB0_FAA084F78EDE__INCLUDED_)
#define AFX_SOUNDGENERATOR_H__FAB88780_6163_46F5_8DB0_FAA084F78EDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NB_CHANNELS 2
#define FE 44100
#define FRAC_BITS 16
#define FRAC_ONE (1 << FRAC_BITS)
#define COS_TABLE_BITS 7
#define CSHIFT (FRAC_BITS - COS_TABLE_BITS - 2)

// This file will generate a test audio stream
class CSoundGenerator  
{
public:
	CSoundGenerator();
	virtual ~CSoundGenerator();

	HRESULT GenerateSound(BYTE* pTargetBuffer, long nBufferLen);

private:
	unsigned int Rnd(unsigned int *seed_ptr, int n);
	void PutSample(int v);
	int  IntCos(int a);

private:
	BYTE* m_pBuffer;
	long m_nBufLen;
	long m_nBufPos;
};

#endif // !defined(AFX_SOUNDGENERATOR_H__FAB88780_6163_46F5_8DB0_FAA084F78EDE__INCLUDED_)
