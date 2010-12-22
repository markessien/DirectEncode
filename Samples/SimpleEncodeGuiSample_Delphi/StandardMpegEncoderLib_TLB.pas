unit StandardMpegEncoderLib_TLB;

// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// PASTLWTR : $Revision:   1.130.1.0.1.0.1.6  $
// File generated on 2006-09-19 11:50:59 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Standard MPEG Encoder\Include\DirectEncode.tlb (1)
// LIBID: {F8485A7F-42AE-4414-A09F-E1B262E68B0B}
// LCID: 0
// Helpfile: 
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
//   (2) v4.0 StdVCL, (C:\WINDOWS\system32\stdvcl40.dll)
// ************************************************************************ //
// *************************************************************************//
// NOTE:                                                                      
// Items guarded by $IFDEF_LIVE_SERVER_AT_DESIGN_TIME are used by properties  
// which return objects that may need to be explicitly created via a function 
// call prior to any access via the property. These items have been disabled  
// in order to prevent accidental use from within the object inspector. You   
// may enable them by defining LIVE_SERVER_AT_DESIGN_TIME or by selectively   
// removing them from the $IFDEF blocks. However, such items must still be    
// programmatically created via a method of the appropriate CoClass before    
// they can be used.                                                          
{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers. 
{$WARN SYMBOL_PLATFORM OFF}
{$WRITEABLECONST ON}
{$VARPROPSETTER ON}
interface

uses Windows, ActiveX, Classes, Graphics, OleServer, StdVCL, Variants;
  

// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLASS_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
const
  // TypeLibrary Major and minor versions
  StandardMpegEncoderLibMajorVersion = 4;
  StandardMpegEncoderLibMinorVersion = 51;

  LIBID_StandardMpegEncoderLib: TGUID = '{F8485A7F-42AE-4414-A09F-E1B262E68B0B}';

  CLASS_StandardMpegEncoder: TGUID = '{CFD87339-C61F-46CA-B6A1-F87D6B96243E}';
  IID_IStandardMpegEncoder: TGUID = '{91D3D934-6DEE-42C5-A687-6F81E1162559}';
  IID_IStandardMpegEncoderProfile: TGUID = '{182EB270-5FA5-46E8-83BA-40F7205C545B}';
  IID_IStandardMpegEncoderStats: TGUID = '{C9510218-F457-4D51-8389-7386E6EDD0EF}';
  CLASS_StandardMpegEncoderStats: TGUID = '{1C356305-4D1C-45E1-AA93-1AE16C7DE429}';
  CLASS_StandardMpegEncoderProfile: TGUID = '{D4D68F8A-B665-41D4-94D1-E8843001E346}';
  IID_IStandardMpegMultiplexerProfile: TGUID = '{7E772181-B7ED-4D9D-A364-0E8771AAFF70}';
  CLASS_StandardMpegMultiplexerProfile: TGUID = '{022A32A5-3689-4D5F-B8CC-C26655C2BA03}';
  IID_IPropertyPage: TGUID = '{B196B28D-BAB4-101A-B69C-00AA00341D07}';
  CLASS_StandardMpegEncoderGeneralProps: TGUID = '{4A6D5C73-270C-4C05-871A-28230F2A8BCC}';
  IID_IPropertyPageSite: TGUID = '{B196B28C-BAB4-101A-B69C-00AA00341D07}';
  CLASS_StandardMpegEncoderVideoProps: TGUID = '{DCD4E0B0-FE55-44C6-9B4C-1E78FA2D6D2C}';
  CLASS_StandardMpegEncoderAudioProps: TGUID = '{BDB70B23-BAA7-44A5-8CB5-A3F5F34865C8}';

// *********************************************************************//
// Declaration of Enumerations defined in Type Library                    
// *********************************************************************//
// Constants for enum _SystemsOutputFormat
type
  _SystemsOutputFormat = TOleEnum;
const
  SYSTEMSFORMAT_NONE = $00000000;
  SYSTEMSFORMAT_MPEG1 = $00000001;
  SYSTEMSFORMAT_MPEG2 = $00000002;
  SYSTEMSFORMAT_VCD = $00000003;
  SYSTEMSFORMAT_SVCD = $00000004;
  SYSTEMSFORMAT_DVD = $00000005;
  SYSTEMSFORMAT_VCD_STILL = $00000006;
  SYSTEMSFORMAT_SVCD_STILL = $00000007;
  SYSTEMSFORMAT_MP4 = $00000008;
  SYSTEMSFORMAT_3GP = $00000009;
  SYSTEMSFORMAT_MOV = $0000000A;
  SYSTEMSFORMAT_3G2 = $0000000B;
  SYSTEMSFORMAT_PSP = $0000000C;
  SYSTEMSFORMAT_AVI = $0000000D;
  SYSTEMSFORMAT_RM = $0000000E;
  SYSTEMSFORMAT_KVCD = $0000000F;

// Constants for enum _Constraint
type
  _Constraint = TOleEnum;
const
  CONSTRAINT_NONE = $00000000;
  CONSTRAINT_NTSC = $00000001;
  CONSTRAINT_FILM = $00000002;
  CONSTRAINT_PAL = $00000003;
  CONSTRAINT_IPOD = $00000004;

// Constants for enum _AudioOutputFormat
type
  _AudioOutputFormat = TOleEnum;
const
  AUDIOFORMAT_NONE = $00000000;
  AUDIOFORMAT_MP3 = $00000001;
  AUDIOFORMAT_MP2 = $00000002;
  AUDIOFORMAT_AC3 = $00000003;
  AUDIOFORMAT_PCM = $00000004;
  AUDIOFORMAT_WAV = $00000005;
  AUDIOFORMAT_AAC = $00000006;
  AUDIOFORMAT_AMRNB = $00000007;

// Constants for enum _VideoOutputFormat
type
  _VideoOutputFormat = TOleEnum;
const
  VIDEOFORMAT_NONE = $00000000;
  VIDEOFORMAT_MPEG1 = $00000001;
  VIDEOFORMAT_MPEG2 = $00000002;
  VIDEOFORMAT_MPEG4 = $00000003;
  VIDEOFORMAT_H263 = $00000004;
  VIDEOFORMAT_H264 = $00000005;

// Constants for enum _AspectRatio
type
  _AspectRatio = TOleEnum;
const
  ASPECTRATIO_1TO1 = $00000000;
  ASPECTRATIO_4TO3 = $00000001;
  ASPECTRATIO_16TO9 = $00000002;
  ASPECTRATIO_2D11TO1 = $00000003;

// Constants for enum _BitrateMode
type
  _BitrateMode = TOleEnum;
const
  BITRATEMODE_CBR = $00000000;
  BITRATEMODE_VBR_2PASS = $00000001;
  BITRATEMODE_MVBR = $00000002;
  BITRATEMODE_CQ_VBR = $00000003;
  BITRATEMODE_CQ = $00000004;

// Constants for enum _EncodeMode
type
  _EncodeMode = TOleEnum;
const
  ENCODEMODE_NOINTERLACE = $00000000;
  ENCODEMODE_INTERLACE = $00000001;
  ENCODEMODE_32PULLDOWN = $00000002;
  ENCODEMODE_32PULLDOWN_INVERSE = $00000003;

type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IStandardMpegEncoder = interface;
  IStandardMpegEncoderDisp = dispinterface;
  IStandardMpegEncoderProfile = interface;
  IStandardMpegEncoderProfileDisp = dispinterface;
  IStandardMpegEncoderStats = interface;
  IStandardMpegEncoderStatsDisp = dispinterface;
  IStandardMpegMultiplexerProfile = interface;
  IStandardMpegMultiplexerProfileDisp = dispinterface;
  IPropertyPage = interface;
  IPropertyPageSite = interface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  StandardMpegEncoder = IUnknown;
  StandardMpegEncoderStats = IStandardMpegEncoderStats;
  StandardMpegEncoderProfile = IStandardMpegEncoderProfile;
  StandardMpegMultiplexerProfile = IStandardMpegMultiplexerProfile;
  StandardMpegEncoderGeneralProps = IPropertyPage;
  StandardMpegEncoderVideoProps = IPropertyPage;
  StandardMpegEncoderAudioProps = IPropertyPage;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//
  wireHWND = ^_RemotableHandle; 
  PUserType1 = ^_GUID; {*}
  PInteger1 = ^Integer; {*}
  PUserType2 = ^tagRECT; {*}
  PIUnknown1 = ^IUnknown; {*}
  PUserType3 = ^tagMSG; {*}

  _GUID = packed record
    Data1: LongWord;
    Data2: Word;
    Data3: Word;
    Data4: array[0..7] of Byte;
  end;

  SystemsOutputFormat = _SystemsOutputFormat; 
  Constraint = _Constraint; 
  AudioOutputFormat = _AudioOutputFormat; 
  VideoOutputFormat = _VideoOutputFormat; 
  AspectRatio = _AspectRatio; 
  BitrateMode = _BitrateMode; 
  EncodeMode = _EncodeMode; 

  tagPOINT = packed record
    x: Integer;
    y: Integer;
  end;

  __MIDL_IWinTypes_0009 = record
    case Integer of
      0: (hInproc: Integer);
      1: (hRemote: Integer);
  end;

  _RemotableHandle = packed record
    fContext: Integer;
    u: __MIDL_IWinTypes_0009;
  end;

  tagMSG = packed record
    hwnd: wireHWND;
    message: SYSUINT;
    wParam: SYSUINT;
    lParam: Integer;
    time: LongWord;
    pt: tagPOINT;
  end;

  tagRECT = packed record
    left: Integer;
    top: Integer;
    right: Integer;
    bottom: Integer;
  end;

  tagSIZE = packed record
    cx: Integer;
    cy: Integer;
  end;

  tagPROPPAGEINFO = packed record
    cb: LongWord;
    pszTitle: PWideChar;
    size: tagSIZE;
    pszDocString: PWideChar;
    pszHelpFile: PWideChar;
    dwHelpContext: LongWord;
  end;


// *********************************************************************//
// Interface: IStandardMpegEncoder
// Flags:     (320) Dual OleAutomation
// GUID:      {91D3D934-6DEE-42C5-A687-6F81E1162559}
// *********************************************************************//
  IStandardMpegEncoder = interface(IUnknown)
    ['{91D3D934-6DEE-42C5-A687-6F81E1162559}']
    procedure GetProfile(systemsFormat: SystemsOutputFormat; Constraint: Constraint; 
                         out pProfile: IStandardMpegEncoderProfile); safecall;
    procedure GetSelectedProfile(out pProfile: IStandardMpegEncoderProfile); safecall;
    procedure SelectProfile(const pProfile: IStandardMpegEncoderProfile); safecall;
    procedure SelectFormat(systemsFormat: SystemsOutputFormat; Constraint: Constraint); safecall;
    procedure SetFilterLicenseKey(const strLicense: WideString); safecall;
    procedure SaveSettings(const strKey: WideString); safecall;
    procedure LoadSettings(const strKey: WideString); safecall;
    procedure PassThruCmd(const strCmd: WideString; nCmd: Integer; dCmd: Double; out pCmd: Byte); safecall;
    procedure SetErrorBoxDisplay(bVal: Integer); safecall;
    procedure SetPass(n: Integer); safecall;
    procedure SetSourceFramerate(dSourceFramerate: Double; out dRequiredInputFramerate: Double); safecall;
    procedure ActivateAudioVideoOutputPins(bVal: Integer); safecall;
    procedure GetAudioVideoOutputPinsActivated(out bVal: Integer); safecall;
    procedure EnableFramerateCorrection(bCorrectVideo: Integer; bCorrectAudio: Integer); safecall;
  end;

// *********************************************************************//
// DispIntf:  IStandardMpegEncoderDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {91D3D934-6DEE-42C5-A687-6F81E1162559}
// *********************************************************************//
  IStandardMpegEncoderDisp = dispinterface
    ['{91D3D934-6DEE-42C5-A687-6F81E1162559}']
    procedure GetProfile(systemsFormat: SystemsOutputFormat; Constraint: Constraint; 
                         out pProfile: IStandardMpegEncoderProfile); dispid 1610678272;
    procedure GetSelectedProfile(out pProfile: IStandardMpegEncoderProfile); dispid 1610678273;
    procedure SelectProfile(const pProfile: IStandardMpegEncoderProfile); dispid 1610678274;
    procedure SelectFormat(systemsFormat: SystemsOutputFormat; Constraint: Constraint); dispid 1610678275;
    procedure SetFilterLicenseKey(const strLicense: WideString); dispid 1610678276;
    procedure SaveSettings(const strKey: WideString); dispid 1610678277;
    procedure LoadSettings(const strKey: WideString); dispid 1610678278;
    procedure PassThruCmd(const strCmd: WideString; nCmd: Integer; dCmd: Double; out pCmd: Byte); dispid 1610678279;
    procedure SetErrorBoxDisplay(bVal: Integer); dispid 1610678280;
    procedure SetPass(n: Integer); dispid 1610678281;
    procedure SetSourceFramerate(dSourceFramerate: Double; out dRequiredInputFramerate: Double); dispid 1610678282;
    procedure ActivateAudioVideoOutputPins(bVal: Integer); dispid 1610678283;
    procedure GetAudioVideoOutputPinsActivated(out bVal: Integer); dispid 1610678284;
    procedure EnableFramerateCorrection(bCorrectVideo: Integer; bCorrectAudio: Integer); dispid 1610678285;
  end;

// *********************************************************************//
// Interface: IStandardMpegEncoderProfile
// Flags:     (320) Dual OleAutomation
// GUID:      {182EB270-5FA5-46E8-83BA-40F7205C545B}
// *********************************************************************//
  IStandardMpegEncoderProfile = interface(IUnknown)
    ['{182EB270-5FA5-46E8-83BA-40F7205C545B}']
    procedure SaveProfile(const strKey: WideString); safecall;
    procedure LoadProfile(const strKey: WideString); safecall;
    procedure GetProfileName(out strName: WideString); safecall;
    procedure SetProfileName(const strName: WideString); safecall;
    procedure SetAudioFormat(audioFormat: AudioOutputFormat); safecall;
    procedure GetAudioFormat(out audioFormat: AudioOutputFormat); safecall;
    procedure SetVideoFormat(videoFormat: VideoOutputFormat); safecall;
    procedure GetVideoFormat(out videoFormat: VideoOutputFormat); safecall;
    procedure SetSystemsFormat(systemsFormat: SystemsOutputFormat); safecall;
    procedure GetSystemsFormat(out systemsFormat: SystemsOutputFormat); safecall;
    procedure ConfigureForSystemsFormat(systemsFormat: SystemsOutputFormat; Constraint: Constraint); safecall;
    procedure SetConstraint(systemsConstraint: Constraint); safecall;
    procedure GetConstraint(out systemsConstraint: Constraint); safecall;
    procedure SetAspectRatio(aspectMode: AspectRatio); safecall;
    procedure GetAspectRatio(out pAspectMode: AspectRatio); safecall;
    procedure SetAutoSelectDimensions(bVal: Integer); safecall;
    procedure GetAutoSelectDimensions(out pbVal: Integer); safecall;
    procedure SetWidth(nWidth: Integer); safecall;
    procedure GetWidth(out nWidth: Integer); safecall;
    procedure GetHeight(out pnHeight: Integer); safecall;
    procedure SetHeight(nHeight: Integer); safecall;
    procedure SetVideoBitrate(nBitrate: Integer); safecall;
    procedure GetVideoBitrate(out nBitrate: Integer); safecall;
    procedure SetAutoSelectBitrate(bVal: Integer); safecall;
    procedure GetAutoSelectBitrate(out pbVal: Integer); safecall;
    procedure SetVideoBitrateMin(nBitrate: Integer); safecall;
    procedure GetVideoBitrateMin(out nBitrate: Integer); safecall;
    procedure SetVideoBitrateMax(nBitrate: Integer); safecall;
    procedure GetVideoBitrateMax(out nBitrate: Integer); safecall;
    procedure SetAudioBitrate(nBitrate: Integer); safecall;
    procedure GetAudioBitrate(out nBitrate: Integer); safecall;
    procedure SetAudioBitrateMin(nBitrate: Integer); safecall;
    procedure GetAudioBitrateMin(out nBitrate: Integer); safecall;
    procedure SetAudioBitrateMax(nBitrate: Integer); safecall;
    procedure GetAudioBitrateMax(out nBitrate: Integer); safecall;
    procedure SetVideoQuality(nQualityPercent: Integer); safecall;
    procedure GetVideoQuality(out nQualityPercent: Integer); safecall;
    procedure SetVideoVBRMode(vbrMode: BitrateMode); safecall;
    procedure GetVideoVBRMode(out pvbrMode: BitrateMode); safecall;
    procedure SetVideoVBVBufferSize(vbvlen: Integer); safecall;
    procedure GetVideoVBVBufferSize(out vbvlen: Integer); safecall;
    procedure SetAudioVBRMode(vbrMode: BitrateMode); safecall;
    procedure GetAudioVBRMode(out pvbrMode: BitrateMode); safecall;
    procedure Set2PassLogFile(const Path: WideString); safecall;
    procedure SetVideoQualityRange(nMin: Integer; nMax: Integer); safecall;
    procedure SetFramerate(fps: Double); safecall;
    procedure GetFramerate(out fps: Double); safecall;
    procedure SetAudioSampleRate(nSampleRate: Integer); safecall;
    procedure GetAudioSampleRate(out pnSampleRate: Integer); safecall;
    procedure SetAudioChannels(nChannelCount: Integer); safecall;
    procedure GetAudioChannels(out pnChannelCount: Integer); safecall;
    procedure SetAudioFlags(bErrorProtection: Integer; bOriginal: Integer; bCopyright: Integer; 
                            bPrivate: Integer); safecall;
    procedure SetComments(const strVal: WideString); safecall;
    procedure SetInformation(const strTitle: WideString; const strAuthor: WideString; 
                             const strCopyright: WideString); safecall;
    procedure SetEncodeMode(nValue: EncodeMode); safecall;
    procedure GetEncodeMode(out pnValue: EncodeMode); safecall;
    procedure SetBWVideo(bVal: Integer); safecall;
    procedure SetGOPSize(nGOPSize: Integer); safecall;
    procedure GetGOPSize(out nGOPSize: Integer); safecall;
    procedure SetDetectSceneChange(bVal: Integer); safecall;
    procedure GetDetectSceneChange(out nVal: Integer); safecall;
    procedure SetSceneChangeThreshold(f: Single); safecall;
    procedure SetClosedGOP(bVal: Integer); safecall;
    procedure GetClosedGOP(out nVal: Integer); safecall;
    procedure SetOutputIntervalOfSequenceHeader(nVal: Integer); safecall;
    procedure GetOutputIntervalOfSequenceHeader(var nVal: Integer); safecall;
    procedure SetGOPStructure(const strStructure: WideString); safecall;
    procedure GetGOPStructure(out pstrStructure: WideString); safecall;
    procedure SetStrictGOP(bVal: Integer); safecall;
    procedure SetProfileAndLevel(const strProfileAndLevel: WideString); safecall;
    procedure GetProfileAndLevel(out pstrProfileAndLevel: WideString); safecall;
    procedure SetMotionSearchPrecision(nVal: Integer); safecall;
    procedure GetMotionSearchPrecision(out nVal: Integer); safecall;
    procedure SetQuantBias(nIntra: Integer; nInter: Integer); safecall;
    procedure SetIDCT(n: Integer); safecall;
    procedure SetQuantFactor(fQuantFactor: Single); safecall;
    procedure GetQuantFactor(out pfQuantFactor: Single); safecall;
    procedure SetInterlaceMode(bPreProcessDeinterlace: Integer; bInterlacedOutputDCT: Integer; 
                               bInterlacedOutputME: Integer); safecall;
    procedure GetInterlaceMode(out bPreProcessDeinterlace: Integer; 
                               out bInterlacedOutputDCT: Integer; out bInterlacedOutputME: Integer); safecall;
  end;

// *********************************************************************//
// DispIntf:  IStandardMpegEncoderProfileDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {182EB270-5FA5-46E8-83BA-40F7205C545B}
// *********************************************************************//
  IStandardMpegEncoderProfileDisp = dispinterface
    ['{182EB270-5FA5-46E8-83BA-40F7205C545B}']
    procedure SaveProfile(const strKey: WideString); dispid 1610678272;
    procedure LoadProfile(const strKey: WideString); dispid 1610678273;
    procedure GetProfileName(out strName: WideString); dispid 1610678274;
    procedure SetProfileName(const strName: WideString); dispid 1610678275;
    procedure SetAudioFormat(audioFormat: AudioOutputFormat); dispid 1610678276;
    procedure GetAudioFormat(out audioFormat: AudioOutputFormat); dispid 1610678277;
    procedure SetVideoFormat(videoFormat: VideoOutputFormat); dispid 1610678278;
    procedure GetVideoFormat(out videoFormat: VideoOutputFormat); dispid 1610678279;
    procedure SetSystemsFormat(systemsFormat: SystemsOutputFormat); dispid 1610678280;
    procedure GetSystemsFormat(out systemsFormat: SystemsOutputFormat); dispid 1610678281;
    procedure ConfigureForSystemsFormat(systemsFormat: SystemsOutputFormat; Constraint: Constraint); dispid 1610678282;
    procedure SetConstraint(systemsConstraint: Constraint); dispid 1610678283;
    procedure GetConstraint(out systemsConstraint: Constraint); dispid 1610678284;
    procedure SetAspectRatio(aspectMode: AspectRatio); dispid 1610678285;
    procedure GetAspectRatio(out pAspectMode: AspectRatio); dispid 1610678286;
    procedure SetAutoSelectDimensions(bVal: Integer); dispid 1610678287;
    procedure GetAutoSelectDimensions(out pbVal: Integer); dispid 1610678288;
    procedure SetWidth(nWidth: Integer); dispid 1610678289;
    procedure GetWidth(out nWidth: Integer); dispid 1610678290;
    procedure GetHeight(out pnHeight: Integer); dispid 1610678291;
    procedure SetHeight(nHeight: Integer); dispid 1610678292;
    procedure SetVideoBitrate(nBitrate: Integer); dispid 1610678293;
    procedure GetVideoBitrate(out nBitrate: Integer); dispid 1610678294;
    procedure SetAutoSelectBitrate(bVal: Integer); dispid 1610678295;
    procedure GetAutoSelectBitrate(out pbVal: Integer); dispid 1610678296;
    procedure SetVideoBitrateMin(nBitrate: Integer); dispid 1610678297;
    procedure GetVideoBitrateMin(out nBitrate: Integer); dispid 1610678298;
    procedure SetVideoBitrateMax(nBitrate: Integer); dispid 1610678299;
    procedure GetVideoBitrateMax(out nBitrate: Integer); dispid 1610678300;
    procedure SetAudioBitrate(nBitrate: Integer); dispid 1610678301;
    procedure GetAudioBitrate(out nBitrate: Integer); dispid 1610678302;
    procedure SetAudioBitrateMin(nBitrate: Integer); dispid 1610678303;
    procedure GetAudioBitrateMin(out nBitrate: Integer); dispid 1610678304;
    procedure SetAudioBitrateMax(nBitrate: Integer); dispid 1610678305;
    procedure GetAudioBitrateMax(out nBitrate: Integer); dispid 1610678306;
    procedure SetVideoQuality(nQualityPercent: Integer); dispid 1610678307;
    procedure GetVideoQuality(out nQualityPercent: Integer); dispid 1610678308;
    procedure SetVideoVBRMode(vbrMode: BitrateMode); dispid 1610678309;
    procedure GetVideoVBRMode(out pvbrMode: BitrateMode); dispid 1610678310;
    procedure SetVideoVBVBufferSize(vbvlen: Integer); dispid 1610678311;
    procedure GetVideoVBVBufferSize(out vbvlen: Integer); dispid 1610678312;
    procedure SetAudioVBRMode(vbrMode: BitrateMode); dispid 1610678313;
    procedure GetAudioVBRMode(out pvbrMode: BitrateMode); dispid 1610678314;
    procedure Set2PassLogFile(const Path: WideString); dispid 1610678315;
    procedure SetVideoQualityRange(nMin: Integer; nMax: Integer); dispid 1610678316;
    procedure SetFramerate(fps: Double); dispid 1610678317;
    procedure GetFramerate(out fps: Double); dispid 1610678318;
    procedure SetAudioSampleRate(nSampleRate: Integer); dispid 1610678319;
    procedure GetAudioSampleRate(out pnSampleRate: Integer); dispid 1610678320;
    procedure SetAudioChannels(nChannelCount: Integer); dispid 1610678321;
    procedure GetAudioChannels(out pnChannelCount: Integer); dispid 1610678322;
    procedure SetAudioFlags(bErrorProtection: Integer; bOriginal: Integer; bCopyright: Integer; 
                            bPrivate: Integer); dispid 1610678323;
    procedure SetComments(const strVal: WideString); dispid 1610678324;
    procedure SetInformation(const strTitle: WideString; const strAuthor: WideString; 
                             const strCopyright: WideString); dispid 1610678325;
    procedure SetEncodeMode(nValue: EncodeMode); dispid 1610678326;
    procedure GetEncodeMode(out pnValue: EncodeMode); dispid 1610678327;
    procedure SetBWVideo(bVal: Integer); dispid 1610678328;
    procedure SetGOPSize(nGOPSize: Integer); dispid 1610678329;
    procedure GetGOPSize(out nGOPSize: Integer); dispid 1610678330;
    procedure SetDetectSceneChange(bVal: Integer); dispid 1610678331;
    procedure GetDetectSceneChange(out nVal: Integer); dispid 1610678332;
    procedure SetSceneChangeThreshold(f: Single); dispid 1610678333;
    procedure SetClosedGOP(bVal: Integer); dispid 1610678334;
    procedure GetClosedGOP(out nVal: Integer); dispid 1610678335;
    procedure SetOutputIntervalOfSequenceHeader(nVal: Integer); dispid 1610678336;
    procedure GetOutputIntervalOfSequenceHeader(var nVal: Integer); dispid 1610678337;
    procedure SetGOPStructure(const strStructure: WideString); dispid 1610678338;
    procedure GetGOPStructure(out pstrStructure: WideString); dispid 1610678339;
    procedure SetStrictGOP(bVal: Integer); dispid 1610678340;
    procedure SetProfileAndLevel(const strProfileAndLevel: WideString); dispid 1610678341;
    procedure GetProfileAndLevel(out pstrProfileAndLevel: WideString); dispid 1610678342;
    procedure SetMotionSearchPrecision(nVal: Integer); dispid 1610678343;
    procedure GetMotionSearchPrecision(out nVal: Integer); dispid 1610678344;
    procedure SetQuantBias(nIntra: Integer; nInter: Integer); dispid 1610678345;
    procedure SetIDCT(n: Integer); dispid 1610678346;
    procedure SetQuantFactor(fQuantFactor: Single); dispid 1610678347;
    procedure GetQuantFactor(out pfQuantFactor: Single); dispid 1610678348;
    procedure SetInterlaceMode(bPreProcessDeinterlace: Integer; bInterlacedOutputDCT: Integer; 
                               bInterlacedOutputME: Integer); dispid 1610678349;
    procedure GetInterlaceMode(out bPreProcessDeinterlace: Integer; 
                               out bInterlacedOutputDCT: Integer; out bInterlacedOutputME: Integer); dispid 1610678350;
  end;

// *********************************************************************//
// Interface: IStandardMpegEncoderStats
// Flags:     (320) Dual OleAutomation
// GUID:      {C9510218-F457-4D51-8389-7386E6EDD0EF}
// *********************************************************************//
  IStandardMpegEncoderStats = interface(IUnknown)
    ['{C9510218-F457-4D51-8389-7386E6EDD0EF}']
    procedure GetFramesEncoded(out lFramesEncoded: Integer); safecall;
    procedure GetVideoFramesDropped(out lFramesDropped: Integer); safecall;
    procedure GetAudioTimeCorrected(out dTimeCorrected: Double); safecall;
    procedure GetWrittenBytes(out lBytesWritten: Integer); safecall;
    procedure GetStatusString(out strValue: WideString); safecall;
  end;

// *********************************************************************//
// DispIntf:  IStandardMpegEncoderStatsDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {C9510218-F457-4D51-8389-7386E6EDD0EF}
// *********************************************************************//
  IStandardMpegEncoderStatsDisp = dispinterface
    ['{C9510218-F457-4D51-8389-7386E6EDD0EF}']
    procedure GetFramesEncoded(out lFramesEncoded: Integer); dispid 1610678272;
    procedure GetVideoFramesDropped(out lFramesDropped: Integer); dispid 1610678273;
    procedure GetAudioTimeCorrected(out dTimeCorrected: Double); dispid 1610678274;
    procedure GetWrittenBytes(out lBytesWritten: Integer); dispid 1610678275;
    procedure GetStatusString(out strValue: WideString); dispid 1610678276;
  end;

// *********************************************************************//
// Interface: IStandardMpegMultiplexerProfile
// Flags:     (320) Dual OleAutomation
// GUID:      {7E772181-B7ED-4D9D-A364-0E8771AAFF70}
// *********************************************************************//
  IStandardMpegMultiplexerProfile = interface(IUnknown)
    ['{7E772181-B7ED-4D9D-A364-0E8771AAFF70}']
    procedure SetDeleteElementaryStreams(bDelete: Integer); safecall;
    procedure GetDeleteElementaryStreams(out bDelete: Integer); safecall;
    procedure SetMultiplexRate(nRate: Integer); safecall;
    procedure GetMultiplexRate(out pnMux: Integer); safecall;
    procedure SetMultiplexPacketSize(nSize: Integer); safecall;
    procedure GetMultiplexPacketSize(out pnSize: Integer); safecall;
    procedure SetMultiplexPreload(fPreload: Single); safecall;
    procedure GetMultiplexPreload(out pfPreload: Single); safecall;
    procedure SetMultiplexMaxDelay(fMaxDelay: Single); safecall;
    procedure SetMultiplexStreams(bMux: Integer); safecall;
    procedure GetMultiplexStreams(out bMux: Integer); safecall;
    procedure SetMultiplexFormat(format: SystemsOutputFormat); safecall;
    procedure GetMultiplexFormat(out format: SystemsOutputFormat); safecall;
    procedure AddMultiplexFile(const strPath: WideString); safecall;
    procedure SetOnFlyMultiplex(bOnFlyMultiplex: Integer); safecall;
    procedure GetOnFlyMultiplex(out pbOnFlyMultiplex: Integer); safecall;
    procedure SetMultiplexFrameBalance(bVal: Integer); safecall;
    procedure SetMultiplexOnStop(bVal: Integer); safecall;
    procedure GetMultiplexProgress(out dProgress: Double); safecall;
  end;

// *********************************************************************//
// DispIntf:  IStandardMpegMultiplexerProfileDisp
// Flags:     (320) Dual OleAutomation
// GUID:      {7E772181-B7ED-4D9D-A364-0E8771AAFF70}
// *********************************************************************//
  IStandardMpegMultiplexerProfileDisp = dispinterface
    ['{7E772181-B7ED-4D9D-A364-0E8771AAFF70}']
    procedure SetDeleteElementaryStreams(bDelete: Integer); dispid 1610678272;
    procedure GetDeleteElementaryStreams(out bDelete: Integer); dispid 1610678273;
    procedure SetMultiplexRate(nRate: Integer); dispid 1610678274;
    procedure GetMultiplexRate(out pnMux: Integer); dispid 1610678275;
    procedure SetMultiplexPacketSize(nSize: Integer); dispid 1610678276;
    procedure GetMultiplexPacketSize(out pnSize: Integer); dispid 1610678277;
    procedure SetMultiplexPreload(fPreload: Single); dispid 1610678278;
    procedure GetMultiplexPreload(out pfPreload: Single); dispid 1610678279;
    procedure SetMultiplexMaxDelay(fMaxDelay: Single); dispid 1610678280;
    procedure SetMultiplexStreams(bMux: Integer); dispid 1610678281;
    procedure GetMultiplexStreams(out bMux: Integer); dispid 1610678282;
    procedure SetMultiplexFormat(format: SystemsOutputFormat); dispid 1610678283;
    procedure GetMultiplexFormat(out format: SystemsOutputFormat); dispid 1610678284;
    procedure AddMultiplexFile(const strPath: WideString); dispid 1610678285;
    procedure SetOnFlyMultiplex(bOnFlyMultiplex: Integer); dispid 1610678286;
    procedure GetOnFlyMultiplex(out pbOnFlyMultiplex: Integer); dispid 1610678287;
    procedure SetMultiplexFrameBalance(bVal: Integer); dispid 1610678288;
    procedure SetMultiplexOnStop(bVal: Integer); dispid 1610678289;
    procedure GetMultiplexProgress(out dProgress: Double); dispid 1610678290;
  end;

// *********************************************************************//
// Interface: IPropertyPage
// Flags:     (0)
// GUID:      {B196B28D-BAB4-101A-B69C-00AA00341D07}
// *********************************************************************//
  IPropertyPage = interface(IUnknown)
    ['{B196B28D-BAB4-101A-B69C-00AA00341D07}']
    function SetPageSite(const pPageSite: IPropertyPageSite): HResult; stdcall;
    function Activate(var hWndParent: _RemotableHandle; var pRect: tagRECT; bModal: Integer): HResult; stdcall;
    function Deactivate: HResult; stdcall;
    function GetPageInfo(out pPageInfo: tagPROPPAGEINFO): HResult; stdcall;
    function SetObjects(cObjects: LongWord; var ppUnk: IUnknown): HResult; stdcall;
    function Show(nCmdShow: SYSUINT): HResult; stdcall;
    function Move(var pRect: tagRECT): HResult; stdcall;
    function IsPageDirty: HResult; stdcall;
    function Apply: HResult; stdcall;
    function Help(pszHelpDir: PWideChar): HResult; stdcall;
    function TranslateAccelerator(var pMsg: tagMSG): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IPropertyPageSite
// Flags:     (0)
// GUID:      {B196B28C-BAB4-101A-B69C-00AA00341D07}
// *********************************************************************//
  IPropertyPageSite = interface(IUnknown)
    ['{B196B28C-BAB4-101A-B69C-00AA00341D07}']
    function OnStatusChange(dwFlags: LongWord): HResult; stdcall;
    function GetLocaleID(out pLocaleID: LongWord): HResult; stdcall;
    function GetPageContainer(out ppUnk: IUnknown): HResult; stdcall;
    function TranslateAccelerator(var pMsg: tagMSG): HResult; stdcall;
  end;

// *********************************************************************//
// The Class CoStandardMpegEncoder provides a Create and CreateRemote method to          
// create instances of the default interface IUnknown exposed by              
// the CoClass StandardMpegEncoder. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoStandardMpegEncoder = class
    class function Create: IUnknown;
    class function CreateRemote(const MachineName: string): IUnknown;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TStandardMpegEncoder
// Help String      : Standard MPEG Encoder Class
// Default Interface: IUnknown
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TStandardMpegEncoderProperties= class;
{$ENDIF}
  TStandardMpegEncoder = class(TOleServer)
  private
    FIntf:        IUnknown;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TStandardMpegEncoderProperties;
    function      GetServerProperties: TStandardMpegEncoderProperties;
{$ENDIF}
    function      GetDefaultInterface: IUnknown;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IUnknown);
    procedure Disconnect; override;
    function QueryInterface(var riid: TGUID; out ppvObject: Pointer): HResult;
    function AddRef: LongWord;
    function Release: LongWord;
    property DefaultInterface: IUnknown read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TStandardMpegEncoderProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TStandardMpegEncoder
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TStandardMpegEncoderProperties = class(TPersistent)
  private
    FServer:    TStandardMpegEncoder;
    function    GetDefaultInterface: IUnknown;
    constructor Create(AServer: TStandardMpegEncoder);
  protected
  public
    property DefaultInterface: IUnknown read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoStandardMpegEncoderStats provides a Create and CreateRemote method to          
