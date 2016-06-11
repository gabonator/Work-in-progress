<? 
  if ( $_SERVER["QUERY_STRING"] == "login" )
	{                                        
		if ( !isset($_SERVER['PHP_AUTH_USER']) || !isUserValid() )
		{	
    	header('WWW-Authenticate: Basic realm="Enter login for blood measurements database access"');
    	header('HTTP/1.0 401 Unauthorized');
	    echo "<script language=\"javascript\">location.href=\"?\";</script>";
	    exit;
		}
	}

	$user = "guest";
	if ( isUserValid() )
	{
		$user = "admin";
	}

	function isUserValid()
	{
		// set your account settings here!
  	return ( $_SERVER['PHP_AUTH_USER'] == "login" && $_SERVER['PHP_AUTH_PW'] == "password" );
	}

  if ( $_GET["add"] )                            
  {
    @$records = json_decode(file_get_contents("db/records.js"),true);
    @$users = json_decode(file_get_contents("db/users.js"),true);
    $uid = 0;
	  if ( is_array($records) )
		{
			$uid = $records[sizeof($records)-1]["nUid"];
			if (isset($uid))  
				$uid++;
			else
				$uid = 0;
		}

    $add = jsonConvert( $_GET["add"] );
    $update = 0;
    $nuid0 = $uid;
    if (!$add["type"])
    {
      foreach ( $add as $i => $rec )
      {
        $addrec = addRecord($rec);
        if ( $addrec )
        {
          $records[sizeof($records)] = $addrec;
          $uid++;
        }
      }
    } else
    {
      $addrec = addRecord($add);
      if ( $addrec )
      {
        $records[sizeof($records)] = $addrec;
        $uid++;
      }
    }

    $fcont = json_encode($records);
    file_put_contents("db/records.js", $fcont);
    echo("{cmd:add,result:1,message=\"Added ".($uid-$nuid0)." records\"}\n");
    die();
  }
  if ( isset($_GET["delete"]) )
  {
		if ( $user != "admin" )
		{
	    echo("{cmd:delete,result:0,message=\"No privileges\"}\n");
 	   	die();
		}	

    @$records = json_decode(file_get_contents("db/records.js"),true);
    @$users = json_decode(file_get_contents("db/users.js"),true);

    $delete = json_decode($_GET["delete"], true);
    $cnt = 0;
		$newrecords = array();
		foreach ($records as $i => $rec)
		{	
			$id = $rec["nUid"];
			$valid = 1;
			foreach ($delete as $j => $del)
				if ( $id == $del )
				{
					$valid = 0;
					break;
				}
			if ($valid)
				$newrecords[sizeof($newrecords)] = $rec;
			else
				$cnt++;
		}
    $fcont = json_encode($newrecords);
    file_put_contents("db/records.js", $fcont);
    echo("{cmd:delete,result:1,message=\"Deleted ".($cnt)." records\"}\n");
    die();
	}

  if ( $_SERVER["QUERY_STRING"] == "getcount" )
	{
    @$records = json_decode(file_get_contents("db/records.js"),true);
    echo( sizeof($records) );
		die();
	}

  if ( isset($_GET["comment"]) )
  {
		if ( $user != "admin" )
		{
	    echo("{cmd:comment,result:0,message=\"No privileges\"}\n");
 	   	die();
		}	

    @$records = json_decode(file_get_contents("db/records.js"),true);
    @$users = json_decode(file_get_contents("db/users.js"),true);

    $comment = jsonConvert($_GET["comment"]);
		$text = $comment["text"];
		$text = str_replace("^c", ",", $text);
		$text = str_replace("^d", ":", $text);

		$changed = 0;
		foreach ($records as $i => $rec)
		{	
			if ( $rec["nUid"] == $comment["id"] )
			{
				$records[$i]["strComment"] = $text;
				$changed = 1;
			}
		}
		if ($changed)
		{
//			print_r($records);
	    $fcont = json_encode($records);
			file_put_contents("db/records.js", $fcont);
	    echo("{cmd:comment,result:1,message=\"Comment changed\"}\n");
		} else {
	    echo("{cmd:comment,result:0,message=\"Cannot find record for corresponding id\"}\n");
		}
    die();
	}

  if ( $_SERVER["QUERY_STRING"]=="json" )
  {
    @$records = json_decode(file_get_contents("db/records.js"),true);
    @$users = json_decode(file_get_contents("db/users.js"),true);

		/* 
			page Current page number. 
			sortname The name of the column to sort by. 
			sortorder The order to sort by – ‘asc’ or ‘desc’. 
			qtype The column selected during ‘quick search’. 
			query The text used within a search. 
			rp The number of records to be returned.
	
			page The current page number. 
			total The total number of records in the result set. Used by Flexigrid to calculate the number of pages. 
			rows This is an array containing the data for the rows. 
		*/  
		$page = $_POST["page"];
		$sortname = $_POST["sortname"];
		$sortorder = $_POST["sortorder"];
		$qtype = $_POST["qtype"];
		$query = $_POST["query"];
		$rp = $_POST["rp"];

		if (!$page)
			$page = 1;
		
		$rows = array();
		if ( is_array($records) )
		{
			foreach( $records as $i => $rec )
			{
				if ( !isset($rec["strComment"]) )
					$rec["strComment"] = "";

				if ( isset($query) && strlen($query)>0 )
				{
					if ( !strstr( strtolower($rec["strUser"]), strtolower($query) ) && 
							 !strstr( strtolower($rec["strComment"]), strtolower($query) ) )
					{
						continue;
					}	
				}
			  $rows[sizeof($rows)] = array(
			      "id" => (string)$rec["nUid"],
			      "cell" => array(
			        sgetDate($rec["dtMeasure"]),
			        sgetTime($rec["dtMeasure"]),
							$rec["strUser"],
							$rec["oValue"]["systolic"],
							$rec["oValue"]["diastolic"],
							$rec["oValue"]["pulse"],
							$rec["strComment"]
 		         	)
			    );
			}
		}	

		$result = array(
		  "page" => $page,
		  "total" => sizeof($rows),
		  "rows" => $rows);

		$txtresult = json_encode($result);
//		$txtresult = str_replace("\"id\":", "id:", $txtresult);
    echo( $txtresult );
    die();
  }

  if ( isset($_GET["chart"]) )
	{
    @$records = json_decode(file_get_contents("db/records.js"),true);

    $pulse = array();
		$systolic = array();
		$diastolic = array();

		$tsstart = -1;
		$query = $_GET["chart"];
		$j = 0;
    foreach ($records as $i => $rec)
		{
				if ( isset($query) && strlen($query)>0 )
				{
					if ( !strstr( strtolower($rec["strUser"]), strtolower($query) ) && 
							 !strstr( strtolower($rec["strComment"]), strtolower($query) ) )
					{
						continue;
					}	
				}

		  $dt = $rec["dtMeasure"];
			$_pulse = intval($rec["oValue"]["pulse"]);
			$_systolic = intval($rec["oValue"]["systolic"]);
			$_diastolic = intval($rec["oValue"]["diastolic"]);
			$_comment = $rec["strComment"];

			$ts = mktime( intval(substr($dt,8,2)), intval(substr($dt,10,2)), intval(substr($dt,12,2)), 
							intval(substr($dt,4,2)), intval(substr($dt,6,2)), intval(substr($dt,0,4)));

			if ( $tsstart == -1 )
				$tsstart = $ts;
			$utcDate = $ts; //($ts-$tsstart)*1000;

			$_value = $_systolic." / ".$_diastolic." @ ".$_pulse;

			$pulse[$j] = array( "x" => $utcDate."000", "y" => $_pulse, "c" => $_comment, "v" => $_value );
			$systolic[$j] = array( "x" => $utcDate."000", "y" => $_systolic, "c" => $_comment, "v" => $_value );
			$diastolic[$j] = array( "x" => $utcDate."000", "y" => $_diastolic, "c" => $_comment, "v" => $_value );
			$j++;
		}	

		$series = array(
			array(
				"name" => "Pulse",
				"data" => $pulse
			),
			array(
				"name" => "Systolic [mmHg]",
				"data" => $systolic
			),
			array(
				"name" => "Diastolic [mmHg]",
				"data" => $diastolic
			)
		);

		echo(json_encode($series));
		die();
		
	}


  function getCurrentDatetime()
  {
    return date("YmdHis");
  }
  function getUserById($id)
  {
    return "Gabriel Valky";
  }
  function addRecord($add)
  {
    global $uid;
    if ( $add["type"]=="boso_bp_1" )
    {
      $ts = $add["timestamp"];
      $systolic = $add["sys"];
      $diastolic = $add["dia"];
      $pulse = $add["pul"];
      $id = $add["id"];
      $flags = $add["flags"];
 
      $rec = array(
        "nUid" => $uid,
        "dtSubmit" => getCurrentDatetime(),
        "dtMeasure" => $ts,
        "strId" => $id,
        "strUser" => getUserById($id),
        "strType" => "blood pressure",
        "oValue" => array(
          "ihb" => $flags,
          "systolic" => $systolic,
          "diastolic" => $diastolic,
          "pulse" => $pulse,
        )
      );
//echo("rec=");
//print_r($rec);
      return $rec;
    }
    echo("<pre class=\"err\">");
    echo("Unknown packet information\n");
    print_r($add);
    echo("</pre>");
    return false;
  }
  @$records = json_decode(file_get_contents("db/records.js"),true);
  @$users = json_decode(file_get_contents("db/users.js"),true);


