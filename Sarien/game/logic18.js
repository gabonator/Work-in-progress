window.logic18=function()
{while(1){switch(B)
{case 0:if(E(DT)){CX(11);CX(21);CX(32);CY(15);CY(16);CY(94);CY(17);CY(93);CY(91);BY(156);if(AGI.C)return;BY(159);if(AGI.C)return;CW(Ck);BJ(Ck);BF(156);if(AGI.C)return;m(o2);m(o3);m(o4);p(o4,15);p(Ego,0);p(o2,16);p(o3,16);w(o4,0);AC(o4,5);AG(o4,68,142);AG(o2,67,130);AG(o3,73,115);AG(Ego,49,166);L(v94,2);AS(o4,v94);AS(o2,v94);AS(o3,v94);if(J(Cl,61)){AG(Ego,71,146);r(Ego,2)}
AY(Ego);AJ(Ego);AJ(o4);AN(o4);if(E(f126)){AJ(o2);AJ(o3)}
BM();if(E(f126)){Bg("There are two spooky ghosts guarding the door of the gloomy castle. This situation looks bad.");Am(o2,10,f30);An(o3);BN(11,f40)}}
if((!E(DQ)||E(f32)||E(f36)||E(f37))){A(4);break}
if((D("check out","antique shop")||D("check out"))){Bg("The castle looks cold and forbidding. Two dark towers rise on either side of it. The castle is surrounded by deadly thorns and brambles.")}
if(D("check out","door")){Bg("The heavy wooden door of the castle is closed.")}
if(D("check out","island")){Bg("There is a dark castle set in the middle of the dismal island. Thorns and brambles grow everywhere. The stink of the foul lake is oppressive.")}
if(BT("Oil Lamp")&&D("pat","lamp")){Bg("You rub and rub, but nothing happens!")}
if(BT("Carpet")&&D("anyword","carpet")){Bg("Evil forces prevent you from doing that.")}
if(!E(f126)){A(1);break}
if(D("check out","ghost")){Bg("These ghostly apparitions guard an evil being lurking within the castle walls.")}
if((D("capture","ghost")||D("acquire","ghost"))){Bg("Are you kidding!? How do you capture a ghost?")}
if(D("kill","ghost")){Bg("Don't you know that spooks are already dead?")}
if((D("speak","ghost")||D("hello","anyword")||D("say","hello"))){Bg("When you speak to the ghosts they utter a mournful wail.")}
case 1:if(E(f126)){if(D("anyword","door")){Bg("The ghosts won't let you reach the door.");A(3);break}}
if((D("open","door")||D("knock","door"))){BC(Ego,o4,v41);if(N(v41,15)){Bg("Your arms won't reach.");A(3);break;A(2);break}
G(DS);if(D("knock","door")){Bg("When you knock on the wooden door of the castle, the sound echoes inside. There is no answer.");A(2);break}
BN(21,f169);AQ(o4,f33);F(DS)}
case 2:if(D("anyword","tree")){Bg("There are no trees on this island. Only brambles and thorns.")}
case 3:if(D("give","anyword")){Bg("The spooks want nothing but you gone!")}
case 4:if(E(f30)){G(f30);if(E(f68)&&E(f70)){Bg("The two spirits are fooled by the black cloak and the large ruby ring that you are wearing. They slowly float away.... Maybe you remind them of someone else.");A(6);break;A(5);break}
if(E(f69)){Bg("The two spirits are afraid of the silver cross you are wearing around your neck. They slowly float away and disappear.");A(6);break;A(5);break}
G(f126);F(f32);Bg("Oh, no! The two spooks float toward you and enter your body. In a trance, you walk toward the thorn covered brambles.");Ad();F(f45)}
case 5:A(7);break;case 6:G(f126);p(o2,17);p(o3,17);AQ(o2,f38);AQ(o3,f169);A(7);break;case 7:if(E(f32)){G(f32);p(o2,17);w(o2,0);p(o3,17);w(o3,0);AQ(o2,f38);AQ(o3,f169);Ah(Ego);Ad();p(Ego,93);L(v94,2);AS(Ego,v94);F(f92);w(Ego,0);AQ(Ego,f36)}
if(E(f36)){G(f36);F(f37);p(Ego,94);L(v94,3);AS(Ego,v94);AL(Ego,v67,v68);L(v67,0);if(P(v68,146)){L(v68,146)}
if(N(v66,0)){L(v54,0);L(v66,2)}
L(v41,0);Al(Ego,v67,v68,v41,f31);AY(Ego)}
if(E(f37)&&!E(f31)){AL(Ego,v67,v68);if(P(v68,146)&&K(v67,v42)&&K(v68,v43)){W(v43,1);L(v67,0);L(v68,1);Aw(Ego,v67,v68);Ag(Ego);A(8);break}
M(v42,v67);M(v43,v68)}
case 8:if(E(f44)){G(f44);Az(o3);Az(o2)}
if(E(f38)){G(f38);F(f44);AC(o3,4);AC(o2,4)}
if(E(f33)){if(!E(f45)){H(61);if(AGI.C)return}}
if(J(Cm,3)){AZ(Ego);H(25);if(AGI.C)return}
if(E(f126)&&E(f41)){BN(32,f41)}
if(E(f40)){G(f40);F(f41)}
BF(156);if(AGI.C)return;BF(159);if(AGI.C)return;return}}}
MESSAGES[18]=["","The castle looks cold and forbidding. Two dark towers rise on either side of it. The castle is surrounded by deadly thorns and brambles.","The heavy wooden door of the castle is closed.","These ghostly apparitions guard an evil being lurking within the castle walls.","There is a dark castle set in the middle of the dismal island. Thorns and brambles grow everywhere. The stink of the foul lake is oppressive.","There are two spooky ghosts guarding the door of the gloomy castle. This situation looks bad.","The two spirits are fooled by the black cloak and the large ruby ring that you are wearing. They slowly float away.... Maybe you remind them of someone else.","The two spirits are afraid of the silver cross you are wearing around your neck. They slowly float away and disappear.","Oh, no! The two spooks float toward you and enter your body. In a trance, you walk toward the thorn covered brambles.","Are you kidding!? How do you capture a ghost?","Don't you know that spooks are already dead?","When you speak to the ghosts they utter a mournful wail.","When you knock on the wooden door of the castle, the sound echoes inside. There is no answer.","The ghosts won't let you reach the door.","Your arms won't reach.","There are no trees on this island. Only brambles and thorns.","The spooks want nothing but you gone!","You rub and rub, but nothing happens!","Evil forces prevent you from doing that."];CONTROLS[18]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4.x><*.r.x5><x5.x.!5><r5.x.!5><l5.!.^5><g5.!.^5><Z5.^.+5><U5.^.+5><P5.+.+5><P5.+.{5><E5.{.{5><E5.{.,5><45.,.,5><45.,<45>.{5<4<45>.+5<9<45>.+5<9<95>.!5<E<95>.!5<E<E5>.r5<K<E5>.r5<K<K5>.g5<P<K5>.g5<P<K5>.Z5<U<P5>.U5<U<P5>.P5<Z<U5>.K5<Z<U5>.E5<g<Z5>.95<g<Z5>.45<l<Z5>,5<r<g5>{5<r<g5>+5<x<l5>^5<x<l5>!5<!<r5>x5<!<r5>r5<^<r5>r5<^<x5>g5<+<x5>g5.9V.Z<!5>U5.9AP5.Z<!5>U5.4595P5.Z<^5>K5.45E5P5.Z<^5>E5.95E5P5.Z<^5>E5.45K5P5.Z<+5>45.45P5P5.Z<+5>45,5U5P5.Z<{5<.{5,5Z5P5.Z<{5<.{5+VK5P5.Z<,5<.^5{5P5K5P5.Z<,5<.^5+AP5K5P5.Z<,5<.!5{AP5K5P5.Z<.45<.x5+595P5K5P5.Z<.45<.r5+5E5P5K5P5.Z<.95<.l5^5K5P5K5P5.Z<.95<.g5^5P5P5K5P5.Z<.E5<.U5^5U5P5K5P5.Z<.E5<.U5!5Z5P5K5P5.Z<.E5<.P5!5gVK5P5.Z<rQEL<.K5!5g5P5K5P5.Z<Z5E5K5E5E5<.E5xVP5P5K5P5.Z<Z5E5K5E5EA<.95x5P5P5P5K5P5.Z<Z5E5K5E5EAEQ<r5xAP5P5P5K5P5.Z<Z5E5K5E5E59595K5<r5r595P5P5P5K5P5.Z<Z5E5EAE5E59595K5<l5r5E5P5P5P5K5P5.Z<Z5E5957LE59595K5<l5l5K5P5P5P5K5P5.Z<Z5EANAE5EAK5<g5l5P5P5KaK5P5.Z<Z5EAXFEAK5<g5l5P5P@E5P5.Z<Z5E5jAK5K5<Z5l5UVx5E5P5.U5<Z595u5K5K5<Z5g5KL.4595P5.U5<ZA`5KAE5<U5gQ.K5E5P5.PA<Z5)5EAE5<P5gA.Z5K5P5.KF<Z5)5EAE5<P5Z5.ZFK5P5PF!L<U5[5E59595<K5Z5{mE5K5P5KLPLKL<P5.25959595<K5U5,5E5K5K5K5P5KLPQ9Q<K5.7595EA<E5U5.45E5K5K5K5P5KLK@<E5.HAEA<E5P5.45K5K5K5K5gQKF9h<E5.HAK5<95P5.95K5K5K5K5UaKA9m<95.S5K5<95K5.E5K5K5K5K5KhPA9m<45.c5E5<45EA^NK5K5KF9QKhP59s.,5.p59A.,595^CPN5E5K5EAZmUy.{5.u9F.{595^79SUF9FPFKmUy.{5.cU595.+A!CE7K7gAK5ZA9mUy.+5.SrA.!A6!CK7K7KSULPyPy.^5.S!65.^6x797K7K7K7K7ZFK@K@.!5.N+65.^6x797K7K7K7K7KNF9*E*.!5.S^6.+6r7E7K7K7K7K7K7E79}E=.x5.c!6.+6r7E7K7K7K7K7K7E79a9aE=.r5.px6.+6l7K7K7K7K7K7K7E7EV9VK=.l5.C.E6.+6l7K7K7K7K7K7K7E7EV9VK=.g5.C.K6.+6gN9SK7K7K7K7E7EV9Q95E=.g5.2.U.|!XK7K7K7K7E7EQKVE=.Z5.C>PNK7K7K7E7KLP.Q.U5.H>U797K7K7K7E7KLP.Q.P5.S>ECE7K7K7K7E7KLU.L.K5.X>97P7K7K7K7E7KA9AP.L.K5.N>E797K7K7K7K7E7K759AU.F.E5.H>P797K7K7K7K7E7K759AU.F.95.C>U7E7K7K7K7K7E7K7QP.F.45.H>U7E7K7K7K7K7E7K79LK.L,5.H>Z7E7K7K7K7K7E7K79QE.L,5.C>Z7K7K7K7K7K7E7K79Q9.Q{5.H>Z7K7K7K7K7K7E7K79QE.L+5.H>g7K7K7K7K7K7E7K7EQ9.L^5.N>Z7KN97K7K7K7E7K7EQ9.L!5.N>gNE7E7K7K7K7E7K7EQE.F!5[9N>^CK7K7K7K7E7K7E.sx5:K7>^7U7K7K7K7E7K7K.mr5.2>,7ZSKSESK.m";