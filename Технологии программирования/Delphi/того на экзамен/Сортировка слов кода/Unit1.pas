unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, Buttons, ExtCtrls;

type
  TfmStGrid = class(TForm)
    Panel1: TPanel;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    OpenDialog1: TOpenDialog;
    StringGrid1: TStringGrid;
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmStGrid: TfmStGrid;

implementation

{$R *.dfm}

procedure TfmStGrid.BitBtn1Click(Sender: TObject);
function GetWord(var S: string): string;
{��������������� ������� ��� ��������� ���������� ����� �� ������}
const  //���-�� �������� �����
  Letters: set of Char = ['a'..'z', 'A'..'Z', '�'..'�'];
begin
  Result := '';
  //������� � ������ ������ ��� �������, �� ����������� � �����
  while (S <> '') and not (S[1] in Letters) do
    Delete(S, 1, 1);
  //��������� ��������� �����
  while (S <> '') and (S[1] in Letters) do
  begin
    Result := Result + S[1];
    Delete(S, 1, 1);
  end;
end; //GetWord
var
  F: TextFile; //���� � �������
  S, Word: string; //��������������� ������
  NCol, NRow: Integer; //����� ������� ������� � ��������� ����
  Words: TStringList; //������ ��������������� ���� �� �����
begin
  //� ������� ������������ ����������� ������������ ��� �����
  if not OpenDialog1.Execute then
    Exit;  //������������ ��������� ������� ����
  //�������� ������� ����
  AssignFile(F, OpenDialog1.FileName);
  try
    Reset(F);
  except
    //���� ������ �������
    ShowMessage('���������� ������� ���� ' + OpenDialog1.FileName);
    Exit;
  end;
  //������� ������ Words
  Words := TStringList.Create;
  Words.Sorted := True; //��������� ������
  Words.Duplicates := dupIgnore; //��������� ���������
  //�������� ��������� ���� ����� ���������� �������
  Screen.Cursor := crHourGlass;
  //������ ���� �� �������
  while not Eof(F) do
  begin
    Readln(F, S); //������ ��������� ������ => �������� �� ������ ����� � ������� � Words
    while S <> '' do
    begin
      Word := GetWord(S);
      if Word <> '' then
        Words.Add(Word); //�� ��������� ������ ������
    end;
  end; //while not eof(f) do
  Screen.Cursor := crDefault; //�� ��������� ������ ������
  CloseFile(F); //��������� ����
  if Words.Count = 0 then
    Exit; //������ ���� - �������
  with StringGrid1 do
  begin
    NCol := 1; // ����� ������ ������� ����
    //���� ������������ �������
    while Words.Count >0 do
    begin
      //���������// ��������� ������� � ���. �������� ������ ����
      Cells[NCol, 0] := AnsiUpperCase(Words[0][1]);
      NRow := 0;
      //���� ���������� ��������� �������
      while (Words.Count > 0) and (Cells[NCol, 0] = AnsiUpperCase(Words[0][1])) do
      begin
        inc(NRow); //����� �������� ����
        if NRow = RowCount then
        begin
           //��������� ������� ����
           RowCount := RowCount + 1; {��� ��-�� ������ ��� inc!}
           Cells[0, NRow] := IntToStr(NRow);
        end;
        Cells[NCol, NRow] := Words[0];
        Words.Delete(0);
      end;
      //��������� � ��������� �������
      if Words.Count = 0 then
        Break; //������� ������, ���� ���� ������ ���
        inc(NCol); //��������� � ��������� �������
        ColCount := ColCount + 1; //��������� ������� ������ �� 1 �������
    end;
  end;
end;
end.
