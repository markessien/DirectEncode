unit MVBitmapOverlay_TLB;

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
// File generated on 2006-09-13 15:55:07 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\MontiVision\MontiVision Development Kit\bin\filter\bitmapoverlay.ax (1)
// LIBID: {775A8A6E-6D5F-4286-A098-D9329CD7851C}
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
  MVBitmapOverlayMajorVersion = 1;
  MVBitmapOverlayMinorVersion = 0;

  LIBID_MVBitmapOverlay: TGUID = '{775A8A6E-6D5F-4286-A098-D9329CD7851C}';

  IID_IMVBitmapOverlay: TGUID = '{6076BCD1-8DD6-4130-BFDA-1B6CEA72B07D}';
  IID_IMVFilterData: TGUID = '{5125ADE2-346C-4ECF-B8D5-10F1E550B44D}';
  IID_IMVFilterInfo: TGUID = '{A60D8C9D-A16B-4E80-BB7B-252CEA4B7B70}';
  IID_IMVAbout: TGUID = '{3D20EE29-5605-4FDD-B5AF-5BDBB60DC5C2}';
  IID_IMVHistogram: TGUID = '{B5F515BB-FA84-439C-90B9-3744CEC8100D}';
  IID_IMVHistogram2: TGUID = '{A2CC0FD6-58C6-4649-9062-1099EA03631A}';
  IID_IMVHistogram3: TGUID = '{7E58B6FA-275B-4EEB-93FB-67071E65A061}';
  IID_IMVRegionOfInterest: TGUID = '{5E00EF26-9DF7-4A25-9B7C-369683C6965A}';
  IID_IMVFilterEvents: TGUID = '{9C33ECD8-33C1-4A37-9076-AAD099F7778B}';
  CLASS_CMVBitmapOverlay: TGUID = '{BCD86F44-429E-4545-88D7-8E0D53F3AD30}';

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

// Constants for enum _MV_GDI_OVERLAY_MODE
type
  _MV_GDI_OVERLAY_MODE = TOleEnum;
const
  MV_GDI_OVERLAY_TRANSPARENT = $00000000;
  MV_GDI_OVERLAY_CONSTANTALPHA = $00000001;
  MV_GDI_OVERLAY_TRANSPARENT_AND_CONSTANTALPHA = $00000002;

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
  IMVBitmapOverlay = interface;
  IMVFilterData = interface;
  IMVFilterInfo = interface;
  IMVAbout = interface;
  IMVHistogram = interface;
  IMVHistogram2 = interface;
  IMVHistogram3 = interface;
  IMVRegionOfInterest = interface;
  IMVFilterEvents = interface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  CMVBitmapOverlay = IMVBitmapOverlay;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//
  PByte1 = ^Byte; {*}

  PrivateAlias1 = array[0..255] of SYSINT; {*}

