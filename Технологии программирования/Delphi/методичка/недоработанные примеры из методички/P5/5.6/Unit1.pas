unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    ComboBox1: TComboBox;
    Edit1: TEdit;
    Memo1: TMemo;
    Button1: TButton;
    RadioGroup1: TRadioGroup;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    procedure ComboBox1KeyPress(Sender: TObject; var Key: Char);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
function Transliterate(s: string): string;
var
  Form1: TForm1;

implementation

{$R *.dfm}
procedure TForm1.ComboBox1KeyPress(Sender: TObject; var Key: Char);
begin
 if key=#13 then
  begin
   ComboBox1.Items.Add(Edit1.text);
   Edit1.Text:='';
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
 Memo1.Clear;
 RadioButton1.Checked:=true;
end;

procedure TForm1.Button1Click(Sender: TObject);
var arr:array [1..100] of string;
    st,NewSt:string;
    nst,n,i,max,k:integer;
begin
  nst:=ComboBox1.ItemIndex;
  st:=ComboBox1.Items[nst]+' ';
  n:=length(st);

  if RadioButton1.Checked then
   begin
    k:=1;
    for i:=1 to n do
     begin
      if st[i]<>' ' then
       begin
        NewSt:=NewSt+st[i];
       end
      else
       begin
        arr[k]:=NewSt;
        inc(k);
        NewSt:='';
       end;
     end;
     dec(k);
     max:=length(arr[1]);
     for i:=2 to k do
      if max<length(arr[i]) then max:=length(arr[i]);
     for i:=1 to k do
      begin
       //Memo1.Lines.add(inttostr(length(arr[i])));
       while (length(arr[i])<max) do arr[i]:=' '+arr[i];
       Memo1.Lines.Add(arr[i]);
       //Memo1.Lines.add(inttostr(length(arr[i])));
      end;
   end;
  if RadioButton2.checked then
   begin
    Memo1.Lines.Add(Transliterate(st));
   end;
end;

function Transliterate(s: string): string;
var
 i: integer;
 t: string;
begin
 for i:=1 to Length(s) do
  begin
   case s[i] of
        '�': t:=t+'a';
        '�': t:=t+'b';
        '�': t:=t+'v';
        '�': t:=t+'g';
        '�': t:=t+'d';
        '�': t:=t+'e';
        '�': t:=t+'ye';
        '�': t:=t+'zh';
        '�': t:=t+'z';
        '�': t:=t+'i';
        '�': t:=t+'y';
        '�': t:=t+'k';
        '�': t:=t+'l';
        '�': t:=t+'m';
        '�': t:=t+'n';
        '�': t:=t+'o';
        '�': t:=t+'p';
        '�': t:=t+'r';
        '�': t:=t+'s';
        '�': t:=t+'t';
        '�': t:=t+'u';
        '�': t:=t+'f';
        '�': t:=t+'ch';
        '�': t:=t+'z';
        '�': t:=t+'ch';
        '�': t:=t+'sh';
        '�': t:=t+'ch';
        '�': t:=t+'''';
        '�': t:=t+'y';
        '�': t:=t+'''';
        '�': t:=t+'e';
        '�': t:=t+'yu';
        '�': t:=t+'ya';
        '�': T:=T+'A';
        '�': T:=T+'B';
        '�': T:=T+'V';
        '�': T:=T+'G';
        '�': T:=T+'D';
        '�': T:=T+'E';
        '�': T:=T+'Ye';
        '�': T:=T+'Zh';
        '�': T:=T+'Z';
        '�': T:=T+'I';
        '�': T:=T+'Y';
        '�': T:=T+'K';
        '�': T:=T+'L';
        '�': T:=T+'M';
        '�': T:=T+'N';
        '�': T:=T+'O';
        '�': T:=T+'P';
        '�': T:=T+'R';
        '�': T:=T+'S';
        '�': T:=T+'T';
        '�': T:=T+'U';
        '�': T:=T+'F';
        '�': T:=T+'Ch';
        '�': T:=T+'Z';
        '�': T:=T+'Ch';
        '�': T:=T+'Sh';
        '�': T:=T+'Ch';
        '�': T:=T+'''';
        '�': T:=T+'Y';
        '�': T:=T+'''';
        '�': T:=T+'E';
        '�': T:=T+'Yu';
        '�': T:=T+'Ya';
      else t:=t+s[i];
   end;
  end;
 Result:=t;
end;

end.
