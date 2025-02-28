unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Menus;

type
  TForm1 = class(TForm)
    MainMenu1: TMainMenu;
    BitBtn1: TBitBtn;
    N1: TMenuItem;
    NOpenModalForm: TMenuItem;
    NOpenModelessForm: TMenuItem;
    procedure NOpenModalFormClick(Sender: TObject);
    procedure NOpenModelessFormClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses Unit2, Unit3;

{$R *.dfm}

procedure TForm1.NOpenModalFormClick(Sender: TObject);
begin
  Form2.ShowModal;
end;

procedure TForm1.NOpenModelessFormClick(Sender: TObject);
begin
  Form3.Show;
end;

end.
