window.logic59=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
BY(166);if(AGI.C)return;CY(49);CW(Ck);BJ(Ck);BF(166);if(AGI.C)return;m(o2);p(o2,49);if(!(J(v98,1))){A(501);break}
w(o2,2);A(1);break;case 501:w(o2,0);case 1:AY(o2);AG(o2,34,114);AJ(o2);AN(o2);AG(Ego,121,158);AJ(Ego);BM();case 500:if(!(E(f31))){A(502);break}
G(f31);if(!(J(v98,0))){A(503);break}
L(v98,1);if(!(!E(f141))){A(504);break}
Bg("There is a candle lying in the drawer of the old dresser.");A(2);break;case 504:Bg("The drawer of the old dresser is empty.");case 2:A(3);break;case 503:L(v98,0);case 502:case 3:if(!E(DQ)){A(12);break}
if((D("check out")||D("check out","antique shop")||D("check out","swim"))){Bg("The musty bedchamber is at the top of a tower. It has the smell of mold and old moth balls. There is a sagging bed and an old dresser in the room.")}
if(D("check out","bed")){Bg("The bed is lumpy and sagging in the middle. A faded old quilt covers it.")}
if(D("check out","bureau")){Bg("The old dresser is scratched and nicked. You can tell it was once a fine piece of furniture. There are several drawers in the dresser.")}
if(D("look in","drawer")){if(J(v98,0)){Bg("The dresser drawer is closed.");A(4);break}
if(!E(f141)){Bg("There is a candle lying in the drawer of the old dresser.");A(4);break}
Bg("The drawer of the old dresser is empty.")}
case 4:if(D("check out","drawer")){if(J(v98,0)){Bg("The dresser drawer is closed.");A(5);break}
Bg("The dresser drawer is open.")}
case 5:if(!((D("open","drawer")||D("open","bureau")))){A(505);break}
if(!(J(v98,0))){A(506);break}
if(!(E(DR))){A(507);break}
AQ(o2,f31);A(6);break;case 507:Bg("You can't reach it from where you are standing.");case 6:A(7);break;case 506:Bg("The drawer is already open.");case 505:case 7:if(!(D("close","drawer"))){A(508);break}
if(!(J(v98,1))){A(509);break}
if(!(E(DR))){A(510);break}
AR(o2,f31);A(8);break;case 510:Bg("You can't reach it from where you are standing.");case 8:A(9);break;case 509:Bg("The drawer is already closed.");case 508:case 9:if(!(D("acquire","candle"))){A(511);break}
if(!(!E(f141)&&J(v98,1))){A(512);break}
BC(Ego,o2,v67);if(!((E(DR)||P(v67,20)))){A(513);break}
Bg("You pick it up and carry it with you.");BS("Candle");F(f141);W(Cn,2);A(10);break;case 513:Bg("You can't reach it from where you are standing.");case 10:A(11);break;case 512:if(!(BT("Candle"))){A(514);break}
Bg("You already have it.");A(11);break;case 514:Bg("You don't see one here.");case 511:case 11:if((D("lie","bed")||D("get on","bed")||D("sit","bed")||D("get in","bed")||D("enter","bed"))){Bg("The bed looks too lumpy and dusty. You wouldn't want to.")}
if((D("check out","stairs")||D("check out","ramp"))){Bg("The ramp spirals steeply downward. Be careful--you don't want to fall.")}
if(D("acquire","quilt")){Bg("The quilt is old and tattered; you wouldn't want it.")}
case 12:if(BO(Ego,116,162,135,167)){H(60);if(AGI.C)return}
BF(166);if(AGI.C)return;return}}}
MESSAGES[59]=["","The musty bedchamber is at the top of a tower. It has the smell of mold and old moth balls. There is a sagging bed and an old dresser in the room.","The bed is lumpy and sagging in the middle. A faded old quilt covers it.","The old dresser is scratched and nicked. You can tell it was once a fine piece of furniture. There are several drawers in the dresser.","The dresser drawer is closed.","The dresser drawer is open.","There is a candle lying in the drawer of the old dresser.","The drawer of the old dresser is empty.","The drawer is already open.","The drawer is already closed.","You pick it up and carry it with you.","The bed looks too lumpy and dusty. You wouldn't want to.","You can't reach it from where you are standing.","The ramp spirals steeply downward. Be careful--you don't want to fall.","You don't see one here.","You already have it.","The quilt is old and tattered; you wouldn't want it."];CONTROLS[59]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4>.PR>g<.x.tUR>E<.lB<PB>4<.ZB<lB<.{<.KG<^B<.^<.4G<.9B<.x<,6<.ZB<.l<+B<.rG<.U<^6<.{M<.9<!6>KG<{<x6>gB<^<lB>xB<x<g6>{6<r<Z6>.46<l<Ui<.KR.KB<Z<^6<.g6.U6<U<^6<.g6.Z6<P<^6<.g6.gB<E<^6S<.EB.l6<9<!6X<.E69B.g6<4<!6S<.K6K6.Z6<4<x6X<.K6P6.Z6.,<x6S<.P6U6.U6.,<r6X<.P6Z6.P6.,<r6S<.U6Z6.U6.{<l6X<.Uz.E6.{<l6X<.{B.E6.{<g6X<.,B.K6.+<g6X>46.K6.+<Z6X>9B.E6.+<Z6X>9B.K6.^<U6X.9.(.P696.E6.^<U6X.96.!6.P6E6.E6.!<P6c.46.^6.P6E6.E6.!<P6X.96.^6.P6K6.E6.x<K6c.46.+6.P6K6.E6.x<K6X.96.{6.K6K6.E6.x<E6c.46.,6.Kb.46.x.U_X.96.,6.lB.96.r.U6.4H.46<46.lB.96.r.P6<P6<46.lB.96.r.P6<K6<96.r6.96.r.K6<P6<96.r6.96.r.K6<K6<E6.r6.96.r.K6<K6<E6.x6.46.r.K6<E6<K6.x6.46.r.E6<K6<K6.x6.46.r.E6<E6<P6.x6.96.l.E6<E6<P6.x6.96.l.E6<96<P6.xB.96.l.E6<96<P6.xB.96.l.96<96<U6.xB.96.l.96<96<U6.xB.96.l.96<96<U6.xB.96.l.96<46<Z6.r696.96.l.E6.,6<Z6.r696.96.l.E6.{6<g6.r696.96.l.E6.{6<g6.rB.E6.l.K6.^6<l6.rB.K6.g.K6.^6<l6.l696.K6.g.K6.!6<r6.l696.K6.g.P6.x6<r6.l696.K6.g.P6.r6<x6.l696.K6.g.P6.r6<x6.l696.K6.g.U6.g6<!6.l696.K6.g.U6.g6<x6.r696.K6.g.U6.Z6<!6.r696.K6.g.U6.Z6<!6.r696.K6.g.Z6.P6<^6.r696.P6.Z.Z6.P6<^6.r696.P6.Z.gB.96<+6.r696.P6.Z.r6.46<+6.r696.P6.Z.xB+6<{6.r696.P6.Z.^_<{.z96.P6.Z";