// create instances of the default interface IStandardMpegEncoderStats exposed by              
// the CoClass StandardMpegEncoderStats. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoStandardMpegEncoderStats = class
    class function Create: IStandardMpegEncoderStats;
    class function CreateRemote(const MachineName: string): IStandardMpegEncoderStats;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TStandardMpegEncoderStats
// Help String      : Standard MPEG Encoder Stats Class
// Default Interface: IStandardMpegEncoderStats
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TStandardMpegEncoderStatsProperties= class;
{$ENDIF}
  TStandardMpegEncoderStats = class(TOleServer)
  private
    FIntf:        IStandardMpegEncoderStats;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TStandardMpegEncoderStatsProperties;
    function      GetServerProperties: TStandardMpegEncoderStatsProperties;
{$ENDIF}
    function      GetDefaultInterface: IStandardMpegEncoderStats;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IStandardMpegEncoderStats);
    procedure Disconnect; override;
    procedure GetFramesEncoded(out lFramesEncoded: Integer);
    procedure GetVideoFramesDropped(out lFramesDropped: Integer);
    procedure GetAudioTimeCorrected(out dTimeCorrected: Double);
    procedure GetWrittenBytes(out lBytesWritten: Integer);
    procedure GetStatusString(out strValue: WideString);
    property DefaultInterface: IStandardMpegEncoderStats read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TStandardMpegEncoderStatsProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TStandardMpegEncoderStats
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TStandardMpegEncoderStatsProperties = class(TPersistent)
  private
    FServer:    TStandardMpegEncoderStats;
    function    GetDefaultInterface: IStandardMpegEncoderStats;
    constructor Create(AServer: TStandardMpegEncoderStats);
  protected
  public
    property DefaultInterface: IStandardMpegEncoderStats read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoStandardMpegEncoderProfile provides a Create and CreateRemote method to          
