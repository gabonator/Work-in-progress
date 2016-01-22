'option strict';

module.exports = {pushLearnData:learn, getLearnData:getLearnData, getLearnRawData:getLearnRawData, sortLearnData:sortLearnData, setLearnData:setLearnData, optimizeLearnData:optimizeLearnData, reduceLearnData:reduceLearnData};

var learnData = [];

function learn(wave, chars)
{
  var result = tts.transcribe(wave, {});

  if ( result.length != chars.length )
  {
    console.log(result);
    console.log(chars);
    throw "transcribed letters count do not match provided chars";
  }

  for (var j = 0; j<chars.length; j++)
  {
    result[j].char = i.charAt(j);
    result[j].origin = chars;
    learnData.push(result[j]);
  }
}

function getLearnData()
{
  return JSON.stringify(learnData);
}

function getLearnRawData()
{
  return learnData;
}

function sortLearnData()
{
  learnData.sort(function(a, b){
    return a.char.charCodeAt(0) - b.char.charCodeAt(0);
  });
}

function setLearnData(d)
{
  learnData = d;
}

function reduceLearnData()
{
  sortLearnData();

  var learnDataOriginalSet = learnData;
  var learnDataReducedSet = [];

  var characters = {};
  for ( var i in learnDataOriginalSet )
    characters[learnDataOriginalSet[i].char] = 1;

  for ( var l in characters )
  {
    var character = l;
    var selected = [];
    for ( var i in learnDataOriginalSet )
    {
      if ( learnDataOriginalSet[i].char == character )
        selected.push(learnDataOriginalSet[i]);

    }

  //  console.log(JSON.stringify(selected));

    for ( var i=0; i<selected.length; i++)
    { 
      var sum = 0;
      for (var j=0; j<selected.length; j++)
        sum += distance(selected[i], selected[j]);

      selected[i].myDistance = sum;
    }

    var minDistanceI = 0;
    for ( var i=1; i<selected.length; i++)
      if ( selected[i].myDistance < selected[minDistanceI].myDistance )
      {
        minDistanceI = i; 
      }

    learnDataReducedSet.push(selected[minDistanceI]);
  }

  learnData = learnDataReducedSet;
}


function optimizeLearnData()
{
  sortLearnData();

  var learnDataOptimizedSet = [];
  var epsilon = 10;

  for ( var i in learnData )
  {
    // find collision
    
    var foundDuplicity = false;
    for ( var j in learnDataOptimizedSet )
    {
      if ( distance(learnData[i], learnDataOptimizedSet[j]) < epsilon && 
           learnData[i].char == learnDataOptimizedSet[j].char )
      {
//console.log("dupl");
        foundDuplicity = true;
        break;
      }       
    }
    if ( foundDuplicity )
      continue;

    learnDataOptimizedSet.push(learnData[i]);
  }
  console.log("optimizeLearnData reducet data set from " + learnData.length + " to "+learnDataOptimizedSet.length + " symbols");

  learnData = learnDataOptimizedSet;
}
