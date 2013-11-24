var Agent = {
    IE: (navigator.appName == "Microsoft Internet Explorer"),
    OP: (navigator.appName == "Opera"),
    iPhone: (navigator.userAgent.indexOf("iPhone") != -1),
    createXmlHttpObject: function () {
        if (Agent.IE)
            return new ActiveXObject("Microsoft.XmlHttp");
        else
            return new XMLHttpRequest()
    },
    cancelEvent: function (evt) {
        if (Agent.IE) {
            evt.cancelBubble = true;
            evt.returnValue = 0
        } else {
            evt.stopPropagation();
            evt.preventDefault()
        }
    },
    setOpacity: function (el, opacity) {
        if (Agent.IE)
            el.style.filter = "alpha(opacity:" + opacity + ")";
        else
            el.style.opacity = opacity / 100
    },
    getBoundingClientRect: function (el) {
        if (el.getBoundingClientRect)
            return el.getBoundingClientRect();
        else if (this.OP) {
            var box = {
                "left": el.offsetLeft,
                "top": el.offsetTop,
                "right": el.offsetWidth,
                "bottom": el.offsetHeight
            };
            for (el.offsetParent; el && el.nodeName != "BODY"; el = el.offsetParent) {
                box.left += el.offsetLeft;
                box.top += el.offsetTop
            }
            box.right += box.left;
            box.bottom += box.top;
            return box
        } else {
            var box = el.ownerDocument.getBoxObjectFor(el);
            return {
                "left": box.x,
                "top": box.y,
                "right": box.x + box.width,
                "bottom": box.y + box.height
            }
        }
    }
};
var MESSAGES = [];
var CONTROLS = {};
var WORDS = [];
var roomNames = {};
var avatarNames = {};
var multiplayerRooms = {};
var vars = [];
var flags = [];
var objects = [];
var c = [];
var items = {};
var controllers = [];
var strings = [];
var B = 0;
var roomEntryPoints = {};
var AGI = {
    block: false,
    C: true,
    current_logic: 0,
    current_room: 0,
    control: 0,
    game_id: "",
    highestObjIndex: 0,
    horizon: 0,
    interval: 42,
    new_room: 0,
    picture: null,
    paused: false,
    priorityTable: [],
    screen: 0,
    screen_width: 160,
    screen_height: 168,
    startMilliseconds: 0,
    zoom: 2,
    stopped: false,
    cycle: 0,
    init: function () {
        for (var i = 0; i < 256; i++) {
            window["o" + i] = i;
            window["f" + i] = i;
            window["v" + i] = i;
            window["c" + i] = i;
            window["i" + i] = i;
            window["s" + i] = i;
            window["m" + i] = i;
            vars[i] = 0;
            flags[i] = 0;
            objects[i] = 0;
            controllers[i] = 0;
            strings[i] = ""
        };
        for (var i in roomNames)
            roomNames[roomNames[i]] = i;
        AGI.control = c_program_control;
        AGI.screen = s_graphics_screen;
        AGI.picture = new Picture();
        this.startMilliseconds = new Date().getTime();
        this.initPriorityTable();
        IO.init();
        Text.init();
        Menu.init();
        if (Test.recording || Test.playing)
            Test.init();
        else
            AGI.start()
    },
    start: function () {
        F(DT)
        BF(0);
        Hacks.init(AGI.game_id);
        MultiplayerClient.init();
        IO.commandsGlobal = IO.getCommands(0);
        if (Sarien.checkForHashChange()) {
            F(DU);
            AGI.control = c_player_control;
            F(Dc);
            Hacks.afterInitialRoomChange(AGI.game_id)
        }
        document.getElementById("canvas").focus();
        AGI.interpretCycle()
    },
    initPriorityTable: function () {
        var y = 0;
        for (var p = 1; p < 15; p++)
            for (var i = 0; i < 12; i++)
                AGI.priorityTable[y++] = p < 4 ? 4 : p
    },
    interpretCycle: function () {
        AGI.cycle++;
        var cycleStarted = new Date().getTime();
        IO.setSpeed(vars[Cw]);
        Test.cycle();
        Hacks.cycle(AGI.game_id);
        IO.cycle();
        Menu.cycle();
        MultiplayerClient.cycle();
        AGI.updateClock();
        if (!AGI.paused) {
            var ego = getEgo();
            if (AGI.control == c_player_control)
                vars[Cr] = ego.direction;
            else
                ego.direction = vars[Cr];
            AGI.checkAllMotions();
            AGI.C = false;
            A(0);
            logic0();
            ego.direction = vars[Cr];
            if (AGI.new_room > 0)
                AGI.new_room = 0;
            else {
                if (State.stateToLoad)
                    State.load();
                if (E(DT)) {
                    G(DT);
                    IO.commandsLocal = IO.getCommands(IO.currentRoomLogics, true);
                    IO.parseRoomCommands(IO.commandsLocal)
                } else {
                    L(Cu, 0);
                    L(Cp, 0);
                    L(Cq, 0);
                    G(DU);
                    G(Da);
                    Sound.setFlags();
                    if (AGI.screen == s_graphics_screen)
                        AGI.updateAllViews();
                    Sarien.checkForHashChange()
                }
            }
        }
        var ego = getEgo();
        if (ego.x || ego.y)
            ego.checkPriority();
        Test.processCycleCommands();
        IO.said = [];
        var cycleEnded = new Date().getTime();
        var interval = Math.max(0, AGI.interval - (cycleEnded - cycleStarted));
        if (!AGI.stopped)
            setTimeout(AGI.interpretCycle, interval)
    },
    checkAllMotions: function () {
        for (var i = 0; i <= AGI.highestObjIndex; i++) {
            var obj = objects[i];
            if (obj && obj.id > -1 && obj.ANIMATED && obj.UPDATE && obj.DRAWN)
                obj.checkMotion()
        }
    },
    updateAllViews: function () {
        for (var i = 0; i <= AGI.highestObjIndex; i++) {
            var obj = objects[i];
            if (obj && obj.id > -1 && obj.ANIMATED && obj.UPDATE && obj.DRAWN) {
                obj.updateViewTableEntry();
                obj.updatePosition();
                obj.update()
            }
        }
        var ego = getEgo();
        ego.ON_WATER = false;
        ego.ON_LAND = false
    },
    updateClock: function () {
        var ms = new Date().getTime() - AGI.startMilliseconds;
        var hours = Math.floor(ms / (1000 * 60 * 60));
        ms -= hours * (1000 * 60 * 60);
        var minutes = Math.floor(ms / (1000 * 60));
        ms -= minutes * (1000 * 60);
        var seconds = Math.floor(ms / 1000);
        vars[Cz] = hours;
        vars[Cy] = minutes;
        vars[Cx] = seconds
    },
    pause: function () {
        AGI.paused = true
    },
    unpause: function () {
        if (Text.messageShown) {
            Text.hideMessage();
            if (window.open_ks) {
                window.open('http://www.kickstarter.com/projects/spaceventure/two-guys-spaceventure-by-the-creators-of-space-que');
                window.open_ks = false;
            }
        }
        if (!Text.messageShown)
            AGI.paused = false
    },
    setAvatar: function (id) {
        p(0, id)
    },
    stop: function () {
        this.stopped = true;
        Multiplayer.disconnect()
    },
    getPriority: function (x, y) {
        var color = Canvas.getPixel(x, y);
        if (!color) {
            var checkStaticObjects = AGI.picture.staticObjects.length > 0;
            if (checkStaticObjects)
                color = AGI.picture.getBoundaryFromStaticObjects(x, y)
        }
        return color
    }
};

function A(lineNr) {
    if (AGI.current_logic == A.lastLogic) {
        A.count = isNaN(A.count) ? 0 : A.count + 1;
        if (A.count > 500) {
            alert("Press any key to continue.");
            IO.key_pressed = true;
            A.count = 0
        }
    } else
        A.count = 0;
    B = lineNr;
    A.lastLogic = AGI.current_logic
};
var Base64 = {
    _keyStr: "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
    encode: function (input) {
        var output = "";
        var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
        var i = 0;
        input = Base64._utf8_encode(input);
        while (i < input.length) {
            chr1 = input.charCodeAt(i++);
            chr2 = input.charCodeAt(i++);
            chr3 = input.charCodeAt(i++);
            enc1 = chr1 >> 2;
            enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
            enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
            enc4 = chr3 & 63;
            if (isNaN(chr2)) {
                enc3 = enc4 = 64
            } else if (isNaN(chr3)) {
                enc4 = 64
            }
            output = output +
                this._keyStr.charAt(enc1) + this._keyStr.charAt(enc2) +
                this._keyStr.charAt(enc3) + this._keyStr.charAt(enc4)
        }
        return output
    },
    decode: function (input) {
        var output = "";
        var chr1, chr2, chr3;
        var enc1, enc2, enc3, enc4;
        var i = 0;
        input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");
        while (i < input.length) {
            enc1 = this._keyStr.indexOf(input.charAt(i++));
            enc2 = this._keyStr.indexOf(input.charAt(i++));
            enc3 = this._keyStr.indexOf(input.charAt(i++));
            enc4 = this._keyStr.indexOf(input.charAt(i++));
            chr1 = (enc1 << 2) | (enc2 >> 4);
            chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
            chr3 = ((enc3 & 3) << 6) | enc4;
            output = output + String.fromCharCode(chr1);
            if (enc3 != 64) {
                output = output + String.fromCharCode(chr2)
            }
            if (enc4 != 64) {
                output = output + String.fromCharCode(chr3)
            }
        }
        output = Base64._utf8_decode(output);
        return output
    },
    _utf8_encode: function (string) {
        string = string.replace(/\r\n/g, "\n");
        var utftext = "";
        for (var n = 0; n < string.length; n++) {
            var c = string.charCodeAt(n);
            if (c < 128) {
                utftext += String.fromCharCode(c)
            } else if ((c > 127) && (c < 2048)) {
                utftext += String.fromCharCode((c >> 6) | 192);
                utftext += String.fromCharCode((c & 63) | 128)
            } else {
                utftext += String.fromCharCode((c >> 12) | 224);
                utftext += String.fromCharCode(((c >> 6) & 63) | 128);
                utftext += String.fromCharCode((c & 63) | 128)
            }
        }
        return utftext
    },
    _utf8_decode: function (utftext) {
        var string = "";
        var i = 0;
        var c = 0;
        var c1 = 0;
        var c2 = 0;
        while (i < utftext.length) {
            c = utftext.charCodeAt(i);
            if (c < 128) {
                string += String.fromCharCode(c);
                i++
            } else if ((c > 191) && (c < 224)) {
                c2 = utftext.charCodeAt(i + 1);
                string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
                i += 2
            } else {
                c2 = utftext.charCodeAt(i + 1);
                c3 = utftext.charCodeAt(i + 2);
                string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
                i += 3
            }
        }
        return string
    }
}
var Canvas = {
    jsx: "0123456789ABCDEFGHJKLMNOPQRSTUVWXYZabcdghijklmnpqrstuwxyz`~!@#$%^*()-+=_[]{}|:;,.<>/?",
    virtualScreen: new Array(160),
    clear: function () {
        var screenWidth = this.virtualScreen.length;
        for (var i = 0; i < screenWidth; i++) {
            this.virtualScreen[i] = new Array(168)
        }
    },
    load: function (id) {
        this.clear();
        var map = CONTROLS[id];
        if (!map) return;
        var y = 0;
        var x = 0;
        var color = 4;
        var count = 0;
        for (var i = 0; i < map.length; i++) {
            var c = map.substr(i, 1);
            var pos = Canvas.jsx.indexOf(c);
            switch (pos) {
            case (16 * 5 + 4):
                count += 160;
                break;
            case (16 * 5 + 3):
                count += 128;
                break;
            case (16 * 5 + 2):
                count += 64;
                break;
            case (16 * 5 + 1):
                count += 32;
                break;
            case (16 * 5 + 0):
                count += 16;
                break;
            default:
                var d = pos / 5;
                count += Math.floor(d);
                color = (pos % 5) + 1;
                if (color == 5) color = 0;
                for (var run = x + count; x < run; x++) {
                    Canvas.putPixel(x, y, color)
                }
                count = 0;
                if (x == 160) {
                    x = 0;
                    y += 1
                }
                break
            }
        }
    },
    putPixel: function (x, y, color) {
        this.virtualScreen[x][y] = color
    },
    getPixel: function (x, y) {
        var axis = this.virtualScreen[x];
        if (!axis)
            return 0;
        var color = 0;
        if (axis)
            var color = axis[y];
        return color ? color : 0
    }
};

function H(roomNr) {
    getEgo().hide();
    for (var i = 0; i < objects.length; i++) {
        var obj = objects[i];
        if (obj) {
            obj.ANIMATED = false;
            obj.DRAWN = false;
            obj.UPDATE = true;
            obj.step_time = 1;
            obj.step_time_count = 1;
            obj.cycle_time = 1;
            obj.cycle_time_count = 1;
            obj.step_size = 1;
            obj.observe_blocks = true
        }
    }
    n();
    Ac();
    AE(0);
    AX();
    AGI.horizon = 36;
    M(Cl, Ck);
    L(Ck, roomNr);
    L(Cp, 0);
    L(Cq, 0);
    L(DC, getEgo().id);
    G(DQ);
    BY(roomNr);
    IO.currentRoomLogics = {};
    var ego = getEgo();
    switch (vars[Cm]) {
    case 1:
        ego.y = AGI.screen_height - 1;
        break;
    case 2:
        ego.x = 0;
        break;
    case 3:
        ego.y = AGI.horizon + 1;
        break;
    case 4:
        ego.x = AGI.screen_width - ego.width();
        break
    }
    L(Cm, 0);
    F(DT);
    AGI.current_room = roomNr;
    AGI.new_room = roomNr;
    AGI.C = true;
    Sarien.updateAddressBar(roomNr);
    Ba();
    AGI.highestObjIndex = 1
};

function J(vn, value) {
    return vars[vn] == value
}

function K(vn, vn2) {
    return vars[vn] == vars[vn2]
}

