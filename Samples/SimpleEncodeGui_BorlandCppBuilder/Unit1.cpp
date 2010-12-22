//---------------------------------------------------------------------------

// This is not an official sample. It's just a helper sample for Borland C++
// users. (c) 2008 Standard Mpeg

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void TestFunction()
{

    ICaptureGraphBuilder2   *pBuild = NULL;

    IGraphBuilder           *pGraph = NULL;

    IBaseFilter             *pSrc = NULL;       // Source filter

    IBaseFilter             *pMux = NULL;       // MUX filter

    IBaseFilter             *pVComp = NULL;     // Video compressor filter



    CoInitialize(NULL);

 

    // Create the capture graph builder.

    CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC,

            IID_ICaptureGraphBuilder2, (void **)&pBuild);

 

    // Make the rendering section of the graph.

    pBuild->SetOutputFileName(

            &MEDIASUBTYPE_Avi,  // File type.

            L"C:\\Temp\\testOut.avi",  // File name.

            &pMux,              // Receives a pointer to the multiplexer.

            NULL);              // Receives a pointer to the file writer.

 

    // Load the source file.

    pBuild->GetFiltergraph(&pGraph);

    pGraph->AddSourceFilter(L"C:\\temp\\demo2.avi", L"Source Filter", &pSrc);

 

    // Add the compressor filter.

 

    CoCreateInstance(CLSID_Encoder, NULL, CLSCTX_INPROC,

            IID_IBaseFilter, (void **)&pVComp);

    pGraph->AddFilter(pVComp, L"Compressor");

 

    // Render the video stream, through the compressor.

    pBuild->RenderStream(

            NULL,       // Output pin category

            &MEDIATYPE_Video,       // Media type

            pSrc,       // Source filter

            pVComp,     // Compressor filter

            pMux);      // Sink filter (the AVI Mux)

 

    // Render the audio stream.

    pBuild->RenderStream(NULL, NULL, pSrc, NULL, pMux);

 

    // Set video compression properties.

    IAMStreamConfig         *pStreamConfig = NULL;

    IAMVideoCompression     *pCompress = NULL;

 

    // Set Encoder Properties

    HRESULT hr;

    IStandardMpegEncoderProfile *iProfile;

    hr = pVComp->QueryInterface(::IID_IStandardMpegEncoderProfile, (void**)&iProfile);

    if (FAILED(iProfile->SetVideoFormat(Standardmpegencoderlib_tlb::VIDEOFORMAT_MPEG2)))

        ShowMessage("Fail to set MPEG2 video format");

 

    iProfile->Release();

 

    IStandardMpegEncoder *iEncoder;

 

    hr = (pVComp->QueryInterface(::IID_IStandardMpegEncoder, (void**)&iEncoder));

 

    if (FAILED(hr))

        ShowMessage("Failed to get encoder interface");

 

    hr = iEncoder->SetFilterLicenseKey(L"FNDF-FEFK-HXTN-PQJL-DTPJ");

    if (FAILED(hr))

        ShowMessage("Fail to set license key, error was:" + AnsiString(hr));

 

 

    // Run the graph.

    IMediaControl   *pControl = NULL;

    IMediaSeeking   *pSeek = NULL;

    IMediaEvent     *pEvent = NULL;

    pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);

    pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

  

    hr = pMux->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);



    pControl->Run();

    printf("Recompressing... \n");

 

    long evCode;

    if (SUCCEEDED(hr))  // IMediaSeeking is supported

    {

        REFERENCE_TIME rtTotal, rtNow = 0;

        pSeek->GetDuration(&rtTotal);

        while ((pEvent->WaitForCompletion(1000, &evCode)) == E_ABORT)

        {

            pSeek->GetCurrentPosition(&rtNow);

            printf("%d%%\n", (rtNow * 100)/(rtTotal+1));

        }

        pSeek->Release();

    }

    else  // Cannot update the progress.

    {

        pEvent->WaitForCompletion(INFINITE, &evCode);

    }

    pControl->Stop();

    printf("All done\n");



    pSrc->Release();

    pMux->Release();

    pVComp->Release();

    pControl->Release();

    pEvent->Release();

    pBuild->Release();

    pGraph->Release();

    CoUninitialize();



}