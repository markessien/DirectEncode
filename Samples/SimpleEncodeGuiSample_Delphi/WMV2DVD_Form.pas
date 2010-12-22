
{
[11:12] <ki9a> var d: Double; d := Timedone / TimeTaken;
[11:12] <ki9a> now you have the % that's done.
[11:12] <ki9a> var d: Double; d := Timedone / totaltime;
[11:12] <ki9a> that's better
[11:13] <ki9a> now you have the % that's done.
[11:13] <ki9a> d := 1 - d;
[11:13] <ki9a> now you have the % todo.
[11:13] <ki9a> that's what you wanted?
[11:14] <|mrw> im converting video, tDone is secs converted, tTaken = how long its taken so far, and tTotal = amount of secs to convert.
[11:14] <ki9a> so:
[11:14] <ki9a> timetaken * (timedone / totaltime)
[11:15] <ki9a> say timetaken is 10 seconds
[11:15] <ki9a> timedone is 5
[11:15] <ki9a> totaltime is 20
[11:15] <ki9a> 5 / 20 = 1/4 = 0.25
[11:15] <ki9a> so it's at a quarter of the processing
[11:15] <ki9a> 10 / 0.25 = 40
[11:15] <ki9a> so the * should be /
[11:16] <ki9a> timetaken / (timedone / totaltime)
}

unit WMV2DVD_Form;

interface

uses
  Windows, Messages, SysUtils,
  Variants, Classes, Graphics, Controls, Forms,
  Dialogs,
  ExtCtrls,
  Mask, ToolEdit,

  Common,
  WMVConvert,

  StdCtrls,

  Math,
  MMSystem,
  ComCtrls,

  rsStorage, rsPropSaver, rsIniData, OleCtrls;



type

  TWMVConvertThread  = class(TThread)
                        public

                         WMVConv : TWMVConvert;

                          pHWND : HWND;
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
                          prevPanel : TPanel;
                         procedure StartConversion;
                         procedure StopConvertsion;
                        protected
                         procedure Execute; override;
                        end;


  TfrmWMVConvert = class(TForm)
    fedIn: TFilenameEdit;
    btnPlay: TButton;
    btnStop: TButton;
    lblInfo1: TLabel;
    lblInfo2: TLabel;
    btnConvert: TButton;
    lblInfo3: TLabel;
    pnlVW: TPanel;
    lblInfo5: TLabel;
    timProg: TTimer;
    pBar: TProgressBar;
    chbNoPreview: TCheckBox;
    rsStorage1: TrsStorage;
    rsIniData1: TrsIniData;
    rsPropSaver1: TrsPropSaver;
    lblInfo4: TLabel;
    PageControl1: TPageControl;
    tsVideo: TTabSheet;
    tsAudio: TTabSheet;
    tsContainer: TTabSheet;
    tsAdvanced: TTabSheet;
    cbVideoStream: TComboBox;
    cbWidth: TComboBox;
    cbHeight: TComboBox;
    cbAspect: TComboBox;
    cbFPS: TComboBox;
    cbBitrateControl: TComboBox;
    edVideoBitrate: TEdit;
    edVideoBitrateMin: TEdit;
    edVideoBitrateMax: TEdit;
    edVBVBufferSize: TEdit;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    cbAudioStream: TComboBox;
    cbAudioBitrate: TComboBox;
    Label16: TLabel;
    cbAudioSample: TComboBox;
    Label17: TLabel;
    cbAudioChannels: TComboBox;
    Label18: TLabel;
    Label19: TLabel;
    chbErrorProtection: TCheckBox;
    chbOrgFlag: TCheckBox;
    chbCopyFlag: TCheckBox;
    chbPrivFlag: TCheckBox;
    cbStreamType: TComboBox;
    Label20: TLabel;
    chbMultiplexAV: TCheckBox;
    fedOut: TFilenameEdit;
    tsDVD: TTabSheet;
    btnBuildDVD: TButton;
    pBarDVD1: TProgressBar;
    fedDVD: TFilenameEdit;
    Label21: TLabel;
    dedDVDOut: TDirectoryEdit;
    Label22: TLabel;
    lblDVDStats: TLabel;
    btnStopBuild: TButton;
    pBarDVD2: TProgressBar;
    fedBMP: TFilenameEdit;
    edTextOverlay: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    edFontSize: TEdit;
    Label3: TLabel;
    chbGraphEdit: TCheckBox;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure cbStreamTypeChange(Sender: TObject);
    procedure DVDProcessing(Sender: TObject; iPos: Integer);
    procedure fedInChange(Sender: TObject);
    procedure fedDVDChange(Sender: TObject);
    procedure btnBuildDVDClick(Sender: TObject);
    procedure btnStopBuildClick(Sender: TObject);
    procedure DVDTotalProcessing(Sender: TObject; iPos, Step,
      Steps: Integer);
    procedure btnConvertClick(Sender: TObject);
    procedure btnStopClick(Sender: TObject);
  private
    { Private declarations }

    appDir              : String;
    WMVConvertThread    : TWMVConvertThread;

    function MakeOutFile(aFileName:String):String;
    procedure HandleMessage(var aMSG:TMessage); message WM_WMVMESSAGE;

  public
    { Public declarations }


  end;

