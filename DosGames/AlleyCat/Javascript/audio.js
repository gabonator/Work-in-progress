// valky.eu 2013, three channel audio generator

var GTone = {
  Play: function(freq, dur)
  {
		if ( typeof(this.ac) == "undefined" )
		{
			if ( window.AudioContext )
				this.ac = new AudioContext();
			else if ( window.webkitAudioContext )
				this.ac = new webkitAudioContext();
		 	var osc = this.ac.createOscillator();
			this.hasNote = osc.noteOn ? true : false;

    }
    Stop();

	 	this.osc = this.ac.createOscillator();
		this.osc.type = "square";
		this.osc.frequency.value = freq;
		this.osc.connect(this.ac.destination);

    var _this = this;
		this.timeout = setTimeout( function() { _this.Stop(); }, dur );
  },
  Stop: function()
  {
    if ( this.timeout )
      clearTimeout( this.timeout );
    if ( this.osc )
      this.osc.disconnect();
  }
};

var GAudio = {
	flavour:"sine",
	volume:1,
	garbage:[],
	attack:[],
	release:[],

	hasNote:true,
	hasGain:true,
	hasFf:false,

  Start: function()
  {
		if ( typeof(this.ac) == "undefined" )
		{
			if ( window.AudioContext )
				this.ac = new AudioContext();
			else if ( window.webkitAudioContext )
				this.ac = new webkitAudioContext();

			this.hasGain = this.ac.createGainNode ? true : false;
		 	var osc = this.ac.createOscillator();
			this.hasNote = osc.noteOn ? true : false;
			this.hasFf = navigator.userAgent.indexOf("Firefox") != -1;
		}
		this.osc = [];
		if ( this.hasFf )
		{
			this.osc = [ this.createOsc(), this.createOsc(), this.createOsc() ];
			for ( var o in this.osc )
			{
				this.osc[o].frequency.value = 0;
				this.hasNote ? this.osc[o].noteOn(0) : this.osc[o].start(0);
			}
		}
  },
  Stop: function()
  {
		console.log("Stopping");
		if ( this.hasFf )
			for ( o in this.osc )
			{ 
				this.release[o] = this.osc[o];	
				this.osc[o] = false;
			}

		for ( o in this.osc )
			if (this.osc[o])
				this.NoteOff( o );

		for ( o in this.release )
		{
			if (!this.release[o])
				continue;
			this.hasNote ? this.release[o].noteOff(0) : this.release[o].stop(0);
			this.release[o].disconnect();
		}
	 	this.osc = [];
  },
  NoteOn: function(ch, note)
  {
		if ( this.hasFf )
		{
			var osc = this.osc[ch];
			osc.frequency.value = this.freq(note);		
			return;
		}
		this.osc[ch] = this.createOsc();
		var osc = this.osc[ch];
		osc.frequency.value = this.freq(note);
		this.hasNote ? osc.noteOn(0) : osc.start(0);

		if ( this.hasGain )
			this.attack[ch] = true;
  },
  NoteOff: function(ch)
  {
		if ( this.hasFf )
		{
			var osc = this.osc[ch];
			osc.frequency.value = 0;
			return;
		}
		if ( !this.osc[ch] )
			return;
		if ( this.hasGain )
		{
			if ( this.release[ch] )
			{
  			this.hasNote ? this.release[ch].noteOff(0) : this.release[ch].stop(0);
  			gen.disconnect();
  			this.release[ch] = false;
			}

			// keep playing, move to release garbage
			this.release[ch] = this.osc[ch];
			if ( this.osc[ch].gain )
				this.release[ch].gain.gain.value = 0;
		} else {
			this.hasNote ? this.osc[ch].noteOff(0) : this.osc[ch].stop(0);
			this.osc[ch].disconnect();
		}
		this.osc[ch] = false;
  },
	Tick: function()
	{
		if ( !this.hasGain )
			return;

		for ( ch in this.attack )
			if (this.attack[ch])
			{
				if ( this.osc[ch].gain )
  				this.osc[ch].gain.gain.value = this.volume;
				this.attack[ch] = false;
			}		
		for ( ch in this.release )
  		if ( this.release[ch] )
  		{
				var gen = this.release[ch];
  			this.hasNote ? gen.noteOff(0) : gen.stop(0);
  			gen.disconnect();
  			this.release[ch] = false;
  		}

	},
// private
  createOsc: function()
  {
	 	var osc = this.ac.createOscillator();
		osc.type = this.flavour;
		osc.frequency.value = 0;

		if ( this.hasGain )
		{
			osc.gain = this.ac.createGainNode();
			osc.gain.gain.value = 0;
			osc.connect(osc.gain);
			osc.gain.connect(this.ac.destination);
		}	else
		{
			osc.gain = false;
			osc.connect(this.ac.destination);
		}
		return osc;
  },
	freq: function(note)
	{
		return (440 / 32) * Math.pow(2, ((note - 9 + 12) / 12));
	}
};
