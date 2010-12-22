#include "stdafx.h"
#include <initguid.h>
#include "convert.h"
#include <conio.h> // _getch

// Essien Research & Development Encode Sample. This sample shows
// how to perform a simple conversion to the various formats in a
// simple console application using DirectShow Editing Services.
// See the CConvert class for the actual DirectShow code. DirectX
// SDK 9.0 or 8.0 is required to compile the sample.

void ParseFormat(char* pstrFormat, char* pstrConstraint, SystemsOutputFormat& systemsFormat, Constraint& constraint, VideoOutputFormat& videoFormat, AudioOutputFormat& audioFormat)
{
	systemsFormat = SYSTEMSFORMAT_MPEG1;
	constraint = CONSTRAINT_NONE;
	videoFormat = VIDEOFORMAT_MPEG1;
	audioFormat = AUDIOFORMAT_MP2;

	if (_stricmp(pstrFormat, "mpeg1") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MPEG1;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG1;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "mpeg2") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MPEG2;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "vcd") == 0 &&
		_stricmp(pstrConstraint, "pal") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_VCD;
		constraint = CONSTRAINT_PAL;
		videoFormat = VIDEOFORMAT_MPEG1;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "vcd") == 0 &&
		_stricmp(pstrConstraint, "ntsc") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_VCD;
		constraint = CONSTRAINT_NTSC;
		videoFormat = VIDEOFORMAT_MPEG1;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "dvd") == 0 &&
		_stricmp(pstrConstraint, "pal") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_DVD;
		constraint = CONSTRAINT_PAL;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_AC3;
	}
	else if (_stricmp(pstrFormat, "dvd") == 0 &&
		_stricmp(pstrConstraint, "ntsc") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_DVD;
		constraint = CONSTRAINT_NTSC;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_AC3;
	}
	else if (_stricmp(pstrFormat, "dvd_with_pcm") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_DVD;
		constraint = CONSTRAINT_PAL;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_PCM;
	}
	else if (_stricmp(pstrFormat, "svcd") == 0 &&
		_stricmp(pstrConstraint, "pal") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_SVCD;
		constraint = CONSTRAINT_PAL;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "svcd") == 0 &&
		_stricmp(pstrConstraint, "ntsc") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_SVCD;
		constraint = CONSTRAINT_NTSC;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "mp4") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MP4;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_AAC;
	}
	else if (_stricmp(pstrFormat, "ipod") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MP4;
		constraint = CONSTRAINT_IPOD;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_AAC;
	}
	else if (_stricmp(pstrFormat, "mp4v") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MP4;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_NONE;
	}
	else if (_stricmp(pstrFormat, "3gp") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_3GP;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_H263;
		audioFormat = AUDIOFORMAT_AMRNB;
	}
	else if (_stricmp(pstrFormat, "vcdstill") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_VCD_STILL;
		constraint = CONSTRAINT_PAL;
		videoFormat = VIDEOFORMAT_MPEG1;
		audioFormat = AUDIOFORMAT_NONE;
	}
	else if (_stricmp(pstrFormat, "svcdstill") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_SVCD_STILL;
		constraint = CONSTRAINT_PAL;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_NONE;
	}
	else if (_stricmp(pstrFormat, "ac3") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_NONE;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_NONE;
		audioFormat = AUDIOFORMAT_AC3;
	}
	else if (_stricmp(pstrFormat, "mp2") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_NONE;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_NONE;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "wav") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_NONE;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_NONE;
		audioFormat = AUDIOFORMAT_WAV;
	}
	else if (_stricmp(pstrFormat, "avi") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_AVI;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "flv") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_FLV;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_FLV;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "flv-vp6") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_FLV;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_VP6;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "dvb") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_DVB;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "mpeg2-hd") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MPEG2;
		constraint = CONSTRAINT_HD;
		videoFormat = VIDEOFORMAT_MPEG2;
		audioFormat = AUDIOFORMAT_MP2;
	}
	else if (_stricmp(pstrFormat, "mpeg4-ipod-nano") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MP4;
		constraint = CONSTRAINT_IPOD_NANO;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_AAC;
	}
	else if (_stricmp(pstrFormat, "mpeg4-iphone") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MP4;
		constraint = CONSTRAINT_IPHONE;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_AAC;
	}
	else if (_stricmp(pstrFormat, "rm") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_RM;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_AAC;
	}
	else if (_stricmp(pstrFormat, "mov") == 0)
	{
		systemsFormat = SYSTEMSFORMAT_MOV;
		constraint = CONSTRAINT_NONE;
		videoFormat = VIDEOFORMAT_MPEG4;
		audioFormat = AUDIOFORMAT_AAC;
	}

}

