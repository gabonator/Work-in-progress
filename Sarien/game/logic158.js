window.logic158=function()
{while(1){switch(B)
{case 0:if(E(f64)){A(1);break}
if((J(Ck,14)||J(Ck,37)||J(Ck,38))){if((D("check out","area")||D("check out"))){Bg("What a lovely little lake! Its sparkling water looks so clean and fresh. An unclimable cliff rises abruptly to the east.")}
if(D("check out","lake")){Bg("What a lovely little lake! Its sparkling water looks so clean and fresh.")}}
if(!J(Ck,13)){if((D("check out","lake")||D("check out")||D("check out","area"))){Bg("What a lovely little lake! Its sparkling water looks so clean and fresh.")}}
if(D("enter","lake")){Bg("Do you want to swim in the lake?")}
if(D("acquire","lake")){Bg("There is no reason for you to obtain water. Why don't you just drink some water if you are really that thirsty?")}
if(N(v95,0)&&D("look under","lake")){Bg("You dip your head under the clear blue water. You see the bottom of the lake.")}
if((D("acquire","drink")||D("drink","lake"))){if(J(Ck,9)&&(BO(Ego,0,42,79,145)||BO(Ego,80,36,159,145))){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,10)&&BO(Ego,0,0,58,95)){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,12)&&(BO(Ego,100,61,130,104)||BO(Ego,131,52,159,120))){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,13)&&(BO(Ego,0,46,62,145)||BO(Ego,63,28,159,143))){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,14)&&BO(Ego,0,86,83,138)){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,33)&&BO(Ego,126,53,159,117)){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,34)&&(BO(Ego,0,30,75,117)||BO(Ego,76,31,159,136))){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,35)&&BO(Ego,0,75,50,127)){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,37)&&(BO(Ego,44,27,159,81)||BO(Ego,63,82,159,160))){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
if(J(Ck,38)&&BO(Ego,0,33,109,167)){Bg("Ahhhhh! The clear lake water is so refreshing.");A(1);break}
Bg("You need to be a little closer to drink the water.")}
case 1:return}}}
MESSAGES[158]=["","What a lovely little lake! Its sparkling water looks so clean and fresh.","Do you want to swim in the lake?","There is no reason for you to obtain water. Why don't you just drink some water if you are really that thirsty?","Ahhhhh! The clear lake water is so refreshing.","You need to be a little closer to drink the water.","You dip your head under the clear blue water. You see the bottom of the lake.","What a lovely little lake! Its sparkling water looks so clean and fresh. An unclimable cliff rises abruptly to the east."];