// *********************************************************************//
// Interface: IMVBitmapOverlay
// Flags:     (0)
// GUID:      {6076BCD1-8DD6-4130-BFDA-1B6CEA72B07D}
// *********************************************************************//
  IMVBitmapOverlay = interface(IUnknown)
    ['{6076BCD1-8DD6-4130-BFDA-1B6CEA72B07D}']
    function Get_Enabled(out Enabled: WordBool): HResult; stdcall;
    function Set_Enabled(Enabled: WordBool): HResult; stdcall;
    function Get_Mode(out piMode: SYSINT): HResult; stdcall;
    function Set_Mode(piMode: SYSINT): HResult; stdcall;
    function Get_InputAlpha(out InputAlpha: Integer): HResult; stdcall;
    function Set_InputAlpha(InputAlpha: Integer): HResult; stdcall;
    function Get_TransparentColour(out plColour: OLE_COLOR): HResult; stdcall;
    function Set_TransparentColour(plColour: OLE_COLOR): HResult; stdcall;
    function Get_PositionMode(out Mode: SYSINT): HResult; stdcall;
    function Set_PositionMode(Mode: SYSINT): HResult; stdcall;
    function Get_XPosition(out X: SYSINT): HResult; stdcall;
    function Set_XPosition(X: SYSINT): HResult; stdcall;
    function Get_YPosition(out Y: SYSINT): HResult; stdcall;
    function Set_YPosition(Y: SYSINT): HResult; stdcall;
    function Get_RelativePosition(out Pos: SYSINT): HResult; stdcall;
    function Set_RelativePosition(Pos: SYSINT): HResult; stdcall;
    function Get_ResizeEnabled(out ResizeEnabled: WordBool): HResult; stdcall;
    function Set_ResizeEnabled(ResizeEnabled: WordBool): HResult; stdcall;
    function Get_AspectRatio(out AspectRatio: WordBool): HResult; stdcall;
    function Set_AspectRatio(AspectRatio: WordBool): HResult; stdcall;
    function Get_OriginalHeight(out OriginalHeight: SYSINT): HResult; stdcall;
    function Get_OriginalWidth(out OriginalWidth: SYSINT): HResult; stdcall;
    function Get_ResizeHeight(out ResizeHeight: SYSINT): HResult; stdcall;
    function Set_ResizeHeight(ResizeHeight: SYSINT): HResult; stdcall;
    function Get_ResizeWidth(out ResizeWidth: SYSINT): HResult; stdcall;
    function Set_ResizeWidth(ResizeWidth: SYSINT): HResult; stdcall;
    function Get_BitmapPath(out BitmapPath: WideString): HResult; stdcall;
    function Set_BitmapPath(const BitmapPath: WideString): HResult; stdcall;
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
// Interface: IMVRegionOfInterest
// Flags:     (0)
// GUID:      {5E00EF26-9DF7-4A25-9B7C-369683C6965A}
// *********************************************************************//
  IMVRegionOfInterest = interface(IUnknown)
    ['{5E00EF26-9DF7-4A25-9B7C-369683C6965A}']
    function GetROISupportInput(out piSupported: SYSINT): HResult; stdcall;
    function GetROISupportOutput(out piSupported: SYSINT): HResult; stdcall;
    function Get_SelectedROIPin(out piActualPin: SYSINT): HResult; stdcall;
    function Set_SelectedROIPin(piActualPin: SYSINT): HResult; stdcall;
    function Get_ROIPinDirection(out piPinDirection: SYSINT): HResult; stdcall;
    function Set_ROIPinDirection(piPinDirection: SYSINT): HResult; stdcall;
    function GetROI(out piXOffset: SYSINT; out piYOffset: SYSINT; out piWidth: SYSINT; 
                    out piHeight: SYSINT): HResult; stdcall;
    function PutROI(iXOffset: SYSINT; iYOffset: SYSINT; iWidth: SYSINT; iHeight: SYSINT): HResult; stdcall;
    function GetCOISupportInfo(out piCOI: SYSINT): HResult; stdcall;
    function Get_COI(out piChannel: SYSINT): HResult; stdcall;
    function Set_COI(piChannel: SYSINT): HResult; stdcall;
    function Get_CopyBackground(out piBackground: SYSINT): HResult; stdcall;
    function Set_CopyBackground(piBackground: SYSINT): HResult; stdcall;
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
// The Class CoCMVBitmapOverlay provides a Create and CreateRemote method to          
// create instances of the default interface IMVBitmapOverlay exposed by              
// the CoClass CMVBitmapOverlay. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoCMVBitmapOverlay = class
    class function Create: IMVBitmapOverlay;
    class function CreateRemote(const MachineName: string): IMVBitmapOverlay;
  end;

  TCMVBitmapOverlayMVFilterMessage = procedure(Sender: TObject; iMessage: SYSINT) of object;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TCMVBitmapOverlay
