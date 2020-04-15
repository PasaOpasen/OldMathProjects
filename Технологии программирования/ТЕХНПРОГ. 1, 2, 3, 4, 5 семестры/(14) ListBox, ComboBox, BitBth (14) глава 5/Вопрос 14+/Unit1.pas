unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    ComboBox1: TComboBox;
    Label2: TLabel;
    Label3: TLabel;
    BitBtn1: TBitBtn;
    GroupBox1: TGroupBox;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    Button1: TButton;
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure Label3Click(Sender: TObject);
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


procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);
begin
  if key = #13 then
  begin    //���� ������ ������� Enter
           //������ �� ���� �������������� ��������� � ������ ������
     ComboBox1.Items.Add(Edit1.Text);  // �������� � ������ ����� �� ������ ������
     Edit1.Text:=''; // ������� ���� ��������������
  end;
end;

procedure TForm1.Label3Click(Sender: TObject);
var sum,position: Integer;
    str: String;
begin
  str:=ComboBox1.Text;
  str:=str+' ';  //�������� ������������
  sum:=0;
  while str <> '' do
  begin
    position:=Pos(' ',str);
    if position > 1 then
      sum:=sum+1;
    Delete(str,1,position);
  end;
  Label3.Caption:=IntToStr(sum);  //��������� ����� � ��������� ������
end;



procedure TForm1.Button1Click(Sender: TObject);
var n,i: Integer;
    f: TextFile;
    str: String;
begin
  if RadioButton1.Checked
    then n:=0         //���������� ��������� �� ������
    else  if RadioButton2.Checked then n:=1
                                  else n:=2;
  AssignFile(f,'In.txt'); //����� ����������� � ����������� ������
  try                                                     // ���������� ����
    Reset(f);  //�������� ��� ������, ������� ������ �������
    for i:=1 to n do ReadLn(f);  //��������� ��������� �� ����.������.
    Read(f,str);   //������ �������� �� �����
    Edit1.Text:=str;
    CloseFile(f);  //�������� �����
  except
    ShowMessage('������ ������ �� �����');
  end;
end;

end.
