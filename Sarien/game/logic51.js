window.logic51=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
CY(38);CY(39);CY(40);CY(43);CY(41);CY(189);CX(4);m(o3);m(o4);L(v94,5);AS(o3,v94);L(v94,3);AS(o4,v94);L(v94,2);AS(Ego,v94);Ai(Ego,v94);CY(35);CW(Ck);BJ(Ck);Bu(Ck);BD(35,0,0,30,122,10,10);Bw(35);Aa(o3);AC(o3,15);AG(o3,5,110);AN(o3);if(!(E(f95))){A(501);break}
if(!(E(f96))){A(502);break}
p(o3,39);A(1);break;case 502:p(o3,38);case 1:w(o3,0);AJ(o3);A(2);break;case 501:p(o3,38);w(o3,0);AJ(o3);AQ(o3,f169);case 2:AY(o4);Aa(o4);AG(o4,25,101);if(!(E(f97))){A(503);break}
p(o4,40);A(3);break;case 503:p(o4,43);case 3:AJ(o4);BN(4,f169);Aa(Ego);AC(Ego,11);AG(Ego,130,100);AJ(Ego);BM();case 500:if((D("check out","clam")||D("look in","clam"))){if(E(f95)){Bg("The huge %w2 behind Neptune is wide open.");A(4);break}
Bg("The enormous %w2 behind King Neptune is tightly shut.")}
case 4:if(D("check out","count dracula")){Bg("King Neptune is tall and imposing, with a flowing robe and long greenish-gray beard. A crown fashioned of shells and pearls adorns his head.")}
if((D("check out","lake")||D("check out")||D("check out","area"))){Bg("The bottom of the sea is teeming with fish and plant life. King Neptune rules this mighty underwater empire.")}
if(D("check out","magic seahorse")){Bg("This is a larger than average seahorse! It has a little saddle attached to its back.")}
if(D("break","clam")){Bg("There is no need to hurt the %w2.")}
if((D("abracadabra","anyword")||D("open","sesame"))){Bg("That might work with some clams, but not this one!")}
if(D("acquire","clam")){Bg("This is an immense %w2! You couldn't carry it with you.")}
if(!E(f96)){if((D("acquire","key")||D("acquire","gold","key"))){if(!E(f95)){Bg("The %w2 is inside the large clam. You have to open the clam to retrieve the %w2.");A(5);break}
if(BO(Ego,0,112,28,142)){Bg("OK.");BS("Gold Key");W(Cn,5);p(o3,39);F(f96);A(5);break}
Bg("You are not close enough.")}}
case 5:if(D("close","clam")){if(E(f95)){Bg("The %w2 will close when it is ready.");A(6);break}
Bg("The huge %w2 is already closed.")}
case 6:if((D("acquire","magic seahorse")||D("capture","magic seahorse"))){Bg("This is a larger than average seahorse! It has a saddle attached to its back.")}
if((D("climb","magic seahorse")||D("sit","magic seahorse"))){Bg("No!")}
if(D("pat","magic seahorse")){Bg("Ahhhh.........")}
if(D("speak","magic seahorse")){Bg("Does it look like Mr. Ed to you?")}
if((D("speak","count dracula")||D("hello","anyword")||D("anyword","hello"))){Bg("Glub, glub, glub, glub ....... !!!!!!")}
if((D("acquire","count dracula")||D("capture","count dracula"))){Bg("I beg your pardon!?")}
if((D("kill","count dracula")||D("fight","count dracula"))){Bg("Hurting King Neptune would not be a wise thing to do. If he doesn't get you, then his fish will.")}
if(E(f97)&&BO(Ego,0,0,80,160)){if(!E(f95)&&!E(f32)){Bg("With a cold look in his eye, King Neptune takes the rusty trident and points it at you.");p(o4,41);AQ(o4,f31);F(f32)}}
if((D("wave","rusty trident","count dracula")||D("point","rusty trident","count dracula"))){Bg("OK.");A(14);break}
BC(Ego,o4,v94);if(N(v94,60)){if((D("open","clam")||D("give","anyword","count dracula")||D("give","count dracula")||D("wave","rusty trident")||D("point","rusty trident"))){Bg("You are not close enough.");A(14);break}}
if(!((D("give","rusty trident","count dracula")||D("give","count dracula","rusty trident")))){A(504);break}
if(!(BT("Trident"))){A(505);break}
CL("Trident");if(!(E(f95))){A(506);break}
Bg("With a cold look in his eye, King Neptune takes the rusty trident and points it at you.");p(o4,41);AQ(o4,f31);A(7);break;case 506:Bg("Reverently, King Neptune accepts his lost trident from you. He gives you a bottle, then waves the trident in front of the huge clam, which opens and reveals ... a large golden key!");p(o4,40);F(f97);BS("Bottle");W(Cn,4);AR(o3,f95);F(f95);case 7:A(8);break;case 505:Bg("You don't have one to give to King Neptune.");case 504:case 8:if((D("give","treasure","count dracula")||D("give","count dracula","treasure"))){if((BT("Tiara")||BT("Earrings")||BT("Bracelet")||BT("Necklace")||BT("Brooch"))){Bg("Which treasure would you like to give to King Neptune?");A(9);break}
Bg("You don't have one to give to King Neptune.")}
case 9:if(!BT("Tiara")&&D("give","diamond and sapphire tiara","count dracula")){Bg("You don't have one to give to King Neptune.")}
if(!BT("Bracelet")&&D("give","bracelet","count dracula")){Bg("You don't have one to give to King Neptune.")}
if(!BT("Brooch")&&D("give","brooch","count dracula")){Bg("You don't have one to give to King Neptune.")}
if(!BT("Necklace")&&D("give","diamond and sapphire necklace","count dracula")){Bg("You don't have one to give to King Neptune.")}
if(!BT("Earrings")&&D("give","earrings","count dracula")){Bg("You don't have one to give to King Neptune.")}
if(!E(DS)&&D("give","anyword")){if((D("give","count dracula","anyword")||D("give","anyword","count dracula"))){Bg("King Neptune solemnly shakes his head at your offer. A look of dismay clouds his face.");A(10);break}
Bg("You must specify who you wish to give it to.")}
case 10:if((D("open","clam")||D("pry","clam"))){if(E(f95)){Bg("The huge clam is already open.");A(11);break}
Bg("The large %w2 is shut tight. Try as you might, you cannot succeed in opening it.")}
case 11:if(!((D("wave","rusty trident")||D("point","rusty trident")))){A(507);break}
if(!(!E(f95))){A(508);break}
if(!(!BT("Trident"))){A(509);break}
Bg("You don't have it.");A(12);break;case 509:Bg("You wave the crusty %w2 in front of the immense clam and slowly it opens ... revealing a large golden key!");AR(o3,f169);F(f95);W(Cn,2);case 12:A(13);break;case 508:Bg("The huge clam is already open.");case 507:case 13:if(D("get off","magic seahorse")){Bg("The magic seahorse helps you breathe underwater. Without it, you would die.")}
if(D("check out","dolphin")){Bg("You can see many beautiful creatures at the bottom of the sea.")}
case 14:if(E(f31)){Bg("You feel a powerful surge of electricity, and then ... nothing. You have died at the bottom of the ocean.");G(f31);p(Ego,189);F(f50)}
if(J(Cm,2)){AE(Ego);L(v64,2);L(Cr,3);Ad();H(52);if(AGI.C)return}
return}}}
MESSAGES[51]=["","The huge %w2 behind Neptune is wide open.","The enormous %w2 behind King Neptune is tightly shut.","King Neptune is tall and imposing, with a flowing robe and long greenish-gray beard. A crown fashioned of shells and pearls adorns his head.","The bottom of the sea is teeming with fish and plant life. King Neptune rules this mighty underwater empire.","This is a larger than average seahorse! It has a little saddle attached to its back.","The large %w2 is shut tight. Try as you might, you cannot succeed in opening it.","You wave the crusty %w2 in front of the immense clam and slowly it opens ... revealing a large golden key!","The huge clam is already open.","That might work with some clams, but not this one!","There is no need to hurt the %w2.","This is an immense %w2! You couldn't carry it with you.","The %w2 is inside the large clam. You have to open the clam to retrieve the %w2.","Do you want to open the clam?","The %w2 will close when it is ready.","The huge %w2 is already closed.","","This is a larger than average seahorse! It has a saddle attached to its back.","No!","Ahhhh.........","Does it look like Mr. Ed to you?","Glub, glub, glub, glub ....... !!!!!!","I beg your pardon!?","Hurting King Neptune would not be a wise thing to do. If he doesn't get you, then his fish will.","Which treasure would you like to give to King Neptune?","You don't have one to give to King Neptune.","King Neptune solemnly shakes his head at your offer. A look of dismay clouds his face.","Reverently, King Neptune accepts his lost trident from you. He gives you a bottle, then waves the trident in front of the huge clam, which opens and reveals ... a large golden key!","With a cold look in his eye, King Neptune takes the rusty trident and points it at you.","You encounter King Neptune! Oh, oh! He points his rusty trident at you.","You are not close enough.","You don't have it.","The magic seahorse helps you breathe underwater. Without it, you would die.","OK.","You can see many beautiful creatures at the bottom of the sea.","You must specify who you wish to give it to.","You feel a powerful surge of electricity, and then ... nothing. You have died at the bottom of the ocean."];CONTROLS[51]="<E6><.+<E6><.+<E6><.+<E6><.+<E6><.+<E6><.+<E6><.+<E6><.+<E6><.+<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96><.{<96>l6<.U<96>l6<.U<96>l6<.U<96>lB<.P<46>rB<.P<46>rB<.P<46>rB<.P<46>r696<.K<46>r696<.K<46>r696<.K<46>r696<.K<46>r696<.K<46>r6E6<.E<46>r6E6<.E<46>r6E6<.E<46>r6E6<.E<46>r6K6<.9<46>r6K6<.9<46>r6K6<.9<46>r6K6<.9<46>r6K6<.9.,6>x6K6<.9.,6>x6K6<.9.,6>r6P6<.9.,6>r6P6<.9.,6>r6P6<.9.,6>l6U6<.9.,6>l6U6<.9.,6>l6U6<.9.,6>l6Z6<.4.,6>g6g6<.4.,6>g6g6<.4.,6>g6g6<.4.,6>Z6l6<.4.,6>Z6l6<.4<46>U6l6<.4<46>P6r6<.4<46>P6r6<.4<46>K6x6<.4<46>K6x6<.4<46>E6!6<.4<46>96^6<.4<46>96^6<.4<46>46+6<.4<46<.,6{6<.4<46<.,6{6<.4<46<.{6,6<.4<96<.^6.46<.4<96<.^6.46<.4<96<.!6.96<.4<96<.!6.96<.4<96<.x6.E6<.4<96<.x6.E6<.4<96<.x6.E6<.4<E6<.l6.K6<.4<E6<.l6.K6<.4<K6<.Z6.P6<.4<K6<.Z6.P6<.4<P6<.U6.K6<.9<P6<.U6.K6<.9<U6<.P6.K6<.9<U6<.P6.K6<.9<U6<.P6.K6<.9<U6<.P6.K6<.9<U6<.P6.K6<.9<U6<.P6.K6<.9<U6<.U6.E6<.9<U6<.U6.E6<.9<U6<.Z6.96<.9<U6<.Z6.96<.9<U6<.g6.46<.9<U6<.g6.46<.9<U6<.l6,6<.9<U6<.rB+6<.9<U6<.!B!6<.9<U6<.+6x6<.9<U6<.{BUM<.9<U6>4R<.U<U6><.x<U6><.x<U6><.x<U6><.x<U6><.x<U6><.x<U6><.x<U6><.x.+n><.x.Kt/K.4G/++G/.4!B96/.9lGK6/.9ZBZ6/.9PBl6/.9K6r6/.E9Bx6/.E46^6/.E+6/.E+6/.E+6/.E+6/.E+6/.E+6/.E+6/.E^6/.K^6/.K^6/.K^6/.K^6/.K^6/.K!6/.P!6/.P!6<.l6>.!x6<.rB>.xx6<.r69B>.lr6<.x6K6>.gZ5E6<.x6P6>.ZUF96<.x6U6>.UUF6<.!6ZB>.KPL65<.x6l6>.E4s<.x6r6>.94s_.P><.M4y+B.E6><.K4y,6.46><.P4y.46{6><.U4@,G^6><.U4*.9MUG><.Z4=.PR><.r4}><.+V{4.5Ka><{.AU4.@><!.m4.=EL><9.y4<V<!y<g.*4<.A.r.y.^.=4<.yr<V.Z<04><}.4<54><.aZ<F4?04?04?04?04?04?04?04?0";