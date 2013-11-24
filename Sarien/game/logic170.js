window.logic170=function()
{while(1){switch(B)
{case 0:if(E(DT)){if((J(Ck,77)||J(Ck,82)||J(Ck,87))){F(f34)}
if((J(Ck,79)||J(Ck,84)||J(Ck,89))){F(f35)}
if(J(Ck,78)){F(f36)}
if(J(Ck,88)){F(f37)}
return}
if(J(v59,1)){AK(Ego);F(f50)}
U(v59);if(J(v63,2)){F(f92);L(v63,3);L(v59,25);Bg("The water is too turbulent to swim in. You have just drowned.")}
if(!E(DQ)&&!BL(c22)){A(10);break}
if((D("check out","island")||D("check out")||D("check out","area"))){if((J(Ck,79)||J(Ck,84)||J(Ck,89))){Bg("The small island offshore has only a few bushes and one large tree growing on it.");A(1);break}
Bg("You can see that the island is really quite small. The foliage is remarkable, though. Plants and flowers have overgrown it, some growing very large in contrast to the tiny island.");if(J(Ck,78)&&!E(f122)){Bg("A glint of metal catches your eye. You look toward the direction of the glint and see an amulet lying on the ground!")}}
case 1:if(D("check out","sky")){Bg("The sky above this crazy world is a gorgeous pink. Where am I? you wonder.")}
if(D("acquire","lake")){Bg("You have no need to carry water.")}
AL(Ego,v105,v106);if(!(!E(DS)&&(D("acquire","drink")||D("drink","lake")))){A(500);break}
if(!(J(Ck,77))){A(501);break}
if(!((BO(Ego,90,48,159,48)||BO(Ego,75,59,93,77)||BO(Ego,55,78,84,113)||BO(Ego,70,144,88,167)))){A(502);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break;case 502:Bg("You need to be a little closer to drink the water.");case 2:A(9);break;case 501:if(!(J(Ck,78))){A(503);break}
if(!((BO(Ego,53,57,112,80)||BO(Ego,35,81,124,122)||P(v106,57)))){A(504);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(3);break;case 504:Bg("You need to be a little closer to drink the water.");case 3:A(9);break;case 503:if(!(J(Ck,79))){A(505);break}
if(!((BO(Ego,0,48,38,55)||BO(Ego,35,56,77,67)||BO(Ego,66,68,92,88)||BO(Ego,59,89,104,113)||BO(Ego,72,114,118,144)||BO(Ego,80,145,119,167)))){A(506);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(4);break;case 506:Bg("You need to be a little closer to drink the water.");case 4:A(9);break;case 505:if(!(J(Ck,82))){A(507);break}
if(!(P(v105,95))){A(508);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(5);break;case 508:Bg("You need to be a little closer to drink the water.");case 5:A(9);break;case 507:if(!(J(Ck,84))){A(509);break}
if(!(N(v105,54))){A(510);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(6);break;case 510:Bg("You need to be a little closer to drink the water.");case 6:A(9);break;case 509:if(!(J(Ck,87))){A(511);break}
if(!((BO(Ego,69,32,111,56)||BO(Ego,38,57,88,142)||BO(Ego,89,104,159,167)))){A(512);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(7);break;case 512:Bg("You need to be a little closer to drink the water.");case 7:A(9);break;case 511:if(!(J(Ck,88))){A(513);break}
if(!(N(v106,134))){A(514);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(8);break;case 514:Bg("You need to be a little closer to drink the water.");case 8:A(9);break;case 513:if(!(J(Ck,89))){A(515);break}
if(!((N(v105,55)||N(v106,135)))){A(516);break}
Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(9);break;case 516:Bg("You need to be a little closer to drink the water.");case 515:case 500:case 9:if((E(f35)||E(f34)||E(f36)||E(f37))){if((D("check out","beach")||D("check out","grass")||D("check out","lake"))){Bg("You are captivated by the beauty of the beach. The dazzling, rainbowlike ocean washes upon it. The blue sand sparkles like finely ground sapphires!")}
if((!J(Ck,78)||P(v106,65))){if((D("swim","anyword")||D("enter","swim")||BL(c22))){Bg("The water is much too turbulent for swimming. If you were to try you would almost certainly drown.");F(DS)}}
if((D("dolphin","anyword")||D("enter","fishing")||D("capture","dolphin")||D("cast","fishing net"))){Bg("You catch nothing.")}}
if(D("check out","tree")){Bg("The trees on this small island are tall, with spreading branches and huge fanlike leaves.")}
if(D("check out","bush")){Bg("The island is completely overgrown with foliage. Huge leaves, flowers, and clinging vines are everywhere.")}
if(D("check out","blossom")){Bg("The brilliant flowers are as big as you are!")}
if(D("check out","boulder")){Bg("The rocks on this island appear to contain large amounts of quartz.")}
if(D("climb","tree")){Bg("The trees are too difficult to climb because of their enormous size.")}
if((D("acquire","blossom")||D("acquire","blossom"))){Bg("The flowers are too large to carry around with you.")}
if(D("smell","blossom")){Bg("The sweet aroma of the huge flowers permeates the air.")}
case 10:if(J(v63,1)){Ay(Ego,v67,v68);p(Ego,104);L(v94,2);AS(Ego,v94);L(v63,2);Ag(Ego)}
return}}}
MESSAGES[170]=["","You can see that the island is really quite small. The foliage is remarkable, though. Plants and flowers have overgrown it, some growing very large in contrast to the tiny island.","You are captivated by the beauty of the beach. The dazzling, rainbowlike ocean washes upon it. The blue sand sparkles like finely ground sapphires!","The water is much too turbulent for swimming. If you were to try you would almost certainly drown.","The trees on this small island are tall, with spreading branches and huge fanlike leaves.","The island is completely overgrown with foliage. Huge leaves, flowers, and clinging vines are everywhere.","The brilliant flowers are as big as you are!","The rocks on this island appear to contain large amounts of quartz.","The trees are too difficult to climb because of their enormous size.","The flowers are too large to carry around with you.","The sweet aroma of the huge flowers permeates the air.","You catch nothing.","The sky above this crazy world is a gorgeous pink. Where am I? you wonder.","YECCHHH!! You cough and choke from the briny water of the ocean.","You have no need to carry water.","You need to be a little closer to drink the water.","The water is too turbulent to swim in. You have just drowned.","A glint of metal catches your eye. You look toward the direction of the glint and see an amulet lying on the ground!","The small island offshore has only a few bushes and one large tree growing on it."];