// create instances of the default interface IStandardMpegEncoderProfile exposed by              
// the CoClass StandardMpegEncoderProfile. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoStandardMpegEncoderProfile = class
    class function Create: IStandardMpegEncoderProfile;
    class function CreateRemote(const MachineName: string): IStandardMpegEncoderProfile;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TStandardMpegEncoderProfile
// Help String      : Standard MPEG Encoder Profile Class
// Default Interface: IStandardMpegEncoderProfile
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TStandardMpegEncoderProfileProperties= class;
{$ENDIF}
  TStandardMpegEncoderProfile = class(TOleServer)
  private
    FIntf:        IStandardMpegEncoderProfile;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TStandardMpegEncoderProfileProperties;
    function      GetServerProperties: TStandardMpegEncoderProfileProperties;
{$ENDIF}
    function      GetDefaultInterface: IStandardMpegEncoderProfile;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IStandardMpegEncoderProfile);
    procedure Disconnect; override;
    procedure SaveProfile(const strKey: WideString);
    procedure LoadProfile(const strKey: WideString);
    procedure GetProfileName(out strName: WideString);
    procedure SetProfileName(const strName: WideString);
    procedure SetAudioFormat(audioFormat: AudioOutputFormat);
    procedure GetAudioFormat(out audioFormat: AudioOutputFormat);
    procedure SetVideoFormat(videoFormat: VideoOutputFormat);
    procedure GetVideoFormat(out videoFormat: VideoOutputFormat);
    procedure SetSystemsFormat(systemsFormat: SystemsOutputFormat);
    procedure GetSystemsFormat(out systemsFormat: SystemsOutputFormat);
    procedure ConfigureForSystemsFormat(systemsFormat: SystemsOutputFormat; Constraint: Constraint);
    procedure SetConstraint(systemsConstraint: Constraint);
    procedure GetConstraint(out systemsConstraint: Constraint);
    procedure SetAspectRatio(aspectMode: AspectRatio);
    procedure GetAspectRatio(out pAspectMode: AspectRatio);
    procedure SetAutoSelectDimensions(bVal: Integer);
    procedure GetAutoSelectDimensions(out pbVal: Integer);
    procedure SetWidth(nWidth: Integer);
    procedure GetWidth(out nWidth: Integer);
    procedure GetHeight(out pnHeight: Integer);
    procedure SetHeight(nHeight: Integer);
    procedure SetVideoBitrate(nBitrate: Integer);
    procedure GetVideoBitrate(out nBitrate: Integer);
    procedure SetAutoSelectBitrate(bVal: Integer);
    procedure GetAutoSelectBitrate(out pbVal: Integer);
    procedure SetVideoBitrateMin(nBitrate: Integer);
    procedure GetVideoBitrateMin(out nBitrate: Integer);
    procedure SetVideoBitrateMax(nBitrate: Integer);
    procedure GetVideoBitrateMax(out nBitrate: Integer);
    procedure SetAudioBitrate(nBitrate: Integer);
    procedure GetAudioBitrate(out nBitrate: Integer);
    procedure SetAudioBitrateMin(nBitrate: Integer);
    procedure GetAudioBitrateMin(out nBitrate: Integer);
    procedure SetAudioBitrateMax(nBitrate: Integer);
    procedure GetAudioBitrateMax(out nBitrate: Integer);
    procedure SetVideoQuality(nQualityPercent: Integer);
    procedure GetVideoQuality(out nQualityPercent: Integer);
    procedure SetVideoVBRMode(vbrMode: BitrateMode);
    procedure GetVideoVBRMode(out pvbrMode: BitrateMode);
    procedure SetVideoVBVBufferSize(vbvlen: Integer);
    procedure GetVideoVBVBufferSize(out vbvlen: Integer);
    procedure SetAudioVBRMode(vbrMode: BitrateMode);
    procedure GetAudioVBRMode(out pvbrMode: BitrateMode);
    procedure Set2PassLogFile(const Path: WideString);
    procedure SetVideoQualityRange(nMin: Integer; nMax: Integer);
    procedure SetFramerate(fps: Double);
    procedure GetFramerate(out fps: Double);
    procedure SetAudioSampleRate(nSampleRate: Integer);
    procedure GetAudioSampleRate(out pnSampleRate: Integer);
    procedure SetAudioChannels(nChannelCount: Integer);
    procedure GetAudioChannels(out pnChannelCount: Integer);
    procedure SetAudioFlags(bErrorProtection: Integer; bOriginal: Integer; bCopyright: Integer; 
                            bPrivate: Integer);
    procedure SetComments(const strVal: WideString);
    procedure SetInformation(const strTitle: WideString; const strAuthor: WideString; 
                             const strCopyright: WideString);
    procedure SetEncodeMode(nValue: EncodeMode);
    procedure GetEncodeMode(out pnValue: EncodeMode);
    procedure SetBWVideo(bVal: Integer);
    procedure SetGOPSize(nGOPSize: Integer);
    procedure GetGOPSize(out nGOPSize: Integer);
    procedure SetDetectSceneChange(bVal: Integer);
    procedure GetDetectSceneChange(out nVal: Integer);
    procedure SetSceneChangeThreshold(f: Single);
    procedure SetClosedGOP(bVal: Integer);
    procedure GetClosedGOP(out nVal: Integer);
    procedure SetOutputIntervalOfSequenceHeader(nVal: Integer);
    procedure GetOutputIntervalOfSequenceHeader(var nVal: Integer);
    procedure SetGOPStructure(const strStructure: WideString);
    procedure GetGOPStructure(out pstrStructure: WideString);
    procedure SetStrictGOP(bVal: Integer);
    procedure SetProfileAndLevel(const strProfileAndLevel: WideString);
    procedure GetProfileAndLevel(out pstrProfileAndLevel: WideString);
    procedure SetMotionSearchPrecision(nVal: Integer);
    procedure GetMotionSearchPrecision(out nVal: Integer);
    procedure SetQuantBias(nIntra: Integer; nInter: Integer);
    procedure SetIDCT(n: Integer);
    procedure SetQuantFactor(fQuantFactor: Single);
    procedure GetQuantFactor(out pfQuantFactor: Single);
    procedure SetInterlaceMode(bPreProcessDeinterlace: Integer; bInterlacedOutputDCT: Integer; 
                               bInterlacedOutputME: Integer);
    procedure GetInterlaceMode(out bPreProcessDeinterlace: Integer; 
                               out bInterlacedOutputDCT: Integer; out bInterlacedOutputME: Integer);
    property DefaultInterface: IStandardMpegEncoderProfile read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TStandardMpegEncoderProfileProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TStandardMpegEncoderProfile
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TStandardMpegEncoderProfileProperties = class(TPersistent)
  private
    FServer:    TStandardMpegEncoderProfile;
    function    GetDefaultInterface: IStandardMpegEncoderProfile;
    constructor Create(AServer: TStandardMpegEncoderProfile);
  protected
  public
    property DefaultInterface: IStandardMpegEncoderProfile read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoStandardMpegMultiplexerProfile provides a Create and CreateRemote method to          
