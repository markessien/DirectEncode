{******************************************************************************}
{*  MontiVision SDK 3.0 Delphi Interfaces                                     *}
{*                                                                            *}
{*  Common Filter Structures and Interfaces                                   *}
{*                                                                            *}
{*  Copyright 2002 - 2006, Ing.-Büro Cymontkowski. All Rights Reserved.       *}
{******************************************************************************}

//  Delphi translation by Alexey Ostrovsky (AMOSoftware@yahoo.com)            //

unit MVFilterCommon;

{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers.
{$WRITEABLECONST ON}
interface

uses Windows, ActiveX;

// *********************************************************************//
// Interfaces declared in this unit                                     //
// *********************************************************************//
const
	IID_IMVAbout: TGUID = '{3D20EE29-5605-4FDD-B5AF-5BDBB60DC5C2}';
	IID_IMVBlobPreProcessing: TGUID = '{6DE9F760-3413-4763-911E-DC6740B5EAA9}';
	IID_IMVCrypt: TGUID = '{E0D0E1B8-07B7-43B3-8F6A-F58F7A875823}';
	IID_IMVFilterData: TGUID = '{5125ADE2-346C-4ECF-B8D5-10F1E550B44D}';
	IID_IMVFilterEvents: TGUID = '{9C33ECD8-33C1-4A37-9076-AAD099F7778B}';
	IID_IMVFilterInfo: TGUID = '{A60D8C9D-A16B-4E80-BB7B-252CEA4B7B70}';
	IID_IMVHistogram: TGUID = '{B5F515BB-FA84-439C-90B9-3744CEC8100D}';
	IID_IMVHistogram2: TGUID = '{A2CC0FD6-58C6-4649-9062-1099EA03631A}';
    IID_IMVHistogram3: TGUID = '{7E58B6FA-275B-4EEB-93FB-67071E65A061}';
	IID_IMVImageCapture: TGUID = '{5A94641D-D027-481A-A1CD-FFD82ADE5A9A}';
	IID_IMVImageCapture2: TGUID = '{28F10FC7-B095-4A8F-89F5-29974BABD35D}';
	IID_IMVImageInfo: TGUID = '{D98D748F-38A3-49D6-8A6B-AD329B3044C5}';
	IID_IMVSetImageFormat: TGUID = '{88C6E1F2-1475-4735-BC64-8794A574B6F2}';
	IID_IMVRegionOfInterest: TGUID = '{5E00EF26-9DF7-4A25-9B7C-369683C6965A}';
	IID_IMVTrigger: TGUID = '{E458EE32-8997-4BBB-ACAF-E403325F19F0}';
    IID_IMVGrid: TGUID = '{F17DCAF8-8A96-43C6-B486-357703B144C8}';



// *********************************************************************//
// Declaration of constants                                             //
// *********************************************************************//
const
	MAX_KEY_LENGTH = 1024;
	MAX_BLOWFISH_KEY_LENGTH	= 56;
	MIN_BLOWFISH_KEY_LENGTH = 4;


// *********************************************************************//
// Declaration of enumerations                                          //
// *********************************************************************//
// Constants for enum _MV_COM_EVENTS
type
	_MV_COM_EVENTS = TOleEnum;
	MV_COM_EVENTS = _MV_COM_EVENTS;
	MV_FILTER_EVENTS = _MV_COM_EVENTS;      // for compatibility with Visual Basic code
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

// Constants for enum _MV_COLOR_CHANNEL
type
	_MV_COLOR_CHANNEL = TOleEnum;
	MV_COLOR_CHANNEL = _MV_COLOR_CHANNEL;
const
	MV_CHANNEL_ALL = $00000000;
	MV_CHANNEL_BLUE = $00000001;
	MV_CHANNEL_GREEN = $00000002;
	MV_CHANNEL_RED = $00000003;

// Constants for enum _MV_INTERPOLATION_MODE
type
	_MV_INTERPOLATION_MODE = TOleEnum;
	MV_INTERPOLATION_MODE = _MV_INTERPOLATION_MODE;
const
	MV_INTERPOLATION_NN = $00000000;
	MV_INTERPOLATION_LINEAR = $00000001;
	MV_INTERPOLATION_CUBIC = $00000002;

// Constants for enum _MV_NETWORK_PROTOCOL
type
	_MV_NETWORK_PROTOCOL = TOleEnum;
	MV_NETWORK_PROTOCOL = _MV_NETWORK_PROTOCOL;
const
	MV_NETWORK_PROTOCOL_UDP = $00000000;
	MV_NETWORK_PROTOCOL_TCP = $00000001;
	MV_NETWORK_PROTOCOL_RTP = $00000002;

// Constants for enum _MV_NETWORK_STATUS
type
	_MV_NETWORK_STATUS = TOleEnum;
	MV_NETWORK_STATUS = _MV_NETWORK_STATUS;
const
	MV_NETWORK_STATUS_IDLE = $00000000;
	MV_NETWORK_STATUS_SEND_MEDIATYPE = $00000001;
	MV_NETWORK_STATUS_SEND_STREAM = $00000002;
	MV_NETWORK_STATUS_RECEIVE_MEDIATYPE = $00000003;
	MV_NETWORK_STATUS_RECEIVE_STREAM = $00000004;

// Specific to IMVCrypt                 //
// ==================================== //
// Constants for enum _MV_CRYPTO_ALGORITHM
type
	_MV_CRYPTO_ALGORITHM = TOleEnum;
	MV_CRYPTO_ALGORITHM = _MV_CRYPTO_ALGORITHM;
const
	MV_CRYPTO_ALGORITHM_AES	= 0;
	MV_CRYPTO_ALGORITHM_BLOWFISH = MV_CRYPTO_ALGORITHM_AES + 1;
	MV_CRYPTO_ALGORITHM_TEA = MV_CRYPTO_ALGORITHM_BLOWFISH + 1;

// Constants for enum _MV_CRYPTO_PADDING
type
	_MV_CRYPTO_MODE = TOleEnum;
	MV_CRYPTO_MODE = _MV_CRYPTO_MODE;
const
	MV_CRYPTO_MODE_ECB	= 0;
	MV_CRYPTO_MODE_CBC	= MV_CRYPTO_MODE_ECB + 1;
	MV_CRYPTO_MODE_CFB	= MV_CRYPTO_MODE_CBC + 1;

// Constants for enum _MV_CRYPTO_PADDING
type
	_MV_CRYPTO_PADDING = TOleEnum;
	MV_CRYPTO_PADDING = _MV_CRYPTO_PADDING;
const
	MV_CRYPTO_PADDING_ZEROS	= 0;
	MV_CRYPTO_PADDING_BLANKS	= MV_CRYPTO_PADDING_ZEROS + 1;
	MV_CRYPTO_PADDING_PKCS7	= MV_CRYPTO_PADDING_BLANKS + 1;

// Specific to IMVImageCapture         //
// =================================== //
// Constants for enum _MV_FILEFORMAT_TYPE
type
	_MV_FILEFORMAT_TYPE = TOleEnum;
	MV_FILEFORMAT_TYPE = _MV_FILEFORMAT_TYPE;
const
	MV_FILEFORMAT_BITMAP = $00000000;
	MV_FILEFORMAT_JPEG = $00000001;
	MV_FILEFORMAT_TIFF = $00000002;
	MV_FILEFORMAT_PNG = $00000003;

// Constants for enum _MV_JPEG_COMPRESSION
type
	_MV_JPEG_COMPRESSION = TOleEnum;
	MV_JPEG_COMPRESSION = _MV_JPEG_COMPRESSION;
const
	MV_JPEG_QUALITY_HIGHEST = $00000000;
	MV_JPEG_QUALITY_HIGH = $00000001;
	MV_JPEG_QUALITY_STANDARD = $00000002;
	MV_JPEG_QUALITY_LOW = $00000003;
	MV_JPEG_QUALITY_LOWEST = $00000004;

// Constants for enum _MV_NAMECREATION
type
	_MV_NAMECREATION = TOleEnum;
	MV_NAMECREATION = _MV_NAMECREATION;
const
	MV_NAMECRATION_FIXED = $00000000;
	MV_NAMECREATION_TEMPLATE = $00000001;

// Specific to IMVBlobXXXX                //
// ====================================== //
// Constants for enum _MV_BLOB_EDGEDETECTION
type
	_MV_BLOB_EDGEDETECTION = TOleEnum;
const
	MV_BLOB_EDGES_NONE = $00000000;
	MV_BLOB_EDGES_SOBEL = $00000001;
	MV_BLOB_EDGES_LAPLACE = $00000002;
	MV_BLOB_EDGES_SCHARR = $00000003;
	MV_BLOB_EDGES_ROBERTS = $00000004;

// Constants for enum _MV_BLOB_PROPERTIES
type
	_MV_BLOB_PROPERTIES = TOleEnum;
const
	MV_BRIGHT_BLOBS = $00000000;
	MV_DARK_BLOBS = $00000001;
    
type
    _MV_GDI_OVERLAY_MODE = TOleEnum;
    MV_GDI_OVERLAY_MODE = _MV_GDI_OVERLAY_MODE;
const
  MV_GDI_OVERLAY_TRANSPARENT = $00000000;
  MV_GDI_OVERLAY_CONSTANTALPHA = $00000001;
  MV_GDI_OVERLAY_TRANSPARENT_AND_CONSTANTALPHA = $00000002;
    
// Constants for enum _MV_TEXT_OVERLAY_MODE
type
    _MV_TEXT_OVERLAY_MODE = TOleEnum;
    MV_TEXT_OVERLAY_MODE = _MV_TEXT_OVERLAY_MODE;
const
  MV_TEXT_OVERLAY_MODE_TEXT = $00000000;
  MV_TEXT_OVERLAY_MODE_DATE = $00000001;

// Constants for enum _MV_POSITION_MODE
type
    _MV_POSITION_MODE = TOleEnum;
    MV_POSITION_MODE = _MV_POSITION_MODE;
const
  MV_POSITION_RELATIVE = $00000000;
  MV_POSITION_ABSOLUTE = $00000001;

// Constants for enum _MV_RELATIVE_POSITION
type
    _MV_RELATIVE_POSITION = TOleEnum;
    MV_RELATIVE_POSITION = _MV_RELATIVE_POSITION;
const
  MV_POSITION_UPPER_LEFT = $00000000;
  MV_POSITION_UPPER_RIGHT = $00000001;
  MV_POSITION_LOWER_RIGHT = $00000002;
  MV_POSITION_LOWER_LEFT = $00000003;
  MV_POSITION_TOP = $00000004;
  MV_POSITION_BOTTOM = $00000005;


// *********************************************************************//
// Declaration of structures                                            //
// *********************************************************************//
type
	_MV_BITMAP_HEADER = packed record
		biSize: LongWord;
		biWidth: Integer;
		biHeight: Integer;
		biPlanes: Word;
		biBitCount: Word;
		biCompression: LongWord;
		biSizeImage: LongWord;
		biXPelsPerMeter: Integer;
		biYPelsPerMeter: Integer;
		biClrUsed: LongWord;
		biClrImportant: LongWord;
	end;
	MV_BITMAP_HEADER = _MV_BITMAP_HEADER;

	_MV_RGB_VALUE = packed record
		MV_Blue: Byte;
		MV_Green: Byte;
		MV_Red: Byte;
		MV_Reserved: Byte;
	end;
	MV_RGB_VALUE = _MV_RGB_VALUE;

	_MV_BITMAP = packed record
		MV_BM_Header: MV_BITMAP_HEADER;
		MV_BM_ColorTable: array[0..255] of MV_RGB_VALUE;
		MV_BM_Data: ^Byte;
	end;
	MV_BITMAP = _MV_BITMAP;

	// Structures specific to IMVBlobFinder and IMVBlobCounter
	_MV_HU_MOMENTS = packed record
		hu1: Double;
		hu2: Double;
		hu3: Double;
		hu4: Double;
		hu5: Double;
		hu6: Double;
		hu7: Double;
	end;
	MV_HU_MOMENTS = _MV_HU_MOMENTS;

	_MV_MOMENTS = packed record
		m00: Double;
		m10: Double;
		m01: Double;
		m20: Double;
		m11: Double;
		m02: Double;
		m30: Double;
		m21: Double;
		m12: Double;
		m03: Double;
		mu20: Double;
		mu11: Double;
		mu02: Double;
		mu30: Double;
		mu21: Double;
		mu12: Double;
		mu03: Double;
		inv_sqrt_m00: Double;
	end;
	MV_MOMENTS = _MV_MOMENTS;

	_MV_RECT = packed record
		x: SYSINT;
		y: SYSINT;
		Width: SYSINT;
		Height: SYSINT;
	end;
	MV_RECT = _MV_RECT;

	_MV_POINT = packed record
		x: SYSINT;
		y: SYSINT;
	end;
	MV_POINT = _MV_POINT;

	// Structures specific to IIntIOSource, IIntIOSource2 and IIOIntRenderer
	_IO_INT_VALUE = record
		case Integer of
			0: (uint8: Byte);
			1: (int8: Shortint);
			2: (uint16: Word);
			3: (int16: Smallint);
			4: (uint32: SYSUINT);
			5: (int32: SYSINT);
			6: (uint64: Largeuint);
			7: (int64: Int64);
	end;
	IO_INT_VALUE = _IO_INT_VALUE;

type
	PByte1 = ^Byte; {*}
  PPSafeArray1 = ^PSafeArray; {*}
	PrivateAlias1 = array[0..255] of SYSINT; {*}
	PrivateAlias2 = array[0..3] of _MV_POINT; {*}
	PUserType1 = ^_MV_HU_MOMENTS; {*}


// *********************************************************************//
// Declaration of interfaces                                            //
// *********************************************************************//

type
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
// Interface: IMVBlobPreProcessing
// Flags:     (0)
// GUID:      {6DE9F760-3413-4763-911E-DC6740B5EAA9}
// *********************************************************************//
	IMVBlobPreProcessing = interface(IUnknown)
		['{6DE9F760-3413-4763-911E-DC6740B5EAA9}']
		function Get_SegmentationThreshold(out pbyThreshold: Byte): HResult; stdcall;
		function Set_SegmentationThreshold(pbyThreshold: Byte): HResult; stdcall;
		function Get_EdgeDetection(out piEdgeDetection: SYSINT): HResult; stdcall;
		function Set_EdgeDetection(piEdgeDetection: SYSINT): HResult; stdcall;
		function Get_BlobType(out piProperties: SYSINT): HResult; stdcall;
		function Set_BlobType(piProperties: SYSINT): HResult; stdcall;
		function Get_DrawSegmentation(out Draw: WordBool): HResult; stdcall;
		function Set_DrawSegmentation(Draw: WordBool): HResult; stdcall;
	end;

// *********************************************************************//
// Interface: IMVCrypt
// Flags:     (0)
// GUID:      {E0D0E1B8-07B7-43B3-8F6A-F58F7A875823}
// *********************************************************************//
	IMVCrypt = interface(IUnknown)
		['{E0D0E1B8-07B7-43B3-8F6A-F58F7A875823}']
		function Get_Enable(out Enable: SYSINT): HResult; stdcall;
		function Set_Enable(Enable: SYSINT): HResult; stdcall;
		function Get_Mode(out Mode: SYSINT): HResult; stdcall;
		function Set_Mode(Mode: SYSINT): HResult; stdcall;
		function Get_Algorithm(out Algorithm: SYSINT): HResult; stdcall;
		function Set_Algorithm(Algorithm: SYSINT): HResult; stdcall;
		function Get_KeyLength(out length: SYSINT): HResult; stdcall;
		function Set_KeyLength(length: SYSINT): HResult; stdcall;
		function Get_Padding(out Padding: SYSINT): HResult; stdcall;
		function Set_Padding(Padding: SYSINT): HResult; stdcall;
		function Get_UseKeyFile(out flag: SYSINT): HResult; stdcall;
		function Set_UseKeyFile(flag: SYSINT): HResult; stdcall;
		function Get_KeyFilePath(out path: WideString): HResult; stdcall;
		function Set_KeyFilePath(const path: WideString): HResult; stdcall;
		function CreateKeyfile(const path: WideString): HResult; stdcall;
		function OpenKeyfile(const path: WideString): HResult; stdcall;
		function CreateKey: HResult; stdcall;
		function GetKey(maxLength: SYSINT; out length: SYSINT; out key: Byte): HResult; stdcall;
		function SetKey(length: SYSINT; var key: Byte): HResult; stdcall;
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
// Interface: IMVFilterEvents
// Flags:     (256) OleAutomation
// GUID:      {9C33ECD8-33C1-4A37-9076-AAD099F7778B}
// *********************************************************************//
	IMVFilterEvents = interface(IUnknown)
		['{9C33ECD8-33C1-4A37-9076-AAD099F7778B}']
		function MVFilterMessage(iMessage: SYSINT): HResult; stdcall;
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
// Interface: IMVImageCapture
// Flags:     (0)
// GUID:      {5A94641D-D027-481A-A1CD-FFD82ADE5A9A}
// *********************************************************************//
  IMVImageCapture = interface(IUnknown)
    ['{5A94641D-D027-481A-A1CD-FFD82ADE5A9A}']
    function Get_NameCreationMethod(out piMethod: SYSINT): HResult; stdcall;
    function Set_NameCreationMethod(piMethod: SYSINT): HResult; stdcall;
    function Get_FixedFileName(out pbstrFileName: WideString): HResult; stdcall;
    function Set_FixedFileName(const pbstrFileName: WideString): HResult; stdcall;
    function Get_OutputPath(out pbstrPath: WideString): HResult; stdcall;
    function Set_OutputPath(const pbstrPath: WideString): HResult; stdcall;
    function Get_OutputFileTemplate(out pbstrPath: WideString): HResult; stdcall;
    function Set_OutputFileTemplate(const pbstrPath: WideString): HResult; stdcall;
    function Get_FileFormat(out piFormat: SYSINT): HResult; stdcall;
    function Set_FileFormat(piFormat: SYSINT): HResult; stdcall;
    function ResetImageCounter: HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVImageCapture2
// Flags:     (0)
// GUID:      {28F10FC7-B095-4A8F-89F5-29974BABD35D}
// *********************************************************************//
  IMVImageCapture2 = interface(IMVImageCapture)
    ['{28F10FC7-B095-4A8F-89F5-29974BABD35D}']
    function Get_OutputWidth(out piWidth: SYSINT): HResult; stdcall;
    function Set_OutputWidth(piWidth: SYSINT): HResult; stdcall;
    function Get_OutputHeight(out piHeight: SYSINT): HResult; stdcall;
    function Set_OutputHeight(piHeight: SYSINT): HResult; stdcall;
    function GetCaptureRegion(out piXOffset: SYSINT; out piYOffset: SYSINT; out piWidth: SYSINT; 
                              out piHeight: SYSINT): HResult; stdcall;
    function PutCaptureRegion(iXOffset: SYSINT; iYOffset: SYSINT; iWidth: SYSINT; iHeight: SYSINT): HResult; stdcall;
    function Get_Interpolation(out piMode: SYSINT): HResult; stdcall;
    function Set_Interpolation(piMode: SYSINT): HResult; stdcall;
    function Get_JpegQuality(out piQuality: SYSINT): HResult; stdcall;
    function Set_JpegQuality(piQuality: SYSINT): HResult; stdcall;
    function Get_Overwrite(out piOverwrite: SYSINT): HResult; stdcall;
    function Set_Overwrite(piOverwrite: SYSINT): HResult; stdcall;
    function Get_DontWriteFiles(out piNoFiles: SYSINT): HResult; stdcall;
    function Set_DontWriteFiles(piNoFiles: SYSINT): HResult; stdcall;
    function GetCurrentBitmap(out piWidth: SYSINT; out piHeight: SYSINT; out piBitCount: SYSINT; 
                              out piSize: SYSINT; out pbyData: Integer): HResult; stdcall;
    function Get_DrawTimeStamp(out piDraw: SYSINT): HResult; stdcall;
    function Set_DrawTimeStamp(piDraw: SYSINT): HResult; stdcall;
    function Get_DrawRegion(out piDraw: SYSINT): HResult; stdcall;
    function Set_DrawRegion(piDraw: SYSINT): HResult; stdcall;
    function ShowCurrentBitmap(hWnd: SYSINT): HResult; stdcall;
    function Get_DrawColour(out plColour: Integer): HResult; stdcall;
    function Set_DrawColour(plColour: Integer): HResult; stdcall;
    function Get_LineWidth(out piLineWidth: SYSINT): HResult; stdcall;
    function Set_LineWidth(piLineWidth: SYSINT): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVImageInfo
// Flags:     (0)
// GUID:      {D98D748F-38A3-49D6-8A6B-AD329B3044C5}
// *********************************************************************//
  IMVImageInfo = interface(IUnknown)
    ['{D98D748F-38A3-49D6-8A6B-AD329B3044C5}']
    function GetCurrentBitmap(cMax: SYSINT; out pbyBitmap: Byte): HResult; stdcall;
    function GetCurrentFileName(out pbstrFileName: WideString): HResult; stdcall;
  end;

// *********************************************************************//
// Interface: IMVSetImageFormat
// Flags:     (0)
// GUID:      {88C6E1F2-1475-4735-BC64-8794A574B6F2}
// *********************************************************************//
  IMVSetImageFormat = interface(IUnknown)
    ['{88C6E1F2-1475-4735-BC64-8794A574B6F2}']
    function SetImageFormat(Width: SYSINT; Height: SYSINT; depth: SYSINT): HResult; stdcall;
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
// Interface: IMVTrigger
// Flags:     (0)
// GUID:      {E458EE32-8997-4BBB-ACAF-E403325F19F0}
// *********************************************************************//
  IMVTrigger = interface(IUnknown)
    ['{E458EE32-8997-4BBB-ACAF-E403325F19F0}']
    function Get_UseTrigger(out piUseTrigger: SYSINT): HResult; stdcall;
    function Set_UseTrigger(piUseTrigger: SYSINT): HResult; stdcall;
    function Get_TriggerMode(out piTriggerMode: SYSINT): HResult; stdcall;
    function Set_TriggerMode(piTriggerMode: SYSINT): HResult; stdcall;
    function Trigger: HResult; stdcall;
  end;


// *********************************************************************//
// Interface: IMVGrid
// Flags:     (0)
// GUID:      {F17DCAF8-8A96-43C6-B486-357703B144C8}
// *********************************************************************//
  IMVGrid = interface(IUnknown)
    ['{F17DCAF8-8A96-43C6-B486-357703B144C8}']
    function Get_Show(out Show: WordBool): HResult; stdcall;
    function Set_Show(Show: WordBool): HResult; stdcall;
    function Get_Colour(out Colour: OLE_COLOR): HResult; stdcall;
    function Set_Colour(Colour: OLE_COLOR): HResult; stdcall;
    function Get_XSize(out Size: Integer): HResult; stdcall;
    function Set_XSize(Size: Integer): HResult; stdcall;
    function Get_YSize(out Size: Integer): HResult; stdcall;
    function Set_YSize(Size: Integer): HResult; stdcall;
    function Get_XOffset(out Offset: Integer): HResult; stdcall;
    function Set_XOffset(Offset: Integer): HResult; stdcall;
    function Get_YOffset(out Offset: Integer): HResult; stdcall;
    function Set_YOffset(Offset: Integer): HResult; stdcall;
  end;

implementation

end.
