unit MazeGen;
{
  generator bludiska inspirovany tymto algoritmom
  http://www.emanueleferonato.com/2008/12/06/perfect-maze-generation-tile-based-version/

  maze_create vytvori pointer na objekt bludiska ktory je nasledne
  pouzivany ako prvy argument pre vsetky funkcie:
    - maze_set_value_for: nastavi jednu bunku pola na konkretny znak
    - maze_set: vymaze cele bludisko na znak
    - maze_value_for: zisti znak na konkretnej suradnici
    - maze_generate: vygeneruje bludisko
    - maze_destroy: znici objekt vrateny z maze_create

  znak steny budeme pouzivat '#' a volny priestor bude ' '
}

interface

type
  TCharArray = array of char;
  PCharArray = ^TCharArray;

  PMazePoint = ^TMazePoint;
  TMazePoint = record
    x, y : integer;
    prev, next : PMazePoint;
  end;

  PMaze = ^TMaze;
  TMaze = record
    width, height : integer;
    wall, path : char;
    parray : PCharArray;
    step : integer;
    root_point, last_point : PMazePoint;
  end;


function maze_create(width, height : integer; wall, path : char; x, y : Integer) : PMaze;
procedure maze_set_value_for(maze : PMaze; x, y : integer; v : char);
procedure maze_set(maze : PMaze; v : char);
function maze_value_for(maze : PMaze; x, y : Integer)  : char;
procedure maze_generate(maze : PMaze);
procedure maze_destroy(maze : PMaze);

implementation

const
  DIR_N = 0;
  DIR_S = 1;
  DIR_E = 2;
  DIR_W = 3;

var
  dir : array[0..3] of integer = ( DIR_N, DIR_S, DIR_E, DIR_W );

Procedure arr_shuffle(var parray : array of integer; n : Integer);
var i, j, t : integer;
begin
  if (n > 1) then
  begin
    for i := 0 to n - 2 do
    begin
      j := Random(n-1);
      t := parray[j];
      parray[j] := parray[i];
      parray[i] := t;
    end;
  end;
end;

Function maze_index_for(maze : PMaze; x, y : Integer) : Integer;
var idx : integer;
begin
  idx := (x * maze^.height) + y;
  if (idx > (maze^.width * maze^.height) - 1) then
    idx := (maze^.width * maze^.height) - 1;
  maze_index_for := idx;
end;

function maze_value_for(maze : PMaze; x, y : Integer)  : char;
begin
  maze_value_for := maze^.parray^[maze_index_for(maze, x, y)];
end;

procedure maze_set_value_for(maze : PMaze; x, y : integer; v : char);
begin
  maze^.parray^[maze_index_for(maze, x, y)] := v;
end;

procedure maze_destroy_point(point : PMazePoint);
begin
  if (point^.next <> nil) then
    maze_destroy_point(point^.next);
  if (point^.prev <> nil) then
    point^.prev^.next := nil;
  Dispose(point);
end;

function maze_create_point(x, y : integer; prev : PMazePoint) : PMazePoint;
var point : PMazePoint;
begin
  New(point);
  point^.x := x;
  point^.y := y;
  point^.next := nil;
  point^.prev := nil;
  if (prev <> nil) then
  begin
    point^.prev := prev;
    prev^.next := point;
  end;
  maze_create_point := point;
end;

function maze_create(width, height : integer; wall, path : char; x, y : Integer) : PMaze;
var maze : PMaze;
    arr : PCharArray;
begin
  if width mod 2 = 0 then
    inc(width);
  if height mod 2 = 0 then
    inc(height);

  New( maze );
  maze^.width := width;
  maze^.height := height;
  maze^.wall := wall;
  maze^.path := path;
  maze^.step := 0;
  New(arr);
  SetLength(arr^, width*height );
  maze^.parray := arr;
  maze^.root_point := maze_create_point(x, y, nil);
  maze^.last_point := maze^.root_point;
  maze_create := maze;
end;

procedure maze_destroy(maze : PMaze);
begin
  maze_destroy_point(maze^.root_point);
  Dispose(maze^.parray);
  Dispose(maze);
end;


function maze_move_to_dir(maze : PMaze; ldir : integer) : boolean;
var point : PMazePoint;
begin
  maze_move_to_dir := true;

  point := maze^.last_point;
  if (ldir = DIR_N) and (point^.y > 2) and (maze_value_for(maze, point^.x, point^.y - 2) = '#') then
  begin
    maze_set_value_for(maze, point^.x, point^.y - 1, ' ');
    maze_set_value_for(maze, point^.x, point^.y - 2, ' ');
    maze^.last_point := maze_create_point(point^.x, point^.y - 2, point);
    exit;
  end;

  if (ldir = DIR_S) and (point^.y < maze^.height - 2) and (maze_value_for(maze, point^.x, point^.y + 2) = '#') then
  begin
    maze_set_value_for(maze, point^.x, point^.y + 1, ' ');
    maze_set_value_for(maze, point^.x, point^.y + 2, ' ');
    maze^.last_point := maze_create_point(point^.x, point^.y + 2, point);
    maze_move_to_dir := true;
    exit;
  end;

  if (ldir = DIR_E) and (point^.x < maze^.width - 2) and (maze_value_for(maze, point^.x + 2, point^.y) =  '#') then
  begin
    maze_set_value_for(maze, point^.x + 1, point^.y, ' ');
    maze_set_value_for(maze, point^.x + 2, point^.y, ' ');
    maze^.last_point := maze_create_point(point^.x + 2, point^.y, point);
  end;
  if (ldir = DIR_W) and (point^.x > 2) and (maze_value_for(maze, point^.x - 2, point^.y) = '#') then
  begin
    maze_set_value_for(maze, point^.x - 1, point^.y, ' ');
    maze_set_value_for(maze, point^.x - 2, point^.y, ' ');
    maze^.last_point := maze_create_point(point^.x - 2, point^.y, point);
  end;
  maze_move_to_dir := false;
end;

procedure maze_move_back(maze : PMaze);
var temp : PMazePoint;
begin
  if (maze^.last_point <> nil) and (maze^.root_point <> maze^.last_point) then
  begin
    temp := maze^.last_point;
    maze^.last_point := temp^.prev;
    maze_destroy_point(temp);
  end;
end;

procedure maze_generate(maze : PMaze);
var move : boolean;
begin
  repeat
    arr_shuffle(dir, 4);
    move := maze_move_to_dir(maze, dir[0]);
    if not move then move := maze_move_to_dir(maze, dir[1]);
    if not move then move := maze_move_to_dir(maze, dir[2]);
    if not move then move := maze_move_to_dir(maze, dir[3]);
    if not move then maze_move_back(maze);
  until (maze^.root_point = maze^.last_point);
end;

procedure maze_set(maze : PMaze; v : char);
var x, y : integer;
begin
  for y := 0 to maze^.height - 1 do
    for x := 0 to maze^.width - 1 do
      maze^.parray^[maze_index_for(maze, x, y)] := v;
end;

end.