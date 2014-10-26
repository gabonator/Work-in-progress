unit PathFinder;

{
  Vyhladavac najkratsej cesty zalozeny na algoritme 
  "Wave propagation flood fill", napisany nerekurzivne
  aby sme setrili stack, vytvori si pole rovnakych rozmerov
  ako je nasa mapa, nastavi do jedneho koncoveho bodu cislo 1
  a toto postupne iterativne rozsiruje a inkrementuje az do
  dosiahnutia druheho koncoveho bodu.
  Potom uz iba postupujeme opacnym smerom - od najvyssieho cisla N
  sledujeme jeho susedov a presunieme sa na bod s hodnotou N-1 a 
  potom dalej na N-2 az kym nedosiahneme N=1. Vyslednu cestu
  ulozime do pola gPath, kde su ulozene cisla reprezentujuce
  bod v mriezke - hodnota je urcena ako y*sirka_mapy+x
}

interface
uses Common;

var
   gPath : Array of Integer;


procedure FindShortestPath;

implementation
{ ------------- vyhladavac najkratsej cesty ---- }

procedure FindShortestPath;
var
  gPathBuf : Array[0..gMapHeight] of array[0..gMapWidth] of Integer;
  sx, sy, fx, fy : integer; // suradnice zaciatku a konca
  cont : boolean;
  cur : integer;
  x, y, i, j : integer;
begin
  { najdeme pociatocny a koncovy bod }
  for y := 0 to gMapHeight do
    for x := 0 to gMapWidth do
    begin
      gPathBuf[y][x] := 0;
      case gMap[y][x] of
        'F': begin // pojdeme od konca
          sx := x;
          sy := y;
          end;
        'S': begin // ku zaciatku, lebo pri prehladavani ideme odzadu
          fx := x;
          fy := y;
          end;
      end;
    end;

  gPathBuf[sy][sx] := 1;

  { flood fill sirenie postupne v iteraciach }
  repeat
    cont := false; // mame sa kam sirit?
    for y := 1 to gMapHeight-1 do
      for x := 1 to gMapWidth-1 do
      if gPathBuf[y][x] > 0 then
      begin
        cur := gPathBuf[y][x]+1;
        if (gMap[y-1,x] <> '#') and (gPathBuf[y-1][x] = 0) then begin gPathBuf[y-1][x] := cur; cont := true; end;
        if (gMap[y+1,x] <> '#') and (gPathBuf[y+1][x] = 0) then begin gPathBuf[y+1][x] := cur; cont := true; end;
        if (gMap[y,x-1] <> '#') and (gPathBuf[y][x-1] = 0) then begin gPathBuf[y][x-1] := cur; cont := true; end;
        if (gMap[y,x+1] <> '#') and (gPathBuf[y][x+1] = 0) then begin gPathBuf[y][x+1] := cur; cont := true; end;
      end;
  until not cont or (gPathBuf[fy][fx] <> 0);

  x := fx;
  y := fy;
  SetLength( gPath, gPathBuf[fy][fx] );
  j := 0;
  gPath[j] := y*gMapWidth + x;
  { backtrace naspat }
  for i := gPathBuf[fy][fx]-1 downto 1 do
  begin
    if ( gPathBuf[y,x-1] = i ) then x := x-1;
    if ( gPathBuf[y,x+1] = i ) then x := x+1;
    if ( gPathBuf[y-1,x] = i ) then y := y-1;
    if ( gPathBuf[y+1,x] = i ) then y := y+1;
    if ( gPathBuf[y,x] <> i ) then
    begin
      Writeln('Stratil som sa!');
    end;
    inc(j);
    gPath[j] := y*gMapWidth + x;
  end;
end;

{ ------------- koniec vyhladavaca ------ }
end.