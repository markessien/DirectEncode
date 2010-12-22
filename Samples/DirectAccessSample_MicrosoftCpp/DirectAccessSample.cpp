// DirectAccessSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h> // _getch
#include "stillbitmap.h"
#include "encodestillimage.h"
#include "soundgenerator.h"


// Standard MPEG DirectAccess Sample. This sample shows
// how to perform a simple conversion to the various formats in a
// simple console application by calling the erdmpg libs directly

// ADD A FILE test.jpg to the c:\\ directory!

void EncodeBitmapAsMpegStill(CComBSTR strPathSourceBitmap)
{
	CEncoder mpegEncoder;
	mpegEncoder.SetOutputFormat(SYSTEMSFORMAT_VCD_STILL, CONSTRAINT_NTSC);
	mpegEncoder.CreateHighResolutionStill(strPathSourceBitmap, L"c:\\hi.mpg");
	mpegEncoder.CreateLowResolutionStill(strPathSourceBitmap, L"c:\\lo.mpg");
	mpegEncoder.Multiplex(L"c:\\hi.mpg", L"c:\\lo.mpg", L"c:\\mpegstill.mpg");

	// if you wish, delete the two temp files with DeleteFile
	DeleteFile("c:\\hi.mpg");
	DeleteFile("c:\\lo.mpg");
}

void EncodeVideoAudioStream(CComBSTR strPathSourceBitmap)
{
	CEncoder mpegEncoder;
	mpegEncoder.SetOutputFormat(SYSTEMSFORMAT_MP4, CONSTRAINT_NONE);

	CStillBitmap bitmap;
	
	HRESULT hr = bitmap.Load(strPathSourceBitmap, 320, 240);
	if (FAILED(hr))
	{
		MessageBox(0, "Please create a file c:\\test.jpg to test with", 0, 0);
		return;
	}

	long nSndBufLen = 1024 * 2048;
	BYTE* pSoundBuf = new BYTE[nSndBufLen];
	memset(pSoundBuf, 0, nSndBufLen);

	CSoundGenerator sound;
	sound.GenerateSound(pSoundBuf,nSndBufLen);
	mpegEncoder.StartEncode(L"c:\\testdirect.mpg", 320, 240, true, true);

	// 10 seconds of video
	mpegEncoder.EncodeVideo(bitmap.GetBuffer(), bitmap.GetBufferLength(), 0, 10);

	mpegEncoder.EncodeAudio(pSoundBuf, nSndBufLen);

	mpegEncoder.EndEncode();
}

int main(int argc, char* argv[])
{
	printf(" ***************************************\n");
	printf("(c) 2009 The Standard Mpeg Encoder\n");
	printf("Standard MPEG & EncodeSample developed by\n");
	printf("Essien Consulting for Industrial Streams\n");
	printf("Visit StandardMPEG.com\n");
	printf(" ***************************************\n\n");

	EncodeVideoAudioStream(CComBSTR("c:\\test.jpg"));

	printf("\n\n\n***************************************\n\n");
	printf("Conversion complete. Press any key to exit");

	_getch(); // wait for user to press a key
	return 0;
}

