	var connected = false;
	var buffer = "";

	var host = "ws://localhost:5331/write_anything_here.php";
  window.onload = function() {
//		connect();
connected = true;
  };

	function message(m)
	{
		console.log(m);
	}


	function connect(){
			try{
				
				socket = new WebSocket(host);
				var in_string;
				message('Socket Status: '+socket.readyState);
				
				socket.onopen = function(){
					connected  = true;
					message('Socket Status: '+socket.readyState+' (open)');	
				}
				
				socket.onmessage = function(msg){	
				
					var in_string = new String(msg.data);
//console.log("RX:"+in_string.charCodeAt(2));
					buffer += in_string;
					while (1)
					{

					var eol_pos = buffer.indexOf("\r",0);
					if (eol_pos == -1)
						eol_pos = buffer.indexOf("\r",0);
					
					if( eol_pos != -1 ){
		
						var line = buffer.substr(0, eol_pos);
						if ( line.substr(0, 1) == "\r" || line.substr(0, 1) == "\n" )
							line = line.substr(1);

						buffer = buffer.substr(eol_pos+1);

					 wsrecv(line);
					} else 
						break;
				}
			
				}
				
				socket.onclose = function(){
					connected  = false;
					message('Socket Status: '+socket.readyState+' (Closed)');
					socket.close();
				}			
					
			} catch(exception){
				message('Error'+exception);
			}
			
		}
			
		function wssend(text)
    {
			try{
				socket.send(text);
			} catch(exception){
				message('Connection problem.');
			}			
		}

		