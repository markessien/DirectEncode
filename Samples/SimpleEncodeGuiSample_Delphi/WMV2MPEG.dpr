program WMV2MPEG;

uses
  CoInit in 'CoInit.pas',
  Forms,
  WMV2DVD_Form in 'WMV2DVD_Form.pas' {frmWMVConvert},
  Common in '..\Montivision graphs and test\Common.pas',
  StandardMpegEncoderLib_TLB2 in 'StandardMpegEncoderLib_TLB2.pas',
  DS_Common in '..\Montivision graphs and test\DS_Common.pas',
  MVFilterCommon in '..\Montivision graphs and test\MVFilterCommon.pas',
  MVBitmapOverlay_TLB in '..\Montivision graphs and test\MVBitmapOverlay_TLB.pas',
  MVTextOverlay_TLB in '..\Montivision graphs and test\MVTextOverlay_TLB.pas',
  MPEGEnc in '..\Montivision graphs and test\MPEGEnc.pas',
  WMVConvert in '..\..\Master-IT v1.0 - Source\Shared forms\WMVConvert.pas',
  MASTERIT_Common in '..\..\Master-IT v1.0 - Source\Shared forms\MASTERIT_Common.pas',
  StandardMpegEncoderLib_TLB in 'StandardMpegEncoderLib_TLB.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmWMVConvert, frmWMVConvert);
  Application.Run;
end.
