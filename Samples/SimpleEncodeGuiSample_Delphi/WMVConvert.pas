unit WMVConvert;

interface

uses Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls,
     Forms, ExtCtrls,
     Dialogs, DirectShow9, WMF9, ActiveX, MasterIT_Common, VSFilter,
     DS_Common,

     Math,
     MVFilterCommon,
     MMSystem,
     MVTextOverlay_TLB,
     MVBitmapOverlay_TLB,
     StandardMpegEncoderLib_TLB
     ;

const
 WM_WMVMESSAGE          = WM_USER+100;

 CLSID_VOBSUB       : TGUID = '{93A22E7A-5091-45EF-BA61-6DA26156A5D0}';
 CLSID_VOBSUBAuto   : TGUID = '{9852A670-F845-491B-9BE6-EBD841B8A613}';


 licKey        = '---';


 lbl1MSG       = 1;
 lbl2MSG       = 2;
 lbl3MSG       = 3;
 lbl4MSG       = 4;
 lbl5MSG       = 5;
 progMSG       = 10;
 memMSG        = 11;

type

 TWMReaderCallback  =
  class(TInterfacedObject,IWMReaderCallback, IAMWMBufferPassCallback)
  private
   public

    aHWND     : HWND;
    aTHID     : Integer;

    curFrame  : SmallInt;
    tdStarted : TDateTime;
    refDur    : REFERENCE_TIME;
   protected

    function OnStatus(Status: TWMTStatus; hr: HRESULT;
      dwType: TWMTAttrDataType; pValue: PBYTE;
      pvContext: Pointer): HRESULT; stdcall;
    function OnSample(dwOutputNum: LongWord; cnsSampleTime, cnsSampleDuration: Int64;
      dwFlags: LongWord; pSample: INSSBuffer; pvContext: Pointer): HRESULT; stdcall;
    function Notify( pNSSBuffer3: INSSBuffer3; pPin: IPin;
                     prtStart, prtEnd: PReferenceTime): HRESULT; stdcall;

  end;

 TWMVConvert =
  class(TInterfacedObject)
   public
    pGB            : IGraphBuilder;
    pMC            : IMediaControl;
    pMS            : IMediaSeeking;
    pWMRCallback   : TWMReaderCallback;

   function ConvertFile(  pHWND : HWND;
                          pAppDir,
                          inWMVFile,
                          outFile,
                          StringToOverlay,
                          BMPOverlayFile : String;
                          FontSize,
                          VStreamType,
                          VWidth,
                          VHeight,
                          BitrateControl,
                          VBitrateKBps,
                          VBitrateMinKBps,
                          VBitrateMaxKBps,
                          AspectRatio,
                          VBVBuffer,
                          AStreamType,
                          ASampleRate,
                          AChannels,
                          ABitrateKBps,
                          StreamType : Integer;
                          FrameRate : Double;
                          ErrorProtection,
                          OriginalFlag,
                          CopyrightFlag,
                          PrivateFlag,
                          noVideoPreview,
                          ShowInGraphEdit : Boolean;
                          prevPanel : TPanel ) : HRESULT;


   function WaitForCompletion( aHWND : HWND;
                               aAppDir : String;
                               aGB : IGraphBuilder ) : HRESULT;
   procedure StopProgress;




  end;

var
    wmvInfo1,
    wmvInfo2,
    wmvInfo3,
    wmvInfo4,
    wmvInfo5            : String;

    curTHID,
    wmvProgress         : Integer;

implementation

{ TWMVConvert }

function TWMVConvert.ConvertFile(pHWND: HWND;
                                 pAppDir,
                                 inWMVFile,
                                 outFile,
                                 StringToOverlay,
                                 BMPOverlayFile : String;
                                 FontSize,
                                 VStreamType,
                                 VWidth,
                                 VHeight,
                                 BitrateControl,
                                 VBitrateKBps,
                                 VBitrateMinKBps,
                                 VBitrateMaxKBps,
                                 AspectRatio,
                                 VBVBuffer,
                                 AStreamType,
                                 ASampleRate,
                                 AChannels,
                                 ABitrateKBps,
                                 StreamType: Integer;
                                 FrameRate: Double;
                                 ErrorProtection,
                                 OriginalFlag,
                                 CopyrightFlag,
                                 PrivateFlag,
                                 noVideoPreview,
                                 ShowInGraphedit : Boolean;
                                 prevPanel : TPanel ): HRESULT;

