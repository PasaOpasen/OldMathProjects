unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    ComboBox1: TComboBox;
    Edit1: TEdit;
    BitBtn1: TBitBtn;
    Label4: TLabel;
    Memo1: TMemo;
    procedure ComdoBox1Click(Sender: TObject);
    procedure ComboBox1KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.ComdoBox1Click(Sender: TObject);
var st,stt,le,re:string;  n,i,nst,p,index,indexe:integer;
begin
  n:=0;
  nst:=ComboBox1.ItemIndex;//��������� ������ ��������� ������
  st:=ComboBox1.Items[nst];//��������� ��������� ������ � ����������
  Label4.Caption:=('');//������� ������ �����, ��� � �� ����� ���� ������ �� ��������
  Memo1.Lines.Add('');

  for i:=1 to Length(st) do
    if st[i]=' ' then inc(n);
  if n<=1 then
  begin
    Label3.Caption:=('��������� �� ����������: ���� ��������');//���� �������� �� ������ ������, �� ��������� �� ����������: �� �������� �������
    exit;//��������� ���������
  end;

  {��������� ����:�������� ������ ������}

  for i:=2 to Length(st) do
  if (st[i-1]=' ') and (st[i]<>' ') then
  begin
    index:=i;//�����, � �������� ���������� ���������
    break; //���� �� ���������� ����� ����� �������
  end;

  p:=0;
  indexe:=0;
  while(st[i]<>' ') do //���� �� �������� �� ��������� ������ - ������ ���������
  begin
    if (st[i]<>'e') and (st[i]<>'+') and (st[i]<>'-') then inc(p);
    if (st[i]='e') then inc(indexe);
    inc(i);
  end;

  stt:=copy(st,index,i-index);//��������� ������ ���������
  Memo1.Lines.Add(stt);

  if (p=0) or (indexe>1) then
  begin
     Label3.Caption:=('��������� �� �������� ������: ��� ���� ��� ����� ���� "e"');//���� � ��������� �� ����� ���� ��� � ��������� ������ ����� ����� 'e', �� ���������� �� ����� ������
     exit;
  end;

   i:=1;
   while (i<=Length(stt)) and (stt[i]<>'e') do inc(i); //������� ����� ����� 'e'

   le:=copy(stt,1,i-1);//����� ����� ����� 'e'
   re:=copy(stt,i+1,Length(stt)-i);//����� ����� ������ 'e'
   Memo1.Lines.Add(le);  Memo1.Lines.Add(re);

   i:=2;
   while (i<=Length(le)) do
   begin
    if (le[i]='+') or (le[i]='-') then
    begin
     Label3.Caption:=('��������� �� �������� ������: ���� �������� � ������ ��������');//���� �� ����� 'e' ���������� ���� �������� (������ ������� ��������), �� ��������� �� ����� ������
     exit;
    end;
    inc(i);
   end;
   i:=2;
   while (i<=Length(re)) do
   begin
    if (re[i]='+') or (re[i]='-') then
    begin
     Label3.Caption:=('��������� �� �������� ������: ���� �������� �� ������ ��������');//���� ����� ����� 'e' ���������� ���� �������� (������ ������� ��������), �� ��������� �� ����� ������
     exit;
    end;
    inc(i);
   end;

   if (Length(re)=1) and ((re[1]='+') or (re[1]='-')) then
   begin
     Label3.Caption:=('��������� �� �������� ������: ����� "�" ���� ���� ������');//���� ����� ����� 'e' ���� ������ ������ ��������, �� ��������� �� ����� ������
     exit;
   end;


   {��������� �������� ������}

   

   if Length(le)=0 then Label3.Caption:=('����� �������������')//���� � ��������� �� 'e' ������ �� �����, �� ���������� ����� ������������� ������
   else if(le[1]='-') then
        begin
        Label3.Caption:=('����� �������������');//���� � ��������� ������ ���� '-', �� ���������� ����� ������������� ������
        end
        else
        begin
          Label3.Caption:=('����� �������������');//���� � ��������� ������ ���� �� '-', �� ���������� ����� ������������� ������
        end;

   if Length(re)=0 then Label4.Caption:=('����� �����')//���� ����� 'e' ������ �� �����, �� ��������� ��������� ����� ������
   else if (re[1]='-') then
        begin
          Label4.Caption:=('����� �������');//���� ����� 'e' ����� '-', �� ��������� ��������� ������� ������
          exit;
        end
        else
        begin
          Label4.Caption:=('����� �����');//���� ����� 'e' ����� '+' ��� �����, �� ��������� ��������� ����� ������
          exit;
        end;

end;

procedure TForm1.ComboBox1KeyPress(Sender: TObject; var Key: Char);
begin
  if key=#13 then
  begin
    ComboBox1.Items.Add(Edit1.Text);
    Edit1.Text:='';
  end;
end;

end.
