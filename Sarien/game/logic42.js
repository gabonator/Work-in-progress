window.logic42=function()
{while(1){switch(B)
{case 0:if(!(E(DT))){A(500);break}
AT(31);CY(8);CY(30);CY(31);CY(32);if(!((BT("Oil Lamp")||BT("Carpet")))){A(501);break}
CY(65);CY(98);case 501:BY(163);if(AGI.C)return;BY(155);if(AGI.C)return;CW(Ck);BJ(Ck);if(!(J(Cl,35))){A(502);break}
AG(Ego,15,32);case 502:AJ(Ego);m(o2);L(v94,3);AS(o2,v94);AY(o2);AG(o2,85,100);if(!(!E(f85))){A(503);break}
p(o2,30);A(1);break;case 503:if(!(!E(f86))){A(504);break}
p(o2,31);A(1);break;case 504:p(o2,32);case 1:w(o2,0);AJ(o2);Az(o2);BM();case 500:if(!E(f85)&&BO(Ego,54,98,84,102)){Aa(Ego);A(2);break}
Ab(Ego);case 2:if(!E(DQ)){A(5);break}
if(D("check out","door")){Bg("This is a magical door! If you can open it, the door will lead you to your heart's desire. There is an inscription on the door.")}
if((D("check out")||D("check out","area"))){Bg("You are at the edge of the forest. There is a deep chasm to the west and a towering cliff to the east.")}
if(E(f35)&&!D("y")){G(f35)}
BC(Ego,o2,v94);if(N(v94,25)){if((D("anyword","door")||D("anyword","key hole")||D("anyword","inscription"))){Bg("You are too far away from the door.");A(5);break}}
AL(Ego,v105,v106);if(P(v106,100)){if((D("anyword","door")||D("anyword","key hole")||D("anyword","inscription"))){Bg("You are on the wrong side of the door to do that.");A(5);break}}
if(!BT("Gold Key")&&D("unlock","door")){Bg("You can't. You don't have the key.")}
if(D("knock","door")){Bg("You don't really expect someone to answer the door, do you?")}
if((D("check out","key hole")||D("look in","key hole"))){Bg("You look through the keyhole and see nothing but a dazzling light.")}
if(E(f85)&&D("close","door")){Bg("If you close the door, it will lock again. Why would you want to do that?")}
if(D("break","door")){Bg("This is a magic door. It is impervious to damage.")}
if(E(f86)){A(4);break}
if(E(f85)){A(3);break}
if(!E(f85)&&D("open","door")){Bg("The door is locked. You cannot open it, no matter how hard you try.")}
if(BT("Gold Key")&&D("unlock","door")){CL("Gold Key");W(Cn,7);BA(o2);p(o2,30);AQ(o2,f173);F(f85);Bg("The key to the first door fits easily into the keyhole. You turn the key and, PRESTO, the door opens, and the key disappears ... revealing a second door with another inscription!")}
if(E(f35)&&D("y")){Bg("The inscription reads: Whosoever chooses to seek the key for this door will undoubtedly make a splash.");F(f67)}
if((D("read","inscription")||D("check out","inscription")||D("read","door"))){Bg("The inscription reads: Whosoever chooses to seek the key for this door will undoubtedly make a splash.");F(f67)}
case 3:if(!E(f86)&&D("open","door")){Bg("The second door is locked. You cannot open it, no matter how hard you try.")}
if(BT("Gold Key")&&D("unlock","door")){CL("Gold Key");W(Cn,7);BA(o2);p(o2,31);AQ(o2,f174);F(f86);Bg("The key to the second door fits easily into the keyhole. You turn the key and, SHAZAM, the door opens, and the second gold key disappears ... revealing a third door with yet another inscription!")}
if(E(f35)&&D("y")){Bg("The inscription reads: Whosoever chooses to seek the key for this door should set their sights high.");F(f134)}
if((D("read","inscription")||D("check out","inscription")||D("read","door"))){F(f134);Bg("The inscription reads: Whosoever chooses to seek the key for this door should set their sights high.")}
case 4:if(!E(f87)&&D("open","door")){Bg("The third door is locked. You cannot open it no matter how hard you try.")}
if(BT("Gold Key")&&!E(f148)&&J(v88,0)&&D("unlock","door")){CL("Gold Key");W(Cn,7);BA(o2);p(o2,32);AQ(o2,f175);F(f87);Bg("The key to the third door fits easily into the keyhole. You turn the key and, PRESTO, the door opens, and again the key disappears ... revealing a world unlike any you've ever seen before!")}
if(E(f35)&&D("y")){Bg("Whosoever chooses to seek the last key must have a stout heart.");F(f75)}
if((D("read","inscription")||D("check out","inscription")||D("read","door"))){Bg("Whosoever chooses to seek the last key must have a stout heart.");F(f75)}
case 5:if(E(f173)){G(f173);Az(o2)}
if(E(f174)){G(f174);Az(o2)}
if(E(f175)){G(f175);AG(Ego,80,80);H(80);if(AGI.C)return}
if(J(Cm,1)){H(35);if(AGI.C)return}
if(J(Cm,2)){H(42);if(AGI.C)return}
if(J(Cm,4)){H(41);if(AGI.C)return}
if(J(Cm,3)){H(49);if(AGI.C)return}
BF(163);if(AGI.C)return;BF(155);if(AGI.C)return;return}}}
MESSAGES[42]=["","This is a magical door! If you can open it, the door will lead you to your heart's desire. There is an inscription on the door.","The door is locked. You cannot open it, no matter how hard you try.","The key to the first door fits easily into the keyhole. You turn the key and, PRESTO, the door opens, and the key disappears ... revealing a second door with another inscription!","You can't. You don't have the key.","Do you want to read the inscription?","The inscription reads: Whosoever chooses to seek the key for this door will undoubtedly make a splash.","If you close the door, it will lock again. Why would you want to do that?","This is a magic door. It is impervious to damage.","The second door is locked. You cannot open it, no matter how hard you try.","The key to the second door fits easily into the keyhole. You turn the key and, SHAZAM, the door opens, and the second gold key disappears ... revealing a third door with yet another inscription!","The inscription reads: Whosoever chooses to seek the key for this door should set their sights high.","The third door is locked. You cannot open it no matter how hard you try.","The key to the third door fits easily into the keyhole. You turn the key and, PRESTO, the door opens, and again the key disappears ... revealing a world unlike any you've ever seen before!","Whosoever chooses to seek the last key must have a stout heart.","You don't really expect someone to answer the door, do you?","You look through the keyhole and see nothing but a dazzling light.","You are too far away from the door.","You are on the wrong side of the door to do that.","You are at the edge of the forest. There is a deep chasm to the west and a towering cliff to the east."];CONTROLS[42]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4{6/.9{6/.9Z6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7>.rZ6g6<.g7<^6<^Z6g6<.g7<^6<^Z6g6<.gj<U6<^Z6g6<+`<^6<^Z6Z6<Zj<.g6<^ZBKG<9S<.,6<^lG<4N>P6<^<gN>l6<^<UC>^6<^<KC>{6<^<9C>.46<^.,C>.E6<^.+C>.P6<^.!C>.Z6<^.rC>.l6<^.gC>.x6<^.UC>.^6<^.KC>.{6<^.9C><46<^.47>.rp6<^{C>l.Cr6<^^C<.!:.^B<xxC<.Uj<+B<lZN<.4c<.g6<g4X<+c<.{6<g<,N>Z6<Z<+C>x6<Z<!C>+6<U<rC>.46<P<l7{b<.{B<E<g7^Gg6<.{B<9<g7xBxB<.!B<K<Z7!6rB<.!B<U<U7+6g6<.!B<g<U7{BP6<.+6<g<P7.9M<.,B<U<P7>.Z6<P<P7>.g6<K<K7>.r6<E<K7>.x6<9<K7>.!B.,<K7>.+6.{<P7>.+6.+<P7>.{B.!<P7><4B.r<K7><KB.g<K7><P6.g<9C><U6.g.,C><g6.g.^H><r6.g.rH>.gB.K6K6K6,.ZH>.ZMEB.96K6K6,.PC>.ZGlB,6K6K6,.9H>.PM+B+6K6K6,{H>.UB.KB!6K6K6,xN>.l6.Z6x6K6K6,gH>.^G.P6x6K6K6,UC><EM.46x6K6K6,EH><l6^G!6K6K6,4C><^6gM{6K6K6,><,6EM.K6E6K6,><.4B.g6E6K6,>.r.1<46E6K6,>.r6{6.,6K6K6,>.r6{6.,6K6K6,>.r6{6.,6K6K6,>.r6{6.,6K6K6,>.r6{6.,6K6K6,>.r6{6.,6K6K6,>.r6{6.,6K6K6,>.r6{6.,6K6K6,>.r6{6.,6KR,>.r6{6.,6.g>.r.1.{6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/g6.l/l6.g/l6.g/l6.g/l6.g/l6.g/l6.g/l6.g.!M><r6.g.ZRPB><g6.g.PB!B><U6.g.K6,B><P6.Z.9B.EB><E6.Z.46.Z6><96.Z{B.g6><96.Z+6.r6><96.Z+6.r6><96.Z{B^BUR><E6.U.46!69R><g6.U.96x6><+6.U.E6l6><{6.U.K6g6><+6.Z.P6Z6><+6.Z.U6U6><+6.Z.U6P6><{6.Z.Z6K6><,6.U.Z6E6><.46.U.gB><.96.U.g6><.E6.U/x6.U/!6.P/!6.P/!6.P/!6.P/x6.U/x6.U/x6.U/x6.U/r6.Z/r6.Z/l6.g/l6.g/l6.g/g6.l/g6.l/g6.l/Z6.r/Z6.r/U6.x/U6.x/U6.x/U6.x/U6.x";