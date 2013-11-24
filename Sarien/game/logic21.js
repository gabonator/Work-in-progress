window.logic21=function()
{while(1){switch(B)
{case 0:if(E(DT)){if((BT("Oil Lamp")||BT("Carpet"))){CY(65);CY(98)}
BY(160);if(AGI.C)return;BY(163);if(AGI.C)return;BY(151);if(AGI.C)return;CW(Ck);BF(160);if(AGI.C)return;BJ(Ck);if(J(Cl,20)){AL(Ego,v105,v106);if(N(v106,72)&&P(v106,120)){L(v106,72);AH(Ego,v105,v106)}}
if(J(Cl,14)){AL(Ego,v105,v106);if(N(v105,84)){L(v105,84);L(v106,37);AH(Ego,v105,v106)}}
if(J(Cl,28)){AL(Ego,v105,v106);if(N(v105,85)){L(v105,130);AH(Ego,v105,v106)}}
AJ(Ego);BM()}
if((D("check out","antique shop")||D("check out","area")||D("check out"))){Bg("You are looking at the back of a quaint little antique shop. It is yellow with a bright red roof. There are lovely curtains in the window.")}
if((D("check out","window")||D("look in","window"))){if(BO(Ego,9,119,27,146)){Bg("You can see inside when you look through the window. It is hard to tell details, though.");A(1);break}
Bg("You are too far away.")}
case 1:if(D("break","window")){Bg("You could get caught for breaking and entering. That would not be wise.")}
if(D("open","window")){Bg("The window does not open.")}
if(J(Cm,1)){H(14);if(AGI.C)return}
if(J(Cm,2)){H(15);if(AGI.C)return}
if(J(Cm,4)){H(20);if(AGI.C)return}
if(J(Cm,3)){H(28);if(AGI.C)return}
BF(160);if(AGI.C)return;BF(163);if(AGI.C)return;BF(151);if(AGI.C)return;return}}}
MESSAGES[21]=["","You are looking at the back of a quaint little antique shop. It is yellow with a bright red roof. There are lovely curtains in the window.","You can see inside when you look through the window. It is hard to tell details, though.","You could get caught for breaking and entering. That would not be wise.","You are too far away.","The window does not open."];CONTROLS[21]="?4?4?4?4?4?4?4?4?4?4?4><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><r5<.Z><l5<.g><ZA<.l><U5<.x><P5<.!><K5<.^><E5<.+><95<.{><45<.,>.,5>4><45<.,><95<.{><EA<.^><P5<.!><U5<.x><Z5<.r><g5<.l><l5<.g><rA<.U><!5<.P><^5<.K><+5<.E><+5<.E><+5<.E><{5<.9><{5<.9><{5<.9><{5<.9><,5<.4><,5<.4<.lQ<.E5<.4<.g5UA<.45<.4<.Z5l5<.45<,<.Z5lA<,5<,<.PAgA<.E5<{<.ZFEA<.U5<+<.rA<.l5<^><.K5<^><.P5<!><.U5<x><.Z5<r><.g5<l><.l5<g><.r5<Z><.x5<U4*><+5<U+5><+5<P+5><{5<K{5><{5<E{5><Uy<9,5>.ry<^.45>.PL<.g.45>.4L<.!.95>+A.ghU5P5K5.9.95>!A.r5Z5U5P5K5.9.E5>r5.!5Z5U5P5K5.9.K5>gA.!5Z5U5P5K5.9.K5>rA.r5Z5U5P5K5.9.P5>xA.g59AK5U5P5K5.9.P5>^A.KLE5E5U5P5K5.9.U5>+A^QgFU5P5K5.9.U5>,APV{5U5P5K5.9.Z5>.4L.U5P5P5K5.9.g5><r5K5P5K5.9.g5><x5E5P5K5.9.l5><x595P5K5.9.l5><!AP5K5.9.r5><!5P5K5.9.x5><x5P5K5.9.x5><!5K5K5.9.!5><x5K5K5.9.!5><!5E5K5.9.^5><x5E5K5.9.+5><x595K5.9.+5><x595K5.9.{5><xAK5.9.{5><xAK5.9.,5><x5K5.9<45><r5K5.9<45><x5E5.9<95><r5E5.9<95><x595.9<E5><r595.9<K5><lF.9<K5><UL.K<P5>.gVUAK5.K<P5>.EQ95E59Q95K5.K<PA>+LZ5E5g5K5.K<P595>xAx5E5g5K5.K<P595>lA^5E5g5K5.K<P5E5>Z5{5E5g5K5.K<P5E5>Z5{5Em.g<P5K5>PA<.9<P5K5>ZF<{<P5KA>lAU}.l<P5K595>rQ{5.l<P5K595>.+5.g<P5K5E5>.^5.g<P5K5E5>.+5.Z<P5K5K5>.^5.Z<P5K5KA>.!5.Z<P5K5KA>.^5.U<P5K5K595>.!5.U<P5K5K595>.!5.U<P5K5K5EQ>.g5.P<P5K5K5PA>.l5.P<KFE5K5EA>.!5.K.,LK595KF>.+5.K.l5KFlA9A><45.K.g59F^A><K5.E.Z5E5<.lQ<.Z5.E.U5<.!5UL<.E5.EghU5<.!5x5<.E5.94alQ<.xA^5<.95.9>+5,A<.45.4>^5.E5<,5.4>xA.P5<{5.4>r5.UF<+5.4>x5.9F<.45.4>!5.45<.95.9>^5{5<.E5.9>+5+5<.E5.9>{5!5<.K5.9>,aP5<.K5.9>.ZA95<.P5.9>.lA<.P5.9/{5.9/+5.E/+5.E/+5.E/+5.E/+5.E/+5.E/+5.E/+5.E/+5.E/+5.E/{5.9/{5.9/{5.9";