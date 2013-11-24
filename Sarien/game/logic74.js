window.logic74=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CY(78);CY(28);CY(76);CY(77);CY(115);CX(5);CW(Ck);BJ(Ck);m(o3);m(o2);L(v94,3);AS(o2,v94);m(o4);L(v94,3);Ai(o4,v94);AG(o3,47,111);if(!(E(f112))){A(501);break}
p(o3,77);A(1);break;case 501:p(o3,76);case 1:AJ(o3);l(0,255,v94);G(f33);if(!(J(v55,0)&&J(v57,0))){A(502);break}
if(!(P(v94,185))){A(503);break}
F(f33);p(o4,28);AG(o4,50,119);Am(o4,7,f34);AJ(o4);case 503:case 502:AC(o2,12);AG(o2,105,141);p(o2,78);if(!(J(v85,0))){A(504);break}
w(o2,0);A(2);break;case 504:w(o2,3);case 2:Aa(o2);Aa(o4);Aa(Ego);AJ(o2);AN(o2);AL(Ego,v105,v106);if(!(P(v106,117))){A(505);break}
L(v106,117);AH(Ego,v105,v106);case 505:AJ(Ego);BM();if(!(E(f33))){A(506);break}
BN(5,f169);Bg("You have stumbled onto the home of the thieving dwarf! Unfortunately for you, he is home!");case 506:case 500:if((D("check out","antique shop")||D("check out","area")||D("check out"))){if(E(f112)){Bg("It seems you have entered the underground home of the little dwarf. It is cozy, with a fire crackling in the hearth. There is a trunk tucked away in the corner.");A(3);break}
Bg("It seems you have entered the underground home of the little dwarf. It is cozy, with a fire crackling in the hearth. A pot of chicken soup bubbling above the fire gives a delicious aroma to the room. There is a trunk tucked away in the corner.")}
case 3:if(D("check out","fire")){if(E(f112)){Bg("The fire is crackling merrily in the fireplace.");A(4);break}
Bg("There is a pot of chicken soup boiling over the fire.")}
case 4:if(D("check out","chest")){Bg("The trunk looks old and worn. The hinges are loose.")}
if(D("check out","cap")){Bg("The stocking hats of the dwarf are sitting on the table.")}
if(!E(DS)&&D("anyword","cap")){Bg("Those hats wouldn't fit you.")}
if((D("open","chest")||D("lift","lid"))){if(!BO(Ego,95,120,122,147)){Bg("You are too far away.");A(5);break}
if(J(v85,1)){Bg("The trunk lid is already open.")}
if(J(v85,0)){AQ(o2,f169);L(v85,1);F(f36)}}
case 5:if((D("close","chest")||D("close","lid"))){if(!BO(Ego,95,120,122,147)){Bg("You are too far away.");A(6);break}
if(J(v85,0)){Bg("The lid of the trunk is already closed.")}
if(J(v85,1)){AR(o2,f169);L(v85,0)}}
case 6:if(D("look in","chest")){if(!J(v85,1)){Bg("You will have to open it to see inside.");A(7);break}
if((E(f78)||!E(f133)||E(f80)||E(f77)||E(f81)||E(f79))){Bg("You look inside and notice...");if((E(f78)||!E(f133))){Bg("earrings")}
if(E(f80)){Bg("bracelet")}
if(E(f77)){Bg("necklace")}
if(E(f81)){Bg("brooch")}
if(E(f79)){Bg("tiara")}
A(7);break}
Bg("You look inside and notice...nothing.")}
case 7:if(!E(f112)&&(D("acquire","broth")||D("acquire","cauldron"))){BC(Ego,o3,v94);if(N(v94,15)){Bg("You are too far away.");A(8);break}
Bg("You grab the wooden handle of the bubbling pot of chicken soup. You take the pot with you.");BS("Chicken Soup");p(o3,77);F(f112);W(Cn,2)}
case 8:if(J(v85,1)&&D("acquire","earrings")){if((E(f78)||!E(f133))){F(f133);G(f78);Bg("You reach into the trunk and get it.");BS("Earrings");W(Cn,7);A(9);break}
G(DS)}
case 9:if(J(v85,1)&&E(f80)&&D("acquire","bracelet")){Bg("You reach into the trunk and get it.");G(f80);BS("Bracelet");W(Cn,7)}
if(J(v85,1)&&E(f77)&&D("acquire","diamond and sapphire necklace")){G(f77);Bg("You reach into the trunk and get it.");BS("Necklace");W(Cn,7)}
if(J(v85,1)&&E(f81)&&D("acquire","brooch")){Bg("You reach into the trunk and get it.");G(f81);BS("Brooch");W(Cn,7)}
if(J(v85,1)&&E(f79)&&D("acquire","diamond and sapphire tiara")){G(f79);Bg("You reach into the trunk and get it.");BS("Tiara");W(Cn,7)}
if(BO(Ego,40,113,64,130)&&D("light","candle")){F(f106)}
if(BO(Ego,40,113,64,120)){if(!E(f37)){Bg("OUCH!!!! This fire is HOT! You're going to burn yourself.");F(f37)}
A(10);break}
G(f37);case 10:if(J(Cm,4)){H(73);if(AGI.C)return}
if(E(f34)){G(f34);p(Ego,115);if(BO(Ego,16,117,60,167)){AK(Ego);AL(Ego,v105,v106);Y(v105,15);AH(Ego,v105,v106);AJ(Ego)}
Ag(Ego);F(f92);AQ(Ego,f35);AC(Ego,15);Aa(Ego)}
if(E(f35)){G(f92);G(f35);p(Ego,0);AE(Ego);H(46);if(AGI.C)return}
return}}}
MESSAGES[74]=["","You have stumbled onto the home of the thieving dwarf! Unfortunately for you, he is home!","It seems you have entered the underground home of the little dwarf. It is cozy, with a fire crackling in the hearth. A pot of chicken soup bubbling above the fire gives a delicious aroma to the room. There is a trunk tucked away in the corner.","It seems you have entered the underground home of the little dwarf. It is cozy, with a fire crackling in the hearth. There is a trunk tucked away in the corner.","There is a pot of chicken soup boiling over the fire.","The fire is crackling merrily in the fireplace.","The trunk looks old and worn. The hinges are loose.","You look inside and notice...","You look inside and notice...nothing.","The trunk lid is already open.","earrings","bracelet","necklace","brooch","tiara","The lid of the trunk is already closed.","You grab the wooden handle of the bubbling pot of chicken soup. You take the pot with you.","You reach into the trunk and get it.","","You are too far away.","You will have to open it to see inside.","The stocking hats of the dwarf are sitting on the table.","Those hats wouldn't fit you.","OUCH!!!! This fire is HOT! You're going to burn yourself."];CONTROLS[74]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4>.!V<.,>.!5P5<.,>.!5P5<.,>.!5P5<.,KVUaPVPQ<.K5PV<.xK5P5U5U5P5P5P5K5<.K5ELK5K5<.ZK5P5U5U5P5P5P5K5<.K5E5K5E5K5K5<.EK5P5U5U5P5P5P5K5<.K5E5P595K5K5<.EK5P5U5U5P5P5P5K5<.K5E5UAK5K5<.EK5P5U5U5P5P5P5K5<.K5E5ZAE5K5<.EK5P5U5U5P5P5P5K5<.K5E5lFK5<.EK5P5U5U5P5P5P5K5<.K5E5x5K5<.EK5P5U5U5P5P5P5K.m.!5E5x5K5<.E4QKmK5PyK59.QE.@E5!5E5<.EUaUmZ.@EFK.hE5^595<.E.PF<UFE.=^595<.E<.,Q<lA<.E><+5<.E><{5<.9><,5<.4><,5<.4><.45<,><.95<{><.E5<+><.E5<+><.K5<^<.9y<.l5<!<{FE5K5Kh<.EA<r<^AU5K5K5EA<.Z5<r<xA95U5K5K5KQ<Z*<r<lFE5U5K5K5K5E59L<K5K5K5E5<r<g5E5E5U5K5K5K5E5E595<K5K5K5E5<r<Z5K5E5U5K5K5K5E5E595<P5E5K5E5<r<Z5K5E5U5K5K5K5E5E595<P5E5K5E5<r<UAK5E5U5K5K5K5E5E5E5<P595K5E5<r<UAK5E5U5K5K5K5E5E5EA{5.UAK5E5<r<P595K5E5U5K5K5K5E5E5EAgm.PAK5K5<l<P595K5E5U5K5K5K5E5E5EAUAE5P59A.Km<l.Uhg595K5E5U5K5K5K5E5E5KAK5P5P5K5.!5<g.KAP5KAP5E5K5E5U5K5K5K5E5E5K595E5P5P5K5.^5<Z.E5Z5P5P5E5K5E5U5K5K5K5E5E5K5E595P5P5EF.^5<U.E5Z5P5P5E5K5E5U5K5K5K5E5E5K5E5E5K5PF.,5<U.KAP5K5U5E5K5E5U5K5K5K5E5E5K5E5K5E5KA<E5<P.UAE5K5U5E5K5E5U5K5K5K5E5E5K5E5PV<U5<K.gVg595K5E5U5K5K5K5E5E5K5E5<.45<E<P595K5E5U5K5K5K5E5E5K595<.95<E<UAK5E5U5K5K5K5E5E5K595<.E5<9<UAK5E5U5K5K5K5E5E5KA<.P5<4<ZAE5E5U5K5K5K5E5E5KA<.U5.,<Z59595E5U5K5K5K5E5E5K5<.Z5.,<rAE5U5K5K5K5E5E5E5<.l5.{<xA95U5K5K5K5E5E595<.x5.+<^AU5K5K5K5E5E595<.!A.!<+AP5K5K5K5E5EA<.{5.x<,AE5K5K5K5EF>95.r<.9FK5K5K59A>PA.g<.K=>l5.Z/x5.U/x5.U/!5.P/!5.P/^5.K/^5.K/!5.P4/@.P";