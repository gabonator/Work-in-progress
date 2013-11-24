window.logic167=function()
{while(1){switch(B)
{case 0:if(E(DT)){if((!E(f105)||!BT("Gasping Fish"))){L(v58,0);G(f105)}
L(v59,0);L(v107,0);m(o4);p(o4,80);L(v94,2);AS(o4,v94);w(o4,0);return}
U(v58);if(J(v58,1)&&E(f105)){L(v58,200);U(v104);if(J(v104,0)){G(f105);if(E(f231)){AN(o4);p(o4,86);Bg("Oh, dear, the beautiful golden fish has died. What a pity.");A(1);break}
CL("Gasping Fish");Bg("Oh, dear, the beautiful fish has died. With a mighty heave, you throw the dead fish back into the sea. Slowly, it sinks to the bottom.")}}
case 1:if(J(v59,1)){AK(Ego);F(f50)}
U(v59);if(J(v107,2)){L(v107,3);L(v59,25);Bg("The water is too turbulent to swim in. You have just drowned.")}
if(J(v107,1)){if(BO(Ego,0,0,159,163)){L(v67,0);L(v68,5);Aw(Ego,v67,v68)}
F(f92);p(Ego,104);L(v94,2);AS(Ego,v94);Ag(Ego);L(v107,2)}
AL(Ego,v105,v106);if(E(DR)&&!N(v107,0)&&!E(f182)){if(E(f232)){G(f232);BC(Ego,o4,v94);if(P(v94,30)){Ad();AK(o4);L(v67,115);L(v68,108);Z(v67,v105);Z(v68,v106);Aw(Ego,v67,v68);p(Ego,82);L(v94,3);Ai(Ego,v94);L(v94,2);AS(Ego,v94);w(Ego,0);Ak(Ego,160,108,2,f169);W(Cn,1)}
A(2);break}
if(BT("Gasping Fish")){CL("Gasping Fish");Bg("Holding on tightly to the struggling fish, you jump into the turbulent water and disappear under the waves. Then...");A(18);break;A(2);break}
L(v107,1);if(J(Ck,85)&&BO(Ego,25,141,97,167)){AK(Ego);A(2);break}
AY(Ego);As(Ego)}
case 2:if(!E(DQ)&&!BL(c22)){A(19);break}
if(E(DQ)&&E(f182)){Bg("No time for that!");G(DQ)}
if(E(f231)){if(D("check out","dolphin")){if(E(f105)){Bg("The large fish is covered with shimmering golden scales. Its graceful fins and tail are almost translucent. Right now, the beautiful fish is writhing in agony.");A(3);break}
Bg("The large and formerly beautiful fish now lies motionless in the odd sunlight. You begin to notice a distinct and unforgettable aroma filling the air.")}}
case 3:if(D("check out","lake")){Bg("This is an ocean unlike any you've ever seen before. It has a rainbow quality, changing colors with the movement of the water. This sea is raging and frothing as if in a storm.")}
if(D("check out","sky")){Bg("The sky above this crazy world is a gorgeous pink. Where am I? you wonder.")}
if(D("check out","boulder")){Bg("The rocks are rather drab; unlike the bright blue sand on the beach.")}
if((D("check out")||D("check out","area")||D("check out","beach")||D("check out","grass"))){Bg("The sand on the sparkling beach is a deep blue. The bright sunlight, from a gorgeous pink sky, dances across it. Cliffs tower above the beach.");if(J(Ck,75)&&!E(f113)){Bg("There is a fishing net in a pile on the beach.")}}
if((D("check out","cliff")||D("climb","cliff"))){Bg("The blue cliffs towering above the beach are totally unclimbable.")}
if(D("acquire","lake")){Bg("You have no need to carry water.")}
if(!(!E(DS)&&(D("acquire","drink")||D("drink","lake")))){A(500);break}
if(!(!J(Ck,85))){A(501);break}
if(!(N(v105,89))){A(502);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(4);break;case 502:Bg("You need to be a little closer to drink the water.");case 4:A(5);break;case 501:if(!(N(v105,114)&&P(v106,60))){A(503);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(5);break;case 503:if(!(N(v105,89)&&N(v106,59)&&P(v106,147))){A(504);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(5);break;case 504:if(!(N(v106,146))){A(505);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(5);break;case 505:Bg("You need to be a little closer to drink the water.");case 500:case 5:if((D("enter","swim")||D("swim","anyword")||BL(c22))){Bg("The iridescent ocean is very turbulent. You cannot swim in it.")}
if(J(Ck,75)&&!E(f113)&&D("acquire","fishing net")){if(!BO(Ego,49,91,75,115)){Bg("You can't reach it from here.");A(6);break}
Bg("You reach down and retrieve the fishing net.");BS("Fishing Net");F(f113);W(Cn,1);AK(o2)}
case 6:if(!(BT("Fishing Net")&&(D("dolphin","anyword")||D("enter","fishing")||D("cast","fishing net")||D("capture","dolphin")||D("dolphin")))){A(506);break}
G(f233);if(!(!J(Ck,85))){A(507);break}
if(!(N(v105,89))){A(508);break}
F(f233);case 508:A(7);break;case 507:if(!(N(v105,114)&&P(v106,60))){A(509);break}
F(f233);A(7);break;case 509:if(!(N(v105,89)&&N(v106,59)&&P(v106,147))){A(510);break}
F(f233);A(7);break;case 510:if(!(N(v106,146))){A(511);break}
F(f233);case 511:case 7:if(!(!E(f233))){A(512);break}
Bg("You need to be closer to the sea to cast your net.");A(8);break;case 512:G(DS);case 506:case 8:if(BT("Fishing Net")&&E(f233)&&(D("dolphin","anyword")||D("enter","fishing")||D("cast","fishing net")||D("capture","dolphin")||D("dolphin"))){l(30,0,v94);if((N(v94,90)||E(f231)||BT("Gasping Fish")||E(f232))){Bg("You fish, and fish, and fish ... However, no matter how hard you try, you don't seem to be able to catch anything.");A(9);break}
Bg("You cast the fishing net into the wild sea. Upon retrieving it, you see you have caught a large golden fish! It falls from the net and flops helplessly on the beach.");AG(o4,45,108);F(f105);p(o4,80);L(v94,2);AS(o4,v94);AM(o4);AJ(o4);F(f231);L(v104,3);L(v58,200);if(!N(v97,0)){L(v97,1);W(Cn,2)}}
case 9:if(!(E(f231))){A(513);break}
BC(Ego,o4,v94);if(!(D("acquire","dolphin"))){A(514);break}
if(!(N(v94,30))){A(515);break}
Bg("You can't reach it from here.");A(10);break;case 515:G(f231);AK(o4);if(!(E(f105))){A(516);break}
Bg("You grab the flopping fish. Its mouth is wide open and its gills are extended. With difficulty, you hold the fish as it twists and turns in your hands.");BS("Gasping Fish");A(10);break;case 516:Bg("Holding your nose, you pick up the dead, stinking fish. Yucchhhh! With a mighty heave, you throw the fish back into the sea. Slowly, it sinks to the bottom.");case 10:A(11);break;case 514:if(!(E(f105)&&BT("Sword")&&D("kill","dolphin"))){A(517);break}
if(!(N(v94,30))){A(518);break}
Bg("You can't reach it from here.");A(11);break;case 518:G(f105);AN(o4);p(o4,86);Bg("You plunge your sword into the writhing fish, instantly killing it!");case 517:case 513:case 11:if((D("get on","dolphin")||D("climb","dolphin"))){if(BT("Gasping Fish")){Bg("You are carrying the fish. How could you ride it?");A(12);break}
if(E(f231)){Bg("The fish is flopping on the beach. How could you ride it?");A(12);break}
if(E(f232)){AK(o4);A(18);break;A(12);break}
Bg("What fish?")}
case 12:if((D("speak","dolphin")||D("hello","anyword")||D("say","hello"))){if((BT("Gasping Fish")||E(f231))){Bg("The gasping fish is unable to utter a sound.");A(13);break}
if(E(f232)){Bg("The golden fish calls out to you, Come! Come ride on my back! I can help you!");if(AGI.C)return;A(13);break}
G(DS)}
case 13:if(!E(DS)&&D("kill","dolphin")){if(BT("Gasping Fish")){Bg("You don't need to kill the golden fish. It will die shortly anyway.");A(14);break}
if(E(f232)){Bg("You could never catch the fish to kill it.");A(14);break}
G(DS)}
case 14:if(D("consume","dolphin")){if(BT("Gasping Fish")){Bg("This fish is not very edible. You wouldn't like it.");A(15);break}
Bg("You don't have the fish.")}
case 15:if(D("kiss","dolphin")){if(BT("Gasping Fish")){Bg("No, nothing happens. Great idea, though!");A(16);break}
if(!E(f105)&&E(f231)){Bg("Yucccchhhhh!! Who wants to kiss a dead fish!");A(16);break}
Bg("You don't have the fish.")}
case 16:if((D("aid","dolphin")||D("cast","back","dolphin")||D("cast","dolphin","back")||D("cast","dolphin","lake")||D("cast","dolphin","lake")||D("drop","dolphin","lake")||D("drop","dolphin","lake")||D("rescue","dolphin")||D("cast","dolphin"))){if(BT("Gasping Fish")){Bg("You throw the poor gasping fish back into the iridescent water. Gratefully, it calls to you, In return for saving my life, I wish to offer you a ride across this ocean.");if(AGI.C)return;L(v58,0);CL("Gasping Fish");AG(o4,115,108);p(o4,81);L(v94,3);AS(o4,v94);F(f232);AJ(o4);if(J(v97,1)){W(Cn,3);L(v97,2)}
A(17);break}
if(!E(f105)&&E(f231)){Bg("It is too late to save the golden fish. It is now dead.");A(17);break}
Bg("You don't have the fish.")}
case 17:A(19);break;case 18:Ad();G(f232);p(Ego,82);L(v94,3);Ai(Ego,v94);L(v94,2);AS(Ego,v94);w(Ego,0);L(v67,115);L(v68,108);Z(v67,v105);Z(v68,v106);Aw(Ego,v67,v68);Ak(Ego,160,108,2,f169);W(Cn,1);F(f94);case 19:if(N(Cm,0)&&!N(v107,0)){AZ(Ego);if(J(Cm,2)){M(v94,Ck);W(v94,1);BK(v94)}
if(J(Cm,1)){M(v94,Ck);Y(v94,5);BK(v94)}
if(J(Cm,3)&&!J(Ck,85)){M(v94,Ck);W(v94,5);BK(v94)}}
return}}}
MESSAGES[167]=["","This is an ocean unlike any you've ever seen before. It has a rainbow quality, changing colors with the movement of the water. This sea is raging and frothing as if in a storm.","The sand on the sparkling beach is a deep blue. The bright sunlight, from a gorgeous pink sky, dances across it. Cliffs tower above the beach.","There is a fishing net in a pile on the beach.","The blue cliffs towering above the beach are totally unclimbable.","The iridescent ocean is very turbulent. You cannot swim in it.","You reach down and retrieve the fishing net.","You cast the fishing net into the wild sea. Upon retrieving it, you see you have caught a large golden fish! It falls from the net and flops helplessly on the beach.","You grab the flopping fish. Its mouth is wide open and its gills are extended. With difficulty, you hold the fish as it twists and turns in your hands.","Oh, dear, the beautiful golden fish has died. What a pity.","What fish?","Holding on tightly to the struggling fish, you jump into the turbulent water and disappear under the waves. Then...","You are carrying the fish. How could you ride it?","The fish is flopping on the beach. How could you ride it?","Oh, dear, the beautiful fish has died. With a mighty heave, you throw the dead fish back into the sea. Slowly, it sinks to the bottom.","The gasping fish is unable to utter a sound.","The golden fish calls out to you, Come! Come ride on my back! I can help you!","The fish nods its head in acknowledgement.","You don't need to kill the golden fish. It will die shortly anyway.","You could never catch the fish to kill it.","This fish is not very edible. You wouldn't like it.","No, nothing happens. Great idea, though!","Yucccchhhhh!! Who wants to kiss a dead fish!","You throw the poor gasping fish back into the iridescent water. Gratefully, it calls to you, In return for saving my life, I wish to offer you a ride across this ocean.","Where do you want to throw the fish?","You plunge your sword into the writhing fish, instantly killing it!","It is too late to save the golden fish. It is now dead.","The water is too turbulent to swim in. You have just drowned.","You don't have the fish.","You can't reach it from here.","You fish, and fish, and fish ... However, no matter how hard you try, you don't seem to be able to catch anything.","Holding your nose, you pick up the dead, stinking fish. Yucchhhh! With a mighty heave, you throw the fish back into the sea. Slowly, it sinks to the bottom.","You need to be closer to the sea to cast your net.","The sky above this crazy world is a gorgeous pink. Where am I? you wonder.","YECCHHH!! You cough and choke from the briny water of the ocean.","You have no need to carry water.","You need to be a little closer to drink the water.","The rocks are rather drab; unlike the bright blue sand on the beach.","The large fish is covered with shimmering golden scales. Its graceful fins and tail are almost translucent. Right now, the beautiful fish is writhing in agony.","No time for that!","The large and formerly beautiful fish now lies motionless in the odd sunlight. You begin to notice a distinct and unforgettable aroma filling the air."];