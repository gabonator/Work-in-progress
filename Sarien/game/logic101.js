window.logic101=function(){while(1){switch(B){case 0:if(E(DT)){F(f115);G(f124);return}
if((E(f147)||N(v51,2)||N(v86,0))){A(7);break}
if(!(!E(f124))){A(500);break}
if(!((D("swim","anyword")||D("enter","swim")||D("swim")||BL(c22)))){A(501);break}
F(f124);if(!(!E(DO))){A(502);break}
Bg("You need to be in the water in order to swim.");A(1);break;case 502:if(!(E(DO)&&J(v95,2))){A(503);break}
Bg("You are already swimming!");A(1);break;case 503:G(DS);case 501:case 1:A(2);break;case 500:if(!BL(c22)){G(f124)}
case 2:if(!(E(DO))){A(504);break}
if(!(!N(v95,0))){A(505);break}
F(f92);L(v52,250);L(v95,1);if(!(E(f116))){A(506);break}
Ay(Ego,v67,v68);A(3);break;case 506:As(Ego);case 3:AL(Ego,v67,v68);p(Ego,104);L(v94,2);AS(Ego,v94);Ag(Ego);if(!((E(f64)||E(f184)))){A(507);break}
L(v86,25);case 507:A(4);break;case 505:if(!(!E(f64)&&(D("swim")||D("enter","swim")||D("swim","anyword")||BL(c22)))){A(508);break}
p(Ego,97);L(v94,1);AS(Ego,v94);Ah(Ego);AL(Ego,v67,v68);L(v82,0);Al(Ego,v67,v68,v82,f169);L(v95,2);case 508:case 504:case 4:if(J(v95,1)&&!N(v86,0)){if(J(v52,0)){F(f185);L(v86,25);A(5);break}
U(v52)}
case 5:if(!E(DO)&&J(v95,2)){G(f92);L(v95,0);p(Ego,0);L(v94,1);AS(Ego,v94);if(E(f118)){Ay(Ego,v67,v68);A(6);break}
At(Ego)}
case 6:G(f116);G(f118);L(v67,0);L(v68,0);case 7:U(v86);if(J(v86,10)){if(E(f64)){Bg("This is a poisoned lake! Too bad, you die of extreme poisoning.");A(8);break}
if(E(f184)){Bg("The water is too turbulent to swim in. You have just drowned.");A(8);break}
if(E(f185)){Bg("You splash around in the water for a while but seem to have forgotten how to swim. Unfortunately, you drown.")}}
case 8:if(J(v86,1)){AK(Ego);F(f50)}
return}}}
MESSAGES[101]=["","You splash around in the water for a while but seem to have forgotten how to swim. Unfortunately, you drown.","This is a poisoned lake! Too bad, you die of extreme poisoning.","You need to be in the water in order to swim.","You are already swimming!","The water is too turbulent to swim in. You have just drowned."];