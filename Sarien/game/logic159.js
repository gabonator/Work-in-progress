window.logic159=function()
{while(1){switch(B)
{case 0:if(E(f249)){G(f249);Bg("You have been poisoned by the thorns and can no longer continue the game.");F(f50);return}
if(D("check out","brambles")){Bg("The brambles are covered with poisoned spiked thorns that mean instant death to anyone punctured by one.")}
if((D("acquire","brambles")||D("acquire","brambles"))){Bg("You would be crazy to touch the thorns.")}
if(D("cut","brambles")&&BT("Sword")){Bg("The brambles are too thick for the sword to cut through.")}
if(D("cut","brambles")&&!BT("Sword")){Bg("You would be crazy to touch the thorns.")}
if(!E(DR)){A(1);break}
if(J(v54,0)&&J(v66,0)){p(Ego,91);L(v67,0);L(v68,6);Aw(Ego,v67,v68);Ap(Ego);Ag(Ego);F(f249)}
case 1:return}}}
MESSAGES[159]=["","The brambles are covered with poisoned spiked thorns that mean instant death to anyone punctured by one.","You would be crazy to touch the thorns.","The brambles are too thick for the sword to cut through.","You have been poisoned by the thorns and can no longer continue the game."];