function L(vn, value) {
    vars[vn] = value
}

function M(vn, vn2) {
    vars[vn] = vars[vn2]
}

function N(vn, value) {
    return vars[vn] > value
}

function O(vn, vn2) {
    return vars[vn] > vars[vn2]
}

function P(vn, value) {
    return vars[vn] < value
}

function Q(vn, vn2) {
    return vars[vn] < vars[vn2]
}

function F(fn) {
    flags[fn] = 1
}

function R(n) {
    flags[vars[n]] = 1
}

function E(n) {
    return flags[n]
}

function S(n) {
    return flags[vars[n]]
}

function G(fn) {
    flags[fn] = 0
};

function T(vn) {
    flags[vars[vn]] = 0
};

function U(vn) {
    if (vars[vn] > 0)
        vars[vn]--
}

function V(vn) {
    if (vars[vn] < 255)
        vars[vn]++
}

function W(vn, value) {
    vars[vn] += value;
    vars[vn] = vars[vn] % 256
}

function X(vn, vn2) {
    vars[vn] += vars[vn2];
    vars[vn] = vars[vn] % 256
}

function Y(vn, value) {
    vars[vn] -= value;
    if (vars[vn] < 0)
        vars[vn] += 256
}

function Z(vn, vn2) {
    vars[vn] -= vars[vn2];
    if (vars[vn] < 0)
        vars[vn] += 256
}

function a(vn, value) {
    vars[vn] *= value
}

function b(vn, vn2) {
    vars[vn] *= vars[vn2]
}

function c(vn, value) {
    vars[vn] /= value
}

function d(vn, vn2) {
    vars[vn] /= vars[vn2]
}

function g(n, m) {
    vars[vars[n]] = m
}

function h(n, m) {
    vars[vars[n]] = vars[m]
}

function i(n, m) {
    vars[n] = vars[vars[m]]
}

function j(n) {
    var is0 = flags[n] == 0;
    flags[n] = is0 ? 1 : 0
}

function k(vn) {
    var is0 = flags[vars[vn]] == 0;
    flags[vars[vn]] = is0 ? 1 : 0
}

function l(min, max, vn) {
    var rnd;
    if (Test.playing)
        rnd = Test.playRandom();
    else
        rnd = Utils.Random(min, max); if (Test.recording)
        Test.recordRandom(rnd);
    vars[vn] = rnd
}

function m(i) {
    var obj = getObject(i);
    obj.ANIMATED = true;
    obj.CYCLING = true;
    obj.UPDATE = true;
    obj.cycle_type = ct_normal_cycle;
    obj.room = AGI.picture.id
}

function n() {
    for (var i = objects.length - 1; i > 0; i--) {
        var obj = objects[i];
        if (obj) {
            obj.remove();
            obj.ANIMATED = false;
            obj.DRAWN = false;
            delete objects[i]
        }
    }
}

function p(i, view) {
    if (avatarNames[view])
        IO.avatars[view] = 1;
    var obj = getObject(i);
    obj.load(view);
    if (obj.loop >= obj.loopCount())
        obj.loop = 0;
    if (obj.cel >= obj.celCount())
        obj.cel = 0;
    obj.update()
};

function q(i, vn) {
    var view = vars[vn];
    p(i, view)
};

function r(i, loop) {
    var obj = getObject(i);
    obj.loop = loop;
    if (obj.loop >= obj.loopCount())
        obj.loop = 0;
    if (obj.cel >= obj.celCount())
        obj.cel = 0;
    obj.update()
};

function s(n, m) {
    var loop = vars[m];
    r(n, loop)
};

function t(n) {
    var obj = getObject(n);
    obj.FIX_LOOP = true
}

function u(n) {
    var obj = getObject(n);
    obj.FIX_LOOP = false
}

function w(i, cel) {
    var obj = getObject(i);
    obj.cel = cel;
    obj.update()
};

function x(i, vn) {
    var obj = getObject(i);
    obj.cel = vars[vn];
    obj.update()
};

function y(i, vn) {
    var obj = getObject(i);
    vars[vn] = obj.celCount() - 1
}

function z(i, vn) {
    var obj = getObject(i);
    vars[vn] = obj.cel
}

function AA(i, vn) {
    var obj = getObject(i);
    vars[vn] = obj.loop
}

function AB(i, vn) {
    var obj = getObject(i);
    vars[vn] = obj.id
}

function AC(i, v) {
    var obj = getObject(i);
    obj.setPriority(v);
    obj.FIXED_PRIORITY = true
}

function AD(i, vn) {
    var v = vars[vn];
    AC(i, v)
}

function AE(n) {
    var obj = getObject(n);
    obj.FIXED_PRIORITY = false
}

function AF(i, vn) {
    var obj = getObject(i);
    vars[vn] = obj.priority
}

function AG(i, x, y) {
    var obj = getObject(i);
    if (i == 0 && y < AGI.horizon)
        y = AGI.horizon + 1;
    obj.position(x, y);
    obj.oldX = x;
    obj.oldY = y;
    obj.destX = x;
    obj.destY = y;
    obj.DIDNT_MOVE = false;
    obj.UPDATE_POS = false
}

function AH(i, vx, vy) {
    AG(i, vars[vx], vars[vy])
};

function AJ(i) {
    var obj = getObject(i);
    if (obj.DRAWN)
        return;
    obj.ANIMATED = true;
    obj.DRAWN = true;
    obj.UPDATE = true;
    obj.show()
};

function AK(n) {
    var obj = getObject(n);
    obj.hide();
    obj.DRAWN = false
}

function AL(n, vx, vy) {
    var obj = getObject(n);
    vars[vx] = obj.x;
    vars[vy] = obj.y
};

function AM(n) {
    var obj = getObject(n);
    obj.CYCLING = true
}

function AN(n) {
    var obj = getObject(n);
    obj.CYCLING = false
}

function AO(n) {
    var obj = getObject(n);
    obj.cycle_type = ct_normal_cycle
}

function AP(n) {
    var obj = getObject(n);
    obj.cycle_type = ct_reverse_cycle
}

function AQ(i, flag) {
    G(flag);
    var obj = getObject(i);
    obj.ANIMATED = true;
    obj.UPDATE = true;
    obj.CYCLING = true;
    obj.flag_to_set = flag;
    obj.cycle_type = ct_end_of_loop
};

function AR(i, flag) {
    G(flag);
    var obj = getObject(i);
    obj.ANIMATED = true;
    obj.UPDATE = true;
    obj.CYCLING = true;
    obj.flag_to_set = flag;
    obj.cycle_type = ct_reverse_loop
};

function AS(n, m) {
    var obj = getObject(n);
    var value = vars[m];
    if (value == 0)
        value = 1;
    obj.cycle_time = value;
    obj.cycle_time_count = value
}

function AT(n) {
    AGI.horizon = n;
    var ego = getEgo();
    ego.fixPosition();
    ego.update()
}

function AU(n) {
    var obj = getObject(n);
    obj.observe_horizon = false
}

function AV(n) {
    var obj = getObject(n);
    obj.observe_horizon = true
}

function AW(x1, y1, x2, y2) {
    AGI.block = {
        "x1": x1,
        "y1": y1,
        "x2": x2,
        "y2": y2
    }
};

function AX() {
    AGI.block = false
};

function AY(n) {
    var obj = getObject(n);
    obj.observe_blocks = false
};

function AZ(n) {
    var obj = getObject(n);
    obj.observe_blocks = true
};

function Aa(n) {
    var obj = getObject(n);
    obj.observe_objects = false
};

function Ab(n) {
    var obj = getObject(n);
    obj.observe_objects = true
};

function Ac() {
    AGI.control = c_player_control
};

function Ad() {
    AGI.control = c_program_control
};

function Ag(n) {
    var obj = getObject(n);
    obj.direction = 0;
    obj.motion_type = mt_normal_motion;
    if (n == 0) {
        vars[Cr] = 0;
        Ad()
    }
};

function Ah(n) {
    var obj = getObject(n);
    obj.motion = true;
    if (n == 0) {
        vars[Cr] = 0;
        Ac()
    }
};

function Ai(n, m) {
    var obj = getObject(n);
    var s = vars[m];
    if (s != 0)
        obj.step_size = s
};

function Aj(n, m) {
    var obj = getObject(n);
    obj.step_time = vars[m];
    obj.step_time_count = vars[m]
};

function Ak(n, x, y, step_size, flag) {
    G(flag);
    var obj = getObject(n);
    obj.UPDATE = true;
    obj.parm3 = obj.step_size;
    if (step_size > 0)
        obj.step_size = step_size;
    obj.setDestination(x, y);
    obj.flag_to_set = flag;
    if (n == 0)
        Ad()
}

function Al(n, vx, vy, vstep, flag) {
    var x = vars[vx];
    var y = vars[vy];
    var step_size = vars[vstep];
    Ak(n, x, y, step_size, flag)
};

function Am(n, s, flag) {
    G(flag);
    var obj = getObject(n);
    obj.motion_type = mt_follow_ego;
    obj.parm1 = s > obj.step_size ? s : obj.step_size;
    obj.parm3 = 255;
    obj.flag_to_set = flag
}

function An(n) {
    var obj = getObject(n);
    obj.motion_type = mt_wander
};

function Ap(n) {
    var obj = getObject(n);
    if (obj.motion_type == mt_wander)
        obj.stop();
    obj.motion_type = mt_normal_motion
};

function Aq(n, m) {
    var obj = getObject(n);
    obj.direction = vars[m]
}

function Ar(n, m) {
    var obj = getObject(n);
    vars[m] = obj.direction
}

function As(n) {
    var obj = getObject(n);
    obj.ON_WATER = true
}

function At(n) {
    var obj = getObject(n);
    obj.ON_LAND = true
}

function Au(n) {
    var obj = getObject(n);
    obj.ON_LAND = false;
    obj.ON_WATER = false
}

function Aw(n, vx, vy) {
    var dx = vars[vx];
    var dy = vars[vy];
    var obj = getObject(n);
    var x = (obj.x + dx) % 256;
    var y = (obj.y + dy) % 256;
    obj.position(x, y);
    obj.UPDATE_POS = true;
    obj.fixPosition()
};

function Ax(n, x, y) {
    var obj = getObject(n);
    obj.position(x, y);
    obj.UPDATE_POS = true;
    obj.fixPosition()
};

function Ay(n, vx, vy) {
    var obj = getObject(n);
    obj.position(vars[vx], vars[vy]);
    obj.UPDATE_POS = true;
    obj.fixPosition()
};

function Az(n) {
    var obj = getObject(n);
    obj.UPDATE = false
};

function BA(n) {
    var obj = getObject(n);
    obj.UPDATE = true
};

function BB(n) {
    var obj = getObject(n);
    obj.update()
};

function BC(n, m, d) {
    var obj1 = objects[n];
    var obj2 = objects[m];
    if (obj1 && obj2 && obj1.DRAWN && obj2.DRAWN)
        vars[d] = Math.abs(obj1.x - obj2.x) + Math.abs(obj1.y - obj2.y);
    else
        vars[d] = 255
}

function BD(view, loop, cel, x, y, prio, margin) {
    var obj = new View();
    obj.FIXED_PRIORITY = true;
    obj.load(view);
    obj.loop = loop;
    obj.cel = cel;
    obj.position(x, y);
    obj.setPriority(prio);
    obj.show();
    obj.update();
    obj.margin = margin;
    AGI.picture.addStaticObject(obj);
    var parent = obj.rootElement.parentNode;
    parent.insertBefore(obj.rootElement, parent.firstChild)
};

function BE(view, loop, cel, x, y, prio) {
    BD(vars[view], vars[loop], vars[cel], vars[x], vars[y], vars[prio])
};

function BF(i) {
    if (AGI.new_room > 0)
        return;
    BY(i);
    var prevLogic = AGI.current_logic;
    AGI.current_logic = i;
    A(0);
    window["logic" + i]();
    AGI.current_logic = prevLogic
}

function BG(vn) {
    BF(vars[vn])
}

function BH(y1, y2, color) {
    for (var y = y1; y <= y2; y++)
        Text.clearLine(y)
};

function BJ(vn) {
    AGI.picture.load(vars[vn])
};

function BK(v) {
    H(vars[v])
};

function BL(cn) {
    if (IO.controllerKey == cn) {
        IO.controllerKey = 0;
        return true
    }
    return false
};

function D() {
    return IO.hasSaid(arguments)
};

function BM() {
    AGI.picture.show()
};

function BN(n, flag) {
    Sound.play(n, flag)
};

function BO(n, x1, y1, x2, y2) {
    var obj = getObject(n);
    var x = obj.x;
    var y = obj.y;
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2)
}

function BP(n, x1, y1, x2, y2) {
    var obj = getObject(n);
    var x = obj.x;
    var y = obj.y;
    return (x >= x1 && x + obj.width() <= x2 && y >= y1 && y <= y2)
}

function BQ(n, x1, y1, x2, y2) {
    var obj = getObject(n);
    var x = obj.x + obj.width();
    var y = obj.y;
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2)
}

function BR(n, x1, y1, x2, y2) {
    var obj = getObject(n);
    var x = obj.x + Math.round(obj.width() / 2);
    var y = obj.y;
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2)
}

function BS(n) {
    if (isNaN(n))
        n = Utils.inventoryNameToIndex(n);
    if (n >= 0)
        items[n] = true
}

function BT(n) {
    if (isNaN(n))
        n = Utils.inventoryNameToIndex(n);
    return (n >= 0 && items[n]) ? true : false
}

function CL(n) {
    if (isNaN(n))
        n = Utils.inventoryNameToIndex(n);
    if (!isNaN(n))
        delete items[n]
}

function cmd_put(n, m) {
    if (m == 0)
        CL(n);
    if (m == 255)
        BS(n)
}

function cmd_put_v(n, m) {
    m = vars[m];
    cmd_put(n, m)
}

function BU() {
    if (IO.key_pressed) {
        IO.key_pressed = false;
        return true
    }
    return false
}

function BV() {
    IO.accept_input = false
}

function BW() {
    IO.accept_input = true
}

function BX(vn) {
    BY(vars[vn])
}

