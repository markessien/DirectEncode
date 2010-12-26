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

// Timestamps.cpp: implementation of the CTimestamps class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Timestamps.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimestamps::CTimestamps()
{

}

CTimestamps::~CTimestamps()
{

}

void CTimestamps::AddVideoSample(LONGLONG llStart, LONGLONG llEnd)
{
	// We do not need to store video samples

//	Timestamp t = {llStart, llEnd};
//	m_videoQueue.push(t);
}

void CTimestamps::AddAudioSample(LONGLONG llStartTime, LONGLONG llEndTime)
{
	/*
	Timestamp t = {llStartTime, llEndTime};
	m_audioQueue.push(t);

	// get difference between start of this sample and end of last
	m_llNextAudioHoleStart = m_llLastAudioEndTime;
	m_llNextAudioHoleEnd = llStartTime;
	m_llLastAudioEndTime = llEndTime;
	*/

	// m_audioHoleQueue;
}

LONGLONG CTimestamps::GetVideoOutputFrameRepeatCount(LONGLONG llInputFrameStart, LONGLONG llInputFrameEnd)
{
	LONGLONG nFramerateCorrection = GetFrameRepeatCount(llInputFrameStart, llInputFrameEnd);
	return nFramerateCorrection;
}

HRESULT CTimestamps::Start(double targetFramerate, long nSamplesPerSec)
{
	m_llFrameLength = (LONGLONG)((1.0f / targetFramerate) * UNITS);
	m_nSamplesPerSecond = nSamplesPerSec;
	m_dFramerate = targetFramerate;
	m_nOutputFrameCount = 0;
	m_nAudioCompensation = 0;
	m_bDoAudioCorrection = true;
	m_nSamplesSinceLastCorrection = 0;
	m_bFramebalance = true;
	m_bShiftedLeftLastTime = false;

	m_llLastAudioEndTime = 0;
	m_llAudioDrift = 0;
	m_llNextAudioHoleEnd = -1;
	m_llNextAudioHoleStart = -1;

	return S_OK;
}

HRESULT CTimestamps::GetAudioSampleCorrection(LONGLONG llStartTime, LONGLONG llEndTime, LONGLONG& llCorrectionTime)
{
	// this function will return the number of samples to drop or to insert

	// variables to store the end time of the last sample
	// as well as drift from where it should be

	// get difference between start of this sample and end of last
	double dDifference = (double)(llStartTime - m_llLastAudioEndTime) / (double)UNITS;
	
	// get the total drift from where it should be
	m_llAudioDrift += (LONGLONG)(dDifference * UNITS);

	// set the static last end time
	m_llLastAudioEndTime = llEndTime;

	// get the drift in seconds
	double dDrift = (double)m_llAudioDrift / (double)UNITS;
	
	if (dDrift > 0.0f)
	{
		m_bDoAudioCorrection = true;

		// we make it correct to allow for 0 drift
		dDifference = (double)m_llAudioDrift / (double)UNITS;
		
		llCorrectionTime = dDifference * UNITS;
		long nSamplesToAdd = (int)(dDifference * (double)m_nSamplesPerSecond);
		return nSamplesToAdd;
	}

	llCorrectionTime = 0;
	return 0;
}

HRESULT CTimestamps::VerifyFrameTimes(LONGLONG llStartTime, LONGLONG llEndTime)
{
#ifdef _DEBUG
#ifdef TRACE_VIDEO
		double dFramerate = (double)m_EncodeParams.nOutputFPSDen / (double)m_EncodeParams.nOutputFPSNum;

		// we do some checking to make sure that our encode is
		// within the correct range for a framerate conversion
		// Whatever algorithm we use, this will assert if we have
		// a drift of more than one second
		LONGLONG llTimePerFrameMPEG = (LONGLONG)((1.0f / dFramerate) * UNITS);

		LONGLONG llStartTimeMPEG = m_nOutputFrameCount * llTimePerFrameMPEG;
		LONGLONG llEndTimeMPEG = llStartTimeMPEG + llTimePerFrameMPEG;

		bool bAssert = false;
		if ((llStartTimeMPEG >= llEndTime ||
			llEndTimeMPEG <= llStartTime) && 
			llStartTimeMPEG != llEndTime)
		{
			bAssert = true; // no frame overlap, WRONG!
		}

		LONGLONG llVideoDrift = llStartTimeMPEG - llStartTime;
		if (llStartTimeMPEG >= llStartTime && llEndTimeMPEG <= llEndTime)
		{
			llVideoDrift = 0; // this mpeg frame lies squarely within the
							  // frame times
		}
		else if (llStartTimeMPEG >= llStartTime && llEndTimeMPEG >= llEndTime)
		{
			// this frame overlaps over the end. We use the end time to set the
			// video drift. Remeber that mpeg frames tpyically are about 1/25th
			// of a second, so we are still pretty aqurate
			llVideoDrift = llEndTimeMPEG - llEndTime;
		}

		// _ASSERT(!bAssert); 
		Trace("Video Drift=%I64d\n", llVideoDrift);
		_ASSERT(llVideoDrift < UNITS);
#endif
#endif

	return S_OK;
}

