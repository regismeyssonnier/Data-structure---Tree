unit Compressor;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.Menus, Vcl.StdCtrls, FileCtrl, System.Zip, System.ZLib,
  Vcl.ComCtrls;

type
  TForm1 = class(TForm)
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    New1: TMenuItem;
    Exit1: TMenuItem;
    N1: TMenuItem;
    About1: TMenuItem;
    Author1: TMenuItem;
    OpenDialog1: TOpenDialog;
    ProgressBar1: TProgressBar;
    TabControl1: TTabControl;
    CompressButt: TButton;
    Label1: TLabel;
    FilePathlab: TEdit;
    Label2: TLabel;
    FileDestlab: TEdit;
    FileDestbutt: TButton;
    OpenFileButt: TButton;

    procedure Exit1Click(Sender: TObject);
    procedure Author1Click(Sender: TObject);
    procedure OpenFileButtClick(Sender: TObject);
    procedure FileDestbuttClick(Sender: TObject);
    procedure New1Click(Sender: TObject);
    procedure TabControl1Change(Sender: TObject);
    procedure CompressButtClick(Sender: TObject);

  private
    { Déclarations privées }
  public
    { Déclarations publiques }
  end;

var
  Form1: TForm1;

implementation
  uses About;
{$R *.dfm}

const
HUFFMAN_LIB = 'Huffmandll.dll';
procedure Compress_file(name:WideString; namef:WideString);
  stdcall; external HUFFMAN_LIB name 'Compress_file';
procedure Decompress_file(name:WideString ; namef:WideString );
  stdcall; external HUFFMAN_LIB name 'Decompress_file';

procedure TForm1.Author1Click(Sender: TObject);
var Tab : TAboutForm;
begin
    Tab := TAboutForm.Create(nil);
    Tab.ShowModal;
    Tab.Release;
end;

procedure TForm1.CompressButtClick(Sender: TObject);
var
  FZip: TZipFile;
  myFile : TextFile;
  LInput, LOutput: TFileStream;
  LZip: TZCompressionStream;
  w : WideString;
    w2 : WideString;
begin

     if TabControl1.TabIndex = 0 then
     begin
          Compress_file(FilePathlab.Text, FileDestlab.Text);

     end
     else if TabControl1.TabIndex = 1 then
     begin
          Decompress_file(FilePathlab.Text, FileDestlab.Text);
     end;





end;

procedure TForm1.Exit1Click(Sender: TObject);
begin
    Close;

end;

procedure TForm1.FileDestbuttClick(Sender: TObject);
var
  DirSelected : string;
begin
  if SelectDirectory('Select a folder:', 'C:\Users\', DirSelected) then
  begin
      FileDestlab.Text := DirSelected;
  end;

end;

procedure TForm1.New1Click(Sender: TObject);
begin
     FileDestlab.Text := '';
     FilePathlab.Text := '';
end;

procedure TForm1.OpenFileButtClick(Sender: TObject);
var
  DirSelected : string;
begin
     OpenDialog1.Execute;
     FilePathlab.Text := OpenDialog1.FileName;
    { if SelectDirectory('Select a folder:', 'C:\Users\', DirSelected) then
  begin
      FilePathlab.Text := DirSelected;
  end;
       }
end;

procedure TForm1.TabControl1Change(Sender: TObject);
begin
     if TabControl1.TabIndex = 0 then
     begin
          CompressButt.Caption := 'Compress';
          Label1.Caption := 'File to compress :';
     end
     else if TabControl1.TabIndex = 1 then
     begin
          CompressButt.Caption := 'Decompress';
          Label1.Caption := 'File to decompress :';
     end;
end;

end.
