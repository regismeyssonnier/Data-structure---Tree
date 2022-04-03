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
    TMyThreadclzwsth = class(TThread)
    private
      { Private declarations }
    protected
      procedure Execute; override;
    end;

type
    TMyThreaddlzwsth = class(TThread)
    private
      { Private declarations }
    protected
      procedure Execute; override;
    end;

type
    TMyThreadclzws = class(TThread)
    private
      { Private declarations }
    protected
      procedure Execute; override;
    end;

type
    TMyThreaddlzws = class(TThread)
    private
      { Private declarations }
    protected
      procedure Execute; override;
    end;

type
    TMyThreadclzw = class(TThread)
    private
      { Private declarations }
    protected
      procedure Execute; override;
    end;

type
    TMyThreaddlzw = class(TThread)
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
    RadioGroupOpt: TRadioGroup;
    RadioGroupTim: TRadioGroup;
    Selectcheckopt: TCheckBox;
    Selectchecktim: TCheckBox;
    Powergroup: TRadioGroup;
    Selectpoweropt: TCheckBox;
    PopupMenu1: TPopupMenu;
    New2: TMenuItem;
    N2: TMenuItem;
    Selectoption1: TMenuItem;
    SelectTime1: TMenuItem;
    SelectPower1: TMenuItem;
    N3: TMenuItem;
    Open1: TMenuItem;
    Path1: TMenuItem;

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
    procedure SelectcheckoptClick(Sender: TObject);
    procedure SelectchecktimClick(Sender: TObject);
    procedure SelectpoweroptClick(Sender: TObject);
    procedure New2Click(Sender: TObject);
    procedure Selectoption1Click(Sender: TObject);
    procedure SelectTime1Click(Sender: TObject);
    procedure SelectPower1Click(Sender: TObject);
    procedure Open1Click(Sender: TObject);
    procedure Path1Click(Sender: TObject);

  private
    { Déclarations privées }
    procedure compression();stdcall;
    procedure decompression();stdcall;
    procedure compressionlzwslowth();stdcall;
    procedure decompressionlzwslowth();stdcall;
    procedure compressionlzwslow();stdcall;
    procedure decompressionlzwslow();stdcall;
    procedure compressionlzw();stdcall;
    procedure decompressionlzw();stdcall;
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
// lzw
procedure Compress_LZW_slow(name:WideString; namef:WideString);
  stdcall; external HUFFMAN_LIB name 'Compress_LZW_slow';
procedure Decompress_LZW_slow(name:WideString; namef:WideString);
  stdcall; external HUFFMAN_LIB name 'Decompress_LZW_slow';
procedure Compress_LZW_slow_th(name:WideString; namef:WideString);
  stdcall; external HUFFMAN_LIB name 'Compress_LZW_slow_th';
procedure Decompress_LZW_slow_th(name:WideString; namef:WideString);
  stdcall; external HUFFMAN_LIB name 'Decompress_LZW_slow_th';
procedure Compress_LZW(name:WideString; namef:WideString);
  stdcall; external HUFFMAN_LIB name 'Compress_LZW';
procedure Decompress_LZW(name:WideString; namef:WideString);
  stdcall; external HUFFMAN_LIB name 'Decompress_LZW';


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

procedure TForm1.compressionlzwslowth();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Compress_LZW_slow_th(FilePathlab.Text, FileDestlab.Text);
  CompressButt.Enabled := True;
end;

procedure TMyThreadclzwsth.Execute;
begin
     Form1.compressionlzwslowth;
end;

procedure TForm1.decompressionlzwslowth();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Decompress_LZW_slow_th(FilePathlab.Text, FileDestlab.Text);
  CompressButt.Enabled := True;
end;

procedure TMyThreaddlzwsth.Execute;
begin
     Form1.decompressionlzwslowth;
end;

procedure TForm1.compressionlzwslow();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Compress_LZW_slow(FilePathlab.Text, FileDestlab.Text);
  CompressButt.Enabled := True;
end;

procedure TMyThreadclzws.Execute;
begin
     Form1.compressionlzwslow;
end;

procedure TForm1.decompressionlzwslow();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Decompress_LZW_slow(FilePathlab.Text, FileDestlab.Text);
  CompressButt.Enabled := True;
end;

procedure TMyThreaddlzws.Execute;
begin
     Form1.decompressionlzwslow;
end;

procedure TForm1.compressionlzw();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Compress_LZW(FilePathlab.Text, FileDestlab.Text);
  CompressButt.Enabled := True;
end;

procedure TMyThreadclzw.Execute;
begin
     Form1.compressionlzw;
end;

procedure TForm1.decompressionlzw();stdcall;
begin
  init_progression();
  CDTimer.Enabled := True;
  Decompress_LZW(FilePathlab.Text, FileDestlab.Text);
  CompressButt.Enabled := True;
end;

procedure TMyThreaddlzw.Execute;
begin
     Form1.decompressionlzw;
end;

procedure TForm1.CompressButtClick(Sender: TObject);
var
    thc : TMyThreadc;
    thd : TMyThreadd;
    thclzwsth :TMyThreadclzwsth;
    thdlzwsth :TMyThreaddlzwsth;
    thclzws :TMyThreadclzws;
    thdlzws :TMyThreaddlzws;
    thclzw :TMyThreadclzw;
    thdlzw :TMyThreaddlzw;