// create instances of the default interface IStandardMpegMultiplexerProfile exposed by              
// the CoClass StandardMpegMultiplexerProfile. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoStandardMpegMultiplexerProfile = class
    class function Create: IStandardMpegMultiplexerProfile;
    class function CreateRemote(const MachineName: string): IStandardMpegMultiplexerProfile;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TStandardMpegMultiplexerProfile
// Help String      : Standard MPEG Multiplexer Profile Class
// Default Interface: IStandardMpegMultiplexerProfile
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TStandardMpegMultiplexerProfileProperties= class;
{$ENDIF}
  TStandardMpegMultiplexerProfile = class(TOleServer)
  private
    FIntf:        IStandardMpegMultiplexerProfile;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TStandardMpegMultiplexerProfileProperties;
    function      GetServerProperties: TStandardMpegMultiplexerProfileProperties;
{$ENDIF}
    function      GetDefaultInterface: IStandardMpegMultiplexerProfile;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IStandardMpegMultiplexerProfile);
    procedure Disconnect; override;
    procedure SetDeleteElementaryStreams(bDelete: Integer);
    procedure GetDeleteElementaryStreams(out bDelete: Integer);
    procedure SetMultiplexRate(nRate: Integer);
    procedure GetMultiplexRate(out pnMux: Integer);
    procedure SetMultiplexPacketSize(nSize: Integer);
    procedure GetMultiplexPacketSize(out pnSize: Integer);
    procedure SetMultiplexPreload(fPreload: Single);
    procedure GetMultiplexPreload(out pfPreload: Single);
    procedure SetMultiplexMaxDelay(fMaxDelay: Single);
    procedure SetMultiplexStreams(bMux: Integer);
    procedure GetMultiplexStreams(out bMux: Integer);
    procedure SetMultiplexFormat(format: SystemsOutputFormat);
    procedure GetMultiplexFormat(out format: SystemsOutputFormat);
    procedure AddMultiplexFile(const strPath: WideString);
    procedure SetOnFlyMultiplex(bOnFlyMultiplex: Integer);
    procedure GetOnFlyMultiplex(out pbOnFlyMultiplex: Integer);
    procedure SetMultiplexFrameBalance(bVal: Integer);
    procedure SetMultiplexOnStop(bVal: Integer);
    procedure GetMultiplexProgress(out dProgress: Double);
    property DefaultInterface: IStandardMpegMultiplexerProfile read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TStandardMpegMultiplexerProfileProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TStandardMpegMultiplexerProfile
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TStandardMpegMultiplexerProfileProperties = class(TPersistent)
  private
    FServer:    TStandardMpegMultiplexerProfile;
    function    GetDefaultInterface: IStandardMpegMultiplexerProfile;
    constructor Create(AServer: TStandardMpegMultiplexerProfile);
  protected
  public
    property DefaultInterface: IStandardMpegMultiplexerProfile read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoStandardMpegEncoderGeneralProps provides a Create and CreateRemote method to          
