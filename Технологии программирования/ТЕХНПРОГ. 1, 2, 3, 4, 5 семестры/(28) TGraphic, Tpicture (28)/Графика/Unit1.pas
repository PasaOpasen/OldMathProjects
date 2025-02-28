unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, TeEngine, Series, ExtCtrls, TeeProcs, Chart, StdCtrls;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    Label8: TLabel;
    Edit7: TEdit;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Chart1: TChart;
    Series1: TLineSeries;
    Series2: TLineSeries;
    Series3: TLineSeries;
    procedure Button3Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  Xmin,Xmax,Ymin,Ymax,Hx,Hy,h:extended;

implementation

{$R *.dfm}
procedure TForm1.FormCreate(Sender: TObject);
begin
  Xmin:=0;
  Xmax:=2*pi;
  Ymin:=-1;
  Ymax:=1;
  Hx:=pi/2;
  Hy:=0.5;
  h:=0.01;
  Edit1.Text:=floatToStr(Xmin);
  Edit2.Text:=floatToStr(Xmax);
  Edit3.Text:=floatToStr(Ymin);
  Edit4.Text:=floatToStr(Ymax);
  Edit5.Text:=floatToStr(Hx);
  Edit6.Text:=floatToStr(Hy);
  Edit7.Text:=floatToStr(h);

  Chart1.BottomAxis.Automatic:=False;
  Chart1.BottomAxis.Minimum:=Xmin;
  Chart1.BottomAxis.Maximum:=Xmax;
  Chart1.LeftAxis.Automatic:=False;
  Chart1.LeftAxis.Minimum:=Ymin;
  Chart1.LeftAxis.Maximum:=Ymax;
  Chart1.BottomAxis.Increment:=Hx;
  Chart1.LeftAxis.Increment:=Hy;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
{������ ������ �� ���� ������������ ����������}
  Xmin:=StrToFloat(Edit1.Text);

  Xmax:=StrToFloat(Edit2.Text);
  Ymin:=StrToFloat(Edit3.Text);
  Hx:=StrToFloat(Edit5.Text);
  Hy:=StrToFloat(Edit6.Text);
  Chart1.bottomAxis.Minimum:=Xmin;
  Chart1.bottomAxis.Maximum:=Xmax;
  Chart1.LeftAxis.Minimum:=Ymin;
  Chart1.LeftAxis.Maximum:=Ymax;
  Chart1.bottomAxis.Increment:=Hx;
  Chart1.LeftAxis.Increment:=Hy;
end;

procedure TForm1.Button2Click(Sender: TObject);
var x,y1,y2,y3:extended;
begin
  Series1.Clear;
  Series2.Clear;
  Series3.Clear;
  Xmin:=StrToFloat(Edit1.Text);
  Xmax:=StrToFloat(Edit2.Text);
  h:=strToFloat(Edit7.Text);
  x:=Xmin;
  repeat
    y1:=sin(x);
    Series1.AddXY(x,y1,'',clTeeColor);
    y2:=cos(x);
    Series2.AddXY(x,y2,'',clTeeColor);
    y3:=sin(x)*cos(x);
    Series3.AddXY(x,y3,'',clTeeColor);
    x:=x+h;
  Until (x>Xmax);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  close;
end;

end.