// Help String      : MontiVision Bitmap Overlay Class
// Default Interface: IMVBitmapOverlay
// Def. Intf. DISP? : No
// Event   Interface: IMVFilterEvents
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TCMVBitmapOverlayProperties= class;
{$ENDIF}
  TCMVBitmapOverlay = class(TOleServer)
  private
    FOnMVFilterMessage: TCMVBitmapOverlayMVFilterMessage;
    FIntf:        IMVBitmapOverlay;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TCMVBitmapOverlayProperties;
    function      GetServerProperties: TCMVBitmapOverlayProperties;
{$ENDIF}
    function      GetDefaultInterface: IMVBitmapOverlay;
  protected
    procedure InitServerData; override;
    procedure InvokeEvent(DispID: TDispID; var Params: TVariantArray); override;
    function Get_Enabled(out Enabled: WordBool): HResult;
    function Set_Enabled(Enabled: WordBool): HResult;
    function Get_Mode(out piMode: SYSINT): HResult;
    function Set_Mode(piMode: SYSINT): HResult;
    function Get_InputAlpha(out InputAlpha: Integer): HResult;
    function Set_InputAlpha(InputAlpha: Integer): HResult;
    function Get_TransparentColour(out plColour: OLE_COLOR): HResult;
    function Set_TransparentColour(plColour: OLE_COLOR): HResult;
    function Get_PositionMode(out Mode: SYSINT): HResult;
    function Set_PositionMode(Mode: SYSINT): HResult;
    function Get_XPosition(out X: SYSINT): HResult;
    function Set_XPosition(X: SYSINT): HResult;
    function Get_YPosition(out Y: SYSINT): HResult;
    function Set_YPosition(Y: SYSINT): HResult;
    function Get_RelativePosition(out Pos: SYSINT): HResult;
    function Set_RelativePosition(Pos: SYSINT): HResult;
    function Get_ResizeEnabled(out ResizeEnabled: WordBool): HResult;
    function Set_ResizeEnabled(ResizeEnabled: WordBool): HResult;
    function Get_AspectRatio(out AspectRatio: WordBool): HResult;
    function Set_AspectRatio(AspectRatio: WordBool): HResult;
    function Get_OriginalHeight(out OriginalHeight: SYSINT): HResult;
    function Get_OriginalWidth(out OriginalWidth: SYSINT): HResult;
    function Get_ResizeHeight(out ResizeHeight: SYSINT): HResult;
    function Set_ResizeHeight(ResizeHeight: SYSINT): HResult;
    function Get_ResizeWidth(out ResizeWidth: SYSINT): HResult;
    function Set_ResizeWidth(ResizeWidth: SYSINT): HResult;
    function Get_BitmapPath(out BitmapPath: WideString): HResult;
    function Set_BitmapPath(const BitmapPath: WideString): HResult;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IMVBitmapOverlay);
    procedure Disconnect; override;
    property DefaultInterface: IMVBitmapOverlay read GetDefaultInterface;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TCMVBitmapOverlayProperties read GetServerProperties;
{$ENDIF}
    property OnMVFilterMessage: TCMVBitmapOverlayMVFilterMessage read FOnMVFilterMessage write FOnMVFilterMessage;
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TCMVBitmapOverlay
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TCMVBitmapOverlayProperties = class(TPersistent)
  private
    FServer:    TCMVBitmapOverlay;
    function    GetDefaultInterface: IMVBitmapOverlay;
    constructor Create(AServer: TCMVBitmapOverlay);
  protected
    function Get_Enabled(out Enabled: WordBool): HResult;
    function Set_Enabled(Enabled: WordBool): HResult;
    function Get_Mode(out piMode: SYSINT): HResult;
    function Set_Mode(piMode: SYSINT): HResult;
    function Get_InputAlpha(out InputAlpha: Integer): HResult;
    function Set_InputAlpha(InputAlpha: Integer): HResult;
    function Get_TransparentColour(out plColour: OLE_COLOR): HResult;
    function Set_TransparentColour(plColour: OLE_COLOR): HResult;
    function Get_PositionMode(out Mode: SYSINT): HResult;
    function Set_PositionMode(Mode: SYSINT): HResult;
    function Get_XPosition(out X: SYSINT): HResult;
    function Set_XPosition(X: SYSINT): HResult;
    function Get_YPosition(out Y: SYSINT): HResult;
    function Set_YPosition(Y: SYSINT): HResult;
    function Get_RelativePosition(out Pos: SYSINT): HResult;
    function Set_RelativePosition(Pos: SYSINT): HResult;
    function Get_ResizeEnabled(out ResizeEnabled: WordBool): HResult;
    function Set_ResizeEnabled(ResizeEnabled: WordBool): HResult;
    function Get_AspectRatio(out AspectRatio: WordBool): HResult;
    function Set_AspectRatio(AspectRatio: WordBool): HResult;
    function Get_OriginalHeight(out OriginalHeight: SYSINT): HResult;
    function Get_OriginalWidth(out OriginalWidth: SYSINT): HResult;
    function Get_ResizeHeight(out ResizeHeight: SYSINT): HResult;
    function Set_ResizeHeight(ResizeHeight: SYSINT): HResult;
    function Get_ResizeWidth(out ResizeWidth: SYSINT): HResult;
    function Set_ResizeWidth(ResizeWidth: SYSINT): HResult;
    function Get_BitmapPath(out BitmapPath: WideString): HResult;
    function Set_BitmapPath(const BitmapPath: WideString): HResult;
  public
    property DefaultInterface: IMVBitmapOverlay read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

