unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
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

procedure TForm1.Button1Click(Sender: TObject);
{var k:Integer;
    Sort1,Sort2:TStringList;
    s:string;
begin
  Sort1:= TStringList.Create;
  Sort2:= TStringList.Create;

  Sort1.Sorted:= true;
  for k:= 0 to 255 do
    begin
      S:= IntToStr(k);
      if k<10 then s:='0'+s;
      if k<100 then s:='0'+s;
      Sort1.Add(Char(k)+#9+s);
      Sort2.Add(s+#9+Char(k));
    end;
  Sort1.Sorted:= false;

  for k:= 0 to Sort1.Count-1 do
    Sort1[k]:= Sort1[k]+#9+Sort2[k];
  Memo1.Lines.Assign(Sort1);

  Sort1.Free;
  Sort2.Free;
end;}

var
  k: byte;
  List1, List2: TStringList;
  S: string;
begin
  List1:= TStringList.Create;
  List1.Sorted:= true;
  List2:= TStringList.Create;
  for k:= 32 to 255 do
  begin
    S:= IntToStr(k);
    If k<100 then
      S:= '0' + S;
    List1.Add(Char(k) + #9 + S);
    List2.Add(S + #9 + Char(k));
  end;
  List1.Sorted:= false;
  for k:= 0 to List1.Count-1 do
    List1[k]:= '                '+List1[k] + #9 + List2[k];
  Memo1.Lines.Assign(List1);
  List1.Free;
  List2.Free;
end;

end.
