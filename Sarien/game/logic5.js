window.logic5=function()
{while(1){switch(B)
{case 0:if(E(DT)){CW(Ck);CX(30);CY(119);if((BT("Oil Lamp")||BT("Carpet"))){CY(65);CY(98)}
BY(151);if(AGI.C)return;BY(154);if(AGI.C)return;BF(154);if(AGI.C)return;BJ(Ck);m(o3);p(o3,119);AG(o3,94,62);AC(o3,14);L(v94,4);AS(o3,v94);AJ(o3);if(J(Cl,4)){AL(Ego,v105,v106);if(N(v106,130)&&P(v106,155)){L(v106,155);AH(Ego,v105,v106)}}
Aa(Ego);AJ(Ego);BM()}
z(o3,v30);if(J(v30,8)){if(!E(f177)){BN(30,f32)}}
if(!E(DQ)){A(2);break}
if(D("anyword","door")&&!D("enter","door")){Bg("There is no door around here.")}
if((D("check out","antique shop")||D("check out"))){Bg("This is an old monastery. The monks living here often help travelers in need.")}
if((D("check out","window")||D("look in","window"))){if((BO(Ego,65,140,80,160)||BO(Ego,97,140,112,160)||BO(Ego,130,140,152,160))){Bg("You can see inside when you look in the window. It is hard to see details, though.");A(1);break}
Bg("You are too far away to see in the window.")}
case 1:if(D("break","window")){Bg("There is no need to do that. The door is unlocked.")}
if(D("check out","bell")){Bg("The bell atop the monastery is ringing merrily.")}
if(D("acquire","bell")){Bg("You cannot take the bell.")}
case 2:if(J(Cm,1)){H(47);if(AGI.C)return}
if(J(Cm,2)){H(6);if(AGI.C)return}
if(J(Cm,4)){H(4);if(AGI.C)return}
if(J(Cm,3)){H(12);if(AGI.C)return}
BF(151);if(AGI.C)return;BF(154);if(AGI.C)return;return}}}
MESSAGES[5]=["","There is no door around here.","This is an old monastery. The monks living here often help travelers in need.","You can see inside when you look in the window. It is hard to see details, though.","There is no need to do that. The door is unlocked.","You are too far away to see in the window.","The bell atop the monastery is ringing merrily.","You cannot take the bell."];CONTROLS[5]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4>U>.y>U5>.x>U5>.x>P5>.!>P5>.!>P5>.!>P5>.!>K5>.^>K5>.^>K5>.^>K5>.^>E5>.+>E5>.+>E5>.+>E5>.+>95>.{>95>.{>95>.{>95>.{>45>.,>45>.,>45>.,>45>.,<.,5><4<.,5><4<.,5><4<.,5><4<.{5><9<.{5><9<.{5><9<.{5><9<.+5><E<.xL><E<.PVEA><E<{VlA><E<xL+A><K<r5.9A><K<l5.EA><K<l5.EA><K<UF.K5><P<EF.UA><P<EA.ZA><P<PLg*><P<lAU5x5><U<x5K5!5><U<!5E5!5><U<^A^5><U<+5!5><Z<.r5><Z<.r5><Z<.r5><Z<.l5><g<.l5><g<.l5><g<.l5><g<.g5><l<.g5><l<.g5><l<.g5><l<.Z5><r.Pm.r5><r+arF.Z5><rrL95.45.Z5><rZFE5E5.95.P5><xPAE5E5E5.95.P5><x9F95E5E5E5+V.K5><x9AE5E5E5E5^5.r5><xK595E5E5E5^5.l5><!PAE5E5E5!5.r><@UA95E5E5lF/ZgAE5E5PL/rl5E59V/+rL/.K?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4";