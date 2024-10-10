program Test;
{$H+}
{$mode objfpc}  
uses sysutils, math, crt;

type
    TObject = class
    public
          valueI : ^Integer;
          N : Integer;

          constructor Create(sz : Integer);
          destructor Destroy; override;
          procedure Sort(f, l : Integer);
          procedure Display();
    private
          function Partition(f, l, pivot: Integer):Integer;


    end;

constructor TObject.Create(sz : Integer);
begin
     N := sz;
     GetMem(valueI, N * SizeOf(Integer));

end;

function TObject.Partition(f, l, pivot: Integer):Integer;
var
   tmp, j, i : Integer;

begin
     tmp := valueI[l];
     valueI[l] := valueI[pivot];
     valueI[pivot] := tmp;

     j := f;
     for i:= f to l-1 do
     begin
          if valueI[i] <= valueI[l] then
          begin
               tmp := valueI[i];
               valueI[i] := valueI[j];
               valueI[j] := tmp;
               j := j+1;
          end;
     end;
     tmp := valueI[l];
     valueI[l] := valueI[j];
     valueI[j] := tmp;

     Result := j;


end;

procedure TObject.Sort(f, l: Integer);
var
   pivot : Integer;
begin
     if f < l then
     begin
         pivot := (f+l) div 2;
         pivot := Partition(f, l, pivot);
         Sort(f, pivot - 1);
         Sort(pivot + 1, l);

     end;
end;

procedure TObject.Display();
var
   i : Integer;
begin
     for i:= 0 to N do
     begin
         Write(inttostr(valueI[i]) + ' ')
     end;
     WriteLn();

end;

destructor TObject.Destroy;
begin
  FreeMem(valueI); // Free the allocated memory
  inherited Destroy;
end;


type
  TTest = class
  private
    FValue: Integer;  // Field to store a value
  public
    constructor Create(AValue: Integer);  // Constructor declaration
    procedure ShowValue;  // Method to show the value
  end;

{ TTest }

constructor TTest.Create(AValue: Integer);
begin
  FValue := AValue;  // Assign the input value to the field
end;

procedure TTest.ShowValue;
begin
  WriteLn('The value is: ', FValue);
end;


var
   obj : TObject;
   i : Integer;

begin
     Randomize;
     obj := TObject.Create(49);
     for i := 0 to 49 do
     begin
          obj.valueI[i] := Random(100)+1;  // Generate random numbers between 0 and 99
     end;
     obj.Display();
     obj.Sort(0, 49);
     WriteLn('-----------------------');
     obj.Display();
  ReadKey;
end.
