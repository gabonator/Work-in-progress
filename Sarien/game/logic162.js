window.logic162=function()
{while(1){switch(B)
{case 0:if(!E(f231)&&E(DT)){F(f231);G(f128);l(0,255,v94);if((P(v94,80)||E(f129))){F(f40);CY(28);CY(115);CX(5);m(o2);p(o2,28);L(v94,3);Ai(o2,v94);if(J(Ck,41)){AG(o2,35,45)}
if(J(Ck,46)){AG(o2,32,56)}
if(J(Ck,47)){AG(o2,67,95)}
if(J(Ck,39)){AG(o2,44,79)}
if(J(Ck,40)){AG(o2,22,89)}
l(40,255,v58);l(0,2,v59)}
return}
if(!E(f128)&&E(f40)){U(v58);if(J(v58,1)){U(v59);if(J(v59,0)){F(f128);Am(o2,5,f38);F(f42);BN(5,f169);Bg("You have come upon a quick little dwarf! Dwarves have a bad reputation for stealing treasure.");AJ(o2);A(1);break}
L(v58,250)}}
case 1:if(!E(f128)){A(3);break}
if(!E(DQ)){A(2);break}
if(D("check out","count dracula")){Bg("The dwarf is a very small fellow. For being so little, he is very fast.")}
if((D("acquire","count dracula")||D("capture","count dracula"))){Bg("The dwarf is too fast on his feet. You could never catch him.")}
if(D("speak","count dracula")){Bg("The dwarf doesn't have time to chat with you. He's too busy running around; possibly with your treasure.")}
if((D("hello","anyword")||D("say","hello"))){Bg("The dwarf doesn't have time to chat with you. He's too busy running around; possibly with your treasure.")}
if(D("kill","count dracula")){Bg("The dwarf is too fast on his feet. You could never catch him.")}
case 2:A(4);break;case 3:if(D("anyword","count dracula")){Bg("He's not here.")}
case 4:if((E(DP)||E(f148))){if(E(f42)){An(o2);G(f42)}
A(5);break}
if(!E(f42)){Am(o2,5,f38);F(f42)}
case 5:if(E(f38)){p(o2,115);G(f37);AQ(o2,f37);G(f38);if(J(v55,0)&&J(v57,0)){F(f41);Bg("Oh, no! The dwarf caught you. You should check to see if he stole anything....!");A(6);break}
Bg("The dwarf seems to have left you alone, thanks to your protective spell!")}
case 6:if(E(f37)){AK(o2);G(f37);G(f128);G(f40)}
if(!E(f41)){A(8);break}
if(BT("Necklace")){Y(Cn,7);CL("Necklace");F(f77);A(7);break}
if(BT("Bracelet")){Y(Cn,7);CL("Bracelet");F(f80);A(7);break}
if(BT("Earrings")){Y(Cn,7);CL("Earrings");F(f78);A(7);break}
if(BT("Tiara")){Y(Cn,7);CL("Tiara");F(f79);A(7);break}
if(BT("Brooch")){Y(Cn,7);CL("Brooch");F(f81);A(7);break}
case 7:G(f41);case 8:return}}}
MESSAGES[162]=["","You have come upon a quick little dwarf! Dwarves have a bad reputation for stealing treasure.","The dwarf is a very small fellow. For being so little, he is very fast.","The dwarf is too fast on his feet. You could never catch him.","The dwarf doesn't have time to chat with you. He's too busy running around; possibly with your treasure.","He's not here.","The dwarf seems to have left you alone, thanks to your protective spell!","Oh, no! The dwarf caught you. You should check to see if he stole anything....!"];