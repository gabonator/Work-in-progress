window.logic32=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
if(!(E(f75))){A(501);break}
CY(24);CY(23);case 501:CY(92);CY(104);CY(91);if(!((BT("Oil Lamp")||BT("Carpet")))){A(502);break}
CY(65);CY(98);case 502:F(f64);BY(156);if(AGI.C)return;BY(101);if(AGI.C)return;CW(Ck);BJ(Ck);BF(156);if(AGI.C)return;BF(101);if(AGI.C)return;if(!(E(f75))){A(503);break}
if(!((J(Cl,25)||!E(f138)))){A(504);break}
m(o3);case 504:case 503:L(v94,3);AS(o3,v94);AY(Ego);if(!(J(Cl,25))){A(505);break}
L(v95,2);AG(Ego,88,140);p(o3,23);AG(o3,69,70);F(f176);Ak(o3,88,126,0,f34);p(Ego,104);L(v94,2);AS(Ego,v94);r(o3,0);AC(o3,4);AJ(o3);A(2);break;A(1);break;case 505:F(f35);case 1:if(!(E(f75)&&!E(f138))){A(506);break}
F(f36);p(o3,24);r(o3,0);w(o3,0);AG(o3,88,126);AJ(o3);Az(o3);case 506:case 2:if(!(!J(Cl,25))){A(507);break}
AJ(Ego);case 507:BM();case 500:if(!E(DO)){if((BO(Ego,0,62,38,121)||BO(Ego,126,77,156,118))){F(DO);F(f116)}}
if((!E(f35)||!E(DQ)||E(DS))){A(13);break}
if((D("check out","area")||D("check out"))){if(E(f36)){Bg("%m18 A shrouded figure stands silent.");A(3);break}
Bg("The lake is foul and stinking! It may be poisoned. All vegetation looks dead around it. There is a desolate island in the middle of the poisoned lake.")}
case 3:if(!E(f36)){A(12);break}
if(D("check out","boat")){Bg("The small wooden rowboat looks old and rotted from traversing the poisoned lake.")}
if(D("check out","count dracula")){Bg("The shrouded ghoul looks very frightening. His hands are little more than claws, and his face is completely hidden inside the hood of the shroud. He is standing in a small boat.")}
if(E(f76)){F(f31)}
if(E(f68)&&E(f70)){F(f31)}
if(!E(f31)&&(D("enter","boat")||D("climb","boat")||D("get in","boat")||D("board","boat")||D("get on","boat"))){Bg("The spooky fiend holds out a bony claw, as if in request for a payment of some kind.")}
if(!(E(f31)&&(D("enter","boat")||D("climb","boat")||D("get in","boat")||D("board","boat")||D("get on","boat")))){A(508);break}
BC(Ego,o3,v94);if(!(N(v94,15))){A(509);break}
Bg("You are too far away.");A(5);break;case 509:if(!(E(f70)&&E(f68))){A(510);break}
Bg("The shrouded ghoul looks at the ruby ring on your finger and the black cloak around your neck. He motions for you to enter the boat, which you do. You must have fooled him into thinking you were someone else.");A(4);break;case 510:Bg("You climb carefully into the old boat. The shrouded ghoul paddles it across the lake to the ominous island.");case 4:G(f35);F(f176);AK(Ego);Ad();BA(o3);p(o3,23);r(o3,1);AM(o3);F(f147);Ak(o3,69,74,0,f32);case 508:case 5:if((D("speak","count dracula")||D("hello","anyword")||D("anyword","hello"))){Bg("You are greeted by stony silence from the frightening ghoul.")}
if(D("acquire","boat")){Bg("The ghoul will not let you take the boat.")}
if(D("kill","count dracula")){Bg("You can't kill something that is already dead.")}
if((D("acquire","count dracula")||D("capture","count dracula"))){Bg("It is impossible to catch a ghoul.")}
if((D("give","treasure","count dracula")||D("give","count dracula","treasure")||D("give","treasure"))){Bg("Which treasure would you like to give the ghoul?");A(13);break}
if((D("give","diamond and sapphire necklace","count dracula")||D("give","count dracula","diamond and sapphire necklace"))){if(BT("Necklace")){CL("Necklace");A(11);break;A(6);break}
Bg("You don't have it.");A(13);break}
case 6:if((D("give","bracelet","count dracula")||D("give","count dracula","bracelet"))){if(BT("Bracelet")){CL("Bracelet");A(11);break;A(7);break}
Bg("You don't have it.");A(13);break}
case 7:if((D("give","diamond and sapphire tiara","count dracula")||D("give","count dracula","diamond and sapphire tiara"))){if(BT("Tiara")){CL("Tiara");A(11);break;A(8);break}
Bg("You don't have it.");A(13);break}
case 8:if((D("give","earrings","count dracula")||D("give","count dracula","earrings"))){if(BT("Earrings")){CL("Earrings");A(11);break;A(9);break}
Bg("You don't have it.");A(13);break}
case 9:if((D("give","brooch","count dracula")||D("give","count dracula","brooch"))){if(BT("Brooch")){CL("Brooch");A(11);break;A(10);break}
Bg("You don't have it.");A(13);break}
case 10:if((D("give","diamond and sapphire tiara")||D("give","bracelet")||D("give","earrings")||D("give","brooch")||D("give","diamond and sapphire necklace"))){Bg("You must specify who you wish to give it to.");A(12);break}
if((D("give","anyword","count dracula")||D("give","count dracula","anyword"))){Bg("The silent fiend slowly shakes his head. He is not interested in it.")}
A(12);break;case 11:Bg("The shrouded ghoul takes your treasure. Silently, he gestures toward the boat.");BA(o3);AQ(o3,f33);F(f76);Y(Cn,7);case 12:if((D("check out")||D("check out","area"))){}
case 13:if(E(f34)){L(v95,0);G(f176);G(f34);p(o3,24);AG(o3,88,126);r(o3,0);w(o3,0);L(v94,1);AS(Ego,v94);p(Ego,0);AJ(Ego);F(f35);F(f36);AN(o3);G(f76)}
if(E(f32)){G(f147);AE(o3);H(25);if(AGI.C)return}
if(E(f33)){G(f33);AR(o3,f169)}
if(!J(Cm,0)){G(f64)}
if(J(Cm,1)){H(25);if(AGI.C)return}
if(J(Cm,2)){H(33);if(AGI.C)return}
if(J(Cm,4)){H(31);if(AGI.C)return}
if(J(Cm,3)){H(39);if(AGI.C)return}
BF(156);if(AGI.C)return;BF(101);if(AGI.C)return;return}}}
MESSAGES[32]=["","","The small wooden rowboat looks old and rotted from traversing the poisoned lake.","","The shrouded ghoul looks very frightening. His hands are little more than claws, and his face is completely hidden inside the hood of the shroud. He is standing in a small boat.","The spooky fiend holds out a bony claw, as if in request for a payment of some kind.","You climb carefully into the old boat. The shrouded ghoul paddles it across the lake to the ominous island.","You are greeted by stony silence from the frightening ghoul.","The ghoul will not let you take the boat.","You can't kill something that is already dead.","It is impossible to catch a ghoul.","Which treasure would you like to give the ghoul?","The shrouded ghoul takes your treasure. Silently, he gestures toward the boat.","The silent fiend slowly shakes his head. He is not interested in it.","You are too far away.","You don't have it.","The shrouded ghoul looks at the ruby ring on your finger and the black cloak around your neck. He motions for you to enter the boat, which you do. You must have fooled him into thinking you were someone else.","You must specify who you wish to give it to.","The lake is foul and stinking! It may be poisoned. All vegetation looks dead around it. There is a desolate island in the middle of the poisoned lake.","%m18 A shrouded figure stands silent."];CONTROLS[32]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?44D^O/{4TP-/PY4.w><.!~4.-><rYr~4<3><4%r~4<J>+~P]rw4<Y<x<wP;rw4<w+.JP<%K.3rw4<]U>YK.8rw4><.qKkET^q4><.qKdg8^q4><.qEd.Uq4><.qEY.Zq4><.qETUD.4q4><.kE89JPY{q4><.YKD9DUk^q4><.TKJ9DPq^q4><.OET9DPw!q4><.JEY9DK~!q4><.DEd9JE~!q4><.3Kq9DE~!q4><;Pq9DE~!q4><]ED9q9DE~!q4<D9>;9q9DKw!q4<8E>.39k9JE~!k4.T9wP>;9k9O9~!k4.JKwP>;9d9.Dxk4.JKqZ>]9Y9.Jxk4.JKqZ>.O9.Oxk4.OKkU>.O9.Txk4.OKkU>.J9.Y!d4.OKkP><~!d4.OKkP><~!d4.TKYU><~!d4.TKYU><~xk4.TKYU><~xk4.TPTP><%xk4.YPOP><%rq4.YPOP><%rq4.dPDU><%rq4.kx><~xq4.kr><%xq4.ql><%xq4.wg><%xq4.wZ><-xq4.wZ><-xq4.wZ><-xq4.wZ><-xq4.wZ><%!q4.~l><q!q4.~r><k!q4.~r><k!q4.~l><q!q4.~Z><~!q4.~U><%!q4.~U><%!q4Y9.JZ><-xq4Y9.JZ><-xq4Y9.JZ><-xq4Y9.JZ><-xq489O9.JZ><-xq4D9J9.JZ><-xq4DEDE.JU><-xq4DEDEOE-U><%!q4DEJZ]U><%!q4J9JP.3U><%!q4JE8K.DU><%xw4JU.JU><%xw4JU.JU><~!w4JP.OU<3U>Y!w4JP.JZ.q9TZ>Y!w4JK.Og.kKJg>T!w4DP.Og.dU8l>T!w4DU.Jg.dUDZ>Y^q48PD9.8l.qEOE>w!q48PJ9.3l><~!q48KO9.3l><~!q48KJ9.8l><~!q48EO9.8l><~!q48KJ9.Dg><k{q4Q.Tg><D.lT45K8Q.3l>.%<E9AUDFY,>.d<gKs.l.8r<.Y<!<rY.l<w<,>x.~<.!>.P~>9?4?4?4.rh><.,.l5lA><.+.g5!5><Zy!.g5xA><KF!Lg.lLKF><ZAlAP5g.l5KF><!AU5EF95g/^AE5ZAg/{595,/,5.4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4";