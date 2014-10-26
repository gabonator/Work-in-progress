unit GlDrawing;
{ unit na vykreslovanie objektov s OpenGl funkciami }

interface
uses Common, OpenGl;

{ vykreslenie blokov mapy }
procedure drawBox(x, y, z : glFloat);
procedure drawGround(x, y, z : glFloat);
procedure drawStart(x, y : glFloat);
procedure drawFinish(x, y : glFloat);
procedure drawDoorX(x, y : glFloat);
procedure drawDoorY(x, y : glFloat);
procedure drawWindowX(x, y : glFloat);
{ DrawLine - nakresli vodorovnu alebo zvislu ruru }
Procedure DrawLine(x1, y1, x2, y2 : glFloat);


implementation

procedure drawBox(x, y, z : glFloat);
begin
    x := -(x - gMapWidth/2);
    y := y - gMapHeight/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, WallTex);  // Bind the Texture to the object
    glBegin(GL_QUADS);
      // vrch
      glNormal3f( 0.0, 0.0, 1.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x + -0.5, y + -0.5, z+1);
      glTexCoord2f(1.0, 0.0); glVertex3f(x + 0.5, y +-0.5, z+ 1);
      glTexCoord2f(1.0, 1.0); glVertex3f(x + 0.5, y + 0.5, z+ 1);
      glTexCoord2f(0.0, 1.0); glVertex3f(x +-0.5, y + 0.5, z+ 1);
       // spodok
      glNormal3f( 0.0, 0.0,-1.0);
      glTexCoord2f(1.0, 0.0); glVertex3f(x +-0.5, y +-0.5, z+0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x +-0.5, y + 0.5, z+0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x + 0.5, y + 0.5, z+0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x + 0.5, y +-0.5, z+0);
      // A
      glNormal3f( 0.0, 1.0, 0.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x +-0.5, y + 0.5, z+0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x +-0.5, y + 0.5, z+ 1);
      glTexCoord2f(1.0, 0.0); glVertex3f(x + 0.5, y + 0.5, z+ 1);
      glTexCoord2f(1.0, 1.0); glVertex3f(x + 0.5, y + 0.5, z+0);
      // B
      glNormal3f( 0.0,-1.0, 0.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x +-0.5, y +-0.5, z+0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x + 0.5, y +-0.5, z+0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x + 0.5, y +-0.5, z+1);
      glTexCoord2f(1.0, 0.0); glVertex3f(x +-0.5, y +-0.5, z+1);
      // C
      glNormal3f( 1.0, 0.0, 0.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x + 0.5, y +-0.5, z+0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x + 0.5, y + 0.5, z+0);
      glTexCoord2f(1.0, 0.0); glVertex3f(x + 0.5, y + 0.5, z+1);
      glTexCoord2f(0.0, 0.0); glVertex3f(x + 0.5, y +-0.5, z+1);
      // D
      glNormal3f(-1.0, 0.0, 0.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x +-0.5, y +-0.5, z+0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x +-0.5, y +-0.5, z+1);
      glTexCoord2f(1.0, 1.0); glVertex3f(x +-0.5, y + 0.5, z+1);
      glTexCoord2f(1.0, 0.0); glVertex3f(x +-0.5, y + 0.5, z+0);
    glEnd();
end;

procedure drawGround(x, y, z : glFloat);
begin
    x := -(x - gMapWidth/2);
    y := y - gMapHeight/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, FloorTex);  // Bind the Texture to the object
    glBegin(GL_QUADS);
      glNormal3f( 0.0, 0.0, 1.0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x+-0.5, y+-0.5, z);
      glTexCoord2f(1.0, 0.0); glVertex3f(x+ 0.5, y+-0.5, z);
      glTexCoord2f(1.0, 1.0); glVertex3f(x+ 0.5, y+ 0.5, z);
      glTexCoord2f(0.0, 1.0); glVertex3f(x+-0.5, y+ 0.5, z);
    glEnd();
end;

procedure drawStart(x, y : glFloat);
begin
    x := -(x - gMapWidth/2);
    y := y - gMapHeight/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, StartTex);  // Bind the Texture to the object
    glBegin(GL_QUADS);
      glNormal3f( 0.0, 0.0, 1.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x+-0.5, y+-0.5, 0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x+ 0.5, y+-0.5, 0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x+ 0.5, y+ 0.5, 0);
      glTexCoord2f(1.0, 0.0); glVertex3f(x+-0.5, y+ 0.5, 0);
    glEnd();
