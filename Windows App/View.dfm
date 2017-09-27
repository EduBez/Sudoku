object View: TView
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = ' SUDOKU! '
  ClientHeight = 451
  ClientWidth = 310
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Grid: TStringGrid
    Left = 14
    Top = 8
    Width = 282
    Height = 282
    ColCount = 9
    DefaultColWidth = 30
    DefaultRowHeight = 30
    FixedCols = 0
    RowCount = 9
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssNone
    TabOrder = 0
    OnDrawCell = OnGridDrawCell
    ColWidths = (
      30
      30
      30
      30
      30
      30
      30
      30
      30)
    RowHeights = (
      30
      30
      30
      30
      30
      30
      30
      30
      30)
  end
  object BtnFile: TButton
    Left = 36
    Top = 405
    Width = 75
    Height = 25
    Caption = '&File'
    DropDownMenu = FileMenu
    Style = bsSplitButton
    TabOrder = 1
    OnClick = OnOpenClick
  end
  object BtnGen: TButton
    Left = 117
    Top = 405
    Width = 75
    Height = 25
    Caption = '&Generate'
    DropDownMenu = GenMenu
    Style = bsSplitButton
    TabOrder = 2
    OnClick = OnGenerateClick
  end
  object BtnRun: TButton
    Left = 198
    Top = 405
    Width = 75
    Height = 25
    Caption = '&Solve'
    TabOrder = 3
    OnClick = OnSolveClick
  end
  object GroupBox: TGroupBox
    Left = 14
    Top = 299
    Width = 282
    Height = 86
    Caption = ' Backtrack Algorithm '
    TabOrder = 4
    object LblBacktracks: TLabel
      Left = 139
      Top = 29
      Width = 51
      Height = 13
      Caption = 'Backtracks'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Backtracks: TLabel
      Left = 212
      Top = 29
      Width = 60
      Height = 13
      AutoSize = False
    end
    object FromNumber: TLabel
      Left = 16
      Top = 32
      Width = 64
      Height = 13
      Caption = 'From Number'
    end
    object LblElapse: TLabel
      Left = 139
      Top = 50
      Width = 62
      Height = 13
      Caption = 'Elapsed Time'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Elapsed: TLabel
      Left = 212
      Top = 50
      Width = 60
      Height = 13
      AutoSize = False
    end
    object ComboBox: TComboBox
      Left = 86
      Top = 29
      Width = 40
      Height = 22
      Style = csOwnerDrawFixed
      ItemIndex = 0
      TabOrder = 0
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9')
    end
  end
  object SaveDialog: TSaveDialog
    Filter = 'Text Documents|*.txt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 192
    Top = 21
  end
  object OpenDialog: TOpenDialog
    Filter = 'Text Documents|*.txt'
    Left = 164
    Top = 21
  end
  object FileMenu: TPopupMenu
    Left = 220
    Top = 21
    object Clear: TMenuItem
      Caption = '&Clear'
      OnClick = OnClearClick
    end
    object Save: TMenuItem
      Caption = '&Save'
      OnClick = OnSaveClick
    end
  end
  object GenMenu: TPopupMenu
    Left = 248
    Top = 21
    object Easy: TMenuItem
      Caption = 'Easy'
      Checked = True
      GroupIndex = 1
      OnClick = OnMenuItemClick
    end
    object Medium: TMenuItem
      Tag = 1
      Caption = 'Medium'
      GroupIndex = 1
      OnClick = OnMenuItemClick
    end
    object Hard: TMenuItem
      Tag = 2
      Caption = 'Hard'
      GroupIndex = 1
      OnClick = OnMenuItemClick
    end
  end
end
