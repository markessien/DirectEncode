#include "stdafx.h"
#include <initguid.h>
#include "convert.h"
#include <conio.h> // _getch

// Standard Mpeg MultipleEncoding Sample. This sample shows
// how to perform multiple encodings using the DirectShow filter
// Also look at the EncodeSample console encode, it shows how 
// to select different formats

// We'll create multiple graphs in this process+
CConvert convert1;
CConvert convert2;
CConvert convert3;
CConvert convert4;

int main(int argc, char* argv[])
{
	printf(" ***************************************\n");
	printf("(c) 2008 Standard MPEG Encoder\n");
	printf("Standard Mpeg Encoder & EncodeSample developed by\n");
	printf("Mark Essien for Standard MPEG\n");
	printf(" ***************************************\n\n");
	

	CoInitialize(0);
	
	// Lets' init graph1 and get it started. The file we are testing with is about 30 seconds long
	// so requires about 10 seconds to encode
	convert1.SetOutputFormat(SYSTEMSFORMAT_MPEG1, CONSTRAINT_NONE, VIDEOFORMAT_MPEG1, AUDIOFORMAT_MP2);
	convert1.SetFiles(CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\test_in.mpg"), 
					 CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\Output Files\\test_out_1.mpg"));
	
	if (FAILED(convert1.StartConversion()))
	{
		printf("Conversion failed\n");
	}
	
	// the graph will be started in a second thread
	// wait for 2 seconds
	Sleep(2000);

	// Let's start a second graph
	convert2.SetOutputFormat(SYSTEMSFORMAT_MPEG1, CONSTRAINT_NONE, VIDEOFORMAT_MPEG1, AUDIOFORMAT_MP2);
	convert2.SetFiles(CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\test_in.mpg"), 
					 CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\Output Files\\test_out_2.mpg"));
	
	if (FAILED(convert2.StartConversion()))
	{
		printf("Conversion failed\n");
	}

	// wait 5 seconds
	Sleep(5000);

	// Let's start a third graph
	convert3.SetOutputFormat(SYSTEMSFORMAT_MPEG1, CONSTRAINT_NONE, VIDEOFORMAT_MPEG1, AUDIOFORMAT_MP2);
	convert3.SetFiles(CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\test_in.mpg"), 
					 CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\Output Files\\test_out_3.mpg"));
	
	if (FAILED(convert3.StartConversion()))
	{
		printf("Conversion failed\n");
	}

	// Now we wait for graph 1 to end
	convert1.WaitForCompletion();
	convert1.StopConversion();

	// Now we wait for graph 2 to end
	convert2.WaitForCompletion();
	convert2.StopConversion();

	// we restart graph1
	convert1.SetOutputFormat(SYSTEMSFORMAT_MPEG1, CONSTRAINT_NONE, VIDEOFORMAT_MPEG1, AUDIOFORMAT_MP2);
	convert1.SetFiles(CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\test_in.mpg"), 
					 CComBSTR("Z:\\Projects\\Standard MPEG\\Test Files\\Output Files\\test_out_1b.mpg"));
	
	if (FAILED(convert1.StartConversion()))
	{
		printf("Conversion failed\n");
	}

	// wait for graph 3 to complete
	convert3.WaitForCompletion();
	convert3.StopConversion();

	
	// We wait for graph 1b to end
	convert1.WaitForCompletion();
	convert1.StopConversion();

	printf("\n\n\n***************************************\n\n");
	printf("Conversion complete. Press any key to exit");

	_getch(); // wait for user to press a key

	return 0;
}

