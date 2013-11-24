window.logic6=function()
{while(1){switch(B)
{case 0:if(E(DT)){CW(Ck);CX(21);CY(7);if((BT("Oil Lamp")||BT("Carpet"))){CY(65);CY(98)}
BY(151);if(AGI.C)return;BY(154);if(AGI.C)return;BF(154);if(AGI.C)return;BJ(Ck);m(o3);p(o3,7);w(o3,0);AY(o3);AG(o3,64,146);AC(o3,13);AJ(o3);Az(o3);if(J(Cl,48)){AL(Ego,v105,v106);if(N(v106,12)&&P(v106,25)){L(v106,25);AH(Ego,v105,v106)}}
if(J(Cl,71)){AG(Ego,70,150)}
AJ(Ego);BM()}
if((D("check out","antique shop")||D("check out"))){Bg("This is an old monastery. The monks living here often help travelers in need.")}
if((D("check out","window")||D("look in","window"))){if(BO(Ego,2,140,22,160)){Bg("You can see inside when you look in the window. It is hard to see details, though.");A(1);break}
Bg("You are too far away to see in the window.")}
case 1:if(D("break","window")){Bg("There is no need to do that. The door is unlocked.")}
if(D("check out","door")){Bg("The monastery door is made of very thick wood held together by iron bars.")}
if((E(f148)||!J(v88,0)||!D("open","door"))){A(2);break}
BC(Ego,o3,v94);if(N(v94,20)){Bg("Your arms are too short to reach the door from here!");A(2);break}
BA(o3);BN(21,f169);AQ(o3,f61);case 2:if(E(f61)){G(f61);H(71);if(AGI.C)return}
if(!D("knock","door")){A(3);break}
BC(Ego,o3,v94);if(N(v94,20)){Bg("Your arms are too short to reach the door from here!");A(3);break}
Bg("It is not necessary to knock at a church door. All are welcome.");case 3:if(J(Cm,1)){H(48);if(AGI.C)return}
if(J(Cm,2)){H(7);if(AGI.C)return}
if(J(Cm,4)){H(5);if(AGI.C)return}
if(J(Cm,3)){H(13);if(AGI.C)return}
BF(151);if(AGI.C)return;BF(154);if(AGI.C)return;return}}}
MESSAGES[6]=["","There are not many flowers around here.","This is an old monastery. The monks living here often help travelers in need.","You can see inside when you look in the window. It is hard to see details, though.","Have you nothing better to do than pick flowers?","There is no need to do that. The door is unlocked.","The monastery door is made of very thick wood held together by iron bars.","It is not necessary to knock at a church door. All are welcome.","Your arms are too short to reach the door from here!","You are too far away to see in the window."];CONTROLS[6]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4<E5><.+<E5><.+.g5x5><.+.g5x5><.+.g5KQE5><.+.g5K5K5E5><.+.gAE5K5E5><.+.gAE5K5E5><.+.gAE5K5E5><.+.gAE5K5E5><.+.gAE5K5E5><.+.gAE5K5E5><.+.gAE5K5E5><.+.gAE5K5E5><.+.gQKL><.+.la/9?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4456>.5>+96ERK6>Z5>^96E6K6K6>Z5>^96E6K6K6>g5>!96E6K6K6>g5>!96E6K6K6>l5>x96E6K6K6>l5>x96E6K6K6>r5>r96E6K6K6>x5>l96E6K6K6>x5>l96E6K6K6>!5>g96E6K6K6>!5>g96E6K6K6>^5>Z9MK6K6>+5>UlR>+5>U>.!5>P>.!5>P>.^5>K>.^5>K>.+5>E>.{5>9>.{5>9>.,5>4>.,5>4><45<.,><95<.{><95<.{><E5<.+><E5<.+><K5<.^><K5<.^<.r=.+.0<^<.r5+=.{5<^<.r5.x5.{5<^<.r5.x5.{5<^<.r5.x5.{5<^<.r5.x5.{5<^<.r5.x5.{5<^<.r5.x5.{5<^<.r5.x5.{5<^<.r5.x5.{5<^<.l5.!5.{5<^<.l5.!5.{5<^<.l5.!5.{5<^<.l5.!5.^F<^<.l5.!5.lL<,<.l5.!5.ZA<.K<.l5.!5.Z5<.P<.l5.!5.g5<.K<.l5.!5.g5<.K<.l5.!5.g5<.K<.l5.!5.l5<.E<.l5.^5.g5<.E<.l5.^5.g5<.E<.l5.^5.g5<.E<.l5.^5.l5<.9<.l5.^5.l5<.9<.l5.^5.l5<.99MEM<+5.^5.r5<.496E6E6E6<+5.^5.r5<.496E6E6E6<+5.^5.r5<.496E6E6E6<^5.+5.x5<,96E6E6E6<^5.+5.xV<x96E6E6E6<^5.+5<4Q<U96E6E6E6<^5.+5<U5<P96E6E6E6<^5.+5<ZA<E96E6E6E6<^5.+5<l5<996E6E6E6<^5.+5<r5<496E6E6E6<^5.+5<x5.,96E6E6E6<^5.+5<!A.+96E6E6E6<^R.r5<+5G.r96E6E6E6<.9R+i<{596.r96E6E6E6<.U6+6<.U596.r96E6E6E6<.U6+6<.Z56.r96E6E6E6<.P69(96<.U56.r96EME6<.K6.96<.U5.r4<.mR.Kn<*.r<.!6.g6>^?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4";