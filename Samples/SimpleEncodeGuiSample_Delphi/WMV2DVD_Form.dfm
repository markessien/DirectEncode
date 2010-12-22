object frmWMVConvert: TfrmWMVConvert
  Left = 278
  Top = 182
  Width = 545
  Height = 381
  Caption = 'WMV 2 DVD'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lblInfo1: TLabel
    Left = 16
    Top = 73
    Width = 40
    Height = 16
    Caption = '[ Info ]'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblInfo2: TLabel
    Left = 16
    Top = 90
    Width = 40
    Height = 16
    Caption = '[ Info ]'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblInfo3: TLabel
    Left = 16
    Top = 107
    Width = 40
    Height = 16
    Caption = '[ Info ]'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblInfo5: TLabel
    Left = 16
    Top = 140
    Width = 40
    Height = 16
    Caption = '[ Info ]'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblInfo4: TLabel
    Left = 16
    Top = 123
    Width = 40
    Height = 16
    Caption = '[ Info ]'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object fedIn: TFilenameEdit
    Left = 16
    Top = 8
    Width = 505
    Height = 21
    Filter = 'WMV|*.wmv'
    NumGlyphs = 1
    TabOrder = 0
    Text = 
      'C:\WMS Test applications\Montivision graphs and test\TEST_MAINCO' +
      'NCEPT_WMV.wmv'
    OnChange = fedInChange
  end
  object btnPlay: TButton
    Left = 448
    Top = 110
    Width = 75
    Height = 25
    Caption = 'Play'
    TabOrder = 1
  end
  object btnStop: TButton
    Left = 448
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Stop'
    TabOrder = 2
    OnClick = btnStopClick
  end
  object btnConvert: TButton
    Left = 448
    Top = 80
    Width = 75
    Height = 25
    Caption = 'Convert'
    TabOrder = 3
    OnClick = btnConvertClick
  end
  object pnlVW: TPanel
    Left = 328
    Top = 80
    Width = 113
    Height = 81
    BevelOuter = bvLowered
    TabOrder = 4
  end
  object pBar: TProgressBar
    Left = 328
    Top = 166
    Width = 193
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 5
  end
  object chbNoPreview: TCheckBox
    Left = 328
    Top = 60
    Width = 77
    Height = 17
    Caption = 'No preview'
    TabOrder = 6
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 184
    Width = 521
    Height = 153
    ActivePage = tsVideo
    TabIndex = 0
    TabOrder = 7
    object tsVideo: TTabSheet
      Caption = 'Video'
      object Label6: TLabel
        Left = 192
        Top = 64
        Width = 63
        Height = 13
        Caption = 'Target bitrate'
      end
      object Label7: TLabel
        Left = 272
        Top = 64
        Width = 49
        Height = 13
        Caption = 'Bitrate min'
      end
      object Label8: TLabel
        Left = 328
        Top = 64
        Width = 52
        Height = 13
        Caption = 'Bitrate max'
      end
      object Label9: TLabel
        Left = 400
        Top = 64
        Width = 73
        Height = 13
        Caption = 'VBV Buffer size'
      end
      object Label10: TLabel
        Left = 16
        Top = 64
        Width = 94
        Height = 13
        Caption = 'Bitrate control mode'
      end
      object Label11: TLabel
        Left = 16
        Top = 16
        Width = 84
        Height = 13
        Caption = 'Video stream type'
      end
      object Label12: TLabel
        Left = 168
        Top = 16
        Width = 55
        Height = 13
        Caption = 'Video width'
      end
      object Label13: TLabel
        Left = 248
        Top = 16
        Width = 31
        Height = 13
        Caption = 'Height'
      end
      object Label14: TLabel
        Left = 328
        Top = 16
        Width = 56
        Height = 13
        Caption = 'Aspect ratio'
      end
      object Label15: TLabel
        Left = 432
        Top = 16
        Width = 47
        Height = 13
        Caption = 'Framerate'
      end
      object cbVideoStream: TComboBox
        Left = 16
        Top = 32
        Width = 145
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 2
        TabOrder = 0
        Text = 'MPEG-2 Video'
        Items.Strings = (
          'No video stream'
          'MPEG-1 Video'
          'MPEG-2 Video'
          'MPEG-4 Video'
          'H.263'
          'H.264')
      end
      object cbWidth: TComboBox
        Left = 168
        Top = 32
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 1
        Text = '720'
        Items.Strings = (
          '352'
          '720')
      end
      object cbHeight: TComboBox
        Left = 248
        Top = 32
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 2
        Text = '576'
        Items.Strings = (
          '280'
          '576')
      end
      object cbAspect: TComboBox
        Left = 328
        Top = 32
        Width = 97
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 2
        TabOrder = 3
        Text = '16:9 Display'
        Items.Strings = (
          '1:1 VGA Pixel'
          '4:3 Display'
          '16:9 Display'
          '2.21:1 Display')
      end
      object cbFPS: TComboBox
        Left = 432
        Top = 32
        Width = 73
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 2
        TabOrder = 4
        Text = '25'
        Items.Strings = (
          '23.979'
          '24'
          '25'
          '29.97'
          '30'
          '50'
          '59.94'
          '60')
      end
      object cbBitrateControl: TComboBox
        Left = 16
        Top = 80
        Width = 169
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 2
        TabOrder = 5
        Text = 'Manual VBR (bitrate range)'
        Items.Strings = (
          'Constant bitrate'
          '2-Pass VBR (calculated 1st pass)'
          'Manual VBR (bitrate range)'
          'Automatic VBR (guess bitrate)')
      end
      object edVideoBitrate: TEdit
        Left = 192
        Top = 80
        Width = 65
        Height = 21
        TabOrder = 6
        Text = '6000'
      end
      object edVideoBitrateMin: TEdit
        Left = 272
        Top = 80
        Width = 41
        Height = 21
        TabOrder = 7
        Text = '2500'
      end
      object edVideoBitrateMax: TEdit
        Left = 328
        Top = 80
        Width = 41
        Height = 21
        TabOrder = 8
        Text = '8000'
      end
      object edVBVBufferSize: TEdit
        Left = 400
        Top = 80
        Width = 41
        Height = 21
        TabOrder = 9
        Text = '0'
      end
    end
    object tsAudio: TTabSheet
      Caption = 'Audio'
      ImageIndex = 1
      object Label16: TLabel
        Left = 16
        Top = 16
        Width = 84
        Height = 13
        Caption = 'Audio stream type'
      end
      object Label17: TLabel
        Left = 160
        Top = 16
        Width = 93
        Height = 13
        Caption = 'Sampling frequency'
      end
      object Label18: TLabel
        Left = 304
        Top = 16
        Width = 68
        Height = 13
        Caption = 'Channel mode'
      end
      object Label19: TLabel
        Left = 16
        Top = 64
        Width = 59
        Height = 13
        Caption = 'Audio bitrate'
      end
      object cbAudioStream: TComboBox
        Left = 16
        Top = 32
        Width = 137
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 2
        TabOrder = 0
        Text = 'MP2'
        Items.Strings = (
          'No audio'
          'MP3'
          'MP2'
          'AC3'
          'PCM'
          'WAV'
          'AAC')
      end
      object cbAudioBitrate: TComboBox
        Left = 16
        Top = 80
        Width = 137
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 2
        TabOrder = 1
        Text = '224'
        Items.Strings = (
          '64'
          '128'
          '224'
          '320'
          '384'
          '448')
      end
      object cbAudioSample: TComboBox
        Left = 160
        Top = 32
        Width = 129
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 2
        TabOrder = 2
        Text = '48000'
        Items.Strings = (
          '32000'
          '44100'
          '48000')
      end
      object cbAudioChannels: TComboBox
        Left = 304
        Top = 32
        Width = 129
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 1
        TabOrder = 3
        Text = 'Stereo'
        Items.Strings = (
          'Mono'
          'Stereo'
          'Surround 5.1')
      end
      object chbErrorProtection: TCheckBox
        Left = 168
        Top = 74
        Width = 97
        Height = 17
        Caption = 'Error Protection'
        TabOrder = 4
      end
      object chbOrgFlag: TCheckBox
        Left = 168
        Top = 90
        Width = 97
        Height = 17
        Caption = 'Original flag'
        TabOrder = 5
      end
      object chbCopyFlag: TCheckBox
        Left = 296
        Top = 74
        Width = 97
        Height = 17
        Caption = 'Copyright flag'
        TabOrder = 6
      end
      object chbPrivFlag: TCheckBox
        Left = 296
        Top = 90
        Width = 97
        Height = 17
        Caption = 'Private flag'
        TabOrder = 7
      end
    end
    object tsContainer: TTabSheet
      Caption = 'Container'
      ImageIndex = 2
      object Label20: TLabel
        Left = 16
        Top = 16
        Width = 59
        Height = 13
        Caption = 'Stream type:'
      end
      object cbStreamType: TComboBox
        Left = 16
        Top = 32
        Width = 241
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 5
        TabOrder = 0
        Text = 'MPEG-2 DVD'
        OnChange = cbStreamTypeChange
        Items.Strings = (
          'None'
          'MPEG-1'
          'MPEG-2'
          'MPEG-1 Video CD'
          'MPEG-2 Super Video CD'
          'MPEG-2 DVD'
          'Video CD Still'
          'Super Video CD Still'
          'MPEG-4'
          '3GP'
          'Quicktime MOV'
          '3G2'
          'PSP'
          'AVI (as MPEG-4 container)')
      end
      object chbMultiplexAV: TCheckBox
        Left = 16
        Top = 64
        Width = 153
        Height = 17
        Caption = 'Multiplex audio and video'
        TabOrder = 1
      end
    end
    object tsAdvanced: TTabSheet
      Caption = 'Advanced'
      ImageIndex = 3
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 58
        Height = 13
        Caption = 'Text overlay'
      end
      object Label2: TLabel
        Left = 8
        Top = 48
        Width = 124
        Height = 13
        Caption = 'Picture overlay ( filename )'
      end
      object Label3: TLabel
        Left = 424
        Top = 8
        Width = 42
        Height = 13
        Caption = 'Font size'
      end
      object fedBMP: TFilenameEdit
        Left = 8
        Top = 64
        Width = 497
        Height = 21
        Filter = 'Images|*.bmp;*.jpg'
        NumGlyphs = 1
        TabOrder = 0
      end
      object edTextOverlay: TEdit
        Left = 8
        Top = 24
        Width = 409
        Height = 21
        TabOrder = 1
        Text = 'edTextOverlay'
      end
      object edFontSize: TEdit
        Left = 424
        Top = 24
        Width = 81
        Height = 21
        TabOrder = 2
        Text = '24'
      end
    end
    object tsDVD: TTabSheet
      Caption = 'Make DVD'
      ImageIndex = 4
      object Label21: TLabel
        Left = 8
        Top = 4
        Width = 115
        Height = 13
        Caption = 'Select MPEG-2 DVD file'
      end
      object Label22: TLabel
        Left = 8
        Top = 44
        Width = 85
        Height = 13
        Caption = 'DVD output folder'
      end
      object lblDVDStats: TLabel
        Left = 8
        Top = 86
        Width = 56
        Height = 13
        Caption = 'DVD Status'
      end
      object btnBuildDVD: TButton
        Left = 336
        Top = 96
        Width = 89
        Height = 25
        Caption = 'Build DVD'
        TabOrder = 0
        OnClick = btnBuildDVDClick
      end
      object pBarDVD1: TProgressBar
        Left = 8
        Top = 101
        Width = 153
        Height = 17
        Min = 0
        Max = 100
        TabOrder = 1
      end
      object fedDVD: TFilenameEdit
        Left = 8
        Top = 20
        Width = 497
        Height = 21
        Filter = 'WMV|*.wmv'
        NumGlyphs = 1
        TabOrder = 2
        OnChange = fedDVDChange
      end
      object dedDVDOut: TDirectoryEdit
        Left = 8
        Top = 60
        Width = 497
        Height = 21
        NumGlyphs = 1
        TabOrder = 3
      end
      object btnStopBuild: TButton
        Left = 432
        Top = 96
        Width = 75
        Height = 25
        Caption = 'Stop build'
        TabOrder = 4
        OnClick = btnStopBuildClick
      end
      object pBarDVD2: TProgressBar
        Left = 168
        Top = 100
        Width = 161
        Height = 17
        Min = 0
        Max = 100
        TabOrder = 5
      end
    end
  end
  object fedOut: TFilenameEdit
    Left = 16
    Top = 32
    Width = 505
    Height = 21
    Filter = 'WMV|*.wmv'
    NumGlyphs = 1
    TabOrder = 8
  end
  object chbGraphEdit: TCheckBox
    Left = 432
    Top = 60
    Width = 77
    Height = 17
    Caption = 'Graphedit'
    TabOrder = 9
  end
  object timProg: TTimer
    Left = 240
    Top = 136
  end
  object rsStorage1: TrsStorage
    Active = True
    StorageData = rsIniData1
    Left = 208
    Top = 136
  end
  object rsIniData1: TrsIniData
    FileName = 'wmv2mpeg.ini'
    Options = []
    Left = 272
    Top = 136
  end
  object rsPropSaver1: TrsPropSaver
    Storage = rsStorage1
    RootSection = 'Form1.rsPropSaver1'
    Properties.Strings = (
      'chbCopyFlag.Checked'
      'chbErrorProtection.Checked'
      'chbMultiplexAV.Checked'
      'chbNoPreview.Checked'
      'chbOrgFlag.Checked'
      'chbPrivFlag.Checked'
      'edVBVBufferSize.Text'
      'edVideoBitrate.Text'
      'edVideoBitrateMax.Text'
      'edVideoBitrateMin.Text'
      'cbAspect.ItemIndex'
      'cbAudioBitrate.ItemIndex'
      'cbAudioChannels.ItemIndex'
      'cbAudioSample.ItemIndex'
      'cbAudioStream.ItemIndex'
      'cbBitrateControl.ItemIndex'
      'cbFPS.ItemIndex'
      'cbHeight.ItemIndex'
      'cbStreamType.ItemIndex'
      'cbVideoStream.ItemIndex'
      'cbWidth.ItemIndex'
      'fedIn.Text'
      'dedDVD.Text'
      'fedBMP.Text'
      'edTextOverlay.Text')
    WhenLoad = wlOnCreate
    WhenSave = wsOnClose
    Left = 176
    Top = 136
  end
end
