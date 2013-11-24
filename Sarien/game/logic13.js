window.logic13=function()
{while(1){switch(B)
{case 0:if(E(DT)){CY(97);CY(104);if((BT("Oil Lamp")||BT("Carpet"))){CY(65);CY(98)}
BY(151);if(AGI.C)return;BY(101);if(AGI.C)return;BY(158);if(AGI.C)return;BY(154);if(AGI.C)return;CW(Ck);BF(101);if(AGI.C)return;BF(154);if(AGI.C)return;BJ(Ck);AY(Ego);AJ(Ego);BM()}
if(!E(DO)){if((BO(Ego,75,99,128,123)||BO(Ego,76,74,120,98)||BO(Ego,83,46,113,73)||BO(Ego,77,45,87,58)||BO(Ego,121,78,129,86)||BO(Ego,80,77,118,92)||BO(Ego,80,93,122,101)||BO(Ego,121,65,141,79))){F(DO);F(f116)}}
if(!N(v95,0)&&E(DO)&&!E(DR)){AL(Ego,v67,v68);if(BO(Ego,0,60,13,68)){L(v67,3);L(v68,75);F(f116)}
if(BO(Ego,77,45,87,58)){L(v67,83);L(v68,51);F(f116)}
if(BO(Ego,82,45,98,53)){L(v67,92);L(v68,53);F(f116)}
if(BO(Ego,99,45,116,53)){L(v67,108);L(v68,53);F(f116)}
if(BO(Ego,117,45,128,53)){L(v67,114);L(v68,54);F(f116)}
if(BO(Ego,132,65,147,76)){L(v67,130);L(v68,72);F(f116)}
if(BO(Ego,14,60,66,68)){L(v67,6);L(v68,71);F(f116)}
if(BO(Ego,22,69,36,78)){L(v67,18);L(v68,82);F(f116)}
if(BO(Ego,37,69,51,78)){L(v67,34);L(v68,83);F(f116)}
if(BO(Ego,119,53,143,57)){L(v67,110);L(v68,54);F(f116)}
if(BO(Ego,112,58,135,69)){L(v67,115);L(v68,71);F(f116)}
if(BO(Ego,65,109,159,134)){W(v67,251);W(v68,250);F(f116)}
if(BO(Ego,107,78,134,102)){F(f116);AL(Ego,v67,v68);Y(v67,20)}
if(BO(Ego,115,77,159,107)){F(f116);W(v68,6);Y(v67,12);F(f116)}}
if(!N(v95,0)&&E(DO)&&E(DR)){if(BO(Ego,107,78,134,102)){F(f116);AL(Ego,v67,v68);Y(v67,20)}}
if(E(DR)&&J(v95,2)&&N(Cr,1)&&P(Cr,5)){G(DO);F(f118);AL(Ego,v67,v68);if(P(v68,84)){L(v67,135);L(v68,78);A(1);break}
L(v67,129);L(v68,90)}
case 1:if((D("check out","lake")||D("check out")||D("check out","area"))){Bg("This is a pretty little pond set among the trees. A group of boulders are reflected in the clear water.")}
if(D("check out","boulder")){Bg("There is a small opening at the base of one of the large boulders.")}
if((D("check out","hole")||D("look in","hole"))){if(!BO(Ego,39,57,55,84)){Bg("You can't see into the opening from where you are.");A(2);break}
if(!E(f66)){if(!E(f156)){W(Cn,1);F(f156)}
Bg("There is a glittering diamond and sapphire brooch lying on the ground in the opening between the rocks!");A(2);break}
Bg("There is nothing in the opening at the base of the rock.")}
case 2:if(!((D("acquire","brooch")||D("acquire","jewelry")))){A(500);break}
if(!(!E(f66))){A(501);break}
if(!(BO(Ego,39,57,55,84))){A(502);break}
Bg("You get the brooch.");BS("Brooch");F(f66);W(Cn,7);A(3);break;case 502:Bg("You can't reach it from here!");case 3:A(4);break;case 501:Bg("It's not there.");case 500:case 4:if(J(Cm,1)){H(6);if(AGI.C)return}
if(J(Cm,2)){H(14);if(AGI.C)return}
if(J(Cm,4)){H(12);if(AGI.C)return}
if(J(Cm,3)){H(20);if(AGI.C)return}
BF(151);if(AGI.C)return;BF(101);if(AGI.C)return;BF(158);if(AGI.C)return;BF(154);if(AGI.C)return;return}}}
MESSAGES[13]=["","This is a pretty little pond set among the trees. A group of boulders are reflected in the clear water.","There is a small opening at the base of one of the large boulders.","There is a glittering diamond and sapphire brooch lying on the ground in the opening between the rocks!","There is nothing in the opening at the base of the rock.","You get the brooch.","You can't reach it from here!","It's not there.","You can't see into the opening from where you are."];CONTROLS[13]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4<.l5K5><K<.l5K5<.+5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.l5K5<.x5E5<U<.rL<.!F<U?4?4?4,a>.PDKD<,{5g5<.xO!%KO<+{5l5<.r.~KdZw.x{5r5<.r.wK.%.U,5ZA<.x.kU.].K.45P5<.^.dZ<3.9.959A<.+.Tl<8.4.E5<.,.OEDU.;.E>.E.dg.-.K>.K.Yg.w.Z>.K.Tr.J.^>.Z.Dl.8.,>.l.3g.8<4>.r]lwKJ<9>.x-rd<r>4h.E;gd<r.4Y<PaE}r]gk<l{.Y.ELK5E5E5K5xAg%xq<Z^.q,Ag5E5E5K5^5U%!w<Ur.-+5r5E5E5K5+5P~x]<KK<J+5r5E5E5K5+5K~!.8<44<J,5x5E5E5K5{5%+.Y.x4.;.E5!5E5E5K5{5~{.q.g4.-.K5^5E5E5K5,5q.4.d+8x4.%.P5^5E5E5K5{59w,.d+Dr4.~.P5+5E5E5K5{5%KDx.Y+Dr4.q.ZQr5E5E5K5ga.8r.k+Dr4.w.r5r5EQE5g5.Ox.w^8!4.w.r5r59L85E5g5.Ox.w.l4.~.lAEAKFT959QEA.J^.q.l4.%.PTADFqFOA.T{.d.l4<Jl<.dg8r.O.r4><398KTr.O.r4><39k!.JZL,4><3EJ9J!.D7ELP5{4><3EJE8+;C9ArA^4><3KD.4-979A+5!4><8EJ.4w9CA.45x4><8KD.EYE795.E5x4><8K8.PO9CEsr5x4><8.KJKD97+5l5!4><8.EkC{5g5^4><8.Ed7.45Z5+4>.;.UY97,5U5{4>.].P89d97{5U5{4>.-.Zq97+5P5,4>.~P8.Kw97^5P5,4>.wPD.Pw97^A95.44>.;.Zw9C^A.44>.;.g~97.+4>.].g-97.^4>.]U8,.397.!4>.-PO{.897.x4>.%KT.4.D7.r4>.~KT.E.J.l4>.wEY.Z.J.U4>.q9d.x.O.94><3.x.w^E>.-U8.U<8UP>.~KJ.P<dZ>.q9T.9<wl>.-.4<~x>.w.E<w^>.d!8l<q.4>.3Z8gJg<k.K>%ZD98UOl<Y.l>YZTUTx<J.{<.;ZYUT^<8<P<.qUdUYx<D<x<.DUkUYl<O<+<]UqUqP<T<+<.3EwU<.D<{<.~Z<.8<.9<.kZ<.8<.K<.YZ<.8<.K<.YZ<.8<.P<.TZ<.8<.U<.OZDZ<q<.l<.8.l.;<.^<w<.x<.,<J<.{>E.3>{?4?4?4?4?4?4?4?4?4?4?4?4?4><x5<.U><lA95<.P><ZAP5<.K><Us<.9><U5g5<.E><ZAP5<.K><lAE5<.K><xA<.P?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4";