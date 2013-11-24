window.logic56=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
BY(165);if(AGI.C)return;BY(164);if(AGI.C)return;if(!((BT("Oil Lamp")||BT("Carpet")))){A(501);break}
CY(65);CY(98);case 501:CY(66);CY(46);CY(47);CY(44);CY(45);CY(91);CY(8);CW(Ck);BJ(Ck);BF(165);if(AGI.C)return;BF(164);if(AGI.C)return;m(o3);L(v94,3);AS(o3,v94);AU(o3);AG(o3,115,100);if(!(!E(f136))){A(502);break}
AL(Ego,v105,v106);if(!(P(v106,50))){A(503);break}
L(v106,50);A(1);break;case 503:if(!(N(v106,148))){A(504);break}
L(v106,148);case 504:case 1:AH(Ego,v105,v106);case 502:AJ(Ego);if(!(!E(f108)&&!E(f109)&&!E(f110))){A(505);break}
p(o3,44);F(f31);A(2);break;case 505:if(!(E(f108))){A(506);break}
Aa(Ego);p(o3,66);AC(o3,5);A(2);break;case 506:if(!(E(f109)&&!E(f110))){A(507);break}
p(o3,46);F(f32);case 507:case 2:if(!(!E(f110))){A(508);break}
AJ(o3);case 508:BM();if(!(!E(f108)&&!E(f109)&&!E(f110))){A(509);break}
Bg("Look out! There is a poisonous viper blocking your path!");case 509:case 500:if(D("check out","snake")){if(E(f31)){Bg("The snake appears to be about ten feet long. It is coiled and ready to strike.");A(3);break}
if(E(f108)){Bg("The huge snake is deceased.");A(3);break}
Bg("There is no snake here!")}
case 3:if(E(f31)&&!E(f35)&&!E(f136)&&!E(f125)&&BO(Ego,100,80,111,115)){F(f35);F(f179);p(o3,45);AQ(o3,f34)}
if(E(f34)){G(f34);p(Ego,91);Bg("The snake has struck you dead.");F(f50)}
if((!E(DQ)||E(DS)||E(f35))){A(12);break}
if(!E(f32)&&(D("speak","snake")||D("hello","anyword")||D("kiss","snake")||D("say","hello"))){if(E(f31)){Bg("SSSsssssss! SSssstay away or I will ssssssstrike!");A(4);break}
if(E(f108)){Bg("The huge snake is deceased.");A(4);break}
Bg("There is no snake here!")}
case 4:if(!E(f109)&&(D("acquire","snake")||D("capture","snake"))){if(E(f31)){Bg("Are you joking!");A(5);break}
Bg("Why would you want a dead snake? Ugh!!")}
case 5:if(E(f31)&&(D("feed","snake")||D("feed","anyword","snake"))){Bg("The serpent only wants to eat YOU!")}
if(!E(DS)&&E(f31)&&(D("feed","anyword")||D("give","anyword"))){Bg("The snake has no use for it. He is interested in only one thing. Getting rid of YOU!")}
if(!(D("kill","snake"))){A(510);break}
if(!(!BO(Ego,71,72,107,120))){A(511);break}
Bg("You are too far away.");A(7);break;case 511:if(!(E(f31))){A(512);break}
if(!(BT("Sword"))){A(513);break}
Aa(Ego);Bg("Brandishing the sharp sword, you quickly slash the viper into ribbons.");F(f108);G(f31);AC(o3,5);p(o3,66);W(Cn,2);A(6);break;case 513:Bg("This is a very large snake. You don't have any weapons strong enough to kill it.");case 6:A(7);break;case 512:Bg("The huge snake is deceased.");case 510:case 7:if(E(f37)&&D("snake")){A(8);break}
G(f37);case 8:if(!((D("cast","bridle","snake")||D("drop","bridle","snake")||E(f37)))){A(514);break}
G(f37);if(!(!BO(Ego,71,72,137,120))){A(515);break}
Bg("You are too far away.");A(10);break;case 515:if(!(E(f31))){A(516);break}
if(!(BT("Bridle"))){A(517);break}
CL("Bridle");W(Cn,5);p(o3,46);G(f31);F(f109);F(f32);Bg("You toss the leather bridle onto the coiled snake. Instantly, there stands before you not a snake, but a beautiful winged horse wearing the bridle!");A(9);break;case 517:Bg("You don't have it.");case 9:A(10);break;case 516:if(!(BT("Bridle"))){A(518);break}
Bg("You put the bridle on the dead snake. Nothing happens. You pick the bridle up again.");A(10);break;case 518:Bg("The huge snake is deceased.");case 10:A(11);break;case 514:if(D("cast","bridle")){Bg("Where do you want to throw the bridle?");F(f37)}
case 11:if(!E(f32)){A(12);break}
if(E(f110)&&(D("anyword","flying horse")||D("anyword","anyword","flying horse"))){Bg("The horse is flying away, and pays no attention to you.");A(12);break}
if(D("check out","flying horse")){Bg("This is a handsome white horse! It has beautiful wings of delicate white feathers. The leather bridle is around the winged horse's head.")}
if(D("speak","flying horse")){Bg("\"Thank you, kind sir, for saving me. An evil enchanter turned me into a snake when I refused to be his steed. To repay you, here is a magic sugar cube that will guard against poisonous brambles.\"");BS("Sugar Cube");W(Cn,2);F(f110);AC(o3,15);Aa(o3);L(v94,2);Ai(o3,v94);p(o3,47);Ak(o3,115,60,0,f36)}
if((D("get on","flying horse")||D("sit","flying horse"))){Bg("The winged horse has a very independent nature. It doesn't want a rider on its back.")}
if((D("acquire","flying horse")||D("capture","flying horse"))){Bg("The white horse is much too big and strong for you to hold it.")}
if(D("kill","flying horse")){Bg("Why would you want to kill a beautiful horse like that?")}
if((D("feed","flying horse")||D("feed","anyword","flying horse"))){Bg("The flying horse is not particularly hungry, thank you.")}
if(D("pat","flying horse")){Bg("The beautiful white horse lets you stroke its velvety soft nose.")}
if((D("hello","anyword")||D("say","hello"))){Bg("The flying horse bobs its head up and down in greeting.")}
case 12:if(J(Cm,4)){p(Ego,0);H(55);if(AGI.C)return}
if(J(Cm,2)){H(57);if(AGI.C)return}
if(E(f33)){G(f33);G(f32);AK(o3)}
if(E(f36)){G(f36);Ak(o3,0,60,0,f33)}
BF(165);if(AGI.C)return;BF(164);if(AGI.C)return;return}}}
MESSAGES[56]=["","Look out! There is a poisonous viper blocking your path!","The snake appears to be about ten feet long. It is coiled and ready to strike.","The huge snake is deceased.","SSSsssssss! SSssstay away or I will ssssssstrike!","Are you joking!","The serpent only wants to eat YOU!","Brandishing the sharp sword, you quickly slash the viper into ribbons.","This is a very large snake. You don't have any weapons strong enough to kill it.","You toss the leather bridle onto the coiled snake. Instantly, there stands before you not a snake, but a beautiful winged horse wearing the bridle!","Where do you want to throw the bridle?","You don't have it.","This is a handsome white horse! It has beautiful wings of delicate white feathers. The leather bridle is around the winged horse's head.","\"Thank you, kind sir, for saving me. An evil enchanter turned me into a snake when I refused to be his steed. To repay you, here is a magic sugar cube that will guard against poisonous brambles.\"","The winged horse has a very independent nature. It doesn't want a rider on its back.","The white horse is much too big and strong for you to hold it.","Why would you want to kill a beautiful horse like that?","The flying horse is not particularly hungry, thank you.","The beautiful white horse lets you stroke its velvety soft nose.","The flying horse bobs its head up and down in greeting.","The snake has struck you dead.","There is no snake here!","You are too far away.","The snake has no use for it. He is interested in only one thing. Getting rid of YOU!","Why would you want a dead snake? Ugh!!","You put the bridle on the dead snake. Nothing happens. You pick the bridle up again.","The horse is flying away, and pays no attention to you."];CONTROLS[56]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4><.P6<!><.P6<!><.P6.x6.4><.P6.x6.44X.r.p<.^6.x6ljZurX.r.7{.)6.x6jl.4p<.4[.+6.r6.9>.{6.U6.l6.E>ZR.9B9G.E6.l6.E>U6U6{BZB.96.Z6.K>P6g6+6r6.46.U6.P>K6r6!6!6{6.PB.U>E6!6x6!6{6.4M.g>96!6!6!6+6.96.x>E6r6^6!6^6.E6.x>E6gB+6rB+6.E6.x>KBKB.46ZB{6.K6.x>UG.E6EM,6.P6.x>.xG.E6.P6.!><,6.K6.^><{6.K6.+><{6.9B.{><+6.4B<4>!W.^6,6<E>rBK6Eb.P6,6<K>gB96K6P6KM.96,6<K<.^MUGE6K6P6K6E6.46{B<P<.xGKRE6E6K6P6K6E6.46!G<Z<.lBE6PbE6K6P6K69B,6xB<r<.rB969GZMK6P6KB.46x6<!<.!G^RP69B.E6r6<^>{GEB.K6r6<+>.9G.K6r6<{><UBx6<{><9M^6<{>.,BE6{6<+>.{6P6{6<+>.^GP6KRKW<!>.!6E6P6K6K6K6KB<!>.x6K6P6K6K6K6PG<r>.r6P6P6K6K6K6P6E6<l>.x6K6P6K6K6K6PG<r>.!6E6P6K6KREG<!>.^iK6K6KG<{><KRE6<.U><gG<.Z?4?4.,i><.r.PzK6KM><.Z{WZRK6K6KB><.P{6!6K6K6K6P6><.P,6x6K6K6K6KB><.P.4Bl6EM96KM><.Z.E6gGPR<.{G<.r.KBPB>ZGKB<.g.UM>g6l6<.Z>.,6x6<.U>.,6!6<.P>.{6^6<.P>.+6{6<.K>.!B,6<.K>.x6.E6<.E>.x6.E6<.E>.x6.K6<.9>.x6.K6<.9>.rB.P6<.4>.rB.P6<.4>.rB.U6<,>.rB.U6<,<.+n.E696.Z6<{<.^69WEB{BE6.Z6<{<.xBE6P6P6^6P6.g6<+<.r6P6P6U6rBU6.l6<^<.r6P6P6KBlB96U6.r6<!<.r6P6P69BlBK6U6.x6<x<.l6U6PBlB96K6U6.!6<r<.l6U6P6gBK6K6U6.^6<l<.l6U6P6Z696K6K6U6E6.x6<g<.r6P6K6Z6E6K6K6U6E6.x6<g<.x6K69Bg6E6K6K6U6E6.!6<Z<.!6EBl6K6K6K6U6E6.^6<U<.^Bx6K6K6K6U6E6.^6<U>r6E6K6K6U6E6E6.x6<P>r6E6K6K6U6E6E6.x6<P>xGK6K6U6E6E6.x6<P>^RKbE6E6.x6<P>.4RUME6P6P6K6^6<P>.+6E6P6P6K6^6<P>.{696P6P6K6^6<P>.,BP6P6K6^i.+><46P6P6K6.P6.^><96K6P6K6.U6.!><E6E6P6K6.U6.!><E6E6P6K6P6.96.x><E6E6P6K6P6.E6.r<.^N<E6E6P6K6P6.K6.l<.!7Pj.x6E6KWP6.K6.l<.!7^)+6E69BPBP6.P6.g<.x7.xH!MZBP6.U6.Z<.x7.+7^6Z696P6.Z6.U<.x7.+7.K696P6.g6.P<.x7.{7.E696P6.lB.E<.r7<47.EBP6.x6.9<.r7<97.E6P6.!6.4KS<.97<97.E6P6.^6,4HUC<+C<K7.E6K6.+6{xH.xXr7<ZC.96E6.{6++C.9cZp<rC.4696.{6+,.7>9C{696.{6+><K[696.,6$><.9696.,6^><.96<{><.96<{?4?4?4?4?4?4?4?4?4?4";