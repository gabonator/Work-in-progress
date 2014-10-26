unit App;

interface
Uses Common, OpenGl, GlDrawing, MazeGen, PathFinder;

procedure appInit;
procedure appDraw;


implementation

var BaseTime : Longint = 0;

procedure getPathPoint(f : real; var x, y, z : glFloat; defz : glFloat );
var dec : integer;
    flo : real;
    x1, y1, z1, x2, y2, z2 : glFloat;
begin
  f := f+1000; { problem so zapornymi hodnotami f}
  dec := Trunc(f);
  flo := f - dec ;
  dec := dec - 1000;

  if (dec >= 0) and (dec < length(gPath)) then
  begin
    x1 := gPath[dec] mod gMapWidth;
    y1 := gPath[dec] div gMapWidth;
    x1 := -(x1-gMapWidth/2);
    y1 := y1-gMapHeight/2;
    z1 := defz;
  end else
  begin
    x1 := x;
    y1 := y;
    z1 := z;
  end;
  if (dec+1 >= 0) then
  begin
    dec := dec + 1;
    if dec > length(gPath)-1 then
      dec := length(gPath)-1;

    x2 := gPath[dec] mod gMapWidth;
    y2 := gPath[dec] div gMapWidth;
    x2 := -(x2-gMapWidth/2);
    y2 := y2-gMapHeight/2;
    z2 := defz;
  end else
  begin
    x2 := x;
    y2 := y;
    z2 := z;
  end;

  // interpoluj
  x := x1 + (x2-x1)*flo;
  y := y1 + (y2-y1)*flo;
  z := z1 + (z2-z1)*flo;
end;

{
  remap - natiahneme vygenerovanu mapu tak aby vnutorne bunky vytvarali
  miestnosti s rozmerom 3x3. Bunky sa nachadzaju vzdy na suradniciach ked
  x aj y su zaroven delitelne dvomi s vynimkou okraja mapy
}
var
  arrRemap : Array[0..7*4-1] of Integer = (
  0, 1, 1, 1,
  2, 3, 3, 3,
  4, 5, 5, 5,
  6, 7 ,7 ,7,
  8, 9, 9, 9,
  10, 11, 11, 11,
  12, 13, 13, 13);
procedure remapCoord( var x : integer );
begin
{  if x > 9 then x := 9;}
  x := arrRemap[x];
end;

procedure appInit;
var x, y : integer;
    maze : PMaze;
    tx, ty, lx, ly : integer;
begin
  { obvodovy ram mapy }
  for y := 0 to gMapHeight - 1 do
    for x := 0 to gMapWidth - 1 do
    begin
      gMap[y, x] := ' ';
      if (x=0) or (x=gMapWidth-1) or (y=0) or (y=gMapHeight-1) then
        gMap[y, x] := '#';
    end;

  { vygenerovanie bludiska }
  Randomize;
  {maze := maze_create(gMapWidth, gMapHeight, '#', ' ', 1, 1);}
  tx := 13;
  ty := 13;

  maze := maze_create(tx, ty, '#', ' ', 1, 1);
  maze_set(maze, '#');
  maze_generate(maze);

  { skopirovanie vygenerovaneho bludiska do nasej mapy gMap }
  for y := 0 to gMapHeight-1 do
    for x := 0 to gMapWidth-1 do
    begin
      lx := x;
      ly := y;
      remapCoord(lx);
      remapCoord(ly);
      gMap[y, x] := maze_value_for(maze, lx, ly);
      {dopln steny}
      if (x mod 4 = 0) and (y mod 4 <> 2) then
        gMap[y, x] := '#';
      if ((y = 8) or (y = 16)) and (x mod 4 <> 2) then
        gMap[y, x] := '#';
    end;

  { dopln dvere }
  for y := 0 to gMapHeight-1 do
    for x := 0 to gMapWidth-1 do
    begin
      if (x mod 4 = 0) and (y mod 4 = 2) and (gMap[y, x] = ' ') then
        gMap[y, x] := 'D';
      if (y = 8) and (x mod 4 = 2) and (gMap[y, x] = ' ') and (gMap[y, x+1] = '#') then
        gMap[y, x] := 'd';
    end;

  { okna }
  for y := 0 to gMapHeight-1 do
    for x := 0 to gMapWidth-1 do
    begin
      if ( x = 0 ) and ( y mod 4 = 2 ) and ( gMap[y, x+1] = ' ' ) then
        gMap[y, x] := 'W';
      if ( x = gMapWidth-1 ) and ( y mod 4 = 2 ) and ( gMap[y, x-1] = ' ' ) then
        gMap[y, x] := 'w';
    end;

{  gMap[2, 2] := 'S';}

  maze_destroy(maze);