long CTimestamps::GetFrameRepeatCount(LONGLONG llStartTime, LONGLONG llEndTime)
{
	// This function tells us if this frame is to be
	// duplicated, or if it is to be dropped
	
	// retrieve target framerate

	// how many times will we encode this very sample?
	// default is one time
	static bool bLastFrameWasDropped = false;
	int nTimesToEncodeThisFrame = 1; 
	if (m_bFramebalance == true)
	{
		 // All time values are represented in integer 100 millisecond units

		 // First we need the average time for one output frame (in units)
		 LONGLONG llTimePerOutputFrame = (LONGLONG)((1.0f / m_dFramerate) * UNITS);

		 // if we were to encode this video sample, it would actually
		 // be displayed at time llDisplayTime in the output mpeg file
		 LONGLONG llDisplayTime = m_nOutputFrameCount * llTimePerOutputFrame;

		 
		 // llStartTime is when the sample sent in should start
		 // displaying in the mpeg output file. llStopTime is when
		 // the sample should stop displaying

		 // The frame we 
		 // There is a time offset between those two that is 
		 LONGLONG llTimeOffset = llDisplayTime - llStartTime;
		
		 // How many frames does the display frame span? We will
		 // add this to the number of times the frame should be repeated
		 // How many mpeg output frames are covered by the start and end 
		 // time of this particular frame that we are looking at? This value is
		 // the number of "span frames", i.e, the number of frames it spans. 
		 // Each of the output frames it spans is the same as this particular frame,
		 // so every one of them is going to be this frame, but repeated

		 LONGLONG nSpanFrames = (llEndTime - llStartTime) / llTimePerOutputFrame;
		 // _ASSERT(nSpanFrames == 0);

		 // this offset could be positive or negative

		 // -- At our current framerate, how many frames would fit into
		 // this time offset?
		 // We divide by the remaining time to get the number of frames that
		 // would fit into that space
		__int64 iFramesTillDisplayTime = llTimeOffset / llTimePerOutputFrame;

        if (iFramesTillDisplayTime >= 1)
		{
		//	_ASSERT(bLastFrameWasDropped != true);
            nTimesToEncodeThisFrame = 0; // drop frame
			bLastFrameWasDropped = true;
		}
        else if (iFramesTillDisplayTime <= -1)
		{
            nTimesToEncodeThisFrame = (long)(fabs((double)iFramesTillDisplayTime) + 1.0); //more than 1 frame
		}

		// if (nSpanFrames >= 0)
		nTimesToEncodeThisFrame += (int)(nSpanFrames /*- 1*/); // the -1 because there is already 1 encode

		_ASSERT(nTimesToEncodeThisFrame >= 0);

		TraceVerbose("Target Display Time For Frame: %I64d - %I64d\n", llDisplayTime, llDisplayTime + llTimePerOutputFrame);
		TraceVerbose("Actual Display Time For Frame: %I64d - %I64d\n", llStartTime, llEndTime);

		if (nTimesToEncodeThisFrame == 0)
			TraceVerbose("FRAMEDROP\n");
		else
			bLastFrameWasDropped = false;
	}

	return nTimesToEncodeThisFrame;
}

bool CTimestamps::ShouldOutputFrameBeDropped()
{
	// how big is the audio gap we are compensating for
	LONGLONG llHoleLength = m_llNextAudioHoleEnd - m_llNextAudioHoleStart;
	
	// if it is smaller than half a frame, we don't drop the frame.
	// NOTE: It may be a bit less than half a frame, in which case
	// on the next round, we drop it!!!
	if (llHoleLength <= m_llFrameLength)
	{
		// todo: we may have a 0.4 shift because of this function
		// save it somehwere and compensate on the next one
		if (llHoleLength <= m_llFrameLength / 2)
			return false;

		m_bShiftedLeftLastTime = !m_bShiftedLeftLastTime;
		if (m_bShiftedLeftLastTime)
			return false;
		else
			return true;
	}

	// get the times when this frame starts and stops
	LONGLONG llFrameStartTime = m_nOutputFrameCount * m_llFrameLength;
	LONGLONG llFrameEndTime = llFrameStartTime + m_llFrameLength;

	// find out how many of those frames would fit into the hole.
	// if the hole has more space than for just 1 frame, just drop
	// this frame. The real issues lie with the border frames
	LONGLONG nFramesThatWillFitInHole = llHoleLength / m_llFrameLength;
	if (nFramesThatWillFitInHole >= 1)
		return true;

	return false;
}


void CTimestamps::IncrementOutputFrameCount()
{
	m_nOutputFrameCount++;
}

void CTimestamps::IncrementAudioDrift(LONGLONG llDiff)
{
	m_llAudioDrift += llDiff;
}