function sgetDate($dtStamp)
{
  return substr($dtStamp, 6, 2).". ".substr($dtStamp, 4, 2).". ".substr($dtStamp, 0, 4);
}

function sgetTime($dtStamp)
{
  return substr($dtStamp, 8, 2).":".substr($dtStamp, 10, 2);
}
function dumpRecordTable()
{
  global $records;
  foreach( $records as $i => $rec )
  {
    echo("<tr>");
    echo("<td>".sgetDate($rec["dtMeasure"])."</td>");
    echo("<td>".sgetTime($rec["dtMeasure"])."</td>");
    echo("<td>".$rec["strUser"]."</td>");
    echo("<td>".$rec["oValue"]["systolic"]."</td>");
    echo("<td>".$rec["oValue"]["diastolic"]."</td>");
    echo("<td>".$rec["oValue"]["pulse"]."</td>");
    echo("</tr>");
  }

}
function jsonConvert($add)
{
  $add = str_replace("{", "{'", $add);
  $add = str_replace("}", "'}", $add);
  $add = str_replace(":", "':'", $add);
  $add = str_replace(",", "','", $add);
  $add = str_replace("}','{", "},{", $add);
  $add = str_replace("'", "\"", $add);
  $add = json_decode($add, true);
	return $add;
}
//http://www.kenthouse.com/blog/2009/07/fun-with-flexigrids/

