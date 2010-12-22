unit Common;

interface

uses
  Windows, Messages, Classes, Controls, Forms, ExtCtrls,Graphics,
  Registry, SysUtils, Menus, StdCtrls, Variants, Math, DirectShow9,
  IBQuery, DSPack, ActiveX, WMF9, StrUtils;

type
 TTimeCodeRec = record
                 HH,MM,SS,FF : word;
                end;



 TWRKButtons = array[0..19] of boolean;                

const

 WM_RPFTPMSG      = WM_USER+1661;

 regMail           = 'mailto:register@westmediasystems.com';


  // frame rate standards
  FPS_MPG_0    = 0.0;
  FPS_MPG_23   = (24.0*1000)/1001;
  FPS_MPG_24   = 24.0;
  FPS_MPG_25   = 25.0;
  FPS_MPG_29   = (30.0*1000)/1001;
  FPS_MPG_30   = 30.0;
  FPS_MPG_50   = 50.0;
  FPS_MPG_59   = (60.0*1000)/1001;
  FPS_MPG_60   = 60.0;
  FPS_AVISTD   = 15.0;
  FPS_NTSCFILM = FPS_MPG_23;
  FPS_FILM     = FPS_MPG_24;
  FPS_PAL      = FPS_MPG_25;
  FPS_NTSC     = FPS_MPG_29;
  FPS_NTSC_30  = FPS_MPG_30;

{ MASTER-IT STRING ARRAYS }
 HIGHRESSTAT : array[0..9] of string =
 ('NEW VIDEOCLIP','ENCODING CUED','ENCODING',
  'RECORDING','','VIDEOCLIP READY','','','WARNING','ERROR');

 BURNMETHOD : array[0..2] of string =
  ('Burn on local burner','Create ISO image','CD/DVD publisher robot');

 DVDSTAT : array[0..10] of string =
  ('WAITING','CONVERTING','CONVERTED',
   'BUILDING DVD','DVD BUILT',
   'BURNING','BURNED','JOB COMPLETED',
   'COMPLETED, WARNING! SOURCE FILES NOT DELETED!',
   'NO DISC INSERTED, CHECK SERVER','FAILED!');

 CONVSTAT : array[0..10] of string =
  ('WAITING','CONVERTING','JOB COMPLETED','','','',
   '','','','','FAILED!');

 FTPSTAT : array[0..10] of string =
  ('WAITING','TRANSFERRING','JOB COMPLETED','','','',
   '','','FILE(S) NOT DELETED','RECEIVER(S) INVALID','FAILED!');

 EDLSTAT : array[0..10] of string =
  ('WAITING','ENCODING','JOB COMPLETED','','','',
   '','','','','FAILED!');

 RIMAGESTAT : array[0..10] of string =
  ('WAITING','ORDER SENT','WORKING','JOB COMPLETED','','',
   '','','','','RIMAGE FAILED!');

 LOWRESSTAT : array[0..10] of string =
  ('WAITING','ENCODING','JOB COMPLETED','','','',
   '','','','','FAILED!');

 MPSSTAT : array[0..10] of string =
  ('WAITING','ENCODING','TRANSFERRING','JOB COMPLETED',
  '','','','','','','FAILED!');
 MPSFILESTAT : array[0..10] of string =
  ('WAITING','SENDING','FILE SENT','',
  '','','','','','','FAILED!');

  DAYNAMEOFWEEK : array [ 1 .. 7 ] of String =
   ('MONDAY','TUESDAY','WEDNESDAY','THURSDAY','FRIDAY','SATURDAY','SUNDAY');

  NOYES : array[0..1] of string = ('NO','YES');

  ARATIOTEXT : array[0..3] of string = ('4:3','16:9','DV PAL 4:3', 'DV PAL 16:9');

  SUBFORMAT : array[0..3] of string = ('SRT','PAC','SAMI', '890');

  LANGTEXT  : array[0..3] of string = ('SWEDISH','DANISH','NORWEIGAN', 'FINNISH');
  LANGSHORT : array[0..3] of string = ('SW','DA','NO', 'FI');

  JOBPRIORITY : array[0..3] of string = ('EXPRESS','HIGH','NORMAL','LOW');
  RJOBPRIORITY : array[0..10] of string = ('EXPRESS','EXPRESS',
                                          'HIGH','HIGH',
                                          'NORMAL','NORMAL','NORMAL',
                                          'LOW','LOW','LOW','LOW');
{ ARRAY OF COMMON DIALOG TYPES }
   DLGTYPES : array [ 0 .. 10 ] of DWORD =
     (MB_OK or MB_DEFBUTTON1 or MB_ICONINFORMATION,             // 0
      MB_YESNO or MB_DEFBUTTON2 OR MB_ICONQUESTION,             // 1
      MB_YESNO or MB_DEFBUTTON2 or MB_ICONWARNING,              // 2
      MB_OK or MB_ICONSTOP,                                     // 3
      MB_OK or MB_ICONERROR,                                    // 4
      MB_YESNOCANCEL or MB_DEFBUTTON3 or MB_ICONQUESTION,       // 5
      MB_OK or MB_DEFBUTTON1 or MB_ICONEXCLAMATION,             // 6
      MB_YESNO or MB_DEFBUTTON2 or MB_ICONEXCLAMATION,          // 7
      MB_OK or MB_ICONWARNING,                                  // 8
      MB_YESNO or MB_DEFBUTTON2 or MB_ICONINFORMATION,          // 9
      MB_YESNOCANCEL or MB_DEFBUTTON1 or MB_ICONEXCLAMATION);   // 10


