object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'TrafficEye'
  ClientHeight = 506
  ClientWidth = 697
  Color = clMidnightblue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object DBGrid1: TDBGrid
    Left = 136
    Top = 96
    Width = 425
    Height = 225
    Color = clMidnightblue
    DataSource = DataSource1
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    OnDrawColumnCell = DBGrid1DrawColumnCell
  end
  object Button1: TButton
    Left = 24
    Top = 24
    Width = 137
    Height = 33
    Caption = 'Back'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Bell MT'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button1Click
  end
  object FDQuery1: TFDQuery
    Connection = FDConnection1
    Left = 560
    Top = 120
  end
  object FDConnection1: TFDConnection
    Params.Strings = (
      'DriverID=SQLite'
      'Database=C:\Users\carl\Downloads\TrafficEyez\gui\trafficeye.db')
    LoginPrompt = False
    Left = 384
    Top = 368
  end
  object DataSource1: TDataSource
    DataSet = FDQuery1
    Left = 504
    Top = 320
  end
end
