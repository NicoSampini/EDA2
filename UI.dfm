object InterfazGrafica: TInterfazGrafica
  Left = 0
  Top = 0
  Caption = 'InterfazGrafica'
  ClientHeight = 650
  ClientWidth = 960
  Color = $00AAB2B8
  Font.Charset = DEFAULT_CHARSET
  Font.Color = $002C2F31
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  TextHeight = 15
  object ImageMapa: TImage
    Left = 248
    Top = 60
    Width = 465
    Height = 559
    Center = True
    Stretch = True
  end
  object RioTercero: TLabel
    Left = 432
    Top = 288
    Width = 58
    Height = 15
    Caption = 'Rio Tercero'
    Layout = tlCenter
    Visible = False
  end
  object Titulo: TLabel
    Left = 372
    Top = 14
    Width = 216
    Height = 37
    Caption = 'Mapa de Cordoba'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = $002C2F31
    Font.Height = -27
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object TituloDatos: TLabel
    Left = 815
    Top = 24
    Width = 47
    Height = 25
    Caption = 'Datos'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = $002C2F31
    Font.Height = 25
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    Transparent = False
    Visible = False
  end
  object BellVille: TLabel
    Left = 516
    Top = 344
    Width = 44
    Height = 15
    Caption = 'Bell Ville'
    Visible = False
  end
  object OrigenCB: TComboBox
    Left = 24
    Top = 74
    Width = 204
    Height = 23
    TabOrder = 0
    Text = 'Origen'
  end
  object DestinoCB: TComboBox
    Left = 24
    Top = 124
    Width = 204
    Height = 23
    TabOrder = 1
    Text = 'Destino'
  end
  object BtnBuscar: TButton
    Left = 24
    Top = 174
    Width = 96
    Height = 33
    Caption = 'Buscar'
    TabOrder = 2
    OnClick = BtnBuscarClick
  end
  object BtnSalir: TButton
    Left = 56
    Top = 580
    Width = 145
    Height = 33
    Caption = 'Salir'
    TabOrder = 3
    OnClick = BtnSalirClick
  end
  object CortarRutaBtn: TButton
    Left = 132
    Top = 174
    Width = 96
    Height = 33
    Caption = 'Cortar/restaurar ruta'
    TabOrder = 4
    WordWrap = True
    OnClick = CortarRutaBtnClick
  end
  object MemoDatos: TMemo
    Left = 744
    Top = 60
    Width = 192
    Height = 190
    Lines.Strings = (
      '')
    ReadOnly = True
    TabOrder = 5
  end
end
