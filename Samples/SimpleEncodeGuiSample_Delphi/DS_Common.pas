unit DS_Common;

interface

uses Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
     Dialogs, DirectShow9, WMF9, ActiveX, DSPack,
     Common, MMSystem;


 function CreateFilterGraph( var pGraph : IGraphBuilder):HRESULT;
 function CreateFilter( clsid: TGUID; var ppFilter: IBaseFilter):HRESULT;

 function GetUnConnectedPin(aGraph:IGraphBuilder;
                            aIBFName:String;
                            aPinDir:PIN_DIRECTION):IPin;
 function GetAnyPin(aGraph:IGraphBuilder; aIBFName:String;aPinDir:PIN_DIRECTION):IPin;


 function GetConnectedPin(aGraph:IGraphBuilder;
                          aIBFName:String;
                          aPinDir:PIN_DIRECTION):IPin;

 function CreateAndAddFilter(aName:String;
                             aGraph:IGraphBuilder;
                             aCLSID:TGUID):HRESULT;

 function GetFilter(aName:String;aGraph:IGraphBuilder):IBaseFilter;
 function GraphToRot(Graph: IGraphBuilder; out ID: integer): HRESULT;
 function SetNoClock(const pHWND : HWND;pGraph:IFilterGraph):HRESULT;
 function RenderOutPutPins(const pHWND : HWND;pFilter:IBaseFilter;pGB:IGraphBuilder):HRESULT;

function GetFileInfo(pFile : String;
                     var pFrameRate,
                         pDuration : double;
                     var refDuration : REFERENCE_Time;
                     var pVideoStreamAvailable,
                         pAudioStreamAvailable : Boolean;
                     var pWidth, pHeight : Integer) : HRESULT;

function GetPinByMajorType(pFilter: IBaseFilter;
                           PinDir: PIN_DIRECTION; mType: TGUID; var ppPin: IPin): HRESULT;

function ConnectFilters(pGraph : IGraphbuilder;
                        //pOutFilter, pInFilter : IBaseFilter;
                        sFilterOut, sFilterIn : String;
                        pMajorType:TGUID;
                        VerifyMTOut,
                        VerifyMTIn,
                        OnlyUnConnectedOut,
                        OnlyUnConnectedIn : Boolean ) :HRESULT;


implementation

function CreateFilterGraph(var pGraph: IGraphBuilder): HRESULT;
begin
  result := CoCreateInstance(CLSID_FilterGraph, nil,
                             CLSCTX_INPROC,IID_IGraphBuilder, pGraph);
  if (pGraph = nil) then
       begin result :=  E_POINTER; exit; end;

end;

function CreateFilter(clsid: TGUID;
  var ppFilter: IBaseFilter): HRESULT;
begin
   result := CoCreateInstance(clsID, nil,
                              CLSCTX_INPROC,IID_IBaseFilter, ppFilter);
  if (ppFilter = nil) then
       begin result :=  E_POINTER; exit; end;
end;

function GetUnConnectedPin(aGraph:IGraphBuilder; aIBFName:String;aPinDir:PIN_DIRECTION):IPin;
var
 tempIBFilter   : IBaseFilter;
 tPin,
 aPin           : IPin;
 Enum           : IEnumPins;
 currentPinDir  : PIN_DIRECTION;

 aHR            : HRESULT;

begin
  tPin := nil;
  aPin := nil;

  aHR := aGraph.FindFilterByName(StringToOLEStr(aIBFName),tempIBFilter);
  if IsError(ahr) then
   begin
    ShowMessage('ERROR: Could not find filter: '+aIBFName);
    result := nil;
    Exit;
   end;

  aHR := tempIBFilter.EnumPins(Enum);
  if IsError(aHR) then ShowMessage('HRESULT Error: '+HRToStr(aHR)) else
  while (Enum.Next(1,aPin,nil) = s_OK) do
   begin
    aPin.QueryDirection(currentPinDir);
    if (currentPinDir = aPinDir) then
     begin
      tPin := nil;
      ahr := aPin.ConnectedTo(tPin);
      if Succeeded(ahr) then tPin := nil else
       begin
        result := aPin;
        aPin := nil;
        Enum := nil;
        break;
       end;
     end;
   end;
end;

