; C++ filter console sample    
    SetOutPath "$INSTDIR\Samples\ConsoleEncodeSample"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\ConsoleEncodeSample\*.*"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Samples\ConsoleEncode (Visual Studio 6).lnk" "$INSTDIR\Samples\ConsoleEncodeSample\EncodeSampleVS6.dsw"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Samples\ConsoleEncode (Visual Studio 2005).lnk" "$INSTDIR\Samples\ConsoleEncodeSample\EncodeSampleVS8.sln"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Samples\ConsoleEncode (Visual Studio 2003).lnk" "$INSTDIR\Samples\ConsoleEncodeSample\EncodeSampleVS71.sln"

; C++ direct access sample    
    SetOutPath "$INSTDIR\Samples\DirectAccessSample"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\DirectAccessSample\*.*"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Samples\C++ Direct Dll Access Sample - No DirectShow (VS2005).lnk" "$INSTDIR\Samples\DirectAccessSample\DirectAccessSample.sln"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Samples\C++ Direct Dll Access Sample - No DirectShow (VS6).lnk" "$INSTDIR\Samples\DirectAccessSample\DirectAccessSample.dsw"

; C++ multiple encoding sample    
    SetOutPath "$INSTDIR\Samples\MultipleEncodingSample"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\MultipleEncodingSample\*.*"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C++ Samples\Multiple Parallel Encoding Sample.lnk" "$INSTDIR\Samples\MultipleEncodingSample\MultipleEncodingSample.dsw"


; C# Direct Access sample    
    SetOutPath "$INSTDIR\Samples\CSharpDirectAccessSample"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\CSharpDirectAccessSample\*.*"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C# Samples\C# Direct Dll Access Sample (No DirectShow).lnk" "$INSTDIR\Samples\CSharpDirectAccessSample\CSharpDirectAccess.sln"

; C# DirectShow sample (Simple)
    SetOutPath "$INSTDIR\Samples\CSharpSimpleSample"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\CSharpSimpleSample\*.*"
    
	SetOutPath "$INSTDIR\Samples\CSharpSimpleSample\Resources"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\CSharpSimpleSample\Resources\*.*"

	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C# Samples\C# Simple Sample.lnk" "$INSTDIR\Samples\CSharpSimpleSample\QuickEncodeCSharp.sln"

; C# DirectShow sample (Advanced)   
    SetOutPath "$INSTDIR\Samples\CSharpAdvancedSample"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\CSharpAdvancedSample\*.*"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\C# Samples\C# Advanced Sample.lnk" "$INSTDIR\Samples\CSharpAdvancedSample\Transcode.sln"

; VB6 directshow sample    
    SetOutPath "$INSTDIR\Samples\VB6Sample"
	File /x *.ncb /x *.user /x *.suo /x *.opt /x *.plg "..\Samples\VB6Sample\*.*"
	CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\VB6 Samples\VB6 Sample.lnk" "$INSTDIR\Samples\VB6Sample\PrjStandardMpegEncoder.vbp"
