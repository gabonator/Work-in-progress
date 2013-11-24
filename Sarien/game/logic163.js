window.logic163=function()
{while(1){switch(B)
{case 0:if(!E(DQ)){A(1);break}
if(D("check out","tree")){Bg("There are many lovely pine and spruce trees near these mountains.")}
if(!J(Ck,42)){if((D("check out","area")||D("check out"))){Bg("The mountain range is wild and rugged. It would be impossible to cross, unless you could fly like a bird.")}}
if(D("anyword","tree")&&!D("check out","tree")){Bg("You have better things to do.")}
if(D("anyword","cliff")){Bg("The mountain range is wild and rugged. It would be impossible to cross, unless you could fly like a bird.")}
if(D("check out","blossom")){Bg("There are not many flowers around here.")}
if((D("acquire","blossom")||D("smell","blossom"))){Bg("You have better things to do.")}
if(D("check out","bush")){Bg("There are not many bushes around here.")}
case 1:return}}}
MESSAGES[163]=["","There are many lovely pine and spruce trees near these mountains.","You have better things to do.","The mountain range is wild and rugged. It would be impossible to cross, unless you could fly like a bird.","There are not many flowers around here.","There are not many bushes around here."];