(*
  { urcenie cieloveho bodu vovnutri mapy }
  // najdi nahodny bod vovnutri - to bude nas ciel
  x := 0;
  y := 0;
  repeat
    x := Random(gMapHeight-1);
    y := Random(gMapWidth-1);
  until gMap[y, x] = ' ';
  gMap[y, x] := 'F';
*)
  { vypocitaj najkratsiu cestu a uloz si ju do gPath }
  FindShortestPath;
end;

procedure RecurseFill(x, y : integer; ch : Char);
var chCur : char;
begin
  chCur := gMap[y, x];
  if (chCur = ch) or (chCur='#') or (chCur='d') or (chCur='D') or (chCur='w') or (chCur='W') then
    exit;

  gMap[y, x] := ch;
  RecurseFill(x-1, y, ch);
  RecurseFill(x+1, y, ch);
  RecurseFill(x, y-1, ch);
  RecurseFill(x, y+1, ch);
end;

procedure SelectBlock(x, y : integer);
begin
  if ( gMap[y, x] = 'S' ) then
  begin
    startX := -1;
    RecurseFill(x, y, ' ');
    exit;
  end;
  if ( gMap[y, x] = 'F' ) then
  begin
    finishX := -1;
    RecurseFill(x, y, ' ');
    exit;
  end;
  if ( gMap[y, x] = ' ' ) then
  begin
    if startX = -1 then
    begin
      startX := x;
      startY := y;
      RecurseFill(x, y, 'S');
      exit;
    end;
    if finishX = -1 then
    begin
      finishX := x;
      finishY := y;
      RecurseFill(x, y, 'F');
      exit;
    end;
  end;
end;

procedure appDraw();
var  xAngle, yAngle, zAngle, angle : glFloat;
     y, x, i : integer;

var
    x1, y1, x2, y2 : integer;
    px, py, pz,
    qx, qy, qz : glFloat;
    time : glFloat;
    maxTime : glFloat;

    var tx, ty : integer;

 begin
  glClearColor(0.0, 0.9, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT);    // Clear The Screen And The Depth Buffer

  glLoadIdentity(); // Reset The View

  px := 0; py := 10; pz := 35;
  qx := 0; qy := 0; qz := 0;

  if MouseButton = true then
  begin
    tx := Round(MouseCoord[1]);
    ty := Round(MouseCoord[2]);
    if ( tx > 0 ) and ( tx < gMapWidth-1 ) and ( ty > 0 ) and ( ty < gMapHeight - 1) then
    begin
      SelectBlock(tx, ty);
      FindShortestPath;
{
      if gMap[ty,tx] = '#' then
        gMap[ty,tx] := ' '
      else
        gMap[ty,tx] := '#';
}
    end;
    MouseButton := false;
  end;

  if LastKey = 13 then
  begin
    BaseTime := ElapsedTime;
    LastKey := 0;
  end;
  if (startX = -1) or (finishX = -1) then
    BaseTime := 0;
  if BaseTime <> 0 then
    time := (ElapsedTime - BaseTime) / 1000
  else
    time := 0;
  maxTime := 2.1 + length(gPath);
  while (time > maxTime) do
    time := time - maxTime;

  { nastav pohlad }
  getPathPoint(time - 0.5 - 2.1, px, py, pz, 0.5); // kamera
  getPathPoint(time + 1.0 - 2.1, qx, qy, qz, 0.5); // ciel

  glLoadIdentity();
  gluLookAt( px, py, pz,
           qx, qy, qz,
           0, 0, 1);

  { vykresli mapu }
  for y := 0 to gMapHeight do
    for x := 0 to gMapWidth do
    begin
      case gMap[y][x] of
        '#': DrawBox(x, y, 0);
        ' ': DrawGround(x, y, 0);
        'D': begin
               DrawGround(x, y, 0);
               DrawDoorX(x, y);
             end;
        'd': begin
               DrawGround(x, y, 0);
               DrawDoorY(x, y);
             end;
        'W': begin
               DrawGround(x, y, 0);
               DrawWindowX(x, y);
             end;
        'w': begin
               DrawGround(x, y, 0);
               DrawWindowX(x+1, y);
             end;
        'S': DrawStart(x, y);
        'F': DrawFinish(x, y);
      end;
    end;

  { vykresli ruru }
  for i := 0 to length(gPath)-2 do
  begin
    x1 := gPath[i] mod gMapWidth;
    y1 := gPath[i] div gMapWidth;
    x2 := gPath[i+1] mod gMapWidth;
    y2 := gPath[i+1] div gMapWidth;
   DrawLine( x1, y1, x2, y2 );
  end;
end;

end.
