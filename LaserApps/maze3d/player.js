class Player
{
  constructor()
  {
    this.frame = 0;
  }

  play(keys)
  {
    if (this.frame < 170)
    {
      keys.up = false;
      keys.down = false;
      keys.left = false;
      keys.right = false;

      if (this.frame < 135)
        keys.up = true;
      if (this.frame > 45 && this.frame < 60)
        keys.right = true;
      if (this.frame > 90 && this.frame < 95)
        keys.left = true;
      if (this.frame > 100 && this.frame < 112)
        keys.left = true;
      if (this.frame > 130 && this.frame < 168)
        keys.left = true;
    }
    
    this.frame ++;
  }
}

var player = new Player();