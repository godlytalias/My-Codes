<html><head><title>
COURSE PAGE
</title>
</head>
<body>
<?php $server="localhost";
$sqlid="b100143cs";
$sqlpass="godlytalias";
$dbase="db_b100143cs";
$connection=mysql_connect($server,$sqlid,$sqlpass);
if(!$connection)
{
die("database failed".mysql_error());}
$dbselect=mysql_select_db($dbase,$connection);
if(!dbselect)
{
die("database failed".mysql_error());}
if($_POST[student])
{
$no=$_POST[rNo];
$fname=$_POST[fname];
$lname=$_POST[lname];
$dob=$_POST[doby]."-".$_POST[dobm]."-".$_POST[dobd];
$dob=date($dob);
$result=mysql_query("INSERT INTO Students (rNo,firstName,lastName,DOB) VALUES('$no','$fname','$lname','$dob')");

}
if($_POST[course])
{

$result=mysql_query("INSERT INTO Courses VALUES('$_POST[ccode]','$_POST[cname]','$_POST[cr]')");
}

if(!$result)
{echo "ENTRY FAILED".mysql_error();}
else echo "DATA ENTERED SUCCESSFULLY";

header("Location: course.php");

mysql_close($connection);
?>
</body>
</html>
