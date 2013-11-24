window.logic156=function()
{while(1){switch(B)
{case 0:if(E(DT)){G(f93);return}
if(E(f147)){A(4);break}
if(!E(f64)){A(4);break}
if(D("check out","bush")){Bg("The bushes are nothing but leafless dry sticks.")}
if(D("anyword","blossom")){Bg("What flowers? Why would you think flowers could grow around this stinking lake?")}
if(D("look across","lake")){Bg("There is a desolate island in the middle of the poisoned lake.")}
if((D("check out","lake")||D("check out")||D("check out","area"))){Bg("This lake is foul and stinking! It may be poisoned. All vegetation looks dead around it.")}
if((D("acquire","lake")||D("acquire","lake"))){Bg("There is no reason for you to carry around this foul water.")}
if(D("check out","island")){Bg("There is a dreary-looking castle on the island.")}
if((D("cross","lake")||D("enter","island"))){Bg("The lake is foul and toxic. How could you get across it?")}
if(D("check out","antique shop")){if(J(Ck,32)){Bg("The castle on the island looks dark and forbidding. It is surrounded by thorns and brambles. You wonder who would live there.");A(1);break}
Bg("It is difficult to see any details of the castle from here.")}
case 1:if(!((D("acquire","drink")||D("drink","lake")))){A(500);break}
if(!(J(Ck,10)&&(BO(Ego,93,157,119,167)||BO(Ego,101,143,125,156)||BO(Ego,109,130,159,142)||BO(Ego,124,119,159,129)))){A(501);break}
A(2);break;case 501:if(!(J(Ck,11)&&BO(Ego,0,103,159,167))){A(502);break}
A(2);break;case 502:if(!(J(Ck,12)&&(BO(Ego,0,124,36,167)||BO(Ego,37,135,55,167)||BO(Ego,56,142,75,167)))){A(503);break}
A(2);break;case 503:if(!(J(Ck,17)&&(BO(Ego,95,0,159,51)||BO(Ego,96,52,131,72)||BO(Ego,78,73,121,95)||BO(Ego,60,96,118,167)))){A(504);break}
A(2);break;case 504:if(!(J(Ck,19)&&(BO(Ego,0,0,65,76)||BO(Ego,0,77,75,107)||BO(Ego,0,108,93,167)))){A(505);break}
A(2);break;case 505:if(!(J(Ck,24)&&(BO(Ego,72,0,159,96)||BO(Ego,51,97,159,167)))){A(506);break}
A(2);break;case 506:if(!(J(Ck,25)&&BO(Ego,0,145,159,167))){A(507);break}
A(2);break;case 507:if(!(J(Ck,26)&&(BO(Ego,0,0,92,81)||BO(Ego,0,82,82,167)))){A(508);break}
A(2);break;case 508:if(!(J(Ck,31)&&(BO(Ego,38,0,79,93)||BO(Ego,40,94,114,122)||BO(Ego,115,101,159,124)))){A(509);break}
A(2);break;case 509:if(!(J(Ck,32)&&BO(Ego,0,0,159,136))){A(510);break}
A(2);break;case 510:if(!(J(Ck,33)&&(BO(Ego,0,0,80,85)||BO(Ego,0,86,78,100)||BO(Ego,0,101,70,110)||BO(Ego,0,111,50,130)))){A(511);break}
A(2);break;case 511:Bg("You need to be a little closer to drink the water.");A(3);break;case 2:Bg("You bend over and take a deep drink of the stinking water. Oh, dear, the lake is toxic! You die of extreme poisoning.");F(f147);AL(Ego,v67,v68);if(!(P(v68,45))){A(512);break}
L(v67,0);L(v68,5);Aw(Ego,v67,v68);case 512:Ad();F(f92);p(Ego,92);L(v94,3);AS(Ego,v94);AQ(Ego,f93);case 500:case 3:if((D("check out","tree")||D("check out","tree")||D("climb","tree"))){Bg("The trees around the poisoned lake are dead.")}
case 4:if(E(f93)){AC(Ego,15);p(Ego,91);F(f50)}
return}}}
MESSAGES[156]=["","This lake is foul and stinking! It may be poisoned. All vegetation looks dead around it.","There is no reason for you to carry around this foul water.","You bend over and take a deep drink of the stinking water. Oh, dear, the lake is toxic! You die of extreme poisoning.","The trees around the poisoned lake are dead.","The bushes are nothing but leafless dry sticks.","What flowers? Why would you think flowers could grow around this stinking lake?","You need to be a little closer to drink the water.","There is a desolate island in the middle of the poisoned lake.","There is a dreary-looking castle on the island.","It is difficult to see any details of the castle from here.","The castle on the island looks dark and forbidding. It is surrounded by thorns and brambles. You wonder who would live there.","The lake is foul and toxic. How could you get across it?"];