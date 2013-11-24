window.logic99=function()
{while(1){switch(B)
{case 0:if(D("check out","flag")){Bg("drown_swim = %v95\ngenie_delay = %v88");if(E(f176)){Bg("in_boat is set")}
if(E(DO)){Bg("on_water is set")}
if(E(f92)){Bg("keep_cycling is set")}
if(E(f148)){Bg("ego_flying is set")}
if(E(f179)){Bg("snakeInAction is set")}
if(E(f127)){Bg("hag_in_room is set")}
if(E(f132)){Bg("enchanter_in_room is set")}
if(E(f128)){Bg("dwarf_in_room is set")}
if(E(f55)){Bg("is_carpet_room is set")}
if(E(f180)){Bg("egoFallingCliff is set")}
if(E(f119)){Bg("ego_falling_chasm is set")}
if(E(f125)){Bg("ego_fell is set")}}
if(D("tp")){Bl("new room: ",v77);BK(v77)}
if((D("position")||D("pos"))){Bl("x: ",v77);Bl("y: ",v78);AK(Ego);AH(Ego,v77,v78);AJ(Ego)}
if(D("acquire","object")){Bl("object number: ",v77);get_v(v77)}
if(D("drop","var")){Bl("var number: ",v77);Bl("var value: ",v78);h(v77,v78)}
if((D("object")||D("object"))){Bl("object #: ",v77);obj_status_v(v77)}
if(BL(c5)){show_pri_screen()}
if((D("show","var")||D("sv"))){Bl("var number: ",v111);i(v126,v111);Bg("var %v111: %v126")}
if((D("show","flag")||D("sf"))){Bl("flag number: ",v111);if(S(v111)){Bg("flag %v111 is set");A(1);break}
Bg("flag %v111 is not set")}
case 1:if(D("reset","flag")){Bl("flag number: ",v111);T(v111)}
if(D("drop","flag")){Bl("flag number: ",v111);R(v111)}
if(BL(c4)){show_mem()}
if(E(f163)){if(J(Cu,1)){log("%m12%w1")}
if(J(Cu,2)){log("%m12%w2")}
if(J(Cu,3)){log("%m12%w3")}
if(J(Cu,0)&&E(DQ)&&!E(DS)){log("No response to input.")}}
return}}}
MESSAGES[99]=["","new room: ","x: ","y: ","object number: ","var number: ","var value: ","object #: ","var %v111: %v126","flag number: ","flag %v111 is set","flag %v111 is not set","Word not known: ","%m12%w1","%m12%w2","%m12%w3","No response to input.","","","","drown_swim = %v95\ngenie_delay = %v88","in_boat is set","on_water is set","keep_cycling is set","ego_flying is set","snakeInAction is set","hag_in_room is set","enchanter_in_room is set","dwarf_in_room is set","","is_carpet_room is set","egoFallingCliff is set","ego_falling_chasm is set","ego_fell is set"];