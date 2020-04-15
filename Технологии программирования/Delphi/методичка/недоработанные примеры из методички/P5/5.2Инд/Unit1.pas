unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Buttons, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    ListBox1: TListBox;
    ButtonTestData: TButton;
    ButtonClearListBox: TButton;
    BitBtn1: TBitBtn;
    ButtonInt: TButton;
    ButtonFloat1: TButton;
    LabelInt: TLabel;
    LabelFloat1: TLabel;
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure ButtonTestDataClick(Sender: TObject);
    procedure ButtonClearListBoxClick(Sender: TObject);
    procedure ButtonIntClick(Sender: TObject);
    procedure ButtonFloat1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);
begin
  if Key = #13 then  //���� ������ ������� Enter
  begin
    ListBox1.Items.Add(Edit1.Text); //��������� � ListBox1 ������
    Edit1.Text:='������� ������ � ������� Enter';
//�������� Tag ������� ListBox1 ���������� ��� �������� ���-�� ����� � ListBox1
    ListBox1.Selected[ListBox1.Tag]:=true; //�������� � ListBox1 ��������� ������
    ListBox1.Tag:=ListBox1.Tag+1;
  end;
end;

procedure TForm1.ButtonTestDataClick(Sender: TObject);
var f: TextFile;
    str: String;
begin
  AssignFile(f,'In.txt'); //������������� ����� ����� �������� ���������� � ������
  try
    Reset(f); //��������� ���� ��� ������
    while not SeekEOF(f) do //���� �� ����� �����
    begin
      ReadLn(f,str);  //��������� ������ �� ����� � ���������� str
      ListBox1.Items.Add(str);  //��������� ������ � ListBox1
      ListBox1.Tag:=ListBox1.Tag+1; //����������� ������� ����� �����
    end;
    if ListBox1.Tag <> 0 then //���� � listBox1 ���� ������ ���� ������
      ListBox1.Selected[ListBox1.Tag-1]:=true; //�������� ��������� ������
    CloseFile(f); //��������� ����
  except
    ShowMessage('������ ������ �� �����!');
  end;
end;

procedure TForm1.ButtonClearListBoxClick(Sender: TObject);
begin
  ListBox1.Clear;  //������� ListBox1
  ListBox1.Tag:=0; //�������� ������� ���-�� �����
end;

procedure TForm1.ButtonIntClick(Sender: TObject);
const symb: Set of Char = ['+','-','0'..'9']; //���������-���������, ��������� �� +,-,0,1,2,3,4,5,6,7,8,9
var str,st: String;
    i: Integer;
    flag: Boolean;
begin
  try
    str:=ListBox1.Items[ListBox1.ItemIndex];  //���������� � str ���������� � ListBox ������
  except
    ShowMessage('�������� ������!');
    Exit; //����� �� ���������
  end;
  str:=str+' '; //��� ���������� ���������� ����� �� ������ str ���������� ������� �� ���� ������ ������-���� �������
  st:=''; //� st ������ ����� ��������, ������� ���������������� �������� ������
  flag:=false; //���� flag ����� true, �� st �������� ����� ��������, ����������, ����������������, ������
  LabelInt.Caption:='';
  for i:=1 to length(str) do  //������� Length(str) ���������� ����� ������ str
    if str[i] in symb then  //���� i-��� ������ �� ������ str ���������� � ���������-��������� symb
    begin
      st:=st+str[i];
      flag:=true;
    end else
      if flag then //���� st �������� ����� ��������
      begin
//�������� ��������������� ���������� ������ st � ����� �����
//���� �������, �� ������� ��� ����� �����
        try
          StrToInt(st);
          LabelInt.Caption:=LabelInt.Caption+' '+st;
        except
        end;
        flag:=false;
        st:='';
      end;
  if LabelInt.Caption = '' then
    LabelInt.Caption:='������ �� �������� ����� �����';
end;

procedure TForm1.ButtonFloat1Click(Sender: TObject);
const symb: Set of Char = ['.','+','-','0'..'9'];
var str,st: String;
    i: Integer;
    flag,flag2: Boolean;
begin
  try
    str:=ListBox1.Items[ListBox1.ItemIndex];
  except
    ShowMessage('�������� ������!');
    Exit;
  end;
  str:=str+' ';
  st:='';
  flag:=false;
  flag2:=false;  //���� flag2 ����� true, �� ������ st �������� �����
  LabelFloat1.Caption:='';
  for i:=1 to length(str) do
    if str[i] in symb then
    begin
      st:=st+str[i];
      flag:=true;
      if str[i] = '.' then
        flag2:=true;
    end else
      if flag then
      begin
        if flag2 then //���� ������ st �������� �����
          try
            StrToFloat(st);
            LabelFloat1.Caption:=LabelFloat1.Caption+' '+st;
          except
          end;
        flag:=false;
        flag2:=false;
        st:='';
      end;
  if LabelFloat1.Caption = '' then
    LabelFloat1.Caption:='������ �� �������� �������. ����� � ������������� ������';
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  DecimalSeparator:='.';  //������������� � �������� ����������� ����� � ������� ������ - �����
end;

end.