{ COMMON CHARS AS CONST }

  SOH   = #1;  // Start Of Heading
  STX   = #2;  // Start Of Text
  ETX   = #3;  // End Of Text
  EOT   = #4;  // End Of Transmission
  ENQ   = #5;  // Enquiry
  ACK   = #6;  // Acknowledge
  BEL   = #7;  // Bell
  BS    = #8;  // Backspace
  HT    = #9;  // Horisontal Tabulation
  LF    = #10; // Line Feed
  VT    = #11; // Vertical Tabulation
  FF    = #12; // Form Feed
  CR    = #13; // Carriage Return
  SO    = #14; // Shift Out
  SI    = #15; // Shift In
  DLE   = #16; // Data Link Escape
  XON   = #17; // Device Control 1 (XON)
  DC2   = #18; // Device Control 2
  XOFF  = #19; // Device Control 3 (XOFF)
  DC4   = #20; // Device Control 4
  NAK   = #21; // Negative Acknowledgement
  SYN   = #22; // Syncronous Idle
  ETB   = #23; // End Of Transmission Block
  CAN   = #24; // Cancel Line
  EM    = #25; // End Of Medium
  SUB   = #26; // Substitute
  ESC   = #27; // Escape
  FS    = #28; // File Separator
  GS    = #29; // Group Separator
  RS    = #30; // Record Separator
  US    = #31; // Unit Separator
  SP    = #32; // Space

  LUS   = ' | ';

  CRLF  = CR+LF;

  histCREATED   = 0;
  histCOMPLETED = 1;
  histDELETED   = 2;

  WMPStart      = 9;
  WMPEnd        = 9;
  WMPRew        = 5;
  WMPFF         = 4;
  WMPPlay       = 3;
  WMPPause      = 2;
  WMPStop       = 1;


  sIDAdmin              = 0;
  sIDRecPlay            = 1;
  sIDWorker             = 2;
  sIDRequester          = 3;
  sIDVServer            = 4;
  sIDModStatus          = 5;
  sIDPlayer             = 6;
  sIDSubtitler          = 7;

  sIDModLowRes          = 10;
  sIDModHighRes         = 11;
  sIDModDVDConvert      = 12;
  sIDModDVDBuild        = 13;
  sIDModDVDBurner       = 14;
  sIDModConverter       = 15;
  sIDModFTPOut          = 16;
  sIDModEDL             = 17;
  sIDModRimage          = 18;
  sIDModMPS             = 19;
  sIDModMPSFTP          = 20;


  subSRT                = 0;
  subPAC                = 1;
  subSAMI               = 2;
  sub890                = 3;

  RPFTPKey              = 'SOFTWARE\West Mediasystems\MASTER-IT RPFTP\1.0';


var

  firstRun    : Boolean;

// License variables
  ProgVerStr,
  UsrName, Company, RegisterString : String;

  LicenseStrings         : TStringList;

  bRegistered,
  bLimitReached,
  bInvalidLicense,
  bLIcenseNotFound       : Boolean;

  strMachID,
  strAppInfo,
  strAppText             : String;

  iDaysLeft,
  iUsageLeft,
  iTotalUsage,
  iTotalDays             : Integer;

  dStartDate,
  dEndDate               : TDateTime;
  
 { system and DB variables }
 curDBUserType,
 curDBUserID    : Integer;
 curDBUserSL,
 curDBUser,
 curDBPass,
 curDBServ,
 curDBFile,
 curDBRName     : String;

 defValidToDays, 
 curSID         : Integer;

 vServIP,
 vServPort      : String;

 AppDir         : String;

 RegExists      : Boolean;

 { lock program variables }

 activeTD       : TDateTime;
 inActiveLimit  : TTime;

 mouseX, mouseY,
 oldX, oldY     : Integer;

 lastMGID,
 lastHRID       : Integer;


 { gloval TC var }
  tcCommStr     : String;
  maxFrames     : Cardinal;
  curFPS        : Double; // current frame rate (frames per second)


 { system modules }

  ModuleActive          : Boolean;
  ModuleThreadID,
  ModuleProcessID,
  ModuleHandle          : Integer;

  ModuleComputerName    : String;

  MailStr               : String;

  MailWaiting           : Boolean;

  modProgress           : Boolean;

  modAppKey,
  modName,
  modServer             : String;
  modID,
  modPort               : Integer;
  modReg,
  modRunning            : Boolean;

 { recplay and FTP }
  RPFTPHandle    : HWND;

 { general stuff +}

 function  ConnectAndVerifyUNC(pHandle : HWND; sPATH, sUSER, sPASS : String;
                               var sMSG : String):Boolean;
 function  GetFileSize(const FileName: string): Int64;
 function  ShowDlg ( const strCaption, strText: STRING; dlgType: INTEGER ): INTEGER;
 function  FindForm ( const pClass: TCustomFormClass ): TCustomForm;
 function  HRToStr(hr: HResult): string;
 function  CheckFileAccessOK(aFile:String):Boolean;
 function  FileIsReady(aFILE:String):Boolean;
 function  SetWindowsTime(aTD:TDateTime):Boolean;
 Function  IsNewVersion(cMajor,cMinor,cRelease,cBuild : Word; nVerStr:String):Boolean;
 function  NAStr(aStr:String):String;
 function  ExtractFileFromURL(const URL: WideString): WideString;
 function  ExtractPathFromURL(const URL: WideString): WideString;

 function  GetLUSStr(aIndex:Integer;aStr:String):String;

 function  NewLUSStr(aIndex:Integer;
                     LUSStr:String;
                     newText : String):String;

 function  Win32LastError: String; stdcall;

 function  ReadReg(RegKey,Value:String; const ValueType:Variant;var Found:Boolean):Variant;
 function  WriteReg(RegKey,Value:String;const WriteValue : Variant):Boolean;

 function  InsertStr(aFileName,aString,PosStr:String):String;
 function  FixFileExt(aString,aExt:String):String;
 procedure DebugLog(AppPath,LogText:String);

 procedure InStr2SL(aStr:String;var aSL:TStringList;splitChar:Char);

 function  GetDateTimeFileName:String;
 Function  CodeString(Str,Pwd: String; Encode: Boolean): String;
 Function  RotateBits(C: Char; Bits: Integer): Char;
 function  FixFED(fStr:String):String;

 function  NoCRLF(aStr:String):String;
 function  NoPercent(aStr:String):String;
 function  NoSpace(aStr:String):String;
 function  RplSpacesToUScore(aStr:String):String;

 function  GetCurrentComputerName: string;

 // DS Timecode handling...

 function UpdateDur(aTCIn,aTCOut:TTimeCode):String;
 function UpdateOut(aTCIn,aTCDur:TTimeCode):String;

 function FixWMVTCStr(aStr:String):String;
 function MakeTCStr(aStr : String):String;
 function TCToStr(aTC:TTimeCode):String;
 function FrameToStr(aFrame:Int64):String;
 function FrameToStrNoZeros(aFrame:Int64):String;
 function REFToStr(refTime: REFERENCE_TIME):String;

 function TCStrOK(aTCStr:String):Boolean;
 function StrToTC(aTCStr:String;var aTC :TTimeCode):Boolean;
 function StrToTC2(aTCStr:String):TTimeCode;
 function StrToFrame(aTCStr:String):cardinal;
 function StrToSecs(aTCStr:String):Integer;

 function GetMaxFrames:Cardinal;

 function TCToLed(aTC:TTimeCode):String;

 function FrameToREF(aFrame:Int64):REFERENCE_TIME;
 function REFToFrame(aREF:REFERENCE_TIME):Cardinal;

 function  TimeToTC(timevalue:TTime):TTimeCode;
 function  TCToTime(aTC:TTimeCode):TDateTime;
 function  TCToTimeInt(aTC: TTimeCode): Integer;
 function  GetTCFRate(aTC : TTimeCode):Double;
 function  SetTCFRate(aFrameRate : Double):Word;

 procedure TCToREF(aTC:TTimeCode;var refTime : REFERENCE_TIME);
 function  FrameToMSEC(aFrame:Cardinal):Int64;

 procedure REFToTC(refTime : REFERENCE_TIME; var aTC:TTimeCode);
 procedure StrToHMSF(aTCStr:String;var HH,MM,SS,FF:Word);
 procedure TCToVCRHMSF(aTC:TTimeCode;var HH,MM,SS,FF:Integer);
 function  TCRFileExists(aOrgFile:string;var aTC:TTimeCode):Boolean;

 function  UDPStrToTC(aStr:String):TTimeCode;
 function  GetDurInFrames(inTC,outTC:TTimeCode):Cardinal;
 function  GetDurInStr(inTC,outTC:String;noZeros:Boolean):String;
 function  GetTCOutStr(inTCStr,durTCStr:String):String;

 function  GetTCInSRT(aStr:String):String;
 function  GetTCOutSRT(aStr:String):String;

 { more other stuff }
 function  GetLBInfo(aLBItem: String; var aVideoID,jobID:String ) : Boolean;
 function  NoColonTCStr(aTCStr:String):String;
 function  NoZeroTCStr(aStr:String):String;
 procedure AppendTCToFile(aTCStr:String;var FileName:String);

 function  WriteStrFile(aFileName,aString:String):Boolean;

 { MODULES }
 //function  ActivateModule


 procedure SQLWork;
 procedure SQLNoWork;

