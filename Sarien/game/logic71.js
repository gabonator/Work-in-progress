window.logic71=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
if(!(E(f100))){A(501);break}
G(f34);G(f32);A(1);break;case 501:F(f34);F(f32);case 1:CW(Ck);BJ(Ck);Bu(Ck);CX(6);CY(101);CY(91);if(!(!E(f100))){A(502);break}
CY(75);m(o2);L(v94,3);AS(o2,v94);p(o2,75);w(o2,0);AG(o2,70,81);case 502:if(!(!E(f100))){A(503);break}
AJ(o2);AN(o2);case 503:AG(Ego,70,167);L(Cr,1);AJ(Ego);BM();BN(6,f169);case 500:if((!E(DQ)||E(DS))){A(8);break}
if(!(!E(DS)&&E(f38)&&D("anyword","anyword"))){A(504);break}
if(!(E(f37))){A(505);break}
if(!((D("pray","anyword")||D("pray")))){A(506);break}
Bg("You already are.");A(2);break;case 506:Bg("Please be quiet while praying.");case 2:A(3);break;case 505:if(!((D("pray","anyword")||D("pray")))){A(507);break}
G(DS);A(3);break;case 507:if(!(D("bow","anyword"))){A(508);break}
Bg("You already are.");A(3);break;case 508:Bg("You should not talk while kneeling at the altar. It shows a lack of respect.");case 3:if(!(E(DS))){A(509);break}
case 509:case 504:if((D("check out","antique shop")||D("check out")||D("check out","area"))){if(E(f100)){Bg("The chapel of the monastery is plain and unadorned. Rows of pews lead toward an altar, which is topped by a large cross.");A(4);break}
if(!E(f32)){Bg("The chapel of the monastery is plain and unadorned. A monk in simple clothing is standing next to the altar. He looks kindly at you.");A(4);break}
Bg("The chapel of the monastery is plain and unadorned. A monk in simple clothing is bent in prayer toward the cross on the altar.")}
case 4:if(!BT("Cross")&&(D("check out","cross")||D("look up","cross"))){Bg("The wooden cross is plain and simple. An altar of polished oak supports it.")}
if(D("check out","altar")){Bg("There is a large wooden cross atop the oaken altar.")}
if(!(!BO(Ego,50,81,92,83)&&(D("bow","anyword")||D("pray","anyword")||D("pray")))){A(510);break}
if(!(E(f34))){A(511);break}
Bg("Come, join me at the altar, my friend, says the monk.");A(5);break;case 511:Bg("Shouldn't you go to the altar to pray?");case 5:A(6);break;case 510:if((D("pray")||D("pray","anyword"))){if(!E(f154)){F(f154);W(Cn,2)}
AM(Ego);F(f92);Bg("You kneel near the altar. Bowing your head, you pray.");F(f37);if(!E(f38)){p(Ego,101);AQ(Ego,f31);L(v94,4);AS(o2,v94)}
F(f38);F(f36)}
if(D("bow","anyword")){AM(Ego);F(f92);Bg("You kneel near the altar. You look up at the wooden cross.");p(Ego,101);L(v94,4);AS(o2,v94);AQ(Ego,f31);F(f38)}
case 6:if(BT("Cross")&&D("acquire","cross")){Bg("You already have a cross.")}
if(!E(f34)){if(D("anyword","count dracula")){Bg("You are the only one in the chapel.")}
A(9);break}
if(D("check out","count dracula")){Bg("The monk is dressed in a simple ankle-length robe. A belt of thin leather is tied around his ample waist. He walks on worn sandals.")}
if((D("acquire","count dracula")||D("capture","count dracula"))){Bg("What do you think you would accomplish by doing that?")}
if(D("kill","count dracula")){Bg("Anyone who would kill a man of the cloth doesn't deserve to play this game. Therefore, we will end it.");p(Ego,91);F(f50)}
if((D("speak","count dracula")||D("hello","anyword")||D("say","hello"))){if(E(f32)){Bg("You speak to the praying monk but he does not respond. He seems deep in worship.");A(7);break}
Bg("Can I be of service? the monk asks. What name do you go by?")}
case 7:if(D("yell","count dracula")&&E(f32)){Bg("You shout at the praying monk. He pays no attention. The monk is deep in prayer.")}
if(!E(f100)&&!E(f32)&&(D("graham")||D("my name","graham"))){Bg("The kindly monk explains that he has heard of you and your quest. Here is my cross. It will protect you from evil, he says. He removes a chain with a silver cross from around his neck and gives it to you. The monk then resumes his prayers.");BS("Cross");W(Cn,2);AR(o2,f169);F(f100);F(f32);G(f33)}
if(D("sit","anyword")){Bg("You don't have time to sit around.")}
if(D("pat","count dracula")){BC(Ego,o2,v94);if(N(v94,20)){Bg("Your arms will not reach.");A(8);break}
Bg("You tap the monk on his shoulder but it does no good. He is very deep in prayer.")}
case 8:if(E(f33)&&E(f32)&&!E(f100)){AM(o2);AQ(o2,f169);Bg("The plump monk lifts his head from prayer and seems to notice you for the first time. He stands and asks your name.");G(f32)}
case 9:if(E(f31)){G(f92);G(f31);L(v58,30)}
if(N(v58,0)){AN(Ego)}
U(v58);if(J(v58,1)){F(f92);AR(Ego,f35)}
if(E(f35)){G(f35);G(f92);G(f37);G(f38);p(Ego,0);L(v94,1);AS(o2,v94);r(Ego,3);Ac();if(E(f36)){F(f33);G(f36)}}
if(J(Cm,3)){H(6);if(AGI.C)return}
return}}}
MESSAGES[71]=["","The chapel of the monastery is plain and unadorned. Rows of pews lead toward an altar, which is topped by a large cross.","The chapel of the monastery is plain and unadorned. A monk in simple clothing is bent in prayer toward the cross on the altar.","The chapel of the monastery is plain and unadorned. A monk in simple clothing is standing next to the altar. He looks kindly at you.","The monk is dressed in a simple ankle-length robe. A belt of thin leather is tied around his ample waist. He walks on worn sandals.","What do you think you would accomplish by doing that?","Anyone who would kill a man of the cloth doesn't deserve to play this game. Therefore, we will end it.","You speak to the praying monk but he does not respond. He seems deep in worship.","Can I be of service? the monk asks. What name do you go by?","Please be quiet while praying.","You shout at the praying monk. He pays no attention. The monk is deep in prayer.","There is a large wooden cross atop the oaken altar.","The wooden cross is plain and simple. An altar of polished oak supports it.","You kneel near the altar. You look up at the wooden cross.","You kneel near the altar. Bowing your head, you pray.","The plump monk lifts his head from prayer and seems to notice you for the first time. He stands and asks your name.","The kindly monk explains that he has heard of you and your quest. Here is my cross. It will protect you from evil, he says. He removes a chain with a silver cross from around his neck and gives it to you. The monk then resumes his prayers.","You are the only one in the chapel.","Come, join me at the altar, my friend, says the monk.","It doesn't work. The monk is deep in prayer.","You don't have time to sit around.","You tap the monk on his shoulder but it does no good. He is very deep in prayer.","Shouldn't you go to the altar to pray?","Your arms will not reach.","You should not talk while kneeling at the altar. It shows a lack of respect.","You already are.","You already have a cross."];CONTROLS[71]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4<Z.m<4.s<g<Z5.g5<45.l5<g<U5.g5<E5.l5<Z<U5.g5<E5.l5<Z<U5.g5<E5.l5<Z<P5.g5<K5.r5<U<P5.g5<P5.l5<U<P5.Z5<U5.r5<P<K5.g5<U5.r5<P<K5.g5<Z5.l5<P<E5.g5<g5.r5<K<E5.g5<g5.r5<K<E5.g5<g5.r5<K<95.l5<g5.x5<E<95.l<m.x5<E<95>.!5<E<45>.+5<9<45>.+5<9<45>.{5<4.,5>.,5<4.,5>.,5<4.,5><45.,.{5><95.,.{5><95.,.+5><K5.{.+5><K5.{.+5><P5.+.^5><U5.+.^5><U5.+.^5><Z5.^.!5><g5.^.!5><g5.^.!5><l5.!.x<}{<=.!.x5<+5{5<^5.!.x5<+5{5<+5.x.r5<{5{5<+5.x.r5<{5,5<+5.r.l5<{5.45<+5.r.l5<{5.45<+5.r.l5<{5.45<{5.l.g59<}.4<.0.l.g5><,5.l.g5><.45.g.Z5><.95.g.Z5><.95.g.Z<.5.E<.5.Z.U5<.45.E5<,5.Z.U5<.45.E5<.45.U.U5<.45.E5<.45.U.P5<.95.E5<.45.U.P5<.95.E5<.95.P.K5<.E5.E5<.95.P.K<.L.E<.F.P.K5><.l5.K.E5><.r5.K.E5><.x5.E.E5><.x5.E.9<.Q.P<.L.E.95<.K5.P5<.K5.9.95<.K5.P5<.K5.9.45<.P5.P5<.K5.9.45<.P5.P5<.P5.4.45<.P5.P5<.P5.4,5<.U5.P5<.P5.4,<.a.P<.a,{5/95,{5/E5{{5/E5{+5/K5{+<.h.Z<.h++5<.Z5.Z5<.Z5+^5<.g5.Z5<.Z5+^5<.g5.Z5<.g5^^5<.g5.Z5<.g5^!5<.l5.Z5<.g5^!5<.l5.g5<.g5!!<.s.g<.m!x5/x5xx5/x5xr5/!5xr<.y.l<.yrr5<.r5.l5<.r5rl5<.x5.l5<.r5rl5<.x5.l5<.x5ll5<.x5.l5<.x5lg5<.!5.r5<.x5gg5<.!5.r5<.x5gg5<.!5.r5<.x5gZ<.=.r<.*ZZ5/.E5ZZ5/.E5ZU<.=.x<.=UU5<.^5.x5<.^5UP5<.+5.x5<.^5UP5<.+5.x5<.+5PP5<.+5.x5<.+5PK5<.{5.x5<.{5KK5<.{5.x5<.{5KK5<.{5.x5<.{5KE5<.,5.x5<.,5EE5<.,5.x5<.,5E";