var
 pGBID          : Integer;

 pVideoPin      : IPin;
 pBufferPass    : IAMWMBufferPass;

 pIBMPEG        : IBaseFilter;
 pMPEGProfile   : IStandardMpegEncoderProfile;
 pMPEGEncoder   : IStandardMPEGEncoder;
 pMPEGStats     : IStandardMPEGEncoderStats;

 pFS            : IFileSinkFilter;
 pFSrc          : IFileSourceFilter;
 pNullR,
 pSG,
 pVR,
 pColour1,
 pColour2,
 pInfTee        : IBaseFilter;

 pMVBMP         : IMVBitmapOverlay;
 pMVTEXT        : IMVTextOverlay;
 pVW            : IVideoWindow;
 pWMReader      : IWMreader;

 bKey           : Byte;
 nMinNow,
 nKey           : Integer;

 ap             : TPoint;
 aMT            : _AMMediaType;

 pOleEnum       : TOleEnum;
 ws             : WideString;


 dFPS,
 dDuration      : Double;
 refDuration    : Int64;

 bVStreamExists,
 bAStreamExists : Boolean;

 iOrgHeight,
 iOrgWidth      : Integer;

 tdStart        : TDateTime;

begin

 CoInitialize(nil);

 tdStart := now;

 curFPS := FrameRate;

 result := GetFileInfo( inWMVFile,
                    dFPS, dDuration, refDuration,
                    bVStreamExists, bAStreamExists,
                    iOrgWidth, iOrgHeight );

 if failed(result) then
  begin
   DebugLog(pAppDir,'GetFileINFO failed: '+HRToStr(result));
  end;

 result := CreateFilterGraph(pGB);
 if failed(result) then begin
                     DebugLog(pAppDir,'CreateFilterGraph failed: '+HRToStr(result));
                     Exit;
                    end;

 if ShowInGraphEdit then
 begin
  result := GraphToRot(pGB,pGBID);
   if failed(result) then begin
                       DebugLog(pAppDir,'GraphToRot failed: '+HRToStr(result));
                      end;
 end;

 result := pGB.QueryInterface(IID_IMediaControl, pMC);
 if failed(result) then begin
                     DebugLog(pAppDir,'QI IMediacontrol failed: '+HRToStr(result));
                     Exit;
                    end;
 result := pGB.QueryInterface(IID_IMediaSeeking,pMS);
 if failed(result) then begin
                     DebugLog(pAppDir,'QI IMediaSeeking failed: '+HRToStr(result));
                     Exit;
                    end;

 if not noVideoPreview then
  result := pGB.QueryInterface(IID_IVideoWindow, pVW);
  if failed(result) then begin
                      DebugLog(pAppDir,'QI IVideoWindow failed: '+HRToStr(result));
                      Exit;
                     end;

