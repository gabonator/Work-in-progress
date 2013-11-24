window.logic40=function()
{while(1){switch(B)
{case 0:if(E(DT)){if((BT("Oil Lamp")||BT("Carpet"))){CY(65);CY(98)}
BY(151);if(AGI.C)return;BY(162);if(AGI.C)return;CW(Ck);BF(162);if(AGI.C)return;BJ(Ck);AJ(Ego);BM()}
if(D("check out","tree")){Bg("There is a sizable hole in one of the pine trees.")}
if(!((D("check out","hole")||D("look in","hole")))){A(500);break}
if(!(BO(Ego,71,74,95,104))){A(501);break}
if(!(!E(f84))){A(502);break}
Bg("When you peek into the hole of the pine tree, you see a mallet lying there.");A(1);break;case 502:Bg("When you peer into the hole of the old pine tree, you see that it is empty.");case 1:A(2);break;case 501:Bg("You cannot see into the hole from here.");case 500:case 2:if(!(D("acquire","hammer"))){A(503);break}
if(!(!E(f84))){A(504);break}
if(!(BO(Ego,72,36,96,108))){A(505);break}
Bg("You pick up the mallet and carry it with you.");W(Cn,2);BS("Mallet");F(f84);A(3);break;case 505:Bg("You cannot reach it from here.");case 3:A(4);break;case 504:Bg("You have already taken the mallet from the hole in the tree.");case 503:case 4:if(J(Cm,1)){H(33);if(AGI.C)return}
if(J(Cm,2)){H(41);if(AGI.C)return}
if(J(Cm,4)){H(39);if(AGI.C)return}
if(J(Cm,3)){H(47);if(AGI.C)return}
BF(151);if(AGI.C)return;BF(162);if(AGI.C)return;return}}}
MESSAGES[40]=["","There is a sizable hole in one of the pine trees.","When you peek into the hole of the pine tree, you see a mallet lying there.","When you peer into the hole of the old pine tree, you see that it is empty.","You pick up the mallet and carry it with you.","You cannot see into the hole from here.","You cannot reach it from here.","You have already taken the mallet from the hole in the tree."];CONTROLS[40]="?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4/.x595K<.U5>.g5KVK595K<.U5>.g5K5P5K595K<.U5>.g5K5P5K595K<.E5E5>.g5K5P5K595K<{5K5E5>.g5K5P5K595K<{5K5E5>.g5K5P5K5E5E<{5K5E5>.g5K5P5K5E5E<{5K5E5>.g5K5P5K5E5E<{5K5E5>.g5K5P5K5E5E<{5K5E5>.g5K5P5K5E5E<{5K5E5>.g5K5P5959595K<{5K5E5>.g5K5P59F95K<{5K5E5>.g5K5PA9595P<{5K5E5>.g5K5PAE5U<{5K5E5>.lA95PAl<{5KF>.!AP5r<,F>.,AK5r/.KFx/.U5x?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4+F/.4!AKA/{rAZ5/{r5ZA/{xAEA/.4^A/.E?4?4?4?4?4?4?4?4?4?4?4?4><.Pa<U><^h9@.,><xLK5K5P5K5E5.{><r5E5P5K5P5K5E5.{><l5K5P5K5P5K5K5.+><l5K5P5K5P5K5P5.^><g5P5P5K5P5K5U5.!>ZQ.!5U5P5K5P5K5U5.!>EL95KL.l5P5PQP5K5Z5.x>4A95K5K5KA.gAE5EaP5K5U5.!<.{AK5K5K5K595.lQgmKA.^<.^FP5K5K5K595<lLK5.{<.xAE5P5K5K5K5E5<!F.,<.r5P5P5K5K5K5Ka>Z<.gFP5P5K5K5K5K5P59F>K<.Z5E5P5P5K5K5K5K5P5KL>4<.U5K5P5P5K5K5K5K5P5K5KA<.{<.KAP5P5P5K5K5K5K5P5K5UA<.^<.E5Z5P5P5K5K5K5K5P5K5Z5<.^<.9FU5P5P59A9A95K5K5P5K5Z5<.^<.PVP5PAUAK5K5P5K5U5<.+<.rFE5PAZ5K5K5KFE5KA<.{<.^595P5lA95KLK595E5>4<.+AP5xA9AgQ>9<.{5K5^A>,<.,5E5>.+>4A>.{?4?4?4?4?4?4?4?4?4><ZQ<.U>.,aUF<.E>.!L,A<.4>.lF.UF<+>.g5.!A<!>.UA.{5<x>.P5<45<x>.P5<95<r>.PA.{A<x>.UL,QUA<^>.rL!5PQ<{>.+APQ<.l>.,L<.+?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4?4";