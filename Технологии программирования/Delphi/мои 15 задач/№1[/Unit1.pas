unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, Menus, ExtCtrls;

type
  TForm1 = class(TForm)
    StringGrid1: TStringGrid;
    StringGrid2: TStringGrid;
    StringGrid3: TStringGrid;
    Button1: TButton;
    Label1: TLabel;
    Edit1: TEdit;
    Button2: TButton;
    Label2: TLabel;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    D1: TMenuItem;
    RadioGroup1: TRadioGroup;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioGroup2: TRadioGroup;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    RadioButton5: TRadioButton;
    procedure StringGrid1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure D1Click(Sender: TObject);
    procedure N4Click(Sender: TObject);
    procedure N3Click(Sender: TObject);
    procedure N2Click(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure RadioGroup1Click(Sender: TObject);
    procedure RadioButton3Click(Sender: TObject);
    
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  // ���������� �����
type
  Matr = array [1..10,1..10] of real;
  Vct = array[1..10] of real;

var
  Form1: TForm1;
  //���������� ��������
  A: Matr;
  b,y:Vct;
  n,i,j: integer;
  fz:textfile;

implementation

{$R *.dfm}

procedure TForm1.StringGrid1Click(Sender: TObject);
begin

end;
 //������� ��������� ��������
procedure TForm1.FormCreate(Sender: TObject);
begin
  n:=3;

  Edit1.Text:=FloatToStr(n);
  StringGrid1.ColCount:=n+1;
  StringGrid1.RowCount:=n+1;
  StringGrid2.RowCount:=n+1;
  StringGrid3.RowCount:=n+1;
  StringGrid1.Cells[0,0]:='Matrix A:';
  StringGrid2.Cells[0,0]:='Vector B:';
  StringGrid3.Cells[0,0]:='Vector Y:';

  for i:=1 to n do
  begin
    StringGrid1.Cells[0,i]:='i='+intToStr(i);
    StringGrid1.Cells[i,0]:='j='+intToStr(i);
  end;

  RadioButton2.Checked:=TRUE;
end;
//��������� ������� ������� "�������������"
procedure TForm1.Button2Click(Sender: TObject);
begin
  // Edit1:=�� �����

  n:=StrToInt(Edit1.Text);
  StringGrid1.ColCount:=n+1;
  StringGrid1.RowCount:=n+1;
  StringGrid2.RowCount:=n+1;
  StringGrid3.RowCount:=n+1;
  StringGrid1.Cells[0,0]:='Matrix A:';
  StringGrid2.Cells[0,0]:='Vector B:';
  StringGrid3.Cells[0,0]:='Vector Y:';

  for i:=1 to n do
  begin
    StringGrid1.Cells[0,i]:='i='+intToStr(i);
    StringGrid1.Cells[i,0]:='j='+intToStr(i);
  end;
end;

//��������� ������� ������� "A*b"
procedure TForm1.Button1Click(Sender: TObject);
var f:textfile;
begin
 assignFile(f,'output.txt');
 rewrite(f);
 //����������
 for i:=1 to n do for j:=1 to n do A[i,j]:=StrToFloat(StringGrid1.Cells[j,i]);
 for i:=1 to n do b[i]:=StrToFloat(StringGrid2.Cells[0,i]);
 //�����
 for i:=1 to n do
  begin
    y[i]:=0;
    for j:=1 to n do y[i]:=y[i]+A[i,j]*b[j];
    StringGrid3.Cells[0,i]:=FloatToStrf(y[i],fffixed,6,2);
    Writeln(f,StringGrid3.Cells[0,i]);
  end;
  closefile(f);
end;

  //�������� �� ����� ��
procedure TForm1.D1Click(Sender: TObject);
var a:real; n:integer;
begin
  if OpenDialog1.Execute then
  begin
    AssignFile(fz,OpenDialog1.Filename);
    Reset(fz);

    while not seekeof(fz) do
    begin
      Read(fz,n);
      Edit1.Text:=IntToStr(n);

      for i:=1 to n do for j:=1 to n do
      begin
        Read(fz,a);
        StringGrid1.Cells[j,i]:=FloatToStr(a);
      end;

      for i:=1 to n do
      begin
        Read(fz,a);
        StringGrid2.Cells[0,i]:=FloatToStr(a);
      end;
    end;

    closefile(fz);
  end;
end;

procedure TForm1.N4Click(Sender: TObject);
var a:real; n:integer;
begin
// ������ ������
  if OpenDialog1.Execute then
  begin
    AssignFile(fz,OpenDialog1.Filename);
    Reset(fz);


      Read(fz,n);
      Edit1.Text:=IntToStr(n);
     for i:=1 to n do
      begin
        Read(fz,a);
        StringGrid2.Cells[0,i]:=FloatToStr(a);
      end;


    closefile(fz);
  end;

end;

procedure TForm1.N3Click(Sender: TObject);
var a:real; n:integer;
begin
//������ �������
   if OpenDialog1.Execute then
  begin
    AssignFile(fz,OpenDialog1.Filename);
    Reset(fz);


      Read(fz,n);
      Edit1.Text:=IntToStr(n);

      for i:=1 to n do for j:=1 to n do
      begin
        Read(fz,a);
        StringGrid1.Cells[j,i]:=FloatToStr(a);
      end;
    closefile(fz);
  end;


end;

procedure TForm1.N2Click(Sender: TObject);
var a:real; n:integer;
begin
//������ ����������� �������
   if OpenDialog1.Execute then
  begin
    AssignFile(fz,OpenDialog1.Filename);
    Reset(fz);
    Read(fz,n); Edit1.Text:=IntToStr(n);

    closefile(fz);
   end;
end;

procedure TForm1.RadioButton1Click(Sender: TObject);
var a:real; n:integer;
begin
  if RadioButton1.Checked=TRUE then
  begin
  if OpenDialog1.Execute then
  begin
    AssignFile(fz,OpenDialog1.Filename);
    Reset(fz);

    while not seekeof(fz) do
    begin
      Read(fz,n);
      Edit1.Text:=IntToStr(n);

      //  ������������� �����������
      n:=StrToInt(Edit1.Text);
  StringGrid1.ColCount:=n+1;
  StringGrid1.RowCount:=n+1;
  StringGrid2.RowCount:=n+1;
  StringGrid3.RowCount:=n+1;
  StringGrid1.Cells[0,0]:='Matrix A:';
  StringGrid2.Cells[0,0]:='Vector B:';
  StringGrid3.Cells[0,0]:='Vector Y:';

  for i:=1 to n do
  begin
    StringGrid1.Cells[0,i]:='i='+intToStr(i);
    StringGrid1.Cells[i,0]:='j='+intToStr(i);
  end;

      for i:=1 to n do for j:=1 to n do
      begin
        Read(fz,a);
        StringGrid1.Cells[j,i]:=FloatToStr(a);
      end;

      for i:=1 to n do
      begin
        Read(fz,a);
        StringGrid2.Cells[0,i]:=FloatToStr(a);
      end;
    end;

    closefile(fz);
  end;
  end;
end;

procedure TForm1.RadioGroup1Click(Sender: TObject);
begin
 //close;
end;

procedure TForm1.RadioButton3Click(Sender: TObject);
var a:real; n:integer;
begin
  if RadioButton1.Checked=TRUE then
  begin
    Assign(fz,'3.txt');
    Reset(fz);

    while not seekeof(fz) do
    begin
      n:=3;
      Edit1.Text:=IntToStr(n);

      //  ������������� �����������
  n:=StrToInt(Edit1.Text);
  StringGrid1.ColCount:=n+1;
  StringGrid1.RowCount:=n+1;
  StringGrid2.RowCount:=n+1;
  StringGrid3.RowCount:=n+1;
  StringGrid1.Cells[0,0]:='Matrix A:';
  StringGrid2.Cells[0,0]:='Vector B:';
  StringGrid3.Cells[0,0]:='Vector Y:';

  for i:=1 to n do
  begin
    StringGrid1.Cells[0,i]:='i='+intToStr(i);
    StringGrid1.Cells[i,0]:='j='+intToStr(i);
  end;

      for i:=1 to n do for j:=1 to n do
      begin
        Read(fz,a);
        StringGrid1.Cells[j,i]:=FloatToStr(a);
      end;

      for i:=1 to n do
      begin
        Read(fz,a);
        StringGrid2.Cells[0,i]:=FloatToStr(a);
      end;
    end;

    closefile(fz);
  end;
end;

end.