/// ---------- COCREATE FILTERS

 result := CoCreateInstance(
                   CLASS_CMVTextOverlay, nil,
                   CLSCTX_INPROC_SERVER,
                   IID_IMVTextOverlay,
                   pMVTEXT);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate MVTEXT failed: '+HRToStr(result));
                      Exit;
                     end;
 result := CoCreateInstance(
                  CLASS_CMVBitmapOverlay, nil,
                  CLSCTX_INPROC_SERVER,
                  IID_IMVBitmapOverlay,
                  pMVBMP);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate MVBMP failed: '+HRToStr(result));
                      Exit;
                     end;

 result := CoCreateInstance(
                  CLASS_StandardMpegEncoder, nil,
                  CLSCTX_INPROC_SERVER,
                  IID_IBaseFilter,
                  pIBMPEG);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate IBMPEG failed: '+HRToStr(result));
                      Exit;
                     end;

 result := CoCreateInstance(
                  CLSID_FileWriter, nil,
                  CLSCTX_INPROC_SERVER,
                  IID_IFileSinkFilter,
                  pFS);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate FILESINK failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  CoCreateInstance(
                  CLSID_InfTee, nil,
                  CLSCTX_INPROC_SERVER,
                  IID_IBaseFilter,
                  pInfTee);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate INFTEE failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  CoCreateInstance(
                  CLSID_Colour, nil,
                  CLSCTX_INPROC_SERVER,
                  IID_IBaseFilter,
                  pColour1);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate COLOR1 failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  CoCreateInstance(
                  CLSID_Colour, nil,
                  CLSCTX_INPROC_SERVER,
                  IID_IBaseFilter,
                  pColour2);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate COLOR2 failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  CoCreateInstance(
                  CLSID_WMAsfReader, nil,
                  CLSCTX_INPROC_SERVER,
                  IID_IBaseFilter,
                  pWMReader);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate WMREADER failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  CoCreateInstance(
                   CLSID_VideoRenderer,
                   nil,
                   CLSCTX_INPROC_SERVER,
                   IID_IBaseFilter,
                   pVR);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate VIDEORENDERER failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  CoCreateInstance(
                   CLSID_SampleGrabber,
                   nil,
                   CLSCTX_INPROC_SERVER,
                   IID_IBaseFilter,
                   pSG);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate SAMPLEGRABBER failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  CoCreateInstance(
                   CLSID_NullRenderer,
                   nil,
                   CLSCTX_INPROC_SERVER,
                   IID_IBaseFilter,
                   pNullR);
  if failed(result) then begin
                      DebugLog(pAppDir,'CoCreate NULLRENDERER failed: '+HRToStr(result));
                      Exit;
                     end;