implementation

uses ComObj;

class function CoCMVBitmapOverlay.Create: IMVBitmapOverlay;
begin
  Result := CreateComObject(CLASS_CMVBitmapOverlay) as IMVBitmapOverlay;
end;

class function CoCMVBitmapOverlay.CreateRemote(const MachineName: string): IMVBitmapOverlay;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_CMVBitmapOverlay) as IMVBitmapOverlay;
end;

procedure TCMVBitmapOverlay.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{BCD86F44-429E-4545-88D7-8E0D53F3AD30}';
    IntfIID:   '{6076BCD1-8DD6-4130-BFDA-1B6CEA72B07D}';
    EventIID:  '{9C33ECD8-33C1-4A37-9076-AAD099F7778B}';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TCMVBitmapOverlay.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    ConnectEvents(punk);
    Fintf:= punk as IMVBitmapOverlay;
  end;
end;

procedure TCMVBitmapOverlay.ConnectTo(svrIntf: IMVBitmapOverlay);
begin
  Disconnect;
  FIntf := svrIntf;
  ConnectEvents(FIntf);
end;

procedure TCMVBitmapOverlay.DisConnect;
begin
  if Fintf <> nil then
  begin
    DisconnectEvents(FIntf);
    FIntf := nil;
  end;
end;

function TCMVBitmapOverlay.GetDefaultInterface: IMVBitmapOverlay;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TCMVBitmapOverlay.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TCMVBitmapOverlayProperties.Create(Self);
{$ENDIF}
end;

destructor TCMVBitmapOverlay.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TCMVBitmapOverlay.GetServerProperties: TCMVBitmapOverlayProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TCMVBitmapOverlay.InvokeEvent(DispID: TDispID; var Params: TVariantArray);
begin
  case DispID of
    -1: Exit;  // DISPID_UNKNOWN
(*{The DispID for this method is DISPID_UNKNOWN!?. }
   -1: if Assigned(FOnMVFilterMessage) then
            FOnMVFilterMessage(Self, Params[0] {SYSINT});
*)
  end; {case DispID}
end;

function TCMVBitmapOverlay.Get_Enabled(out Enabled: WordBool): HResult;
begin
    Result := DefaultInterface.Get_Enabled(Enabled);
end;

