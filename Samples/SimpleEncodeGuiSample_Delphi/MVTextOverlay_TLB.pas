unit MVTextOverlay_TLB;

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
// File generated on 2006-09-13 16:03:01 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\MontiVision\MontiVision Development Kit\bin\filter\textoverlay.ax (1)
// LIBID: {A77FC2E0-DE0C-4D49-9460-731D302FD5C7}
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
  MVTextOverlayMajorVersion = 1;
  MVTextOverlayMinorVersion = 0;

  LIBID_MVTextOverlay: TGUID = '{A77FC2E0-DE0C-4D49-9460-731D302FD5C7}';

  IID_IMVTextOverlay: TGUID = '{85E5E6D4-E046-4FAA-A646-0F6519E93011}';
  IID_IMVTextOverlay2: TGUID = '{1F80E700-1B5A-4E6F-A061-B4B625E36E07}';
  IID_IMVFilterData: TGUID = '{5125ADE2-346C-4ECF-B8D5-10F1E550B44D}';
  IID_IMVFilterInfo: TGUID = '{A60D8C9D-A16B-4E80-BB7B-252CEA4B7B70}';
  IID_IMVAbout: TGUID = '{3D20EE29-5605-4FDD-B5AF-5BDBB60DC5C2}';
  IID_IMVHistogram: TGUID = '{B5F515BB-FA84-439C-90B9-3744CEC8100D}';
  IID_IMVHistogram2: TGUID = '{A2CC0FD6-58C6-4649-9062-1099EA03631A}';
  IID_IMVHistogram3: TGUID = '{7E58B6FA-275B-4EEB-93FB-67071E65A061}';
  IID_IMVFilterEvents: TGUID = '{9C33ECD8-33C1-4A37-9076-AAD099F7778B}';
  CLASS_CMVTextOverlay: TGUID = '{18FF8464-7049-4C31-9999-1734C0BD5FC9}';

// *********************************************************************//
// Declaration of Enumerations defined in Type Library                    
// *********************************************************************//
// Constants for enum _MV_COM_EVENTS
type
  _MV_COM_EVENTS = TOleEnum;
const
  MV_ALGORITHM_START_EVENT = $00000000;
  MV_ALGORITHM_END_EVENT = $00000001;
  MV_IMAGE_CAPTURE_START_EVENT = $00000002;
  MV_IMAGE_CAPTURE_END_EVENT = $00000003;
  MV_IO_DATA_RECEIVE_EVENT = $00000004;
  MV_CALIBRATION_VALID_IMAGE_EVENT = $00000005;
  MV_CALIBRATION_FINISHED_EVENT = $00000006;
  MV_START_RECORDING_EVENT = $00000007;
  MV_STOP_RECORDING_EVENT = $00000008;
  MV_CANT_OPEN_COM_PORT_EVENT = $00000009;
  MV_CANT_WRITE_TO_COM_PORT_EVENT = $0000000A;
  MV_CANT_READ_FROM_COM_PORT_EVENT = $0000000B;
  MV_CANT_GET_EVENT_FROM_COM_PORT_EVENT = $0000000C;
  MV_PLAYLIST_ADD_ITEM_EVENT = $0000000D;
  MV_PLAYLIST_REMOVE_ITEM_EVENT = $0000000E;
  MV_PLAYLIST_NEW_CURRENT_ITEM_EVENT = $0000000F;
  MV_PLAYLIST_ITEM_CHANGED_EVENT = $00000010;
  MV_MOTION_START_EVENT = $00000011;
  MV_MOTION_END_EVENT = $00000012;
  MV_RECORD_START_EVENT = $00000013;
  MV_RECORD_END_EVENT = $00000014;
  MV_WATCHDOG_RELEASE_EVENT = $00000015;
  MV_WATCHDOG_FINISHED_EVENT = $00000016;
  MV_FILEWRITER_NEXT_FILE_EVENT = $00000017;
  MV_FILEWRITER_INVALID_OUTPUT_PATH_EVENT = $00000018;
  MV_FILEWRITER_INVALID_VIDEO_ENCODER_EVENT = $00000019;
  MV_FILEWRITER_INVALID_AUDIO_ENCODER_EVENT = $0000001A;
  MV_FILEWRITER_LOW_DISKSPACE_EVENT = $0000001B;
  MV_RXTXCONNECTION_ON_EVENT = $0000001C;
  MV_RXTXCONNECTION_OFF_EVENT = $0000001D;
  MV_IP_CAMERA_RECONNECT_EVENT = $0000001E;
  MV_IP_CAMERA_INITIALIZED_EVENT = $0000001F;

