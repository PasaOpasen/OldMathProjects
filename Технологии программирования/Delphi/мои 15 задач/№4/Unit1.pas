unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, TeeProcs, TeEngine, Chart, StdCtrls, Series;

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
    Button1: TButton;
    Label7: TLabel;
    Edit7: TEdit;
    Button2: TButton;
    Button3: TButton;
    Series1: TLineSeries;
    Series2: TLineSeries;
    Series3: TLineSeries;
    Chart1: TChart;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  Xmin, Xmax, Ymin, Ymax, Hx, Hy,h: Extended;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
  {��������� ��������� ���������� ������������ ����}
  Xmin :=  0;  Xmax := 2 * pi;
  Ymin := -1; Ymax := 1;
  Hx := pi/2; Hy := 0.5;
  h := 0.01; //��������� ���� ������� �������
  {����� ������ � ���� ������������ ����������}
  Edit1.Text := FloatToStr(Xmin);
  Edit2.Text := FloatToStr(Xmax);
  Edit3.Text := FloatToStr(Ymin);
  Edit4.Text := FloatToStr(Ymax);
  Edit5.Text := FloatToStr(Hx);
  Edit6.Text := FloatToStr(Hy);
  Edit7.Text := FloatToStr(h);
  Chart1.BottomAxis.Automatic := False; //���������� ��������������� ����������� ���������� ������ ���
  Chart1.BottomAxis.Minimum := Xmin; //��������� ����� ������� ������ ���
  Chart1.BottomAxis.Maximum := Xmax; //��������� ������ ������� ������ ���
  Chart1.LeftAxis.Automatic := False; //���������� ��������������� ����������� ���������� ����� ���
  Chart1.LeftAxis.Minimum := Ymin; //��������� ������ ������� ����� ���
  Chart1.LeftAxis.Maximum := Ymax; //��������� ������� ������� ����� ���
  Chart1.BottomAxis.Increment := Hx; //��������� ���� �������� �� ������ ���
  Chart1.LeftAxis.Increment := Hy; //��������� ���� �������� �� ����� ���
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  {������ ������ �� ���� ������������ ����������}
  Xmin := StrToFloat(Edit1.Text); Xmax := StrToFloat(Edit2.Text);
  Ymin := StrToFloat(Edit3.Text); Ymax := StrToFloat(Edit4.Text);
  Hx := StrToFloat(Edit5.Text); Hy := StrToFloat(Edit6.Text);
  Chart1.BottomAxis.Minimum := Xmin; //��������� ����� ������� ������ ���
  Chart1.BottomAxis.Maximum := Xmax + 0.01; //��������� ������ ������� ������ ���
  Chart1.LeftAxis.Minimum := Ymin; //��������� ������ ������� ����� ���
  Chart1.LeftAxis.Maximum := Ymax; //��������� ������� ������� ����� ���
  Chart1.BottomAxis.Increment := Hx; //��������� ���� �������� �� ������ ���
  Chart1.LeftAxis.Increment := Hy; //��������� ���� �������� �� ����� ���
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  x, y1, y2, y3: Extended;
begin
  Series1.Clear;
  Series2.Clear;
  Series3.Clear;
  Xmin := StrToFloat(Edit1.Text);
  Xmax := StrToFloat(Edit2.Text);
  h := StrToFloat(Edit7.Text); //��� ������� ������� ��� �������
  x := Xmin; //��������� �������� �� ��� X
  repeat
    y1 := sin(x); //������ �������
    Series1.AddXY(x, y1, '', clTeeColor); //����� ����� �� ������
    y2 := cos(x); //������ �������
    Series2.AddXY(x, y2, '', clTeeColor); //����� ����� �� ������
    x := x + h; //���������� �������� X �� �������� ����
    y3 := Sin(x) * Cos(x); //������ �������
    Series3.AddXY(x, y3, '', clTeeColor); //����� ����� �� ������
    x := x + h; //���������� �������� � �� �������� ����
  Until (x > Xmax);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  Close;
end;

end.
