unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    BitBtn1: TBitBtn;
    Content: TMemo;
    BitBtn2: TBitBtn;
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.BitBtn1Click(Sender: TObject);
 var
  MemSourceStream, MemDestStream: TMemoryStream;
begin
  MemSourceStream:= TMemoryStream.Create;
  try
    MemDestStream:= TMemoryStream.Create;
    try
      MemSourceStream.WriteComponent(BitBtn1);
      MemSourceStream.Seek(0, soFromBeginning);
      ObjectBinaryToText(MemSourceStream, MemDestStream);
      MemDestStream.Seek(0, soFromBeginning);
      Content.Lines.LoadFromStream(MemDestStream)
    finally
      MemDestStream.Free
    end;
  finally
    MemSourceStream.Free
  end;
  end;
procedure TForm1.BitBtn2Click(Sender: TObject);
begin
close;
end;

end.