// Constants for enum _MV_COLOR_CHANNEL
type
  _MV_COLOR_CHANNEL = TOleEnum;
const
  MV_CHANNEL_ALL = $00000000;
  MV_CHANNEL_BLUE = $00000001;
  MV_CHANNEL_GREEN = $00000002;
  MV_CHANNEL_RED = $00000003;

// Constants for enum _MV_TEXT_OVERLAY_MODE
type
  _MV_TEXT_OVERLAY_MODE = TOleEnum;
const
  MV_TEXT_OVERLAY_MODE_TEXT = $00000000;
  MV_TEXT_OVERLAY_MODE_DATE = $00000001;

// Constants for enum _MV_POSITION_MODE
type
  _MV_POSITION_MODE = TOleEnum;
const
  MV_POSITION_RELATIVE = $00000000;
  MV_POSITION_ABSOLUTE = $00000001;

// Constants for enum _MV_RELATIVE_POSITION
type
  _MV_RELATIVE_POSITION = TOleEnum;
const
  MV_POSITION_UPPER_LEFT = $00000000;
  MV_POSITION_UPPER_RIGHT = $00000001;
  MV_POSITION_LOWER_RIGHT = $00000002;
  MV_POSITION_LOWER_LEFT = $00000003;
  MV_POSITION_TOP = $00000004;
  MV_POSITION_BOTTOM = $00000005;

type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IMVTextOverlay = interface;
  IMVTextOverlay2 = interface;
  IMVFilterData = interface;
  IMVFilterInfo = interface;
  IMVAbout = interface;
  IMVHistogram = interface;
  IMVHistogram2 = interface;
  IMVHistogram3 = interface;
  IMVFilterEvents = interface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  CMVTextOverlay = IMVTextOverlay;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//
  PByte1 = ^Byte; {*}

  PrivateAlias1 = array[0..255] of SYSINT; {*}

// *********************************************************************//
// Interface: IMVTextOverlay
// Flags:     (0)
// GUID:      {85E5E6D4-E046-4FAA-A646-0F6519E93011}
// *********************************************************************//
  IMVTextOverlay = interface(IUnknown)
    ['{85E5E6D4-E046-4FAA-A646-0F6519E93011}']
    function Get_Enable(out Enable: WordBool): HResult; stdcall;
    function Set_Enable(Enable: WordBool): HResult; stdcall;
    function Get_OverlayMode(out Mode: SYSINT): HResult; stdcall;
    function Set_OverlayMode(Mode: SYSINT): HResult; stdcall;
    function Get_PositionMode(out Mode: SYSINT): HResult; stdcall;
    function Set_PositionMode(Mode: SYSINT): HResult; stdcall;
    function Get_XPosition(out X: SYSINT): HResult; stdcall;
    function Set_XPosition(X: SYSINT): HResult; stdcall;
    function Get_YPosition(out Y: SYSINT): HResult; stdcall;
    function Set_YPosition(Y: SYSINT): HResult; stdcall;
    function Get_RelativePosition(out Pos: SYSINT): HResult; stdcall;
    function Set_RelativePosition(Pos: SYSINT): HResult; stdcall;
    function Get_TransparentBack(out Enable: WordBool): HResult; stdcall;
    function Set_TransparentBack(Enable: WordBool): HResult; stdcall;
    function Get_BackgroundColor(out Colour: OLE_COLOR): HResult; stdcall;
    function Set_BackgroundColor(Colour: OLE_COLOR): HResult; stdcall;
    function Get_ForegroundColor(out Colour: OLE_COLOR): HResult; stdcall;
    function Set_ForegroundColor(Colour: OLE_COLOR): HResult; stdcall;
    function Get_Text(out Text: WideString): HResult; stdcall;
    function Set_Text(const Text: WideString): HResult; stdcall;
    function Get_FontSize(out Height: SYSINT): HResult; stdcall;
    function Set_FontSize(Height: SYSINT): HResult; stdcall;
    function Get_FontTypeFace(out TypeFace: WideString): HResult; stdcall;
    function Set_FontTypeFace(const TypeFace: WideString): HResult; stdcall;
    function Get_xMargin(out xMargin: SYSINT): HResult; stdcall;
    function Set_xMargin(xMargin: SYSINT): HResult; stdcall;
    function Get_yMargin(out yMargin: SYSINT): HResult; stdcall;
    function Set_yMargin(yMargin: SYSINT): HResult; stdcall;
    function Get_Shadow(out Enable: WordBool): HResult; stdcall;
    function Set_Shadow(Enable: WordBool): HResult; stdcall;
    function Get_ShadowColor(out Colour: OLE_COLOR): HResult; stdcall;
    function Set_ShadowColor(Colour: OLE_COLOR): HResult; stdcall;
    function Get_ShadowOffset(out Offset: SYSINT): HResult; stdcall;
    function Set_ShadowOffset(Offset: SYSINT): HResult; stdcall;
    function Get_Bold(out Enable: WordBool): HResult; stdcall;
    function Set_Bold(Enable: WordBool): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVTextOverlay2
