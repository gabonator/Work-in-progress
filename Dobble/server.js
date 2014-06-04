var http = require("http")
var ws = require("nodejs-websocket")
var fs = require("fs")

http.createServer(function (req, res) {
	fs.createReadStream("net.html").pipe(res)
}).listen(8080)

var server = ws.createServer(function (connection) {
	connection.id = null;

	connection.on("text", function (str) {
	  console.log(connection.id + ": " +str);

		if (connection.id === null) {
			connection.id = str;
			addPlayer(str);
			somethingHasChanged();
//			broadcastExcept(str+"|entered", connection.id)
		} else
    {  
      if ( str == "ping" )
      {
      } else
      if ( str == "request-stacking" )
      {
        doRequestStacking(connection.id);
      } else
      {
//  			broadcastExcept(connection.id+"|"+str, connection.id)
      }
    }
	})

	connection.on("close", function () {
		removePlayer(connection.id);
		somethingHasChanged();
//		broadcast(connection.id+" left")
	})
})
server.listen(8081)

function somethingHasChanged()
{
  var clients = "";
	server.connections.forEach(function (connection) {
    if ( clients != "" )
      clients += ", ";
    clients += "'"+connection.id+"'";
  });

   
  broadcast("_setUsers(["+clients+"])");
  broadcast("_setData("+JSON.stringify(players)+")");
  broadcast("_setStack("+JSON.stringify(cardStack)+");");

  console.log("Players="+JSON.stringify(players));
  console.log("Stack="+JSON.stringify(cardStack));
}

function broadcast(str) {
	server.connections.forEach(function (connection) {
		connection.sendText(str)
	})
}
function broadcastExcept(str, id) {
	server.connections.forEach(function (connection) {
    if ( connection.id != id )
  		connection.sendText(str)
	})
}

/*
setInterval( function()
{
  var clients = "";
	server.connections.forEach(function (connection) {
    if ( clients != "" )
      clients += ", ";
    clients += "'"+connection.id+"'";
  });
  broadcast("_setUsers(["+clients+"])");
  broadcast("_setData("+JSON.stringify(players)+")");
  broadcast("_setStack(["+smallStack[smallStack.length-1]+", "+smallStack[smallStack.length-2]+"]);");
}, 1000);
*/

// gameplay

function doRequestStacking(id)
{
  broadcastExcept("_giveCard('"+id+"')", id);
  findPlayer(id).topCard = takeLastCard();
  findPlayer(id).score++;
  somethingHasChanged();
}

// players
var players = [];
function addPlayer(id)
{
  players[players.length] = {id:id, topCard:takeFirstCard(), score:0};
}
function removePlayer(id)
{
  for (var i=0; i<players.length; i++)
  { 
    if (players[i].id == id)
    {
		  players.splice(i, 1);
      console.log("player removed");
      return;
    }
  }  
  console.log("cannot remove player!");
}
function findPlayer(id)
{
  for (var i=0; i<players.length; i++)
    if (players[i].id == id)
      return players[i];
}

// stack
var cardStack = shuffle(buildStack());
function takeLastCard()
{
  return cardStack.pop();
}                
                 
function takeFirstCard()
{
  return cardStack.splice(0, 1)[0];
}

// utils
function buildStack()
{
  var s = [];
  for (var i=1; i<=54; i++)
    s.push(i);
  return s;
}

function shuffle(array) {
  var currentIndex = array.length
    , temporaryValue
    , randomIndex
    ;

  // While there remain elements to shuffle...
  while (0 !== currentIndex) {

    // Pick a remaining element...
    randomIndex = Math.floor(Math.random() * currentIndex);
    currentIndex -= 1;

    // And swap it with the current element.
    temporaryValue = array[currentIndex];
    array[currentIndex] = array[randomIndex];
    array[randomIndex] = temporaryValue;
  }

  return array;
}

//var smallStack = [takeCard(), takeCard()];