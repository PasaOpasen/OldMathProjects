unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Keyboard;

type
  TForm2 = class(TForm)
    TouchKeyboard1: TTouchKeyboard;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    GroupBox3: TGroupBox;
    Memo1: TMemo;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Button2: TButton;
    procedure FormKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    Ch: Word;
    b: boolean;
    hkl:integer;
  end;

function HEX2DEC(HEX: AnsiString): LONGINT;

var
  Form2: TForm2;

implementation

{$R *.dfm}

function HEX2DEC(HEX: AnsiString): LONGINT;
  function Digt(Ch: AnsiCHAR): BYTE;
  const
    HEXDigts: string[16] = '0123456789ABCDEF';
  var
    I: BYTE;
    N: BYTE;
  begin
    N := 0;
    for I := 1 to Length(HEXDigts) do
      if Ch = HEXDigts[I] then
        N := I - 1;
    Digt := N;
  end;
const
  HEXSet: set of CHAR = ['0'..'9', 'A'..'F'];

var
  J: LONGINT;
  Error: BOOLEAN;
  DEC: LONGINT;

begin
  DEC := 0;
  Error := False;
  for J := 1 to Length(HEX) do
  begin
    if not (UpCase(HEX[J]) in HEXSet) then
      Error := True;
    DEC:=DEC+Digt(UpCase(HEX[J])) shl ((Length(HEX) - J) * 4);
    { 16^N = 2^(N * 4) }
    { N SHL ((Length(HEX) - J) * 4) = N * 16^(Length(HEX) - J) }
  end;
  if Error then
    HEX2DEC := 0
  else
    HEX2DEC := DEC;
end;




procedure TForm2.Button1Click(Sender: TObject);
begin
  b := not b;
  if b then
   begin
     Label2.Caption := '��������';
   end
  else
    Label2.Caption := '�������'
end;

procedure TForm2.Button2Click(Sender: TObject);
var newHKL: PWideChar;
begin

hkl:=LoWord(GetKeyboardLayout(0)); //������� ������� ������
if hkl=1049 then //������� ���� - �������
  begin
    hkl:=1033; //�������� �� ����������
    newHKL:=PChar('0000'+IntToHex(hkl,4));
    LoadKeyboardLayout(newHKL,KLF_ACTIVATE);
    Button2.Caption:='En';
  end
else
  begin   //������� ���� - ����������
    hkl:=1049;
    newHKL:=PChar('0000'+IntToHex(1049,4));
    LoadKeyboardLayout(newHKL,KLF_ACTIVATE);
    Button2.Caption:='Ru';
  end;
Label9.Caption:=IntToStr(hkl);
label11.Caption:=IntToHex(hkl,4);
end;

procedure TForm2.FormKeyPress(Sender: TObject; var Key: Char);
begin
  if b then
  begin
    Ch := Ord(Key);
    Memo1.Lines.Add('++++ ������� ORD() ++++');
    Memo1.Lines.Add('������� ��������            ' + IntToStr(Ord(Key)));
  end;
end;

procedure TForm2.FormKeyUp(Sender: TObject; var Key: Word; Shift: TShiftState);
var
  VK, SC, C: cardinal;
  KS: TKeyboardState;
  Ch: Char;
begin
  if b then  //��� �������� �� �����������
  begin
    SC := MapVirtualKeyEx(Key, MAPVK_VK_TO_VSC,GetKeyboardLayout(0));// �������� ����-���
    VK := MapVirtualKeyEx(SC, MAPVK_VSC_TO_VK,GetKeyboardLayout(0));// ����-��� ����������� � ����������� ���
    C := MapVirtualKeyEx(VK, MAPVK_VK_TO_CHAR, GetKeyboardLayout(0));// ����������� ��� � ��� ������ �� ASCII
    //������� ��, ��� ������ ����� �� ������� ������
    GetKeyboardState(KS);

    Memo1.Lines.Add('++++ KeyUp() ++++');
    Memo1.Lines.Add('������� ��������            ' + IntToStr(Key));
    Memo1.Lines.Add('++++ �������� ������� MapVirtualKey() ++++');
    Memo1.Lines.Add('����-��� �������            ' + IntToStr(SC));
    Memo1.Lines.Add('����������� ��� ������      ' + IntToStr(VK));
    Memo1.Lines.Add('�� ��������� �������� ASCII ' + IntToStr(C));
    Label5.Caption := IntToStr(Key);
    Label7.Caption := Chr(Key);
    Memo1.Lines.Add('++++ �������������� ����� � ������ ++++');
    Memo1.Lines.Add('������� toUnicode ������� �������� '+IntToStr(ToUnicode(VK,SC,KS,@Ch,Sizeof(Ch),0)));
    Memo1.Lines.Add('� ����� �������� ������   "'+Ch+'"');

  end;
end;

end.
