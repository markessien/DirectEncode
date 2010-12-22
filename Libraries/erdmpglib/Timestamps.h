// Timestamps.h: interface for the CTimestamps class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMESTAMPS_H__1A06E9D8_C2A1_4323_825D_5062737600BE__INCLUDED_)
#define AFX_TIMESTAMPS_H__1A06E9D8_C2A1_4323_825D_5062737600BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <queue>
// #include <iostream.h>
#include <cmath>

using namespace std;

class CTimestamps  
{
	struct Timestamp
	{
		LONGLONG llStart;
		LONGLONG llEnd;
	};

public:
	void IncrementAudioDrift(LONGLONG llDiff);
	CTimestamps();
	virtual ~CTimestamps();

	HRESULT   GetAudioSampleCorrection(LONGLONG llStart, LONGLONG llEnd, LONGLONG& llCorrectionTime);
	HRESULT   Start(double targetFramerate, long nSamplesPerSecond);
	LONGLONG  GetVideoOutputFrameRepeatCount(LONGLONG llInputFrameStart, LONGLONG llInputFrameEnd);
	void      AddAudioSample(LONGLONG llStart, LONGLONG llEnd);
	void      AddVideoSample(LONGLONG llStart, LONGLONG llEnd);
	void      IncrementOutputFrameCount();

private:
	HRESULT  VerifyFrameTimes(LONGLONG llStartTime, LONGLONG llEndTime);
	long     GetFrameRepeatCount(LONGLONG llStartTime, LONGLONG llEndTime);
	bool     ShouldOutputFrameBeDropped();

private:
	queue<Timestamp> m_audioHoleQueue;

	LONGLONG m_nOutputFrameCount;
	long m_nSamplesPerSecond;
	long m_nAudioCompensation;
	bool m_bDoAudioCorrection;
	long m_nSamplesSinceLastCorrection;
	bool m_bFramebalance;
	bool m_bShiftedLeftLastTime;
	double m_dFramerate;
	
	LONGLONG m_llFrameLength;
	LONGLONG m_llLastAudioEndTime;
	LONGLONG m_llAudioDrift;
	LONGLONG m_llNextAudioHoleEnd;
	LONGLONG m_llNextAudioHoleStart;
};

#endif // !defined(AFX_TIMESTAMPS_H__1A06E9D8_C2A1_4323_825D_5062737600BE__INCLUDED_)
