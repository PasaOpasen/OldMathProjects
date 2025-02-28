unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, ExtCtrls, Menus;

type
  TForm1 = class(TForm)
    StringGrid1: TStringGrid;
    Button1: TButton;
    StringGrid2: TStringGrid;
    Edit1: TEdit;
    Button2: TButton;
    RadioGroup1: TRadioGroup;
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure N2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
type Matr=array [1..10,1..10] of real;
var
  Form1: TForm1;
   n,i,j:integer;
   A:matr;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
    k:integer;
    x,b:real;
begin
  for i:=1 to n do
    for j:=1 to n do
      A[i,j]:=StrToFloat(StringGrid1.Cells[j,i]);

  if radioGroup1.ItemIndex=0 then
    begin
      for i:=1 to n do
        begin
          k:=i;
          x:=a[i,1];
          for j:=i+1 to n do
            if (a[j,1]<x) then
              begin
                k:=j;
                x:=a[j,1];
              end;
          for j:=1 to n do
            begin
              b:=a[k,j];
              a[k,j]:=a[i,j];
              a[i,j]:=b;
            end;
   end;


    end;
  if radioGroup1.ItemIndex=1 then
    begin
      for i:=1 to n do
        begin
          k:=i;
          x:=a[i,1];
          for j:=i+1 to n do
            if (a[j,1]>x) then
              begin
                k:=j;
                x:=a[j,1];
              end;
          for j:=1 to n do
            begin
              b:=a[k,j];
              a[k,j]:=a[i,j];
              a[i,j]:=b;
            end;
        end;
    end;
  if radioGroup1.ItemIndex=2 then
    begin
      for i:=1 to n do
        begin
          k:=i;
          x:=a[1,i];
          for j:=i+1 to n do
            if (a[1,j]<x) then
              begin
                k:=j;
                x:=a[1,j];
              end;
          for j:=1 to n do
            begin
              b:=a[j,k];
              a[j,k]:=a[j,i];
              a[j,i]:=b;
            end;
        end;
    end;
  if radioGroup1.ItemIndex=3 then
    begin
      for i:=1 to n do
        begin
          k:=i;
          x:=a[1,i];
          for j:=i+1 to n do
            if (a[1,j]>x) then
              begin
                k:=j;
                x:=a[1,j];
              end;
          for j:=1 to n do
            begin
              b:=a[j,k];
              a[j,k]:=a[j,i];
              a[j,i]:=b;
            end;
        end;
    end;
  for i:=1 to n do
    for j:=1 to n do
      StringGrid2.Cells[j,i]:=FloatToStr(A[i,j])
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  n:=3;
  Edit1.Text:='3';
  StringGrid1.RowCount:=n+1;
  StringGrid1.ColCount:=n+1;
  StringGrid2.RowCount:=n+1;
  StringGrid2.ColCount:=n+1;
  for i:=1 to 10 do
   begin
    StringGrid1.Cells[0,i]:=inttostr(i);
    StringGrid1.Cells[i,0]:=inttostr(i);
    StringGrid2.Cells[0,i]:=inttostr(i);
    StringGrid2.Cells[i,0]:=inttostr(i);
   end;

end;

procedure TForm1.Button2Click(Sender: TObject);
begin
 n:=StrToInt(Edit1.Text);
 StringGrid1.RowCount:=n+1;
 StringGrid2.RowCount:=n+1;
 StringGrid1.ColCount:=n+1;
 StringGrid2.ColCount:=n+1;


end;

procedure TForm1.N1Click(Sender: TObject);
var txt:TextFile;
    i,j:integer;
    scan:real;
begin
 if OpenDialog1.Execute then
  begin
    assignFile(txt,OpenDialog1.FileName);
    reset(txt);
    read(txt,n);
    StringGrid1.ColCount:=n+1;
    StringGrid1.RowCount:=n+1;
    StringGrid2.ColCount:=n+1;
    StringGrid2.RowCount:=n+1;
    for i:=1 to n do
     begin
      for j:=1 to n do
        begin
          read(txt,scan);
          StringGrid1.Cells[j,i]:=FLoatToStr(scan);
        end;
     end;
  end;
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
        for j:=1 to n do write(txt,StringGrid1.Cells[j,i]:6);
        writeln(txt);
      end;
    writeln(txt);
    for i:=1 to n do
      begin
        for j:=1 to n do write(txt,StringGrid2.Cells[j,i]:6);
        writeln(txt);
      end;
    CloseFile(txt);
  end;
end;

end.
