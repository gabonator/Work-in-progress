window.logic67=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CY(99);CY(58);L(v31,96);CW(v31);m(o4);l(0,255,v106);if(!(E(f129))){A(501);break}
L(v106,0);case 501:if(!(P(v106,128)&&!J(v92,2))){A(502);break}
L(v92,1);L(v91,0);m(o3);L(v94,2);Ai(o3,v94);AE(o3);CY(53);CY(59);CY(51);CY(52);CY(57);CY(60);p(o4,57);w(o4,0);A(1);break;case 502:if(!(!J(v92,2))){A(503);break}
L(v92,0);case 503:p(o4,58);if(!(J(v91,2))){A(504);break}
w(o4,0);A(1);break;case 504:w(o4,3);L(v91,1);case 1:AG(Ego,132,130);if(!(E(f106))){A(505);break}
L(v30,1);G(f162);CW(Ck);BJ(Ck);Bu(Ck);AY(o4);AG(o4,65,95);AJ(o4);Az(o4);A(2);break;case 505:L(v30,0);F(f162);p(Ego,99);BJ(v31);AC(Ego,12);AC(o3,4);AC(o4,4);case 2:AJ(Ego);BM();case 500:if(N(v35,0)){Bw(60);Bw(57);Bw(52);Bw(51);Bw(59);if(J(v35,6)){Bw(53)}
L(v35,0)}
U(v32);if(J(v92,1)&&J(v32,0)&&J(v91,1)){BA(o4);w(o4,0);p(o4,60);L(v94,2);AS(o4,v94);AQ(o4,f39);L(v92,3);Bg("Count Dracula is awake! Run before it's too late!")}
if(E(f39)){G(f39);L(v34,2);p(o4,58);w(o4,3);p(o3,51);AG(o3,73,107);AJ(o3);F(f38);Am(o3,4,f34);BB(o4)}
if(!(E(f34))){A(506);break}
Bg("You are caught in Dracula's grasp! Saliva drips off the end of his sharp fangs.");G(f34);if(!(E(f69))){A(507);break}
Bg("Suddenly, he is aware of the silver cross you are wearing around your neck!");F(f37);A(4);break;case 507:if(!(!E(f106))){A(508);break}
AC(Ego,4);case 508:BV();AK(o3);Ag(Ego);if(!((BO(Ego,32,96,44,100)||BO(Ego,28,111,40,127)||BO(Ego,23,128,35,144)||BO(Ego,18,145,31,160)||BO(Ego,97,94,104,106)))){A(509);break}
L(v67,0);L(v68,0);A(3);break;case 509:L(v67,248);L(v68,0);case 3:Aw(Ego,v67,v68);p(Ego,53);L(v94,3);AS(Ego,v94);F(f92);w(Ego,0);AQ(Ego,f35);L(v35,5);case 506:case 4:if(E(f35)){AN(Ego);G(f92);Bg("You feel them sink into the soft flesh of your neck, and then ... nothing.");G(f35);L(v92,5);F(f50)}
if(J(v34,2)&&E(f37)){L(v34,0);A(31);break}
if(E(f36)){AK(o3);G(f38);G(f36);L(v35,6)}
U(v33);if(J(v33,1)){BB(o4);p(o4,58);w(o4,3);G(f92);Ah(Ego);p(Ego,0);r(Ego,1);AL(Ego,v105,v106);L(v67,76);L(v68,107);Z(v67,v105);Z(v68,v106);Aw(Ego,v67,v68);L(v35,6);Bg("You place the pointed stake on Count Dracula's chest. Quickly, using the mallet, you pound the stake through his heart. Dracula disintegrates into a pile of dust. A small silver key is left behind in the coffin.")}
if(E(f33)){G(f33);Ag(Ego);w(Ego,0);AL(Ego,v105,v106);L(v67,65);L(v68,107);Z(v67,v105);Z(v68,v106);Aw(Ego,v67,v68);p(Ego,59);L(v33,25);W(Cn,4);X(Cn,v80)}
if(!E(f106)){if(J(v30,1)){L(v30,2);F(f162);if(E(f38)){AK(o3)}
BJ(v31);BM();AC(Ego,12);p(Ego,99);AC(o3,4);AC(o4,4);Az(o4);BB(o4);if(E(f38)){AJ(o3)}
A(5);break}
A(32);break}
case 5:if(!E(DQ)){A(33);break}
if((D("check out")||D("check out","antique shop")||D("check out","swim"))){Bg("There is a beautiful, ornate coffin to one side of this dreadful room. Dust is everywhere, cobwebs fill the corners, and a sickly odor permeates the air.")}
if(D("acquire","casket")){Bg("You don't think you could carry around a heavy %w2, do you?")}
if((D("get in","casket")||D("enter","casket")||D("climb","casket"))){Bg("That is truly crazy!")}
if(!D("check out","casket")&&!D("look in","casket")){A(8);break}
if(!BO(Ego,50,105,97,109)){Bg("At this distance the candle does not provide enough light for you to see much detail.");A(33);break}
if(!J(v91,1)){Bg("The lid of the beautifully carved coffin is closed.");A(33);break}
if(J(v92,1)){Bg("Quaking, you look into the beautiful coffin. A vampire is lying asleep within it! It must be Count Dracula!");A(33);break;A(6);break}
Bg("Trembling with fear, you peer into the ornate coffin. Finding it unoccupied, you see the interior is lined with shiny red satin.");case 6:if(!E(f137)){Bg("A red satin pillow lies at one end.");A(7);break}
if(!E(f138)){Bg("Against the red satin, you notice a large golden key!")}
case 7:if(!E(f139)&&J(v92,2)){Bg("A small silver key is lying within the coffin!")}
A(33);break;case 8:if(!D("open","casket")&&!D("open","lid")){A(10);break}
if(J(v91,1)){Bg("The lid to the coffin is already up.");A(9);break}
if(!BO(Ego,50,105,97,115)){Bg("To do that, you will need to get closer.");A(9);break}
BA(o4);AQ(o4,f169);L(v91,1);if(!J(v92,1)){Bg("Nervously, you lift the heavy lid of the elegant coffin. You peek into its red satin interior. The coffin is unoccupied.");A(6);break;A(9);break}
Bg("With trepidation, you lift the heavy lid of the beautifully carved coffin. Your heart beats wildly when you see a vampire lying asleep within it! It must be Count Dracula!");L(v32,100);case 9:A(33);break;case 10:if(!D("close","casket")&&!D("close","lid")){A(12);break}
if(!J(v91,1)){Bg("The lid to the coffin is already closed.");A(11);break}
if(!BO(Ego,50,105,97,115)){Bg("To do that, you will need to get closer.");A(11);break}
BA(o4);AR(o4,f169);L(v91,2);L(v32,0);case 11:A(33);break;case 12:if(D("acquire","cushion")){if(BT("Pillow")){Bg("You already have.");A(13);break}
if((!J(v91,1)||E(f137))){Bg("You don't see one here.");A(13);break}
if(!BO(Ego,50,105,97,115)){Bg("To do that, you will need to get closer.");A(13);break}
if(J(v92,1)){Bg("That was truly a dumb thing to do! Run before he catches you!");L(v32,0);A(13);break}
Bg("You remove the shiny red %w2 from the coffin. Lo and behold, a large gold key was under the %w2!");BS("Pillow");F(f137)}
case 13:if(!(J(v91,1))){A(510);break}
if(!(J(v92,2))){A(511);break}
if(!(!E(f139))){A(512);break}
if(!((!E(f137)||E(f138)))){A(513);break}
A(17);break;A(14);break;case 513:A(19);break;case 512:case 511:case 14:if(!(E(f137)&&!E(f138))){A(514);break}
A(15);break;case 514:case 510:if((D("acquire","key")||D("acquire","gold","key")||D("acquire","silver","key")||D("acquire","keys")||D("acquire","both","keys"))){Bg("You don't see one here.");A(33);break}
A(24);break;case 15:if((D("acquire","key")||D("acquire","gold","key"))){if(!BO(Ego,50,105,97,115)){Bg("To do that, you will need to get closer.");A(16);break}
A(20);break}
case 16:A(23);break;case 17:if((D("acquire","key")||D("acquire","silver","key"))){if(!BO(Ego,50,105,97,115)){Bg("To do that, you will need to get closer.");A(18);break}
A(21);break}
case 18:A(23);break;case 19:if(D("acquire","key")){Bg("There are two keys in the coffin. Do you want the gold one or the silver one?");F(f32);A(33);break}
if(D("acquire","gold","key")){A(20);break}
if(E(f32)&&(D("gold","one")||D("gold","key")||D("acquire","gold","one"))){A(20);break}
if(D("acquire","silver","key")){A(21);break}
if(E(f32)&&(D("silver","one")||D("silver","key")||D("acquire","silver","one"))){A(21);break}
if((D("acquire","keys")||D("acquire","both","keys"))){A(22);break}
if(E(f32)&&D("acquire","both","them")){A(22);break}
if(!E(DS)&&D("anyword","anyword")){G(DS);G(f32)}
A(24);break;case 20:Bg("OK.");BS("Gold Key");F(f138);G(f32);W(Cn,5);A(33);break;case 21:Bg("OK.");BS("Silver Key");F(f139);G(f32);W(Cn,2);A(33);break;case 22:Bg("OK.");BS("Gold Key");F(f138);BS("Silver Key");F(f139);G(f32);W(Cn,5);W(Cn,2);A(33);break;case 23:if((D("acquire","keys")||D("acquire","both","keys"))){Bg("There is only one key here.");A(33);break;A(24);break}
if((D("anyword","key")||D("anyword","anyword","key"))){if(!D("check out","key")&&!D("check out","anyword","key")){Bg("You don't see one here.");A(33);break;A(24);break}
G(DS)}
case 24:if((D("show","cross")||D("show","count dracula","cross"))){if(!BT("Cross")){Bg("You don't have it!");A(33);break}}
if(!(J(v92,1)&&J(v91,1))){A(515);break}
if(!((D("speak","count dracula")||D("hello","anyword")||D("say","hello")||D("show","cross")||D("show","count dracula","cross")))){A(516);break}
Bg("Count Dracula is fast asleep in his coffin. He pays you no heed.");A(27);break;case 516:if(!((D("acquire","count dracula")||D("capture","count dracula")))){A(517);break}
Bg("That is truly crazy!");A(27);break;case 517:if(!(!BO(Ego,50,105,97,115))){A(518);break}
if(!((D("wake","count dracula")||D("kill","count dracula")||D("pound","pole","count dracula")))){A(519);break}
Bg("To do that, you will need to get closer.");A(25);break;case 519:if(!(D("check out","count dracula"))){A(520);break}
Bg("At this distance the candle does not provide enough light for you to see much detail.");case 520:case 25:A(27);break;case 518:if(!(D("wake","count dracula"))){A(521);break}
Bg("That was truly a dumb thing to do! Run before he catches you!");L(v32,0);A(27);break;case 521:if(!((D("kill","count dracula")||D("pound","pole","count dracula")))){A(522);break}
if(!(BT("Stake")&&BT("Mallet")&&!D("kill","count dracula","knife"))){A(523);break}
F(f92);Ak(Ego,76,107,0,f33);L(v32,250);L(v92,2);A(26);break;case 523:if(!(BT("Sword")&&!D("pound","pole","count dracula"))){A(524);break}
Bg("You plunge the sword into Count Dracula's sleeping body. Oh, dear! It has no effect. You just woke him up.");L(v32,0);A(26);break;case 524:Bg("You have no way of killing Count Dracula. You are in mortal danger!");case 26:A(27);break;case 522:if(!(D("check out","count dracula"))){A(525);break}
Bg("Count Dracula is tall and elegantly dressed with a black cloak wrapped around him. His face and hands are chalk white. His lips are blood red.");case 525:case 27:A(33);break;case 515:if(J(v92,1)&&!J(v91,1)){if((D("speak","count dracula")||D("kill","count dracula"))){Bg("The coffin isn't open.")}}
case 28:if(!(J(v92,3))){A(526);break}
if(!((D("speak","count dracula")||D("hello","anyword")||D("say","hello")))){A(527);break}
Bg("You don't want to chitchat with Count Dracula!");A(29);break;case 527:if(!((D("show","cross")||D("show","count dracula","cross")))){A(528);break}
F(f37);A(29);break;case 528:if(!((D("kill","count dracula")||D("pound","pole","count dracula")))){A(529);break}
Bg("You have no way of killing Count Dracula. You are in mortal danger!");A(29);break;case 529:if(!(D("check out","count dracula"))){A(530);break}
Bg("Count Dracula is tall and elegantly dressed with a black cloak wrapped around him. His face and hands are chalk white. His lips are blood red.");A(29);break;case 530:if(!((D("anyword","count dracula")||D("anyword","anyword","count dracula")))){A(531);break}
Bg("You don't have time! Run for your life!");case 531:case 29:A(33);break;case 526:if((D("anyword","count dracula")||D("anyword","anyword","count dracula")||D("show","cross"))){if((!J(v92,1)||J(v91,3))){Bg("There is no one here but you.");A(30);break}
if(J(v91,2)){Bg("Count Dracula is fast asleep in his coffin. He pays you no heed.")}}
case 30:A(33);break;case 31:Bg("Count Dracula is terrified of the cross. He turns into a bat and flies away.");BB(o4);w(o4,3);p(o4,58);p(o3,52);L(v94,2);AS(o3,v94);Ai(o3,v94);AY(o3);Aa(o3);AM(o3);AC(o3,11);L(v92,4);Ak(o3,137,80,0,f36);X(Cn,v80);L(v80,0);A(33);break;case 32:if(!E(DS)&&!D("light","candle")){if(D("check out","anyword")){Bg("It is pitch black in here! You can't see a thing!");A(33);break}
if(D("show","cross")){A(28);break;A(33);break}
if(D("anyword","anyword")){Bg("You can't do that while stumbling around in the dark.")}}
case 33:if(!E(DS)&&D("check out","anyword")){if(J(v92,3)){Bg("You don't have time! Run for your life!");A(34);break}
if(J(v92,1)){Bg("Are you crazy? Dracula hangs out here, and you want to stand around looking at things?");A(34);break}
G(DS)}
case 34:if(!(J(Cm,2))){A(532);break}
Ab(o3);AE(Ego);AE(o3);BB(o4);AE(o4);if(!(J(v92,0))){A(533);break}
l(0,100,v106);if(!(P(v106,128))){A(534);break}
L(v92,61);A(35);break;case 534:L(v92,64);case 533:case 35:if(!(J(v92,3))){A(535);break}
L(v92,71);case 535:H(66);if(AGI.C)return;case 532:return}}}
MESSAGES[67]=["","There is a beautiful, ornate coffin to one side of this dreadful room. Dust is everywhere, cobwebs fill the corners, and a sickly odor permeates the air.","The lid of the beautifully carved coffin is closed.","Trembling with fear, you peer into the ornate coffin. Finding it unoccupied, you see the interior is lined with shiny red satin.","A red satin pillow lies at one end.","Against the red satin, you notice a large golden key!","A small silver key is lying within the coffin!","Quaking, you look into the beautiful coffin. A vampire is lying asleep within it! It must be Count Dracula!","The lid to the coffin is already up.","Nervously, you lift the heavy lid of the elegant coffin. You peek into its red satin interior. The coffin is unoccupied.","With trepidation, you lift the heavy lid of the beautifully carved coffin. Your heart beats wildly when you see a vampire lying asleep within it! It must be Count Dracula!","The lid to the coffin is already closed.","Count Dracula is tall and elegantly dressed with a black cloak wrapped around him. His face and hands are chalk white. His lips are blood red.","You remove the shiny red %w2 from the coffin. Lo and behold, a large gold key was under the %w2!","At this distance the candle does not provide enough light for you to see much detail.","There are two keys in the coffin. Do you want the gold one or the silver one?","There is only one key here.","You don't think you could carry around a heavy %w2, do you?","Count Dracula is awake! Run before it's too late!","You are caught in Dracula's grasp! Saliva drips off the end of his sharp fangs.","You feel them sink into the soft flesh of your neck, and then ... nothing.","Count Dracula is fast asleep in his coffin. He pays you no heed.","You don't want to chitchat with Count Dracula!","That is truly crazy!","You place the pointed stake on Count Dracula's chest. Quickly, using the mallet, you pound the stake through his heart. Dracula disintegrates into a pile of dust. A small silver key is left behind in the coffin.","You have no way of killing Count Dracula. You are in mortal danger!","You plunge the sword into Count Dracula's sleeping body. Oh, dear! It has no effect. You just woke him up.","You need something to pound the stake with.","That was truly a dumb thing to do! Run before he catches you!","To do that, you will need to get closer.","There is no one here but you.","You don't have time! Run for your life!","Count Dracula is terrified of the cross. He turns into a bat and flies away.","You don't have it!","You don't see one here.","You already have.","OK.","You can't do that while stumbling around in the dark.","Suddenly, he is aware of the silver cross you are wearing around your neck!","It is pitch black in here! You can't see a thing!","Are you crazy? Dracula hangs out here, and you want to stand around looking at things?","The coffin isn't open."];CONTROLS[67]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.ri.xt<.!<.gt.x<1<U<!.W.x<1<U<P.GUR.xW.l696<P<P.(.xW.rB<P<KB.g<G96.rB<P<K6.l<G96.r696<K<K6.l<G96.xB<K<K6.l<R.xB<K<EB.l<R.x696<E<E6.r<R.!B<E<E6.r<R.!B<E<9B.r<R.!696<9<9B.r<R.^B<9<96.x<R.^B<9<96.x<R.^696<4<4B>.^B<4<46>.+B<4<46>.+696.,<46>.{<6.,B>.{<6.,6/4.,6/4.{B/4.{B/4.{6/9.{6/9.+B/9.+6/E.+6/E.^B/E.^B/E.^6/K.^6/K.!B/K.!B/K.!6/P.!6/P.xB/P.x6/U.x6/U.rB/U.rB/U.r6/Z.r6/Z.lB/Z.lB/Z.l6/g.gB/g.gB/g.g6/l.g6/l.ZB><,.n.ZB><.4.i.Z6><.9696.U.UB><.EB.U.UB><.E696.P.UB><.KB.P.U6><.P696.K.PB><.UB.K.PB><.U696.E.P6><.gB.E.P6><.lB.9.KB><.lB.9.KB><.rB.4.K6><.xB.4.EB><.!B,.EB><.!B,.EB><.^B{.E6><.+B{.9/B+.9/B+?4?4?4?4?4";