/// --- ADD FILTERS TO GRAPH

 result :=  pGB.AddFilter(pMVBMP as IBaseFilter, 'MVBMP');
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfiler: MVBMP failed: '+HRToStr(result));
                      Exit;
                     end;
 result :=  pGB.AddFilter(pMVTEXT as IBaseFilter, 'MVTEXT');
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfiler: MVTEXT failed: '+HRToStr(result));
                      Exit;
                     end;
 result :=  pGB.AddFilter(pIBMPEG,StringToOLEStr('MPEGENC'));
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfiler: MPEGENC failed: '+HRToStr(result));
                      Exit;
                     end;
 result :=  pGB.AddFilter(pFS as IBaseFilter,StringToOLEStr('FILEWRITER'));
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfiler: FILEWRITER failed: '+HRToStr(result));
                      Exit;
                     end;
 result :=  pGB.AddFilter(pColour1, StringToOLEStr('COLOR1'));
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfiler: COLOR1 failed: '+HRToStr(result));
                      Exit;
                     end;
 result :=  pGB.AddFilter(pColour2, StringToOLEStr('COLOR2'));
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfiler: COLOR2 failed: '+HRToStr(result));
                      Exit;
                     end;
 result :=  pGB.AddFilter(pVR, StringToOLEStr('VR'));
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfiler: VR failed: '+HRToStr(result));
                      Exit;
                     end;


 with pMVTEXT do
  try
   Set_Enable(True);
   Set_OverlayMode(MV_TEXT_OVERLAY_MODE_TEXT);
   Set_Text(StringToOverlay);
   Set_PositionMode(MV_POSITION_RELATIVE);
   Set_RelativePosition(MV_POSITION_UPPER_RIGHT);
   Set_ForegroundColor(clWhite);
   Set_TransparentBack(true);
   Set_Shadow(true);
   Set_ShadowColor(clBlack);
   Set_FontTypeFace('Arial');
   Set_FontSize(FontSize);
   Set_Bold(true);
   Set_xMargin(15);
   Set_yMargin(15);
  except on E:Exception do
   begin
    DebugLog(pAppDir,'Exception MVTEXT: '+E.Message);
    Exit;
   end;
  end;



 with pMVBMP do
  try
   Set_BitmapPath(BMPOverlayFile);
   Set_AspectRatio(true);
   Set_mode(MV_GDI_OVERLAY_TRANSPARENT); //MV_GDI_OVERLAY_TRANSPARENT_AND_CONSTANTALPHA);
   Set_InputAlpha(100);
   Set_PositionMode(MV_POSITION_ABSOLUTE); //MV_POSITION_RELATIVE); //);
   Set_RelativePosition(MV_POSITION_UPPER_LEFT);
   Set_TransparentColour(clBlack);
   Set_XPosition(8);
   Set_YPosition(8);
   Set_ResizeHeight(35);
   Set_ResizeEnabled(true);
   Set_Enabled(True);
  except on E:Exception do
   begin
    DebugLog(pAppDir,'Exception MVBMP: '+E.Message);
    Exit;
   end;
  end;

 // Create MPEG + writer...
 result  := pIBMPEG.QueryInterface(IID_IStandardMPEGEncoder, pMPEGEncoder);
  if failed(result) then begin
                      DebugLog(pAppDir,'QI IStandardMPEGENcoder failed: '+HRToStr(result));
                      Exit;
                     end;
 pFS := (GetFilter('FILEWRITER',pGB) as IFileSinkFilter);
 if pFS = nil then begin
                    DebugLog(pAppDir,'GetFilter FILEWRITER failed. ');
                    Exit;
                   end;

 // REGISTER FILTER

 result :=  pFS.SetFileName(StringToOLEStr(outFile),nil);
  if failed(result) then begin
                      DebugLog(pAppDir,'pFS.SetFileName failed: '+HRToStr(result));
                      Exit;
                     end;


 // SET UP ENCODER FILTER ...
 try

  case StreamType of
    1  : pOleEnum := SYSTEMSFORMAT_MPEG1;
    2  : pOleEnum := SYSTEMSFORMAT_MPEG2;
    3  : pOleEnum := SYSTEMSFORMAT_VCD;
    4  : pOleEnum := SYSTEMSFORMAT_SVCD;
    5  : pOleEnum := SYSTEMSFORMAT_DVD;
    6  : pOleEnum := SYSTEMSFORMAT_VCD_STILL;
    7  : pOleEnum := SYSTEMSFORMAT_SVCD_STILL;
    8  : pOleEnum := SYSTEMSFORMAT_MP4;
    9  : pOleEnum := SYSTEMSFORMAT_3GP;
    10 : pOleEnum := SYSTEMSFORMAT_MOV;
    11 : pOleEnum := SYSTEMSFORMAT_3G2;
    12 : pOleEnum := SYSTEMSFORMAT_PSP;
    13 : pOleEnum := SYSTEMSFORMAT_AVI;
   else  pOleEnum := SYSTEMSFORMAT_NONE;

  end;
  pMPEGEncoder.GetProfile(pOleENum,
                          CONSTRAINT_PAL,
                          pMPEGProfile);

  case VStreamType of
   0 : pOleEnum := VIDEOFORMAT_NONE;
   1 : pOleEnum := VIDEOFORMAT_MPEG1;
   2 : pOleEnum := VIDEOFORMAT_MPEG2;
   3 : pOleEnum := VIDEOFORMAT_MPEG4;
   4 : pOleEnum := VIDEOFORMAT_H263;
   5 : pOleEnum := VIDEOFORMAT_H264;
  end;

  pMPEGProfile.SetVideoFormat(pOleEnum);

  pMPEGProfile.SetWidth(VWidth);
  pMPEGProfile.SetHeight(VHeight);

  case AspectRatio of
   0 : pOleEnum := ASPECTRATIO_1TO1;
   1 : pOleEnum := ASPECTRATIO_4TO3;
   2 : pOleEnum := ASPECTRATIO_16TO9;
   3 : pOleEnum := ASPECTRATIO_2D11TO1;
  end;
  pMPEGProfile.SetAspectRatio(pOleEnum);

  pMPEGProfile.SetFramerate(FrameRate);
  pMPEGProfile.SetVideoBitrate(VBitrateKBps*1000);
  pMPEGProfile.SetVideoBitrateMin(VBitrateMinKBps*1000);
  pMPEGProfile.SetVideoBitrateMax(VBitrateMaxKBPs*1000);

  case BitrateControl of
   0 : pOleEnum := BITRATEMODE_CBR;
   1 : pOleEnum := BITRATEMODE_VBR_2PASS;
   2 : pOleEnum := BITRATEMODE_MVBR;
   3 : pOleEnum := BITRATEMODE_CQ_VBR;
  end;

  pMPEGProfile.SetVideoVBRMode(pOleEnum);

  pMPEGProfile.SetVideoVBVBufferSize(VBVBuffer);


  case aStreamType of
   0 : pOleEnum := AUDIOFORMAT_NONE;
   1 : pOleEnum := AUDIOFORMAT_MP3;
   2 : pOleEnum := AUDIOFORMAT_MP2;
   3 : pOleEnum := AUDIOFORMAT_AC3;
   4 : pOleEnum := AUDIOFORMAT_PCM;
   5 : pOleEnum := AUDIOFORMAT_WAV;
   6 : pOleEnum := AUDIOFORMAT_AAC;
  end;

  pMPEGProfile.SetAudioFormat(pOleEnum);

  pMPEGProfile.SetAudioBitrate(ABitrateKBps*1000);
  pMPEGProfile.SetAudioSampleRate(ASamplerate);

  case AChannels of
   0 : pMPEGProfile.SetAudioChannels(1);
   1 : pMPEGProfile.SetAudioChannels(2);
   2 : pMPEGProfile.SetAudioChannels(6);
  end;

