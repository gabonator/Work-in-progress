unit Common;

{
  Rozmer a samotne pole mapy mame tu a zdielame ho pre viacej unitov
  (napr. PathFinder), takisto aj vyslednu cestu (gPath) a textury pre
  opengl
}

interface
Uses Opengl, Windows;

const
     gMapWidth = 25;
     gMapHeight = 25;
var
     gMap : Array[0..gMapHeight] of array[0..gMapWidth] of Char;
     gPath : Array of Integer;

var
     FloorTex, WallTex, StartTex, FinishTex,
     DoorTex, WindowTex : glUint;
     ElapsedTime : Integer;

procedure glBindTexture(target: GLenum; texture: GLuint); stdcall; external opengl32;

implementation

end.