function BY(i) {
    if (!window["logic" + i]) {
        var url = Sarien.path + "/logic" + i + ".js";
        Sarien.loadResource(url)
    }
    if (E(DT) && AGI.current_room > 0)
        IO.currentRoomLogics[i] = 1
}

function BZ(n, s) {
    strings[n] = s
}

function Ba() {
    AGI.screen = s_graphics_screen;
    document.getElementById("canvas").className = "";
    if (!Text.messageShown)
        Text.clear()
}

function Bb() {
    Text.hideMessage();
    AGI.screen = s_text_screen;
    document.getElementById("canvas").className = "text-screen"
}

function Bc(row, col, msg) {
    msg = Text.parseMessage(msg);
    Text.add(col, row, msg, Text.foregroundColor, Text.backgroundColor)
}

function Bd(vrow, vcol, vmsg) {
    var row = vars[vrow];
    var col = vars[vcol];
    var i = vars[vmsg];
    var msg = MESSAGES[AGI.current_logic][i];
    Bc(row, col, msg)
}

function Bg(msg) {
    msg = Text.parseMessage(msg);
    Text.displayMessage(msg)
}

function Bh(msg) {
    Bg(msg)
}

function Bi(n) {
    var i = vars[n];
    var msg = MESSAGES[AGI.current_room][i];
    Bg(msg)
}

function Bj(n) {
    var i = vars[n];
    var msgs = MESSAGES[AGI.current_room];
    if (msgs) {
        var msg = MESSAGES[AGI.current_room][i];
        Bg(msg)
    }
}

function Bk(n, msg, x, y, len) {
    strings[n] = Text.getInput(msg)
}

function Bl(msg, n) {
    vars[n] = Text.getInput(msg)
}

function BZ(sn, msg) {
    strings[sn] = msg
}

function Bn(s1) {
    IO.parseCommandLine(strings[s1])
}

function Bp(id) {
    AGI.game_id = id
}

function Bq(keyCode, scanCode, controller) {
    if (keyCode == 0)
        IO.keyMap[scanCode] = controller
}

function Br(s1, s2) {
    return strings[s1] == strings[s2]
}

function Bs(n, m) {
    if (isNaN(n))
        n = Utils.inventoryNameToIndex(n);
    return (n >= 0) ? !items[n] : false
}

function CD(fg, bg) {
    Text.foregroundColor = fg;
    Text.backgroundColor = bg
}

function CJ(y1, x1, y2, x2, c) {
    for (var y = y1; y <= y2; y++)
        for (var x = x1; x <= x2; x++)
            Text.clearPos(x, y)
}

function CY(n) {
    if (avatarNames[n])
        IO.avatars[n] = 1
};

function CZ(n) {
    CY(vars[n])
};

function cmd_show_obj(n) {
    Text.showInventoryItem(n)
}

function CM(n) {
    Text.showInventoryItem(vars[n])
}

function By() {
    IO.showCommandLine()
}

function Bz() {
    IO.hideCommandLine()
}

function CK() {
    document.location.href = "/"
}

function CS() {
    State.save()
}

function CT() {
    State.restore()
}

