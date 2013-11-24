window.logic3=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CW(Ck);CX(21);CY(4);CY(5);if(!((BT("Oil Lamp")||BT("Carpet")))){A(501);break}
CY(65);CY(98);case 501:BY(153);if(AGI.C)return;BY(151);if(AGI.C)return;BJ(Ck);BF(153);if(AGI.C)return;m(o2);m(o3);p(o2,5);w(o2,0);p(o3,4);AY(o3);AY(o2);AG(o2,69,107);AG(o3,9,110);AC(o3,11);if(!(J(Cl,70))){A(502);break}
AG(Ego,73,110);case 502:if(!(E(f54))){A(503);break}
w(o3,3);A(1);break;case 503:w(o3,0);case 1:if(!(J(Cl,4)&&BO(Ego,152,125,159,140))){A(504);break}
AG(Ego,158,143);case 504:if(!(J(Cl,4)&&BO(Ego,152,80,159,98))){A(505);break}
AG(Ego,158,76);case 505:AJ(Ego);AJ(o3);AJ(o2);AN(o2);AN(o3);Az(o2);Az(o3);BM();case 500:AL(Ego,v105,v106);if(N(v105,12)){AZ(Ego);Ab(Ego);A(3);break}
if(BO(Ego,0,117,17,124)&&E(f54)){AZ(Ego);A(2);break}
AY(Ego);case 2:Aa(Ego);case 3:if(!E(DQ)){A(13);break}
if((D("check out","antique shop")||D("check out","area")||D("check out"))){Bg("The cozy cottage is located in a thick wood. A patio shades the front entrance and flowers adorn a window box.")}
if(D("check out","door")){Bg("The door of the little cottage is closed.")}
if(D("check out","box")){Bg("The mailbox has the words Grandma's House on it.")}
if(D("acquire","box")){Bg("The mailbox is firmly attached to the post.")}
if((D("check out","window")||D("look in","window"))){if(BO(Ego,30,90,65,111)){Bg("You can see inside when you look through the window. It is hard to see any detail, though.");A(4);break}
Bg("You are too far away.")}
case 4:if(!D("knock","door")){A(5);break}
BC(Ego,o2,v94);if(N(v94,20)){Bg("You are too far away.");A(5);break}
Bg("You knock loudly on the door and hear a muffled, \"Come in.\"");case 5:if((E(f148)||!J(v88,0))){A(6);break}
if(!D("open","door")){A(6);break}
BC(Ego,o2,v94);if(N(v94,20)){Bg("You are too far away.");A(6);break}
BA(o2);AQ(o2,f31);BN(21,f169);case 6:BC(Ego,o3,v94);if(N(v94,40)&&(D("open","box")||D("close","box")||D("look in","box"))){Bg("You are too far away.")}
if(!(D("look in","box"))){A(506);break}
if(!(E(f54))){A(507);break}
if(!(E(f57))){A(508);break}
Bg("The mailbox is empty.");A(7);break;case 508:Bg("There is a basket of goodies in the mailbox.");case 7:A(8);break;case 507:Bg("The mailbox is closed. You cannot look in it.");case 506:case 8:if(!(D("acquire","basket"))){A(509);break}
if(!(E(f54))){A(510);break}
if(!(E(f57))){A(511);break}
Bg("The mailbox is empty.");A(9);break;case 511:BS("Basket of Goodies");W(Cn,2);F(f57);F(f65);Bg("OK.");case 9:A(10);break;case 510:Bg("Where do you think it could be?");case 509:case 10:if(D("open","box")){if(E(f54)){Bg("The mailbox is already open.");A(11);break}
if(!E(f153)){W(Cn,1);F(f153)}
BA(o3);AQ(o3,f56)}
case 11:if(D("close","box")){if(E(f54)){G(f54);BA(o3);AR(o3,f58);A(12);break}
Bg("The mailbox is already closed.")}
case 12:if((D("break","window")||D("break","door"))){Bg("There is no need to do that. The door is unlocked.")}
if(D("check out","fence")){Bg("You see a low white fence.")}
if(D("anyword","fence")&&!D("enter","fence")&&!D("check out","fence")){Bg("You should do nothing with the fence.")}
if(D("anyword","flower box")){Bg("You see nothing special about the flower box.")}
case 13:if(E(f58)){G(f58);Az(o3)}
if(E(f56)){F(f54);G(f56);Az(o3);if(E(f57)){Bg("When you open the mailbox you see that it is empty.");A(14);break}
Bg("Lo and behold, when you open the mailbox you see a basket of goodies!")}
case 14:if(E(f31)){H(70);if(AGI.C)return}
if(J(Cm,1)){H(45);if(AGI.C)return}
if(J(Cm,2)){H(4);if(AGI.C)return}
if(J(Cm,4)){H(2);if(AGI.C)return}
if(J(Cm,3)){H(10);if(AGI.C)return}
BF(153);if(AGI.C)return;BF(151);if(AGI.C)return;return}}}
MESSAGES[3]=["","The cozy cottage is located in a thick wood. A patio shades the front entrance and flowers adorn a window box.","The door of the little cottage is closed.","The mailbox has the words Grandma's House on it.","You can see inside when you look through the window. It is hard to see any detail, though.","You knock loudly on the door and hear a muffled, \"Come in.\"","Lo and behold, when you open the mailbox you see a basket of goodies!","When you open the mailbox you see that it is empty.","The mailbox is empty.","The mailbox is already open.","The mailbox is already closed.","There is no need to do that. The door is unlocked.","You are too far away.","OK.","You should do nothing with the fence.","You see a low white fence.","The mailbox is firmly attached to the post.","Where do you think it could be?","You already have it.","The mailbox is closed. You cannot look in it.","The mailbox is empty.","There is a basket of goodies in the mailbox.","You see nothing special about the flower box."];CONTROLS[3]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4><.^m.!><.g5EArA.r><.lA!5.x><.l5ZV.!><.rV<9?4?4?4?4?4>.!h<.+>.4ylL<.r>Zs.gQ<.P4>V<Z.Q.,E5K5<ry<.P5.45.,E5K5.,s>4A{5.,E5K5.Py>^5+5.,E5K5ry>.l5^5.,E5Ks><PAx5.,4V><.45r5.,><.g5l5.,^}>.+AZ5.,^5{5>.{AP5.,^5,A>.{AE5.,+5.45>.,F.,+5.45><^.Q+5{A><+5P5Z5U5E+5+5>4G<^5P5Z5U5E{5xA<.^RKB<x5P5Z5U5E45+y<.rRxB<l5P5Z5U5E95>xW.96<gAK5Z5U5EE5>PR.lB<gA95Z5U5EK5<.{R.,6<lAZ5U5EPA<.gR<UB<lAP5U5EZ5<.9R<^B<lF95U5Eg5<xW<.K6<xAU5E4s<KR<.xB<xAK5Er.5!i<.!b<!A95Ex5{5!GEB<.Ub<.PAE!5+5^BPB<.K6<.^A^5^5{BP6<.E6<.{+Ax5.46PB<.46<.{,5r5.9BPB<{6<.{.45l5.KBPB<^6<.{.95g5.UBP6<!6<.{.E5Z5.g6PB<gG<.{.K5U5.lBPB.,W>9.P5P5.xBP6.rR>g.UAE5.^6PB.ER>^.g595.+BPBxW>.9.lA.,BPBKR>.g.ZW.,BER>.^.rA<EB><9.r595/P.r5E5>.lF<l.r5K5>.EQE5<l.r5PA>xVg5<l.gAg5>PQ+5<l.Z5x5<.{Q.E5<l.4V^5<.gV.g5<l.45U5gV<.9Q9.*<l^M=<.Pm>U>.EF>!?4?4?4?4?4?4?4?4?4?4><!<.Q<{F<.x5<.EA<{5E5<.r5<{LE<{5K5<.l5<xLZ<{5P5<.g5<ZLx<{5U5<.Z5<KF{<{5Z5<.U5.,L.9<{5g5<.P5.!L.U<{5l5<.K5.gL.r<{5r5<.E5.PF.+<{5x5<.95.4L<4<{*<.45^L<P<.x<.AlL<l<.!5<.UF<^<.^5<.4L<,<.+5<!L<.K<.{5<gF<.g<.,5<EL<.x>45.+L<.{>95.lL>E>E5.PF>Z>K5,L>r>P5xL>+>U5UL>.9>Z59F>.U>g5>.l?4?4?4?4?4?4?4?4?4?4";