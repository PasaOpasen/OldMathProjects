unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    ComboBox1: TComboBox;
    RadioGroup1: TRadioGroup;
    Label1: TLabel;
    Label2: TLabel;
    Button1: TButton;
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure ComboBox1Click(Sender: TObject);
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
var st:string;
    i:integer;
begin
  if key=#13 then
    begin
      st:=Edit1.Text+' ';

      while (st[1]=' ') do delete(st,1,1);

      i:=1;
      while (i<=length(st)) do
        begin
          if (st[i-1]=' ') and (st[i]=' ') then delete(st,i,1)
          else inc(i);
        end;

      ComboBox1.Items.Add(st);
      Edit1.Text:='';
    end;
end;

procedure swap(var a,b:char);
var temp:char;
begin
 temp:=a;
 a:=b;
 b:=temp;
end;

Procedure zamena(var str:string);
var s:string;
    i:integer;
begin
  s:='';
  for i:=1 to length(str) do
    case str[i] of
      ' ':s:=s+' ';
      '�':s:=s+'a';
      '�':s:=s+'b';
      '�':s:=s+'v';
      '�':s:=s+'g';
      '�':s:=s+'d';
      '�':s:=s+'e';
      '�':s:=s+'e';
      '�':s:=s+'zh';
      '�':s:=s+'z';
      '�':s:=s+'i';
      '�':s:=s+'i';
      '�':s:=s+'k';
      '�':s:=s+'l';
      '�':s:=s+'m';
      '�':s:=s+'n';
      '�':s:=s+'o';
      '�':s:=s+'p';
      '�':s:=s+'r';
      '�':s:=s+'s';
      '�':s:=s+'t';
      '�':s:=s+'u';
      '�':s:=s+'f';
      '�':s:=s+'x';
      '�':s:=s+'c';
      '�':s:=s+'ch';
      '�':s:=s+'sh';
      '�':s:=s+'sha';
      '�':s:=s+'';
      '�':s:=s+'';
      '�':s:=s+'';
      '�':s:=s+'e';
      '�':s:=s+'yu';
      '�':s:=s+'ya';
      '�':s:=s+'A';
      '�':s:=s+'B';
      '�':s:=s+'V';
      '�':s:=s+'G';
      '�':s:=s+'D';
      '�':s:=s+'R';
      '�':s:=s+'R';
      '�':s:=s+'Zh';
      '�':s:=s+'Z';
      '�':s:=s+'I';
      '�':s:=s+'I';
      '�':s:=s+'K';
      '�':s:=s+'L';
      '�':s:=s+'M';
      '�':s:=s+'N';
      '�':s:=s+'O';
      '�':s:=s+'P';
      '�':s:=s+'R';
      '�':s:=s+'S';
      '�':s:=s+'T';
      '�':s:=s+'U';
      '�':s:=s+'F';
      '�':s:=s+'X';
      '�':s:=s+'C';
      '�':s:=s+'Ch';
      '�':s:=s+'Sh';
      '�':s:=s+'Sha';
      '�':s:=s+'E';
      '�':s:=s+'Yu';
      '�':s:=s+'Ya';
    end;
    str:=s;
end;


procedure TForm1.ComboBox1Click(Sender: TObject);
var st:string;
    n,i,nst,ind,numChar1,numChar2:integer;
    c:char;
begin
  n:=0;
  ind:=0;
  nst:=ComboBox1.ItemIndex ;
  st:=comboBox1.Items[nst];

  if (RadioGroup1.ItemIndex=0) then
    begin
      numChar1:=1;
      for i:=1 to length(st) do
       begin
        if(st[i-1]=' ') then numChar1:=i;
        if(st[i+1]=' ') then
         begin
          numChar2:=i;
          swap(st[numChar1],st[numChar2]);
         end;
       end;
      label2.Caption:=st;
    end;

  if (radioGroup1.ItemIndex=1) then
    begin
      zamena(st);
      label2.Caption:=st;
    end;


end;

procedure TForm1.Button1Click(Sender: TObject);
var txt:textFile;
    st:string;
begin
assignFile(txt,'in.txt');
reset(txt);
while not eof(txt) do
  begin
    readln(txt,st);
    comboBox1.Items.Add(st);
  end;
closeFile(txt);
end;


end.
