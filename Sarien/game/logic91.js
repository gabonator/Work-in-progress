window.logic91=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CY(88);CY(89);CY(90);CY(177);CY(188);CY(8);CY(87);CX(31);CX(21);CX(29);CW(Ck);BJ(Ck);m(o3);p(o3,87);L(v94,3);AS(o3,v94);AC(o3,5);AY(o3);AG(o3,80,120);w(o3,0);if(!(J(Cl,90))){A(501);break}
AR(o3,f169);r(Ego,2);AG(Ego,88,124);Ah(Ego);A(1);break;case 501:AN(o3);AG(Ego,64,164);r(Ego,3);Ah(Ego);case 1:AJ(o3);AJ(Ego);m(o2);if(!(J(v75,0))){A(502);break}
p(o2,88);L(v94,3);AS(o2,v94);F(f35);L(v30,16);A(2);break;case 502:if(!(J(v75,2))){A(503);break}
p(o2,188);L(v94,6);AS(o2,v94);A(2);break;case 503:if(!(J(v75,3))){A(504);break}
p(o2,89);A(2);break;case 504:p(o2,188);L(v94,6);AS(o2,v94);case 2:AG(o2,88,142);AJ(o2);Aa(o2);BM();case 500:if(E(f38)){G(f38);w(o2,0);if(!N(v75,0)){l(18,150,v31)}}
U(v31);if(J(v31,1)){AQ(o2,f38);L(v32,14)}
U(v32);if(J(v32,1)){BN(31,f37)}
AL(Ego,v105,v106);if(P(v106,124)){Ab(Ego);A(3);break}
Aa(Ego);case 3:U(v30);if(J(v30,1)){Bg("Be careful!!! There is a huge lion with dripping fangs at the top of the stairs. He has a hungry look in his eye!")}
if(E(f32)){Bg("CRUNCH! SNARL! CHOMP! Well, you made a nice meal for the hungry lion! SMACK! SLURP!");AN(Ego);G(f92);L(v75,5);F(f50)}
if(!(!E(f125))){A(505);break}
if(!(E(DR)&&P(v75,4))){A(506);break}
CC();M(v74,v105);L(v106,200);AY(Ego);Aa(Ego);AC(Ego,11);p(Ego,8);L(v94,2);AS(Ego,v94);L(v94,3);Ai(Ego,v94);F(f125);L(Cw,2);L(v108,5);Al(Ego,v105,v106,v108,f169);F(f92);BN(29,f36);A(4);break;case 506:if(!(J(v75,0)&&E(f35))){A(507);break}
G(f35);AQ(o2,f38);L(v32,13);case 507:case 4:A(5);break;case 505:A(16);break;case 5:if(J(v75,0)&&BO(Ego,82,122,115,137)){Ag(Ego);L(v75,4);p(Ego,90);L(v94,2);AS(Ego,v94);AL(Ego,v105,v106);L(v67,83);L(v68,142);Z(v67,v105);Z(v68,v106);Aw(Ego,v67,v68);F(f92);AQ(Ego,f32);AK(o2)}
if(E(f33)){G(f33);p(o2,188);L(v94,6);AS(o2,v94);AM(o2);L(v75,2)}
if((!E(DQ)||N(v75,3))){A(16);break}
if((D("cast","knife")||D("cast","knife","hungry lion"))){Bg("Swords don't fly very well. Think again.")}
if((D("check out")||D("check out","swim")||D("check out","antique shop"))){Bg("You are at the top of the wooden steps in the quartz tower. A door leads off to the north.");if(J(v75,0)){Bg("A hungry-looking lion guards the door.");A(6);break}
if(J(v75,2)){Bg("A lion is sleeping near the door.");A(6);break}
Bg("A dead lion is lying near the door.")}
case 6:if(D("check out","door")){Bg("The heavy door is closed.")}
if(D("check out","stairs")){Bg("The wooden steps spiral steeply downward.")}
if((D("acquire","hungry lion")||D("capture","hungry lion"))){if(!J(v75,3)){Bg("There is no way you could hold an enormous lion.");A(7);break}
Bg("The large lion has succumbed from the blow of your sword. He is dead.")}
case 7:if(!(J(v75,0))){A(508);break}
if(!((D("open","door")||D("knock","door")))){A(509);break}
Bg("You can't. A huge hungry lion blocks the door. You had better not get too close!");A(11);break;case 509:if(!(D("check out","hungry lion"))){A(510);break}
Bg("This is the BIGGEST lion you have ever seen! He could eat you with two bites of his powerful jaws. His tail thumps repeatedly on the floor.");A(11);break;case 510:if(!((D("speak","hungry lion")||D("hello","anyword")||D("say","hello")))){A(511);break}
Bg("The huge lion just snarls at you. You might be irritating him.");A(11);break;case 511:if(!((D("kill","hungry lion")||D("kill","hungry lion","knife")||D("stab","hungry lion")||D("stab","hungry lion","knife")))){A(512);break}
if(!(!BT("Sword"))){A(513);break}
Bg("You have nothing with which to kill a lion.");A(8);break;case 513:if(!(N(v105,75))){A(514);break}
CC();Bg("With one mighty heave of your sword, you fatally wound the large lion. He slumps to the floor.");p(o2,89);L(v75,3);W(Cn,2);CL("Sword");A(8);break;case 514:Bg("You must get closer to do that.");case 8:A(11);break;case 512:if(!((D("pat","hungry lion")||D("kiss","hungry lion")||D("embrace","hungry lion")))){A(515);break}
Bg("That would be a wrong move!");A(11);break;case 515:if(!((D("feed","ham")||D("feed","hungry lion","ham")||D("feed","hungry lion")||D("feed","ham","hungry lion")||D("give","ham")||D("give","ham","hungry lion")||D("give","hungry lion","ham")||D("cast","ham")||D("cast","ham","hungry lion")||D("cast","hungry lion","ham")))){A(516);break}
if(!(BT("Ham"))){A(517);break}
CC();W(Cn,4);CL("Ham");AN(o2);p(o2,177);L(v94,2);AS(o2,v94);AQ(o2,f33);L(v75,1);Bg("Hungrily, the lion gobbles down the smoked ham and then falls fast asleep.");A(9);break;case 517:Bg("You are not carrying it.");case 9:A(11);break;case 516:if(!((D("feed","broth")||D("feed","hungry lion","broth")||D("give","broth")||D("give","hungry lion","broth")||D("cast","broth")||D("cast","hungry lion","broth")))){A(518);break}
if(!(BT("Chicken Soup"))){A(519);break}
Bg("There is not enough sustenance in chicken soup to satisfy a hungry lion.");A(10);break;case 519:Bg("You are not carrying it.");case 10:A(11);break;case 518:if(!((D("feed","basket")||D("feed","hungry lion","basket")||D("give","basket")||D("give","hungry lion","basket")||D("cast","basket")||D("cast","hungry lion","basket")))){A(520);break}
if(!(BT("Basket of Goodies"))){A(521);break}
Bg("The lion sniffs the goodies in the basket but is not interested in them.");A(11);break;case 521:Bg("You are not carrying it.");case 520:case 11:A(13);break;case 508:if(!(D("open","door"))){A(522);break}
if(!(BO(Ego,78,119,98,130))){A(523);break}
BN(21,f36);AQ(o3,f31);A(12);break;case 523:Bg("You must get closer to do that.");case 12:A(13);break;case 522:if(D("knock","door")){if(BO(Ego,78,119,98,130)){Bg("A sweet voice from behind the heavy door begs, Help me, please help me!");A(13);break}
Bg("You must get closer to do that.")}
case 13:if(J(v75,3)&&!E(DS)&&(D("anyword","hungry lion")||D("anyword","anyword","hungry lion")||D("give","anyword")||D("feed","anyword")||D("cast","anyword"))){Bg("The large lion has succumbed from the blow of your sword. He is dead.");A(16);break}
if(!(J(v75,2))){A(524);break}
if(!((D("kill","hungry lion")||D("kill","hungry lion","knife")||D("stab","hungry lion")||D("stab","hungry lion","knife")))){A(525);break}
if(!(!BT("Sword"))){A(526);break}
Bg("You have nothing with which to kill a lion.");A(14);break;case 526:if(!(N(v105,75))){A(527);break}
Bg("With one mighty heave of your sword, you fatally wound the large lion. He slumps to the floor.");p(o2,89);L(v75,3);Y(Cn,3);CL("Sword");A(14);break;case 527:Bg("You must get closer to do that.");case 14:A(15);break;case 525:if(!((D("pat","hungry lion")||D("kiss","hungry lion")||D("wake","hungry lion")||D("embrace","hungry lion")))){A(528);break}
Bg("That would be a wrong move!");A(15);break;case 528:if(!(!E(DS)&&(D("anyword","hungry lion")||D("anyword","anyword","hungry lion")))){A(529);break}
Bg("The lion is sound asleep.");case 529:case 15:A(16);break;case 524:if(!E(DS)&&(D("give","anyword")||D("feed","anyword")||D("cast","anyword"))){Bg("The lion sniffs at it but does not appear interested.")}
case 16:AL(Ego,v105,v106);if(E(f31)){H(90);if(AGI.C)return}
if(J(Cm,3)){H(92);if(AGI.C)return}
return}}}
MESSAGES[91]=["","Be careful!!! There is a huge lion with dripping fangs at the top of the stairs. He has a hungry look in his eye!","You are at the top of the wooden steps in the quartz tower. A door leads off to the north.","The lion is sound asleep.","The heavy door is closed.","The wooden steps spiral steeply downward.","You can't. A huge hungry lion blocks the door. You had better not get too close!","This is the BIGGEST lion you have ever seen! He could eat you with two bites of his powerful jaws. His tail thumps repeatedly on the floor.","The huge lion just snarls at you. You might be irritating him.","There is no way you could hold an enormous lion.","You have nothing with which to kill a lion.","With one mighty heave of your sword, you fatally wound the large lion. He slumps to the floor.","The large lion has succumbed from the blow of your sword. He is dead.","That would be a wrong move!","CRUNCH! SNARL! CHOMP! Well, you made a nice meal for the hungry lion! SMACK! SLURP!","The lion sniffs at it but does not appear interested.","","Hungrily, the lion gobbles down the smoked ham and then falls fast asleep.","You are not carrying it.","There is not enough sustenance in chicken soup to satisfy a hungry lion.","The lion sniffs the goodies in the basket but is not interested in them.","A hungry-looking lion guards the door.","A lion is sleeping near the door.","A dead lion is lying near the door.","A sweet voice from behind the heavy door begs, Help me, please help me!","You must get closer to do that.","Swords don't fly very well. Think again."];CONTROLS[91]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4>.rB>U>.gBEB>K>.UBZB>9>.KBxG<.{>.9B,B<.^>.46.KB<.x>.9B.96<.!>.K6,6<.^>.P6{6<.^>.P6+6<.+>.P6+6<.+>.P6+6K6K6<.U>.P6+6K6K6K6<.9>.P6+6K6K6K6<.9>.P6+6K6K6K6<.9>.P6+6K6K6K6<.9>.P6+6K6K6K6<.9>.P6+6K6K6K6<.9>.P6+6K6K6K6<.9>.P6+6KRK6<.9>.P6+69MK6E6<.9>^RK6+BlG<.9>PiPR.r6<.9<.^i<!6<.4<.Pi<.P6<,<.4M<.^6<,<,6>96<{<{6>E6<{<{6>K6<+<+6>P6<+<+6>U6<^<^6>Z6<^<^6.!c.4.R<^<^6.!7Z7{6.U6<!<!6.^7g7^6.Z6<!<!6.^7l7rB.l6<x<!6.^7r7g6.x6<x<!6.+7l7Z6.^6<r<x6.{7r7P6.+6<r<x6.{7r7K<1<r<x6.{7r7P7>g<x6.{7r7P7>g<x6.{7r7K7>l<x6.{7r7K7>l<x6.,7rH>r<x6.,7!7>r<x6.,7>.U<x6.,7>.U<x6<47>.P<x6<47>.P<!6.,7>.P<!6<47>.K<!6<97>.E<!6<97>.E<^6<97>.9<^6<E7>.4<+6<E7>,<+6<K7>{<{6<E7>{<,6<E7>+<.46<E7>^<.96<97>^<.E6<97>!<.K6<9C>r<.P6<EC>g<.UB<E7>Z<.g6<EC>P<.l6<K7>K";