//  pMPEGProfile.SetVideoQuality(10);

 except on E:Exception do
  begin
   DebugLog(pAppDir,'Exception setting Encoder: '+E.Message);
   Exit;
  end;
 end;

 pMPEGEncoder.SelectProfile( pMPEGProfile );


{ result :=  pMPEGEncoder.QueryInterface(IID_IStandardMpegEncoderStats, pMPEGStats);
  if failed(result) then begin
                      DebugLog(pAppDir,'QI IStandardMPEGEncoderStats failed: '+HRToStr(result));
                      Exit;
                     end;    }

 result :=  pWMReader.QueryInterface(IID_IFileSourceFilter,pFSrc);
  if failed(result) then begin
                      DebugLog(pAppDir,'QI IFileSourceFilter failed: '+HRToStr(result));
                      Exit;
                     end;

 result :=  pFSrc.Load(StringToOLEStr(inWMVFile),nil);
  if failed(result) then begin
                      DebugLog(pAppDir,'pFSrc.Load failed: '+HRToStr(result));
                      DebugLog(pAppDir,'File: '+inWMVFile);
                      Exit;
                     end;

 result :=  pGB.AddFilter(pWMReader as IBaseFilter,'WMREADER');
  if failed(result) then begin
                      DebugLog(pAppDir,'Addfilter WMREADER failed: '+HRToStr(result));
                      Exit;
                     end;

 { Callback for reader... }
  pWMRCallBack := TWMReaderCallBack.Create;
  if pWMRCallBack = nil then
                          begin
                           result:=E_OUTOFMEMORY;
                           exit;
                          end else
  begin
   pWMRCallBack.refDur           := RefDuration;
   pWMRCallback.aHWND            := pHWND;
   pWMRCallBack.aTHID            := 0;
   pWMRCallBack.curFrame         := 5;
   pWMRCallBack.tdStarted        := tdStart;
  end;


 result :=  GetPinByMajorType(pWMReader as IBaseFilter,PINDIR_OUTPUT,MEDIATYPE_VIDEO, pVideoPin);
 if failed(result) then begin DebugLog(pAppDir,'HR ERROR: '+HRToStr(result)); exit; end;

 result :=  pVideoPin.QueryInterface(IAMWMBufferPass,pBufferPass);
 if failed(result) then begin DebugLog(pAppDir,'HR ERROR: '+HRToStr(result)); exit; end;

 result :=  pBufferPass.SetNotify(pWMRCallBack);
 if failed(result) then begin DebugLog(pAppDir,'HR ERROR: '+HRToStr(result)); exit; end;