var
  frmWMVConvert: TfrmWMVConvert;

implementation

{$R *.dfm}

procedure TfrmWMVConvert.FormCreate(Sender: TObject);
begin
 appDir := ExtractFilePath(Application.ExeName);
end;

function TfrmWMVConvert.MakeOutFile(aFileName: String): String;
var
 s : String;
begin
 s := aFileName;

 case cbStreamType.ItemIndex of
   0 : result := FixFileExt(s,'.xxx');
   1,
   2,
   3,
   4,
   5,
   6,
   7 : result := FixFileExt(s,'mpg');
   8 : result := FixFileExt(s,'mp4');
   9 : result := FixFileExt(s,'3gp');
  10 : result := FixFileExt(s,'mov');
  11 : result := FixFileExt(s,'3g2');
  12 : result := FixFileExt(s,'psp');
  13 : result := FixFileExt(s,'avi');
 end;

 Insert('"',result,1);
 result := result + '"';

end;

procedure TfrmWMVConvert.FormShow(Sender: TObject);
begin
 fedOut.Text := MakeOutFile(fedIn.FileName);
end;

procedure TfrmWMVConvert.cbStreamTypeChange(Sender: TObject);
begin
 fedOut.Text := MakeOutFile(fedIn.FileName);
 if cbStreamType.ItemIndex = 5 then
  fedDVD.Text := MakeOutFile(fedIn.FileName);
end;

procedure TfrmWMVConvert.DVDProcessing(Sender: TObject; iPos: Integer);
begin
 pBarDVD2.Position := iPos;
end;

procedure TfrmWMVConvert.fedInChange(Sender: TObject);
begin
 fedOut.Text := MakeOutFile(fedIn.FileName);
 if cbStreamType.ItemIndex = 5 then
  fedDVD.Text := MakeOutFile(fedIn.FileName);

end;

procedure TfrmWMVConvert.fedDVDChange(Sender: TObject);
var
 s : string;
begin
 s := ExtractFilePath(fedDVD.FileName);

 if s[length(s)]<>'\' then s:=s+'\';

 dedDVDOut.Text := s;
end;

procedure TfrmWMVConvert.btnBuildDVDClick(Sender: TObject);
begin

{ dvd.NoMenu := true;
 dvd.OutputDir := dedDVDOut.EditText;
 dvd.AddMenuButton(1,1,100,100,0,fedDVD.FileName);

 dvd.BuildDVDImage; }
 
end;

procedure TfrmWMVConvert.btnStopBuildClick(Sender: TObject);
begin
// dvd.StopBuildDVDImage;
end;

procedure TfrmWMVConvert.DVDTotalProcessing(Sender: TObject; iPos, Step,
  Steps: Integer);
begin

{ if step <= steps then
  begin
   lblDVDStats.Caption := 'Building '+IntToStr(step)+' of '+
                          intToStr(steps)+' steps.';
   with pBarDVD1 do
    begin
     Min := 1;
     Max := steps;
     Position := step;
     Application.ProcessMessages;
    end;
  end;   }