function GetAnyPin(aGraph:IGraphBuilder; aIBFName:String;aPinDir:PIN_DIRECTION):IPin;
var
 tempIBFilter   : IBaseFilter;
 tPin,
 aPin           : IPin;
 Enum           : IEnumPins;
 currentPinDir  : PIN_DIRECTION;

 aHR            : HRESULT;

begin
  tPin := nil;
  aPin := nil;

  aHR := aGraph.FindFilterByName(StringToOLEStr(aIBFName),tempIBFilter);
  if IsError(ahr) then
   begin
    ShowMessage('ERROR: Could not find filter: '+aIBFName);
    result := nil;
    Exit;
   end;

  aHR := tempIBFilter.EnumPins(Enum);
  if IsError(aHR) then ShowMessage('HRESULT Error: '+HRToStr(aHR)) else
  while (Enum.Next(1,aPin,nil) = s_OK) do
   begin
    aPin.QueryDirection(currentPinDir);
    if (currentPinDir = aPinDir) then
     begin
       result := aPin;
       break;
     end;
   end;
end;

function GetConnectedPin(aGraph:IGraphBuilder; aIBFName:String;aPinDir:PIN_DIRECTION):IPin;
var
 tempIBFilter   : IBaseFilter;
 tPin,
 aPin           : IPin;
 Enum           : IEnumPins;
 currentPinDir  : PIN_DIRECTION;

 ahr : HRESULT;

begin
  tPin := nil;
  aPin := nil;

  ahr := aGraph.FindFilterByName(StringToOLEStr(aIBFName),tempIBFilter);
  if IsError(ahr) then
   begin
    ShowDlg('Directshow error: ','ERROR: Could not find filter: '+aIBFName,4);
    result := nil;
    Exit;
   end;
  ahr := tempIBFilter.EnumPins(Enum);
  if IsError(aHR) then ShowDlg('HRESULT Error',HRToStr(aHR),4) else
  while (Enum.Next(1,aPin,nil) = s_OK) do
   begin
    aPin.QueryDirection(currentPinDir);
    if (currentPinDir = aPinDir) then
     begin
      tPin := nil;
      ahr := aPin.ConnectedTo(tPin); // check if connected
      if Succeeded(ahr) then // is it?
       begin
        result := aPin;
        aPin := nil;
        Enum := nil;
        break;
       end else tPin := nil; // no connected pin next...
     end;
   end;
end;


function GraphToRot(Graph: IGraphBuilder; out ID: integer): HRESULT;
  var
    Moniker: IMoniker;
    ROT    : IRunningObjectTable;
    wsz    : WideString;
  begin
    result := GetRunningObjectTable(0, ROT);
    if (result <> S_OK) then exit;
    wsz := format('FilterGraph %p pid %x',[pointer(graph),GetCurrentProcessId()]);
    result  := CreateItemMoniker('!', PWideChar(wsz), Moniker);
    if (result <> S_OK) then exit;
    result  := ROT.Register(0, Graph, Moniker, ID);
    Moniker := nil;
  end;

function GetFilter(aName:String;aGraph:IGraphBuilder):IBaseFilter;
var
 hr : HRESULT;
 begin
  hr := aGraph.FindFilterByName(StringToOLEStr(aName),result);

  if IsError(hr) then
   ShowDlg('Directshow error: ','ERROR: Could not find filter: '+aName,4);
 end;

function CreateAndAddFilter(aName:String;
                                   aGraph:IGraphBuilder;
                                   aCLSID:TGUID):HRESULT;
 var
  tempIBFilter : IBaseFilter;
  hr : HRESULT;
 begin

  result := CoCreateInstance(aCLSID, nil, CLSCTX_INPROC ,IID_IBaseFilter, tempIBFilter);
  if Failed(result) then
   begin ShowDlg('Directshow error','Add filter error: '+HRToStr(result),4); Exit; end;

  result := aGraph.AddFilter(tempIBFilter,StringToOLEStr(aName));
  if Failed(result) then
   begin ShowDlg('Directshow error','Add filter error: '+HRToStr(result),4); Exit; end;

  if aName = 'BM Video' then
   begin
