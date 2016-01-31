'option strict';

module.exports = {transcribe:mainTranscribe, process:mainProcess, _getWave:hex2samples};

function mainTranscribe(hexWave, _debug)
{
  var wave = hex2samples(hexWave);
  var waveMax = getMax(wave);
  _debug.signalMax = waveMax;
  _debug.waveSource = wave;
  _debug.source = wave;
  _debug.waveLp = lowPass(wave);
  _debug.waveHp = highPass(wave);
  _debug.waveRe = rectify(wave);
  _debug.envelopeLp = envelope(_debug.waveLp);
  _debug.envelopeHp = envelope(_debug.waveHp);
  _debug.triggerLp = fillGap(trigger(_debug.envelopeLp, 0.30*waveMax, 0.25*waveMax), 550);
  _debug.triggerHp = fillGap(triggerComp(_debug.envelopeHp, _debug.envelopeLp, 0.20*waveMax), 140);
  _debug.triggerRe = fillGap(trigger(_debug.waveRe, 0.4*waveMax, 0.3*waveMax), 100); //fillGap(trigger(_debug.waveSource, 0.30*waveMax, 0.25*waveMax), 550);

  _debug.trigger = fillGap(logicSum(logicSum(_debug.triggerLp, _debug.triggerHp), _debug.triggerRe), 400);

  _debug.fun = calcFreq(_debug.waveLp, waveMax*0.3);

  if ( 1 )
  {
    _debug.envelopeLp = downsample32x(_debug.envelopeLp);
    _debug.envelopeHp = downsample32x(_debug.envelopeHp);
    _debug.triggerLp = downsample32x(_debug.triggerLp);
    _debug.triggerHp = downsample32x(_debug.triggerHp);
    _debug.triggerRe = skip32x(_debug.triggerRe);
    _debug.waveLp = skip32x(_debug.waveLp);
    _debug.waveHp = skip32x(_debug.waveHp);
    _debug.waveRe = skip32x(_debug.waveRe);
    _debug.source = skip32x(_debug.source);
    _debug.trigger = skip32x(_debug.trigger);
    _debug.fun = skip32x(_debug.fun);
  }
  if ( 1 )
  {
    _debug.envelopeLp = average(_debug.envelopeLp, waveMax/4);
    _debug.envelopeHp = average(_debug.envelopeHp, waveMax/4);
    _debug.fun = average(_debug.fun, waveMax/4);
  }

  var intervals = getIntervals(_debug.trigger, _debug.triggerLp, _debug.triggerHp, _debug.triggerRe);
  for ( var i in intervals )
    processInterval(intervals[i], _debug.envelopeLp, _debug.envelopeHp, _debug.fun, waveMax);

  return encodeIntervals(intervals); //getResult(process(wave, _debug));
}

function mainProcess(hexWave, _debug)
{
  return {}; //process(hex2samples(hexWave), _debug);
}

function encodeInterval(interval)
{
  return {char:'?', len:interval.total, llp:interval.lenLow, lhp:interval.lenHigh, lsi:interval.lenSilent, lno:interval.lenNoise,
    avglp:Math.floor(interval.stats.all.lp.avg*100),
    siglp:Math.floor(interval.stats.all.lp.sig*100),
    avghp:Math.floor(interval.stats.all.hp.avg*100),
    sighp:Math.floor(interval.stats.all.hp.sig*100),

    avglp1:Math.floor(interval.stats.begin.lp.avg*100),
    siglp1:Math.floor(interval.stats.begin.lp.sig*100),
    avghp1:Math.floor(interval.stats.begin.hp.avg*100),
    sighp1:Math.floor(interval.stats.begin.hp.sig*100),

    avglp2:Math.floor(interval.stats.end.lp.avg*100),
    siglp2:Math.floor(interval.stats.end.lp.sig*100),
    avghp2:Math.floor(interval.stats.end.hp.avg*100),
    sighp2:Math.floor(interval.stats.end.hp.sig*100),

    avgpe:Math.floor(interval.stats.all.pe.avg*100),
    avgpe1:Math.floor(interval.stats.begin.pe.avg*100),
    avgpe2:Math.floor(interval.stats.end.pe.avg*100)

  };
}

function encodeIntervals(intervals)
{
  var q = [];
  for (var i in intervals)
    q.push(encodeInterval(intervals[i]));
  return q;
}

