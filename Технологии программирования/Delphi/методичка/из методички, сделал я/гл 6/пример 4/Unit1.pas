unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, Buttons, Grids, StdCtrls;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    GroupBox1: TGroupBox;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    Edit3: TEdit;
    Edit4: TEdit;
    Button1: TButton;
    StringGrid1: TStringGrid;
    BitBtn1: TBitBtn;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    MainMenu1: TMainMenu;
    Fil: TMenuItem;
    new: TMenuItem;
    opn: TMenuItem;
    sv: TMenuItem;
    s: TMenuItem;
    srt: TMenuItem;
    svsrt: TMenuItem;
    procedure FormCreate(Sender: TObject);
    procedure newClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure opnClick(Sender: TObject);
    procedure svClick(Sender: TObject);
    procedure srtClick(Sender: TObject);
    procedure svsrtClick(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    //0procedure TForm1.FormClose(Sender: TObject;var Action:TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

Type TStudent=record
    FIO:string[40];
    otc:array[1..3] of word;
    sball:real;
   end;
var
  Form1: TForm1;
  Fz:file of TStudent;
  Ft:TextFile;
  Stud: array[1..100] of TStudent;
  nzap:integer;
  flg:Boolean;

implementation

{$R *.dfm}


procedure TForm1.FormCreate(Sender: TObject);
begin
  Button1.Hide;
  with StringGrid1 do
  begin
    Cells[0,0]:='�.�.�';Cells[1,0]:='�������.';
    Cells[2,0]:='������';Cells[3,0]:='�������.';
    Cells[4,0]:='�����.�';
  end;
  flg:=False;
end;

procedure TForm1.newClick(Sender: TObject);
var i:word;
begin
  OpenDialog1.Title:='������� ����� ����';
  if OpenDialog1.Execute then
  begin
    AssignFile(fz,OpenDialog1.FileName);
    Rewrite(Fz);
    Button1.Show;
    nzap:=0;
    for i:=1 to nzap do
      with StringGrid1 do
      begin
        Cells[0,i]:='';Cells[1,i]:='';
        Cells[2,i]:='';Cells[3,i]:='';
        Cells[4,i]:='';
      end;
    flg:=True;
  end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  inc(nzap);
  with Stud[nzap] do
  begin
    FIO:=Edit1.Text;
    otc[1]:=StrToInt(Edit2.text);
    otc[2]:=StrToInt(Edit3.text);
    otc[3]:=StrToInt(Edit4.text);
    sball:=(otc[1]+otc[2]+otc[3])/3;
  end;
  with StringGrid1 do
  begin
    Cells[0,nzap]:=Edit1.Text;Cells[1,nzap]:=Edit2.Text;
    Cells[2,nzap]:=Edit3.Text;Cells[3,nzap]:=Edit4.Text;
    Cells[4,nzap]:=FloatToStrF(Stud[nzap].sball,fffixed,2,1);
  end;
  write(fz,Stud[nzap]);
  Edit1.Text:=''; Edit2.Text:=''; Edit3.Text:=''; Edit4.Text:='';
end;

procedure TForm1.opnClick(Sender: TObject);
begin
  if OpenDialog1.Execute then
  begin
    AssignFile(fz,OpenDialog1.FileName);
    Reset(Fz);
    nzap:=0;
    while not eof(Fz) do
    begin
      inc(nzap);
      read(fz,stud[nzap]);
      with StringGrid1,stud[nzap] do
      begin
        Cells[0,nzap]:=fio;Cells[1,nzap]:=intToStr(otc[1]);
        Cells[2,nzap]:=intToStr(otc[2]);Cells[3,nzap]:=intToStr(otc[3]);
        Cells[4,nzap]:=FloatToStr(sball);
      end;
    end;
    Button1.Show;
  end;
end;

procedure TForm1.svClick(Sender: TObject);
begin
  if flg then
  begin
    CloseFile(fz);
    flg:=false;
  end;
  Button1.Hide;
end;

procedure TForm1.srtClick(Sender: TObject);
var i,j:word; st:Tstudent;
begin
  if nzap>0 then
  begin
    for i:=1 to nzap-1 do
      for j:=i+1 to nzap do
        if Stud[i].sball<Stud[j].sball then
        begin
          st:=Stud[i];
          Stud[i]:=Stud[j];
          Stud[j]:=st;
        end;
     for i:=1 to nzap do
       with StringGrid1,stud[i] do
       begin
         Cells[0,nzap]:=fio;Cells[1,nzap]:=intToStr(otc[1]);
         Cells[2,nzap]:=intToStr(otc[2]);Cells[3,nzap]:=intToStr(otc[3]);
         Cells[4,nzap]:=FloatToStr(sball);
       end;
  end;
end;

procedure TForm1.svsrtClick(Sender: TObject);
var i:word;
begin
  if SaveDialog1.Execute then
  begin
    AssignFile(ft,SaveDialog1.FileName);
    rewrite(ft);
    for i:=1 to nzap do
     with stud[i] do write(ft,i:4,'.',fio,sball:8:2);
    closeFile(ft);
  end;
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
begin
  if flg then closeFile(fz);
end;


////////////

{procedure TForm1.FormClose(Sender: TObject;var Action:TCloseAction);
begin
  if flg then closeFile(fz);
end;  }

end.
