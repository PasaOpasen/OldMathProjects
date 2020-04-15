unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    edt1: TEdit;
    btn1: TButton;
    strngrd1: TStringGrid;
    strngrd2: TStringGrid;
    strngrd3: TStringGrid;
    btn2: TButton;
    RadioGroup1: TRadioGroup;
    Label2: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
    procedure RadioGroup1Click(Sender: TObject);
    procedure btnFilleClick(Sender: TObject);
    procedure btnKeyboardClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
type
  Matr = array[1..10,1..10] of real;
  Vct = array[1..10] of Real;
var
  Form1: TForm1;
  n : Integer;
  
implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
var i,j:Integer;
begin
  // ������ �������������� ������
  n:=3; //����������� �������
  edt1.Text:=FloatToStr(n); // ������� �� �����
  for j:=1 to n do
  for i:=1 to n do
  begin
    strngrd1.Cells[i,j]:=intToStr(i+j);
    strngrd2.Cells[0,i]:=intToStr(i);
  end;
  // ������� ����� �������� � ����� � ��������
  strngrd1.ColCount:=n+1;
  strngrd1.RowCount:=n+1;
  strngrd2.RowCount:=n+1;
  strngrd3.RowCount:=n+1;
  // ���������� ����� ������� ������ ������ ����������
  strngrd1.Cells[0,0]:=' �';
  strngrd2.Cells[0,0]:='������ B:';
  strngrd3.Cells[0,0]:='������ Y:';
  // ���������� ������ ��o���� � ������ ������� � ����������� ��������� i =1,2..n; j=1,2..n
  for i:=1 to n do
  begin
    strngrd1.Cells[0,i]:='i='+intToStr(i);
    strngrd1.Cells[i,0]:='j='+intToStr(i);
  end;
end;

// ������ : "������ �����������!"
procedure TForm1.btn1Click(Sender: TObject);
var i,j:Integer;
begin
  try
    n:=StrToInt(edt1.Text);
    if (n<=0) or (n>10) then
      begin
        i:=0;
        i:=1 div i;
      end;
    except
    on EConvertError do
    ShowMessage('�� ����� ������� ����������� ������� � �������');
    on EDivByZero do
    ShowMessage('�� �������� ��������� ������y � ������ ��� n<0 ��� ��� n>10');
  end;
  

  //������� ����� ����� � �������� � ��������
  strngrd1.ColCount:=n+1;
  strngrd1.RowCount:=n+1;
  strngrd2.RowCount:=n+1;
  strngrd3.RowCount:=n+1;
  // ���������� ������ ������� � ������ ����������� ��������� i =1,2..n; j=1,2..n
  for i:=1 to n do
  begin
    strngrd1.Cells[0,i]:='i='+IntToStr(i);
    strngrd1.Cells[i,0]:='j='+IntToStr(i);
  end;
  // �������� �����
  for i:=1 to n do for j:=1 to n do
  begin
   strngrd1.Cells[i,j]:='';
   strngrd2.Cells[0,i]:='';
   strngrd3.Cells[0,i]:='';
  end;
end;

// ������: "A*b="
procedure TForm1.btn2Click(Sender: TObject);
var A:Matr; // ���������� ���������� �������
    b,y:Vct; //  ���������� ���������� ��������
    i,j:Integer;
begin
   try

    // ���������� ������� � ���������� �� ������� strngrd1
    for i:=1 to n do for j:=1 to n do
      A[j,i]:=StrToFloat(strngrd1.Cells[i,j]);

    // ���������� ������� b ���������� �� ������� strngrd2
    for i:=1 to n do b[i]:=StrToFloat(strngrd2.Cells[0,i]);
   except ShowMessage('�� ����� ������� �������� ������� ��� �������');
           Exit;
   end;

   //��������� ������� A �� ������ b
   for i:=1 to n do
   begin
     y[i]:=0;
     for j:=1 to n do y[i]:=y[i]+A[i,j]*b[j];
     //����� ���������� � ������� strngrd3
     strngrd3.Cells[0,i]:=FloatToStrF(y[i],ffFixed,6,2);
   end;
end;

// ������� ������� �� �����
procedure TForm1.RadioGroup1Click(Sender: TObject);
var f:TextFile;
    i,j: Byte;
    x:Integer;
begin
  n:=RadioGroup1.ItemIndex+3; //����������� �������
  strngrd1.ColCount:=n+1;
  strngrd1.RowCount:=n+1;
  strngrd2.RowCount:=n+1;
  strngrd3.RowCount:=n+1;

    //��������� ���� � ����������
  strngrd1.Enabled:=True;
  strngrd2.Enabled:=True;
  // �������� �����
  for i:=1 to n do for j:=1 to n do
  begin
   strngrd1.Cells[i,j]:='';
   strngrd2.Cells[0,i]:='';
   strngrd3.Cells[0,i]:='';
  end;

  for i:=1 to n+1 do
  begin
    strngrd1.Cells[0,i]:='i='+IntToStr(i);
    strngrd1.Cells[i,0]:='j='+IntToStr(i);
  end;

  AssignFile(f,IntToStr(n)+'.txt');
  Reset(f);

  // ������� �������
  for i:=1 to n do
  begin
    for j:=1 to n do
    begin
      read(f,x);
      strngrd1.Cells[j,i]:=IntToStr(x);
    end;
  end;

  // ������� ������
  for j:=1 to n do
  begin
    read(f,x);
    strngrd2.Cells[0,j]:=IntToStr(x);
  end;
  
  CloseFile(f);
end;

procedure TForm1.btnFilleClick(Sender: TObject);
var i,j:Byte;
begin
  //��������� ���� � ����������
  strngrd1.Enabled:=False;
  strngrd2.Enabled:=False;
  // �������� �����
  for i:=1 to n do for j:=1 to n do
  begin
   strngrd1.Cells[i,j]:='';
   strngrd2.Cells[0,i]:='';
   strngrd3.Cells[0,i]:='';
  end;
end;

procedure TForm1.btnKeyboardClick(Sender: TObject);
var i,j:Byte;
begin
  //��������� ���� � ����������
  strngrd1.Enabled:=True;
  strngrd2.Enabled:=True;
  // �������� �����
  for i:=1 to n do for j:=1 to n do
  begin
   strngrd1.Cells[i,j]:='';
   strngrd2.Cells[0,i]:='';
   strngrd3.Cells[0,i]:='';
  end;
end;

end.
