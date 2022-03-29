unit Compressor;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.Menus, Vcl.StdCtrls, FileCtrl, System.Zip, System.ZLib,
  Vcl.ComCtrls, Vcl.ExtCtrls;

type
    TMyThreadc = class(TThread)
    private
      { Private declarations }
    protected
      procedure Execute; override;
    end;

type
    TMyThreadd = class(TThread)
    private
      { Private declarations }
    protected
      procedure Execute; override;
    end;

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
    CDTimer: TTimer;
    upButt: TButton;
    downButt: TButton;

    procedure Exit1Click(Sender: TObject);
    procedure Author1Click(Sender: TObject);
    procedure OpenFileButtClick(Sender: TObject);
    procedure FileDestbuttClick(Sender: TObject);
    procedure New1Click(Sender: TObject);
    procedure TabControl1Change(Sender: TObject);
    procedure CompressButtClick(Sender: TObject);
    procedure CDTimerTimer(Sender: TObject);
    procedure upButtClick(Sender: TObject);
    procedure downButtClick(Sender: TObject);

  private
    { Déclarations privées }
    procedure compression();stdcall;
    procedure decompression();stdcall;
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
procedure init_progression();
  stdcall; external HUFFMAN_LIB name 'init_progression';
function get_progression_interface():integer;
  stdcall; external HUFFMAN_LIB name 'get_progression_interface';
procedure End_Compress_file();
  stdcall; external HUFFMAN_LIB name 'End_Compress_file';
procedure End_Decompress_file();
  stdcall; external HUFFMAN_LIB name 'End_Decompress_file';

procedure TForm1.Author1Click(Sender: TObject);
var Tab : TAboutForm;
begin
    Tab := TAboutForm.Create(nil);
    Tab.ShowModal;
    Tab.Release;
end;

procedure TForm1.CDTimerTimer(Sender: TObject);
begin
     ProgressBar1.Position := get_progression_interface;

end;

procedure TForm1.compression();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Compress_file(FilePathlab.Text, FileDestlab.Text);
  End_Compress_file;
  CompressButt.Enabled := True;
end;

procedure TForm1.decompression();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Decompress_file(FilePathlab.Text, FileDestlab.Text);
  End_Decompress_file;
  CompressButt.Enabled := True;
end;

procedure TMyThreadc.Execute;
begin
     Form1.compression;
end;

procedure TMyThreadd.Execute;
begin
     Form1.decompression;
end;


procedure TForm1.CompressButtClick(Sender: TObject);
var
    thc : TMyThreadc;
    thd : TMyThreadd;
begin
     ProgressBar1.Min := 0;
     ProgressBar1.Max := 100;
     ProgressBar1.Position := 0;
     CompressButt.Enabled := False;
     if TabControl1.TabIndex = 0 then
     begin

          thc := TMyThreadc.Create(False);

     end
     else if TabControl1.TabIndex = 1 then
     begin
          thd := TMyThreadd.Create(False);

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

procedure TForm1.upButtClick(Sender: TObject);
begin
      FilePathlab.Text := FileDestlab.Text;
end;

procedure TForm1.downButtClick(Sender: TObject);
begin
      FileDestlab.Text := FilePathlab.Text;
end;

end.