// Flags:     (0)
// GUID:      {1F80E700-1B5A-4E6F-A061-B4B625E36E07}
// *********************************************************************//
  IMVTextOverlay2 = interface(IMVTextOverlay)
    ['{1F80E700-1B5A-4E6F-A061-B4B625E36E07}']
    function Get_NumOfOverlays(out NumOverlays: SYSINT): HResult; stdcall;
    function Set_NumOfOverlays(NumOverlays: SYSINT): HResult; stdcall;
    function Get_SelectedOverlay(out Selected: SYSINT): HResult; stdcall;
    function Set_SelectedOverlay(Selected: SYSINT): HResult; stdcall;
    function Get_IOPinSeparator(out Separator: WideString): HResult; stdcall;
    function Set_IOPinSeparator(const Separator: WideString): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVFilterData
// Flags:     (0)
// GUID:      {5125ADE2-346C-4ECF-B8D5-10F1E550B44D}
// *********************************************************************//
  IMVFilterData = interface(IUnknown)
    ['{5125ADE2-346C-4ECF-B8D5-10F1E550B44D}']
    function GetFilterRegKey(out pbstrRegKey: WideString): HResult; stdcall;
    function GetFilterData(cMax: SYSINT; out pFilterData: Byte): HResult; stdcall;
    function PutFilterData(cMax: SYSINT; var pFilterData: Byte): HResult; stdcall;
    function GetMaxDataSize(out piMaxDataSize: SYSINT): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVFilterInfo
// Flags:     (0)
// GUID:      {A60D8C9D-A16B-4E80-BB7B-252CEA4B7B70}
// *********************************************************************//
  IMVFilterInfo = interface(IUnknown)
    ['{A60D8C9D-A16B-4E80-BB7B-252CEA4B7B70}']
    function GetNumOfInPins(out piInputPins: SYSINT): HResult; stdcall;
    function GetNumOfOutPins(out piOutputPins: SYSINT): HResult; stdcall;
    function Get_SelectedInfoPin(out piActualPin: SYSINT): HResult; stdcall;
    function Set_SelectedInfoPin(piActualPin: SYSINT): HResult; stdcall;
    function Get_InfoPinDirection(out piPinDirection: SYSINT): HResult; stdcall;
    function Set_InfoPinDirection(piPinDirection: SYSINT): HResult; stdcall;
    function GetImageInfo(out piWidth: SYSINT; out piHeight: SYSINT; out piChannel: SYSINT): HResult; stdcall;
    function GetImageWidth(out piWidth: SYSINT): HResult; stdcall;
    function GetImageHeight(out piHeight: SYSINT): HResult; stdcall;
    function GetNumOfChannels(out piChannel: SYSINT): HResult; stdcall;
    function GetSymbol16(out ppbySymbol: PByte1): HResult; stdcall;
    function GetSymbol32(out ppbySymbol: PByte1): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVAbout
// Flags:     (0)
// GUID:      {3D20EE29-5605-4FDD-B5AF-5BDBB60DC5C2}
// *********************************************************************//
  IMVAbout = interface(IUnknown)
    ['{3D20EE29-5605-4FDD-B5AF-5BDBB60DC5C2}']
    function GetAboutData(out pbyAboutData: Byte): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVHistogram
