// valky.eu 2013, AGI tune player

var playofs = [0, 0, 0];
var time = 0;
var melody = [];
var _tid = false;
var playing = false;
var lastsound = -1;
var playingdly = true;

function _gaboPlay(n, x)
{
	if ( playing && lastsound == n )
	{
		console.log("Already playing!");
		return;
	}
	console.log("Play sound: " +n + "("+x+")");
	lastsound = n;
	Sarien.loadResource(Sarien.path + "/sound" + n + ".js");
	playerStart(window["sound"+n]);
}
function _gaboStop()
{
	playerStop();
}

function timer()
{
	GAudio.Tick();
	if ( time == 0 )
		for (var t in melody)
		{
			if ( melody[t][0] > 0 )
				GAudio.NoteOn(t, melody[t][0]);
			playofs[t] = 1;
		}
	time++;
	var playing = false;
	for (var t in melody)
	{
		var trk = melody[t];
		if ( playofs[t] < 0 )
			continue;

		if ( time == trk[playofs[t]] )
		{                   
			GAudio.NoteOff(t);
			if ( playofs[t]+1 >= trk.length )
			{
				playofs[t] = -1;
				continue;
			}
			playing = true;
			if ( trk[playofs[t]+1] > 0 )	
				GAudio.NoteOn(t, trk[playofs[t]+1]);
			playofs[t] += 2;
		} else
			playing = true;
	}
	if (!playingdly)
	{
		// delay one tick
		console.log("finished!");
		playerStop();
	}
	playingdly = playing;
}

function calculate()
{
	for (var j in melody)
	{
		var time = 0;
		for ( var i=1; i<melody[j].length; i+=2)
		{
			time += melody[j][i];
			melody[j][i] = time;
		}
	}
}

function playerStop()
{
	if ( _tid )
	{
		playing = false;
		clearInterval(_tid);
	  GAudio.Stop();
		_tid = false;
	}
}

function playerStart(m)
{
	playerStop();
	playing = true;
	playingdly = true;
	melody = m;
	playofs = [0, 0, 0];
	time = 0;
	calculate();
	if ( melody[0][0] < 36 )
	{
		GAudio.flavour = "sine";		// sfx
		GAudio.volume = 0.3;
	}
	else
	{
		GAudio.flavour = "sine";			// melody
		GAudio.volume = 1;
	}
	GAudio.Start();
	_tid = setInterval("timer()", 18);
}