/// CONNECT FILTERS AND RE-ROUTE THEM ...

 try

  (pGB as IFilterGraph2).RenderEx(
   GetUnConnectedPin(pGB,'WMREADER',PINDIR_OUTPUT),
   AM_RENDEREX_RENDERTOEXISTINGRENDERERS, nil);

  (pGB as IFilterGraph2).RenderEx(
   GetUnConnectedPin(pGB,'WMREADER',PINDIR_OUTPUT),
   AM_RENDEREX_RENDERTOEXISTINGRENDERERS, nil);

   result :=  pGB.AddFilter(pInfTee, StringToOLEStr('INFTEE'));
   if failed(result) then begin
                       DebugLog(pAppDir,'AddFilter INFTEE failed: '+HRToStr(result));
                       Exit;
                      end;

   if noVideoPreview then
    begin
     pGB.AddFilter(pSG,StringToOLEStr('SG'));
     pGB.AddFilter(pNullR,StringToOLEStr('NULL'));
     pGB.RemoveFilter(pVR);
    end;


   result :=  // ID 1
   ConnectFilters(pGB,
                  'WMVideo Decoder DMO',
                  'MVTEXT',
                  MEDIATYPE_VIDEO, false, false, false, false );
   if failed(result) then begin
                       DebugLog(pAppDir,'ConnectFilters ID 1 failed: '+HRToStr(result));
                       Exit;
                      end;
   result :=  // ID 2
   ConnectFilters(pGB,
                  'MVTEXT',
                  'MVBMP',
                  MEDIATYPE_VIDEO, false, false,false,false );
   if failed(result) then begin
                       DebugLog(pAppDir,'ConnectFilters ID 2 failed: '+HRToStr(result));
                       Exit;
                      end;
   result :=  // ID 3
   ConnectFilters(pGB,
                  'MVBMP',
                  'INFTEE',
                  MEDIATYPE_VIDEO, false, false, false, false );
   if failed(result) then begin
                       DebugLog(pAppDir,'ConnectFilters ID 3 failed: '+HRToStr(result));
                       Exit;
                      end;
   result :=  // ID 4
   ConnectFilters(pGB,
                  'INFTEE',
                  'COLOR1',
                  MEDIATYPE_VIDEO, false, false, false, false );
   if failed(result) then begin
                       DebugLog(pAppDir,'ConnectFilters ID 4 failed: '+HRToStr(result));
                       Exit;
                      end;
   result :=  // ID 5
   ConnectFilters(pGB,
                  'COLOR1',
                  'MPEGENC',
                  MEDIATYPE_VIDEO, false, false, false, false );
   if failed(result) then begin
                       DebugLog(pAppDir,'ConnectFilters ID 5 failed: '+HRToStr(result));
                       Exit;
                      end;
   result :=  // ID 6
   ConnectFilters(pGB,
                  'MPEGENC',
                  'FILEWRITER',
                  MEDIATYPE_VIDEO, false, false, false, false );
   if failed(result) then begin
                       DebugLog(pAppDir,'ConnectFilters ID 6 failed: '+HRToStr(result));
                       Exit;
                      end;
   result :=  // ID 7
   ConnectFilters(pGB,
                  'INFTEE',
                  'COLOR2',
                  MEDIATYPE_VIDEO, false, false, true, false );
   if failed(result) then begin
                       DebugLog(pAppDir,'ConnectFilters ID 7 failed: '+HRToStr(result));
                       Exit;
                      end;


   if noVideoPreview then
    begin
     aMT.majortype := MEDIATYPE_Video;
     (pSG as ISampleGrabber).SetMediaType(aMT);
     (pSG as ISampleGrabber).SetOneShot(false);
     (pSG as ISampleGrabber).SetBufferSamples(false);

     result :=  // ID 8
     ConnectFilters(pGB,
                    'COLOR2',
                    'SG',
                    MEDIATYPE_VIDEO, false, false, false, false );
     if failed(result) then begin
                         DebugLog(pAppDir,'ConnectFilters ID 8 failed: '+HRToStr(result));
                         Exit;
                        end;
     result :=  // ID 9
     ConnectFilters(pGB,
                    'SG',
                    'NULL',
                    MEDIATYPE_VIDEO, false, false, false, false );
     if failed(result) then begin
                         DebugLog(pAppDir,'ConnectFilters ID 9 failed: '+HRToStr(result));
                         Exit;
                        end;
    end
   else
    begin
     result :=  // ID 10
     ConnectFilters(pGB,
                    'COLOR2',
                    'VR',
                    MEDIATYPE_VIDEO, false, false, false, false );
     if failed(result) then begin
                         DebugLog(pAppDir,'ConnectFilters ID 10 failed: '+HRToStr(result));
                         Exit;
                        end;
    end;

 except on E:Exception do
   begin
    DebugLog(pAppDir,'Exception in reroute of connections: '+E.Message);
    Exit;
   end;
 end;


 if not noVideoPreview then
  begin
   aP := Point(prevPanel.Left, prevPanel.Top);
   aP := prevPanel.ClientToScreen(aP);

   pVW.put_Owner(prevPanel.Handle);
   pVW.put_WindowStyle(WS_CHILD or WS_CLIPCHILDREN);
   pVW.put_Width(prevPanel.Width);
   pVW.put_Height(prevPanel.Height);
   pVW.put_Left(1);
   pVW.put_Top(1);
   pVW.put_Visible(true);
  end;

 SetNoClock(0,pGB);

 pFS            := nil;
 pFSrc          := nil;
 pNullR         := nil;
 pSG            := nil;
 pVR            := nil;
 pColour1       := nil;
 pColour2       := nil;
 pInfTee        := nil;

 pMVBMP         := nil;
 pMVTEXT        := nil;
 pVW            := nil;
 pMPEGProfile   := nil;
 pWMReader      := nil;
 pMPEGEncoder   := nil;


 pMC.Run;

 WaitForCompletion(pHWND, pAppDir, pGB);

 CoUnInitialize;

