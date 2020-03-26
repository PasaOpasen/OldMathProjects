unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    x1: TEdit;
    RadioGroup1: TRadioGroup;
    Vis: TCheckBox;
    Per: TCheckBox;
    Bis: TCheckBox;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    x2: TEdit;
    x3: TEdit;
    Label5: TLabel;
    y1: TEdit;
    Label6: TLabel;
    Label7: TLabel;
    y2: TEdit;
    y3: TEdit;
    Memo1: TMemo;
    Button1: TButton;
    procedure Memo1Change(Sender: TObject);
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

procedure TForm1.Memo1Change(Sender: TObject);
begin
  //Memo1.Clear;
  Per.Checked:=True;
end;

procedure TForm1.Button1Click(Sender: TObject);
Var s1,s2,s3:string[5]; Flag:Boolean; v1,v2,v3,b1,b2,b3,a,b,c,xx1,xx2,xx3,yy1,yy2,yy3:real;
begin
  s1:='';s2:='';s3:='';
  Memo1.Clear;

  try xx1:=StrToFloat(x1.Text)
    except ShowMessage('������ ����� x1');
  end;
  try xx2:=StrToFloat(x2.Text)
    except ShowMessage('������ ����� x3');
  end;
  try xx3:=StrToFloat(x3.Text)
    except ShowMessage('������ ����� x3');
  end;
  try yy1:=StrToFloat(y1.Text)
    except ShowMessage('������ ����� y1');
  end;
  try yy2:=StrToFloat(x3.Text)
    except ShowMessage('������ ����� y2');
  end;
  try yy3:=StrToFloat(y3.Text)
    except ShowMessage('������ ����� y3');
  end;


  a:=sqrt(sqr(xx1-xx2)+sqr(yy1-yy2));
  b:=sqrt(sqr(xx2-xx3)+sqr(yy2-yy3));
  c:=sqrt(sqr(xx3-xx1)+sqr(yy3-yy1));

  Memo1.Lines.Add('  ����� ������ ');Memo1.Lines.Add(FloatToStr(a)); Memo1.Lines.Add(FloatToStr(b));Memo1.Lines.Add(FloatToStr(c));

  if ((a>=(b+c)) or (b>=(a+c)) or (c>=(b+a))) then {ShowMessage}Memo1.Lines.Add('������:�� ����������� ����������� ������������')
  else
    begin
      if Vis.Checked then
        begin
          v1:=abs((yy2-yy3)*xx1+(xx3-xx2)*yy1+(xx2*yy3-yy2*xx3))/sqrt(sqr(yy2-yy3)+sqr(xx3-xx2));
          v2:=abs((yy1-yy3)*xx2+(xx3-xx1)*yy2+(xx1*yy3-yy1*xx3))/sqrt(sqr(yy1-yy3)+sqr(xx3-xx1));
          v3:=abs((yy2-yy1)*xx3+(xx1-xx2)*yy3+(xx2*yy1-yy2*xx1))/sqrt(sqr(yy2-yy1)+sqr(xx1-xx2));
          s1:=FloatToStr(v1);
          s2:=FloatToStr(v2);
          s3:=FloatToStr(v3);
          Memo1.Lines.Add('  ����� ����� '+ s1+'  '+s2 +'  '+s3 )
          end;
      if Per.Checked then
        begin
          s1:=FloatToStr(a+b+c);
          Memo1.Lines.Add('  ����� ��������� '+s1)
        end;
      if Bis.Checked then
        begin
          b1:=sqrt(a*b*(a+b+c)*(a+b-c))/a+b;
          b2:=sqrt(c*b*(a+b+c)*(c+b-a))/c+b;
          b3:=sqrt(a*c*(a+b+c)*(a+c-b))/a+c;
          s1:=FloatToStr(b1);
          s2:=FloatToStr(b2);
          s3:=FloatToStr(b3);
          Memo1.Lines.Add('  ����� ���������� '+ s1+'  '+ s2+'  '+ s3)
        end;
    end;
end;

end.