implementation

function ConnectAndVerifyUNC(pHandle : HWND; sPATH, sUSER, sPASS : String;
                             var sMSG : String  ):Boolean;
var
 nRSrc : TNETRESOURCE;
 res   : DWORD;
begin

 result := false;

 nRSrc.lpLocalName  := nil;
 nRSrc.lpRemoteName := PChar(sPATH);
 nRSrc.dwType       := RESOURCETYPE_DISK;
 nRSrc.dwDisplayType:= RESOURCEDISPLAYTYPE_GENERIC; ///RESOURCEDISPLAYTYPE_SHARE; //RESOURCEDISPLAYTYPE_GENERIC;
 nRSrc.dwUsage      := RESOURCEUSAGE_CONTAINER;	//RESOURCEUSAGE_CONNECTABLE;
 nRSrc.dwScope      := RESOURCE_GLOBALNET; //RESOURCE_REMEMBERED;
 nRSrc.lpProvider   := nil;


 res := WNetCancelConnection( PChar(sPATH), true);
 case res of
  ERROR_BAD_PROFILE	        : sMSG := 'The user profile is in an incorrect format.';
  ERROR_CANNOT_OPEN_PROFILE	: sMSG := 'The system is unable to open the user profile to process persistent connections.';
  ERROR_DEVICE_IN_USE	        : sMSG := 'The device is in use by an active process and cannot be disconnected.';
  ERROR_EXTENDED_ERROR	        : sMSG := 'A network-specific error occurred. To get a description of the error, use the WNetGetLastError function.';
  ERROR_NOT_CONNECTED	        : sMSG := 'The name specified by the lpName parameter is not a redirected device, or the system is not currently connected to the device specified by the parameter.';
  ERROR_OPEN_FILES	        : sMSG := 'There are open files, and the fForce parameter is FALSE.';
 end;

 // if not res = NO_ERROR then ShowMessage(sMSG);



 res := WNetAddConnection3( pHandle, nRSrc, Pchar(sUSER), Pchar(sPASS), 0);

 case res of
  ERROR_ACCESS_DENIED	        : sMSG := 'Access to the network resource was denied.';
  ERROR_ALREADY_ASSIGNED	: sMSG := 'The local device specified by lpLocalName is already connected to a network resource.';
  ERROR_BAD_DEV_TYPE	        : sMSG := 'The type of local device and the type of network resource do not match.';
  ERROR_BAD_DEVICE	        : sMSG := 'The value specified by lpLocalName is invalid.';
  ERROR_BAD_NET_NAME	        : sMSG := 'The value specified by lpRemoteName is not acceptable to any network resource provider. The resource name is invalid, or the named resource cannot be located.';
  ERROR_BAD_PROFILE	        : sMSG := 'The user profile is in an incorrect format.';
  ERROR_BAD_PROVIDER	        : sMSG := 'The value specified by lpProvider does not match any provider.';
  ERROR_BAD_USERNAME            : sMSG := 'The user name entered is invalid.';
  ERROR_BUSY	                : sMSG := 'The router or provider is busy, possibly initializing. The caller should retry.';
  ERROR_CANCELLED	        : sMSG := 'The attempt to make the connection was cancelled by the user through a dialog box from one of the network resource providers, or by a called resource.';
  ERROR_CANNOT_OPEN_PROFILE	: sMSG := 'The system is unable to open the user profile to process persistent connections.';
  ERROR_DEVICE_ALREADY_REMEMBERED : sMSG := 'An entry for the device specified in lpLocalName is already in the user profile.';
  ERROR_EXTENDED_ERROR	        : sMSG := 'A network-specific error occured. Call the WNetGetLastError function to get a description of the error.';
  ERROR_INVALID_PASSWORD	: sMSG := 'The specified password is invalid.';
  ERROR_NO_NET_OR_BAD_PATH	: sMSG := 'A network component has not started, or the specified name could not be handled.';
  ERROR_NO_NETWORK	        : sMSG := 'There is no network present.';
  ERROR_BAD_NETPATH             : sMSG := sPath+' is an invalid path.';
  ERROR_LOGON_FAILURE           : sMSG := 'Logon failed check username and password.';
  ERROR_SESSION_CREDENTIAL_CONFLICT : sMsg := 'Credential conflict, there is allready a connection.';
  NO_ERROR                      : begin result := True end;
  else
   sMSG := 'Unknown error: '+IntToStr(res);
 end;