end;

procedure drawFinish(x, y : glFloat);
begin
    x := -(x - gMapWidth/2);
    y := y - gMapHeight/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, FinishTex);  // Bind the Texture to the object
    glBegin(GL_QUADS);
      glNormal3f( 0.0, 0.0, 1.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x+-0.5, y+-0.5, 0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x+ 0.5, y+-0.5, 0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x+ 0.5, y+ 0.5, 0);
      glTexCoord2f(1.0, 0.0); glVertex3f(x+-0.5, y+ 0.5, 0);
    glEnd();
end;

procedure drawDoorY(x, y : glFloat);
begin
    x := -(x - gMapWidth/2);
    y := y - gMapHeight/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, DoorTex);  // Bind the Texture to the object
    glBegin(GL_QUADS);
      glNormal3f( 0.0, 1.0, 0.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x-0.5, y, 0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x+0.5, y, 0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x+0.5, y, 1);
      glTexCoord2f(1.0, 0.0); glVertex3f(x-0.5, y, 1);
    glEnd();
end;

procedure drawDoorX(x, y : glFloat);
begin
    x := -(x - gMapWidth/2);
    y := y - gMapHeight/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, DoorTex);  // Bind the Texture to the object
    glBegin(GL_QUADS);
      glNormal3f( 1.0, 0.0, 0.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x, y-0.5, 0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x, y+0.5, 0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x, y+0.5, 1);
      glTexCoord2f(1.0, 0.0); glVertex3f(x, y-0.5, 1);
    glEnd();
end;


procedure drawWindowX(x, y : glFloat);
begin
    x := -(x - gMapWidth/2);
    y := y - gMapHeight/2;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, WindowTex);  // Bind the Texture to the object
    glBegin(GL_QUADS);
      glNormal3f( 1.0, 0.0, 0.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(x+0.5, y-0.5, 0);
      glTexCoord2f(0.0, 1.0); glVertex3f(x+0.5, y+0.5, 0);
      glTexCoord2f(0.0, 0.0); glVertex3f(x+0.5, y+0.5, 1);
      glTexCoord2f(1.0, 0.0); glVertex3f(x+0.5, y-0.5, 1);
    glEnd();
end;

Procedure DrawLine(x1, y1, x2, y2 : glFloat);
const z : glFloat = 0.1;
      r : glFloat = 0.1;
var      nx, ny, len : glFloat;
      i : integer;
begin
  x1 := -(x1 - gMapWidth/2);
  y1 := y1 - gMapHeight/2;
  x2 := -(x2 - gMapWidth/2);
  y2 := y2 - gMapHeight/2;
  glDisable(GL_TEXTURE_2D);
  if y1 = y2 then
  begin
    glBegin(GL_QUADS);
    for i := 1 to 20 do
    begin
      glNormal3f( -sin(i/20*2*Pi)*r, 0, cos(i/20*2*Pi)*r);
      glColor3f(1, 0, 0); glVertex3f(x1, y1 + cos(i/20*2*Pi)*r, z + sin(i/20*2*Pi)*r);
      glColor3f(1, 0, 0); glVertex3f(x2, y2 + cos(i/20*2*Pi)*r, z + sin(i/20*2*Pi)*r);
      glColor3f(1, 0, 0); glVertex3f(x2, y2 + cos((i+1)/20*2*Pi)*r, z + sin((i+1)/20*2*Pi)*r);
      glColor3f(1, 0, 0); glVertex3f(x1, y1 + cos((i+1)/20*2*Pi)*r, z + sin((i+1)/20*2*Pi)*r);
    end;
    glEnd();
  end;

  if x1 = x2 then
  begin
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for i := 1 to 20 do
    begin
      glNormal3f( 0, -sin(i/20*2*Pi)*r, cos(i/20*2*Pi)*r);
      glVertex3f(x1 + cos(i/20*2*Pi)*r, y1, z + sin(i/20*2*Pi)*r);
      glVertex3f(x2 + cos(i/20*2*Pi)*r, y2 , z + sin(i/20*2*Pi)*r);
      glVertex3f(x2 + cos((i+1)/20*2*Pi)*r, y2, z + sin((i+1)/20*2*Pi)*r);
      glVertex3f(x1 + cos((i+1)/20*2*Pi)*r, y1, z + sin((i+1)/20*2*Pi)*r);
    end;
    glEnd();
  end;
end;

end.