function getIntervalWaveStats(begin, end, wave, wavemax)
{
  var wsum = 0, wmin = wave[begin], wmax = wave[begin];
  for (var i=begin; i<end; i++)
  {
    var cur = wave[i];
    wmax = Math.max(wmax, cur);
    wmin = Math.min(wmin, cur);
    wsum += cur;
  }
  wsum /= end-begin;
  return {avg:wsum, sig:(wmax-wmin)/wavemax, max:wmax, min:wmin};
}

function getIntervalStats(begin, end, envLp, envHp, envPe, wmax)
{
  return {
    lp:getIntervalWaveStats(begin, end, envLp, wmax),
    hp:getIntervalWaveStats(begin, end, envHp, wmax),
    pe:getIntervalWaveStats(begin, end, envPe, wmax)
  };
}

function processInterval(interval, envLp, envHp, envPe, wmax)
{
  var l = interval.total, b = interval.begin;
  interval.stats = {
    begin:getIntervalStats(Math.floor(b + l*0.1), Math.floor(b+l*0.3), envLp, envHp, envPe, wmax),
    all:getIntervalStats(Math.floor(b + l*0.1), Math.floor(b+l*0.9), envLp, envHp, envPe, wmax),
    end:getIntervalStats(Math.floor(b + l*0.7), Math.floor(b+l*0.9), envLp, envHp, envPe, wmax)
  };
}

function getIntervals(trigger, triggerLp, triggerHp, triggerRe)
{
  var intervals = [];
  for (var i=0; i<trigger.length; i++)
  {
    if ( trigger[i] == 1 )
    {  
      var lenLow = 0, lenHigh = 0, lenSilent = 0, lenNoise = 0;
      for (var j=i; j<trigger.length; j++)
      {
        if ( triggerLp[j] == 1 )
          lenLow++;
        if ( triggerHp[j] == 1 )
          lenHigh++;
        if ( triggerHp[j] == 0 && triggerLp[j] == 0 && triggerRe[j] == 0 )
          lenSilent++;
        if ( triggerHp[j] == 0 && triggerLp[j] == 0 && triggerRe[j] == 1 )
          lenNoise++;

        if ( trigger[j] == 0 )
          break;
      }
      var lenTotal = j - i;
      if ( lenLow + lenHigh > 0 )
        intervals.push({begin:i, end:j, total:lenTotal, lenLow:lenLow, lenHigh:lenHigh, lenSilent:lenSilent, lenNoise:lenNoise});
      i = j;
    }
  }
  return intervals;  
}

function rectify(wave)
{
  var arrRectified = new Array(wave.length);
  for (var i = 0; i<wave.length; i++)
    arrRectified[i] = Math.abs(wave[i]);
  return arrRectified;

}

function calcFreq(wave, thresh)
{
  var arrFreq = new Array(wave.length);
  var freq = 0;
  var phase = -1;

  thresh /= 2;

  for (var i = 0; i<wave.length; i++)
  { 
    var cur = wave[i];

    var newphase = 0;
    if ( cur > thresh )
      newphase = 1;
    if ( cur < -thresh )
      newphase = -1;
 
    if ( phase == 1 && newphase == -1 )
      freq+=0.1;   
    if ( phase == -1 && newphase == 1 )
      freq+=0.1;   

    if (newphase != 0)
      phase = newphase;                

    if ( freq > 0 )
      freq *= 0.99;
    if ( freq > 1 )
      freq = 1;	
    arrFreq[i] = freq;
  }
  return arrFreq;

}

function average(wave, q, d)
{
  var arrQuant = new Array(wave.length);
  var filter = [0.1, 0.3, 0.4, 0.7, 1.0, 0.7, 0.4, 0.3, 0.1];
  
  var sum = 0;
  for (var i in filter) sum += filter[i];
  sum = 1/sum;
  
  for (var i=5; i<arrQuant.length-5; i++)
    arrQuant[i] = (wave[i-4]*filter[0] + wave[i-3]*filter[1] + wave[i-2]*filter[2] + wave[i-1]*filter[3] + 
      wave[i]*filter[4] + wave[i+1]*filter[5] + wave[i+2]*filter[6] + wave[i+3]*filter[7] + wave[i+4]*filter[8])*sum;

  return arrQuant;
}

function logicSum(wave1, wave2)
{
  var arrSum = new Array(Math.min(wave1.length, wave2.length));
  for (var i=0; i<arrSum.length; i++)
    arrSum[i] = Math.min(1, wave1[i] + wave2[i]);
  return arrSum;
}

