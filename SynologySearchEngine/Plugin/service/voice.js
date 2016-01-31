'option strict';

module.exports = {captchaByVoice:captchaByVoice};

var transcribe = require('./transcribe.js').transcribe;
var matcher = require('./matcher.js').matcher;

function captchaByVoice(wave)
{
  var q = (new Buffer(wave, 'binary')).toString('hex');
  q = q.substr(48*2, (wave.length-48-4)*2);
  return matcher(transcribe(q, {}));
}