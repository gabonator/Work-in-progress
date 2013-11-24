window.logic15=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CX(10);CW(Ck);BY(152);if(AGI.C)return;BY(101);if(AGI.C)return;if(!((BT("Oil Lamp")||BT("Carpet")))){A(501);break}
CY(65);CY(98);case 501:CY(10);CY(11);CY(97);CY(104);CY(12);CY(13);CY(110);BJ(Ck);BF(152);if(AGI.C)return;BF(101);if(AGI.C)return;L(v108,2);AS(o2,v108);m(o3);m(o2);L(v108,2);AS(o3,v108);AG(o2,7,60);AC(o2,14);p(o2,10);if(!(E(f67)&&!E(f96))){A(502);break}
F(f31);BN(10,f169);AJ(o2);A(1);break;case 502:case 1:if(!(J(Cl,22))){A(503);break}
AL(Ego,v105,v106);if(!(N(v105,39))){A(504);break}
W(v105,80);A(2);break;case 504:if(!(N(v105,60))){A(505);break}
W(v105,59);A(2);break;case 505:if(!(P(v105,38))){A(506);break}
W(v105,30);case 506:case 2:AH(Ego,v105,v106);case 503:if(!(J(Cl,54))){A(507);break}
L(v95,2);F(f92);AG(Ego,0,100);p(Ego,13);AR(Ego,f36);case 507:if(!(J(Cl,50))){A(508);break}
AL(Ego,v105,v106);if(!(N(v106,67)&&P(v106,76))){A(509);break}
L(v106,76);case 509:AH(Ego,v105,v106);case 508:AJ(Ego);BM();case 500:if(E(f36)){G(f36);AK(Ego);AG(o3,0,100);p(o3,12);r(o3,1);w(o3,0);AJ(o3);AQ(o3,f37);p(Ego,97);AG(Ego,20,100);AJ(Ego);L(v95,2);G(f33)}
if(E(f37)){G(f37);AK(o3)}
if((BO(Ego,0,21,50,85)||BO(Ego,0,89,70,137))){F(DO)}
if(E(DO)&&!N(v95,0)){AL(Ego,v67,v68);if(BO(Ego,37,31,63,49)){L(v67,32);L(v68,43);F(f116)}
if(BO(Ego,32,50,68,57)){L(v67,41);L(v68,55);F(f116)}}
if(!BO(Ego,0,0,80,100)){if(!E(DS)&&D("anyword","bitch")){if((D("find","bitch")||D("check out","bitch")||D("speak","bitch"))){G(DS);A(3);break}
Bg("You are too far away.");A(11);break}}
case 3:if(!(E(f31))){A(510);break}
if(!(D("check out","boulder"))){A(511);break}
Bg("Can you believe it! There is a mermaid reclining on a large rock offshore!");A(4);break;case 511:if(!(D("check out","bitch"))){A(512);break}
Bg("The mermaid has long flowing hair covering most of her upper body. The green scales on her fish tail are sparkling like emeralds as she slowly waves it back and forth. She beckons with her hand.");A(4);break;case 512:if(!((D("enter","boulder")||D("climb","boulder")||D("get on","boulder")))){A(513);break}
Bg("There is no room for you on this rock. It is occupied already.");A(4);break;case 513:if(!((D("kill","bitch")||D("capture","bitch")||D("acquire","bitch")))){A(514);break}
Bg("Wrong move! You frightened the poor mermaid. She dives into the water and disappears.");AS(o2,v108);p(o2,11);AQ(o2,f32);G(f31);case 514:case 4:A(5);break;case 510:if(D("check out","boulder")){Bg("There is a large rock in the ocean a short way from shore. Small waves lap at the edges.");A(5);break}
if(D("check out","bitch")){Bg("She's not there.");A(5);break}
if(D("follow","bitch")){Bg("It would be impossible for you to follow a mermaid in the ocean!")}
case 5:if(E(f32)){G(f32);G(f31);AK(o2)}
if(!E(f31)){A(8);break}
if(D("speak","bitch")){Bg("The mermaid does not reply. She gives you a quizzical look and continues waving her fish tail.")}
if((D("hello")||D("say","hello"))){Bg("The mermaid does not reply. She gives you a quizzical look and continues waving her fish tail.")}
if((D("embrace","bitch")||D("kiss","bitch"))){Bg("Don't get too close! You might frighten her.")}
if(!BO(Ego,0,40,50,90)){if(D("give","anyword","bitch")){Bg("You are too far away.");A(11);break}}
if((D("give","treasure","bitch")||D("give","bitch","treasure"))){Bg("Which treasure would you like to give to the mermaid?")}
if(BT("Brooch")&&(D("give","brooch","bitch")||D("give","bitch","brooch"))){CL("Brooch");F(f35)}
if(BT("Tiara")&&(D("give","diamond and sapphire tiara","bitch")||D("give","bitch","diamond and sapphire tiara"))){CL("Tiara");F(f35)}
if(BT("Necklace")&&(D("give","diamond and sapphire necklace","bitch")||D("give","bitch","diamond and sapphire necklace"))){CL("Necklace");F(f35)}
if(BT("Bracelet")&&(D("give","bracelet","bitch")||D("give","bitch","bracelet"))){CL("Bracelet");F(f35)}
if(BT("Earrings")&&(D("give","earrings","bitch")||D("give","bitch","earrings"))){CL("Earrings");F(f35)}
if(E(f35)){Bg("The mermaid gladly takes your treasure. In return, she summons forth from the sea a magic seahorse! Maybe you could ride it.")}
if(BT("Bouquet of Flowers")&&(D("give","bouquet","bitch")||D("give","bitch","bouquet")||D("give","blossom","bitch")||D("give","bitch","blossom"))){CL("Bouquet of Flowers");Bg("You graciously offer the beautiful bouquet of wildflowers to the mermaid. She loves the flowers! She then summons forth a magic seahorse! Maybe you could ride it.");F(f35);F(f39)}
if(BT("Trident")&&(D("give","rusty trident","bitch")||D("give","bitch","rusty trident"))){Bg("You hand the rusty trident to the mermaid. Oh, no! She dives into the water and disappears with it! Now she's gone.");Y(Cn,3);CL("Trident");p(o2,11);AQ(o2,f32);F(f97)}
if(!E(DS)&&(D("give","bouquet")||D("give","blossom")||D("give","rusty trident")||D("give","diamond and sapphire necklace")||D("give","brooch")||D("give","diamond and sapphire tiara")||D("give","earrings")||D("give","bracelet"))){if(D("give","anyword","bitch")){Bg("You aren't carrying it.");A(6);break}
Bg("You must specify who you wish to give it to.")}
case 6:if(!E(DS)&&D("give","anyword","bitch")){Bg("The mermaid looks at your offering distastefully. She is not interested in it.")}
if(!(E(f35))){A(515);break}
AG(o3,7,87);p(o3,12);w(o3,5);AJ(o3);AR(o3,f169);L(v58,25);G(f35);if(!(E(f39))){A(516);break}
W(Cn,2);A(7);break;case 516:Y(Cn,7);case 7:F(f33);case 515:U(v58);if(J(v58,1)){p(o2,11);AQ(o2,f32);G(f31)}
case 8:if(!E(f33)){A(11);break}
if(D("check out","magic seahorse")){Bg("This is a larger than average seahorse! It has a little saddle attached to its back. The seahorse tosses its head expectantly.")}
if((D("acquire","magic seahorse")||D("capture","magic seahorse"))){Bg("The magic seahorse is already here for your use.")}
if(D("y")&&E(f38)){G(f38);A(9);break}
if(!((D("get on","magic seahorse")||D("get on","flying horse")))){A(517);break}
case 9:BC(Ego,o3,v94);if(!(N(v94,20))){A(518);break}
Bg("You are too far away.");A(10);break;A(10);break;case 518:if(!(!N(v33,0))){A(519);break}
L(v33,0);W(Cn,2);case 519:Bg("Quick as a flash, it glides under the water with you on its back!");AK(o3);Ad();AK(Ego);AG(Ego,10,100);p(Ego,110);w(Ego,0);AJ(Ego);AQ(Ego,f34);L(v64,4);L(Cr,7);case 517:case 10:if(E(f34)){G(f34);p(Ego,0);H(54);if(AGI.C)return}
if(D("pat","magic seahorse")){Bg("You gently pat the seahorse's nose.")}
if(D("speak","magic seahorse")){Bg("Don't you know that seahorses can't talk!")}
if(!E(f31)&&(D("say","hello")||D("hello"))){Bg("Don't you know that seahorses can't talk!")}
if(E(DS)&&E(f38)){G(f38)}
if((D("climb","magic seahorse")||D("sit","magic seahorse"))){Bg("Do you wish to ride the magic seahorse?");F(f38)}
case 11:if(J(Cm,1)){H(8);if(AGI.C)return}
if(J(Cm,2)){H(16);if(AGI.C)return}
if(J(Cm,4)){H(50);if(AGI.C)return}
if(J(Cm,3)){H(22);if(AGI.C)return}
BF(152);if(AGI.C)return;BF(101);if(AGI.C)return;return}}}
MESSAGES[15]=["","There is a large rock in the ocean a short way from shore. Small waves lap at the edges.","Can you believe it! There is a mermaid reclining on a large rock offshore!","The mermaid has long flowing hair covering most of her upper body. The green scales on her fish tail are sparkling like emeralds as she slowly waves it back and forth. She beckons with her hand.","","There is no room for you on this rock. It is occupied already.","Wrong move! You frightened the poor mermaid. She dives into the water and disappears.","The mermaid does not reply. She gives you a quizzical look and continues waving her fish tail.","Don't get too close! You might frighten her.","Which treasure would you like to give to the mermaid?","The mermaid gladly takes your treasure. In return, she summons forth from the sea a magic seahorse! Maybe you could ride it.","You graciously offer the beautiful bouquet of wildflowers to the mermaid. She loves the flowers! She then summons forth a magic seahorse! Maybe you could ride it.","You hand the rusty trident to the mermaid. Oh, no! She dives into the water and disappears with it! Now she's gone.","It would be impossible for you to follow a mermaid in the ocean!","She's not there.","This is a larger than average seahorse! It has a little saddle attached to its back. The seahorse tosses its head expectantly.","The magic seahorse is already here for your use.","Quick as a flash, it glides under the water with you on its back!","Do you wish to ride the magic seahorse?","You gently pat the seahorse's nose.","Don't you know that seahorses can't talk!","You are too far away.","The mermaid looks at your offering distastefully. She is not interested in it.","You must specify who you wish to give it to.","You aren't carrying it."];CONTROLS[15]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4><.U5<x><.U5<x><.U5<x><{5E5K5<x><{5E5K5<x><{5E5K5<x><{5E5K5<x><{5E5K5<x><{5E5K5<x><{5E5K5<x><{5E5K5<x4<8Z-<.x5E5K5<x4<3g%<.!5E5K5<x4<3l%<.x5E5K5<x4.]x-<.r5E5EA<x4.]!]<.gA9F<^4.-^;<.lA<{4.-^.3><g4.%{.3><Z4.%ULU.8><U4-K%EFPFK.8><P4~Zw9AxA9.8><P4qlw5{59.3><P4qrq5!Q.3><P4qrw5lA.Y><K4qr~APA.k><K4qx%L.w><K4qx<w><K4q!<q><K4k^<q><K4k+YU.-><K4k,Dl.%><K4k.x.~><K4k.!.w><K4k.^.q><K4k.^.w><E4d.{.w>,.A4d.{.w>!LELKLU4Y<4.w>gFK5E5E5K5E5U4Y<4.~>KFZ5E5E5K5E5U4T<9.-<4Q.lQl5E5E5K5E5U4T<E.-.+AK59s^FK5l5E5E5K5E5U4O^}l.;.rAU5E5K5E59Ar5E5K5l5E5E5K5E5U4OlL,LU<3.Z5g5E5K5E59595g5K5K5l5E5E5K5E5U4OZA.gAK<D.K5l5E5K5E595E5UAK5K5l5E5E5K5E5U4TEF.!5K<J.95l5E5K5E595E5P595K5K5l5E5E5K5E5U4TA.,A9<T{5r5E5K5E59595P5E5K5K5l5E5E5K5E5U4O5<EA<d!5x5E5K5E59FPs95l5E5EAE5E5U4TA.{A<wxAr5EQEF,595l5E5E59595E5U4dAKL.EF<%^Ag59AKL.EAl5E595KAE5U4qFOA+F<.3+AUA.!AlQUA95U4.DArA<.O{Q.{5lLl5Z4.OAUA<.Y<.9m+5U4.YQ<.q>gAK4>.O>rF4>.O>^4>.O>^4>.O>^4>.O>^4>.O>^4>.O>^4>.O>^4>.J>+4>.J>+4>.D>{4>.D>{4>.8>,4>.8>,4>.D>{4>.D>{4>.J>+4<.T9.->+4<.JP.->^4<.DZ.%>^4<.8g.]>x4<.8l.]>r4<.3x.]>l4<.3!.;>Z4<;^<3>U4<-{<D>K4<%.4<J>94<%.4<T<.,4<~.E<d<.^4<w.U<d<.x4<w.Z<k<.l4<q.g<w<.Z4<q.l<~<.P4<k.r<%<.K4<k.r<]<.94<k.r<;<.44<Y^L^<;<,4<TrLPLl<.8<+4<OZL^FU<.D<^4<OPA.KLE<.D<!4<O9F.rA<.J<x4<JA.^5<.O<x4<J5.+5<.T<r4<OA.x5<.d<l4<YA.g5<.q<g4<kF.K5<.~<Z4<~F,5<.%<Z4<]F!59<.-<U4<.39y9<.;<P4><.%<P4><.%<P4><.-<K4><.-<K4><.-<K4><.-<K4><.-<K4><.-<K4><.]<E4><.]<E4><.]<E4><.-<K4><.-<K4><.%<P4><.%<P4><.~<U4><.~<U4><.w<Z4><.w<Z4><.q<g4><.q<g4><.q<g4><.k<l4><.k<l4><.k<l4><.k<l4><.d<r4><.d<r4><.d<r4><.k<l4><.k<l4><.q<g4><.q<g4><.w<Z4><.w<Z4><.~<U4><.~<U4><.%<P4><.%<P4><.-<K";