//    hr := tempIBFilter.QueryInterface(IDeckLinkKeyer,dKey);
//    if IsError(hr) then ShowMessage('KEY ERROR: '+HRTOStr(hr));
//    dKey.set_DefaultTimebase(
   end;

  tempIBFilter := nil;

  while (HR <> S_OK) and (tempIBFilter = nil) do
  HR := aGraph.FindFilterByName(StringToOLEStr(aName),tempIBFilter);


 end;

function SetNoClock(const pHWND : HWND;pGraph: IFilterGraph): HRESULT;
var
 pFilter : IMediaFilter;
begin
 if (pGraph=nil) then result := E_POINTER else
  begin
   result := pGraph.QueryInterface(IMediaFilter,pFilter);
   if failed(result) then begin exit; end;
   result := pFilter.SetSyncSource(nil);
   if failed(result) then begin exit; end;
  end;
end;

function RenderOutPutPins(const pHWND : HWND;pFilter:IBaseFilter;pGB:IGraphBuilder):HRESULT;
var
 pEnum          : IEnumPins;
 pPin           : IPin;
 pPinDir        : PIN_DIRECTION;

begin

 result := pFilter.EnumPins(pEnum);
 if failed(result) then begin exit; end;

 while (pEnum.Next(1,pPin,nil)=S_OK) do
  begin
   pPin.QueryDirection(pPinDir);
   if (pPinDir = PINDIR_OUTPUT) then
   result := ( pGB as IFilterGraph2).RenderEx(
               pPin,AM_RENDEREX_RENDERTOEXISTINGRENDERERS,nil);
   if failed(result) then break;
  end;

end;


function GetFileInfo(pFile : String;
                     var pFrameRate,
                         pDuration : double;
                     var refDuration : REFERENCE_Time;
                     var pVideoStreamAvailable,
                         pAudioStreamAvailable : Boolean;
                     var pWidth, pHeight : Integer) : HRESULT;

var
 bVideoStream   : Boolean;
 dVideoDuration,
 dAudioDuration : double;
 i,
 lStreamCount,
 nVideoLengthBytes,
 nAudioLengthByte  : integer;

 majorType,
 videoSubType      : TGUID;

 pDet              : IMediaDet;

 mt                : _AMMediaType;
 pVih              : PWMVideoInfoHeader;

 pWav              : PWaveFormatEx;

begin
	// init all pointers
	pFramerate := 0;
	pVideoStreamAvailable := FALSE;
	pAudioStreamAvailable := FALSE;
	pWidth := 0;
	pHeight := 0;
	pDuration := 0;
        bVideoStream := False;

	result := S_OK;


        result := CoCreateInstance(CLSID_MediaDet, nil,
                                   CLSCTX_INPROC,IID_IMediaDet, pDet);

	if failed(result) then exit;

	result := pDet.put_Filename(pFIle);
	if (FAILED(result)) then exit;

	result := pDet.get_OutputStreams(lStreamCount);
	for i:=0 to lStreamCount - 1 do
	begin

		result:= pDet.put_CurrentStream(i);
		result:= pDet.get_StreamType(majortype);

		if IsEqualGUID(majortype,MEDIATYPE_Video) then  // Found a video stream.
		begin
			bVideoStream := TRUE;

			// video stream is available
			pVideoStreamAvailable := TRUE;

			// get framerate
			pDet.get_FrameRate(pFramerate);

			// get length of video stream
			pDet.get_StreamLength(dVideoDuration);
			pDuration := dVideoDuration;

			// get detailed info about video
			result:= pDet.get_StreamMediaType(mt);
			if (SUCCEEDED(result)) then
			begin
				videoSubType := mt.subtype;

				// avi, mpeg and so on have this...
				if IsEqualGUID(mt.formattype,FORMAT_VideoInfo) then
				begin
                                       pVih := PWMVideoInfoHeader(mt.pbFormat);
					pWidth := pVih.bmiHeader.biWidth;
					pHeight := pVih.bmiHeader.biHeight;
					if (pHeight < 0)then pHeight := -1;
				end
				else if IsEqualGUID(mt.formattype, FORMAT_VideoInfo2) then
				begin
					ASSERT(FALSE); // not supported yet
				end
				else if IsEqualGUID(mt.formattype, FORMAT_MPEG2Video ) then
				begin
					ASSERT(FALSE); // not supported yet
				end;
			end;


		end
		else if IsEqualGUID(majortype,MEDIATYPE_Audio) then
		begin
			// audio stream is available
			pAudioStreamAvailable := TRUE;

			// get audio stream length
			pDet.get_StreamLength(dAudioDuration);

			result:= pDet.get_StreamMediaType(mt);
			if (SUCCEEDED(result)) and
                           IsEqualGUID(mt.formattype,FORMAT_WaveFormatEx) then
			begin
                                pWav := PWaveFormatEX(mt.pbFormat);
				nAudioLengthByte := Trunc(pWav.nAvgBytesPerSec * dAudioDuration);
			end
		end
	end;

	// use the longer duration of the two as the duration
	if (pDuration>0) then
	begin
		if (dAudioDuration >  dVideoDuration) then
			pDuration := dAudioDuration
		else
			pDuration := dVideoDuration;
         refDuration := Trunc(pDuration * 10000000);
	end;

 pDet := nil;

