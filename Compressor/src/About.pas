unit About;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Compressor;

type
  TAboutForm = class(TForm)
    Label1: TLabel;
  private
    { Déclarations privées }
  public
    AboutForm: TAboutForm;
    { Déclarations publiques }
  end;

var
  AboutForm: TAboutForm;

implementation

{$R *.dfm}

end.