?>

<html>
<body>

<script type="text/javascript" src="flexigrid/jquery-1.7.js"></script>
<link rel="StyleSheet" href="flexigrid/css/flexigrid.css" type="text/css"/>
<script language="javascript" src="flexigrid/js/flexigrid.js"></script>
<style>
.flexigrid div.fbutton .add {
	background: url(images/add.png) no-repeat center left;
}

.flexigrid div.fbutton .delete {
	background: url(images/delete.png) no-repeat center left;
}
</style>
<div id="flex1"></div>

<script src="highcharts/js/highcharts.src.js"></script>
<!--<script src="http://code.highcharts.com/modules/exporting.js"></script>-->
<script type="text/javascript" src="highcharts/theme.js"></script>
<div id="graph" style="min-width: 400px; height: 400px; margin: 0 auto"></div>


<script language="javascript">
$("#flex1").flexigrid({
			url : 'index.php?json',
			dataType : 'json',
			colModel : [ 
				{ display : 'Date', name : 'date', width : 100, sortable : true, align : 'center' }, 
				{ display : 'Time', name : 'time', width : 60, sortable : false, align : 'left' }, 
				{	display : 'Name',	name : 'name', width : 140, sortable : true, align : 'left' }, 
				{ display : 'Systolic', name : 'systolic', width : 75, sortable : true, align : 'left', hide : false},
				{ display : 'Diastolic', name : 'diastolic', width : 75, sortable : true, align : 'left' }, 
				{ display : 'Pulse', name : 'pulse', width : 75, sortable : true, align : 'left'},
				{ display : 'Comment', name : 'comment', width:200, sortable : true, align : 'left'} 
			],
			buttons : [ 
				{ name : 'Add', bclass : 'add', onpress : test}, 
				{ name : 'Delete', bclass : 'delete', onpress : test}, 
				{ separator : true },
				{ name : 'Edit...', class : 'add', onpress : test}, 
				{ separator : true },
				{ name : 'Show graph', class : 'add', onpress : test}, 
				{ separator : true }, 
<? if ($user == "guest") { ?>
				{ name : 'Login', class : 'add', onpress : test}, 
<? } else { ?>
				{ name : 'Logout (<? echo $user; ?>)', class : 'add', onpress : test}, 
<? } ?>
				{ separator : true } 
			],
		searchitems : [ 
//				{ display : 'Name', name : 'name', isdefault : true }, 
//				{ display : 'Comment', name : 'comment' } ],
				{ display : 'Name / Comment', name : 'all' } ],
			sortname : "iso",
			sortorder : "asc",
			usepager : true,
			title : 'Blood pressure measurements',
			useRp : true,
			rp : 50,
			showTableToggleBtn : true,
			singleSelect: true,
			width : 800,
			height : 300
		});