end;

function GetPinByMajorType(pFilter: IBaseFilter;
                           PinDir: PIN_DIRECTION;
                           mType: TGUID; var ppPin: IPin
                           ): HRESULT;

var
 pEnum                  : IEnumPins;
 pPin                   : IPin;
 pPinDir                : PIN_DIRECTION;
 pEnumMediaTypes        : IEnumMediaTypes;
 mt                     : TAMMediaType;
 pMT                    : PAMMediaType;
begin

 result := pFilter.EnumPins(pEnum);
 if failed(result) then begin exit; end;

 while (pEnum.Next(1,pPin,nil)=S_OK) do
  begin
   pPin.QueryDirection(pPinDir);
   result := pPin.ConnectionMediaType(mt);
   if SUCCEEDED(result) then
    begin
     if ( PinDir = pPinDir ) and
        ( IsEqualGUID(mType,mt.majortype) ) then
        begin
         ppPin := pPin;
         exit;
        end;
    end
   else
    begin
     if result = VFW_E_NOT_CONNECTED then
      begin
       pPin.EnumMediaTypes(pEnumMediaTypes);
       while (pEnumMediaTypes.Next(1,pMT,nil)=S_OK) do
       if IsEqualGUID(pMT^.majortype,mType) then
        begin
         ppPin := pPin;
         result := S_OK;
         exit;
        end;
      end;
    end;
   end;

 result := E_FAIL;

end;


function ConnectFilters(pGraph : IGraphbuilder;
                        //pOutFilter, pInFilter : IBaseFilter;
                        sFilterOut, sFilterIn : String;
                        pMajorType : TGUID;
                        VerifyMTOut,
                        VerifyMTIn,
                        OnlyUnConnectedOut,
                        OnlyUnConnectedIn : Boolean):HRESULT;
var
 tPin,
 inPin,
 outPin : IPin;

 pInFilter,
 pOutFilter : IBaseFilter;

begin

 // Get filters
 pOutFilter := GetFilter(sFilterOut,pGraph);
 pInFilter := GetFilter(sFilterIn,pGraph);

 if (pOutFilter = nil) or (pInFilter = nil) then
  begin result := E_FAIL; exit; end;

 // Get PINS to connect.
 if VerifyMTOut then
  result := GetPinByMajorType(pOutFilter,PINDIR_OUTPUT,pMajorType,outPin) else
 if OnlyUnConnectedOut then
  outPin := GetUnConnectedPin(pGraph,sFilterOut,PINDIR_OUTPUT)
 else
  outPin := GetAnyPin(pGraph,sFilterOut,PINDIR_OUTPUT);
 if outPin = nil then begin result := E_FAIL; Exit; end;

 if VerifyMTIn then
  result := GetPinByMajorType(pInFilter,PINDIR_INPUT,pMajorType,inPin) else
 if OnlyUnConnectedIn then
  outPin := GetUnConnectedPin(pGraph,sFilterIn,PINDIR_INPUT)
 else
  inPin := GetAnyPin(pGraph,sFilterIn,PINDIR_INPUT);

 if inPin = nil then begin result := E_FAIL; Exit; end;

 // Check so its not allready connected, if it is: Disconnect.
  result := OutPin.ConnectedTo(tPin);
   if Succeeded(result) then
    OutPin.Disconnect;
  result := InPin.ConnectedTo(tPin);
   if Succeeded(result) then
    InPin.Disconnect;

  result := pGraph.Connect(outPin,inPin);

end;


end.