// create instances of the default interface IPropertyPage exposed by              
// the CoClass StandardMpegEncoderGeneralProps. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoStandardMpegEncoderGeneralProps = class
    class function Create: IPropertyPage;
    class function CreateRemote(const MachineName: string): IPropertyPage;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TStandardMpegEncoderGeneralProps
// Help String      : Standard MPEG Encoder General Properties Page
// Default Interface: IPropertyPage
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TStandardMpegEncoderGeneralPropsProperties= class;
{$ENDIF}
  TStandardMpegEncoderGeneralProps = class(TOleServer)
  private
    FIntf:        IPropertyPage;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TStandardMpegEncoderGeneralPropsProperties;
    function      GetServerProperties: TStandardMpegEncoderGeneralPropsProperties;
{$ENDIF}
    function      GetDefaultInterface: IPropertyPage;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IPropertyPage);
    procedure Disconnect; override;
    function SetPageSite(const pPageSite: IPropertyPageSite): HResult;
    function Activate(var hWndParent: _RemotableHandle; var pRect: tagRECT; bModal: Integer): HResult;
    function Deactivate: HResult;
    function GetPageInfo(out pPageInfo: tagPROPPAGEINFO): HResult;
    function SetObjects(cObjects: LongWord; var ppUnk: IUnknown): HResult;
    function Show(nCmdShow: SYSUINT): HResult;
    function Move(var pRect: tagRECT): HResult;
    function IsPageDirty: HResult;
    function Apply: HResult;
    function Help(pszHelpDir: PWideChar): HResult;
    function TranslateAccelerator(var pMsg: tagMSG): HResult;
    property DefaultInterface: IPropertyPage read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TStandardMpegEncoderGeneralPropsProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TStandardMpegEncoderGeneralProps
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TStandardMpegEncoderGeneralPropsProperties = class(TPersistent)
  private
    FServer:    TStandardMpegEncoderGeneralProps;
    function    GetDefaultInterface: IPropertyPage;
    constructor Create(AServer: TStandardMpegEncoderGeneralProps);
  protected
  public
    property DefaultInterface: IPropertyPage read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoStandardMpegEncoderVideoProps provides a Create and CreateRemote method to          
// create instances of the default interface IPropertyPage exposed by              
// the CoClass StandardMpegEncoderVideoProps. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoStandardMpegEncoderVideoProps = class
    class function Create: IPropertyPage;
    class function CreateRemote(const MachineName: string): IPropertyPage;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TStandardMpegEncoderVideoProps
// Help String      : Standard MPEG Encoder Video Properties Page
// Default Interface: IPropertyPage
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TStandardMpegEncoderVideoPropsProperties= class;
{$ENDIF}
  TStandardMpegEncoderVideoProps = class(TOleServer)
  private
    FIntf:        IPropertyPage;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TStandardMpegEncoderVideoPropsProperties;
    function      GetServerProperties: TStandardMpegEncoderVideoPropsProperties;
{$ENDIF}
    function      GetDefaultInterface: IPropertyPage;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IPropertyPage);
    procedure Disconnect; override;
    function SetPageSite(const pPageSite: IPropertyPageSite): HResult;
    function Activate(var hWndParent: _RemotableHandle; var pRect: tagRECT; bModal: Integer): HResult;
    function Deactivate: HResult;
    function GetPageInfo(out pPageInfo: tagPROPPAGEINFO): HResult;
    function SetObjects(cObjects: LongWord; var ppUnk: IUnknown): HResult;
    function Show(nCmdShow: SYSUINT): HResult;
    function Move(var pRect: tagRECT): HResult;
    function IsPageDirty: HResult;
    function Apply: HResult;
    function Help(pszHelpDir: PWideChar): HResult;
    function TranslateAccelerator(var pMsg: tagMSG): HResult;
    property DefaultInterface: IPropertyPage read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TStandardMpegEncoderVideoPropsProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TStandardMpegEncoderVideoProps
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TStandardMpegEncoderVideoPropsProperties = class(TPersistent)
  private
    FServer:    TStandardMpegEncoderVideoProps;
    function    GetDefaultInterface: IPropertyPage;
    constructor Create(AServer: TStandardMpegEncoderVideoProps);
  protected
  public
    property DefaultInterface: IPropertyPage read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoStandardMpegEncoderAudioProps provides a Create and CreateRemote method to          
// create instances of the default interface IPropertyPage exposed by              
// the CoClass StandardMpegEncoderAudioProps. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoStandardMpegEncoderAudioProps = class
    class function Create: IPropertyPage;
    class function CreateRemote(const MachineName: string): IPropertyPage;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TStandardMpegEncoderAudioProps
// Help String      : Standard MPEG Encoder Audio Properties Page
// Default Interface: IPropertyPage
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TStandardMpegEncoderAudioPropsProperties= class;
{$ENDIF}
  TStandardMpegEncoderAudioProps = class(TOleServer)
  private
    FIntf:        IPropertyPage;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TStandardMpegEncoderAudioPropsProperties;
    function      GetServerProperties: TStandardMpegEncoderAudioPropsProperties;
{$ENDIF}
    function      GetDefaultInterface: IPropertyPage;
  protected
    procedure InitServerData; override;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IPropertyPage);
    procedure Disconnect; override;
    function SetPageSite(const pPageSite: IPropertyPageSite): HResult;
    function Activate(var hWndParent: _RemotableHandle; var pRect: tagRECT; bModal: Integer): HResult;
    function Deactivate: HResult;
    function GetPageInfo(out pPageInfo: tagPROPPAGEINFO): HResult;
    function SetObjects(cObjects: LongWord; var ppUnk: IUnknown): HResult;
    function Show(nCmdShow: SYSUINT): HResult;
    function Move(var pRect: tagRECT): HResult;
    function IsPageDirty: HResult;
    function Apply: HResult;
    function Help(pszHelpDir: PWideChar): HResult;
    function TranslateAccelerator(var pMsg: tagMSG): HResult;
    property DefaultInterface: IPropertyPage read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TStandardMpegEncoderAudioPropsProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TStandardMpegEncoderAudioProps
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TStandardMpegEncoderAudioPropsProperties = class(TPersistent)
  private
    FServer:    TStandardMpegEncoderAudioProps;
    function    GetDefaultInterface: IPropertyPage;
    constructor Create(AServer: TStandardMpegEncoderAudioProps);
  protected
  public
    property DefaultInterface: IPropertyPage read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

implementation

uses ComObj;

class function CoStandardMpegEncoder.Create: IUnknown;
begin
  Result := CreateComObject(CLASS_StandardMpegEncoder) as IUnknown;
end;

class function CoStandardMpegEncoder.CreateRemote(const MachineName: string): IUnknown;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_StandardMpegEncoder) as IUnknown;
end;

procedure TStandardMpegEncoder.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{CFD87339-C61F-46CA-B6A1-F87D6B96243E}';
    IntfIID:   '{00000000-0000-0000-C000-000000000046}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TStandardMpegEncoder.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IUnknown;
  end;
end;

procedure TStandardMpegEncoder.ConnectTo(svrIntf: IUnknown);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TStandardMpegEncoder.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TStandardMpegEncoder.GetDefaultInterface: IUnknown;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TStandardMpegEncoder.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TStandardMpegEncoderProperties.Create(Self);
{$ENDIF}
end;

destructor TStandardMpegEncoder.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TStandardMpegEncoder.GetServerProperties: TStandardMpegEncoderProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TStandardMpegEncoder.QueryInterface(var riid: TGUID; out ppvObject: Pointer): HResult;
begin
  Result := DefaultInterface.QueryInterface(riid, ppvObject);
end;

function TStandardMpegEncoder.AddRef: LongWord;
begin
  Result := DefaultInterface._AddRef;
end;

function TStandardMpegEncoder.Release: LongWord;
begin
  Result := DefaultInterface._Release;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TStandardMpegEncoderProperties.Create(AServer: TStandardMpegEncoder);
begin
  inherited Create;
  FServer := AServer;
end;

function TStandardMpegEncoderProperties.GetDefaultInterface: IUnknown;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

class function CoStandardMpegEncoderStats.Create: IStandardMpegEncoderStats;
begin
  Result := CreateComObject(CLASS_StandardMpegEncoderStats) as IStandardMpegEncoderStats;
end;

class function CoStandardMpegEncoderStats.CreateRemote(const MachineName: string): IStandardMpegEncoderStats;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_StandardMpegEncoderStats) as IStandardMpegEncoderStats;
end;

