function Kick(context) {
  this.context = context;
};

Kick.prototype.setup = function() {
  this.osc = this.context.createOscillator();
  this.gain = this.context.createGain();
  this.osc.connect(this.gain);
  this.gain.connect(this.context.destination)
};

Kick.prototype.trigger = function(time) {
  this.setup();

  this.osc.frequency.setValueAtTime(250, time);
  this.gain.gain.setValueAtTime(1, time);

  this.osc.frequency.exponentialRampToValueAtTime(0.01, time + 0.5);
  this.gain.gain.exponentialRampToValueAtTime(0.01, time + 0.5);

  this.osc.start(time);

  this.osc.stop(time + 0.5);
};

function Snare(context) {
  this.context = context;
};

Snare.prototype.setup = function() {
  this.noise = this.context.createBufferSource();
  this.noise.buffer = this.noiseBuffer();

  var noiseFilter = this.context.createBiquadFilter();
  noiseFilter.type = 'highpass';
  noiseFilter.frequency.value = 1000;
  this.noise.connect(noiseFilter);

  this.noiseEnvelope = this.context.createGain();
  noiseFilter.connect(this.noiseEnvelope);

  this.noiseEnvelope.connect(this.context.destination);

  this.osc = this.context.createOscillator();
  this.osc.type = 'triangle';

  this.oscEnvelope = this.context.createGain();
  this.osc.connect(this.oscEnvelope);
  this.oscEnvelope.connect(this.context.destination);
};

Snare.prototype.noiseBuffer = function() {
  var bufferSize = this.context.sampleRate;
  var buffer = this.context.createBuffer(1, bufferSize, this.context.sampleRate);
  var output = buffer.getChannelData(0);

  for (var i = 0; i < bufferSize; i++) {
    output[i] = Math.random() * 2 - 1;
  }

  return buffer;
};

Snare.prototype.trigger = function(time) {
  this.setup();

  this.noiseEnvelope.gain.setValueAtTime(1, time);
  this.noiseEnvelope.gain.exponentialRampToValueAtTime(0.01, time + 0.2);
  this.noise.start(time)

  this.osc.frequency.setValueAtTime(100, time);
  this.oscEnvelope.gain.setValueAtTime(0.7, time);
  this.oscEnvelope.gain.exponentialRampToValueAtTime(0.01, time + 0.1);
  this.osc.start(time)

  this.osc.stop(time + 0.2);
  this.noise.stop(time + 0.2);
};


function HiHat(context)
{
  this.context = context;
}

HiHat.prototype.setup = function() {
  this.gain = this.context.createGain();

  // Bandpass
  this.bandpass = this.context.createBiquadFilter();
//  this.bandpass = this.gain;
  this.bandpass.type = "bandpass";
  this.bandpass.frequency.value = 10000;

  // Highpass
  this.highpass = this.context.createBiquadFilter();
  this.highpass.type = "highpass";
  this.highpass.frequency.value = 7000;

  // Connect the graph
  this.bandpass.connect(this.highpass);
  this.highpass.connect(this.gain);
  this.gain.connect(this.context.destination);
}

HiHat.prototype.trigger = function(when) {
  var fundamental = 40;
  var ratios = [2, 3, 4.16, 5.43, 6.79, 8.21];

  this.setup();


  ratios.forEach((function(ratio) {
    var osc = this.context.createOscillator();
    osc.type = "square";
    // Frequency is the fundamental * this oscillator's ratio
    osc.frequency.value = fundamental * ratio;
    osc.connect(this.bandpass);
    osc.start(when);
    osc.stop(when + 0.3);
  }).bind(this));

  this.gain.gain.setValueAtTime(0.00001, when);
  this.gain.gain.exponentialRampToValueAtTime(1, when + 0.02);
  this.gain.gain.exponentialRampToValueAtTime(0.3, when + 0.03);
  this.gain.gain.exponentialRampToValueAtTime(0.00001, when + 0.3);
};

function Voice(context, url, handler) {
	this.context = context;
        this.handler = handler;
        this.load(context, url);
//	this.buffer = buffer;
};

Voice.prototype.setup = function() {
	this.source = this.context.createBufferSource();
	this.source.buffer = this.buffer;
        this.source.playbackRate.value = Math.pow(2, 1/12);
	this.source.connect(this.context.destination);
};

Voice.prototype.toneToTime = function(ch, ofs)
{
  if (ch.length == 1)
    ch += "-";

  var tones = "C-C#D-D#E-F-F#G-G#A-A#B-" + "c-c#d-d#e-f-f#g-g#a-a#b-";
  var tone = tones.indexOf(ch)/2;
  tone += ofs ? ofs : 0;
  return Math.pow(2, (tone-12)/12);
}

Voice.prototype.trigger = function(time, tone, part) {
	this.setup();               
	if (part==".") // now
        {
  	  this.source.start(time, 1.0);
          this.source.stop(time + 0.29);
        }
	if (part=="1") // happy
        {
  	  this.source.start(time, 0.56);
          this.source.stop(time + 0.75 - 0.56 - 0.015);
        }
	if (part=="2") // happy now
        {
  	  this.source.start(time, 0.56);
          this.source.stop(time + 0.7);
        }
	if (part=="3") // you are happy
        {
  	  this.source.start(time, 0.150);
          this.source.stop(time + 0.77-0.150 - 0.02);
        }
	if (part=="8") // bass
        {
  	  this.source.start(time, 0.150 + 0.01);
          this.source.stop(time + 0.100 + 0.0495);
  	  this.source.playbackRate.value = this.toneToTime(tone, -12);
  	  return;
        }
	if (part=="9") // all
        {
  	  this.source.start(time, 0.0);
  	  return;
        }

	this.source.playbackRate.value = this.toneToTime(tone);
};

