var fs = require('fs');

var syscall = 'dir *.wav /b';
var exec = require('child_process').exec;
                                        
exec(syscall, function(error, stdout, stderr) {
  var files = stdout.toString().split("\r\n");

  var q = "wave=[];\n";
  for ( var i in files )
  {
    var file = files[i];
    if ( file.length != 8 )
      continue;

    console.log(file);

    q += "wave['"+file+"']='";
    var data = fs.readFileSync(file, "binary");
    for (var i = 48; i < data.length-48-4; i++)
      q += ("0"+data.charCodeAt(i).toString(16)).substr(-2);

    q += "';\n";
  }

  fs.writeFile("wave.js", q, "binary");
});