procedure TStandardMpegEncoderStats.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{1C356305-4D1C-45E1-AA93-1AE16C7DE429}';
    IntfIID:   '{C9510218-F457-4D51-8389-7386E6EDD0EF}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TStandardMpegEncoderStats.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IStandardMpegEncoderStats;
  end;
end;

procedure TStandardMpegEncoderStats.ConnectTo(svrIntf: IStandardMpegEncoderStats);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TStandardMpegEncoderStats.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TStandardMpegEncoderStats.GetDefaultInterface: IStandardMpegEncoderStats;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TStandardMpegEncoderStats.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TStandardMpegEncoderStatsProperties.Create(Self);
{$ENDIF}
end;

destructor TStandardMpegEncoderStats.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TStandardMpegEncoderStats.GetServerProperties: TStandardMpegEncoderStatsProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TStandardMpegEncoderStats.GetFramesEncoded(out lFramesEncoded: Integer);
begin
  DefaultInterface.GetFramesEncoded(lFramesEncoded);
end;

procedure TStandardMpegEncoderStats.GetVideoFramesDropped(out lFramesDropped: Integer);
begin
  DefaultInterface.GetVideoFramesDropped(lFramesDropped);
end;

procedure TStandardMpegEncoderStats.GetAudioTimeCorrected(out dTimeCorrected: Double);
begin
  DefaultInterface.GetAudioTimeCorrected(dTimeCorrected);
end;

procedure TStandardMpegEncoderStats.GetWrittenBytes(out lBytesWritten: Integer);
begin
  DefaultInterface.GetWrittenBytes(lBytesWritten);
end;

procedure TStandardMpegEncoderStats.GetStatusString(out strValue: WideString);
begin
  DefaultInterface.GetStatusString(strValue);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TStandardMpegEncoderStatsProperties.Create(AServer: TStandardMpegEncoderStats);
begin
  inherited Create;
  FServer := AServer;
end;

function TStandardMpegEncoderStatsProperties.GetDefaultInterface: IStandardMpegEncoderStats;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

class function CoStandardMpegEncoderProfile.Create: IStandardMpegEncoderProfile;
begin
  Result := CreateComObject(CLASS_StandardMpegEncoderProfile) as IStandardMpegEncoderProfile;
end;

class function CoStandardMpegEncoderProfile.CreateRemote(const MachineName: string): IStandardMpegEncoderProfile;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_StandardMpegEncoderProfile) as IStandardMpegEncoderProfile;
end;

procedure TStandardMpegEncoderProfile.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{D4D68F8A-B665-41D4-94D1-E8843001E346}';
    IntfIID:   '{182EB270-5FA5-46E8-83BA-40F7205C545B}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TStandardMpegEncoderProfile.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IStandardMpegEncoderProfile;
  end;
end;

procedure TStandardMpegEncoderProfile.ConnectTo(svrIntf: IStandardMpegEncoderProfile);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TStandardMpegEncoderProfile.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TStandardMpegEncoderProfile.GetDefaultInterface: IStandardMpegEncoderProfile;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TStandardMpegEncoderProfile.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TStandardMpegEncoderProfileProperties.Create(Self);
{$ENDIF}
end;

destructor TStandardMpegEncoderProfile.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TStandardMpegEncoderProfile.GetServerProperties: TStandardMpegEncoderProfileProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TStandardMpegEncoderProfile.SaveProfile(const strKey: WideString);
begin
  DefaultInterface.SaveProfile(strKey);
end;

procedure TStandardMpegEncoderProfile.LoadProfile(const strKey: WideString);
begin
  DefaultInterface.LoadProfile(strKey);
end;

procedure TStandardMpegEncoderProfile.GetProfileName(out strName: WideString);
begin
  DefaultInterface.GetProfileName(strName);
end;

procedure TStandardMpegEncoderProfile.SetProfileName(const strName: WideString);
begin
  DefaultInterface.SetProfileName(strName);
end;

procedure TStandardMpegEncoderProfile.SetAudioFormat(audioFormat: AudioOutputFormat);
begin
  DefaultInterface.SetAudioFormat(audioFormat);
end;

procedure TStandardMpegEncoderProfile.GetAudioFormat(out audioFormat: AudioOutputFormat);
begin
  DefaultInterface.GetAudioFormat(audioFormat);
end;

procedure TStandardMpegEncoderProfile.SetVideoFormat(videoFormat: VideoOutputFormat);
begin
  DefaultInterface.SetVideoFormat(videoFormat);
end;

procedure TStandardMpegEncoderProfile.GetVideoFormat(out videoFormat: VideoOutputFormat);
begin
  DefaultInterface.GetVideoFormat(videoFormat);
end;

procedure TStandardMpegEncoderProfile.SetSystemsFormat(systemsFormat: SystemsOutputFormat);
begin
  DefaultInterface.SetSystemsFormat(systemsFormat);
end;

procedure TStandardMpegEncoderProfile.GetSystemsFormat(out systemsFormat: SystemsOutputFormat);
begin
  DefaultInterface.GetSystemsFormat(systemsFormat);
end;

procedure TStandardMpegEncoderProfile.ConfigureForSystemsFormat(systemsFormat: SystemsOutputFormat; 
                                                                Constraint: Constraint);
begin
  DefaultInterface.ConfigureForSystemsFormat(systemsFormat, Constraint);
end;

procedure TStandardMpegEncoderProfile.SetConstraint(systemsConstraint: Constraint);
begin
  DefaultInterface.SetConstraint(systemsConstraint);
end;

procedure TStandardMpegEncoderProfile.GetConstraint(out systemsConstraint: Constraint);
begin
  DefaultInterface.GetConstraint(systemsConstraint);
end;

procedure TStandardMpegEncoderProfile.SetAspectRatio(aspectMode: AspectRatio);
begin
  DefaultInterface.SetAspectRatio(aspectMode);
end;

procedure TStandardMpegEncoderProfile.GetAspectRatio(out pAspectMode: AspectRatio);
begin
  DefaultInterface.GetAspectRatio(pAspectMode);
end;

procedure TStandardMpegEncoderProfile.SetAutoSelectDimensions(bVal: Integer);
begin
  DefaultInterface.SetAutoSelectDimensions(bVal);
end;

procedure TStandardMpegEncoderProfile.GetAutoSelectDimensions(out pbVal: Integer);
begin
  DefaultInterface.GetAutoSelectDimensions(pbVal);
end;

procedure TStandardMpegEncoderProfile.SetWidth(nWidth: Integer);
begin
  DefaultInterface.SetWidth(nWidth);
end;

procedure TStandardMpegEncoderProfile.GetWidth(out nWidth: Integer);
begin
  DefaultInterface.GetWidth(nWidth);
end;

procedure TStandardMpegEncoderProfile.GetHeight(out pnHeight: Integer);
begin
  DefaultInterface.GetHeight(pnHeight);
end;

procedure TStandardMpegEncoderProfile.SetHeight(nHeight: Integer);
begin
  DefaultInterface.SetHeight(nHeight);
end;

procedure TStandardMpegEncoderProfile.SetVideoBitrate(nBitrate: Integer);
begin
  DefaultInterface.SetVideoBitrate(nBitrate);
end;

procedure TStandardMpegEncoderProfile.GetVideoBitrate(out nBitrate: Integer);
begin
  DefaultInterface.GetVideoBitrate(nBitrate);
end;

procedure TStandardMpegEncoderProfile.SetAutoSelectBitrate(bVal: Integer);
begin
  DefaultInterface.SetAutoSelectBitrate(bVal);
end;

procedure TStandardMpegEncoderProfile.GetAutoSelectBitrate(out pbVal: Integer);
begin
  DefaultInterface.GetAutoSelectBitrate(pbVal);
end;

procedure TStandardMpegEncoderProfile.SetVideoBitrateMin(nBitrate: Integer);
begin
  DefaultInterface.SetVideoBitrateMin(nBitrate);
end;

procedure TStandardMpegEncoderProfile.GetVideoBitrateMin(out nBitrate: Integer);
begin
  DefaultInterface.GetVideoBitrateMin(nBitrate);
end;

procedure TStandardMpegEncoderProfile.SetVideoBitrateMax(nBitrate: Integer);
begin
  DefaultInterface.SetVideoBitrateMax(nBitrate);
end;

procedure TStandardMpegEncoderProfile.GetVideoBitrateMax(out nBitrate: Integer);
begin
  DefaultInterface.GetVideoBitrateMax(nBitrate);
end;

procedure TStandardMpegEncoderProfile.SetAudioBitrate(nBitrate: Integer);
begin
  DefaultInterface.SetAudioBitrate(nBitrate);
end;

procedure TStandardMpegEncoderProfile.GetAudioBitrate(out nBitrate: Integer);
begin
  DefaultInterface.GetAudioBitrate(nBitrate);
end;

procedure TStandardMpegEncoderProfile.SetAudioBitrateMin(nBitrate: Integer);
begin
  DefaultInterface.SetAudioBitrateMin(nBitrate);
end;

procedure TStandardMpegEncoderProfile.GetAudioBitrateMin(out nBitrate: Integer);
begin
  DefaultInterface.GetAudioBitrateMin(nBitrate);
end;

procedure TStandardMpegEncoderProfile.SetAudioBitrateMax(nBitrate: Integer);
begin
  DefaultInterface.SetAudioBitrateMax(nBitrate);
end;

procedure TStandardMpegEncoderProfile.GetAudioBitrateMax(out nBitrate: Integer);
begin
  DefaultInterface.GetAudioBitrateMax(nBitrate);
end;

procedure TStandardMpegEncoderProfile.SetVideoQuality(nQualityPercent: Integer);
begin
  DefaultInterface.SetVideoQuality(nQualityPercent);
end;

procedure TStandardMpegEncoderProfile.GetVideoQuality(out nQualityPercent: Integer);
begin
  DefaultInterface.GetVideoQuality(nQualityPercent);
end;

procedure TStandardMpegEncoderProfile.SetVideoVBRMode(vbrMode: BitrateMode);
begin
  DefaultInterface.SetVideoVBRMode(vbrMode);
end;

procedure TStandardMpegEncoderProfile.GetVideoVBRMode(out pvbrMode: BitrateMode);
begin
  DefaultInterface.GetVideoVBRMode(pvbrMode);
end;

procedure TStandardMpegEncoderProfile.SetVideoVBVBufferSize(vbvlen: Integer);
begin
  DefaultInterface.SetVideoVBVBufferSize(vbvlen);
end;

procedure TStandardMpegEncoderProfile.GetVideoVBVBufferSize(out vbvlen: Integer);
begin
  DefaultInterface.GetVideoVBVBufferSize(vbvlen);
end;

procedure TStandardMpegEncoderProfile.SetAudioVBRMode(vbrMode: BitrateMode);
begin
  DefaultInterface.SetAudioVBRMode(vbrMode);
end;

procedure TStandardMpegEncoderProfile.GetAudioVBRMode(out pvbrMode: BitrateMode);
begin
  DefaultInterface.GetAudioVBRMode(pvbrMode);
end;

procedure TStandardMpegEncoderProfile.Set2PassLogFile(const Path: WideString);
begin
  DefaultInterface.Set2PassLogFile(Path);
end;

