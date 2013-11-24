window.logic62=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CX(29);BY(166);if(AGI.C)return;CY(8);CY(54);CW(Ck);BJ(Ck);m(o3);p(o3,54);if(!(J(v93,2))){A(501);break}
w(o3,3);A(1);break;case 501:w(o3,0);case 1:AG(o3,124,126);AC(o3,11);AJ(o3);AN(o3);AG(Ego,47,165);r(Ego,0);AJ(Ego);Ah(Ego);Aa(Ego);AT(96);BM();case 500:if(!(E(DR))){A(502);break}
if(!(!BO(Ego,80,0,159,167))){A(503);break}
BN(29,f169);F(f92);p(Ego,8);L(v94,2);AS(Ego,v94);L(v94,3);Ai(Ego,v94);L(v60,1);AC(Ego,15);Ak(Ego,36,154,4,f145);A(2);break;case 503:F(f35);case 2:A(3);break;case 502:G(f35);case 3:if(!(E(f34))){A(504);break}
G(f34);if(!(J(v93,1))){A(505);break}
L(v93,2);if(!(!E(f143))){A(506);break}
Bg("With a creak and a groan, the old lid opens, dragging cobwebs with it.");Bg("Looking into the interior of the musty chest, you see a dazzling diamond and sapphire tiara!");A(4);break;case 506:Bg("You open the heavy lid of the dusty old chest and peer into it.");Bg("It is empty.");case 4:A(5);break;case 505:L(v93,1);case 504:case 5:if(!E(DQ)){A(19);break}
if((D("check out")||D("check out","antique shop")||D("check out","swim"))){Bg("There is not much here at the top of the tower but an aging chest against the wall.")}
if(D("look in","chest")){if(!J(v93,2)){Bg("The dusty old chest is closed.");A(6);break}
if(!E(f143)){Bg("Looking into the interior of the musty chest, you see a dazzling diamond and sapphire tiara!");A(6);break}
Bg("It is empty.")}
case 6:if(D("check out","chest")){if(!J(v93,2)){Bg("The dusty old chest is closed.");A(7);break}
Bg("The dusty old chest is open.")}
case 7:if(!(D("unlock","chest"))){A(507);break}
if(!(J(v93,0))){A(508);break}
if(!(BT("Silver Key"))){A(509);break}
if(!(E(f35))){A(510);break}
Bg("With hands trembling, you fit the little silver key into the lock. Slowly, you turn it until you hear a click. The old chest is now unlocked.");L(v93,1);V(Cn);A(8);break;case 510:Bg("You can't reach it from where you are standing.");case 8:A(9);break;case 509:Bg("You do not have the key that will unlock this old chest.");case 9:A(10);break;case 508:Bg("The aging chest is already unlocked.");case 507:case 10:if(!(D("open","chest"))){A(511);break}
if(!(!J(v93,2))){A(512);break}
if(!(E(f35))){A(513);break}
if(!(J(v93,0))){A(514);break}
Bg("The old chest is locked shut. You need to unlock it.");A(11);break;case 514:AQ(o3,f34);case 11:A(12);break;case 513:Bg("You can't reach it from where you are standing.");case 12:A(13);break;case 512:Bg("The aging chest is already open.");case 511:case 13:if(!(D("close","chest"))){A(515);break}
if(!(J(v93,2))){A(516);break}
if(!(E(f35))){A(517);break}
AR(o3,f34);A(14);break;case 517:Bg("You can't reach it from where you are standing.");case 14:A(15);break;case 516:Bg("The aging chest is already closed.");case 515:case 15:if(!(D("acquire","diamond and sapphire tiara"))){A(518);break}
if(!(!E(f143)&&J(v93,2))){A(519);break}
if(!(E(f35))){A(520);break}
Bg("You pick it up and carry it with you.");BS("Tiara");F(f143);W(Cn,7);A(16);break;case 520:Bg("You can't reach it from where you are standing.");case 16:A(17);break;case 519:if(!(BT("Tiara"))){A(521);break}
Bg("You already have it.");A(17);break;case 521:Bg("You don't see it here.");case 518:case 17:if(D("acquire","chest")){Bg("You couldn't possibly carry this heavy chest around with you.")}
if(D("break","chest")){if(E(f35)){Bg("This old chest is stronger than it looks.");A(18);break}
Bg("You can't reach it from where you are standing.")}
case 18:if(D("check out","stairs")){Bg("The stairs spiral steeply downward. Be careful, you don't want to fall.")}
case 19:if((BO(Ego,41,164,46,167)||N(v60,0))){Ab(Ego);H(63);if(AGI.C)return}
BF(166);if(AGI.C)return;return}}}
MESSAGES[62]=["","There is not much here at the top of the tower but an aging chest against the wall.","The dusty old chest is closed.","The dusty old chest is open.","The old chest is locked shut. You need to unlock it.","With a creak and a groan, the old lid opens, dragging cobwebs with it.","You open the heavy lid of the dusty old chest and peer into it.","The aging chest is already open.","The aging chest is already closed.","You do not have the key that will unlock this old chest.","The aging chest is already unlocked.","With hands trembling, you fit the little silver key into the lock. Slowly, you turn it until you hear a click. The old chest is now unlocked.","You couldn't possibly carry this heavy chest around with you.","It is empty.","You pick it up and carry it with you.","The bed looks too lumpy and dusty. You wouldn't want to.","You can't reach it from where you are standing.","The stairs spiral steeply downward. Be careful, you don't want to fall.","You don't see it here.","You already have it.","Looking into the interior of the musty chest, you see a dazzling diamond and sapphire tiara!","This old chest is stronger than it looks."];CONTROLS[62]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4<.rQ><E<.r5K5KQKQ>.E<.r5K5K5K5K5K5KQKQ>E<xQKQE5K5K5K5K5K5K5K5K5K5>E<x5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<EQK5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<E5K5K5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<E5K5K5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<E5K5K5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<E5K5K5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<E5K5K5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<E5K5K5K5K5K5E5K5K5K5K5K5K5K5K5K5>E<E5K5K5K5K5K5E5K5K5K5KmKVE5>E<E5K5K5K5K5K5E59aKQPhUF>E<E5K5K5K5K5K5EAPV.lA>9<E5K5K5K5K5KF<ZA<.,<E5K5K5K5K59F<xA<.+<E5K5K5KV<,a<.Z<E5K5K59F<.!5<.U<E5K5K595<.{5<.P<E5K5K595<.{5<.P<E5K5KA>45<.K<E5K5KA>9F<.4<E5K5K5>Uh<l<E5K5E5>{5<g<E5EA95>.4A<U<E5959A>.K5<P<E595>.g5xQ.P<EA>.rAl5K5.P<E5>.^5g5K5.P<E5>.+AU5K5.P<95>.^CEAK5K5.P<45>.xHZ5E5K5.P<45>.ZNlAE5K5.P.{A>.UCla95K5E5E5{.^A>.l7UF95KA95K5E5E5{.^5>.r7U5K5K59AK5E5E5{.!5>.!7U5E5K59AK5E5E5{.!5>.!7U5E5K5E5K5E5E5{.x5>.+7U595K5E5K5E5E5{.xC>.^7U595K5K5E5E5E5{.^N>.r7P595K5EF95E5E5{<4N>.U7UA9QKAE5E5{<PN>.E7PFr5E5E5{<lN>{7.45E5E5{<^H>^7+C5E5E5{<{7>^7xHK595E5{<{7>+7UNZ595E5{<,7>^7EHx595E5{<,7>+C+595E5{<,7>.+AE5{<,7>.+AE5{<.47>.^AE5{<.47>.^AE5{<.47>.^AE5{<.97>.!AE5{<.97>.!AE5{<.E7>.xQ{<.E7>.x5.E<.K7>.r5.E<.PC>.g5.E<.ZC>.U5.E<.lC>.K5.E<.xN>,5.E<.{H>^5.E>45>!5.K<.,5>^5.K<.+A>^5.P<.^5>+5.U<.!5>{5.U<.x5>{5.Z<.lA>{5.g<.g5>.45.g<.Z5>.45.l<.U5>.95.l<.KA>.95.r<.E5>.K5.r<.95>.K5.x<,A>.P5.x<{5>.PA.!<+5>.P5.+<^5>.P5.{<xA>.KA.,<r5>.P5<9<l5>.KA<E<.x>A<P";