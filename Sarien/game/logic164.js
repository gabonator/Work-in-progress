window.logic164=function()
{while(1){switch(B)
{case 0:if(E(DT)){G(f120);return}
if((D("check out","cliff")||D("check out","area")||D("check out")||D("check out","cliff"))){if(J(Ck,55)){Bg("There are steep cliffs on three sides of this mountain top. Don't get too near the edge!");A(1);break}
Bg("You are walking on a narrow mountain top with steep cliffs on two sides.")}
case 1:if(D("check out","tree")){Bg("There are a few pine and fir trees on this mountain top.")}
if(D("check out","blossom")){Bg("There are not many flowers around here.")}
if(D("acquire","blossom")){Bg("The flowers are of no interest.")}
if(D("climb","tree")){Bg("It would be fun to stop and climb trees for a while, but don't you have something better to do?")}
if(D("climb","boulder")){Bg("Don't be silly. Climbing on rocks is kid stuff.")}
if((D("climb","cliff")||D("climb","cliff")||D("climb")||D("look down","anyword"))){Bg("The cliffs are too steep! Climbing them could mean death.")}
if(E(DR)&&!E(f125)){G(DR);F(f180);F(f125);AY(Ego);p(Ego,8);L(v94,2);AS(Ego,v94);L(v94,3);Ai(Ego,v94);AF(Ego,v94);AL(Ego,v105,v106);if(P(v106,90)){U(v94)}
AD(Ego,v94);AL(Ego,v94,v70);L(v70,167);L(v108,3);Al(Ego,v94,v70,v108,f120);L(v69,30);BN(29,f169)}
U(v69);if((J(v69,1)||E(f120))){G(f120);AK(Ego);F(f50);Bg("It seems you have fallen to your death from this high mountain top.")}
return}}}
MESSAGES[164]=["","There are steep cliffs on three sides of this mountain top. Don't get too near the edge!","There are a few pine and fir trees on this mountain top.","There are not many flowers around here.","The flowers are of no interest.","It would be fun to stop and climb trees for a while, but don't you have something better to do?","Don't be silly. Climbing on rocks is kid stuff.","","The cliffs are too steep! Climbing them could mean death.","You are walking on a narrow mountain top with steep cliffs on two sides.","It seems you have fallen to your death from this high mountain top."];