function downsample32x(wave)
{
  return downsample(downsample(downsample(downsample(downsample(wave)))));
}

function skip32x(wave)
{
  var arrSkip = new Array(Math.floor(wave.length/32));
  for (var i = 0, j = 0; i < arrSkip.length; i++, j+=32)
    arrSkip[i] = wave[j];
  return arrSkip;
}

function getMax(wave)
{
  var waveMax = 0;
  for (var i = 0; i<wave.length; i++)
    waveMax = Math.max(waveMax, Math.abs(wave[i]));
  return waveMax;
}

function envelope(wave)
{
  var arrEnvelope = new Array(wave.length);
  var tEnvelope = 0;

  for (var i =0; i<wave.length; i++)
  {
    var cur = Math.abs(wave[i]);

    if ( cur > tEnvelope )
      tEnvelope = tEnvelope * 0.80 + cur * 0.2;
    else
      tEnvelope *= 0.995;

    arrEnvelope[i] = tEnvelope;
  }
  return arrEnvelope;
}

function triggerComp(wave, waveCompare, dist)
{
  var arrTrigger = new Array(wave.length);
  var tTrigger = 0;
                                                 
  for (var i=0; i<wave.length; i++)
  {
    var cur = wave[i];
    var com = waveCompare[i];

    if (cur > com + dist)
      tTrigger = 1;
    if (cur < com + dist * 0.9)
      tTrigger = 0;

    arrTrigger[i] = tTrigger;
  }
  return arrTrigger;
}

function trigger(wave, low, high)
{
  var arrTrigger = new Array(wave.length);
  var tTrigger = 0;
                                                 
  for (var i=0; i<wave.length; i++)
  {
    var cur = wave[i];

    if (cur > high)
      tTrigger = 1;
    if (cur < low)
      tTrigger = 0;

    arrTrigger[i] = tTrigger;
  }
  return arrTrigger;
}

function fillGap(wave, gapSize)
{
  // expand
  var dead = 0;
  for (var i=wave.length-1; i > 0; i--)
  {
    var cur = wave[i];
    if ( cur == 1 ) 
      dead = gapSize;

    if ( dead > 0 )
      wave[i] = 1;

    dead--;
  }

  dead = Math.max(0, dead);

  // reduce
  var prev = 0;
  for (var i=0; i<wave.length; i++)
  {
    var cur = wave[i];
    if ( prev == 0 && cur == 1 )
    {
      for (var j=i; j<i+gapSize-dead; j++)
        wave[j] = 0;
      dead = 0;
      i = j;
    }
    prev = cur;
  }

  // kill noise
  for (var i=0; i<wave.length; i++)
  {
    if ( wave[i] == 1 )
    {
      for (var j=i; j<wave.length; j++)
        if ( wave[j] == 0 )
          break;

      var len = j - i;
      if ( len < gapSize )
        for ( var k=i; k<j; k++)
          wave[k] = 0;

      i = j;
    }
    prev = cur;
  }
  

  return wave;
}

function lowPass(arr)
{
  arr = downsample(downsample(downsample(arr)));
  arr = upsample(upsample(upsample(arr)));
  return arr;
}

function downsample(arr)
{
  var arrNew = new Array(Math.floor(arr.length/2));
  for ( var i=0, j=0; i < arrNew.length; i++, j+=2)
    arrNew[i] = (arr[j] + arr[j+1])/2;
  return arrNew;
}

function upsample(arr)
{
  var arrNew = new Array(Math.floor(arr.length*2));
  for ( var i=0, j=0; i < arrNew.length-1; i+=2, j++)
  {
    arrNew[i] = arr[j];
    arrNew[i+1] = (arr[j] + arr[j+1])/2;
  }
  arrNew[arrNew.length-1] = arrNew[arrNew.length-2];
  return arrNew;
}

function highPass(arr)
{
  var arrNew = new Array(arr.length);
  for ( var i=0; i < arrNew.length-1; i++)
    arrNew[i] = (arr[i] - arr[i+1])/2;

  arrNew[arrNew.length-1] = 0;

  return arrNew;
}

function getResult(sequence)
{
  var result = "";
  for (var i in sequence)
    result += sequence[i].symbol;
  return result;
}

function hex2samples(string)
{
  var t = new Array(Math.floor(string.length/2));
  for (var i=0; i<string.length/2; i++)
  {
    var val = ("0x"+string[i*2]+string[i*2+1])*1;
    t[i] = (val-128)/128;
  }
  return t;
}
