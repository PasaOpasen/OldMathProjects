unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, Spin, Buttons, XPMan;

type
  TForm1 = class(TForm)
    SpinEdit1: TSpinEdit;
    ProgressBar1: TProgressBar;
    Button1: TButton;
    Button2: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    XPManifest1: TXPManifest;
    BitBtn1: TBitBtn;
    Label1: TLabel;
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button2Click(Sender: TObject);
var
  f: File of real;
  k: integer;
  BegTime: TDateTime;
  r: real;
begin
  BegTime:= Time;
  ProgressBar1.Max:= SpinEdit1.Value;
  ProgressBar1.Position:= 0;
  ProgressBar1.Show;
  AssignFile(f,'Test.dat');
  Rewrite(f);
  for k:= 1 to SpinEdit1.Value do
  begin
    r:= random;
    write(f,r);
    Label4.Caption:= IntToStr(k);
    ProgressBar1.Position:= k;
    Application.ProcessMessages;
  end;
  CloseFile(f);
  ProgressBar1.Hide;
  Label4.Caption:= FormatDateTime('hh:mm:ss.zzz',Time - BegTime);
end;

procedure TForm1.Button1Click(Sender: TObject);
type
  PReal = ^Real;
var
  HFile, HMap: THandle;
  AdrBase, AdrReal: PReal;
  k: integer;
  FSize: Cardinal;
  BegTime: TDateTime;
begin
  BegTime:= Time;
  ProgressBar1.Max:= SpinEdit1.Value;
  ProgressBar1.Position:= 0;
  ProgressBar1.Show;
  FSize:= SizeOf(Real)*SpinEdit1.Value; // ������ ������ �����
  HFile:=FileCreate('Test.dat');  // ������� ����
  If HFile=0 then    // ? ��� ������ � ����� ����������
    raise Exception.Create('������ �������� �����');
  try // ? ����� ����� TRY, ���� RAISE - ��� ����������, ������� ������������� ��������. ���� ��� �� ���, �� ������ �� ����� ��� TRY
    HMap:= CreateFileMapping(HFile, NIL, PAGE_READWRITE, 0, FSize, NIL);  // ? ������ ASSIGN
    If HMap = 0 then
      raise Exception.Create('������ ����������� �����');
    try
      AdrBase:= MapViewOfFile(HMap, FILE_MAP_WRITE, 0, 0, FSize); // ? ������ RESET
      If AdrBase = NIL then
        raise Exception.Create('���������� ����������� ����');
      AdrReal:= AdrBase;    // ? ����� ������ ��������������
      for k:= 1 to SpinEdit1.Value do
      begin
        AdrReal^:= Random;
        AdrReal:= Pointer(Integer(AdrReal) + SizeOf(Real)); // ? ��� ���
        Label3.Caption:= IntToStr(k);
        ProgressBar1.Position:= k;
        Application.ProcessMessages;
      end;
      UnmapViewOfFile(AdrBase)
    finally
      CloseHandle(HMap)
    end                // ? ����� ���� ��������� ���
  finally
    CloseHandle(HFile)
  end;
  ProgressBar1.Hide;
  Label3.Caption:= FormatDateTime('hh:mm:ss.zzz',Time - BegTime);
end;

end.