Voice.prototype.load = function(context, url)
{
  var request = new XMLHttpRequest();
  request.open('get', url, true);
  request.responseType = 'arraybuffer';
  request.onload = (function() {
    context.decodeAudioData(request.response, (function(buffer) {
      this.buffer = buffer;
      this.handler();
    }).bind(this));
  }).bind(this);
  request.send();
}


var patterns = 
[ {
  bassdrum: "*... *... *... *...",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..C. ..C. ..C. ..C.",
}, {
  bassdrum: "*... *... *... *..*",
  hihat:    "*.*. *.*. *.*. *.*.",
  voice:    "..D. ..D. ..D. ..D.",
}, {
  bassdrum: "*... *... *... *...",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..A. ..A. ..A. ..A.",
}, {
  bassdrum: "*... *... *... *...",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..G. ..G. ..G. ..G.",
},
// add cl hihat
 {
  bassdrum: "*... *... *... *...",
  snare:    "...* ..*. .*.* ..*.",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..C. ..C. ..C. ..C.",
}, {
  bassdrum: "*... *... *... *..*",
  snare:    "...* ..*. .*.* ..*.",
  hihat:    "*.*. *.*. *.*. *.*.",
  voice:    "..D. ..D. ..D. ..D.",
}, {
  bassdrum: "*... *... *... *...",
  snare:    "...* ..*. .*.* ..*.",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..F. ..F. ..F. ..F.",
}, {
  bassdrum: "*... *... *... *...",
  snare:    "...* ..*. *.*. *...",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..F. ..F. ..F. ..F.",
},
// happy
 {
  bassdrum: "*... *... *... *...",
  snare:    "...* ..*. .*.* ..*.",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..C. ..C. ..C. ..C.",
  voice1:   "c... .... c... ....",
}, {
  bassdrum: "*... *... *... *..*",
  snare:    "...* ..*. .*.* ..*.",
  hihat:    "*.*. *.*. *.*. *.*.",
  voice:    "..D. ..D. ..D. ..D.",
  voice1:   "c... .... c2.. ....",
}, {
  bassdrum: "*... *... *... *...",
  snare:    "...* ..*. .*.* ..*.",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..F. ..F. ..F. ..F.",
  voice1:   "c... .... c... ....",
}, {
  bassdrum: "*... *... *... *...",
  snare:    "...* ..*. *.*. *...",
  hihat:    "*.*. *.*. **** *.*.",
  voice:    "..F. ..F. ..F. ..F.",
  voice1:   "c... .... c2.. ....",
}];

var patterns = 
[
 {
  bassdrum: "*... *... *... *...",
  voice1:   "c... .... c2.. ....",
},{
  bassdrum: "*... *... *... *...",
  voice1:   "c3.. .... c2.. ....",
},
 {
  bassdrum: "*... *... *... *...",
  hihat:    "..*. ..*. ..** ..*.",
  voice1:   "c... .... c2.. ....",
},{
  bassdrum: "*... *... *... *...",
  hihat:    "..*. ..*. ..** ..*.",
  voice1:   "c3.. .... c2.. ....",
},
 {
  bassdrum: "*... *... *... *...",
  hihat:    "..*. ..*. ..** ..*.",
  voice1:   "c... .... c2.. ....",
  bass:      "..c. ..c. ..c. ..c.",
},{
  bassdrum: "*... *... *... *...",
  hihat:    "..*. ..*. ..** ..*.",
  voice1:   "c3.. .... c2.. ....",
//  bass:     "..G- ..G# ..A- ..C-",
  bass:      "..c. ..c. ..c. ..c.",
},
,{
  bassdrum: "*... *... *... *...",
  hihat:    "..*. ..*. ..** ..*.",
  voice1:   "c3.. .... c2.. ....",
  bass:     "..c. ..c. ..c. ..c.",
},{
  all:      "c... .... .... ....",
}];

/*
var patterns = 
[
{  bass:      "..c. ..c. ..c. ..c."}
] */

var speech = "You are happy now! Thank you for supporting good guys!";
var happySongSpeechUrl = "/speech?"+encodeURIComponent(speech);

function playHappySong()
{

  window.AudioContext = window.AudioContext || window.webkitAudioContext;

  var context = new AudioContext();

  var kick = new Kick(context);
  var snare = new Snare(context);
  var hihat = new HiHat(context);
  var voice = new Voice(context, happySongSpeechUrl, onFinish);

  var tempo = 120;
  var pertick = 60 / tempo / 4;
  var tick = 0;

  function onFinish()
  {
    var now = context.currentTime;

    for (var pattern in patterns)
    {
      for (var instrument in patterns[pattern])
      {
        var pat = patterns[pattern][instrument].split(" ").join("");
        for (var i=0; i<pat.length; i++)
          if (pat[i] != ".")
          {
            if (instrument == "bassdrum")
              kick.trigger(now + (tick+i)*pertick);
            if (instrument == "snare")
              snare.trigger(now + (tick+i)*pertick);
            if (instrument == "hihat")
              hihat.trigger(now + (tick+i)*pertick);
            if (instrument == "voice")
              voice.trigger(now + (tick+i)*pertick, pat[i], pat[i+1]);
            if (instrument == "voice1" && "0123456789".indexOf(pat[i]) == -1 )
              voice.trigger(now + (tick+i)*pertick, pat[i], pat[i+1] == "." ? "1" : pat[i+1]);
            if (instrument == "bass" && "cdefgabCDEFGAB".indexOf(pat[i]) != -1)
              voice.trigger(now + (tick+i)*pertick, pat[i] + pat[i+1], '8');
            if (instrument == "all")
              voice.trigger(now + (tick+i)*pertick, pat[i], '9');
          }  
      }
      tick += 16;
    }
  }
}
