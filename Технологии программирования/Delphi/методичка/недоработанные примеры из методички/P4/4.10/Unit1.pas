unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, StdCtrls, Grids;

type
  TForm1 = class(TForm)
    StringGrid1: TStringGrid;
    StringGrid2: TStringGrid;
    Edit1: TEdit;
    Edit2: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Button1: TButton;
    Button2: TButton;
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    procedure N1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure N2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
type matr=array [1..100,1..100] of real;
var
  Form1: TForm1;
  a,b:matr;
  n,m,i,j:integer;

implementation

{$R *.dfm}

procedure TForm1.N1Click(Sender: TObject);
var txt:TextFile;
    scan:real;
begin
  if OPenDialog1.Execute then
    begin
      assignFile(txt,openDialog1.FileName);
      reset(txt);
      read(txt,n);
      read(txt,m);
      StringGrid1.RowCount:=n+1;
      StringGrid1.ColCount:=m+1;
      StringGrid2.RowCount:=n+1;
      StringGrid2.ColCount:=m+1;
      for i:=1 to n do
        for j:=1 to m do
          begin
            read(txt,scan);
            StringGrid1.Cells[j,i]:=FloatToSTr(scan);
          end;




    end;

end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  n:=3;
  m:=3;
  EDit1.Text:='3';
  Edit2.Text:='3';
  StringGrid1.RowCount:=n+1;
  StringGrid1.ColCount:=m+1;
  StringGrid2.RowCount:=n+1;
  StringGrid2.ColCount:=m+1;
  for i:=1 to 10 do
    begin
      StringGrid1.Cells[0,i]:=intToStr(i);
      StringGrid1.Cells[i,0]:=intToStr(i);
      StringGrid2.Cells[0,i]:=intToStr(i);
      StringGrid2.Cells[i,0]:=intToStr(i);
    end;
end;

procedure TForm1.Button2Click(Sender: TObject);
var max:real;
    NUmMaxI,numMaxJ:integer;
begin
  for i:=1 to n do
    for j:=1 to m do
      StringGrid2.Cells[j,i]:='';

  for i:=1 to n do
    for j:=1 to m do
      a[i,j]:=strToFloat(stringGrid1.Cells[j,i]);

  max:=a[1,1];
  numMaxI:=1;
  numMaxJ:=1;
  for i:=1 to n do
    for j:=1 to m do
      if abs(a[i,j])>max then
        begin
          max:=abs(a[i,j]);
          numMaxI:=i;
          numMaxJ:=j;
        end;

  StringGrid2.RowCount:=n;
  StringGrid2.ColCount:=m;

  for i:=1 to n-1 do
    begin
      if i>=numMaxI then
        for j:=1 to m do
          a[i,j]:=a[i+1,j];
      for j:=1 to m-1 do
        if j>=numMaxJ then
          a[i,j]:=a[i,j+1];
    end;


  for i:=1 to n do
    for j:=1 to m do
        STringGrid2.Cells[j,i]:=FloatToSTr(a[i,j]);
end;

procedure TForm1.N2Click(Sender: TObject);
var txt:textFile;
    i,j:integer;
begin
 if saveDialog1.Execute then
  begin
    assignFile(txt,SaveDialog1.FileName);
    rewrite(txt);
    for i:=1 to n do
      begin
        for j:=1 to m do write(txt,StringGrid1.Cells[j,i]:6);
        writeln(txt);
      end;
    writeln(txt);
    for i:=1 to n do
      begin
        for j:=1 to m do write(txt,StringGrid2.Cells[j,i]:6);
        writeln(txt);
      end;
    CloseFile(txt);
  end;
end;

end.
