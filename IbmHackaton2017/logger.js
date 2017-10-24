module.exports = {mylog:mylog, datestamp:datestamp, timestamp:timestamp, hostname:hostname};

var fs = require("fs");
var dns = require("dns");

function datestamp()
{
  var d = new Date();
  return d.getFullYear() + "-" +
         ("0" + (1+d.getMonth())).substr(-2) + "-" +
         ("0" + d.getDate()).substr(-2);
}

function timestamp()
{
  var d = new Date();
  return datestamp() + " " +
         ("0" + d.getHours()).substr(-2) + ":" +
         ("0" + d.getMinutes()).substr(-2) + ":" +
         ("0" + d.getSeconds()).substr(-2);
}

function mylog(msg)
{
  if (typeof(msg) != "string")
    msg = JSON.stringify(msg);

  fs.appendFile("logs/"+datestamp()+".txt", msg + "\r\n", function (e) {if (e) console.log("Log error:" + e)});
}

function hostname(ip, handler)
{
  ip = ip.replace("::ffff:", "");

  dns.reverse(ip, function(err, domains) {
    if(err)
    {
      handler(ip);
      return;
    }
    var domain = domains[0];
 //   domain = domain.replace(".xxx.xxx", "");
    handler(domain);
  });
}