// Flags:     (0)
// GUID:      {B5F515BB-FA84-439C-90B9-3744CEC8100D}
// *********************************************************************//
  IMVHistogram = interface(IUnknown)
    ['{B5F515BB-FA84-439C-90B9-3744CEC8100D}']
    function Get_SelectedHistPin(out piActualPin: SYSINT): HResult; stdcall;
    function Set_SelectedHistPin(piActualPin: SYSINT): HResult; stdcall;
    function Get_HistPinDirection(out piPinDirection: SYSINT): HResult; stdcall;
    function Set_HistPinDirection(piPinDirection: SYSINT): HResult; stdcall;
    function Get_HistChannel(out piChannel: SYSINT): HResult; stdcall;
    function Set_HistChannel(piChannel: SYSINT): HResult; stdcall;
    function Get_WhiteClipping(out piWhiteClip: SYSINT): HResult; stdcall;
    function Set_WhiteClipping(piWhiteClip: SYSINT): HResult; stdcall;
    function Get_BlackClipping(out piBlackClip: SYSINT): HResult; stdcall;
    function Set_BlackClipping(piBlackClip: SYSINT): HResult; stdcall;
    function Get_WhiteClipWidth(out piWhiteClip: SYSINT): HResult; stdcall;
    function Set_WhiteClipWidth(piWhiteClip: SYSINT): HResult; stdcall;
    function Get_BlackClipWidth(out piBlackClip: SYSINT): HResult; stdcall;
    function Set_BlackClipWidth(piBlackClip: SYSINT): HResult; stdcall;
    function CalculateHistogram: HResult; stdcall;
    function GetHistogramData(iHistogram: PrivateAlias1): HResult; stdcall;
    function GetNumOfPinChannel(out piNumOfChannel: SYSINT): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVHistogram2
// Flags:     (0)
// GUID:      {A2CC0FD6-58C6-4649-9062-1099EA03631A}
// *********************************************************************//
  IMVHistogram2 = interface(IMVHistogram)
    ['{A2CC0FD6-58C6-4649-9062-1099EA03631A}']
    function Get_AutoUpdate(out pbAuto: WordBool): HResult; stdcall;
    function Set_AutoUpdate(pbAuto: WordBool): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVHistogram3
// Flags:     (0)
// GUID:      {7E58B6FA-275B-4EEB-93FB-67071E65A061}
// *********************************************************************//
  IMVHistogram3 = interface(IMVHistogram2)
    ['{7E58B6FA-275B-4EEB-93FB-67071E65A061}']
    function GetHistogramValue(Index: SYSINT; out Value: SYSINT): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVFilterEvents
// Flags:     (256) OleAutomation
// GUID:      {9C33ECD8-33C1-4A37-9076-AAD099F7778B}
// *********************************************************************//
  IMVFilterEvents = interface(IUnknown)
    ['{9C33ECD8-33C1-4A37-9076-AAD099F7778B}']
    function MVFilterMessage(iMessage: SYSINT): HResult; stdcall;
  end;

// *********************************************************************//
// The Class CoCMVTextOverlay provides a Create and CreateRemote method to          
// create instances of the default interface IMVTextOverlay exposed by              
// the CoClass CMVTextOverlay. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoCMVTextOverlay = class
    class function Create: IMVTextOverlay;
    class function CreateRemote(const MachineName: string): IMVTextOverlay;
  end;

  TCMVTextOverlayMVFilterMessage = procedure(Sender: TObject; iMessage: SYSINT) of object;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TCMVTextOverlay