procedure TStandardMpegEncoderProfile.SetVideoQualityRange(nMin: Integer; nMax: Integer);
begin
  DefaultInterface.SetVideoQualityRange(nMin, nMax);
end;

procedure TStandardMpegEncoderProfile.SetFramerate(fps: Double);
begin
  DefaultInterface.SetFramerate(fps);
end;

procedure TStandardMpegEncoderProfile.GetFramerate(out fps: Double);
begin
  DefaultInterface.GetFramerate(fps);
end;

procedure TStandardMpegEncoderProfile.SetAudioSampleRate(nSampleRate: Integer);
begin
  DefaultInterface.SetAudioSampleRate(nSampleRate);
end;

procedure TStandardMpegEncoderProfile.GetAudioSampleRate(out pnSampleRate: Integer);
begin
  DefaultInterface.GetAudioSampleRate(pnSampleRate);
end;

procedure TStandardMpegEncoderProfile.SetAudioChannels(nChannelCount: Integer);
begin
  DefaultInterface.SetAudioChannels(nChannelCount);
end;

procedure TStandardMpegEncoderProfile.GetAudioChannels(out pnChannelCount: Integer);
begin
  DefaultInterface.GetAudioChannels(pnChannelCount);
end;

procedure TStandardMpegEncoderProfile.SetAudioFlags(bErrorProtection: Integer; bOriginal: Integer; 
                                                    bCopyright: Integer; bPrivate: Integer);
begin
  DefaultInterface.SetAudioFlags(bErrorProtection, bOriginal, bCopyright, bPrivate);
end;

procedure TStandardMpegEncoderProfile.SetComments(const strVal: WideString);
begin
  DefaultInterface.SetComments(strVal);
end;

procedure TStandardMpegEncoderProfile.SetInformation(const strTitle: WideString; 
                                                     const strAuthor: WideString; 
                                                     const strCopyright: WideString);
begin
  DefaultInterface.SetInformation(strTitle, strAuthor, strCopyright);
end;

procedure TStandardMpegEncoderProfile.SetEncodeMode(nValue: EncodeMode);
begin
  DefaultInterface.SetEncodeMode(nValue);
end;

procedure TStandardMpegEncoderProfile.GetEncodeMode(out pnValue: EncodeMode);
begin
  DefaultInterface.GetEncodeMode(pnValue);
end;

procedure TStandardMpegEncoderProfile.SetBWVideo(bVal: Integer);
begin
  DefaultInterface.SetBWVideo(bVal);
end;

procedure TStandardMpegEncoderProfile.SetGOPSize(nGOPSize: Integer);
begin
  DefaultInterface.SetGOPSize(nGOPSize);
end;

procedure TStandardMpegEncoderProfile.GetGOPSize(out nGOPSize: Integer);
begin
  DefaultInterface.GetGOPSize(nGOPSize);
end;

procedure TStandardMpegEncoderProfile.SetDetectSceneChange(bVal: Integer);
begin
  DefaultInterface.SetDetectSceneChange(bVal);
end;

procedure TStandardMpegEncoderProfile.GetDetectSceneChange(out nVal: Integer);
begin
  DefaultInterface.GetDetectSceneChange(nVal);
end;

procedure TStandardMpegEncoderProfile.SetSceneChangeThreshold(f: Single);
begin
  DefaultInterface.SetSceneChangeThreshold(f);
end;

procedure TStandardMpegEncoderProfile.SetClosedGOP(bVal: Integer);
begin
  DefaultInterface.SetClosedGOP(bVal);
end;

procedure TStandardMpegEncoderProfile.GetClosedGOP(out nVal: Integer);
begin
  DefaultInterface.GetClosedGOP(nVal);
end;

procedure TStandardMpegEncoderProfile.SetOutputIntervalOfSequenceHeader(nVal: Integer);
begin
  DefaultInterface.SetOutputIntervalOfSequenceHeader(nVal);
end;

procedure TStandardMpegEncoderProfile.GetOutputIntervalOfSequenceHeader(var nVal: Integer);
begin
  DefaultInterface.GetOutputIntervalOfSequenceHeader(nVal);
end;

procedure TStandardMpegEncoderProfile.SetGOPStructure(const strStructure: WideString);
begin
  DefaultInterface.SetGOPStructure(strStructure);
end;

procedure TStandardMpegEncoderProfile.GetGOPStructure(out pstrStructure: WideString);
begin
  DefaultInterface.GetGOPStructure(pstrStructure);
end;

procedure TStandardMpegEncoderProfile.SetStrictGOP(bVal: Integer);
begin
  DefaultInterface.SetStrictGOP(bVal);
end;

procedure TStandardMpegEncoderProfile.SetProfileAndLevel(const strProfileAndLevel: WideString);
begin
  DefaultInterface.SetProfileAndLevel(strProfileAndLevel);
end;

procedure TStandardMpegEncoderProfile.GetProfileAndLevel(out pstrProfileAndLevel: WideString);
begin
  DefaultInterface.GetProfileAndLevel(pstrProfileAndLevel);
end;

procedure TStandardMpegEncoderProfile.SetMotionSearchPrecision(nVal: Integer);
begin
  DefaultInterface.SetMotionSearchPrecision(nVal);
end;

procedure TStandardMpegEncoderProfile.GetMotionSearchPrecision(out nVal: Integer);
begin
  DefaultInterface.GetMotionSearchPrecision(nVal);
end;

procedure TStandardMpegEncoderProfile.SetQuantBias(nIntra: Integer; nInter: Integer);
begin
  DefaultInterface.SetQuantBias(nIntra, nInter);
end;

procedure TStandardMpegEncoderProfile.SetIDCT(n: Integer);
begin
  DefaultInterface.SetIDCT(n);
end;

procedure TStandardMpegEncoderProfile.SetQuantFactor(fQuantFactor: Single);
begin
  DefaultInterface.SetQuantFactor(fQuantFactor);
end;

procedure TStandardMpegEncoderProfile.GetQuantFactor(out pfQuantFactor: Single);
begin
  DefaultInterface.GetQuantFactor(pfQuantFactor);
end;

procedure TStandardMpegEncoderProfile.SetInterlaceMode(bPreProcessDeinterlace: Integer; 
                                                       bInterlacedOutputDCT: Integer; 
                                                       bInterlacedOutputME: Integer);
begin
  DefaultInterface.SetInterlaceMode(bPreProcessDeinterlace, bInterlacedOutputDCT, 
                                    bInterlacedOutputME);
end;

procedure TStandardMpegEncoderProfile.GetInterlaceMode(out bPreProcessDeinterlace: Integer; 
                                                       out bInterlacedOutputDCT: Integer; 
                                                       out bInterlacedOutputME: Integer);
begin
  DefaultInterface.GetInterlaceMode(bPreProcessDeinterlace, bInterlacedOutputDCT, 
                                    bInterlacedOutputME);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TStandardMpegEncoderProfileProperties.Create(AServer: TStandardMpegEncoderProfile);
begin
  inherited Create;
  FServer := AServer;
end;

function TStandardMpegEncoderProfileProperties.GetDefaultInterface: IStandardMpegEncoderProfile;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

class function CoStandardMpegMultiplexerProfile.Create: IStandardMpegMultiplexerProfile;
begin
  Result := CreateComObject(CLASS_StandardMpegMultiplexerProfile) as IStandardMpegMultiplexerProfile;
end;

class function CoStandardMpegMultiplexerProfile.CreateRemote(const MachineName: string): IStandardMpegMultiplexerProfile;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_StandardMpegMultiplexerProfile) as IStandardMpegMultiplexerProfile;
end;

procedure TStandardMpegMultiplexerProfile.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{022A32A5-3689-4D5F-B8CC-C26655C2BA03}';
    IntfIID:   '{7E772181-B7ED-4D9D-A364-0E8771AAFF70}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TStandardMpegMultiplexerProfile.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IStandardMpegMultiplexerProfile;
  end;
end;

procedure TStandardMpegMultiplexerProfile.ConnectTo(svrIntf: IStandardMpegMultiplexerProfile);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TStandardMpegMultiplexerProfile.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TStandardMpegMultiplexerProfile.GetDefaultInterface: IStandardMpegMultiplexerProfile;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TStandardMpegMultiplexerProfile.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TStandardMpegMultiplexerProfileProperties.Create(Self);
{$ENDIF}
end;

destructor TStandardMpegMultiplexerProfile.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TStandardMpegMultiplexerProfile.GetServerProperties: TStandardMpegMultiplexerProfileProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TStandardMpegMultiplexerProfile.SetDeleteElementaryStreams(bDelete: Integer);
begin
  DefaultInterface.SetDeleteElementaryStreams(bDelete);
end;

procedure TStandardMpegMultiplexerProfile.GetDeleteElementaryStreams(out bDelete: Integer);
begin
  DefaultInterface.GetDeleteElementaryStreams(bDelete);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexRate(nRate: Integer);
begin
  DefaultInterface.SetMultiplexRate(nRate);
end;

procedure TStandardMpegMultiplexerProfile.GetMultiplexRate(out pnMux: Integer);
begin
  DefaultInterface.GetMultiplexRate(pnMux);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexPacketSize(nSize: Integer);
begin
  DefaultInterface.SetMultiplexPacketSize(nSize);
end;

procedure TStandardMpegMultiplexerProfile.GetMultiplexPacketSize(out pnSize: Integer);
begin
  DefaultInterface.GetMultiplexPacketSize(pnSize);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexPreload(fPreload: Single);
begin
  DefaultInterface.SetMultiplexPreload(fPreload);
end;

procedure TStandardMpegMultiplexerProfile.GetMultiplexPreload(out pfPreload: Single);
begin
  DefaultInterface.GetMultiplexPreload(pfPreload);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexMaxDelay(fMaxDelay: Single);
begin
  DefaultInterface.SetMultiplexMaxDelay(fMaxDelay);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexStreams(bMux: Integer);
begin
  DefaultInterface.SetMultiplexStreams(bMux);
end;

procedure TStandardMpegMultiplexerProfile.GetMultiplexStreams(out bMux: Integer);
begin
  DefaultInterface.GetMultiplexStreams(bMux);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexFormat(format: SystemsOutputFormat);
begin
  DefaultInterface.SetMultiplexFormat(format);
end;

procedure TStandardMpegMultiplexerProfile.GetMultiplexFormat(out format: SystemsOutputFormat);
begin
  DefaultInterface.GetMultiplexFormat(format);
end;

procedure TStandardMpegMultiplexerProfile.AddMultiplexFile(const strPath: WideString);
begin
  DefaultInterface.AddMultiplexFile(strPath);
end;

procedure TStandardMpegMultiplexerProfile.SetOnFlyMultiplex(bOnFlyMultiplex: Integer);
begin
  DefaultInterface.SetOnFlyMultiplex(bOnFlyMultiplex);
end;

procedure TStandardMpegMultiplexerProfile.GetOnFlyMultiplex(out pbOnFlyMultiplex: Integer);
begin
  DefaultInterface.GetOnFlyMultiplex(pbOnFlyMultiplex);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexFrameBalance(bVal: Integer);
begin
  DefaultInterface.SetMultiplexFrameBalance(bVal);
end;

procedure TStandardMpegMultiplexerProfile.SetMultiplexOnStop(bVal: Integer);
begin
  DefaultInterface.SetMultiplexOnStop(bVal);
end;

