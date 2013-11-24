window.logic166=function()
{while(1){switch(B)
{case 0:if(!E(f230)&&E(DT)){F(f230);if(J(v92,4)){L(v92,0)}
if(P(Ck,65)){G(f162)}
return}
if(!(K(Ck,v92))){A(500);break}
if(!(J(Ck,66))){A(501);break}
AG(o3,1,150);A(2);break;case 501:l(0,255,v106);if(!(J(Ck,61))){A(502);break}
if(!(P(v106,80))){A(503);break}
AG(o3,71,148);A(1);break;case 503:if(!(P(v106,160))){A(504);break}
AG(o3,33,120);A(1);break;case 504:AG(o3,97,104);case 1:A(2);break;case 502:if(!(P(v106,80))){A(505);break}
AG(o3,120,142);A(2);break;case 505:if(!(P(v106,160))){A(506);break}
AG(o3,74,100);A(2);break;case 506:AG(o3,30,123);case 2:L(v92,3);if(!(!J(Ck,66))){A(507);break}
m(o3);L(v230,2);Ai(o3,v230);Bg("Count Dracula is here!! Run before it's too late!");A(3);break;case 507:if(!(!E(f106))){A(508);break}
AC(o3,4);case 508:case 3:p(o3,51);AJ(o3);Am(o3,4,f231);case 500:if(E(f231)){Bg("You are caught in Dracula's grasp! Saliva drips off the end of his sharp fangs.");G(f231);if(E(f69)){Bg("Suddenly, he is aware of the silver cross you are wearing around your neck!");A(10);break;A(4);break}
if(J(Ck,66)&&!E(f106)){AC(Ego,4)}
BV();AK(o3);Ag(Ego);L(v67,250);L(v68,0);Aw(Ego,v67,v68);p(Ego,53);L(v230,3);AS(o3,v230);F(f92);w(Ego,0);AQ(Ego,f232);L(v92,5)}
case 4:if(E(f232)){AN(Ego);G(f92);Bg("You feel them sink into the soft flesh of your neck, and then ... nothing.");G(f232);F(f50)}
if(E(f233)){G(f233);AK(o3);L(v92,0)}
if(!E(DQ)){A(13);break}
if(J(v92,0)&&(D("anyword","count dracula")||D("anyword","anyword","count dracula"))){Bg("There is no one here but you.");A(13);break}
if(!(J(v92,3))){A(509);break}
if(!((D("speak","count dracula")||D("hello","anyword")||D("say","hello")))){A(510);break}
Bg("You don't want to chitchat with Count Dracula!");A(5);break;case 510:if(!((D("show","cross")||D("show","count dracula","cross")))){A(511);break}
A(10);break;A(5);break;case 511:if(!((D("kill","count dracula")||D("pound","pole","count dracula")))){A(512);break}
Bg("You have no way of killing Count Dracula. You are in mortal danger!");A(5);break;case 512:if(!(D("check out","count dracula"))){A(513);break}
Bg("Count Dracula is tall and elegantly dressed with a black cloak wrapped around him. His face and hands are chalk white. His lips are blood red.");A(5);break;case 513:if(!((D("anyword","count dracula")||D("anyword","anyword","count dracula")))){A(514);break}
Bg("You don't have time! Run for your life!");case 514:case 5:A(13);break;case 509:if(D("check out","window")&&(J(Ck,59)||J(Ck,62))){Bg("You see the thorny island and the foul lake through the window.")}
if(!(J(Ck,64)&&BO(Ego,0,100,40,144))){A(515);break}
if(!(D("check out","torch"))){A(516);break}
Bg("The torches lend the only warmth to this dreary castle.");A(6);break;case 516:if(!(D("acquire","torch"))){A(517);break}
Bg("The torch is firmly attached to the wall. Try as you might, you cannot budge it.");case 517:case 6:A(8);break;case 515:if(!(J(Ck,61))){A(518);break}
if(!(D("check out","torch"))){A(519);break}
Bg("The torches lend the only warmth to this dreary castle.");A(7);break;case 519:if(!(D("acquire","torch"))){A(520);break}
Bg("The torch is firmly attached to the wall. Try as you might, you cannot budge it.");A(7);break;case 520:if(!(D("light","candle")&&BT("Candle")&&!E(f106))){A(521);break}
Bg("You hold your candle up to the blazing torch, but the flames are out of your reach.");case 521:case 7:A(8);break;case 518:if(D("anyword","torch")&&!J(Ck,60)&&!J(Ck,63)){Bg("You don't see one here.")}
case 8:if(E(f162)&&!E(DS)&&!D("light","candle")){if((D("check out")||D("check out","anyword"))){Bg("It is pitch black in here! You can't see a thing!");A(9);break}
if(D("anyword","anyword")){Bg("You can't do that while stumbling around in the dark.")}}
case 9:A(13);break;case 10:Bg("Count Dracula is terrified of the cross. He transforms into a bat and flies away.");p(o3,52);L(v230,2);AS(o3,v230);AY(o3);Aa(o3);AM(o3);AF(o3,v105);if(N(v105,12)){AC(o3,12);A(11);break}
AD(o3,v105);case 11:L(v92,4);if(J(Ck,61)){Ak(o3,136,55,0,f233);A(12);break}
if(J(Ck,64)){Ak(o3,0,46,0,f233);A(12);break}
Ak(o3,0,116,0,f233);case 12:X(Cn,v80);L(v80,0);case 13:if(N(v92,66)){U(v92)}
return}}}
MESSAGES[166]=["","The torches lend the only warmth to this dreary castle.","The torch is firmly attached to the wall. Try as you might, you cannot budge it.","You hold your candle up to the blazing torch, but the flames are out of your reach.","There is no one here but you.","You don't see one here.","You see the thorny island and the foul lake through the window.","You can't do that while stumbling around in the dark.","Suddenly, he is aware of the silver cross you are wearing around your neck!","It is pitch black in here! You can't see a thing!","Count Dracula is tall and elegantly dressed with a black cloak wrapped around him. His face and hands are chalk white. His lips are blood red.","Count Dracula is here!! Run before it's too late!","You are caught in Dracula's grasp! Saliva drips off the end of his sharp fangs.","You feel them sink into the soft flesh of your neck, and then ... nothing.","You don't want to chitchat with Count Dracula!","That is truly crazy!","You have no way of killing Count Dracula. You are in mortal danger!","You don't have time! Run for your life!","Count Dracula is terrified of the cross. He transforms into a bat and flies away."];