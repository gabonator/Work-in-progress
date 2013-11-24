window.logic64=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
AT(0);BY(166);if(AGI.C)return;CY(134);CY(56);if(!(K(Ck,v92))){A(501);break}
CY(51);CY(52);CY(53);case 501:CW(Ck);BJ(Ck);BF(166);if(AGI.C)return;if(!(!E(f140))){A(502);break}
m(o2);p(o2,56);AC(o2,12);AG(o2,65,98);AN(o2);AJ(o2);case 502:m(o3);p(o3,134);AC(o3,9);AG(o3,63,26);AJ(o3);AM(o3);if(!(J(Cl,65))){A(503);break}
AG(Ego,128,119);A(1);break;case 503:if(!(J(Cl,61))){A(504);break}
AG(Ego,25,119);A(1);break;case 504:AG(Ego,80,85);r(Ego,2);w(Ego,0);case 1:Aa(Ego);AJ(Ego);BM();case 500:if(!E(f31)){AG(o3,63,26);F(f31);A(2);break}
AG(o3,91,26);G(f31);case 2:if(!E(DQ)){A(4);break}
if((D("check out")||D("check out","antique shop")||D("check out","swim"))){Bg("This is the dingy dining room of the drafty old castle. Ants crawl among old bits of food. Dust covers a dilapidated table top.");if(!E(f140)){Bg("A delicious-looking smoked ham is on the table.")}}
if(D("check out","stairs")){Bg("The stairway appears to lead down into the dark depths of the castle.")}
if(D("check out","chair")){Bg("The chairs are old and worn.")}
if(D("check out","table")){Bg("The table top is completely covered with dust. Scratches scar the legs of the table. Chairs with torn padding accompany it.");if(!E(f140)){Bg("A delicious-looking smoked ham is on the table.")}}
if((D("sit","table")||D("sit","chair")||D("sit")||D("sit","chair"))){Bg("The worn chairs look uninviting to sit upon.")}
if(!(D("acquire","ham"))){A(505);break}
if(!(!E(f140))){A(506);break}
if(!(BO(Ego,50,102,108,138))){A(507);break}
Bg("OK.");BS("Ham");F(f140);AK(o2);W(Cn,2);A(3);break;case 507:Bg("To do that, you will need to get closer.");case 3:A(4);break;case 506:if(!(BT("Ham"))){A(508);break}
Bg("You don't see one here.");A(4);break;case 508:Bg("You already have it.");case 505:case 4:if(E(DR)&&!J(v92,5)){AL(Ego,v105,v106);if((J(v92,1)||J(v92,3))){L(v92,0)}
if(P(v106,100)){H(63);if(AGI.C)return;A(5);break}
if(N(v105,80)){H(65);if(AGI.C)return;A(5);break}
if(P(v105,80)){H(61);if(AGI.C)return}}
case 5:BF(166);if(AGI.C)return;return}}}
MESSAGES[64]=["","This is the dingy dining room of the drafty old castle. Ants crawl among old bits of food. Dust covers a dilapidated table top.","A delicious-looking smoked ham is on the table.","The stairway appears to lead down into the dark depths of the castle.","The table top is completely covered with dust. Scratches scar the legs of the table. Chairs with torn padding accompany it.","The worn chairs look uninviting to sit upon.","To do that, you will need to get closer.","You don't see one here.","You already have it.","The chairs are old and worn.","OK."];CONTROLS[64]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4>E.|<.,>E.|<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!B<.,>EB.!696<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.^B<.{>EB.$B<.{<.Z_.^.W<x<x#9(.^.b<r<x(<.{B<r<rB>!B<l<r6>^B<l<lB>+B<g<l6>{B<g<gB>,B<Z<g6>.4B<Z<ZB>.4B<Z<ZB>.4B<Z<UB>.9B<Z<UB>.9B<Z<PB>.KB<U<PB>.KBr6.!<K696>.PBl6.!<KB>.UBl6.!<E696>.ZBg6.!<EB>.gBg6.!<9696>.ln.!4<G>.rn.!4<G><47.^.^7><Z7.^.!7><l7.!.!7><l7.!.x7><x7.x.x7><x7.x.r7><^7.r.r7<U.G<.P7.r.l7<U69.69.B<K7.l.g7<UG.9.G<K7.l.g7<PB<UB<K7.g.Z7<KB<lG<97.g.Z7.,M<!M<47.Z.U7.^W<.4M.+7.Z.U7.rGEB<.UM.!7.U.P7.lBEG<.rM.r7.U.P7.ZB9G<.{M.l7.P.K7.UB9B>KG.g7.P.E7.ZG>ZB.l7.K.E7.ZB>gB.l7.K.97.gB>gB.r7.E.97.gB>gB.r7.E.47.lB>Eb.x7.9.47.l|<{_.x7.9,7.r|<{B<g7.4{7<lB<+B<g7.4{7<l<.6<l7,+7<r<.6<l7,+7/K7{^7/P7{^7/U7+!7/Z7+!7/g7^x7/l7^r7/x7!r7/x7!l7/^7xl7/^7xg7/{7rg7/{7rZ7/.47l4_/r7l4_/Kbl^B/K|!696/KBZb!B/P696^x696/UB^xB/Z696!r696/gB!rB/rBxlB/!6xlB/!BrgB/+Blg6/,6lZB/,BgUB/.9BZUB/.E6ZPB/.KBUP6/.UBPKB/.Z6PK6/.l6KEB/.lBEE/.#E9/._9?4";