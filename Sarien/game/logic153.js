window.logic153=function()
{while(1){switch(B)
{case 0:if(!E(f248)&&E(DT)){F(f248);G(f53);if(!J(Ck,3)&&!E(f59)){l(0,250,v94);if((P(v94,80)||E(f129))){F(f38);m(o2);CY(3);CY(2);l(40,255,v58);l(0,2,v59);if(J(Ck,2)){AG(o2,140,140)}
if(J(Ck,3)){AG(o2,140,150)}
if(J(Ck,4)){AG(o2,40,140)}
if(J(Ck,9)){AG(o2,20,150)}
if(J(Ck,10)){AG(o2,25,125)}
if(J(Ck,16)){AG(o2,120,60)}
At(o2);p(o2,2)}}
return}
if(!E(f53)&&E(f38)){U(v58);if(J(v58,1)){U(v59);if(J(v59,0)){F(f53);An(o2);AJ(o2);Bg("What is this! It appears you have run into Little Red Riding Hood! She looks a little troubled.");A(1);break}
L(v58,250)}}
case 1:if(!E(f53)){A(6);break}
BC(Ego,o2,v94);if(N(v94,110)){if(D("anyword","bitch")){Bg("You are too far away from her.")}}
if(E(f59)&&D("acquire","bouquet")){Bg("You already have it.")}
if(D("follow","bitch")){Bg("No!")}
if(D("acquire","bitch")){Bg("Now, that wouldn't be very nice, would it?")}
if(D("kill","bitch")){Bg("That would be incredibly nasty!")}
if(D("kiss","bitch")){Bg("You don't need to be kissing little girls.")}
if(D("embrace","bitch")){Bg("You are a stranger to Little Red Riding Hood. You shouldn't hug her.")}
if(!E(f59)&&(D("acquire","bouquet")||D("steal","bouquet"))){Bg("It would not be nice to take the bouquet of flowers away from the little girl.")}
if(D("check out","bitch")){Bg("Little Red Riding Hood is a sweet little girl. She has long blond locks peeking out from her red cape and hood.")}
if(D("speak","bitch")){if(E(f59)){Bg("Little Red Riding Hood is overjoyed to have her basket of goodies back. Thank you, Mister, she exclaims. Now I can take the goodies to my sick grandma.");A(2);break}
Bg("Tearfully, Little Red Riding Hood explains that someone stole her basket of goodies while she was picking a bouquet of flowers. Could you please help her find it?")}
case 2:if((D("hello","anyword")||D("say","hello"))){if(E(f59)){Bg("Shyly, Little Red Riding Hood returns your hello.");A(3);break}
Bg("Shyly, Little Red Riding Hood returns your hello. She looks a little upset.")}
case 3:if(D("capture","bitch")){Bg("Now, that wouldn't be very nice, would it?")}
if(!((D("give","basket","bitch")||D("give","bitch","basket")))){A(500);break}
if(!(N(v94,25))){A(501);break}
Bg("You are too far away from her.");A(8);break;case 501:if(!(BT("Empty Basket"))){A(502);break}
Bg("You ate the goodies out of the basket! Why would you think she would want it now?");A(4);break;case 502:if(!(BT("Basket of Goodies"))){A(503);break}
CL("Basket of Goodies");BS("Bouquet of Flowers");p(o2,3);F(f59);Bg("Gratefully, Little Red Riding Hood accepts the basket of goodies. In return, she gives you her bouquet of flowers.");W(Cn,4);A(4);break;case 503:G(DS);case 4:A(5);break;case 500:if((D("give","anyword","bitch")||D("give","bitch","anyword"))){Bg("Little Red Riding Hood is not interested in it.");A(5);break}
if(D("give","anyword")){Bg("You must specify who you wish to give it to.")}
case 5:if((D("acquire","basket")||D("steal","basket"))){if(E(f57)&&!BT("Basket of Goodies")&&!BT("Empty Basket")){Bg("You gave the basket of goodies to Little Red Riding Hood. It's hers now. You can't take it!")}}
A(7);break;case 6:if(D("anyword","bitch")){Bg("There is nobody here but you.")}
if(!E(f59)){if((D("acquire","bouquet")||D("steal","bouquet"))){Bg("There is no one here to get it from.")}}
if(D("give","basket")){if((BT("Basket of Goodies")||BT("Empty Basket"))){Bg("There is nobody here to give it to.");A(7);break}
Bg("You do not have it to give.")}
case 7:if(E(f64)){A(8);break}
if(D("check out","tree")){Bg("This is a heavily wooded area. It would be easy to get lost among the trees.")}
if(D("check out","blossom")){Bg("Many flowers beautify these woods.")}
if(D("acquire","blossom")){Bg("You have better things to do than to dilly-dally around picking flowers.")}
if(D("climb","tree")){Bg("It would be fun to climb trees for a while, but you really have better things to do.")}
if(D("smell","blossom")){Bg("The lovely fragrance of wildflowers is all around you in these woods.")}
if(D("check out","bush")){Bg("There are many bushes and shrubs among the trees.")}
case 8:return}}}
MESSAGES[153]=["","Little Red Riding Hood is a sweet little girl. She has long blond locks peeking out from her red cape and hood.","Now, that wouldn't be very nice, would it?","","","Tearfully, Little Red Riding Hood explains that someone stole her basket of goodies while she was picking a bouquet of flowers. Could you please help her find it?","Shyly, Little Red Riding Hood returns your hello. She looks a little upset.","What is this! It appears you have run into Little Red Riding Hood! She looks a little troubled.","You don't need to be kissing little girls.","You are a stranger to Little Red Riding Hood. You shouldn't hug her.","Gratefully, Little Red Riding Hood accepts the basket of goodies. In return, she gives you her bouquet of flowers.","You ate the goodies out of the basket! Why would you think she would want it now?","You are too far away from her.","Little Red Riding Hood is overjoyed to have her basket of goodies back. Thank you, Mister, she exclaims. Now I can take the goodies to my sick grandma.","That would be incredibly nasty!","This is a heavily wooded area. It would be easy to get lost among the trees.","Many flowers beautify these woods.","You have better things to do than to dilly-dally around picking flowers.","It would be fun to climb trees for a while, but you really have better things to do.","The lovely fragrance of wildflowers is all around you in these woods.","There are many bushes and shrubs among the trees.","It would not be nice to take the bouquet of flowers away from the little girl.","There is nobody here but you.","There is no one here to get it from.","There is nobody here to give it to.","You do not have it to give.","No!","You already have it.","Shyly, Little Red Riding Hood returns your hello.","You gave the basket of goodies to Little Red Riding Hood. It's hers now. You can't take it!","Little Red Riding Hood is not interested in it.","You must specify who you wish to give it to."];