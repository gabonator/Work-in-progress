window.logic152=function()
{while(1){switch(B)
{case 0:if(E(DT)){G(f91);L(v62,0);if(!J(Ck,15)){m(o7);AY(o7);Aa(o7);if(J(Ck,1)){p(o7,1)}
if(J(Ck,8)){p(o7,122);AG(o7,6,113)}
if(J(Ck,22)){p(o7,62);L(v94,2);AS(o7,v94)}
if(J(Ck,29)){p(o7,111);L(v94,2);AS(o7,v94)}
if(J(Ck,36)){p(o7,96)}
if(J(Ck,43)){p(o7,118);L(v94,2);AS(o7,v94)}
w(o7,0);AN(o7);AJ(o7);l(5,80,v62);G(f90)}
return}
U(v62);if(J(v62,1)){F(f90);AQ(o7,f91);if(!N(v88,0)){BN(25,f44)}}
if(E(f91)){G(f91);G(f90);w(o7,0);l(5,80,v62)}
if(E(f41)){U(v40)}
if(E(f41)&&J(v40,0)){G(f41);Bg("Ok. You are all through digging. You find nothing.");Ah(Ego)}
if(E(f41)&&!J(Cr,0)){if(!E(f43)){F(f43);Bg("You can't possibly dig while walking. Stand still.")}}
if(J(Cr,0)&&E(f43)){G(f43)}
if(D("dig","anyword")){if(!J(Cr,0)){Bg("You can't possibly dig while walking. Stand still.");A(1);break}
L(DH,16);Bg("Dig...Dig...Dig...");Bg("Ok. You are all through digging. You find nothing.")}
case 1:if(!J(Ck,22)&&!J(Ck,36)){if((D("check out","beach")||D("check out","area")||D("check out"))){Bg("The glittering white sand of the beach feels warm from the sun. The azure water of the ocean laps up to its edge.")}}
if(D("check out","bush")){Bg("The plants grow well in the moist sea air.")}
if(D("check out","blossom")){Bg("The flowers are a beautiful contrast to the blue ocean.")}
if(D("acquire","beach")){Bg("Sifting through the sand, you notice nothing of interest.")}
if((D("acquire","blossom")||D("acquire","blossom"))){Bg("The flowers are of no interest.")}
if(D("smell","blossom")){Bg("The flowers give a sweet smell to the air.")}
if((D("suntan","anyword")||D("anyword","suntan"))){Bg("King Graham is not dressed for tanning.")}
if((D("drink","lake")||D("acquire","drink"))){if(J(Ck,1)&&(BO(Ego,0,0,57,61)||BO(Ego,0,62,81,101)||BO(Ego,0,102,75,117)||BO(Ego,0,118,68,137)||BO(Ego,0,138,60,157))){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break}
if(J(Ck,8)&&(BO(Ego,0,0,46,82)||BO(Ego,0,83,57,120)||BO(Ego,0,121,78,167))){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break}
if(J(Ck,15)&&(BO(Ego,0,0,83,52)||BO(Ego,0,53,111,86)||BO(Ego,0,87,152,103)||BO(Ego,0,104,159,145)||BO(Ego,0,146,151,167))){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break}
if(J(Ck,22)&&(BO(Ego,0,0,72,82)||BO(Ego,0,83,91,167))){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break}
if(J(Ck,29)&&(BO(Ego,0,0,85,85)||BO(Ego,0,86,92,167))){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break}
if(J(Ck,36)&&(BO(Ego,0,0,90,100)||BO(Ego,0,101,80,136)||BO(Ego,0,137,66,167))){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break}
if(J(Ck,43)&&(BO(Ego,0,0,93,51)||BO(Ego,0,52,114,99)||BO(Ego,0,100,135,167))){Bg("YECCHHH!! You cough and choke from the briny water of the ocean.");A(2);break}
Bg("You need to be a little closer to drink the water.")}
case 2:if(D("acquire","lake")){Bg("You have no need to carry water.")}
if(D("check out","lake")){Bg("The calm water of the clear blue ocean looks inviting.")}
if(D("check out","wave")){Bg("You see waves crashing upon the rocks.")}
if(D("check out","tree")){Bg("The leaning palm trees sway in the ocean breeze.")}
if(D("climb","tree")){Bg("There are nothing but green coconuts in the palm trees and the trees are too slippery to climb.")}
if(N(v95,0)&&D("look under","lake")){Bg("You dip your head under the ocean water. You see nothing but colorful fish and seaweed.")}
if(!E(DS)&&D("climb","boulder")){Bg("The rocks along the ocean are too dangerous to climb.")}
return}}}
MESSAGES[152]=["","The glittering white sand of the beach feels warm from the sun. The azure water of the ocean laps up to its edge.","","","","","The plants grow well in the moist sea air.","The flowers are a beautiful contrast to the blue ocean.","","","Sifting through the sand, you notice nothing of interest.","The flowers are of no interest.","The flowers give a sweet smell to the air.","","OK.","I thought you wanted to dig?","Ok. You are all through digging. You find nothing.","You can't possibly dig while walking. Stand still.","King Graham is not dressed for tanning.","","YECCHHH!! You cough and choke from the briny water of the ocean.","You have no need to carry water.","The calm water of the clear blue ocean looks inviting.","You see waves crashing upon the rocks.","The leaning palm trees sway in the ocean breeze.","","","There are nothing but green coconuts in the palm trees and the trees are too slippery to climb.","","You need to be a little closer to drink the water.","You dip your head under the ocean water. You see nothing but colorful fish and seaweed.","The rocks along the ocean are too dangerous to climb.","Dig...Dig...Dig..."];