end;



function GetFileSize(const FileName: string): Int64;
var
    SearchRec: TSearchRec;
begin
    if FindFirst(ExpandFileName(FileName), faAnyFile, SearchRec) = 0 then begin
        Result := (SearchRec.FindData.nFileSizeHigh shl 32) + SearchRec.FindData.nFileSizeLow;
        SysUtils.FindClose(SearchRec);
    end
    else
        Result := -1;
end;

{ SHOWDLG FUNCTION }
function ShowDlg ( const strCaption, strText: STRING; dlgType: INTEGER ): INTEGER;
 begin
   if (dlgType <= HIGH(DLGTYPES)) then
     Result := MessageBox(GetForeGroundWindow,POINTER(strText),POINTER(strCaption),DLGTYPES[dlgType])
     //GetForeGroundWindow
   else
     Result := 9999;
end;

{ FINDFORM FUNCTION }
function FindForm ( const pClass: TCustomFormClass ): TCustomForm;
var iIndex : INTEGER;
 begin
  try
   for iIndex := 0 to (Screen.FormCount - 1) do
   begin
    Result := Screen.Forms[iIndex];
    if (Result.InheritsFrom(pClass)) then exit;
   end;
   Result := NIL;
  except
   Result := NIL;
  end;
 end;

{MAKE HRESULT TO STRING }
function HRToStr(hr: HResult): string;
begin
  if IsError(hr) then
  begin
    case hr of
      S_OK: result:= 'Success';
      S_FALSE: result:= 'False';
      E_UNEXPECTED: result:= 'Catastrophic failure';
      E_NOTIMPL: result:= 'Not implemented';
      E_OUTOFMEMORY: result:= 'Ran out of memory';
      E_INVALIDARG: result:= 'One or more arguments are invalid';
      E_NOINTERFACE: result:= 'No such interface supported';
      E_POINTER: result:= 'Invalid pointer';
      E_HANDLE: result:= 'Invalid handle';
      E_ABORT: result:= 'Operation aborted';
      E_FAIL: result:= 'Unspecified error';
      E_ACCESSDENIED: result:= 'General access denied error';
      E_PENDING: result:=
        'The data necessary to complete this operation is not yet available.';
    else result:= 'Unknown error: '+IntToHex(hr, 8);
    end;
  end
  else
   if HR = S_OK then result := ' ok!';
end;

{ CHECK FILE ACCESS }
function CheckFileAccessOK(aFile:String):Boolean;
 var f : file of byte;
 begin
  if not FileExists(aFile) then Result := False
  else
   begin
    AssignFile(F, aFile);
    {$I-} Reset(F); {$I+}
    Result := (IOResult = 0);
    CloseFile(F);
   end;
 end;

function FileIsReady(aFILE:String):Boolean;
var
 fs : TFileStream;
begin
 try
  fs := TFileStream.Create(aFile,fmShareExclusive);
  fs.Free;
  result := true;
 except
  result := false;
 end;

end;



function  SetWindowsTime(aTD:TDateTime):Boolean;
var
  NewTime : _SystemTime;
  yr,mo,da,
  hr,min,sec,msec : word;