function CU() {
    document.location.href = document.location.href.replace(/#.*/gi, "")
}

function Cj() {
    IO.input = IO.lastInput;
    IO.showCommandLine()
}

function CQ(n, m) {
    vars[m] = BT(vars[n]) ? 255 : vars[Ck]
}

function Bt() {}

function Bu() {}

function Bw() {}

function Bx() {}

function CA() {}

function CB() {}

function CC() { Sound.stop(); }

function CE() {}

function CF() {}

function CG() {}

function CH() {}

function CN() {}

function CO() {}

function CP() {}

function CR() {}

function CV(i, prio) {}

function CW() {};

function CX() {};

function Ca(menu) {}

function Cb(menu_item, c) {}

function Cc() {}

function CP(c) {}

function Cg() {}

function Ch() {}

function Ci() {}

function cmd_menu_input() {}

function version() {}

function overlay_pic() {}
var Hacks = {
    init: function (game) {
        IO.addPrettyVerbs({
            "acquire": "take",
            "add": "give",
            "administer": "give",
            "aid": "help",
            "aim": "throw",
            "al sent me": "ken sent me",
            "ale": "beer",
            "ankle": "leg",
            "answer": "talk to",
            "ascent": "climb down",
            "ask": "talk to",
            "ass": "xxx",
            "asshole": "xxx",
            "attire": "suit",
            "bar tender": "bartender",
            "being": "man",
            "bite": "drink",
            "bitch": "girl",
            "bodies": "body",
            "boob": "xxx",
            "bouncer": "man",
            "breast": "xxx",
            "broad": "girl",
            "bull shit": "xxx",
            "c": "close",
            "cab": "taxi",
            "call call": "radio",
            "capture": "take",
            "cart": "cartridge",
            "cast": "throw",
            "catch": "take",
            "check out": "look at",
            "clit": "xxx",
            "cock": "xxx",
            "computer console": "computer",
            "conceal": "hide",
            "consume": "eat",
            "copulate": "xxx",
            "credit card": "card",
            "cunnilingus": "xxx",
            "cunt": "xxx",
            "d": "door",
            "disembark": "get out",
            "dont move": "stop",
            "examine": "look at",
            "explore": "search",
            "fill": "insert",
            "fst": "test",
            "get": "take",
            "get down": "take off",
            "hh": "HH",
            "i'm": "go to",
            "i_d.": "id",
            "increase": "open",
            "inv": "inventory",
            "jack off": "xxx",
            "key board": "keyboard",
            "let": "jump",
            "move": "push",
            "n": "no",
            "o": "open",
            "rest": "sit",
            "speak": "talk to",
            "shsr": "SHSR",
            "sp": "object",
            "tp": "teleport",
            "y": "yes"
        });
        switch (game) {
        case "SQ":
            strings[1] = "Roger Wilco";
            window.logic69 = function () {
                H(2)
            };
            window.cmd_new_room_ori = window.H;
            window.H = function (roomNo) {
                if (roomNo != 77) window.cmd_new_room_ori(roomNo)
            }
            break;
        case "SQ2":
            strings[1] = "Roger Wilco";
            window.logic98 = function () {
                H(2)
            };
            break;
        case "LLLLL":
            G(f85);
            G(f38);
            window.cmd_new_room_ori = window.H;
            window.H = function (roomNo) {
                if (roomNo != 6)
                    window.cmd_new_room_ori(roomNo);
                else {
                    AK(0);
                    objects[0] = null;
                    H(11)
                }
            }
            Sound.setDuration(21, 20000);
            break;
        case "PQ":
            break;
        case "BC":
            IO.addPrettyVerbs({
                "F6": "do",
                "F8": "look"
            });
            Sound.setDuration(21, 10000);
            window.CR = function () {
                Text.displayMessage("To use an object, press \"/\" or rightclick, and choose the inventory object from the \"use\" submenu.")
            }
            break;
        case "KQ3":
            window.AH = function (i, vx, vy) {
                var x = vars[vx];
                var y = vars[vy];
                if (x || y)
                    AG(i, x, y)
            }
            break
        }
    },
    cycle: function (game) {
        switch (game) {
        case "BC":
            IO.commandsLocal = [
                ["F6"],
                ["F8"],
                ["use"]
            ];
            for (var i = 0; i < INVENTORY.length; i++) {
                if (BT(i))
                    IO.commandsLocal.push(["use", INVENTORY[i]])
            }
            break
        }
    },
    parse: function (game, input) {
        switch (input) {
        case "back kickstarter":
        case "back the kickstarter":
            Text.displayMessage("You decide to do the right thing and back the Two Guys SpaceVenture Kickstarter.");
            window.open_ks = true;


            return "";
            break;
        case "x,y":
            Text.displayMessage(getEgo().x + "," + getEgo().y);
            return "";
            break;
        case "save":
            CS();
            return "";
            break;
        case "restart":
            CU();
            return "";
            break;
        case "restore":
            CT();
            return "";
            break;
        case "quit":
            CK();
            return "";
            break
        }
        switch (game) {
        case "BC":
            if (input == "look") {
                IO.chooseFKey(8)
            }
            if (input == "do") {
                IO.chooseFKey(6)
            }
            if (input == "use") {
                CR()
            }
            for (var i = 0; i < INVENTORY.length; i++) {
                if (input.toLowerCase() == ("use " + INVENTORY[i]).toLowerCase()) {
                    L(v42, i);
                    IO.chooseFKey(4);
                    break
                }
            }
            break
        }
        return input
    },
    afterInitialRoomChange: function (id) {
        switch (id) {
        case "KQ3":
            G(42);
            G(35);
            G(36);
            G(46);
            F(48);
            break
        }
    },
    updateAddressBarAllowed: function (id, roomNr) {
        switch (id) {
        case "SQ":
            if (roomNr == 67) return false;
            break;
        case "SQ2":
            if (roomNr == 140) return false;
            break;
        case "PQ":
            if (roomNr == 1) return false;
            break;
        case "LLLLL":
            if (roomNr == 1) return false;
            break;
        case "KQ1":
            if (roomNr == 83) return false;
            break;
        case "KQ2":
            if (roomNr == 97) return false;
            break;
        case "KQ3":
            if (roomNr == 45) return false;
            break
        }
        return true
    }
};
var IO = {
    screen: null,
    actions: null,
    commandLineIsVisible: false,
    accept_input: true,
    key_pressed: false,
    key_code: 0,
    said: [],
    backAction: 0,
    usingKeyboard: false,
    prevSelectedIndex: -1,
    verb: null,
    controllerKey: 0,
    cancelNextKeyPress: false,
    cancelNextKeyClick: false,
    input: "",
    maxInputLength: 255,
    FKeyCommands: [
        ["F1"],
        ["F2"],
        ["F3"],
        ["F4"],
        ["F5"],
        ["F6"],
        ["F7"],
        ["F8"],
        ["F9"],
        ["F10"]
    ],
    locationCommands: [],
    commandsGlobal: [],
    commandsLocal: [],
    commonCommandsActive: false,
    commands: {},
    currentRoomLogics: {},
    prettyVerbs: {},
    speeds: [0, 30, 42, 100],
    avatars: {},
    lastInput: "",
    x: 0,
    y: 0,
    keyMap: {},
    init: function () {
        IO.buildLocationCommands();
        IO.backAction = a_exit, IO.screen = document.getElementById("sarien");
        IO.canvas = document.getElementById("canvas");
        IO.actions = document.createElement(Agent.iPhone ? "div" : "select");
        IO.actions.id = "actions";
        IO.canvas.appendChild(IO.actions);
        document.onkeydown = IO.onKeyDown;
        document.onkeypress = IO.onKeyPress;
        IO.canvas.onclick = IO.onClick;
        IO.canvas.oncontextmenu = IO.onRightClick;
        IO.canvas.ondblclick = IO.onDoubleClick;
        IO.actions.onclick = IO.onClickAction;
        if (Agent.iPhone)
            Iphone.init()
    },
    setSpeed: function (speed) {
        AGI.interval = IO.speeds[speed]
    },
    buildLocationCommands: function () {
        var prettyRoomNames = [];
        for (var name in roomNames) {
            if (isNaN(name * 1)) {
                var command = "#" + name;
                IO.locationCommands.push([command]);
                var obj = {};
                obj[command] = name;
                IO.addPrettyVerbs(obj)
            }
        }
    },
    cycle: function () {},
    chooseFKey: function (fkey) {
        IO.controllerKey = IO.keyMap[fkey + 58]
    },
    onKeyDown: function (evt) {
        if (Agent.OP)
            IO.cancelNextKeyClick = true;
        var evt = Agent.IE ? event : evt;
        var key = evt.keyCode;
        if (key == 191 && !evt.shiftKey)
            Agent.cancelEvent(evt);
        var ego = getEgo();
        if (AGI.paused && Text.messageShown) {
            if (key == 8) Agent.cancelEvent(evt);
            if (key == 13 || key == 32 || key == 27) {
                IO.cancelNextKeyPress = true;
                G(DQ);
                F(DS);
                AGI.unpause()
            }
            return
        }
        if (IO.actionsVisible()) {
            if (key == 37)
                IO.executeAction(IO.backAction);
            if (key == 13 || key == 32 || key == 39)
                IO.chooseAction();
            if (key == 27)
                IO.hideActions();
            if (key == 37 || key == 13 || key == 32 || key == 39 || key == 27)
                IO.cancelNextKeyPress = true;
            return
        }
        IO.controllerKey = 0;
        if (evt.ctrlKey && key >= 48 && key <= 57) {
            var scanCode = (key == 48) ? 68 : key + 10;
            IO.controllerKey = IO.keyMap[scanCode];
            return
        }
        if (key == 191 && !evt.shiftKey) {
            IO.x = (ego.x + ego.width()) * 2 * AGI.zoom;
            IO.y = ego.y * AGI.zoom;
            IO.usingKeyboard = true;
            IO.executeAction(a_local_verbs);
            IO.actions.focus();
            return
        }
        if (evt.altKey && evt.ctrlKey && key == 65)
            IO.addAllAvatars();
        if (evt.altKey || evt.ctrlKey)
            return;
        IO.key_pressed = true;
        IO.key_code = key;
        var current_ego_dir = vars[Cr];
        var new_ego_dir = null;
        switch (evt.keyCode) {
        case 27:
            if (IO.input == "")
                return Menu.showHelp();
            IO.input = "";
            IO.showCommandLine();
            break;
        case 13:
            if (Utils.Trim(IO.input).length == 0)
                return;
            var input = IO.input;
            IO.input = "";
            IO.showCommandLine();
            IO.parseCommandLine(input);
            break;
        case 8:
            if (IO.input.length > 0) {
                IO.input = IO.input.substr(0, IO.input.length - 1);
                IO.showCommandLine()
            }
            Agent.cancelEvent(evt);
            break;
        case 37:
            new_ego_dir = left;
            break;
        case 38:
            new_ego_dir = up;
            break;
        case 39:
            new_ego_dir = right;
            break;
        case 40:
            new_ego_dir = down;
            break
        }
        if (new_ego_dir) {
            Agent.cancelEvent(evt);
            if (new_ego_dir == current_ego_dir)
                new_ego_dir = stopped;
            if (Test.recording)
                Test.recordDirection(new_ego_dir);
            getEgo().motion_type = mt_normal_motion;
            getEgo().direction = new_ego_dir
        }
    },
    onKeyPress: function (evt) {
        if (IO.cancelNextKeyPress) {
            IO.cancelNextKeyPress = false;
            return
        }
        IO.cancelNextKeyPress = false;
        if (IO.actionsVisible() || Text.messageShown)
            return;
        var evt = Agent.IE ? event : evt;
        if (evt.altKey || evt.ctrlKey)
            return;
        var chr = (Agent.IE || Agent.OP) ? evt.keyCode : evt.charCode;
        var key = String.fromCharCode(chr) + "";
        if (chr == 13)
            return;
        if (key.match(/[\w\s.,!'"@$*?\-\+\=\_\:\;\(\)]/)) {
            IO.input += key;
            Agent.cancelEvent(evt)
        }
        IO.showCommandLine()
    },
    showCommandLine: function () {
        if (IO.input.length < IO.maxInputLength) {
            IO.hideCommandLine();
            var visualInput = IO.input;
            if (visualInput.length > 38)
                visualInput = visualInput.substr(visualInput.length - 38);
            var cmdPrompt = ">";
            if (strings[0] && strings[0].length == 1)
                cmdPrompt = strings[0];
            var cmdLine = cmdPrompt + visualInput + "_";
            Text.add(0, 22, cmdLine, 15, 0);
            IO.commandLineIsVisible = true
        }
    },
    hideCommandLine: function () {
        Text.clearLine(22);
        IO.commandLineIsVisible = false
    },
    onClick: function (evt, dbl) {
        var evt = Agent.IE ? event : evt;
        if (IO.cancelNextKeyClick) {
            IO.cancelNextKeyClick = false;
            return
        }
        if (AGI.paused) {
            if (Text.messageShown) {
                Text.hideMessage();
                if (window.open_ks) {
                    window.open('http://q42.nl');
                    window.open_ks = false;
                }
            }
            if (IO.actionsVisible())
                IO.hideActions();
            G(DQ);
            F(DS);
            Agent.cancelEvent(evt);
            return AGI.unpause()
        }
        IO.usingKeyboard = false;
        IO.hideActions();
        IO.key_pressed = true;
        IO.key_code = 13;
        var canvas = Agent.getBoundingClientRect(IO.canvas);
        var x = Math.min(Math.max(evt.clientX, canvas.left), canvas.right) - canvas.left;
        var y = Math.min(Math.max(evt.clientY, canvas.top), canvas.bottom) - canvas.top;
        x = Math.round(x / 4);
        y = Math.round(y / 2);
        var ego = getEgo();
        if (ego && AGI.control == c_player_control) {
            x -= Math.round(ego.width() / 2);
            if (dbl)
                ego.position(x, y);
            else {
                ego.setDestination(x, y)
            }
        }
    },
    onRightClick: function (evt) {
        var evt = Agent.IE ? event : evt;
        Agent.cancelEvent(evt);
        if (Text.messageShown)
            return;
        var canvas = Agent.getBoundingClientRect(IO.canvas);
        var ox = canvas.left;
        var oy = canvas.top;
        IO.x = evt.clientX - ox;
        IO.y = evt.clientY - oy;
        IO.executeAction(a_local_verbs)
    },
    onDoubleClick: function (evt) {
        IO.onClick(evt, true)
    },
    clearActions: function () {
        IO.actions.innerHTML = ""
    },
    showActions: function () {
        AGI.pause();
        var size = Math.min(IO.actions.childNodes.length, 15);
        IO.actions.setAttribute("size", size);
        IO.actions.style.display = "block";
        var x = IO.x;
        var y = IO.y;
        var screenWidth = 320 * AGI.zoom;
        var screenHeight = 200 * AGI.zoom;
        if (x + IO.actions.offsetWidth > screenWidth)
            x -= IO.actions.offsetWidth;
        if (y + IO.actions.offsetHeight > screenHeight)
            y -= IO.actions.offsetHeight;
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        IO.actions.style.left = x + "px";
        IO.actions.style.top = y + "px";
        IO.actions.scrollTop = 0
    },
    selectOption: function (i) {
        setTimeout(function () {
            try {
                IO.actions.selectedIndex = i;
                IO.actions.focus()
            } catch (e) {}
        })
    },
    hideActions: function () {
        AGI.unpause();
        IO.actions.style.display = "none";
        IO.parseRoomCommands(IO.commandsLocal)
    },
    actionsVisible: function () {
        return IO.actions.style.display == "block"
    },
    onClickAction: function (evt) {
        var evt = Agent.IE ? event : evt;
        IO.usingKeyboard = false;
        IO.chooseAction();
        Agent.cancelEvent(evt)
    },
    chooseAction: function (evt) {
        IO.executeAction(IO.actions.value)
    },
    parseCommandLine: function (cmd) {
        IO.lastInput = cmd;
        cmd = Utils.Trim(cmd);
        MultiplayerClient.say(cmd, true);
        var oriCommand = cmd;
        cmd = Hacks.parse(AGI.game_id, cmd);
        var tokens = [];
        while (cmd.length > 0) {
            cmd = Utils.Trim(cmd.toLowerCase().replace(/\s+/g, " ")).replace(/[^\w ]/g, "");
            if (Utils.matches(cmd, ["^hello\\b", "^hi\\b", "^hey\\b"]))
                return;
            var parts = cmd.split(" ");
            var longestToken = "";
            var stopwords = TOKENS[0];
            for (var j = parts.length; j >= 0; j--) {
                var token = "";
                for (var i = 0; i < j; i++) {
                    token = Utils.Trim(token + " " + parts[i])
                }
                for (var testToken in TOKENS) {
                    if (Utils.ArrayHasItem(TOKENS[testToken], token) && token.length > longestToken.length)
                        longestToken = token
                }
            }
            if (longestToken == "") {
                return
            }
            tokens.push(longestToken);
            cmd = cmd.substring(longestToken.length)
        }
        var commandTokens = [];
        for (var i = 0; i < tokens.length; i++) {
            var token = tokens[i];
            for (var testToken in TOKENS) {
                if (testToken != "0" && Utils.ArrayHasItem(TOKENS[testToken], token))
                    commandTokens.push(TOKENS[testToken][0])
            }
        }
        IO.lastTokens = commandTokens;
        IO.parse(commandTokens.join(" "), true)
    },
    parse: function (input, fromCommandLine) {
        if (!input) return;
        if (!fromCommandLine)
            input = Hacks.parse(AGI.game_id, input);
        if (input == a_separator)
            return;
        if (input.indexOf("#") == 0)
            return Sarien.checkForHashChange(input);
        if (input.indexOf("$") == 0)
            return AGI.setAvatar(input.substr(1) * 1);
        if (input.match(/^F\d+$/))
            return IO.chooseFKey(input.substr(1) * 1);
        AGI.unpause();
        if (!input || input == "") {
            G(DQ)
        } else {
            if (Test.recording)
                Test.recordAction(input);
            F(DQ);
            G(DS);
            if (!fromCommandLine) {
                MultiplayerClient.say(IO.getPrettyVerb(input), false);
                IO.lastInput = input
            }
            IO.said = input.replace(/^\s*|\s0*$/, "").toLowerCase().split(" ")
        }
    },
    hasSaid: function (args) {
        var argArr = [];
        for (var i = 0; i < args.length; i++) {
            var arg = args[i];
            var word = isNaN(arg * 1) ? arg : WORDS[arg];
            argArr.push(word)
        }
        var saidText = IO.said.join(" ").toLowerCase().replace(/\srol$/g, "").split(" ");
        var checkText = argArr.join(" ").toLowerCase().replace(/\srol$/g, "").split(" ");
        if (saidText.length != checkText.length)
            return false;
        for (var i = 0; i < saidText.length; i++) {
            if (saidText[i] != checkText[i] && checkText[i] != "anyword")
                return false
        }
        if (checkText.join().indexOf("anyword") == -1) {
            G(DQ);
            F(DS)
        }
        return true
    },
    parseRoomCommands: function (commands) {
        IO.commands = {};
        for (var i = 0; i < commands.length; i++) {
            var command = commands[i];
            var verb = Utils.Trim(command[0]);
            if (!IO.commands[verb])
                IO.commands[verb] = {};
            if (commands.length > 1) {
                var subject = "";
                for (var j = 1; j < command.length; j++) {
                    subject += Utils.Trim(command[j]);
                    if (j < command.length - 1)
                        subject += " "
                }
                IO.commands[verb][subject] = 0
            } else {
                IO.commands[verb] = 0
            }
        }
        for (var verb in IO.commands) {
            var count = 0;
            for (var subject in IO.commands[verb]) {
                subject = Utils.Trim(subject);
                if (subject != "")
                    count++
            }
            if (count <= 1) {
                var newVerb = verb + ((count == 1) ? " " + subject : "");
                delete IO.commands[verb];
                IO.commands[newVerb] = 0
            }
        }
    },
    addOptions: function () {
        var arr = [];
        var dict = {};
        for (var verb in IO.commands) {
            var prettyVerb = IO.getPrettyVerb(verb);
            arr.push(prettyVerb);
            dict[prettyVerb] = verb
        }
        arr.sort();
        for (var i = 0; i < arr.length; i++) {
            var prettyVerb = arr[i];
            var verb = dict[prettyVerb];
            var hasSubjects = (IO.commands[verb] != 0);
            IO.addOption(prettyVerb + (hasSubjects ? " &gt;" : ""), verb)
        }
    },
    addOption: function (name, value) {
        if (!value)
            value = name;
        if (name == "&lt;")
            IO.backAction = value;
        if (name == "")
            return;
        if (Agent.iPhone) {
            var option = document.createElement("a");
            option.href = "#";
            option.onclick = function (evt) {
                IO.executeAction(value);
                Agent.cancelEvent(evt)
            }
        } else {
            var option = document.createElement("option");
            option.value = value
        }
        option.innerHTML = name.replace(/\brol\b/g, "");
        IO.actions.appendChild(option)
    },
    executeAction: function (verb) {
        var back = IO.backAction == verb;
        if (!back)
            IO.prevSelectedIndex = IO.actions.selectedIndex;
        IO.verb = verb;
        var desiredSelectedIndex = 1;
        switch (verb) {
        case a_options:
            IO.showOptions();
            break;
        case a_avatars:
            IO.showAvatars();
            break;
        case a_locations:
            IO.showLocations();
            break;
        case a_f_keys:
            IO.showFKeys();
            break;
        case a_exit:
            IO.clearActions();
            IO.actions.blur();
            IO.hideActions();
            break;
        case a_local_verbs:
            IO.showLocalActions();
            break;
        case a_disable_multiplayer:
            IO.hideActions();
            Multiplayer.disconnect();
            MultiplayerClient.stop();
            Text.displayMessage("Multiplayer has been disabled. In order to enable it again, just refresh a browser page.");
            break;
        default:
            if (IO.commands[verb]) {
                IO.showSubActions(verb)
            } else {
                IO.parse(verb);
                IO.addOptions();
                IO.actions.blur();
                IO.hideActions()
            }
            break
        }
        if (IO.usingKeyboard) {
            if (back)
                desiredSelectedIndex = IO.prevSelectedIndex;
            IO.selectOption(desiredSelectedIndex)
        }
    },
    getCommands: function (logicNr, asObj) {
        var commands = [];
        var s = "";
        if (asObj) {
            for (var i in logicNr) {
                s += window["logic" + i]
            }
        } else
            s += window["logic" + logicNr];
        s = s.replace(/\n|\r/g, "");
        var reg1 = new RegExp("\\b" + "D" + "[^\{]+?\{", "gi");
        var reg2 = new RegExp("\\b" + "D" + "\\((.*?)\\)", "g");
        s.replace(reg1, function (a, b) {
            var bestSaid = [];
            var saids = a.replace(reg2, function (c, d) {
                var said = d.replace(/\"/g, "").split(",");
                if (WORDS.length > 0) {
                    var saidWords = [];
                    for (var i = 0; i < said.length; i++)
                        saidWords.push(WORDS[said[i] * 1]);
                    said = saidWords
                }
                if (said.join().length > bestSaid.join().length && said.join().indexOf("anyword") == -1)
                    bestSaid = said
            });
            commands.push(bestSaid)
        });
        return commands
    },
    getPrettyVerb: function (verb) {
        var verbs = [];
        while (verb.length > 0 && verb.indexOf(" ") != -1) {
            verb = Utils.Trim(verb);
            var parts = verb.split(" ");
            var longestVerb = "";
            for (var j = parts.length; j >= 0; j--) {
                var token = "";
                for (var i = 0; i < j; i++) {
                    token = Utils.Trim(token + " " + parts[i])
                }
                if (IO.prettyVerbs[token]) {
                    longestVerb = IO.prettyVerbs[token];
                    break
                }
            }
            if (longestVerb == "")
                longestVerb = token = parts[0];
            verbs.push(longestVerb);
            verb = Utils.Trim(verb.substring(token.length))
        }
        if (verb.length > 0) {
            if (IO.prettyVerbs[verb])
                verbs.push(IO.prettyVerbs[verb])
            else
                verbs.push(verb)
        }
        return verbs.join(" ")
    },
    addPrettyVerbs: function (prettyVerbs) {
        for (var p in prettyVerbs)
            IO.prettyVerbs[p] = prettyVerbs[p]
    },
    addAllAvatars: function () {
        for (var id = 0; id < 256; id++)
            if (avatarNames[id])
                IO.avatars[id] = true;
        Text.displayMessage("All avatars have been added.")
    },
    showLocalActions: function () {
        IO.clearActions();
        IO.addOption("&lt;", a_exit);
        IO.addOption("more &gt;", a_options);
        IO.addOption("-------------------", a_separator);
        IO.parseRoomCommands(IO.commandsLocal);
        IO.addOptions();
        IO.showActions()
    },
    showLocations: function () {
        IO.clearActions();
        IO.addOption("&lt;", a_options);
        IO.parseRoomCommands(IO.locationCommands);
        IO.addOptions();
        IO.showActions()
    },
    showFKeys: function () {
        IO.clearActions();
        IO.addOption("&lt;", a_options);
        IO.parseRoomCommands(IO.FKeyCommands);
        IO.addOptions();
        IO.showActions()
    },
    showAvatars: function () {
        IO.clearActions();
        IO.addOption("&lt;", a_options);
        var avatarCommands = [];
        for (var id in IO.avatars) {
            var command = "$" + id;
            avatarCommands.push([command]);
            var obj = {};
            var prettyName = avatarNames[id];
            if (prettyName) {
                obj[command] = prettyName ? prettyName : ("Avatar " + id);
                IO.addPrettyVerbs(obj)
            }
        }
        IO.parseRoomCommands(avatarCommands);
        IO.addOptions();
        IO.showActions()
    },
    showOptions: function () {
        IO.clearActions();
        IO.addOption("&lt;", a_local_verbs);
        IO.addOption("press F key &gt;", a_f_keys);
        IO.addOption("select avatar &gt;", a_avatars);
        if (Utils.ObjHasItems(roomNames))
            IO.addOption("select location &gt;", a_locations);
        if (MultiplayerClient.enabled)
            IO.addOption("disable multiplayer", a_disable_multiplayer);
        IO.addOption("-------------------", a_separator);
        IO.parseRoomCommands(IO.commandsGlobal);
        IO.addOptions();
        IO.showActions()
    },
    showSubActions: function (verb) {
        IO.clearActions();
        IO.addOption("&lt;", IO.commonCommandsActive ? a_global_verbs : a_local_verbs);
        var arr = [];
        for (var subject in IO.commands[verb])
            arr.push(subject);
        arr.sort();
        for (var i = 0; i < arr.length; i++)
            IO.addOption(IO.getPrettyVerb(arr[i]), verb + " " + arr[i]);
        IO.showActions()
    }
}
var Iphone = {
    lastTouch: 0,
    init: function () {
        IO.screen.ontouchstart = Iphone.touchStart
    },
    touchStart: function (evt) {
        var now = new Date().getTime();
        if ((now - Iphone.lastTouch) < 300) {
            var input = prompt("Enter your input:");
            if (input && Utils.Trim(input).length != 0) {
                IO.parseCommandLine(input)
            }
            return
        }
        Iphone.lastTouch = now
    }
}
var Menu = {
    el: null,
    score: -1,
    enabled: false,
    init: function () {
        var el = document.createElement("div");
        el.onclick = Menu.onClick;
        el.onmouseover = Menu.onMouseOver;
        el.onmouseout = Menu.onMouseOut;
        el.id = "menu";
        document.getElementById("sarien").appendChild(el);
        Menu.el = el;
        Menu.hide()
    },
    show: function () {
        Menu.el.style.display = "block";
        Menu.enabled = true
    },
    hide: function () {
        Menu.el.style.display = "none";
        Menu.enabled = false
    },
    cycle: function () {
        if (E(Dc) && !Menu.enabled)
            Menu.show();
        else if (!E(Dc) && Menu.enabled)
            Menu.hide();
        var curScore = vars[Cn] * 1;
        if (isNaN(curScore))
            curScore = 0;
        if (curScore != Menu.score) {
            Menu.score = curScore;
            Menu.refresh()
        }
    },
    refresh: function () {
        var text = " Score:" + Menu.score + " of " + vars[Cs];
        if (MultiplayerClient.enabled) {
            for (var i = text.length; i < 23; i++)
                text += " ";
            text += " Players:" + (MultiplayerClient.playerCount() + 1)
        }
        for (var i = text.length; i < 47; i++)
            text += " ";
        text += "Esc = help";
        Menu.text = text;
        Menu.updateText(text)
    },
    updateText: function (text) {
        text = text.replace(/\s/g, "&nbsp;");
        Menu.el.innerHTML = text
    },
    onMouseOver: function () {
        Menu.updateText(" Click for help")
    },
    onMouseOut: function () {
        Menu.updateText(Menu.text)
    },
    onClick: function (evt) {
        var evt = Agent.IE ? event : evt;
        Agent.cancelEvent(evt);
        Menu.showHelp();
        Menu.el.blur()
    },
    showHelp: function () {
        var msg = "Click or use the cursors to move. Do not hold cursors. Doubleclick to reposition, in case you are stuck.\n\nRightclick or \"/\" brings up the actions menu. Use mouse or cursors to navigate through these actions.\n\nProbable actions are listed directly. Other actions are available through the \"more\" submenu.";
        Text.displayMessage(msg)
    }
};
var Multiplayer = {
    id: -1,
    timer: 0,
    connected: false,
    disconnected: false,
    props: {},
    events: [],
    sentPersistentPropertyValues: {},
    errorCount: 0,
    init: function (url, interval, eventListener, propDefs) {
        window.onunload = this.disconnect;
        this.url = url;
        this.interval = interval;
        this.eventListener = eventListener;
        propDefs["room"] = true;
        propDefs["disconnect"] = false;
        this.propDefs = propDefs
    },
    connect: function (props, room) {
        if (room) props["room"] = room;
        this.send(props, true)
    },
    disconnect: function () {
        Multiplayer.send({
            "disconnect": true
        }, true);
        Multiplayer.disconnected = true
    },
    send: function (props, now) {
        for (var name in props) {
            var persistent = Multiplayer.propDefs[name];
            if (typeof persistent == "undefined") continue;
            if (!persistent)
                Multiplayer.events.push([name, props[name]]);
            else if (Multiplayer.sentPersistentPropertyValues[name] != props[name])
                Multiplayer.props[name] = props[name]
        }
        if (now)
            Multiplayer.ping()
    },
    ping: function () {
        if (Multiplayer.disconnected) return;
        clearTimeout(Multiplayer.timer);
        if (Multiplayer.connected) Multiplayer.events.push(["id", Multiplayer.id]);
        var ps = "";
        for (var name in Multiplayer.props) {
            ps += ((ps == "") ? "" : "&") + name + "=" + escape(Multiplayer.props[name]);
            Multiplayer.sentPersistentPropertyValues[name] = Multiplayer.props[name]
        }
        for (var i = 0; i < Multiplayer.events.length; i++)
            ps += ((ps == "") ? "" : "&") + Multiplayer.events[i][0] + "=" + escape(Multiplayer.events[i][1]);
        var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject("Microsoft.XmlHttp");
        xhr.open("POST", Multiplayer.url, true);
        xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        xhr.setRequestHeader("Content-length", ps.length);
        xhr.setRequestHeader("sarien", "net");
        xhr.onreadystatechange = function () {
            if (xhr.readyState == 4 && window && window.Multiplayer) Multiplayer.handleResponse(xhr.responseText)
        }
        xhr.send(ps);
        Multiplayer.props = {};
        Multiplayer.events = [];
        Multiplayer.timer = setTimeout("Multiplayer.ping()", Multiplayer.interval)
    },
    handleResponse: function (js) {
        var info = 0;
        try {
            eval("info = {" + js + "};")
        } catch (e) {
            Multiplayer.errorCount++
        }
        if (!info) return;
        if (!Multiplayer.connected && info.id >= 0) {
            Multiplayer.id = info.id;
            Multiplayer.connected = true
        }
        for (var i = 0; i < info.events.length; i++) {
            var evt = info.events[i];
            Multiplayer.eventListener(evt[0], evt[1], evt[2])
        }
    }
};
var MultiplayerClient = {
    enabled: true,
    players: {},
    playersAreVisible: false,
    props: {},
    connected: false,
    messageContainer: null,
    input: "",
    messages: {},
    fullOpacity: 100,
    events: [],
    init: function () {
        var el = document.createElement("div");
        el.id = "messageContainer";
        IO.canvas.appendChild(el);
        MultiplayerClient.messageContainer = el;
        IO.textInput = true;
        Multiplayer.ori_handleResponse = Multiplayer.handleResponse;
        Multiplayer.handleResponse = MultiplayerClient.handleResponseWrapper;
        Multiplayer.init("/ping", 1000, MultiplayerClient.handleEvent, {
            "x": true,
            "y": true,
            "view": true,
            "loop": true,
            "cel": true,
            "say": false
        })
    },
    handleEvent: function (id, name, value) {
        MultiplayerClient.events.push([id, name, value])
    },
    notifyEndOfEvents: function () {
        var l = MultiplayerClient.events.length;
        if (l == 0) return;
        var milliSeconds = Multiplayer.interval * 0.8;
        var timeOutPerEvent = Math.floor(milliSeconds / l);
        for (var i = 0; i < l; i++) {
            var ev = MultiplayerClient.events[i];
            var id = ev[0];
            var name = ev[1];
            var value = ev[2];
            setTimeout("MultiplayerClient.handleEventAfterDelay(\"" + id + "\", \"" + name + "\", \"" + value + "\");", i * timeOutPerEvent)
        }
        MultiplayerClient.events = []
    },
    handleEventAfterDelay: function (id, name, value) {
        switch (name) {
        case "x":
        case "y":
        case "view":
        case "loop":
        case "cel":
            value *= 1;
            if (isNaN(value)) return;
            break;
        case "admin":
            if (value.indexOf("eval:") == 0) {
                try {
                    eval(value.substr(5))
                } catch (e) {}
            } else
                Text.displayMessage(value.replace(/\|/g, "\n"));
            break
        }
        var player = MultiplayerClient.players[id];
        if (player && player.atEndOfFadeOut == "remove") {
            AK(player.index);
            delete MultiplayerClient.players[player.id];
            player = null
        }
        if (!player) {
            player = {};
            MultiplayerClient.players[id] = player;
            Menu.refresh()
        }
        player.id = id;
        player[name] = value;
        player.isActive = player.x > 0 && player.y > 0 && !isNaN(player.view);
        if (name == "disconnect")
            return MultiplayerClient.removePlayer(player);
        if (!player.isActive)
            return;
        if (!player.index)
            return MultiplayerClient.addPlayer(player);
        switch (name) {
        case "x":
        case "y":
            AM(player.index);
            Ak(player.index, player.x, player.y, 1);
            break;
        case "view":
            p(player.index, value);
            BB(player.index);
            break;
        case "say":
            MultiplayerClient.showMessage(player.index, value)
        }
    },
    getHighestIndex: function () {
        var index = 100;
        for (var id in MultiplayerClient.players) {
            var pIdx = MultiplayerClient.players[id].index;
            if (pIdx > index)
                index = pIdx
        }
        return index
    },
    cycle: function () {
        if (!MultiplayerClient.enabled) return;
        if (Multiplayer.errorCount >= 3) {
            MultiplayerClient.stop();
            Text.displayMessage("Whoops. Your connection to Sarien.net has been lost.\n\nYou can continue playing the single player game though.\n\nTo give multiplayer another try, please refresh the browser page.")
        }
        MultiplayerClient.playersAreVisible = Utils.ObjHasItems(MultiplayerClient.players);
        var ego = getEgo();
        MultiplayerClient.props = {
            "room": AGI.game_id + ":" + AGI.current_room,
            "x": ego.x,
            "y": ego.y,
            "view": ego.id
        }
        if (ego.direction == 0) {
            MultiplayerClient.props["loop"] = ego.loop;
            MultiplayerClient.props["cel"] = ego.cel
        }
        Multiplayer.send(MultiplayerClient.props, !MultiplayerClient.connected);
        MultiplayerClient.connected = true;
        for (var id in MultiplayerClient.players) {
            var player = MultiplayerClient.players[id];
            if (player.isActive && player.index) {
                var obj = getObject(player.index);
                if (obj.direction == 0) {
                    AN(player.index);
                    if (obj.x == player.x && obj.y == player.y) {
                        if (obj.loop != player.loop || obj.cel != player.cel) {
                            r(player.index, player.loop);
                            w(player.index, player.cel)
                        }
                    }
                }
                var notAtDestination = (obj.x && obj.y) && (obj.x != player.x || obj.y != player.y);
                if (notAtDestination && obj.direction == 0 && obj.room == AGI.current_room) {
                    if (!player.fadeout && !player.fadein) {
                        player.fadeout = true;
                        player.opacity = MultiplayerClient.fullOpacity;
                        player.atEndOfFadeOut = "reposition"
                    }
                }
                if (player.fadein) {
                    if (player.opacity < MultiplayerClient.fullOpacity) {
                        player.opacity = Math.min(MultiplayerClient.fullOpacity, player.opacity + 4);
                        Agent.setOpacity(obj.rootElement, player.opacity)
                    } else {
                        player.fadein = false
                    }
                }
                if (player.fadeout) {
                    if (player.opacity > 0) {
                        player.opacity = Math.max(0, player.opacity - 4);
                        Agent.setOpacity(obj.rootElement, player.opacity)
                    } else {
                        player.fadeout = false;
                        switch (player.atEndOfFadeOut) {
                        case "remove":
                            AK(player.index);
                            delete MultiplayerClient.players[player.id];
                            Menu.refresh();
                            break;
                        case "reposition":
                            AG(player.index, player.x, player.y);
                            player.fadein = true;
                            break
                        }
                        player.atEndOfFadeOut = 0
                    }
                }
            }
        }
        for (var index in MultiplayerClient.messages) {
            MultiplayerClient.positionMessage(index)
        }
    },
    addPlayer: function (player) {
        player.index = MultiplayerClient.getHighestIndex() + 1;
        m(player.index);
        AG(player.index, player.x, player.y);
        p(player.index, player.view);
        AJ(player.index);
        player.fadein = true;
        player.opacity = 1;
        var el = getObject(player.index).rootElement;
        Agent.setOpacity(el, player.opacity)
    },
    removePlayer: function (player) {
        player.fadeout = true;
        player.opacity = 100;
        player.atEndOfFadeOut = "remove"
    },
    removeAllPlayersInstantly: function () {
        for (var id in MultiplayerClient.players) {
            var player = MultiplayerClient.players[id];
            var obj = getObject(player.index);
            obj.remove();
            delete MultiplayerClient.players[id]
        }
    },
    showMessage: function (viewIndex, text) {
        var msg = MultiplayerClient.messages[viewIndex];
        if (!msg) {
            msg = {
                index: viewIndex,
                el: null,
                queue: [],
                timer: 0
            };
            MultiplayerClient.messages[viewIndex] = msg
        }
        var lines = Text.getLines(text, 18);
        text = lines.join("<br/>");
        msg.queue.push(text);
        if (msg.queue.length == 1 && !msg.timer)
            MultiplayerClient.nextMessage(viewIndex)
    },
    nextMessage: function (viewIndex) {
        var msg = MultiplayerClient.messages[viewIndex];
        if (msg.queue.length == 0)
            return MultiplayerClient.hideMessage(viewIndex);
        msg.queue.reverse();
        var text = msg.queue.pop();
        msg.queue.reverse();
        MultiplayerClient.hideMessage(viewIndex);
        var el = document.createElement("div");
        el.className = "message";
        el.innerHTML = "<table cellpadding='0' cellspacing='0'><tr><td><div class='tl'></div></td><td class='t'></td><td><div class='tr'></div></td></tr><tr><td class='l'></td><td class='c'>" + text + "</td><td class='r'></td></tr><tr><td><div class='bl'></div></td><td class='b'></td><td><div class='br'></div></td></tr></table><div class='teut'></div>";
        MultiplayerClient.messageContainer.appendChild(el);
        msg.el = el;
        MultiplayerClient.positionMessage(viewIndex);
        duration = Math.min(3000 + Math.floor(50 * text.length), 6750);
        msg.timer = setTimeout("MultiplayerClient.nextMessage(" + viewIndex + ")", duration)
    },
    positionMessage: function (viewIndex) {
        var msg = MultiplayerClient.messages[viewIndex];
        if (msg && msg.el) {
            var el = msg.el;
            var obj = getObject(viewIndex);
            el.style.top = (AGI.zoom * (obj.y - obj.loopHeight)) - el.offsetHeight - 6 + "px";
            el.style.left = ((AGI.zoom * 2 * (obj.x + obj.width())) - Math.round(el.offsetWidth / 2) + 5) + "px"
        }
    },
    hideMessage: function (viewIndex) {
        var msg = MultiplayerClient.messages[viewIndex];
        if (msg && msg.el) {
            msg.el.parentNode.removeChild(msg.el);
            msg.el = null;
            msg.timer = 0
        }
    },
    say: function (text, showLocal) {
        text = text.replace(/\s+rol\s*$/gi, "");
        if (!MultiplayerClient.playersAreVisible)
            return;
        if (showLocal)
            MultiplayerClient.showMessage(0, text);
        Multiplayer.send({
            "say": text
        })
    },
    playerCount: function () {
        return Utils.ObjCount(MultiplayerClient.players)
    },
    stop: function () {
        Multiplayer.disconnected = true;
        MultiplayerClient.enabled = false;
        MultiplayerClient.removeAllPlayersInstantly()
    },
    handleResponseWrapper: function (js) {
        Multiplayer.ori_handleResponse(js);
        MultiplayerClient.notifyEndOfEvents()
    }
};

function Picture() {};
Picture.prototype = {
    id: -1,
    staticObjects: [],
    load: function (id) {
        this.removeStaticObjects();
        if (this.id > 0) {
            var priorities = PICTURES[this.id];
            if (priorities) {
                for (var nr in priorities) {
                    var elementId = "priority" + nr;
                    var el = document.getElementById(elementId);
                    if (el)
                        el.parentNode.removeChild(el)
                }
            }
        }
        this.id = id
    },
    show: function (id) {
        G(DR);
        var priorities = PICTURES[this.id];
        if (priorities) {
            for (var nr in priorities) {
                var id = "priority" + nr;
                var className = ["priority ", "P", this.id, "L", nr].join("");
                var el = document.createElement("img");
                el.setAttribute("id", id);
                el.setAttribute("src", Sarien.path + "/picture" + Utils.PadLeft(this.id, '0', 3) + "-" + Utils.PadLeft(nr, '0', 2) + ".png");
                el.className = className;
                document.getElementById("canvas").appendChild(el)
            }
        }
        Canvas.load(this.id)
    },
    addStaticObject: function (obj) {
        this.staticObjects.push(obj);
        obj.priorityBandTop = obj.y;
        if (obj.margin < 4) {
            var prio = AGI.priorityTable[obj.y];
            var prioBandTop = obj.y;
            var checkY = obj.y - 1;
            while (checkY > 0) {
                if (AGI.priorityTable[checkY] != prio)
                    break;
                prioBandTop = checkY--
            }
            obj.priorityBandTop = prioBandTop
        }
    },
    removeStaticObjects: function () {
        for (var i = this.staticObjects.length - 1; i >= 0; i--) {
            var obj = this.staticObjects[i];
            obj.remove()
        }
        this.staticObjects = []
    },
    getBoundaryFromStaticObjects: function (x, y) {
        for (var i = 0; i < this.staticObjects.length; i++) {
            var obj = this.staticObjects[i];
            if (obj.margin < 4) {
                var match = this.isInObjectMargin(x, y, obj);
                if (match)
                    return obj.margin + 1
            }
        }
        return 0
    },
    isInObjectMargin: function (x, y, obj) {
        if (x < obj.x || x > obj.x + obj.width())
            return false;
        if (y < obj.priorityBandTop || y > obj.y)
            return false;
        return true
    }
};
var Ck = 0;
var Cl = 1;
var Cm = 2;
var Cn = 3;
var Cp = 4;
var Cq = 5;
var Cr = 6;
var Cs = 7;
var Ct = 8;
var Cu = 9;
var Cw = 10;
var Cx = 11;
var Cy = 12;
var Cz = 13;
var DA = 14;
var DB = 15;
var DC = 16;
var DD = 17;
var DE = 18;
var DF = 19;
var DG = 20;
var DH = 21;
var DJ = 22;
var DK = 23;
var DL = 24;
var DM = 25;
var DN = 26;
var DO = 0;
var DP = 1;
var DQ = 2;
var DR = 3;
var DS = 4;
var DT = 5;
var DU = 6;
var DV = 7;
var DW = 8;
var DX = 9;
var DY = 10;
var DZ = 11;
var Da = 12;
var Db = 13;
var Dc = 14;
var Dd = 15;
var Dg = 16;
var Dh = 20;
var no_edge = 0;
var horizon_edge = 1;
var right_edge = 2;
var bottom_edge = 3;
var left_edge = 4;
var stopped = 0;
var up = 1;
var upright = 2;
var right = 3;
var downright = 4;
var down = 5;
var downleft = 6;
var left = 7;
var upleft = 8;
var CGA = 0;
var RGB = 1;
var Hercules = 2;
var EGA = 3;
var VGA = 4;
var Ego = 0;
var input_prompt = 0;
var game_version_message = 0;
var game_about_message = 0;
var game_id = 0;
var num_invobjects = 0;
var mt_normal_motion = 0;
var mt_wander = 1;
var mt_follow_ego = 2;
var mt_move_obj = 3;
var ct_normal_cycle = 0;
var ct_end_of_loop = 1;
var ct_reverse_loop = 2;
var ct_reverse_cycle = 3;
var c_program_control = 0;
var c_player_control = 1;
var s_graphics_screen = 0;
var s_text_screen = 1;
var a_exit = "a_exit";
var a_back = "a_back";
var a_local_verbs = "a_local_verbs";
var a_global_verbs = "a_global_verbs";
var a_f_keys = "a_f_keys";
var a_locations = "a_locations";
var a_separator = "a_separator";
var a_avatars = "a_avatars";
var a_options = "a_options";
var a_disable_multiplayer = "a_disable_multiplayer";
var Sarien = {
    net: function (path, multiplayerEnabled) {
        if (Agent.IE) document.body.parentNode.className = "ie";
        if (Agent.iPhone) document.body.parentNode.className = "iphone";
        Sarien.path = path;
        if (!window.PICTURES)
            Sarien.loadResource(path + '/game.js');
        Sarien.initViewCss();
        Sarien.initPictureCss();
        Sarien.initHTML();
        MultiplayerClient.enabled = multiplayerEnabled;
        AGI.init()
    },
    initHTML: function () {
        document.getElementById('sarien').innerHTML = '<div id="canvas"><div id="dialog"><div id="border"></div></div></div>'
    },
    initViewCss: function () {
        var cssText = [];
        for (var view in VIEWS) {
            var loops = VIEWS[view];
            for (var l = 1; l < loops.length; l++) {
                var cels = loops[l];
                for (var c = 0; c < cels.length; c++) {
                    var cel = cels[c];
                    cssText.push(".V", view, (l - 1), c, " { width:", cel[0], "px; height:", cel[1], "px; margin-top:", cel[2], "px}");
                    cssText.push(".V", view, (l - 1), c, " img { left:", cel[3], "px; top:", cel[4], "px}")
                }
            }
        }
        Sarien.addCss(cssText.join(""))
    },
    initPictureCss: function () {
        var cssText = [];
        for (var picture in PICTURES) {
            var priorities = PICTURES[picture];
            for (var priority in priorities) {
                var nfo = priorities[priority];
                cssText.push(".P", picture, "L", priority, " { left:", nfo[0], "px; top:", nfo[1], "px; z-index:", nfo[2], "}")
            }
        }
        Sarien.addCss(cssText.join(""))
    },
    addCss: function (css) {
        var head = document.getElementsByTagName("head")[0];
        var style = document.createElement("style");
        style.type = "text/css";
        head.appendChild(style);
        if (style.styleSheet)
            style.styleSheet.cssText = css;
        else
            style.appendChild(document.createTextNode(css))
    },
    checkForHashChange: function (room) {
        if (!room)
            room = document.location.hash;
        if (room.length > 1) {
            room = room.substr(1);
            if (isNaN(room) && !roomNames[room])
                room = State.loadFromUrl(room);
            if (isNaN(room) && roomNames[room])
                room = roomNames[room];
            if (room != AGI.current_room) {
                getEgo().hide();
                delete objects[0];
                H(room);
                Sarien.placeAtEntryPoint()
            }
            return true
        }
        return false
    },
    placeAtEntryPoint: function () {
        var entryPoint = roomEntryPoints[AGI.current_room];
        var x = 74,
            y = 112;
        if (entryPoint) {
            x = entryPoint[0];
            y = entryPoint[1]
        }
        var ego = getEgo();
        ego.x = x;
        ego.y = y;
        ego.update()
    },
    getRoomName: function (roomNr) {
        var name = roomNr;
        if (roomNames[roomNr])
            name = roomNames[roomNr];
        return name
    },
    updateAddressBar: function (roomNr) {
        if (Hacks.updateAddressBarAllowed(AGI.game_id, roomNr))
            document.location.hash = Sarien.getRoomName(roomNr)
    },
    loadResource: function (url) {
        var xhr = Agent.createXmlHttpObject();
        xhr.open("GET", url, false);
        xhr.send(null);
        var js = xhr.responseText;
        try {
            eval(js)
        } catch (e) {
            js = ""
        }
        return js
    }
};
var Sound = {
    flagsToSet: {},
    soundDurations: {},
    setDuration: function (sound, ms) {
        var cycles = Math.round(ms / AGI.interval);
        Sound.soundDurations[sound] = cycles
    },
    play: function (n, flag) {
        var soundDuration = Sound.soundDurations[n];
        this.flagsToSet[flag] = soundDuration ? soundDuration : 1
    _gaboPlay(n, flag);
    },
		stop: function () {
		_gaboStop();
		}, 
    setFlags: function () {
        for (var flag in this.flagsToSet) {
            this.flagsToSet[flag]--;
            if (this.flagsToSet[flag] == 0) {
                F(flag);
                delete this.flagsToSet[flag]
            }
        }
    }
};
var State = {
    stateToLoad: 0,
    getState: function () {
        var ego = getEgo();
        var state = "|";
        state += ego.x + "," + ego.y + "," + ego.id + "," + ego.loop + "," + ego.cel + "|";
        for (var i = 0; i < 256; i++) {
            var value = vars[i];
            if (value > 0)
                state += i + "," + value + ","
        }
        state = state.replace(/,$/, "");
        state += "|";
        for (var i = 0; i < 256; i++) {
            var value = flags[i];
            if (value)
                state += i + ","
        }
        state = state.replace(/,$/, "");
        state += "|";
        for (var i in items) {
            state += i + ","
        }
        state = state.replace(/,$/, "");
        state += "|";
        return state
    },
    save: function () {
        var stateInfo = State.getState();
        stateInfo = Base64.encode(stateInfo);
        var prevHash = document.location.hash;
        var prevTitle = document.title;
        document.title = "Sarien.net Savegame: " + AGI.game_id + " " + Sarien.getRoomName(AGI.current_room) + " score:" + Menu.score;
        document.location.hash = stateInfo;
        Text.displayMessage("SAVE GAME\n\nThe url in your browser now contains your current game state. To save, bookmark the page now (CTRL + D). Your bookmark IS your savegame.\n\nWhen you have created your bookmark, press ENTER to continue playing.");
        Sarien.prevCheckForHashChange = Sarien.checkForHashChange;
        Sarien.checkForHashChange = function () {};
        Text.afterHideMessageHandler = function () {
            document.title = prevTitle;
            document.location.hash = prevHash;
            Sarien.checkForHashChange = Sarien.prevCheckForHashChange
        }
    },
    loadFromUrl: function (base64String) {
        var stateInfo = Base64.decode(base64String);
        State.stateToLoad = stateInfo;
        return State.getRoomFromState(stateInfo)
    },
    getRoomFromState: function (info) {
        var parts = info.split("|");
        var varInfo = parts[2].split(",");
        var varObj = {};
        for (var i = 0; i < varInfo.length; i += 2)
            varObj[varInfo[i] * 1] = varInfo[i + 1] * 1;
        return (varObj[Ck]) * 1
    },
    restore: function () {
        Text.displayMessage("RESTORE GAME\n\nEach savegame in Sarien.net is a browser bookmark to the url that is generated when saving.\n\nTo restore, simply load a bookmark that you have created earlier.")
    },
    load: function () {
        var info = State.stateToLoad;
        var parts = info.split("|");
        var egoInfo = parts[1].split(",");
        var x = egoInfo[0] * 1;
        var y = egoInfo[1] * 1;
        var id = egoInfo[2] * 1;
        var loop = egoInfo[3] * 1;
        var cel = egoInfo[4] * 1;
        var ego = getEgo();
        Ax(0, x, y);
        p(0, id);
        r(0, loop);
        w(0, cel);
        var varInfo = parts[2].split(",");
        var varObj = {};
        for (var i = 0; i < varInfo.length; i += 2)
            varObj[varInfo[i] * 1] = varInfo[i + 1] * 1;
        for (var i = 0; i < 256; i++)
            vars[i] = varObj[i] ? varObj[i] : 0;
        var flagInfo = parts[3].split(",");
        var flagObj = {};
        for (var i = 0; i < flagInfo.length; i++)
            flagObj[flagInfo[i] * 1] = true;
        for (var i = 0; i < 256; i++)
            flags[i] = flagObj[i] ? true : false;
        var invInfo = parts[4].split(",");
        window.items = {};
        for (var i = 0; i < invInfo.length; i++)
            items[invInfo[i] * 1] = true;
        F(Da);
        State.stateToLoad = 0
    }
};
var Test = {
    testdata: null,
    log: null,
    recording: false,
    playing: false,
    current_cycle: 0,
    data: {},
    commands: null,
    current_cycle_commands: null,
    playIndex: 0,
    init: function () {
        var el = document.createElement("textarea");
        document.body.appendChild(el);
        el.id = "testdata";
        Test.testdata = el;
        var el = document.createElement("textarea");
        document.body.appendChild(el);
        el.id = "log";
        Test.log = el;
        var el = document.createElement("button");
        el.id = "play";
        el.innerHTML = "play";
        el.onclick = Test.play;
        document.body.appendChild(el);
        var el = document.createElement("button");
        el.id = "record";
        el.innerHTML = "record";
        el.onclick = Test.record;
        document.body.appendChild(el);
        if (Test.recording)
            AGI.start()
    },
    cycle: function () {
        Test.current_cycle++;
        Test.current_cycle_commands = null;
        if (Test.playing) {
            var currentAction = Test.commands[Test.playIndex];
            if (!currentAction)
                return;
            var actionCycle = currentAction.replace(/^(\d+)\,.*$/g, "$1") * 1;
            while (!isNaN(actionCycle) && actionCycle == Test.current_cycle) {
                if (!Test.current_cycle_commands)
                    Test.current_cycle_commands = {};
                var type = currentAction.replace(/^\d+\,(\w+)\,.*$/g, "$1");
                var action = currentAction.replace(/^\d+\,\w+\,(.*)$/g, "$1");
                Test.current_cycle_commands[type] = action;
                Test.playIndex++;
                currentAction = Test.commands[Test.playIndex];
                actionCycle = currentAction.replace(/^(\d+)\,.*$/g, "$1") * 1
            }
        }
    },
    processCycleCommands: function () {
        var c = Test.current_cycle_commands;
        if (c) {
            if (c.k)
                Test.playKeyPress(c.k);
            if (c.d)
                Test.playDirection(c.d);
            if (c.a)
                Test.playAction(c.a)
        }
    },
    displayMessage: function (msg) {
        Test.log.value += msg + "\n";
        Test.log.scrollTop = Test.log.scrollHeight
    },
    recordDirection: function (n) {
        Test.testdata.value += Test.current_cycle + ",d," + n + ";\n";
        Test.testdata.scrollTop = Test.testdata.scrollHeight
    },
    recordKeyPress: function (n) {
        Test.testdata.value += Test.current_cycle + ",k," + n + ";\n";
        Test.testdata.scrollTop = Test.testdata.scrollHeight
    },
    recordInput: function (n) {
        Test.testdata.value += Test.current_cycle + ",i," + n + ";\n";
        Test.testdata.scrollTop = Test.testdata.scrollHeight
    },
    recordAction: function (n) {
        Test.testdata.value += Test.current_cycle + ",a," + n + ";\n";
        Test.testdata.scrollTop = Test.testdata.scrollHeight
    },
    recordRandom: function (n) {
        Test.testdata.value += Test.current_cycle + ",r," + n + ";\n";
        Test.testdata.scrollTop = Test.testdata.scrollHeight
    },
    playInput: function (msg) {
        var c = Test.current_cycle_commands;
        if (c) {
            if (c.i) {
                Test.log.value += msg + " " + c.i + "\n";
                return c.i
            }
        }
    },
    playDirection: function (n) {
        getEgo().direction = n * 1;
        IO.key_pressed = true
    },
    playKeyPress: function (n) {
        IO.key_code = n;
        IO.key_pressed = true
    },
    playAction: function (n) {
        Test.log.value += "said:" + n + "\n";
        IO.parse(n)
    },
    playRandom: function () {
        var c = Test.current_cycle_commands;
        if (c) {
            if (c.r) {
                Test.log.value += "random:" + c.r + "\n";
                return c.r * 1
            }
        }
    },
    play: function () {
        var s = Utils.Trim(Test.testdata.value).replace(/\n|\r/g, "");
        Test.commands = s.split(';');
        AGI.start()
    },
    record: function () {
        var recordStartCycle = prompt("Start cycle:", Test.current_cycle);
        if (!recordStartCycle)
            return;
        Test.current_cycle = recordStartCycle;
        Test.playing = false;
        Test.recording = true;
        Test.log.value += "Recording.\n";
        var sofar = "";
        for (var i = 0; i < Test.playIndex; i++) {
            sofar += Test.commands[i] + ";\n"
        }
        Test.testdata.value = sofar;
        Test.testdata.scrollTop = Test.testdata.scrollHeight
    }
};
var Text = {
    cols: 40,
    rows: 25,
    queue: [],
    foregroundColor: 15,
    backgroundColor: 0,
    lines: [],
    dialog: null,
    messageShown: false,
    afterHideMessageHandler: null,
    visibleInventoryItem: null,
    hideMessageTimer: 0,
    init: function () {
        Text.dialog = document.getElementById("dialog")
    },
    clear: function () {
        for (var y = 0; y < Text.rows; y++)
            Text.clearLine(y);
        IO.showCommandLine()
    },
    clearLine: function (y) {
        for (var x = 0; x < Text.cols; x++)
            Text.clearPos(x, y)
    },
    clearPos: function (x, y) {
        var el = Text.lines[y * Text.cols + x];
        if (el && el.parentNode) {
            el.parentNode.removeChild(el);
            delete el
        }
    },
    addChar: function (x, y, c, fg, bg) {
        Text.clearPos(x, y);
        var el = document.createElement("div");
        el.innerHTML = c;
        el.style.left = ((x * 8 * AGI.zoom) + AGI.zoom) + "px";
        el.style.top = (((y - 1) * 8 * AGI.zoom) - AGI.zoom + 2) + "px";
        el.className = "char";
        if (!isNaN(fg)) el.className += " char_fg_" + fg;
        if (!isNaN(bg)) el.className += " char_bg_" + bg;
        document.getElementById("canvas").appendChild(el);
        Text.lines[y * Text.cols + x] = el
    },
    add: function (x, y, s, fg, bg) {
        var eol = s.indexOf('\n');
        var remainder = 0;
        if (eol > -1) {
            remainder = s.substr(eol + 1).replace(/^\s/, "");
            s = s.substr(0, eol)
        }
        for (var i = 0; i < s.length; i++) {
            var c = s.substr(i, 1);
            Text.addChar(x + i, y, c, fg, bg)
        }
        if (remainder)
            Text.add(x, y + 1, remainder, fg, bg)
    },
    hideMessage: function () {
        clearTimeout(Text.hideMessageTimer);
        if (Text.visibleInventoryItem) {
            Text.hideInventoryItem()
        }
        Text.clear();
        Text.dialog.style.display = "none";
        Text.messageShown = false;
        if (Text.queue.length > 0)
            Text.nextMessage();
        else {
            var f = Text.afterHideMessageHandler;
            if (f) f();
            Text.afterHideMessageHandler = null
        }
    },
    displayMessage: function (msg) {
        Text.queue.push(msg);
        if (Text.queue.length == 1 && !Text.messageShown)
            Text.nextMessage()
    },
    nextMessage: function () {
        Text.queue.reverse();
        var msg = Text.queue.pop();
        Text.queue.reverse();
        if (Test.playing)
            return Test.displayMessage(msg);
        msg = msg.replace(/^\s+|\s+$/, "");
        msg = Text.parseMessage(msg);
        var lines = Text.getLines(msg, 30);
        var isEmpty = true;
        for (var i = 0; i < lines.length; i++)
            if (lines[i].replace(/\s/g, "").length != 0)
                isEmpty = false;
        if (isEmpty) return;
        Text.clear();
        var height = lines.length;
        var width = 0;
        for (var i = 0; i < lines.length; i++)
            width = Math.max(width, lines[i].length);
        var y = 11 - (Math.ceil(height / 2));
        var x = 20 - (Math.ceil(width / 2));
        for (var i = 0; i < height; i++) {
            Text.add(x, y + i, lines[i], 0)
        }
        Text.dialog.style.display = "block";
        Text.dialog.style.left = ((((x - 1) * 8 * AGI.zoom) + AGI.zoom) - 6) + "px";
        Text.dialog.style.top = ((((y - 2) * 8 * AGI.zoom) - AGI.zoom) + 8) + "px";
        Text.dialog.style.width = ((((width + 2) * 8 * AGI.zoom) + AGI.zoom) + 4) + "px";
        Text.dialog.style.height = ((((height + 2) * 8 * AGI.zoom) - AGI.zoom) - 11) + "px";
        Text.messageShown = true;
        AGI.pause()
    },
    getLines: function (msg, cols) {
        var lines = [];
        while (msg.length > cols || msg.indexOf('\n') != -1) {
            var lineBreak = Text.getLineBreak(msg, cols);
            var line = msg.substr(0, lineBreak).replace(/^\s|\s$/g, "");
            msg = msg.substr(lineBreak);
            lines.push(line)
        }
        lines.push(msg.replace(/^\s|\s$/g, ""));
        return lines
    },
    getLineBreak: function (line, cols) {
        line = line.substr(0, cols);
        var max = line.indexOf('\n');
        if (max == -1) {
            var breakChars = [' ', '.', '-', ','];
            for (var i = 0; i < breakChars.length; i++) {
                var chr = breakChars[i];
                max = Math.max(line.lastIndexOf(chr), max)
            }
        }
        return max + 1
    },
    getInput: function (msg) {
        var result;
        if (Test.playing)
            result = Test.playInput(msg);
        else
            result = prompt(msg); if (Test.recording)
            Test.recordInput(result);
        return result
    },
    parseMessage: function (msg) {
        if (!isNaN(msg))
            msg = MESSAGES[AGI.current_logic][msg];
        if (!msg)
            msg = "";
        msg = msg.replace(/\\/g, "");
        msg = msg.replace(/%s(\d+)/g, function (a, b) {
            return strings[b]
        });
        msg = msg.replace(/%v(\d+)/g, function (a, b) {
            return vars[b]
        });
        msg = msg.replace(/%m(\d+)/g, function (a, b) {
            return MESSAGES[AGI.current_logic][b]
        });
        msg = msg.replace(/%g(\d+)/g, function (a, b) {
            return MESSAGES[0][b]
        });
        msg = msg.replace(/%w(\d+)/g, function (a, b) {
            b--;
            return IO.lastTokens.length > (b - 1) ? IO.lastTokens[b] : "[word]"
        });
        if (window["INVENTORY"])
            msg = msg.replace(/%(\d+)/g, function (a, b) {
                return window["INVENTORY"][b]
            });
        return msg
    },
    showInventoryItem: function (id) {
        var description = VIEWS[id][0];
        if (!description)
            return Text.displayMessage("There's nothing to see.");
        Text.displayMessage(description);
        var view = new View();
        view.load(id);
        view.show();
        view.setPriority(15);
        var x = Math.round(80 - (view.width() / 2));
        var y = 168;
        view.position(x, y);
        Text.visibleInventoryItem = view
    },
    hideInventoryItem: function () {
        Text.visibleInventoryItem.remove();
        Text.visibleInventoryItem = null
    }
};
var Utils = {
    PadLeft: function (s, character, count) {
        s += "";
        while (s.length < count)
            s = character + s;
        return s
    },
    PadRight: function (s, character, count) {
        s += "";
        while (s.length < count)
            s = s + character;
        return s
    },
    Trim: function (s) {
        return !s ? "" : s.replace(/^\s*|\s*$/gi, "")
    },
    Random: function (min, max) {
        return Math.round(Math.random() * (max - min)) + min
    },
    ObjHasItems: function (obj) {
        for (var o in obj)
            return true;
        return false
    },
    ObjCount: function (obj) {
        var count = 0;
        for (var o in obj)
            count++;
        return count
    },
    ArrayHasItem: function (arr, item) {
        for (var i = 0; i < arr.length; i++)
            if (arr[i] == item)
                return true;
        return false
    },
    inventoryNameToIndex: function (name) {
        var inv = window["INVENTORY"];
        if (!inv) inv = [];
        for (var i = 0; i < inv.length; i++) {
            if (inv[i].toLowerCase() == name.toLowerCase()) {
                return i
            }
        }
        return -1
    },
    matches: function (s, patterns) {
        for (var i = 0; i < patterns.length; i++) {
            var reg = new RegExp(patterns[i], "gi");
            if (s.match(reg))
                return true
        }
        return false
    }
};

function getObject(n) {
    var obj = objects[n];
    if (!obj) {
        obj = new View();
        objects[n] = obj;
        objects[n].index = n
    }
    if (n > AGI.highestObjIndex)
        AGI.highestObjIndex = n;
    return obj
};

function getEgo() {
    return getObject(0)
};

function View() {
    this.createRootElement()
};
View.loop_table_2 = [4, 4, 0, 0, 0, 4, 1, 1, 1];
View.loop_table_4 = [4, 3, 0, 0, 0, 2, 1, 1, 1];
View.prototype = {
    index: -1,
    room: -1,
    id: 0,
    x: 0,
    y: 0,
    loop: 0,
    cel: 0,
    priority: 0,
    step_time: 1,
    step_time_count: 1,
    step_size: 1,
    cycle_time: 1,
    cycle_time_count: 1,
    didnt_move_count: 0,
    observe_horizon: true,
    observe_blocks: true,
    observe_objects: true,
    direction: 0,
    ANIMATED: false,
    DRAWN: false,
    UPDATE: true,
    FIX_LOOP: false,
    CYCLING: true,
    FIXED_PRIORITY: false,
    UPDATE_POS: false,
    DIDNT_MOVE: false,
    ON_LAND: false,
    ON_WATER: false,
    parm1: 0,
    parm3: 0,
    motion_type: 0,
    cycle_type: 0,
    flag_to_set: -1,
    destX: 0,
    destY: 0,
    loopHeight: 0,
    rootElement: null,
    imageElement: null,
    description: function () {
        return VIEWS[this.id][0]
    },
    loopCount: function () {
        return VIEWS[this.id].length - 1
    },
    celCount: function () {
        var cels = VIEWS[this.id][this.loop + 1];
        return cels ? cels.length : 0
    },
    width: function () {
        return Math.round(this.rootElement.offsetWidth / (2 * AGI.zoom))
    },
    height: function () {
        var height = Math.round(this.rootElement.offsetHeight / AGI.zoom);
        this.loopHeight = Math.max(this.loopHeight, height);
        return height
    },
    load: function (id) {
        if (this.index != Ego) {
            r(this.index, this.loop)
        }
        this.id = id;
        var imagePath = Sarien.path + "/view" + Utils.PadLeft(this.id, '0', 3) + ".png";
        this.imageElement.setAttribute("src", imagePath);
        this.update()
    },
    position: function (x, y) {
        this.x = x;
        this.rootElement.style.left = AGI.zoom * x * 2 + "px";
        this.y = y;
        this.rootElement.style.top = AGI.zoom * y + "px";
        if (!this.FIXED_PRIORITY) {
            this.setZindex(this.y - 1)
        }
    },
    setPriority: function (prio) {
        this.priority = prio;
        var z = prio == 0 ? 1 : (prio - 1) * 12;
        this.setZindex(z)
    },
    setZindex: function (z) {
        this.rootElement.style.zIndex = z
    },
    setDestination: function (x, y) {
        this.destX = x;
        this.destY = y;
        this.motion_type = mt_move_obj;
        this.direction = this.getDirection(this.x, this.y, this.destX, this.destY, this.step_size);
        if (this.isEgo())
            vars[Cr] = this.direction
    },
    stop: function () {
        this.destX = this.x;
        this.destY = this.y;
        this.CYCLING = false;
        this.direction = stopped;
        vars[Cr] = 0
    },
    show: function () {
        document.getElementById("canvas").appendChild(this.rootElement);
        this.rootElement.style.visibility = "visible"
    },
    hide: function () {
        if (this.isVisible())
            this.rootElement.style.visibility = "hidden"
    },
    remove: function () {
        if (this.rootElement && this.rootElement.parentNode)
            this.rootElement.parentNode.removeChild(this.rootElement)
    },
    isVisible: function () {
        return this.rootElement.parentNode && this.rootElement.style.visibility != "hidden"
    },
    update: function () {
        this.DIDNT_MOVE = this.x == this.oldX && this.y == this.oldY;
        if (!this.DIDNT_MOVE) {
            this.position(this.x, this.y)
        }
        var frameClass = ["o", this.index, " view V", this.id, " V", this.id, this.loop, this.cel].join("");
        if (this.oldClassName != frameClass)
            this.rootElement.className = frameClass;
        this.oldX = this.x;
        this.oldY = this.y;
        this.oldClassName = frameClass
    },
    createRootElement: function () {
        var div = document.createElement("div");
        var img = document.createElement("img");
        div.appendChild(img);
        this.rootElement = div;
        this.imageElement = img
    },
    checkMotion: function () {
        switch (this.motion_type) {
        case mt_wander:
            this.motionWander();
            break;
        case mt_follow_ego:
            this.motionFollowEgo();
            break;
        case mt_move_obj:
            this.motionMoveObj();
            break
        }
        if (AGI.block && this.observe_blocks && this.direction)
            this.changePos()
    },
    motionWander: function () {
        if (!this.direction || this.DIDNT_MOVE)
            this.direction = Utils.Random(1, 8);
        if (this.isEgo())
            vars[Cr] = this.direction
    },
    motionFollowEgo: function () {
        this.step_size = Math.min(this.step_size, 1);
        var ego_x, ego_y;
        var obj_x, obj_y;
        var dir;
        var ego = getEgo();
        ego_x = Math.round(ego.x + ego.width() / 2);
        ego_y = ego.y;
        obj_x = Math.round(this.x + this.width() / 2);
        obj_y = this.y;
        dir = this.getDirection(obj_x, obj_y, ego_x, ego_y, this.parm1);
        if (dir == 0) {
            this.direction = 0;
            this.motion_type = mt_normal_motion;
            F(this.flag_to_set);
            this.flag_to_set = -1;
            return
        }
        if (this.parm3 == 255) {
            this.parm3 = 0
        } else if (this.DIDNT_MOVE) {
            this.direction = Utils.Random(1, 8);
            var d = (Math.abs(ego_y - obj_y) + Math.abs(ego_x - obj_x)) / 2 + 1;
            if (d <= this.step_size) {
                this.parm3 = this.step_size;
                return
            }
            do {
                this.parm3 = Utils.Random(0, d)
            }
            while (this.parm3 < this.step_size);
            return
        }
        if (this.parm3 != 0) {
            this.parm3 -= this.step_size
            if (this.parm3 < 0)
                this.parm3 = 0
        } else {
            this.direction = dir
        }
    },
    motionMoveObj: function () {
        this.direction = this.getDirection(this.x, this.y, this.destX, this.destY, this.step_size);
        if (this.isEgo())
            vars[Cr] = this.direction;
        if (this.direction == 0)
            this.inDestination()
    },
    changePos: function () {
        var b, x, y;
        var dx = [0, 0, 1, 1, 1, 0, -1, -1, -1];
        var dy = [0, -1, -1, 0, 1, 1, 1, 0, -1];
        var x = this.x;
        var y = this.y;
        var b = this.checkBlock(x, y);
        x += this.step_size * dx[this.direction];
        y += this.step_size * dy[this.direction];
        if (this.checkBlock(x, y) != b) {
            this.direction = 0;
            if (this.isEgo())
                vars[Cr] = 0
        }
    },
    isEgo: function () {
        return this.index == 0
    },
    getDirection: function (x0, y0, x, y, s) {
        var dir_table = [8, 1, 2, 7, 0, 3, 6, 5, 4];
        return dir_table[this.checkStep(x - x0, s) + 3 * this.checkStep(y - y0, s)]
    },
    checkStep: function (delta, step) {
        return (-step >= delta) ? 0 : (step <= delta) ? 2 : 1
    },
    inDestination: function () {
        if (this.flag_to_set > -1) {
            if (this.parm3 > 0) {
                this.step_size = this.parm3;
                this.parm3 = 0
            }
            F(this.flag_to_set);
            this.flag_to_set = -1
        }
        if (this.motion_type != mt_wander)
            this.motion_type = mt_normal_motion;
        if (this.isEgo())
            AGI.control = c_player_control
    },
    checkBlock: function (x, y) {
        if (x <= AGI.block.x1 || x >= AGI.block.x2)
            return false;
        if (y <= AGI.block.y1 || y >= AGI.block.y2)
            return false;
        return true
    },
    updateViewTableEntry: function () {
        var loop = 4;
        if (!this.FIX_LOOP) {
            switch (this.loopCount()) {
            case 2:
            case 3:
                loop = View.loop_table_2[this.direction];
                break;
            case 4:
                loop = View.loop_table_4[this.direction];
                break
            }
        }
        if (loop != 4 && loop != this.loop) {
            if (this.step_time_count == 1)
                this.loop = loop
        }
        if (!this.CYCLING)
            return;
        if (this.cycle_time_count == 0)
            return;
        if (--this.cycle_time_count == 0) {
            this.updateCel();
            this.cycle_time_count = this.cycle_time
        }
    },
    updateCel: function () {
        var cel = this.cel;
        var lastCel = this.celCount() - 1;
        switch (this.cycle_type) {
        case ct_normal_cycle:
            if (++cel > lastCel)
                cel = 0;
            break;
        case ct_end_of_loop:
            if (cel < lastCel) {
                if (++cel != lastCel)
                    break
            }
            if (this.flag_to_set > -1) {
                F(this.flag_to_set);
                this.flag_to_set = -1
            }
            this.CYCLING = false;
            this.direction = 0;
            this.cycle_type = ct_normal_cycle;
            break;
        case ct_reverse_loop:
            if (cel) {
                if (--cel)
                    break
            }
            if (this.flag_to_set > -1) {
                F(this.flag_to_set);
                this.flag_to_set = -1
            }
            this.CYCLING = false;
            this.direction = 0;
            this.cycle_type = ct_normal_cycle;
            break;
        case ct_reverse_cycle:
            if (cel == 0)
                cel = lastCel;
            else
                cel--;
            break
        }
        this.cel = cel
    },
    updatePosition: function () {
        var x, y, old_x, old_y, border;
        if (this.step_time_count != 0) {
            if (--this.step_time_count != 0)
                return
        }
        this.step_time_count = this.step_time;
        x = old_x = this.x;
        y = old_y = this.y;
        if (true || this.UPDATE_POS) {
            var dx = [0, 0, 1, 1, 1, 0, -1, -1, -1];
            var dy = [0, -1, -1, 0, 1, 1, 1, 0, -1];
            x += this.step_size * dx[this.direction];
            y += this.step_size * dy[this.direction]
        }
        border = 0;
        if (x < 0) {
            x = 0;
            border = 4
        } else if (x + this.width() > AGI.screen_width) {
            x = AGI.screen_width - this.width();
            border = 2
        }
        if (y - this.height() + 1 < 0) {
            y = this.height() - 1;
            border = 1
        } else if (y > AGI.screen_height - 1) {
            y = AGI.screen_height - 1;
            border = 3
        } else if (this.observe_horizon && y <= AGI.horizon) {
            y = AGI.horizon + 2;
            border = 1
        }
        this.x = x;
        this.y = y;
        if (!this.xyok()) {
            this.y = old_y;
            if (!this.xyok()) {
                this.x = old_x;
                this.y = y;
                if (!this.xyok()) {
                    this.y = old_y;
                    border = 0;
                    this.inDestination()
                }
            }
        }
        if (this.x == old_x && this.y == old_y) {
            if (this.didnt_move_count)
                this.direction = 0;
            else
                this.didnt_move_count++
        } else
            this.didnt_move_count = 0; if (border != 0) {
            if (this.isEgo()) {
                vars[Cm] = border
            } else {
                vars[Cp] = this.index;
                vars[Cq] = border
            }
            if (this.motion_type == mt_move_obj) {
                this.inDestination()
            }
        }
        this.UPDATE_POS = false
    },
    xyok: function () {
        return (!this.checkCollision() && this.checkPriority() && this.checkPosition())
    },
    fixPosition: function () {
        var count, dir, size;
        if (this.observe_horizon && this.y <= AGI.horizon) {
            this.y = AGI.horizon + 1
        }
        dir = 0;
        count = size = 1;
        while (!this.checkPosition()) {
            switch (dir) {
            case 0:
                this.x--;
                if (--count) continue;
                dir = 1;
                break;
            case 1:
                this.y++;
                if (--count) continue;
                dir = 2;
                size++;
                break;
            case 2:
                this.x++;
                if (--count) continue;
                dir = 3;
                break;
            case 3:
                this.y--;
                if (--count) continue;
                dir = 0;
                size++;
                break
            }
            count = size
        }
    },
    checkCollision: function () {
        if (!this.observe_objects)
            return false;

        function checkCollisionWithObject(obj1, obj2) {
            if (!obj2)
                return false;
            if (!obj2.ANIMATED || !obj2.isVisible() || !obj2.observe_objects)
                return false;
            if (obj1.index == obj2.index)
                return false;
            if (obj1.x + obj1.width() < obj2.x || obj1.x > obj2.x + obj2.width())
                return false;
            if (obj1.y == obj2.y)
                return true;
            return false
        }
        for (var i = 0; i <= AGI.highestObjIndex; i++) {
            var obj = objects[i];
            if (!obj || obj.index >= 100)
                continue;
            if (checkCollisionWithObject(this, obj))
                return true
        }
        return false
    },
    checkPosition: function () {
        if (this.x < 0 || this.x + this.width() > AGI.screen_width || this.y - this.height() + 1 < 0 || this.y >= AGI.screen_height || (this.observe_horizon && this.y <= AGI.horizon)) {
            return 0
        }
        return 1
    },
    checkPriority: function () {
        var i, trigger, water, pass, pri, w;
        if (!this.FIXED_PRIORITY) {
            this.priority = AGI.priorityTable[this.y]
        }
        trigger = 0;
        water = 0;
        pass = 1;
        if (this.priority != 15) {
            for (i = 0, w = this.width(); i < w; i++) {
                pri = AGI.getPriority(this.x + i, this.y) - 1;
                if (pri == 0) {
                    pass = 0;
                    break
                }
                if (pri == 3) {
                    water = 1;
                    continue
                }
                if (pri == 1) {
                    if (!this.observe_blocks)
                        continue;
                    pass = 0;
                    break
                }
                if (pri == 2)
                    trigger = 1
            }
            if (pass) {
                if (!water && this.ON_WATER)
                    pass = 0;
                if (water && this.ON_LAND)
                    pass = 0
            }
        }
        if (this.isEgo()) {
            flags[DR] = trigger ? true : false;
            flags[DO] = water ? true : false
        }
        return pass
    }
};