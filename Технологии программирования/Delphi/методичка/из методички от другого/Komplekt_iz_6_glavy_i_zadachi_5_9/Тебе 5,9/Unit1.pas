unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Buttons;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    ListBox1: TListBox;
    ButtonTestData: TButton;
    ButtonClearListBox: TButton;
    ButtonShowLower: TButton;
    ButtonShowUpper: TButton;
    BitBtn1: TBitBtn;
    PanelShowLower: TPanel;
    PanelShowUpper: TPanel;
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure ButtonTestDataClick(Sender: TObject);
    procedure ButtonClearListBoxClick(Sender: TObject);
    procedure ButtonShowLowerClick(Sender: TObject);
    procedure ButtonShowUpperClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}


procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);  //���������, ����������� ��� ������� �����-���� ������� � Edit1
begin
  if Key = #13 then  //���� ����� Enter
  begin
    ListBox1.Items.Add(Edit1.Text); //��������� � ListBox1 ���������� Edit1
    Edit1.Text:='������� ������ � ������� Enter';
    ListBox1.Selected[ListBox1.Tag]:=true;  //�������� ����������� � ListBox1 ������
    ListBox1.Tag:=ListBox1.Tag+1; //����������� ������� ���-�� ����� �� 1
  end;
end;

procedure TForm1.ButtonTestDataClick(Sender: TObject); //���������, ����������� ��� ������� �� ������ "������ �������� ������ �� �����"
var f: TextFile;
    str: String;
begin
  AssignFile(f,'In.txt'); //������������� ����� ����� �������� ���������� � ������
  try
    Reset(f);  //��������� ���� ��� ������
    while not SeekEOF(f) do  //���� �� ����� ����� ������
    begin
      ReadLn(f,str);  //��������� ������ �� ����� � ���������� str
      ListBox1.Items.Add(str);  //��������� � ListBox1 ������ str
      ListBox1.Tag:=ListBox1.Tag+1; //����������� ������� ���-�� ����� �� 1
    end;
    if ListBox1.Tag <> 0 then //���� ���-�� ����� � ListBox1 �� 0
      ListBox1.Selected[ListBox1.Tag-1]:=true; //�������� ��������� ������ � ListBox1
    CloseFile(f); //��������� ����
  except
    ShowMessage('������ ������ �� �����');
  end;
end;

procedure TForm1.ButtonClearListBoxClick(Sender: TObject); //���������, ����������� ��� ������� �� ������ "�������� ������ �����"
begin
  ListBox1.Clear;  //������� ListBox1
  ListBox1.Tag:=0; //�������� ������� ���-�� �����
end;

procedure TForm1.ButtonShowLowerClick(Sender: TObject); //���������, ����������� ��� ������� �� ������ "������� �������� ������� �����"
const lower: set of Char = ['�'..'�','�']; //���������-��������� �� ���� ������� �������� ����
var str,st: String;
    i: Integer;
begin
  try
    str:=ListBox1.Items[ListBox1.ItemIndex]; //��������� � ���������� str ���������� � ListBox1 ������
  except
    ShowMessage('�������� ������!');
    Exit; //����� �� ���������
  end;
  st:=''; //� ���������� st ������ ��� �������� ������� ����� �� ������ str
  for i:=1 to length(str) do //������� length(str) ���������� ����� ������ str
    if str[i] in lower then //���� i-��� ������ �� ������ str ����������� ��������� ���� ������� �������� ����
      st:=st+str[i]; //��������� � ������ st i-��� ������
  if st <> '' then //���� st �� �����
    PanelShowLower.Caption:=st //������� st
  else
    PanelShowLower.Caption:='��� �������� ������� ����!';
end;

procedure TForm1.ButtonShowUpperClick(Sender: TObject); //���������, ����������� ��� ������� �� ����� "������� ��������� ������� �����"
const upper: array [1..33] of Char = ('�','�','�','�','�','�','�','�','�','�','�','�','�', //���������-������ �� ���� ��������� ������� ����
                                      '�','�','�','�','�','�','�','�','�','�','�','�','�',
                                      '�','�','�','�','�','�','�');
var CharsMass: array [1..33] of Boolean; //����, ��������, CharsMass[2] ����� true, �� ������ str �������� ����� "�", CharsMass[33] ����� true, �� str �������� ����� "�"
    str: String;
    i,j: Integer;
begin
  try
    str:=ListBox1.Items[ListBox1.ItemIndex]; //��������� ���������� � ListBox1 ������ � ���������� str
  except
    ShowMessage('�������� ������!');
    Exit; //����� �� ���������
  end;
  for i:=1 to 33 do //�������, ��� str �� �������� �� ����� ��������� ������� �����
    CharsMass[i]:=false;
  for i:=1 to length(str) do
    for j:=1 to 33 do //���������� i-��� ������� ������ str �� ����� ���������� �������
      if str[i] = upper[j] then
        CharsMass[j]:=true;
  str:=''; //������ � str ������ � ���������� ������� ��������� ������� ����� �� ������ str
  for i:=1 to 33 do
    if CharsMass[i] then
      str:=str+upper[i];
  if str <> '' then
    PanelShowUpper.Caption:=str
  else
    PanelShowUpper.Caption:='��� ��������� ������� ����!';

end;

end.
