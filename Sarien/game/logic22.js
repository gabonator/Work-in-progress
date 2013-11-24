window.logic22=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CW(Ck);CX(25);BY(152);if(AGI.C)return;BY(101);if(AGI.C)return;CY(62);CY(97);CY(104);CY(20);CY(21);if(!((BT("Oil Lamp")||BT("Carpet")))){A(501);break}
CY(65);CY(98);case 501:BJ(Ck);AG(o7,10,70);BF(152);if(AGI.C)return;BF(101);if(AGI.C)return;m(o3);m(o4);p(o3,20);p(o4,21);AG(o3,100,100);AG(o4,100,100);AY(o7);if(!(J(Cl,15))){A(502);break}
AL(Ego,v105,v106);if(!(N(v105,81))){A(503);break}
Y(v105,80);A(1);break;case 503:if(!(N(v105,60))){A(504);break}
Y(v105,59);A(1);break;case 504:if(!(N(v105,40))){A(505);break}
Y(v105,35);A(1);break;case 505:L(v105,5);case 1:L(v106,37);AH(Ego,v105,v106);case 502:if(!(J(Cl,29))){A(506);break}
AL(Ego,v105,v106);if(!(P(v105,120))){A(507);break}
if(!(N(v105,3))){A(508);break}
Y(v105,4);A(2);break;case 508:L(v105,0);case 507:case 2:AH(Ego,v105,v106);case 506:if(!(!E(f72))){A(509);break}
AJ(o3);case 509:if(!(E(f72)&&!E(f73))){A(510);break}
AJ(o4);case 510:AJ(Ego);BM();case 500:if(BO(Ego,0,0,80,167)){Aa(Ego);A(3);break}
Ab(Ego);case 3:if((D("check out","beach")||D("check out","grass")||D("check out","area")||D("check out"))){if(E(f73)){Bg("It is a beautiful sandy beach.");A(4);break}
if(E(f72)){Bg("There is a beautiful diamond and sapphire bracelet lying in the sand!");A(4);break}
Bg("You notice a pretty clamshell lying on the sandy beach.")}
case 4:if(!E(f72)&&D("check out","clam")){Bg("You notice a pretty clamshell lying on the sandy beach.")}
if(D("open","clam")){if(E(f72)){Bg("You open the clamshell and discover that it is empty. There is nothing special about it.");A(5);break}
Bg("You need to get the clam first.")}
case 5:if(!E(f72)&&D("acquire","clam")){BC(Ego,o3,v94);if(N(v94,15)){Bg("You can't reach it from here.");A(6);break}
Bg("When you pick up the clamshell, you see that there was a sparkling sapphire and diamond bracelet under it!");BS("Clamshell");AK(o3);AJ(o4);F(f72)}
case 6:if(E(f72)&&!E(f73)&&D("acquire","bracelet")){BC(Ego,o4,v94);if(N(v94,15)){Bg("You can't reach it from here.");A(7);break}
Bg("OK.");F(f73);BS("Bracelet");W(Cn,7);AK(o4)}
case 7:if(J(Cm,1)){H(15);if(AGI.C)return}
if(J(Cm,2)){H(23);if(AGI.C)return}
if(J(Cm,4)){H(50);if(AGI.C)return}
if(J(Cm,3)){H(29);if(AGI.C)return}
BF(152);if(AGI.C)return;BF(101);if(AGI.C)return;return}}}
MESSAGES[22]=["","You notice a pretty clamshell lying on the sandy beach.","It is a beautiful sandy beach.","When you pick up the clamshell, you see that there was a sparkling sapphire and diamond bracelet under it!","You can't reach it from here.","You open the clamshell and discover that it is empty. There is nothing special about it.","You need to get the clam first.","There is a beautiful diamond and sapphire bracelet lying in the sand!","OK."];CONTROLS[22]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?44<.3><.44<%><.P4<~><.U4<~><.U4<~><.U4<~><.U4<~><.U4<~><.U4<~><.U4<~><.U4<%><.P4<-><.K4<]><.E4<.3><.44<.D><{4<.D><{4<.D><{4<.D><{4<.8><,4<.3><.44<;><.94<]<4(>U4<].!R^6>U4<-.rG.96>U4<-.x6.K6>P4<].r6.EB>P4<].x6{G>Z4<;.r6!G>r4<.3.r6x6>!4<.8.l6x6>!4<.D.l6r6>!4<.O.Z6r6>!4<.T.Z6l6>!4<.Y.U6l6>!4<.Y.Z6g6>!4.TM.].U6Z6>^4.T6D6.].Z6EM>^4.T6D6.-.gG>.44.T6D6.-><x4.T6D6.-><x4.T6D6.%><!4.TM.%><!4<.O><^4<.O><^4<.J><+4<.D><{4<.3><.44<;><.94<]><.E4<]><.E4<-><.K4<-><.K4<%><.P4<%><.P4<~><.U4<~><.U4<w><.Z4<w><.Z4<w><.Z4<q><.g4<q><.g4<q><.g4<w><.Z4<w><.Z4<~><.U4<%><.P4<]><.E4<.3><.44<.8><,4<.D>gW<94<.D>UBZ6<44<.J>K6r6.,4<.O>96!6.{4<.O>96^W.l4<.T>96.96.g4<.T>96.96.g4<.T>E6.96.Z4<.T>KG{6.Z4<.Y>P6{6.Z4<.Y>P6{6.Z4<.Y>P6{6.Z4<.T>U6{6.Z4<.T>U6{6.Z4<.O>ZB^6.g4<.O>lBlB.l4<.O>xi.x4<.J><+4<.J><+4<.D><{4<.D><{4<.8><,4<.8><,4<.8><,4<.3><.44<.3><.44<;><.94<;><.94<]><.E4<]><.E4<]><.E4<]><.E4<-><.K4<-><.K4<-><.K4<-><.K4<]><.E4<]><.E4<;><.94<.3><.44<.3><.44<.8><,4<.D><{4<.J><+4<.O><^4<.T><!4<.T><!4<.Y><x4<.d><r4<.k><l4<.k><l4<.q><g4<.q><g4<.w><Z4<.w><Z4<.~><U4<.~><U4<.~><U4<.w><Z4<.w><Z4<.w><Z4<.q><g4<.q><g4<.k><l";