end;
procedure TfrmWMVConvert.HandleMessage(var aMSG: TMessage);
begin
 try
 if aMSG.Msg = WM_WMVMESSAGE then
  case aMSG.WParam of
   lbl1MSG : lblInfo1.Caption := wmvinfo1;
   lbl2MSG : lblInfo2.Caption := wmvinfo2;
   lbl3MSG : lblInfo3.Caption := wmvinfo3;
   lbl4MSG : lblInfo4.Caption := wmvinfo4;
   lbl5MSG : lblInfo5.Caption := wmvinfo5;
   progMSG : pBar.Position := wmvProgress;
  end; // case
 except on E:Exception do
  DebugLog(AppDir,E.Message);
 end;
end;

{ TWMVConvertThread }

procedure TWMVConvertThread.Execute;
begin
 StartConversion;
end;

procedure TWMVConvertThread.StartConversion;
var
 hr      : HRESULT;

begin

 WMVConv := TWMVConvert.Create;

 hr := WMVConv.ConvertFile( pHWND, pAppDir, inWMVFile,
                            outFile, StringToOverlay,
                            BMPOverlayFile, FontSize, VStreamType,
                            vWidth, vHeight,
                            BitrateControl, VBitrateKBps,
                            VBitrateMinKBps, VBitrateMaxKBps,
                            AspectRatio, VBVBuffer, AStreamType,
                            aSampleRate, aChannels, aBitRateKBps,
                            StreamType, FrameRate, ErrorProtection,
                            OriginalFlag, CopyrightFlag,
                            PrivateFlag, noVideoPreview,
                            ShowInGraphEdit, prevPanel);

 if failed( hr ) then
  frmWMVConvert.lblInfo1.Caption := 'FAILED: '+HRToStr(hr);



end;

procedure TfrmWMVConvert.btnConvertClick(Sender: TObject);
begin

 WMVConvertThread := TWMVConvertThread.Create(true);

 with WMVConvertThread do
  begin

   Priority := tpNormal;
   FreeOnTerminate := True;

    pHWND               := frmWMVConvert.Handle;
    pAppDir             := AppDir;
    inWMVFile           := fedIn.FileName;
    outFile             := fedOut.FileName;
    StringToOverlay     := edTextOverlay.Text;
    BMPOverlayFile      := fedBMP.FileName;
    FontSize            := StrToIntDef(edFontSize.Text, 24);
    VStreamType         := cbVideoStream.ItemIndex;
    VWidth              := StrToInt(cbWidth.Text);
    VHeight             := StrToInt(cbHeight.Text);
    BitrateControl      := cbBitrateControl.ItemIndex;
    VBitrateKBps        := StrToInt(edVideoBitrate.Text);
    VBitrateMinKBps     := StrToInt(edVideoBitrateMin.Text);
    VBitrateMaxKBps     := StrToInt(edVideoBitrateMax.Text);
    AspectRatio         := cbAspect.ItemIndex;
    VBVBuffer           := StrToInt(edVBVBufferSize.Text);
    AStreamType         := cbAudioStream.ItemIndex;
    ASampleRate         := StrToInt(cbAudioSample.Text);
    AChannels           := cbAudioChannels.ItemIndex;
    ABitrateKBps        := StrToInt(cbAudioBitrate.Text);
    StreamType          := cbStreamType.ItemIndex;
    FrameRate           := StrToFloat(cbFPS.Text);
    ErrorProtection     := chbErrorProtection.Checked;
    OriginalFlag        := chbOrgFlag.Checked;
    CopyrightFlag       := chbCopyFlag.Checked;
    PrivateFlag         := chbPrivFlag.Checked;
    noVideoPreview      := chbNoPreview.Checked;
    ShowInGraphEdit     := chbGraphEdit.Checked;
    prevPanel           := pnlVW;

   RESUME;

  end;
end;

procedure TWMVConvertThread.StopConvertsion;
begin
 if WMVConv <> nil then WMVConv.StopProgress;

 frmWMVConvert.lblInfo1.Caption := 'ABORTED !';
 Application.ProcessMessages;
 
end;

procedure TfrmWMVConvert.btnStopClick(Sender: TObject);
begin
 if Assigned(WMVConvertThread) then
 if not WMVConvertThread.Terminated then
  WMVConvertThread.StopConvertsion;
end;

end.