begin

  DecodeDate(aTD,yr,mo,da);
  DecodeTime(aTD,hr,min,sec,msec);

  FillChar(NewTime, sizeof(NewTime), #0);
  NewTime.wYear         := yr;
  NewTime.wMonth        := mo;
  NewTime.wDay          := da;
  NewTime.wHour         := hr;
  NewTime.wMinute       := min;
  NewTime.wSecond       := sec;
  NewTime.wMilliseconds := msec;

  result := SetLocalTime(NewTime);

end;


Function IsNewVersion(cMajor,cMinor,cRelease,cBuild : Word; nVerStr:String):Boolean;
var
 j,
 i : integer;
 s : string;
 nMajor, nMinor,
 nRelease, nBuild : Integer;
begin

 try
   j := 0;
   for i:=1 to length(nVerStr) do
   begin
     if nVerStr[i]<>'.' then s := s + nVerStr[i];
     if (nVerStr[i]='.') or (i=length(nVerStr)) then
      case j of
       0 : begin nMajor   := StrToInt(s); s:=''; inc(j); end;
       1 : begin nMinor   := StrToInt(s); s:=''; inc(j); end;
       2 : begin nRelease := StrToInt(s); s:=''; inc(j); end;
       3 : begin nBuild   := StrToInt(s); s:=''; inc(j); end;
      end;
   end;

   Result := ( ( (cMajor  *1000000000 )+
                 (cMinor  *1000000 ) +
                 (cRelease*1000 )+
                 (cBuild  *100) ))

                 <

               ( (nMajor  *1000000000 )+
                 (nMinor  *1000000 ) +
                 (nRelease*1000 )+
                 (nBuild  *100) );
 except
  result := false;
 end;
end;

function  NAStr(aStr:String):String;
 begin
  if aStr = '' then result := 'Not available'
  else result := aStr;
 end;

function ExtractFileFromURL(const URL: WideString): WideString;
var
  I: Integer;
begin
  If URL = '' then
    Result := ''
  else begin
    I := LastDelimiter('/', URL);
    Result := Copy(URL, I + 1, MaxInt);
  end;
end;

function ExtractPathFromURL(const URL: WideString): WideString;
var
  I: Integer;
begin
  If URL = '' then
    Result := ''
  else begin
    I := LastDelimiter('/', URL);
    Result := Copy(URL, 1, I );
  end;
end;

function  GetLUSStr(aIndex:Integer;aStr:String):String;
 var
  c,
  i : integer;
  s : string;

 begin
  c := 1; s:='';

  for i:=1 to Length(aStr) do
   begin
    s:=s+aStr[i];
    if (pos(LUS,s)>0) then
    if (aIndex=c) then
     begin
      result := copy(s,1,Length(s)-3);
      break;
     end else
     begin
      s:='';
      inc(c);
     end;
   end;

 end;

function NewLUSStr(aIndex:Integer;
                   LUSStr:String;
                   newText : String):String;

 var
  iPos1,
  iLength,
  c,
  i : integer;
  s : string;


 begin

  i := 1;
  c := 0;

  iPos1 := 1;
  iLength := 0;

  // Go through string and find start stop position of LUS

  while i <= Length(LUSStr) do // locate start stop pos of string
   begin
    if LUSStr[i] = '|' then
     begin
      Inc(c); // inc what index is current.
      if c=aIndex then break else
      begin iPos1 := i+2; iLength := 0; end;
     end;
     Inc(iLength);
     Inc(i);
   end;

   s := LUSStr;

  // Dec(iLength); // -1 to save space before |

   Delete(s,iPos1,iLength-3); // -3 save LUS
   Insert(newText,s,iPos1);

   result := s;

 end;

{ GET WIN32 LAST ERROR }
function Win32LastError: String; stdcall;
var
 lpMsgBuf : PChar;
 lastErrNum: Cardinal;

begin
 lastErrNum := GetLastError();

    FormatMessage(
                  FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM,
                  nil,
                  lastErrNum,
                  //MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (SUBLANG_DEFAULT shl 10) or LANG_NEUTRAL,
                  @lpMsgBuf,
                  0,
                  nil
    );

   result := StrPas( lpMsgBuf );
   result := result + ' (Win32 Err# ' + inttostr(lastErrNum) + ')';

   LocalFree( Cardinal(lpMsgBuf) );
end;


{ WriteREG FUNCTION }
function  WriteReg(RegKey,Value:String;const WriteValue : Variant):Boolean;
 begin
 with TRegistry.Create do
 try RootKey := HKEY_LOCAL_MACHINE;
  Result := OpenKey(RegKey, True);
  if Result then
     case VarType(WriteValue) of
      varString         : WriteString(Value,WriteValue);
      varDouble         : WriteFloat(Value,WriteValue);
      varByte,
      varWord,
      varLongWord,
      varInt64,
      varSmallInt,
      varShortInt,
      varInteger        : WriteInteger(Value,WriteValue);
      varBoolean        : WriteBool(Value,WriteValue);
     end; {case}
  finally free;
 end;
end;

{ ReadREG FUNCTION }
 function  ReadReg(RegKey,Value:String; const ValueType:Variant;var Found:Boolean):Variant;
 begin
 with TRegistry.Create do
 try RootKey := HKEY_LOCAL_MACHINE;
  Found := OpenKey(RegKey, False);
  if Found then
    if ValueExists(Value) then
     case VarType(ValueType) of
      varString         : Result := ReadString(Value);
      varDouble         : Result := ReadFloat(Value);
      varByte,
      varWord,
      varLongWord,
      varInt64,
      varSmallInt,
      varShortInt,
      varInteger        : Result := ReadInteger(Value);
      varBoolean        : Result := ReadBool(Value);
     else Found := False;
     end {case}
    else Found := False;
  finally free;
 end;
end;


{ REMOVE AND MAKE A NEW FILE EXTENSION }
function  InsertStr(aFileName,aString,PosStr:String):String;
var
 nStr : String;
 begin

  nStr := aFileName;
  Insert(aString,nStr,Pos(PosStr,nStr));

  result := nStr;

 end;

{ REMOVE AND MAKE A NEW FILE EXTENSION }
function  FixFileExt(aString,aExt:String):String;
var
 revExt, revStr,
 newStr, first4  : string;
 begin

  revStr := ReverseString(aString);
  revExt := ReverseString(aExt);

  first4 := copy(revStr,1,4);

  if Uppercase(first4) = UpperCase(revExt)+'.' then result := aString else
   begin
    if pos('.',revStr)>0 then delete( revStr,1,Pos('.',revStr) );
    newStr := revExt+'.'+revStr;

    result := ReverseString(newStr);
   end;
 end;


{ SAVE TEXT TO FILE - DEBUG }
procedure DebugLog(AppPath,LogText:String);
var
 F : Textfile;
 Filename : String;
begin

 try
  FileName := AppPath+DateToStr(now)+'.log';
  AssignFile(F,FileName);
                           
  if FileExists(FileName) then
   Append(F) else ReWrite(F);

   WriteLn(F,DateTimeToStr(Now)+' | '+NoCRLF(LogText));
  CloseFile(F);

 except
 end;
end;

procedure InStr2SL(aStr:String;var aSL:TStringList;splitChar:Char);
var
 i      : Integer;
 tmpStr : String;
 begin

  tmpStr := '';
  aSL.Clear;

  for i:=1 to Length(aStr) do
   begin
    if aStr[i]<>SplitChar then tmpStr := tmpStr + aStr[i]
     else begin aSL.Append(tmpStr); tmpStr := ''; end;
   end;

 if aSL.Count < 4 then for i:=aSL.Count to 4 do aSL.Append('');

end;


function GetDateTimeFileName:String;
 var
  Ye,Mo,Da,
  Ho,Mi,Se,Ms : Word;

 begin
  DecodeDate(Now,Ye,Mo,Da);
  DecodeTime(Now,Ho,Mi,Se,Ms);

  Result := Format('%4.4d%2.2d%2.2d_%2.2d%2.2d%2.2d',
                   [Ye,Mo,Da,Ho,Mi,Se]);

 end;
Function RotateBits(C: Char; Bits: Integer): Char;
var
  SI : Word;
begin
  Bits := Bits mod 8;
  // Are we shifting left?
  if Bits < 0 then
    begin
      // Put the data on the right half of a Word (2 bytes)
      SI := MakeWord(Byte(C),0);
      // Now shift it left the appropriate number of bits
      SI := SI shl Abs(Bits);
    end
  else 
    begin
      // Put the data on the left half of a Word (2 bytes)
      SI := MakeWord(0,Byte(C));
      // Now shift it right the appropriate number of bits
      SI := SI shr Abs(Bits);
    end; 
  // Now OR the two halves together
  SI := Lo(SI) or Hi(SI);
  Result := Chr(SI);
end;

Function CodeString(Str,Pwd: String; Encode: Boolean): String;
var
  a,PwdChk,Direction,ShiftVal,PasswordDigit : Integer;
begin
  PasswordDigit := 1;
  PwdChk := 0;
  for a := 1 to Length(Pwd) do Inc(PwdChk,Ord(Pwd[a]));
  Result := Str;
  if Encode then Direction := -1 else Direction := 1;
  for a := 1 to Length(Result) do
    begin
      if Length(Pwd)=0 then 
        ShiftVal := a
      else
        ShiftVal := Ord(Pwd[PasswordDigit]);
      if Odd(A) then
        Result[A] := RotateBits(Result[A],-Direction*(ShiftVal+PwdChk))
      else
        Result[A] := RotateBits(Result[A],Direction*(ShiftVal+PwdChk));
      inc(PasswordDigit);
      if PasswordDigit > Length(Pwd) then PasswordDigit := 1;
    end;
end;


function FixFED(fStr:String):String;
var
 aStr : String;
begin
 aStr := fStr;
 while Pos('"',aStr)>0 do Delete(aStr,Pos('"',aStr),1);
 result := aStr;
end;

function  NoCRLF(aStr:String):String;
var
 nStr : String;
begin
 nStr := aStr;
 while Pos(#13,nStr)>0 do begin Insert(' ',nStr,Pos(#13,nStr)); Delete(nStr,Pos(#13,nStr),1); end;
 while Pos(#10,nStr)>0 do Delete(nStr,Pos(#10,nStr),1);
 result := nStr;
end;

function  NoPercent(aStr:String):String;
var
 nStr : String;
begin
 nStr := aStr;
 while Pos('%',nStr)>0 do begin Delete(nStr,Pos('%',nStr),1); end;
 result := nStr;
end;

function  NoSpace(aStr:String):String;
var
 nStr : String;
begin
 nStr := aStr;
 while Pos(#32,nStr)>0 do begin Delete(nStr,Pos(#32,nStr),1); end;
 result := nStr;
end;

function  RplSpacesToUScore(aStr:String):String;
var
 nStr : String;
begin
 nStr := aStr;
 while Pos(#32,nStr)>0 do begin Insert('_',nStr,Pos(#32,nStr)); Delete(nStr,Pos(#32,nStr),1); end;
 result := nStr;
end;


function GetCurrentComputerName: string;
var
  dwLength: dword;
begin
  dwLength := MAX_COMPUTERNAME_LENGTH + 1;
  SetLength(Result, dwLength);
  Win32Check(GetComputerName(PChar(Result), dwLength));
  SetLength(Result, dwLength);
end;


//////// TIMECODE FUNCTIONS AND PROCEDURE //////////


function  NoZeroTCStr(aStr:String):String;
var
 i      : integer;
begin
 i:= 1;
 while ((aStr[i]=':') or (aStr[i]='0')) and
        not (i>(Length(aStr)-3)) do Inc(I);
 result := copy(aStr,I,Length(aStr) - (I-1));
end;

function GetTCFRate(aTC : TTimeCode):Double;
begin
 case aTC.wFrameRate of
  ED_FORMAT_SMPTE_30           : result := 30;
  ED_FORMAT_SMPTE_30DROP       : result := 29.97; {TODO: check this!}
  ED_FORMAT_SMPTE_25           : result := 25;
  ED_FORMAT_SMPTE_24           : result := 24;
  else result := 25;
 end;
end;

function SetTCFRate(aFrameRate : Double):Word;
begin
 if aFrameRate = 30 then result := ED_FORMAT_SMPTE_30 else
 if aFrameRate = 29.97 then result := ED_FORMAT_SMPTE_30DROP else
 if aFrameRate = 25 then result := ED_FORMAT_SMPTE_25 else
 if aFrameRate = 24 then result := ED_FORMAT_SMPTE_24 else
                         result := ED_FORMAT_SMPTE_25;
end;

function REFToStr(refTime: REFERENCE_TIME):String;
var
 aTC: TTimeCode;
 begin
  REFToTC(refTime,aTC);
  result := TCToSTR(aTC);
 end;


function UpdateDur(aTCIn, aTCOut: TTimeCode): String;
var
 frames : Integer;
 tempTC : TTimeCode;
begin

 frames := aTCOut.dwFrames - aTCIn.dwFrames;

 if frames<0 then
  tempTC.dwFrames := GetMaxFrames - abs(frames) else
 if frames>=GetMaxFrames then
  tempTC.dwFrames := frames - GetMaxFrames else
  tempTC.dwFrames := frames;

 result := TCToStr(tempTC);

end;

function UpdateOut(aTCIn, aTCDur: TTimeCode): String;
var
 frames : Integer;
 tempTC : TTimeCode;
begin

 frames := aTCIn.dwFrames + aTCDur.dwFrames;

 if frames<0 then
  tempTC.dwFrames := GetMaxFrames - abs(frames) else
 if frames>=GetMaxFrames then
  tempTC.dwFrames := frames - GetMaxFrames else
  tempTC.dwFrames := frames;

 result := TCToStr(tempTC);

end;

function FixWMVTCStr(aStr:String):String;
begin
 Result := Copy(aStr,8,Length(aStr)-7);
end;

function MakeTCStr(aStr : String):String;
var
 newStr : String;
 i : integer;
 begin

  newStr := aStr;

  if Length(newStr)=11 then
   begin
    result := newStr;
    Exit;
   end else
  if Length(newStr)= 8 then
   begin
    insert(':',newStr,7);
    insert(':',newStr,5);
    insert(':',newStr,3);
   end else
  if length(newStr) < 8 then
   begin
    for i := length(newStr) to 7 do
     newStr := newStr + '0';
    insert(':',newStr,7);
    insert(':',newStr,5);
    insert(':',newStr,3);
   end;

  result := newStr;

 end;


function TCToStr(aTC:TTimeCode):String;
var
 HH,
 MM,
 SS,
 FF             : word;
 totFrames    : cardinal;

begin
 totFrames := aTC.dwFrames;
  FF := totFrames MOD (trunc(GetTCFRate(aTC)));
  SS := Trunc(totFrames / GetTCFRate(aTC)) MOD 60;
  MM := Trunc(totFrames / (60* GetTCFRate(aTC))) MOD 60;
  HH := Trunc(totFrames / (60*60*GetTCFRate(aTC))) MOD 60;
  if HH > 24 then HH := HH mod 24;
 result := Format('%2.2d:%2.2d:%2.2d:%2.2d',[HH,MM,SS,FF]);
end;

function TCStrOK(aTCStr:String):Boolean;
var
  HH,
  MM,
  SS,
  FF             : ShortInt;
 begin
  try
   HH := StrToIntDef(aTCStr[1]+aTCStr[2],-1);
   MM := StrToIntDef(aTCStr[4]+aTCStr[5],-1);
   SS := StrToIntDef(aTCStr[7]+aTCStr[8],-1);
   FF := StrToIntDef(aTCStr[10]+aTCStr[11],-1);

   result := True;

   if (( HH > 23 ) or ( HH = -1 )) then result := false else
   if (( MM > 59 ) or ( MM = -1 )) then result := false else
   if (( SS > 59 ) or ( SS = -1 )) then result := false else
   if (( FF > curFPS - 1 ) or (FF = -1 )) then result := false;

  except
   result := False;
  end;
 end;

function StrToTC(aTCStr:String;var aTC : TTimeCode):Boolean;
var
  HH,
  MM,
  SS,
  FF             : word;
 begin
  try
   HH := StrToIntDef(aTCStr[1]+aTCStr[2],0);
   MM := StrToIntDef(aTCStr[4]+aTCStr[5],0);
   SS := StrToIntDef(aTCStr[7]+aTCStr[8],0);
   FF := StrToIntDef(aTCStr[10]+aTCStr[11],0);

   aTC.dwFrames := Round((( SS + (60*MM) + (HH*3600)) * GetTCFRate(aTC)) + FF);

   result := True;
  except
   result := False;
  end;
 end;

function StrToTC2(aTCStr:String):TTimeCode;
var
  HH,
  MM,
  SS,
  FF             : word;
 begin
  try
   HH := StrToIntDef(aTCStr[1]+aTCStr[2],0);
   MM := StrToIntDef(aTCStr[4]+aTCStr[5],0);
   SS := StrToIntDef(aTCStr[7]+aTCStr[8],0);
   FF := StrToIntDef(aTCStr[10]+aTCStr[11],0);

   result.dwFrames := Round((( SS + (60*MM) + (HH*3600)) * curFPS) + FF);
   result.wFrameRate := SetTCFrate(curFPS);
  except
   result.dwFrames := 0;
  end;
 end;

function FrameToStr(aFrame:Int64):String;
var
 HH,
 MM,
 SS,
 FF             : word;
 totFrames      : Int64;
 begin

  totFrames := aFrame;
  if totFrames < 0 then totFrames := 0;

  FF := totFrames MOD (trunc(curFPS));
  SS := Trunc(totFrames / curFPS) MOD 60;
  MM := Trunc(totFrames / (60* curFPS)) MOD 60;
  HH := Trunc(totFrames / (60*60*curFPS)) MOD 60;
  if HH > 24 then HH := HH mod 24;

  result := Format('%2.2d:%2.2d:%2.2d:%2.2d',[HH,MM,SS,FF]);
 end;


function FrameToStrNoZeros(aFrame:Int64):String;
var
 HH,
 MM,
 SS,
 FF             : word;
 totFrames      : Int64;

 i              : Integer;

 tcStr          : String;

 begin

  totFrames := aFrame;
  if totFrames < 0 then totFrames := 0;

  FF := totFrames MOD (trunc(curFPS));
  SS := Trunc(totFrames / curFPS) MOD 60;
  MM := Trunc(totFrames / (60* curFPS)) MOD 60;
  HH := Trunc(totFrames / (60*60*curFPS)) MOD 60;
  if HH > 24 then HH := HH mod 24;

  tcStr := Format('%2.2d:%2.2d:%2.2d:%2.2d',[HH,MM,SS,FF]);

  i:=1;

  while Length(tcStr)>1 do
  if ( tcStr[i] = '0' ) or ( tcStr[i] = ':' ) then
   Delete(tcStr,1,1) else Break;

  result := tcStr;

 end;

procedure TCToVCRHMSF(aTC:TTimeCode;var HH,MM,SS,FF:Integer);
var
 tHH,
 tMM,
 tSS,
 tFF             : word;
 totFrames    : cardinal;

begin
 totFrames := aTC.dwFrames;
  tFF := totFrames MOD (trunc(curFPS));
  tSS := Trunc(totFrames / curFPS) MOD 60;
  tMM := Trunc(totFrames / (60* curFPS)) MOD 60;
  tHH := Trunc(totFrames / (60*60*curFPS)) MOD 60;
  if tHH > 24 then tHH := tHH mod 24;

  HH := tHH;
  MM := tMM;
  SS := tSS;
  FF := tFF;

end;

procedure StrToHMSF(aTCStr:String;var HH,MM,SS,FF:Word);
 begin
   HH := StrToIntDef(aTCStr[1]+aTCStr[2],0);
   MM := StrToIntDef(aTCStr[4]+aTCStr[5],0);
   SS := StrToIntDef(aTCStr[7]+aTCStr[8],0);
   FF := StrToIntDef(aTCStr[10]+aTCStr[11],0);
 end;

function TimeToTC(timevalue:TTime):TTimeCode;
 var
 hh,mm,ss,ff,
 msec : Word;
  begin
  with Result do begin
   DecodeTime(TimeValue,HH,MM,SS,MSEC);
   FF := ceil(MSEC * curFPS) div 1000;

   result.dwFrames := Round((( SS + (60*MM) + (HH*3600)) * curFPS) + FF);
  end;
 end;

function TCToTime(aTC: TTimeCode): TDateTime;
var
 HH,
 MM,
 SS,
 FF             : word;
 totFrames    : cardinal;

begin

 totFrames := aTC.dwFrames;
  FF := totFrames MOD (trunc(curFPS));
  SS := Trunc(totFrames / curFPS) MOD 60;
  MM := Trunc(totFrames / (60* curFPS)) MOD 60;
  HH := Trunc(totFrames / (60*60*curFPS)) MOD 60;
  if HH > 24 then HH := HH mod 24;

 Result := Int(now)+Frac(EncodeTime( HH,MM,SS, (FF DIV Trunc(curFPS) ) * 1000) );

end;

function TCToTimeInt(aTC: TTimeCode): Integer;
var
 HH,
 MM,
 SS,
 FF             : word;
 totFrames    : cardinal;

begin

 totFrames := aTC.dwFrames;
  FF := totFrames MOD (trunc(curFPS));
  SS := Trunc(totFrames / curFPS) MOD 60;
  MM := Trunc(totFrames / (60* curFPS)) MOD 60;
  HH := Trunc(totFrames / (60*60*curFPS)) MOD 60;
  if HH > 24 then HH := HH mod 24;

 Result := Trunc(Frac(EncodeTime( HH,MM,SS, (FF DIV Trunc(curFPS) ) * 1000) )*100000);

end;


function StrToFrame(aTCStr:String):cardinal;
var
  HH,
  MM,
  SS,
  FF             : word;
 begin
   HH := StrToIntDef(aTCStr[1]+aTCStr[2],0);
   MM := StrToIntDef(aTCStr[4]+aTCStr[5],0);
   SS := StrToIntDef(aTCStr[7]+aTCStr[8],0);
   FF := StrToIntDef(aTCStr[10]+aTCStr[11],0);

  result := Round((( SS + (60*MM) + (HH*3600)) * curFPS) + FF);
 end;

function StrToSecs(aTCStr:String):Integer;
var
 HH,MM,SS,FF : Word;
begin
  StrToHMSF(aTCStr,HH,MM,SS,FF);
  Result := ( SS + (60*MM) + (HH*3600) );
end;

function GetMaxFrames:Cardinal;
var
 tStr : String;
begin
 tStr := '23:59:59:'+IntToStr(Round(curFPS));
 result := StrToFrame(tStr);
end;



function TCToLed(aTC :TTimeCode):String;
var
 aStr : String;
begin
 aStr := FrameToStr(aTC.dwFrames);
 while pos(':',aStr)>0 do Delete(aStr,Pos(':',aStr),1);
 result := aStr;
end;

function  FrameToREF(aFrame:Int64):REFERENCE_TIME;
 begin
  Result := Round( (aFrame / curFPS) * 10000000 );
 end;

function REFToFrame(aREF:REFERENCE_TIME):Cardinal;
 begin
  result := ( Round(aREF  * curFPS ) DIV 10000000 );
 end;

procedure TCToREF(aTC:TTimeCode;var refTime : REFERENCE_TIME);
 begin
  refTime := Round( (aTC.dwFrames / GetTCFRate(aTC)) * 10000000 );
 end;

function  FrameToMSEC(aFrame:Cardinal):Int64;
 begin
  result := Round( (aFrame / curFPS ) * 1000 );
 end;

procedure REFToTC(refTime : REFERENCE_TIME; var aTC:TTimeCode);
 begin
  aTC.dwFrames := Round( (refTime / 10000000 ) * GetTCFRate(aTC) );
 end;


function TCRFileExists(aOrgFile:string;var aTC:TTimeCode):Boolean;
var
 aTCRecfile     : file of TTimeCodeRec;
 extTCFile      : string;
 aTCRec         : TTimeCodeRec;
 totFrames      : Double;

 begin
   result := false;

   ExtTCFile := aOrgFile;
   Delete(extTCFile,Length(extTCFile)-3,4);
   extTCFile := extTCFile + '.tcr';

   if (not FileExists(ExtTCFile)) then
    begin
     aTC.dwFrames := 0;
     Exit;
    end
   else
    begin
     AssignFile(aTCRecFile,ExtTCFile);
      Reset(aTCRecFile);
      Read(aTCRecFile,aTCRec);
     CloseFile(aTCRecFile);

     with aTCRec do
      totFrames := ((SS + (60 * MM) + (HH * 3600)) * GetTCFRate(aTC) + FF);
      aTC.dwFrames := Round(totFrames);
     result := true;
    end;
 end;


function UDPStrToTC(aStr:String):TTimeCode;
var
 tStr : String;
 begin

  if length(aStr) <> 4 then exit;
  tStr := Format('%2.2d:%2.2d:%2.2d:%2.2d',
                 [ord(aStr[1]),ord(aStr[2]),
                  ord(aStr[3]),ord(aStr[4])]);
  Result := StrToTC2(tStr);

 end;

function  GetDurInFrames(inTC,outTC:TTimeCode):Cardinal;
var
 Duration : Integer;
 begin
  Duration := ( outTC.dwFrames ) -( inTC.dwFrames );
  if Duration < 0 then result := Duration + maxFrames else result := Duration;
 end;

function  GetDurInStr(inTC,outTC:String;noZeros:Boolean):String;
 var
  tc1,tc2 : TTimeCode;
  totF    : Cardinal;
 begin

  if (inTC ='') or (outTC='') then
   begin result := ''; exit; end;

  tc1.dwFrames := StrToFrame(inTC);
  tc2.dwFrames := StrToFrame(outTC);

  totF := GetDurInFrames(tc1,tc2);

  if noZeros then
   result := NoZeroTCStr(FrameToStr(totF)) else
   result := FrameToStr(totF);


 end;

function  GetTCOutStr(inTCStr,durTCStr:String):String;

var
 inTC,
 durTC : TTimeCode;
begin
 inTC  := StrToTC2(inTCStr);
 durTC := StrToTC2(durTCStr);

 result := UpdateOut(inTC,durTC);

end;



function  GetTCInSRT(aStr:String):String;
 begin
  result := Copy(aStr,1,11);
 end;

function  GetTCOutSRT(aStr:String):String;
 begin
  result := Copy(aStr,17,11);
 end;

function GetLBInfo(aLBItem: String;var aVideoID,jobID:String ):Boolean;
begin

 if Pos(', ',aLBItem) > 0 then
  begin
   aVideoID    :=  Copy( aLBItem,1,Pos(', ',aLBItem)-1);
   jobID       :=  Copy( aLBItem, Pos(', ',aLBItem)+2,
                         Pos(' | ',aLBItem) - (Pos(', ',aLBItem)+2) );
   result := True;
  end else result := False;

end;

function NoColonTCStr(aTCStr:String):String;
var
 aStr : String;
begin
 aStr := aTCStr;
 while pos(':',aStr)>0 do Delete(aStr,Pos(':',aStr),1);
 result := aStr;
end;


procedure AppendTCToFile(aTCStr:String;var FileName:String);
var
 tStr : String;
 begin
  tStr := '_'+NoColonTCStr(aTCStr);
  Insert(tStr,FileName,Length(FileName)-3);
 end;


function  WriteStrFile(aFileName,aString:String):Boolean;
var
 ss : TStringStream;
 fs : TFileStream;

 begin
   result := true;

   ss := TStringStream.Create(aString);
   fs := TFileStream.Create(aFileName,fmCreate);
    try
     fs.CopyFrom(ss,0);
    except on E:Exception do
     begin
      debugLog(appdir,'WriteFile error: '+E.Message);
      result := false;
     end;
    end;
   fs.Free;
   ss.Free;
 end;


procedure SQLWork;
begin
 Screen.Cursor := crSQLWait;
end;

procedure SQLNoWork;
begin
 Screen.Cursor := crDefault;
end;

end.
