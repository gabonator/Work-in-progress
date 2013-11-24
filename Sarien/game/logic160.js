window.logic160=function()
{while(1){switch(B)
{case 0:if(!E(f238)&&E(DT)){F(f238);G(f132);l(0,255,v241);if(P(v241,100)){F(f234);l(40,255,v58);l(1,3,v59);CY(115);CY(18);CY(112);CY(95);CY(19);CX(27);L(v94,2);Ai(o4,v94);m(o4);p(o4,18);At(o4);if(J(Ck,19)){AG(o4,140,80)}
if(J(Ck,20)){AG(o4,33,63)}
if(J(Ck,21)){AG(o4,80,126)}
if(J(Ck,26)){AG(o4,102,85)}
if(J(Ck,27)){AG(o4,84,126)}
if(J(Ck,28)){AG(o4,72,143)}}
return}
if(!(!E(f132)&&E(f234))){A(500);break}
U(v58);if(!(J(v58,1))){A(501);break}
U(v59);if(!(J(v59,0)&&!J(v88,1))){A(502);break}
F(f132);AJ(o4);Am(o4,5,f232);F(f236);BN(5,f169);if(!(J(v55,0)&&J(v57,0))){A(503);break}
Bg("You have run into an evil enchanter! Get out of there fast, before he turns you into something!");A(1);break;case 503:Bg("You have run into an evil enchanter! Let's hope the fairy's spell works!");case 1:A(2);break;case 502:L(v58,250);case 501:case 500:case 2:if(!E(f132)){A(7);break}
if(!E(DQ)){A(3);break}
if(D("check out","count dracula")){Bg("The enchanter is tall and stately with a black flowing robe and a long white beard. He has an evil gleam in his piercing black eyes.")}
if(D("acquire","count dracula")){Bg("The evil enchanter is magic! There is nothing you can do!")}
if(D("capture","bitch")){Bg("The evil enchanter is magic! There is nothing you can do!")}
if(D("speak","count dracula")){Bg("Stopping to talk to the wicked enchanter could be big trouble!")}
if((D("hello","anyword")||D("say","hello"))){Bg("Stopping to talk to the wicked enchanter could be big trouble!")}
if(D("kill","count dracula")){Bg("The evil enchanter is magic! There is nothing you can do!")}
case 3:if(J(Ck,20)){if(BO(Ego,72,107,114,145)){F(DP)}
if(BO(o4,72,132,86,144)){if(!E(f236)){AL(o4,v105,v106);Z(v67,v105);Z(v68,v106);Aw(o4,v67,v68)}
A(4);break}
AL(o4,v67,v68)}
case 4:if((E(DP)||E(f148))){if(E(f236)){An(o4);G(f236)}
A(5);break}
if(!E(f236)){Am(o4,5,f232);F(f236)}
case 5:if(E(f232)&&J(v88,0)){G(f232);if(J(v55,0)&&J(v57,0)){G(f55);F(f181);Ad();Ag(Ego);Ah(Ego);L(v94,3);Aj(o4,v94);p(o4,112);w(o4,0);AQ(o4,f231);AF(o4,v94);W(v94,1);AD(Ego,v94);A(6);break}
p(o4,115);AQ(o4,f237)}
case 6:if(E(f237)){G(f237);AK(o4);G(f234);G(f132)}
if(E(f231)){G(f231);F(f92);if(J(Ck,20)){AY(Ego);if(BO(Ego,69,36,159,106)){AC(o4,9)}}
p(Ego,95);AQ(Ego,f233)}
if(E(f233)){G(f233);p(o4,19);AK(Ego);An(o4);if(BO(Ego,69,36,159,106)){AE(o4)}
L(v96,3);AM(o4);F(f235);L(v240,100);Bg("Poooooof!!! The evil enchanter has turned you into a cute little froggy. Ribbit, ribbit!")}
U(v240);if(J(v240,1)){F(f50)}
if(E(f235)){G(f235);BN(27,f235)}
A(8);break;case 7:if(D("anyword","count dracula")){Bg("He's not here.")}
case 8:return}}}
MESSAGES[160]=["","You have run into an evil enchanter! Get out of there fast, before he turns you into something!","The enchanter is tall and stately with a black flowing robe and a long white beard. He has an evil gleam in his piercing black eyes.","The evil enchanter is magic! There is nothing you can do!","Stopping to talk to the wicked enchanter could be big trouble!","Poooooof!!! The evil enchanter has turned you into a cute little froggy. Ribbit, ribbit!","He's not here.","You have run into an evil enchanter! Let's hope the fairy's spell works!"];