// Help String      : MontiVision Text Overlay Filter Class
// Default Interface: IMVTextOverlay
// Def. Intf. DISP? : No
// Event   Interface: IMVFilterEvents
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TCMVTextOverlayProperties= class;
{$ENDIF}
  TCMVTextOverlay = class(TOleServer)
  private
    FOnMVFilterMessage: TCMVTextOverlayMVFilterMessage;
    FIntf:        IMVTextOverlay;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TCMVTextOverlayProperties;
    function      GetServerProperties: TCMVTextOverlayProperties;
{$ENDIF}
    function      GetDefaultInterface: IMVTextOverlay;
  protected
    procedure InitServerData; override;
    procedure InvokeEvent(DispID: TDispID; var Params: TVariantArray); override;
    function Get_Enable(out Enable: WordBool): HResult;
    function Set_Enable(Enable: WordBool): HResult;
    function Get_OverlayMode(out Mode: SYSINT): HResult;
    function Set_OverlayMode(Mode: SYSINT): HResult;
    function Get_PositionMode(out Mode: SYSINT): HResult;
    function Set_PositionMode(Mode: SYSINT): HResult;
    function Get_XPosition(out X: SYSINT): HResult;
    function Set_XPosition(X: SYSINT): HResult;
    function Get_YPosition(out Y: SYSINT): HResult;
    function Set_YPosition(Y: SYSINT): HResult;
    function Get_RelativePosition(out Pos: SYSINT): HResult;
    function Set_RelativePosition(Pos: SYSINT): HResult;
    function Get_TransparentBack(out Enable: WordBool): HResult;
    function Set_TransparentBack(Enable: WordBool): HResult;
    function Get_BackgroundColor(out Colour: OLE_COLOR): HResult;
    function Set_BackgroundColor(Colour: OLE_COLOR): HResult;
    function Get_ForegroundColor(out Colour: OLE_COLOR): HResult;
    function Set_ForegroundColor(Colour: OLE_COLOR): HResult;
    function Get_Text(out Text: WideString): HResult;
    function Set_Text(const Text: WideString): HResult;
    function Get_FontSize(out Height: SYSINT): HResult;
    function Set_FontSize(Height: SYSINT): HResult;
    function Get_FontTypeFace(out TypeFace: WideString): HResult;
    function Set_FontTypeFace(const TypeFace: WideString): HResult;
    function Get_xMargin(out xMargin: SYSINT): HResult;
    function Set_xMargin(xMargin: SYSINT): HResult;
    function Get_yMargin(out yMargin: SYSINT): HResult;
    function Set_yMargin(yMargin: SYSINT): HResult;
    function Get_Shadow(out Enable: WordBool): HResult;
    function Set_Shadow(Enable: WordBool): HResult;
    function Get_ShadowColor(out Colour: OLE_COLOR): HResult;
    function Set_ShadowColor(Colour: OLE_COLOR): HResult;
    function Get_ShadowOffset(out Offset: SYSINT): HResult;
    function Set_ShadowOffset(Offset: SYSINT): HResult;
    function Get_Bold(out Enable: WordBool): HResult;
    function Set_Bold(Enable: WordBool): HResult;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IMVTextOverlay);
    procedure Disconnect; override;
    property DefaultInterface: IMVTextOverlay read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TCMVTextOverlayProperties read GetServerProperties;
{$ENDIF}
    property OnMVFilterMessage: TCMVTextOverlayMVFilterMessage read FOnMVFilterMessage write FOnMVFilterMessage;
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TCMVTextOverlay
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TCMVTextOverlayProperties = class(TPersistent)
  private
    FServer:    TCMVTextOverlay;
    function    GetDefaultInterface: IMVTextOverlay;
    constructor Create(AServer: TCMVTextOverlay);
  protected
    function Get_Enable(out Enable: WordBool): HResult;
    function Set_Enable(Enable: WordBool): HResult;
    function Get_OverlayMode(out Mode: SYSINT): HResult;
    function Set_OverlayMode(Mode: SYSINT): HResult;
    function Get_PositionMode(out Mode: SYSINT): HResult;
    function Set_PositionMode(Mode: SYSINT): HResult;
    function Get_XPosition(out X: SYSINT): HResult;
    function Set_XPosition(X: SYSINT): HResult;
    function Get_YPosition(out Y: SYSINT): HResult;
    function Set_YPosition(Y: SYSINT): HResult;
    function Get_RelativePosition(out Pos: SYSINT): HResult;
    function Set_RelativePosition(Pos: SYSINT): HResult;
    function Get_TransparentBack(out Enable: WordBool): HResult;
    function Set_TransparentBack(Enable: WordBool): HResult;
    function Get_BackgroundColor(out Colour: OLE_COLOR): HResult;
    function Set_BackgroundColor(Colour: OLE_COLOR): HResult;
    function Get_ForegroundColor(out Colour: OLE_COLOR): HResult;
    function Set_ForegroundColor(Colour: OLE_COLOR): HResult;
    function Get_Text(out Text: WideString): HResult;
    function Set_Text(const Text: WideString): HResult;
    function Get_FontSize(out Height: SYSINT): HResult;
    function Set_FontSize(Height: SYSINT): HResult;
    function Get_FontTypeFace(out TypeFace: WideString): HResult;
    function Set_FontTypeFace(const TypeFace: WideString): HResult;
    function Get_xMargin(out xMargin: SYSINT): HResult;
    function Set_xMargin(xMargin: SYSINT): HResult;
    function Get_yMargin(out yMargin: SYSINT): HResult;
    function Set_yMargin(yMargin: SYSINT): HResult;
    function Get_Shadow(out Enable: WordBool): HResult;
    function Set_Shadow(Enable: WordBool): HResult;
    function Get_ShadowColor(out Colour: OLE_COLOR): HResult;
    function Set_ShadowColor(Colour: OLE_COLOR): HResult;
    function Get_ShadowOffset(out Offset: SYSINT): HResult;
    function Set_ShadowOffset(Offset: SYSINT): HResult;
    function Get_Bold(out Enable: WordBool): HResult;
    function Set_Bold(Enable: WordBool): HResult;
  public
    property DefaultInterface: IMVTextOverlay read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