function replaceAll(txt, replace, with_this) {
  return txt.replace(new RegExp(replace, 'g'),with_this);
}


var chart;
var series;

	function generateChart()
	{
    chart = new Highcharts.Chart({
        chart:			{ renderTo: 'graph', type: 'spline' },
        title:			{ text: 'Blood pressure chart' },
        subtitle:		{ text: 'Gabriel Valky, March 2012' },
        xAxis:			{ type: 'datetime', dateTimeLabelFormats: { month: '%e. %b', year: '%b' } },
        yAxis:			{ title: { text: 'Blood pressure (mmHg) / pulse [BPM]' }, min: 50 },
        tooltip:		{
            formatter: function() {
//										var d = new Date(this.x);
//										ts = d.getDay() + ". " + (d.getMonth()+1) + ". " + d.getYear() + " " + d.getHours() + ":" + d.getMinutes() + ":" + d.getSeconds();
										var val = this.point.v.split(" ");
										switch ( this.series.name.substr(0, 3) )
										{
											case "Sys": val[0] = "<b>" + val[0] + "</b>"; break;
											case "Dia": val[2] = "<b>" + val[2] + "</b>"; break;
											case "Pul": val[4] = "<b>" + val[4] + "</b>"; break;
										}	
										val = val.join(" ");
									
                    return '<b>'+ this.series.name +'</b><br/>'+val+'<br>'+
                    Highcharts.dateFormat("%d. %m. %Y %H:%M", parseInt(this.x)) + "<br>" + this.point.c;
            }
        },
				series: series 
		});
	}

		function test(com, grid) 
		{
	  	if (com=='Login')
			{
				window.location = "?login";
			}

	  	if (com=='Show graph')
			{
				var query = $('input[name=q]', grid).val();
				$.ajax({
					type: "GET",
					url: "",
					data: "chart="+query,
					success: function(data){
					  series = eval(data);
						generateChart();
					}
				});

			}
<? if ($user == "admin") { ?>

	  	if (com=='Edit...')
			{
				var items = $('.trSelected',grid);
				for(i=0;i<items.length;i++)
				{
					var id = items[i].id.substr(3);
					//qqq = items[i].children[6].children[0].innerHTML;
					var prev = items[i].children[6].children[0].innerHTML;
					if ( prev == "&nbsp;" )
						prev = "";
					var reply = prompt("Enter new comment for this record", prev);
//alert('comment={id:'+id+',text:'+escape(reply)+'}');
					if (reply)
					{
						reply = replaceAll(reply, ",", "^c");
						reply = replaceAll(reply, ":", "^d");

						$.ajax({
							type: "GET",
							url: "",
							data: 'comment={id:'+id+',text:'+escape(reply)+'}',
							success: function(data){
								$('#flex1').flexReload();
							}
						});
						
					}
				}

			}

	  	if (com=='Delete')
			{
				if($('.trSelected',grid).length>0)
				{
					if(confirm('Delete ' + $('.trSelected',grid).length + ' items?'))      
					{
						var items = $('.trSelected',grid);
						var itemlist = "";
						//qqq = items[0];
						for(i=0;i<items.length;i++)
						{
							if (i>0)
								itemlist += ",";
							itemlist = items[i].id.substr(3);
						}
					
						$.ajax({
							type: "GET",
							url: "",
							data: "delete=["+itemlist+"]",
							success: function(data){
								$('#flex1').flexReload();
							}
						});
					}
				} else 
				{
					return false;
				} 
			}
<? } else { ?>
			if ( com == "Edit..." || com == "Delete" || com == "Add" )
			{
				alert("You have to log in first to access these functions");
			}			
<? } ?>
		}	   
/*
		function test(com, grid) {
			if (com == 'Delete') {
				confirm('Delete ' + $('.trSelected', grid).length + ' items?')
			} else if (com == 'Add') {
				alert('Add New Item');
			}
	        }
*/
var nLastCount = -1;
setInterval('update()', 5000);

	function update()
	{
						$.ajax({
							type: "GET",
							url: "",
							data: "getcount",
							success: function(data){
								var nNewCount = parseInt(data);
								if ( nLastCount == -1 )
									nLastCount = nNewCount;
								if ( nLastCount != nNewCount )
									$('#flex1').flexReload();
								nLastCount = nNewCount;
							}
						});
	}

</script>

</body>
</html>