begin
     if(Selectchecktim.Checked = false) and (Selectcheckopt.Checked = false) and (Selectpoweropt.Checked = false)  then
     begin
          Selectcheckopt.Checked := true;
     end;

     if((FilePathlab.Text <> '') and  (FileDestlab.Text <> ''))then
     begin
          ProgressBar1.Min := 0;
          ProgressBar1.Max := 100;
          ProgressBar1.Position := 0;
          CompressButt.Enabled := False;
         if TabControl1.TabIndex = 0 then
         begin
              if Selectcheckopt.Checked then
              begin
                  if(RadioGroupopt.ItemIndex = 0) then   //huffman
                  begin
                      thc := TMyThreadc.Create(False);
                  end
                  else if(RadioGroupopt.ItemIndex = 1) then   //lzwslth
                  begin
                      thclzwsth := TMyThreadclzwsth.Create(False);
                  end;
              end
              else if Selectchecktim.Checked then
              begin
                  if(RadioGrouptim.ItemIndex = 0) then   //huffman
                  begin
                      thc := TMyThreadc.Create(False);
                  end
                  else if(RadioGrouptim.ItemIndex = 1) then   //lzwslth
                  begin
                      thclzws := TMyThreadclzws.Create(False);
                  end
                  else if(RadioGrouptim.ItemIndex = 2) then   //lzwslth
                  begin
                      thclzws := TMyThreadclzws.Create(False);
                  end;

              end
              else if Selectpoweropt.Checked then
              begin
                  if(PowerGroup.ItemIndex = 0) then   //huffman
                  begin
                      thc := TMyThreadc.Create(False);
                  end
                  else if(PowerGroup.ItemIndex = 1) then   //lzwslth
                  begin
                      thclzw := TMyThreadclzw.Create(False);
                  end
                  else if(PowerGroup.ItemIndex = 2) then   //lzwslth
                  begin
                      thclzwsth := TMyThreadclzwsth.Create(False);
                  end;

              end;

         end
         else if TabControl1.TabIndex = 1 then
         begin
              if Selectcheckopt.Checked then
              begin
                  if(RadioGroupopt.ItemIndex = 0) then    // huffman
                  begin
                      thd := TMyThreadd.Create(False);
                  end
                  else if(RadioGroupopt.ItemIndex = 1) then   //lzwslth
                  begin
                      thdlzwsth := TMyThreaddlzwsth.Create(False);
                  end;
              end
              else if Selectchecktim.Checked then
              begin
                  if(RadioGrouptim.ItemIndex = 0) then   //huffman
                  begin
                      thd := TMyThreadd.Create(False);
                  end
                  else if(RadioGrouptim.ItemIndex = 1) then   //lzwslth
                  begin
                      thdlzws := TMyThreaddlzws.Create(False);
                  end
                  else if(RadioGrouptim.ItemIndex = 2) then   //lzwslth
                  begin
                      thdlzwsth := TMyThreaddlzwsth.Create(False);
                  end;

              end
              else if Selectpoweropt.Checked then
              begin
                  if(PowerGroup.ItemIndex = 0) then   //huffman
                  begin
                      thd := TMyThreadd.Create(False);
                  end
                  else if(PowerGroup.ItemIndex = 1) then   //lzwslth
                  begin
                      thdlzw := TMyThreaddlzw.Create(False);
                  end
                  else if(PowerGroup.ItemIndex = 2) then   //lzwslth
                  begin
                      thdlzwsth := TMyThreaddlzwsth.Create(False);
                  end;

              end;


         end;
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

procedure TForm1.New2Click(Sender: TObject);
begin
     FileDestlab.Text := '';
     FilePathlab.Text := '';
end;

procedure TForm1.Open1Click(Sender: TObject);
var
  DirSelected : string;
begin
     OpenDialog1.Execute;
     FilePathlab.Text := OpenDialog1.FileName;

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

procedure TForm1.Path1Click(Sender: TObject);
var
  DirSelected : string;
begin
  if SelectDirectory('Select a folder:', 'C:\Users\', DirSelected) then
  begin
      FileDestlab.Text := DirSelected;
  end;
end;

procedure TForm1.SelectcheckoptClick(Sender: TObject);
begin
     Selectchecktim.Checked := false;
     Selectpoweropt.Checked := false;
     Selectcheckopt.SetFocus();
     //Selectcheckopt.Checked := true;
end;

procedure TForm1.SelectchecktimClick(Sender: TObject);
begin
     Selectcheckopt.Checked := false;
     Selectpoweropt.Checked := false;
     Selectchecktim.SetFocus();
end;

procedure TForm1.Selectoption1Click(Sender: TObject);
begin
     Selectcheckopt.Checked := true;
     Selectchecktim.Checked := false;
     Selectpoweropt.Checked := false;
     //Selectcheckopt.SetFocus();
end;

procedure TForm1.SelectPower1Click(Sender: TObject);
begin
      Selectpoweropt.Checked := true;
     Selectchecktim.Checked := false;
     Selectcheckopt.Checked := false;
     Selectpoweropt.SetFocus();
end;

procedure TForm1.SelectpoweroptClick(Sender: TObject);
begin
     Selectchecktim.Checked := false;
     Selectcheckopt.Checked := false;
     Selectpoweropt.SetFocus();
end;

procedure TForm1.SelectTime1Click(Sender: TObject);
begin
     Selectchecktim.Checked := true;
     Selectcheckopt.Checked := false;
     Selectpoweropt.Checked := false;
     Selectchecktim.SetFocus();
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