implementation

uses ComObj;

class function CoCMVTextOverlay.Create: IMVTextOverlay;
begin
  Result := CreateComObject(CLASS_CMVTextOverlay) as IMVTextOverlay;
end;

class function CoCMVTextOverlay.CreateRemote(const MachineName: string): IMVTextOverlay;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_CMVTextOverlay) as IMVTextOverlay;
end;

procedure TCMVTextOverlay.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{18FF8464-7049-4C31-9999-1734C0BD5FC9}';
    IntfIID:   '{85E5E6D4-E046-4FAA-A646-0F6519E93011}';
    EventIID:  '{9C33ECD8-33C1-4A37-9076-AAD099F7778B}';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TCMVTextOverlay.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    ConnectEvents(punk);
    Fintf:= punk as IMVTextOverlay;
  end;
end;

procedure TCMVTextOverlay.ConnectTo(svrIntf: IMVTextOverlay);
begin
  Disconnect;
  FIntf := svrIntf;
  ConnectEvents(FIntf);
end;

procedure TCMVTextOverlay.DisConnect;
begin
  if Fintf <> nil then
  begin
    DisconnectEvents(FIntf);
    FIntf := nil;
  end;
end;

function TCMVTextOverlay.GetDefaultInterface: IMVTextOverlay;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TCMVTextOverlay.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TCMVTextOverlayProperties.Create(Self);
{$ENDIF}
end;

destructor TCMVTextOverlay.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TCMVTextOverlay.GetServerProperties: TCMVTextOverlayProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TCMVTextOverlay.InvokeEvent(DispID: TDispID; var Params: TVariantArray);
begin
  case DispID of
    -1: Exit;  // DISPID_UNKNOWN
(*{The DispID for this method is DISPID_UNKNOWN!?. }
   -1: if Assigned(FOnMVFilterMessage) then
            FOnMVFilterMessage(Self, Params[0] {SYSINT});
*)
  end; {case DispID}
end;

