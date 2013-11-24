window.logic20=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CX(21);CY(65);CY(98);CY(114);BY(151);if(AGI.C)return;BY(160);if(AGI.C)return;CW(Ck);BF(160);if(AGI.C)return;BJ(Ck);m(o3);p(o3,114);w(o3,0);AC(o3,10);AG(o3,94,114);AY(o3);Aa(Ego);if(!(J(Cl,68))){A(501);break}
r(Ego,1);AG(Ego,87,117);A(1);break;case 501:if(!(J(Cl,105))){A(502);break}
AC(Ego,15);L(v94,2);AS(Ego,v94);Ai(Ego,v94);p(Ego,98);AG(Ego,45,40);Ak(Ego,45,70,0,f32);case 502:case 1:AJ(Ego);AJ(o3);AN(o3);if(!(E(f134))){A(503);break}
if(!(E(f101))){A(504);break}
G(f71);A(2);break;case 504:F(f71);case 503:case 2:BM();case 500:if((BT("Carpet")||BT("Oil Lamp"))){if(BQ(Ego,85,70,122,106)){BA(o3);AN(o3);Ag(o3);F(f30);A(3);break}
if(E(f30)){G(f30);Az(o3)}}
case 3:if(!E(DQ)){A(9);break}
if((D("check out","antique shop")||D("check out")||D("check out","area"))){Bg("This is a quaint little antique shop. There is a sign in the window.")}
if((D("check out","sign")||D("read","sign"))){if(E(f71)){Bg("The sign says \"open.\"");A(4);break}
Bg("The sign says \"closed.\"")}
case 4:if((D("check out","window")||D("look in","window"))){if(BO(Ego,80,122,120,145)){Bg("You can see inside when you look through the window. It is hard to tell details, though.");A(5);break}
Bg("You are too far away.")}
case 5:if(D("check out","door")){Bg("The door to the antique store is closed.")}
if((E(f148)||!J(v88,0))){A(8);break}
if(D("open","door")){if(!E(f71)){Bg("The antique store is closed. You cannot enter it.");A(6);break}
if(BO(Ego,86,109,98,122)){BN(21,f169);AQ(o3,f31);A(6);break}
Bg("You are too far away.")}
case 6:if((D("knock","door")||D("knock"))){if(!E(f71)){Bg("You rap loudly on the door but get no reply.");A(7);break}
if(BO(Ego,86,109,98,122)){Bg("You rap loudly on the door and hear a cheery, \"Come on in.\"");A(7);break}
Bg("You are too far away.")}
case 7:if(D("unlock","door")){if(BO(Ego,86,109,98,122)){Bg("You can't unlock the door. You don't have a key that fits.");A(8);break}
Bg("You are too far away.")}
case 8:if((D("break","window")||D("break","door"))){Bg("You could get caught for \"breaking and entering.\" That would not be wise.")}
case 9:if(E(f31)){G(f31);H(68);if(AGI.C)return}
if(E(f32)){Ab(Ego);AE(Ego);p(Ego,0);G(f32);G(f148);L(v94,1);AS(Ego,v94);Ai(Ego,v94)}
if(J(Cm,1)){H(13);if(AGI.C)return}
if(J(Cm,2)){H(21);if(AGI.C)return}
if(J(Cm,4)){H(19);if(AGI.C)return}
if(J(Cm,3)){H(27);if(AGI.C)return}
BF(151);if(AGI.C)return;BF(160);if(AGI.C)return;return}}}
MESSAGES[20]=["","","","","","","","This is a quaint little antique shop. There is a sign in the window.","The sign says \"closed.\"","The sign says \"open.\"","You can see inside when you look through the window. It is hard to tell details, though.","The door to the antique store is closed.","The antique store is closed. You cannot enter it.","You could get caught for \"breaking and entering.\" That would not be wise.","You rap loudly on the door but get no reply.","You rap loudly on the door and hear a cheery, \"Come on in.\"","You are too far away.","You can't unlock the door. You don't have a key that fits."];CONTROLS[20]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4{5K5/+{5K5/+{5K5/+!5E5K5/+!5E5K5/+!5E5K5/+!5E5K5/+!5E5K5/+!5E5K5/+!5E5K5/+!5E5K5/+!5E5K5/+!5E5EA/+^Q/,{5/.9?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4<EF><.!<4AKA><.r.{AgA><.g.{5r5><.g.{5lA><.g.,AKF><.r<9F><.^?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4>x.BZ<._>x>.W>x6E6P6E6ZMU6KWP6r6U6U6PWPWE>x6E6P6E6gMPRKBP6r6U6U6P6P6P6P6E>x6E6P6E6!6!BP6r6U6U6P6P6P6P6E>x6E6P6E6^6xBP6r6U6U6P6P6P6P6E>x6E6P6E6+6rBP6r6U6U6P6P6P6P6E>x6E6EW{6EMEBP6r6U6U6P6P6P6P6E>x6E696.UBPMP6r6U6U6P6P6P6P6E>x6E696.UB^6r6U6U6P6P6P6P6E>x6E696.Z6^6r6U6U6P6P6P6P6E>x6E696.g6!6r6U6U6P6P6P6P6E>x6E696.g6!6r6U6U6P6P6P6P6E>x69M.g6!6K6U6U6U6P6P6P6P6E>x696.x6!6K6U6U6U6P6P6P6P6E>x696.!6x6K6U6U6U6P6P6P6P6E>x696.^6r6K6U6U6U6P6P6P6P6E>x696.+6l6K6U6U6U6P6P6P6P6E>x696.{6g6K6U6U6U6P6P6P6P6E>xG.,6Z6K6U6U6U6P6P6P6P6E>lG<96Z6K6U6U6U6P6P6P6P6E>l696.9R^6U6K6U6U6U6P6P6P6P6E<+LlQx696{GU6^6P6K6U6U6U6P6P6P6P6E.lA6L!F96EAU5K69Al696{6gB^6K6K6U6U6U6P6P6P6P6E.ZAE6K5!5K6K5U5K695r696+6lB+6E6K6U6U6U6P6P6P6P6E.U5P6K5^5E6FgA965xG^6r696+696K6U6U6U6P6P6P6P6E.Z5K6K5^F+56!6+6x6E6!MK6U6U6U6P6P6P6P6E.Z5K6E5<.g6!6K6ZMK6K6U6U6U6P6P6P6P6E.g5E6E5<.g6!6K6EMK6K6K6U6U6U6P6P6P6P6E.g5EF<.l6!6KG96U6K6K6U6U6U6P6P6P6P6E.lA<.rB^6K6K6U6K6K6U6U6U6P6P6P6P6E>.9B{6K6K6U6K6K6U6U6U6P6P6P6P6E>.46.46K6K6U6K6K6U6U6U6P6P6P6P6E>.46.46K6K6U6K6K6U6U6U6P6P6P6P6E>.46.46K6K6U6K6K6U6U6U6P6P6P6P6E>.46.46K6K6U6K6K6U6U6U6P6P6P6P6E>.46rMg6K6U6K6K6U6U6U6P6P6P6P6E>.46KWP6Z6K6U6K6K6U6U6U6ERE6P6P6E>.4M!6U6K6r6K6U6U6U6E6P696P6KBE><46l6r6r6U6U6E6UbE69B9><96.96lGP6U6E6g6KGP6><96.96KRE6P6U696rGl><E6,Rg6P6UB.U><K6rR+BE6KB.g><P6KR.PW.r><UG<.l?4<.9F6F><l<.45K6KAla>.g.+F6Lx5P6K5r5E6E5>.g.+5E6K5!5K6E5r5K6E5>.g.+5E6E5^5K6Ax5K6A>.l.{596E5+59A+A95>.x.{59695{A.95>.!.{59695><.+.{A65><.{?4?4?4?4?4";