function TCMVBitmapOverlay.Set_Enabled(Enabled: WordBool): HResult;
  { Warning: The property Enabled has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Enabled := Enabled;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_Mode(out piMode: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_Mode(piMode);
end;

function TCMVBitmapOverlay.Set_Mode(piMode: SYSINT): HResult;
  { Warning: The property Mode has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Mode := piMode;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_InputAlpha(out InputAlpha: Integer): HResult;
begin
    Result := DefaultInterface.Get_InputAlpha(InputAlpha);
end;

function TCMVBitmapOverlay.Set_InputAlpha(InputAlpha: Integer): HResult;
  { Warning: The property InputAlpha has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.InputAlpha := InputAlpha;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_TransparentColour(out plColour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.Get_TransparentColour(plColour);
end;

function TCMVBitmapOverlay.Set_TransparentColour(plColour: OLE_COLOR): HResult;
  { Warning: The property TransparentColour has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.TransparentColour := plColour;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_PositionMode(out Mode: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_PositionMode(Mode);
end;

function TCMVBitmapOverlay.Set_PositionMode(Mode: SYSINT): HResult;
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

function TCMVBitmapOverlay.Get_XPosition(out X: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_XPosition(X);
end;

function TCMVBitmapOverlay.Set_XPosition(X: SYSINT): HResult;
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

function TCMVBitmapOverlay.Get_YPosition(out Y: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_YPosition(Y);
end;

function TCMVBitmapOverlay.Set_YPosition(Y: SYSINT): HResult;
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

function TCMVBitmapOverlay.Get_RelativePosition(out Pos: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_RelativePosition(Pos);
end;

function TCMVBitmapOverlay.Set_RelativePosition(Pos: SYSINT): HResult;
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

function TCMVBitmapOverlay.Get_ResizeEnabled(out ResizeEnabled: WordBool): HResult;
begin
    Result := DefaultInterface.Get_ResizeEnabled(ResizeEnabled);
end;

function TCMVBitmapOverlay.Set_ResizeEnabled(ResizeEnabled: WordBool): HResult;
  { Warning: The property ResizeEnabled has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ResizeEnabled := ResizeEnabled;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_AspectRatio(out AspectRatio: WordBool): HResult;
begin
    Result := DefaultInterface.Get_AspectRatio(AspectRatio);
end;

function TCMVBitmapOverlay.Set_AspectRatio(AspectRatio: WordBool): HResult;
  { Warning: The property AspectRatio has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.AspectRatio := AspectRatio;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_OriginalHeight(out OriginalHeight: SYSINT): HResult;
begin
    Result := DefaultInterface.get_OriginalHeight(OriginalHeight);
end;

function TCMVBitmapOverlay.Get_OriginalWidth(out OriginalWidth: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_OriginalWidth(OriginalWidth);
end;

function TCMVBitmapOverlay.Get_ResizeHeight(out ResizeHeight: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_ResizeHeight(ResizeHeight);
end;

function TCMVBitmapOverlay.Set_ResizeHeight(ResizeHeight: SYSINT): HResult;
  { Warning: The property ResizeHeight has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ResizeHeight := ResizeHeight;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_ResizeWidth(out ResizeWidth: SYSINT): HResult;
begin
    Result := DefaultInterface.Get_ResizeWidth(ResizeWidth);
end;

function TCMVBitmapOverlay.Set_ResizeWidth(ResizeWidth: SYSINT): HResult;
  { Warning: The property ResizeWidth has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ResizeWidth := ResizeWidth;
  Result := S_OK;
end;

function TCMVBitmapOverlay.Get_BitmapPath(out BitmapPath: WideString): HResult;
begin
    Result := DefaultInterface.Get_BitmapPath(BitmapPath);
end;

function TCMVBitmapOverlay.Set_BitmapPath(const BitmapPath: WideString): HResult;
  { Warning: The property BitmapPath has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.BitmapPath := BitmapPath;
  Result := S_OK;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TCMVBitmapOverlayProperties.Create(AServer: TCMVBitmapOverlay);
begin
  inherited Create;
  FServer := AServer;
end;

function TCMVBitmapOverlayProperties.GetDefaultInterface: IMVBitmapOverlay;
begin
  Result := FServer.DefaultInterface;
end;

function TCMVBitmapOverlayProperties.Get_Enabled(out Enabled: WordBool): HResult;
begin
    Result := DefaultInterface.Enabled[Enabled];
end;

function TCMVBitmapOverlayProperties.Set_Enabled(Enabled: WordBool): HResult;
  { Warning: The property Enabled has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Enabled := Enabled;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_Mode(out piMode: SYSINT): HResult;
begin
    Result := DefaultInterface.Mode[piMode];
end;

function TCMVBitmapOverlayProperties.Set_Mode(piMode: SYSINT): HResult;
  { Warning: The property Mode has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.Mode := piMode;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_InputAlpha(out InputAlpha: Integer): HResult;
begin
    Result := DefaultInterface.InputAlpha[InputAlpha];
end;

function TCMVBitmapOverlayProperties.Set_InputAlpha(InputAlpha: Integer): HResult;
  { Warning: The property InputAlpha has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.InputAlpha := InputAlpha;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_TransparentColour(out plColour: OLE_COLOR): HResult;
begin
    Result := DefaultInterface.TransparentColour[plColour];
end;

function TCMVBitmapOverlayProperties.Set_TransparentColour(plColour: OLE_COLOR): HResult;
  { Warning: The property TransparentColour has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.TransparentColour := plColour;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_PositionMode(out Mode: SYSINT): HResult;
begin
    Result := DefaultInterface.PositionMode[Mode];
end;

function TCMVBitmapOverlayProperties.Set_PositionMode(Mode: SYSINT): HResult;
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

function TCMVBitmapOverlayProperties.Get_XPosition(out X: SYSINT): HResult;
begin
    Result := DefaultInterface.XPosition[X];
end;

function TCMVBitmapOverlayProperties.Set_XPosition(X: SYSINT): HResult;
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

function TCMVBitmapOverlayProperties.Get_YPosition(out Y: SYSINT): HResult;
begin
    Result := DefaultInterface.YPosition[Y];
end;

function TCMVBitmapOverlayProperties.Set_YPosition(Y: SYSINT): HResult;
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

function TCMVBitmapOverlayProperties.Get_RelativePosition(out Pos: SYSINT): HResult;
begin
    Result := DefaultInterface.RelativePosition[Pos];
end;

function TCMVBitmapOverlayProperties.Set_RelativePosition(Pos: SYSINT): HResult;
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

function TCMVBitmapOverlayProperties.Get_ResizeEnabled(out ResizeEnabled: WordBool): HResult;
begin
    Result := DefaultInterface.ResizeEnabled[ResizeEnabled];
end;

function TCMVBitmapOverlayProperties.Set_ResizeEnabled(ResizeEnabled: WordBool): HResult;
  { Warning: The property ResizeEnabled has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ResizeEnabled := ResizeEnabled;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_AspectRatio(out AspectRatio: WordBool): HResult;
begin
    Result := DefaultInterface.AspectRatio[AspectRatio];
end;

function TCMVBitmapOverlayProperties.Set_AspectRatio(AspectRatio: WordBool): HResult;
  { Warning: The property AspectRatio has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.AspectRatio := AspectRatio;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_OriginalHeight(out OriginalHeight: SYSINT): HResult;
begin
    Result := DefaultInterface.OriginalHeight[OriginalHeight];
end;

function TCMVBitmapOverlayProperties.Get_OriginalWidth(out OriginalWidth: SYSINT): HResult;
begin
    Result := DefaultInterface.OriginalWidth[OriginalWidth];
end;

function TCMVBitmapOverlayProperties.Get_ResizeHeight(out ResizeHeight: SYSINT): HResult;
begin
    Result := DefaultInterface.ResizeHeight[ResizeHeight];
end;

function TCMVBitmapOverlayProperties.Set_ResizeHeight(ResizeHeight: SYSINT): HResult;
  { Warning: The property ResizeHeight has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ResizeHeight := ResizeHeight;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_ResizeWidth(out ResizeWidth: SYSINT): HResult;
begin
    Result := DefaultInterface.ResizeWidth[ResizeWidth];
end;

function TCMVBitmapOverlayProperties.Set_ResizeWidth(ResizeWidth: SYSINT): HResult;
  { Warning: The property ResizeWidth has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.ResizeWidth := ResizeWidth;
  Result := S_OK;
end;

function TCMVBitmapOverlayProperties.Get_BitmapPath(out BitmapPath: WideString): HResult;
begin
    Result := DefaultInterface.BitmapPath[BitmapPath];
end;

function TCMVBitmapOverlayProperties.Set_BitmapPath(const BitmapPath: WideString): HResult;
  { Warning: The property BitmapPath has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.BitmapPath := BitmapPath;
  Result := S_OK;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TCMVBitmapOverlay]);
end;

end.