end;


procedure TWMVConvert.StopProgress;
begin
 if pMC <> nil then pMC.Stop;

 pMC            := nil;
 pMS            := nil;
 pGB            := nil;

end;

function TWMVConvert.WaitForCompletion( aHWND : HWND;
                                        aAppDir : String;
                                        aGB: IGraphBuilder): HRESULT;
var
  hr          : HRESULT;
  levCode     : integer;
  pME         : IMediaEvent;
  hEvent      : OAEVENT;
  lp1, lp2    : Integer;

begin


 result := s_ok;
 levCode := 0;

 if (aGB = nil) then
      begin result :=  -1; exit; end;

    result := aGB.QueryInterface(IMediaEvent, pME);
    if (SUCCEEDED(hr)) then
    begin
       result := pME.GetEventHandle(hEvent);
        while(SUCCEEDED(hr)) do
         try
            // Wait for completion and dispatch messages for any windows
            // created on our thread.
           if (WaitForSingleObject( hEvent, INFINITE ) = WAIT_OBJECT_0 ) then
              // Event signaled. See if we're done.
                if(pME.GetEvent(levCode, lp1, lp2, 0) = S_OK) then
                begin
                    pME.FreeEventParams(levCode, lp1, lp2);
                    result := levCode;
                    if(EC_COMPLETE = levCode) then
                    begin
                     break;
                    end
                    else if(EC_ERRORABORT = levCode) then
                    begin
                     DebugLog(aAppDir,'EVENT: ERROR ABORT !');
                     break;
                    end
                    else if(EC_USERABORT = levCode) then
                    begin
                     DebugLog(aAppDir,'EVENT: USER ABORT !');
                     break;
                    end
                    else if( EC_PREPROCESS_COMPLETE = levCode) then
                    begin
                     break;
                    end
                    else
                    begin
                     DebugLog(aAppDir,'EVENT: Unknown '+IntToStr(levCode));
                     //DebugLog(strAppDir,'WaitForCompletion: Received event: '+IntToStr(levCode));
                    end;
                 end;
         except on E:Exception do
          begin
           DebugLog(aAppDir,'WaitForComplet exception: '+E.Message);
           result := E_Fail;
          end;
         end; // except
    end else
     begin
      DebugLog(aAppDir, 'WaitForCompletion: QI failed for IMediaEvent interface');
     end;