int main(int argc, char* argv[])
{
	printf(" ***************************************\n");
	printf("(c) 2009 Standard MPEG Encoder\n");
	printf("Standard Mpeg Encoder & EncodeSample developed by\n");
	printf("Essien Research & Development for Standard MPEG\n");
	printf(" ***************************************\n\n");
	
	bool bStandardTest = false;
	bool bAllTest = false;
	if (argc < 2)
	{
		printf("  - - - - - - - - -\n");
		printf("Usage: EncodeSample.exe inputfile.avi outputfile.mpg mpeg1\n");
		printf("Parameter1: Input file path\n");
		printf("Parameter2: Output file path\n");
		printf("Parameter3: Output format: mpeg1, mpeg2, vcd, svcd, dvd, etc\n");
		printf("Parameter4: Constraint: pal, ntsc, 44100, 48000\n");
		printf("  > 4th parameter specifies the sample rate for wav output.\n");

		printf("  - - - - - - - - -\n");
		printf("Press 'q' to exit. Press 's' for standard test.\n");
		printf("Press 'a' to test all output formats.\n");
		printf("    Standard is: c:\\test_in.mpg -> c:\\test_out.mpg\n");
		printf("    The 'all test' is: c:\\test_in.mpg -> c:\\test_out_FORMAT.mpg\n");

		printf("->");
		while (1 && (bStandardTest == false && bAllTest == false))
			switch (getchar()) {
			case 'q': exit(1); break;
			case 's': bStandardTest = true; break;
			case 'a': bAllTest = true; break;
			}	
	}

	// ** Change these to change standard test
	char* pstrInputPath = "c:\\Mark\\Hello.mpg";
	char* pstrOutputPath = "c:\\Mark\\Test.22.mp4";
	char* pstrFormat = "mov";
	char* pstrConstraint = "none";
	// ---

	if (bStandardTest == false && bAllTest == false)
	{
		pstrInputPath = argv[1];
		pstrOutputPath = argv[2];
		pstrFormat = "mpg";
		pstrConstraint = "none";
	}
	
	if (argc >= 3)
		pstrFormat = argv[3];
	
	if (argc >= 4)
		pstrConstraint = argv[4];

	CoInitialize(0);
	CConvert convert;

	for (int i=0;i<=9;i++)
	{
		if (bAllTest)
		{
			switch (i)
			{
			case 0:
				pstrFormat = "mpeg1";
				pstrConstraint = "none";
				pstrOutputPath = "c:\\test_out_mpeg1.mpg";
				break;
			case 1:
				pstrFormat = "mp4";
				pstrConstraint = "none";
				pstrOutputPath = "c:\\test_out_mp4.mp4";
				break;
			case 2:
				pstrFormat = "mpeg2";
				pstrConstraint = "none";
				pstrOutputPath = "c:\\test_out_mpeg2.mpg";
				break;
			case 3:
				pstrFormat = "ipod";
				pstrConstraint = "none";
				pstrOutputPath = "c:\\test_out_mpeg4_ipod.mp4";
				break;
			case 4:
				pstrFormat = "vcd";
				pstrConstraint = "pal";
				pstrOutputPath = "c:\\test_out_vcd_pal.mpg";
				break;
			case 5:
				pstrFormat = "vcd";
				pstrConstraint = "ntsc";
				pstrOutputPath = "c:\\test_out_vcd_ntsc.mpg";
				break;
			case 6:
				pstrFormat = "svcd";
				pstrConstraint = "pal";
				pstrOutputPath = "c:\\test_out_svcd_pal.mpg";
				break;
			case 7:
				pstrFormat = "svcd";
				pstrConstraint = "ntsc";
				pstrOutputPath = "c:\\test_out_svcd_ntsc.mpg";
				break;
			case 8:
				pstrFormat = "dvd";
				pstrConstraint = "pal";
				pstrOutputPath = "c:\\test_out_dvd_pal.mpg";
				break;
			case 9:
				pstrFormat = "dvd";
				pstrConstraint = "ntsc";
				pstrOutputPath = "c:\\test_out_dvd_ntsc.mpg";
				break;

				// there are new formats like flv and rm. These are not tested here automatically
			default:
				bAllTest = false;
			}
		}

		printf("%s|%s # %s --> %s\n", pstrFormat, pstrConstraint, pstrInputPath, pstrOutputPath);

		SystemsOutputFormat systemsFormat;
		Constraint constraint;
		VideoOutputFormat videoFormat;
		AudioOutputFormat audioFormat;
		ParseFormat(pstrFormat, pstrConstraint, systemsFormat, constraint, videoFormat, audioFormat);
		convert.SetOutputFormat(systemsFormat, constraint, videoFormat, audioFormat);

		convert.SetFiles(CComBSTR(pstrInputPath), CComBSTR(pstrOutputPath));
		
		if (FAILED(convert.StartConversion()))
		{
			printf("Conversion failed\n");
		}
		else
			convert.WaitForCompletion();

		convert.StopConversion();

		if (bAllTest == false)
			break;
	}

	printf("\n\n\n***************************************\n\n");
	printf("Conversion complete. Press any key to exit");

	_getch(); // wait for user to press a key

	return 0;
}

