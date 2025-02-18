unit ship_;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    procedure Timer1Timer(Sender: TObject);
    procedure FormPaint(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;


implementation

{$R *.DFM}

var

    x,y: integer; // ���������� ������� (������� �����)

// ����������� �� ����������� ����� ��������
// ��� ������� ���
procedure Parohod(x,y: integer; mode: boolean);
     // x,y - ���������� ������� ����� ���������
     // mode: True - ����������, False - �������
const
  { ������� ����� ��������� ��������� � ����� �����,
    ��� ������� ���������� ������ ���������. }
  dx = 9; // ��� ����� �� X
  dy = 7; // ��� ����� �� Y
var
  // ������ � ���������� ����� ��������
  // ��� ������ ������ Polygon
  p1: array[1..7]of TPoint; // ���������� ����� �������
  p2: array[1..8]of TPoint; // ���������� ����� ����������

  pc,bc: TColor; // ������� ���� ��������� � �����

begin
  if not mode then
  begin
    // �������
    Form1.Canvas.Brush.Color := clNavy;
    Form1.Canvas.Pen.Color := clNavy;
    Form1.Canvas.Rectangle(x,y+1,x+17*dx,y-10*dy);
    Form1.Canvas.Brush.Color := clNavy;
    // ����
    if y-10*dy < 80 then
    begin
        // ����� ����� �� ���� ����
        Form1.Canvas.Pen.Color := clSkyBlue;
        Form1.Canvas.Brush.Color := clSkyBlue;
        Form1.Canvas.Rectangle(x,y-10*dy,x+17*dx,80);
    end;
    exit;
  end;

  // ������
  with Form1.Canvas do
  begin
    pc :=Pen.Color;    // �������� ������� ���� ���������
    bc := Brush.Color; // � �����

    Pen.Color:=clBlack;    // ��������� ������ ����
    Brush.Color := clWhite;
    // ������ ...
    //  ������
    p1[1].X := x;      p1[1].y := y;
    p1[2].X :=  x;     p1[2].Y := y-2*dy;
    p1[3].X :=x+10*dx; p1[3].Y := y-2*dy;
    p1[4].X :=x+11*dx; p1[4].Y := y-3*dy;
    p1[5].X :=x+17*dx; p1[5].Y :=y-3*dy;
    p1[6].X :=x+14*dx; p1[6].Y :=y;
    p1[7].X :=x;       p1[7].Y :=y;
    Polygon(p1);
    // ����������
    p2[1].X := x+3*dx;  p2[1].Y := y-2*dy;
    p2[2].X := x+4*dx;  p2[2].Y := y-3*dy;
    p2[3].X := x+4*dx;  p2[3].Y := y-4*dy;
    p2[4].X := x+13*dx; p2[4].Y := y-4*dy;
    p2[5].X := x+13*dx; p2[5].Y := y-3*dy;
    p2[6].X := x+11*dx; p2[6].Y := y-3*dy;
    p2[7].X := x+10*dx;  p2[7].Y := y-2*dy;
    p2[8].X := x+3*dx;  p2[8].Y := y-2*dy;
    Polygon(p2);
    MoveTo(x+5*dx,y-3*dy);
    LineTo(x+9*dx,y-3*dy);
    // ����������� ������
    Rectangle(x+8*dx,y-4*dy,x+11*dx,y-5*dy);
    // �����
    Rectangle(x+7*dx,y-4*dy,x+8*dx,y-7*dy);
    // ������������
    Ellipse(x+11*dx,y-2*dy,x+12*dx,y-1*dy);
    Ellipse(x+13*dx,y-2*dy,x+14*dx,y-1*dy);
    // �����
    MoveTo(x+10*dx,y-5*dy);
    LineTo(x+10*dx,y-10*dy);
    // ��������
    Pen.Color := clWhite;
    MoveTo(x+17*dx,y-3*dy);
    LineTo(x+10*dx,y-10*dy);
    LineTo(x,y-2*dy);
    Pen.Color:=pc; // ����������� ������ ���� ���������
  end;
end;

// ��������� ������� �������
procedure TForm1.Timer1Timer(Sender: TObject);
begin
   Parohod(x,y, False); // ������� �������
   if x < Form1.ClientWidth
      then x := x+2
      else begin // ����� ����
        x := 0;
        y := Random(50) + 100;
      end;
   Parohod(x,y,True); // ���������� � ����� �����
end;

procedure TForm1.FormPaint(Sender: TObject);
begin
    // ����
    Canvas.Brush.Color := clSkyBlue;
    Canvas.Pen.Color   := clSkyBlue;
    Canvas.Rectangle(0,0,ClientWidth,80);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
    x:=0; y:=80;           // �������� ��������� ��������
    Form1.Color:=clNavy;   // ���� ����
    Timer1.Interval := 50; // ������ ������� ������ 50 ����
end;

end.