end;

{ TWMReaderCallback }

function TWMReaderCallback.Notify(pNSSBuffer3: INSSBuffer3; pPin: IPin;
                                  prtStart, prtEnd: PReferenceTime): HRESULT;
var

 secLEFT  : Double;

 S             : String;

 TotalTime     : TDateTime;
 H, M,
 Sec, MS       : Word;

 refSpeed,
 refTime        : Double;
 iProgress,
 EncodedFrames,
 fBytes         : Integer;
 ws             : WideString;

 refTotal,
 refDone       : REFERENCE_TIME;
begin

 // progress ...
  try

   refDone := prtStart^;
   refTotal := refDur;

   if curFrame > 5 then
    begin
     TotalTime     :=  Now - tdStarted;
     DecodeTime(TotalTime, H, M, Sec, MS);

     Sec           := Sec + M * 60 + H * 3600;
     refTime       := Sec + MS / 1000;

     if refTime > 0 then
      refSpeed     := (refDone) / refTime else refSpeed := 0;

     if refSpeed > 0 then begin
       Sec         := Trunc(( (refTOTAL - refDONE) ) / refSpeed);
       S           := Format('%2.2d:%2.2d:%2.2d', [Sec div 3600, (Sec div 60) mod 60, Sec mod 60]);
       S           := 'Time remaining ' + S;
     end
     else S := '';

     wmvProgress := Round(refDone * 100 / refTotal);

     wmvInfo1 := 'Seconds done: '+IntToStr(refDONE DIV 10000000);
     wmvInfo2 := s;
     wmvInfo3 := 'Time: '+TimeToStr(now - tdStarted);
     wmvInfo4 := Format('Speed: %2.2f: s/s',[refSpeed / 10000000] )+
                       ', FPS: '+ IntToStr(REFToFrame(Trunc(refSpeed)));

     SendMessage(aHWND,WM_WMVMESSAGE,lbl1MSG,aTHID);
     SendMessage(aHWND,WM_WMVMESSAGE,lbl2MSG,aTHID);
     SendMessage(aHWND,WM_WMVMESSAGE,lbl3MSG,aTHID);
     SendMessage(aHWND,WM_WMVMESSAGE,lbl4MSG,aTHID);
     SendMessage(aHWND,WM_WMVMESSAGE,lbl5MSG,aTHID);
     SendMessage(aHWND,WM_WMVMESSAGE,progMSG,aTHID);

     curFrame := 0;
    end else Inc(curFrame);

  except on E:Exception do
   begin
   end;
  end;

end;

function TWMReaderCallback.OnSample(dwOutputNum: LongWord; cnsSampleTime,
  cnsSampleDuration: Int64; dwFlags: LongWord; pSample: INSSBuffer;
  pvContext: Pointer): HRESULT;
begin

end;

function TWMReaderCallback.OnStatus(Status: TWMTStatus; hr: HRESULT;
  dwType: TWMTAttrDataType; pValue: PBYTE; pvContext: Pointer): HRESULT;
begin

end;

end.
