window.logic50=function()
{while(1){switch(B)
{case 0:if(E(DT)){AT(55);BY(101);if(AGI.C)return;CY(97);CY(104);CY(36);CW(Ck);BJ(Ck);BF(101);if(AGI.C)return;m(o3);p(o3,36);AG(o3,50,50);AJ(Ego);BM();if(!J(Cl,50)){M(v73,Cl);L(v51,1)}}
if(N(v51,2)&&J(v33,0)){Ad();Bg("You are so far out to sea, you have no chance of ever getting back. You can no longer swim.");p(Ego,104);Ag(Ego);Ah(Ego);L(v94,2);AS(Ego,v94);L(v33,50)}
U(v33);if(J(v33,1)){AK(Ego);F(f50);A(6);break}
if(D("check out","lake")){Bg("The clear blue ocean is very calm. You look out over its vastness, seeing nothing but endless water.")}
if(D("check out","dolphin")){Bg("A large, colorful fish playfully leaps out of the water around you.")}
if((D("capture","dolphin")||D("acquire","dolphin"))){Bg("It is very hard to catch fish while swimming.")}
if(D("drink","lake")){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.")}
if(D("look under","lake")){Bg("You dip your head under the ocean water. You see nothing but colorful fish and seaweed.")}
if(E(f31)){G(f31);G(f32);AK(o3);l(0,255,v34)}
if(!(!E(f31)&&!E(f32))){A(500);break}
U(v34);if(!(J(v34,0))){A(501);break}
case 1:l(0,255,v31);if(!((P(v31,45)||N(v31,130)))){A(502);break}
A(1);break;case 502:case 2:l(0,255,v32);if(!((P(v32,60)||N(v32,130)))){A(503);break}
A(2);break;case 503:w(o3,0);AH(o3,v31,v32);BC(o3,Ego,v230);if(!(N(v230,20))){A(504);break}
AJ(o3);AQ(o3,f31);F(f32);case 504:case 501:case 500:if(!(J(Cm,1))){A(505);break}
if(!(J(v73,1))){A(506);break}
L(v73,43);A(3);break;case 506:if(!(J(v73,43))){A(507);break}
L(v73,36);A(3);break;case 507:Y(v73,7);case 3:H(50);if(AGI.C)return;case 505:if(!(J(Cm,3))){A(508);break}
if(!(J(v73,43))){A(509);break}
L(v73,1);A(4);break;case 509:if(!(J(v73,15))){A(510);break}
L(v73,22);A(4);break;case 510:W(v73,7);case 4:H(50);if(AGI.C)return;case 508:if(J(Cm,4)){W(v51,1);H(50);if(AGI.C)return}
if(J(Cm,2)){U(v51);if(J(v51,0)){BK(v73);A(5);break}
H(50);if(AGI.C)return}
case 5:BF(101);if(AGI.C)return;case 6:return}}}
MESSAGES[50]=["","The clear blue ocean is very calm. You look out over its vastness, seeing nothing but endless water.","A large, colorful fish playfully leaps out of the water around you.","It is very hard to catch fish while swimming.","You are so far out to sea, you have no chance of ever getting back. You can no longer swim.","YECCHHH!! You cough and choke from the briny water of the ocean.","You dip your head under the ocean water. You see nothing but colorful fish 