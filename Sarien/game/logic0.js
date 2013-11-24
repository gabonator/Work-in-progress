window.logic0=function()
{while(1){switch(B)
{case 0:if(E(DU)){F(Dc);CP(c31);if(J(DN,2)&&J(DG,0)){A(1);break}
BH(22,24,0)}
case 1:if((E(Da)||E(DU))){CP(c31)}
if(N(DD,0)){BF(98);if(AGI.C)return;CK(1)}
M(v102,v100);M(v103,v101);AL(Ego,v100,v101);if(E(f50)){G(f50);F(f170);CP(c18);CP(c16);CP(c2);CP(c30);CP(c22);CP(c10);CP(c11);CP(c28);CP(c27);CP(c6);CP(c29);BY(100);if(AGI.C)return}
if(J(Ck,0)){BF(180);if(AGI.C)return;L(DC,0);CB(60);if(E(DU)){F(Dc);CP(c31);H(1);if(AGI.C)return;A(2);break}
Ca("Sierra");Cb("About KQ2",c26);Cb("Help     ",c1);Ca("File");Cb("Save     <F5>",c18);Cb("Restore  <F7>",c19);Cb("-------------",c31);Cb("Restart  <F9>",c20);Cb("Quit  <Alt-Z>",c21);Ca("Action");Cb("Swim           =",c22);Cb("See Object  <F4>",c30);Cb("Inventory  <Tab>",c12);Ca("Special");Cb("Sound On/Off  <F2>",c2);if(J(DG,0)&&!J(DN,3)&&!J(DN,2)){Cb("Color/BW  <Ctrl R>",c11)}
Cb("Joystick  <Ctrl J>",c10);Cb("Pause        <Esc>",c16);if(!J(DG,5)){Ca("Speed");Cb("Normal ",c28);Cb("Slow   ",c29);Cb("Fast   ",c27);Cb("Fastest",c6)}
Cc();CP(c31);H(97);if(AGI.C)return}
case 2:if(!(E(DT))){A(500);break}
G(f149);Ab(Ego);CC();L(v88,0);G(f130);G(f115);G(f64);G(f128);G(f132);G(f127);L(v76,30);case 3:g(v76,0);T(v76);if(!(P(v76,49))){A(501);break}
V(v76);A(3);break;A(5);break;case 501:L(v76,230);case 4:g(v76,0);T(v76);if(!(P(v76,249))){A(502);break}
V(v76);A(4);break;case 502:case 5:L(v58,0);L(v59,0);L(v69,0);L(v70,0);L(v71,0);L(v82,0);L(v94,0);G(f161);F(f55);if(!((J(Ck,35)||J(Ck,7)||J(Ck,42)||J(Ck,41)||J(Ck,48)||J(Ck,49)||J(Ck,55)||J(Ck,56)||J(Ck,57)))){A(503);break}
CX(29);case 503:if(!((J(Ck,39)||J(Ck,40)||J(Ck,46)||J(Ck,47)||J(Ck,30)||J(Ck,31)||J(Ck,37)||J(Ck,38)||J(Ck,44)||J(Ck,45)||J(Ck,19)||J(Ck,20)||J(Ck,21)||J(Ck,26)||J(Ck,27)||J(Ck,28)))){A(504);break}
CX(5);case 504:if(!(P(Ck,60))){A(505);break}
CX(8);case 505:if(!(E(f161))){A(506);break}
BY(99);if(AGI.C)return;case 506:m(Ego);CY(0);CZ(DC);q(Ego,DC);case 500:if(D("tester")){j(f178);if(J(DN,2)&&J(DG,0)){A(6);break}
BH(22,24,0)}
case 6:if(E(f178)){AL(Ego,v112,v113);Bc(24,16,"%v112,%v113    ")}
if(K(v100,v102)&&K(v101,v103)&&K(Cr,v99)){AN(Ego);A(7);break}
AM(Ego);case 7:if(J(Cr,0)){AN(Ego)}
if(E(f92)){AM(Ego)}
M(v99,Cr);if(!(!E(f189)&&!J(Ck,110)&&!J(Ck,97))){A(507);break}
if(!(BL(c15))){A(508);break}
cmd_menu_input();case 508:if(!((D("rescue")||BL(c18)))){A(509);break}
CC();CS();case 509:if(!(!E(f170))){A(510);break}
if(!((D("restore")||BL(c19)))){A(511);break}
CC();CT();case 511:if(!((D("restart")||BL(c20)))){A(512);break}
CC();CU();case 512:if(!((D("status")||BL(c12)))){A(513);break}
CR();case 513:if(!(BL(c30))){A(514);break}
F(Db);CR();if(!(N(DM,0)&&!J(DM,255))){A(515);break}
M(v94,DM);W(v94,151);if(!(J(v94,229))){A(516);break}
if(!(E(f106))){A(517);break}
cmd_show_obj(229);A(8);break;case 517:cmd_show_obj(165);case 8:A(9);break;case 516:CM(v94);case 515:case 9:G(Db);case 514:if(!((BL(c1)||D("aid")||D("aid","a")))){A(518);break}
BF(95);if(AGI.C)return;case 518:case 510:if(!((BL(c16)||D("pause")))){A(519);break}
pause();case 519:if(!(BL(c26))){A(520);break}
Bg("King's Quest ][ was designed by Roberta Williams.");case 520:if(!(BL(c3))){A(521);break}
Cj();case 521:if(!(BL(c9))){A(522);break}
CN();case 522:if(!(BL(c10))){A(523);break}
init_joy();case 523:if(!(BL(c11))){A(524);break}
toggle_monitor();case 524:if(!((BL(c21)||D("quit")))){A(525);break}
CC();if(!(E(f161))){A(526);break}
CK(1);A(10);break;case 526:CK(0);case 525:case 507:case 10:if(BL(c2)){j(DX)}
if(BL(c24)){U(DK)}
if(BL(c25)){if(P(DK,15)){V(DK)}}
if((D("fast","speak")||BL(c13))){Bg("%s4");version();if(!E(f161)){BY(99);if(AGI.C)return;F(f161)}}
if((D("fastest")||BL(c6))){L(Cw,0)}
if((D("fast")||BL(c27))){L(Cw,1)}
if((D("normal")||BL(c28))){L(Cw,2)}
if((D("slow")||BL(c29))){L(Cw,4)}
if(!E(f170)){BG(Ck);if(AGI.C)return;A(11);break}
BF(100);if(AGI.C)return;case 11:if(E(f161)){BF(99);if(AGI.C)return}
U(v55);if(J(v55,0)&&J(v57,1)){Bg("Beware! The fairy's spell has worn off.")}
if(J(v55,0)&&N(v57,0)){U(v57);if(!J(v57,0)){L(v55,250)}}
U(v54);if(J(v54,0)){U(v66);if(J(v66,1)){if(P(Ck,97)){Bg("You feel a sudden tingling sensation. Could it be that the effects of the sugar cube have worn off?")}
A(12);break}
if(!J(v66,0)){L(v54,250)}}
case 12:if(E(f131)){G(f92);G(f131);G(f147);AV(Ego);AE(Ego);F(f107);H(105);if(AGI.C)return}
U(v88);if(J(v88,1)){Ac();p(Ego,0);Ay(Ego,v114,v115);G(f92);if(J(Ck,20)){AZ(Ego)}
if(J(v87,1)){Bg("When you rub the tarnished brass lamp, you hear a POOOOFF and a genie appears! \"Master,\" he says, \"I leave a gift for you. A magic carpet!\" The genie then poofs back into the lamp.")}
if(J(v87,2)){Bg("When you rub the lamp, you hear a loud POOOOFF and a genie magically appears. \"Master,\" he says, \"I leave a gift for you. A beautiful sword!\" The genie then disappears in a puff of smoke.");if(AGI.C)return}
if(J(v87,3)){Bg("Using your sleeve as a cloth you rub the lamp, causing the genie to appear again. \"Master,\" he says, \"I leave a gift for you. A leather bridle!\" The genie then pops back into the lamp.");Bg("Oh, no! The lamp has disappeared from your hands!")}
if(J(Ck,5)){G(f177)}}
if(E(f63)){G(f63);L(v88,70);BN(8,f169)}
if(E(f148)){Aa(Ego)}
if(!E(DQ)){A(37);break}
if(D("acquire","bouquet")&&!J(Ck,2)&&!J(Ck,3)&&!J(Ck,4)&&!J(Ck,9)&&!J(Ck,10)&&!J(Ck,16)){if(!BT("Bouquet of Flowers")){Bg("Where do you think it could be?");A(13);break}
Bg("You already have it.")}
case 13:if(D("thank","anyword")){Bg("You're welcome!")}
if(D("smell","bouquet")){if(BT("Bouquet of Flowers")){Bg("The bouquet of flowers is very fragrant.");A(14);break}
Bg("You are not carrying it.")}
case 14:if(D("consume","basket")){if(BT("Basket of Goodies")){Bg("Yum, yum. The snacks from the goody basket are sure tasty.");Y(Cn,2);CL("Basket of Goodies");BS("Empty Basket");A(15);break}
if(BT("Empty Basket")){Bg("The basket of goodies is empty because you ate all of it.");A(15);break}
Bg("You are not carrying it.")}
case 15:if(!J(Ck,3)&&D("acquire","basket")){if(BT("Empty Basket")){Bg("The basket of goodies is empty because you ate all of it.");A(16);break}
G(DS)}
case 16:if(!J(Ck,51)){if((D("point","rusty trident")||D("wave","rusty trident"))){Bg("With disappointment, you see that nothing happens.")}}
if(D("use","anyword")){Bg("What do you wish to do with it???")}
if(D("who","programmed","game")){Bg("Ken, Roberta, Sol, Jeff, Chris, Doug, Mark, Al, Scott and Dale.")}
if(D("what is","graham","last name")){Bg("Cracker.")}
if((D("acquire","boulder")||D("move","boulder")||D("move","boulder")||D("move","boulder"))){Bg("The rocks are too large and heavy.")}
if(D("dive","anyword")){if(N(v95,0)){Bg("The water is very deep here. Without aid, it is impossible to swim under the water for any length of time.");A(17);break}
Bg("You need to be in the water to try that.")}
case 17:if(D("play","anyword")){Bg("You have better things to do than to play all day.")}
if(N(Ck,49)&&(P(Ck,55)||N(Ck,58))){A(18);break}
if(!BT("Oil Lamp")){A(18);break}
if(D("pat","lamp")){if((N(v95,0)||E(f180)||E(f119)||E(f125)||E(f176)||E(DO)||E(f92)||E(f148)||E(f179)||E(f127)||E(f132)||E(f128)||!E(f55)||!J(v88,0))){Bg("Nothing happens.");A(18);break;A(18);break}
if(J(Ck,20)){AY(Ego)}
if(J(Ck,5)){F(f177)}
Ad();AL(Ego,v114,v115);p(Ego,65);w(Ego,0);F(f92);AQ(Ego,f63);if(J(v87,0)){BS("Carpet");W(Cn,2);L(v87,1);A(18);break}
if(J(v87,1)){BS("Sword");W(Cn,2);L(v87,2);A(18);break}
BS("Bridle");W(Cn,2);CL("Oil Lamp");L(v87,3)}
case 18:if(!E(DS)&&!BT("Oil Lamp")&&D("pat","lamp")){Bg("You are not carrying it.")}
if(BT("Brooch")&&D("put on","brooch")){Bg("The color of the brooch clashes with your outfit. Better leave it off.")}
if(!J(Ck,67)&&(D("hammer","hammer")||D("pound","hammer"))){Bg("You look around but see that there is no reason to use a mallet just now.")}
if(BT("Basket of Goodies")&&D("acquire","basket")){Bg("You already have the goodies. They are right in the basket!")}
if(BT("Amulet")&&!E(f170)&&!E(f184)){if(D("pat","amulet")){Bg("You rub the Tiger's Eye stone on the front of the amulet, but nothing happens.");A(19);break}
if(D("wave","amulet")){Bg("You wave the bronze amulet in the air, but nothing happens.");A(19);break}
if((D("home","anyword")||D("anyword","home")||D("home"))){CL("Amulet");Bg("You murmur the word home. A tingling sensation envelops your body. You black out for a second ... when you come to, you see you are somewhere else!");if(J(Ck,90)){W(Cn,3);H(107);if(AGI.C)return;A(19);break}
H(106);if(AGI.C)return}}
case 19:if((BT("Bottle")||BT("Empty Bottle"))){if(D("open","bottle")){Bg("The glass bottle is already open.")}}
if(BT("Bottle")&&D("acquire","cloth")){Bg("You pull a large piece of cloth out of the bottle.");BS("Empty Bottle");W(Cn,2);BS("Cloth");CL("Bottle")}
if(BT("Sugar Cube")&&D("consume","cube")){Bg("After swallowing the magic sugar cube, you get a feeling of invincibility.");CL("Sugar Cube");if(!E(f157)){W(Cn,1);F(f157)}
L(v54,0);L(v66,75)}
if(D("light","candle")){if(E(f106)){Bg("The candle is already lit.");A(20);break}
if(!BT("Candle")){Bg("You are not carrying it.");A(20);break}
if(!J(Ck,60)&&!J(Ck,61)&&!J(Ck,63)&&!J(Ck,74)){Bg("There is no way for you to light the candle.");A(20);break}
G(DS)}
case 20:if(E(f106)&&BT("Candle")&&D("blow","candle")){Bg("You pucker up your lips and blow out the candle.");G(f106)}
if(BT("Tiara")&&D("put on","diamond and sapphire tiara")){Bg("The tiara would better fit a daintier head than yours.")}
if(BT("Ham")&&D("consume","ham")){Bg("Mmmmmm! The smoked ham was delicious! It sure hit the spot.");CL("Ham")}
if((D("look in","basket")||D("open","basket"))){if(BT("Basket of Goodies")){Bg("You look in the basket of goodies and see many good things to eat: cookies, fruit, crackers, and sandwiches.");A(21);break}
if(BT("Empty Basket")){Bg("The basket of goodies is empty because you ate all of it.");A(21);break}
G(DS)}
case 21:if(BT("Ruby Ring")&&D("put on","ring")){if(!E(f68)){if(!E(f160)){if(E(f70)){F(f160);W(Cn,3)}}
Bg("You are now wearing the beautiful ruby ring.");F(f68);A(22);break}
Bg("You're already wearing it.")}
case 22:if(E(f68)&&D("remove","ring")){G(f68);Bg("OK.")}
if(BT("Bracelet")&&D("put on","bracelet")){Bg("The glittering bracelet is too small for your wrist.")}
if(BT("Necklace")&&D("put on","diamond and sapphire necklace")){Bg("You try to place it around your neck, but it doesn't fit.")}
if(BT("Oil Lamp")){if(D("look in","lamp")){Bg("The old oil lamp is empty inside.");A(23);break}
if(D("light","lamp")){Bg("The oil lamp is empty. You cannot light it.")}}
case 23:if(!N(v88,0)&&!E(f151)&&P(Ck,50)&&!E(f179)&&!E(f119)&&!E(f180)&&!E(f125)&&!E(f176)&&!E(DO)&&!E(f92)&&!E(f148)&&E(f55)&&BT("Carpet")&&!N(v95,0)&&(D("get on","carpet")||D("fly","carpet"))){AC(Ego,15);F(f147);p(Ego,98);L(v94,2);AS(Ego,v94);Ai(Ego,v94);AU(Ego);AL(Ego,v89,v90);L(v90,30);F(f148);L(v94,0);Al(Ego,v89,v90,v94,f131);F(f92);W(Cn,4);F(f151);G(f127);G(f132);G(f128)}
if(P(Ck,50)&&!J(Ck,18)&&BT("Carpet")&&D("sit","carpet")){Bg("If you wish to ride on the magic carpet, then just say so.")}
if(BT("Bridle")&&D("put on","bridle")){Bg("You put the bridle over your head. Nothing happens. Don't you feel silly?")}
if(BT("Caged Nightingale")&&D("open","bird cage")){Bg("You open the pretty birdcage and the nightingale swoops out. The bird is gone. You have nothing but an empty birdcage.");CL("Caged Nightingale");Y(Cn,2);BS("Empty Birdcage")}
if(BT("Black Cloak")&&D("put on","black cape")){if(!E(f70)){Bg("With a flourish, you fling the black cloak around your neck and fasten it.");if(!E(f160)){if(E(f68)){F(f160);W(Cn,3)}}
F(f70);A(24);break}
Bg("You're already wearing it.")}
case 24:if(E(f70)&&D("remove","black cape")){Bg("OK.");G(f70)}
if(BT("Cross")&&D("put on","cross")){if(!E(f69)){Bg("You place the silver cross and chain around your neck and wear it as a necklace.");if(!E(f159)){W(Cn,2);F(f159)}
F(f69);A(25);break}
Bg("You're already wearing it.")}
case 25:if(E(f69)&&D("remove","cross")){G(f69);Bg("OK.")}
if(BT("Chicken Soup")&&(D("consume","broth")||D("drink","broth"))){Bg("Hungrily, you eat the tasty chicken soup. Aaaaahhhh! You feel very satisfied. You throw away the useless empty pot.");CL("Chicken Soup")}
if(BT("Earrings")&&D("put on","earrings")){Bg("The earrings were made for more delicate ears than yours.")}
if(!((D("check out","anyword")||D("check out","anyword","anyword")))){A(527);break}
G(DS);if(!(E(f162))){A(528);break}
A(32);break;A(26);break;case 528:if(!(J(Ck,67)&&!J(v92,0)&&!J(v92,2)&&!J(v92,4))){A(529);break}
A(32);break;case 529:case 26:A(27);break;case 527:A(32);break;case 27:if(D("check out","boulder")&&!J(Ck,15)&&!J(Ck,13)&&!J(Ck,58)&&!J(Ck,75)&&!J(Ck,80)&&!J(Ck,85)&&(P(Ck,77)||N(Ck,93))){Bg("The rocks are the usual sort of rocks, nothing special.")}
if(BT("Amulet")&&(D("check out","amulet")||D("read","amulet"))){cmd_show_obj(232)}
if(BT("Bottle")&&(D("check out","bottle")||D("look in","bottle"))){cmd_show_obj(215)}
if(BT("Empty Bottle")&&(D("check out","bottle")||D("look in","bottle")||D("check out","empty","bottle"))){cmd_show_obj(216)}
if(BT("Cloth")&&D("check out","cloth")){cmd_show_obj(224)}
if(BT("Sugar Cube")&&(D("check out","cube")||D("check out","cube","cube"))){cmd_show_obj(230)}
if(BT("Gold Key")&&BT("Silver Key")){if(D("check out","key")){Bg("You'll have to specify which key you wish to look at.")}}
if(BT("Gold Key")){if((D("check out","gold","key")||D("check out","key"))){cmd_show_obj(212)}}
if(BT("Silver Key")){if((D("check out","silver","key")||D("check out","key"))){cmd_show_obj(234)}}
if(BT("Candle")&&D("check out","candle")){if(E(f106)){cmd_show_obj(229);A(28);break}
cmd_show_obj(165)}
case 28:if(BT("Tiara")&&D("check out","diamond and sapphire tiara")){cmd_show_obj(207)}
if(BT("Ham")&&D("check out","ham")){cmd_show_obj(217)}
if(BT("Pillow")&&D("check out","cushion")){cmd_show_obj(225)}
if(BT("Bouquet of Flowers")&&(D("check out","bouquet")||D("check out","bouquet","blossom"))){cmd_show_obj(203)}
if(BT("Basket of Goodies")&&(D("check out","basket")||D("check out","basket","basket"))){cmd_show_obj(214)}
if(BT("Empty Basket")&&(D("check out","basket")||D("check out","empty","basket"))){cmd_show_obj(213)}
if(BT("Ruby Ring")&&D("check out","ring")){cmd_show_obj(206)}
if(!J(Ck,51)){if(BT("Clamshell")&&(D("check out","clam")||D("check out","clam"))){cmd_show_obj(233)}}
if(BT("Bracelet")&&D("check out","bracelet")){cmd_show_obj(204)}
if(BT("Trident")&&D("check out","rusty trident")){cmd_show_obj(202)}
if(BT("Necklace")&&D("check out","diamond and sapphire necklace")){cmd_show_obj(208)}
if(BT("Mallet")&&D("check out","hammer")){cmd_show_obj(211)}
if(BT("Oil Lamp")&&D("check out","lamp")){cmd_show_obj(223)}
if(!J(Ck,70)&&BT("Carpet")&&D("check out","carpet")){cmd_show_obj(227)}
if(BT("Sword")&&D("check out","knife")){cmd_show_obj(201)}
if(BT("Bridle")&&D("check out","bridle")){cmd_show_obj(228)}
if(!((D("check out","bird")||D("check out","empty","bird cage")||D("check out","bird cage")))){A(530);break}
if(!(BT("Empty Birdcage"))){A(531);break}
cmd_show_obj(222);A(30);break;case 531:if(!(BT("Caged Nightingale"))){A(532);break}
if(!(J(v65,2))){A(533);break}
Bg("The cage is covered.");A(29);break;case 533:if(!(!E(f149))){A(534);break}
CX(22);F(f149);case 534:BN(22,f169);cmd_show_obj(221);case 29:A(30);break;case 532:G(DS);case 530:case 30:if(BT("Black Cloak")&&D("check out","black cape")){cmd_show_obj(219)}
if(BT("Cross")&&D("check out","cross")){cmd_show_obj(220)}
if(BT("Chicken Soup")){if(D("check out","broth")){cmd_show_obj(218);A(31);break}
if(D("check out","cauldron")&&!J(Ck,69)){cmd_show_obj(218)}}
case 31:if(BT("Earrings")&&D("check out","earrings")){cmd_show_obj(209)}
if(BT("Fishing Net")&&D("check out","fishing net")){cmd_show_obj(226)}
if(BT("Gasping Fish")&&D("check out","dolphin")){cmd_show_obj(231)}
if(BT("Brooch")&&D("check out","brooch")){cmd_show_obj(210)}
if(BT("Stake")&&D("check out","pole")){cmd_show_obj(205)}
case 32:if((D("check out","knife")||D("check out","rusty trident")||D("check out","bouquet")||D("check out","bracelet")||D("check out","pole")||D("check out","ring")||D("check out","diamond and sapphire tiara")||D("check out","diamond and sapphire necklace")||D("check out","earrings")||D("check out","brooch")||D("check out","hammer")||D("check out","key")||D("check out","gold")||D("check out","silver")||D("check out","basket")||D("check out","bottle")||D("check out","ham")||D("check out","broth")||D("check out","black cape")||D("check out","cross")||D("check out","bird cage")||D("check out","lamp")||D("check out","cloth")||D("check out","cushion")||D("check out","fishing net")||D("check out","carpet")||D("check out","bridle")||D("check out","candle")||D("check out","cube")||D("check out","dolphin")||D("check out","amulet")||D("check out","clam")||D("check out","bird"))){Bg("You are not carrying it.");A(33);break}
if(!N(Cu,0)&&(D("check out","anyword")||D("look in","anyword"))){Bg("You see nothing special.")}
case 33:if(D("acquire","anyword")&&!D("acquire")){Bg("You cannot get the %w2. At least not now!")}
if(D("drop","anyword")){Bg("There is no reason to do that.")}
if(D("consume","anyword")){if((D("consume","count dracula")||D("consume","bitch"))){Bg("You can't do that.");A(34);break}
if((D("consume","cube")||D("consume","basket"))){Bg("You are not carrying it.");A(34);break}
Bg("The %w2 doesn't appeal just now.")}
case 34:if(D("acquire")){Bg("Just say what you wish to get.")}
if(D("climb","anyword")){Bg("No. That would just waste time.")}
if(D("enter","anyword")){Bg("You can try to go there.")}
if(D("feed","anyword")){Bg("That would be inappropriate at this time.")}
if(D("hello","anyword")){Bg("Hello.")}
if((D("say","hello")||D("hello"))){Bg("There is nobody here but you!");A(35);break}
if(D("say","anyword")){Bg("OK. %w2.")}
case 35:if(D("find","count dracula")){Bg("You will have to find him yourself.");A(36);break}
if(D("find","bitch")){Bg("You will have to find her yourself.");A(36);break}
if(D("find","anyword")){Bg("You will have to find it yourself.")}
case 36:if(D("get on","anyword")){Bg("You're not able to ride the %w2 at this time.")}
if(D("speak","anyword")){Bg("You get no response from the %w2.")}
if(E(DQ)&&!E(DS)&&N(Cu,0)){G(DQ);if(J(Cu,1)){Bg("I don't understand \"%w1\"")}
if(J(Cu,2)){Bg("I don't understand \"%w2\"")}
if(J(Cu,3)){Bg("I don't understand \"%w3\"")}}
if(E(DQ)&&!E(DS)){l(139,141,v94);Bj(v94);G(DQ)}
case 37:if(E(f148)){Aa(Ego)}
return}}}
MESSAGES[0]=["","I don't understand \"%w1\"","Where do you think it could be?","The bouquet of wildflowers is very pretty. The sweet scent is delightful.","The bouquet of flowers is very fragrant.","","What do you wish to do with it???","There are many good things to eat in the basket of goodies.","Yum, yum. The snacks from the goody basket are sure tasty.","The basket of goodies is empty because you ate all of it.","You already have it.","This is a poisoned lake! Too bad, you die of extreme poisoning.","You need to be closer to the water if you want to swim.","You look around but see that there is no reason to use a mallet just now.","The color of the brooch clashes with your outfit. Better leave it off.","","","You feel a sudden tingling sensation. Could it be that the effects of the sugar cube have worn off?","Ken, Roberta, Sol, Jeff, Chris, Doug, Mark, Al, Scott and Dale.","Cracker.","%v112,%v113    ","The rocks are the usual sort of rocks, nothing special.","The rocks are too large and heavy.","","You are not carrying it.","There is no reason to drop it.","You are already swimming.","The water is very deep here. Without aid, it is impossible to swim under the water for any length of time.","You need to be in the water to try that.","You have better things to do than to play all day.","You're already wearing it.","The old oil lamp is empty inside.","The glass bottle is already open.","You pull a large piece of cloth out of the bottle.","If you wish to ride on the magic carpet, then just say so.","The cage is covered.","After swallowing the magic sugar cube, you get a feeling of invincibility.","","You try to place it around your neck, but it doesn't fit.","OK.","You're welcome!","You already have the goodies. They are right in the basket!","","The candle is already lit.","There is no way for you to light the candle.","You pucker up your lips and blow out the candle.","","The tiara would better fit a daintier head than yours.","","Mmmmmm! The smoked ham was delicious! It sure hit the spot.","","","","","","","You are now wearing the beautiful ruby ring.","","","The glittering bracelet is too small for your wrist.","","","","","The oil lamp is empty. You cannot light it.","","","","You put the bridle over your head. Nothing happens. Don't you feel silly?","You open the pretty birdcage and the nightingale swoops out. The bird is gone. You have nothing but an empty birdcage.","","","With a flourish, you fling the black cloak around your neck and fasten it.","","You place the silver cross and chain around your neck and wear it as a necklace.","","Hungrily, you eat the tasty chicken soup. Aaaaahhhh! You feel very satisfied. You throw away the useless empty pot.","","The earrings were made for more delicate ears than yours.","","","","Beware! The fairy's spell has worn off.","","You rub the Tiger's Eye stone on the front of the amulet, but nothing happens.","You wave the bronze amulet in the air, but nothing happens.","You murmur the word home. A tingling sensation envelops your body. You black out for a second ... when you come to, you see you are somewhere else!","","When you rub the tarnished brass lamp, you hear a POOOOFF and a genie appears! \"Master,\" he says, \"I leave a gift for you. A magic carpet!\" The genie then poofs back into the lamp.","When you rub the lamp, you hear a loud POOOOFF and a genie magically appears. \"Master,\" he says, \"I leave a gift for you. A beautiful sword!\" The genie then disappears in a puff of smoke.","Using your sleeve as a cloth you rub the lamp, causing the genie to appear again. \"Master,\" he says, \"I leave a gift for you. A leather bridle!\" The genie then pops back into the lamp.","Nothing happens.","You have two keys! Do you wish to look at the silver one or the gold one?","Oh, no! The lamp has disappeared from your hands!","","With disappointment, you see that nothing happens.","You look in the basket of goodies and see many good things to eat: cookies, fruit, crackers, and sandwiches.","The basket of goodies is empty because you ate all of it.","You'll have to specify which key you wish to look at.","","","%s4","","","","","","","","","","","","","","","Exit Game? (Y/N) ","","","","","You see nothing special.","You cannot get the %w2. At least not now!","There is no reason to do that.","The %w2 doesn't appeal just now.","No. That would just waste time.","You can try to go there.","That would be inappropriate at this time.","Hello.","OK. %w2.","You will have to find him yourself.","You will have to find her yourself.","You will have to find it yourself.","You are not carrying it.","","","","","There is nobody here but you!","You can't do that--at least not now!","Not right now!","You can't do that.","","Just say what you wish to get.","You get no response from the %w2.","I don't understand \"%w1\"","I don't understand \"%w2\"","I don't understand \"%w3\"","You're not able to ride the %w2 at this time.","","Sierra","About KQ2","Help     ","File","Save     <F5>","Restore  <F7>","-------------","Restart  <F9>","Quit  <Alt-Z>","Action","Swim           =","See Object  <F4>","Inventory  <Tab>","Special","Sound On/Off  <F2>","Color/BW  <Ctrl R>","Joystick  <Ctrl J>","Pause        <Esc>","Speed","Normal ","Slow   ","Fast   ","Fastest","King's Quest ][ was designed by Roberta Williams."];