function TCMVTextOverlay.Get_Enable(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.Get_Enable(Enable);
end;

function TCMVTextOverlay.Set_Enable(Enable: WordBool): HResult;
  { Warning: The property Enable has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Enable := Enable;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_OverlayMode(out Mode: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_OverlayMode(Mode);
end;

function TCMVTextOverlay.Set_OverlayMode(Mode: SYSINT): HResult;
  { Warning: The property OverlayMode has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.OverlayMode := Mode;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_PositionMode(out Mode: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_PositionMode(Mode);
end;

function TCMVTextOverlay.Set_PositionMode(Mode: SYSINT): HResult;
  { Warning: The property PositionMode has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.PositionMode := Mode;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_XPosition(out X: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_XPosition(X);
end;

function TCMVTextOverlay.Set_XPosition(X: SYSINT): HResult;
  { Warning: The property XPosition has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.XPosition := X;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_YPosition(out Y: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_YPosition(Y);
end;

function TCMVTextOverlay.Set_YPosition(Y: SYSINT): HResult;
  { Warning: The property YPosition has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.YPosition := Y;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_RelativePosition(out Pos: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_RelativePosition(Pos);
end;

function TCMVTextOverlay.Set_RelativePosition(Pos: SYSINT): HResult;
  { Warning: The property RelativePosition has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.RelativePosition := Pos;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_TransparentBack(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.Get_TransparentBack(Enable);
end;

function TCMVTextOverlay.Set_TransparentBack(Enable: WordBool): HResult;
  { Warning: The property TransparentBack has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.TransparentBack := Enable;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_BackgroundColor(out Colour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.Get_BackgroundColor(Colour);
end;

function TCMVTextOverlay.Set_BackgroundColor(Colour: OLE_COLOR): HResult;
  { Warning: The property BackgroundColor has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.BackgroundColor := Colour;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_ForegroundColor(out Colour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.Get_ForegroundColor(Colour);
end;

function TCMVTextOverlay.Set_ForegroundColor(Colour: OLE_COLOR): HResult;
  { Warning: The property ForegroundColor has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ForegroundColor := Colour;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_Text(out Text: WideString): HResult;
begin
    Result := DefaultInterface.Get_Text(Text);
end;

function TCMVTextOverlay.Set_Text(const Text: WideString): HResult;
  { Warning: The property Text has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Text := Text;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_FontSize(out Height: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_FontSize(Height);
end;

function TCMVTextOverlay.Set_FontSize(Height: SYSINT): HResult;
  { Warning: The property FontSize has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FontSize := Height;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_FontTypeFace(out TypeFace: WideString): HResult;
begin
    Result := DefaultInterface.Get_FontTypeFace(TypeFace);
end;

function TCMVTextOverlay.Set_FontTypeFace(const TypeFace: WideString): HResult;
  { Warning: The property FontTypeFace has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FontTypeFace := TypeFace;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_xMargin(out xMargin: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_xMargin(xMargin);
end;

function TCMVTextOverlay.Set_xMargin(xMargin: SYSINT): HResult;
  { Warning: The property xMargin has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.xMargin := xMargin;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_yMargin(out yMargin: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_yMargin(yMargin);
end;

function TCMVTextOverlay.Set_yMargin(yMargin: SYSINT): HResult;
  { Warning: The property yMargin has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.yMargin := yMargin;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_Shadow(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.Get_Shadow(Enable);
end;

function TCMVTextOverlay.Set_Shadow(Enable: WordBool): HResult;
  { Warning: The property Shadow has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Shadow := Enable;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_ShadowColor(out Colour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.Get_ShadowColor(Colour);
end;

function TCMVTextOverlay.Set_ShadowColor(Colour: OLE_COLOR): HResult;
  { Warning: The property ShadowColor has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ShadowColor := Colour;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_ShadowOffset(out Offset: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_ShadowOffset(Offset);
end;

function TCMVTextOverlay.Set_ShadowOffset(Offset: SYSINT): HResult;
  { Warning: The property ShadowOffset has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ShadowOffset := Offset;
  Result := S_OK;
end;

function TCMVTextOverlay.Get_Bold(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.Get_Bold(Enable);
end;

function TCMVTextOverlay.Set_Bold(Enable: WordBool): HResult;
  { Warning: The property Bold has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Bold := Enable;
  Result := S_OK;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TCMVTextOverlayProperties.Create(AServer: TCMVTextOverlay);
begin
  inherited Create;
  FServer := AServer;
end;

function TCMVTextOverlayProperties.GetDefaultInterface: IMVTextOverlay;
begin
  Result := FServer.DefaultInterface;
end;

function TCMVTextOverlayProperties.Get_Enable(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.Enable(Enable);
end;

function TCMVTextOverlayProperties.Set_Enable(Enable: WordBool): HResult;
  { Warning: The property Enable has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Enable := Enable;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_OverlayMode(out Mode: SYSINT): HResult;
begin
    Result := DefaultInterface.OverlayMode(Mode);
end;

function TCMVTextOverlayProperties.Set_OverlayMode(Mode: SYSINT): HResult;
  { Warning: The property OverlayMode has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.OverlayMode := Mode;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_PositionMode(out Mode: SYSINT): HResult;
begin
    Result := DefaultInterface.PositionMode(Mode);
end;

function TCMVTextOverlayProperties.Set_PositionMode(Mode: SYSINT): HResult;
  { Warning: The property PositionMode has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.PositionMode := Mode;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_XPosition(out X: SYSINT): HResult;
begin
    Result := DefaultInterface.XPosition(X);
end;

function TCMVTextOverlayProperties.Set_XPosition(X: SYSINT): HResult;
  { Warning: The property XPosition has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.XPosition := X;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_YPosition(out Y: SYSINT): HResult;
begin
    Result := DefaultInterface.YPosition(Y);
end;

function TCMVTextOverlayProperties.Set_YPosition(Y: SYSINT): HResult;
  { Warning: The property YPosition has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.YPosition := Y;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_RelativePosition(out Pos: SYSINT): HResult;
begin
    Result := DefaultInterface.RelativePosition[Pos];
end;

function TCMVTextOverlayProperties.Set_RelativePosition(Pos: SYSINT): HResult;
  { Warning: The property RelativePosition has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.RelativePosition := Pos;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_TransparentBack(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.TransparentBack[Enable];
end;

function TCMVTextOverlayProperties.Set_TransparentBack(Enable: WordBool): HResult;
  { Warning: The property TransparentBack has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.TransparentBack := Enable;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_BackgroundColor(out Colour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.BackgroundColor[Colour];
end;

function TCMVTextOverlayProperties.Set_BackgroundColor(Colour: OLE_COLOR): HResult;
  { Warning: The property BackgroundColor has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.BackgroundColor := Colour;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_ForegroundColor(out Colour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.ForegroundColor[Colour];
end;

function TCMVTextOverlayProperties.Set_ForegroundColor(Colour: OLE_COLOR): HResult;
  { Warning: The property ForegroundColor has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ForegroundColor := Colour;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_Text(out Text: WideString): HResult;
begin
    Result := DefaultInterface.Text[Text];
end;

function TCMVTextOverlayProperties.Set_Text(const Text: WideString): HResult;
  { Warning: The property Text has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Text := Text;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_FontSize(out Height: SYSINT): HResult;
begin
    Result := DefaultInterface.FontSize[Height];
end;

function TCMVTextOverlayProperties.Set_FontSize(Height: SYSINT): HResult;
  { Warning: The property FontSize has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FontSize := Height;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_FontTypeFace(out TypeFace: WideString): HResult;
begin
    Result := DefaultInterface.FontTypeFace[TypeFace];
end;

function TCMVTextOverlayProperties.Set_FontTypeFace(const TypeFace: WideString): HResult;
  { Warning: The property FontTypeFace has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FontTypeFace := TypeFace;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_xMargin(out xMargin: SYSINT): HResult;
begin
    Result := DefaultInterface.xMargin[xMargin];
end;

function TCMVTextOverlayProperties.Set_xMargin(xMargin: SYSINT): HResult;
  { Warning: The property xMargin has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.xMargin := xMargin;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_yMargin(out yMargin: SYSINT): HResult;
begin
    Result := DefaultInterface.yMargin[yMargin];
end;

function TCMVTextOverlayProperties.Set_yMargin(yMargin: SYSINT): HResult;
  { Warning: The property yMargin has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.yMargin := yMargin;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_Shadow(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.Shadow[Enable];
end;

function TCMVTextOverlayProperties.Set_Shadow(Enable: WordBool): HResult;
  { Warning: The property Shadow has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Shadow := Enable;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_ShadowColor(out Colour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.ShadowColor[Colour];
end;

function TCMVTextOverlayProperties.Set_ShadowColor(Colour: OLE_COLOR): HResult;
  { Warning: The property ShadowColor has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ShadowColor := Colour;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_ShadowOffset(out Offset: SYSINT): HResult;
begin
    Result := DefaultInterface.ShadowOffset[Offset];
end;

function TCMVTextOverlayProperties.Set_ShadowOffset(Offset: SYSINT): HResult;
  { Warning: The property ShadowOffset has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ShadowOffset := Offset;
  Result := S_OK;
end;

function TCMVTextOverlayProperties.Get_Bold(out Enable: WordBool): HResult;
begin
    Result := DefaultInterface.Bold[Enable];
end;

function TCMVTextOverlayProperties.Set_Bold(Enable: WordBool): HResult;
  { Warning: The property Bold has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Bold := Enable;
  Result := S_OK;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TCMVTextOverlay]);
end;

end.