procedure TStandardMpegMultiplexerProfile.GetMultiplexProgress(out dProgress: Double);
begin
  DefaultInterface.GetMultiplexProgress(dProgress);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TStandardMpegMultiplexerProfileProperties.Create(AServer: TStandardMpegMultiplexerProfile);
begin
  inherited Create;
  FServer := AServer;
end;

function TStandardMpegMultiplexerProfileProperties.GetDefaultInterface: IStandardMpegMultiplexerProfile;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

class function CoStandardMpegEncoderGeneralProps.Create: IPropertyPage;
begin
  Result := CreateComObject(CLASS_StandardMpegEncoderGeneralProps) as IPropertyPage;
end;

class function CoStandardMpegEncoderGeneralProps.CreateRemote(const MachineName: string): IPropertyPage;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_StandardMpegEncoderGeneralProps) as IPropertyPage;
end;

procedure TStandardMpegEncoderGeneralProps.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{4A6D5C73-270C-4C05-871A-28230F2A8BCC}';
    IntfIID:   '{B196B28D-BAB4-101A-B69C-00AA00341D07}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TStandardMpegEncoderGeneralProps.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IPropertyPage;
  end;
end;

procedure TStandardMpegEncoderGeneralProps.ConnectTo(svrIntf: IPropertyPage);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TStandardMpegEncoderGeneralProps.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TStandardMpegEncoderGeneralProps.GetDefaultInterface: IPropertyPage;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TStandardMpegEncoderGeneralProps.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TStandardMpegEncoderGeneralPropsProperties.Create(Self);
{$ENDIF}
end;

destructor TStandardMpegEncoderGeneralProps.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TStandardMpegEncoderGeneralProps.GetServerProperties: TStandardMpegEncoderGeneralPropsProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TStandardMpegEncoderGeneralProps.SetPageSite(const pPageSite: IPropertyPageSite): HResult;
begin
  Result := DefaultInterface.SetPageSite(pPageSite);
end;

function TStandardMpegEncoderGeneralProps.Activate(var hWndParent: _RemotableHandle; 
                                                   var pRect: tagRECT; bModal: Integer): HResult;
begin
  Result := DefaultInterface.Activate(hWndParent, pRect, bModal);
end;

function TStandardMpegEncoderGeneralProps.Deactivate: HResult;
begin
  Result := DefaultInterface.Deactivate;
end;

function TStandardMpegEncoderGeneralProps.GetPageInfo(out pPageInfo: tagPROPPAGEINFO): HResult;
begin
  Result := DefaultInterface.GetPageInfo(pPageInfo);
end;

function TStandardMpegEncoderGeneralProps.SetObjects(cObjects: LongWord; var ppUnk: IUnknown): HResult;
begin
  Result := DefaultInterface.SetObjects(cObjects, ppUnk);
end;

function TStandardMpegEncoderGeneralProps.Show(nCmdShow: SYSUINT): HResult;
begin
  Result := DefaultInterface.Show(nCmdShow);
end;

function TStandardMpegEncoderGeneralProps.Move(var pRect: tagRECT): HResult;
begin
  Result := DefaultInterface.Move(pRect);
end;

function TStandardMpegEncoderGeneralProps.IsPageDirty: HResult;
begin
  Result := DefaultInterface.IsPageDirty;
end;

function TStandardMpegEncoderGeneralProps.Apply: HResult;
begin
  Result := DefaultInterface.Apply;
end;

function TStandardMpegEncoderGeneralProps.Help(pszHelpDir: PWideChar): HResult;
begin
  Result := DefaultInterface.Help(pszHelpDir);
end;

function TStandardMpegEncoderGeneralProps.TranslateAccelerator(var pMsg: tagMSG): HResult;
begin
  Result := DefaultInterface.TranslateAccelerator(pMsg);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TStandardMpegEncoderGeneralPropsProperties.Create(AServer: TStandardMpegEncoderGeneralProps);
begin
  inherited Create;
  FServer := AServer;
end;

function TStandardMpegEncoderGeneralPropsProperties.GetDefaultInterface: IPropertyPage;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

class function CoStandardMpegEncoderVideoProps.Create: IPropertyPage;
begin
  Result := CreateComObject(CLASS_StandardMpegEncoderVideoProps) as IPropertyPage;
end;

class function CoStandardMpegEncoderVideoProps.CreateRemote(const MachineName: string): IPropertyPage;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_StandardMpegEncoderVideoProps) as IPropertyPage;
end;

procedure TStandardMpegEncoderVideoProps.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{DCD4E0B0-FE55-44C6-9B4C-1E78FA2D6D2C}';
    IntfIID:   '{B196B28D-BAB4-101A-B69C-00AA00341D07}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TStandardMpegEncoderVideoProps.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IPropertyPage;
  end;
end;

procedure TStandardMpegEncoderVideoProps.ConnectTo(svrIntf: IPropertyPage);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TStandardMpegEncoderVideoProps.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TStandardMpegEncoderVideoProps.GetDefaultInterface: IPropertyPage;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TStandardMpegEncoderVideoProps.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TStandardMpegEncoderVideoPropsProperties.Create(Self);
{$ENDIF}
end;

destructor TStandardMpegEncoderVideoProps.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TStandardMpegEncoderVideoProps.GetServerProperties: TStandardMpegEncoderVideoPropsProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TStandardMpegEncoderVideoProps.SetPageSite(const pPageSite: IPropertyPageSite): HResult;
begin
  Result := DefaultInterface.SetPageSite(pPageSite);
end;

function TStandardMpegEncoderVideoProps.Activate(var hWndParent: _RemotableHandle; 
                                                 var pRect: tagRECT; bModal: Integer): HResult;
begin
  Result := DefaultInterface.Activate(hWndParent, pRect, bModal);
end;

function TStandardMpegEncoderVideoProps.Deactivate: HResult;
begin
  Result := DefaultInterface.Deactivate;
end;

function TStandardMpegEncoderVideoProps.GetPageInfo(out pPageInfo: tagPROPPAGEINFO): HResult;
begin
  Result := DefaultInterface.GetPageInfo(pPageInfo);
end;

function TStandardMpegEncoderVideoProps.SetObjects(cObjects: LongWord; var ppUnk: IUnknown): HResult;
begin
  Result := DefaultInterface.SetObjects(cObjects, ppUnk);
end;

function TStandardMpegEncoderVideoProps.Show(nCmdShow: SYSUINT): HResult;
begin
  Result := DefaultInterface.Show(nCmdShow);
end;

function TStandardMpegEncoderVideoProps.Move(var pRect: tagRECT): HResult;
begin
  Result := DefaultInterface.Move(pRect);
end;

function TStandardMpegEncoderVideoProps.IsPageDirty: HResult;
begin
  Result := DefaultInterface.IsPageDirty;
end;

function TStandardMpegEncoderVideoProps.Apply: HResult;
begin
  Result := DefaultInterface.Apply;
end;

function TStandardMpegEncoderVideoProps.Help(pszHelpDir: PWideChar): HResult;
begin
  Result := DefaultInterface.Help(pszHelpDir);
end;

function TStandardMpegEncoderVideoProps.TranslateAccelerator(var pMsg: tagMSG): HResult;
begin
  Result := DefaultInterface.TranslateAccelerator(pMsg);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TStandardMpegEncoderVideoPropsProperties.Create(AServer: TStandardMpegEncoderVideoProps);
begin
  inherited Create;
  FServer := AServer;
end;

function TStandardMpegEncoderVideoPropsProperties.GetDefaultInterface: IPropertyPage;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

class function CoStandardMpegEncoderAudioProps.Create: IPropertyPage;
begin
  Result := CreateComObject(CLASS_StandardMpegEncoderAudioProps) as IPropertyPage;
end;

class function CoStandardMpegEncoderAudioProps.CreateRemote(const MachineName: string): IPropertyPage;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_StandardMpegEncoderAudioProps) as IPropertyPage;
end;

procedure TStandardMpegEncoderAudioProps.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{BDB70B23-BAA7-44A5-8CB5-A3F5F34865C8}';
    IntfIID:   '{B196B28D-BAB4-101A-B69C-00AA00341D07}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TStandardMpegEncoderAudioProps.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IPropertyPage;
  end;
end;

procedure TStandardMpegEncoderAudioProps.ConnectTo(svrIntf: IPropertyPage);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TStandardMpegEncoderAudioProps.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TStandardMpegEncoderAudioProps.GetDefaultInterface: IPropertyPage;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TStandardMpegEncoderAudioProps.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TStandardMpegEncoderAudioPropsProperties.Create(Self);
{$ENDIF}
end;

destructor TStandardMpegEncoderAudioProps.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TStandardMpegEncoderAudioProps.GetServerProperties: TStandardMpegEncoderAudioPropsProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TStandardMpegEncoderAudioProps.SetPageSite(const pPageSite: IPropertyPageSite): HResult;
begin
  Result := DefaultInterface.SetPageSite(pPageSite);
end;

function TStandardMpegEncoderAudioProps.Activate(var hWndParent: _RemotableHandle; 
                                                 var pRect: tagRECT; bModal: Integer): HResult;
begin
  Result := DefaultInterface.Activate(hWndParent, pRect, bModal);
end;

function TStandardMpegEncoderAudioProps.Deactivate: HResult;
begin
  Result := DefaultInterface.Deactivate;
end;

function TStandardMpegEncoderAudioProps.GetPageInfo(out pPageInfo: tagPROPPAGEINFO): HResult;
begin
  Result := DefaultInterface.GetPageInfo(pPageInfo);
end;

function TStandardMpegEncoderAudioProps.SetObjects(cObjects: LongWord; var ppUnk: IUnknown): HResult;
begin
  Result := DefaultInterface.SetObjects(cObjects, ppUnk);
end;

function TStandardMpegEncoderAudioProps.Show(nCmdShow: SYSUINT): HResult;
begin
  Result := DefaultInterface.Show(nCmdShow);
end;

function TStandardMpegEncoderAudioProps.Move(var pRect: tagRECT): HResult;
begin
  Result := DefaultInterface.Move(pRect);
end;

function TStandardMpegEncoderAudioProps.IsPageDirty: HResult;
begin
  Result := DefaultInterface.IsPageDirty;
end;

function TStandardMpegEncoderAudioProps.Apply: HResult;
begin
  Result := DefaultInterface.Apply;
end;

function TStandardMpegEncoderAudioProps.Help(pszHelpDir: PWideChar): HResult;
begin
  Result := DefaultInterface.Help(pszHelpDir);
end;

function TStandardMpegEncoderAudioProps.TranslateAccelerator(var pMsg: tagMSG): HResult;
begin
  Result := DefaultInterface.TranslateAccelerator(pMsg);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TStandardMpegEncoderAudioPropsProperties.Create(AServer: TStandardMpegEncoderAudioProps);
begin
  inherited Create;
  FServer := AServer;
end;

function TStandardMpegEncoderAudioPropsProperties.GetDefaultInterface: IPropertyPage;
begin
  Result := FServer.DefaultInterface;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TStandardMpegEncoder, TStandardMpegEncoderStats, TStandardMpegEncoderProfile, TStandardMpegMultiplexerProfile, 
    TStandardMpegEncoderGeneralProps, TStandardMpegEncoderVideoProps, TStandardMpegEncoderAudioProps]);
end;

end.
