unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Label1: TLabel;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
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
begin
  Form1.ClientHeight:=500;
  Form1.ClientWidth:=500;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
Form1.ClientHeight:=400;
  Form1.ClientWidth:=400;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
Form1.ClientHeight:=300;
  Form1.ClientWidth:=300;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  Form1.Height:=100;
  Form1.Top:=100;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
Form1.Height:=400;
  Form1.Top:=400;
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
Form1.Height:=600;
  Form1.Top:=600;
end;

end.
