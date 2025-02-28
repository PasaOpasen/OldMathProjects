unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls;

type
  TForm1 = class(TForm)
    PaintBox1: TPaintBox;
    Timer1: TTimer;
    procedure Timer1Timer(Sender: TObject);
    procedure NewObject(x,y:integer);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

Procedure TForm1.NewObject(x,y:integer);
begin
 with PaintBox1, Canvas do
  begin
    Brush.Color:=clYellow;
    Ellipse(x,y,x+40,y+30);

  end;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  PaintBox1.Canvas.Brush.Style:=bsSolid;
  PaintBox1.Canvas.Brush.Color:=clWhite;
  PaintBox1.Canvas.Rectangle(0,0,PaintBox1.Width,PaintBox1.Height);

  randomize;
  NewObject(40+Random(PaintBox1.Width-80),30+Random(PaintBox1.Height-60));


end;

end.
