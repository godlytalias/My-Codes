<html>
<head>
<title>MODIFY COURSE DETAILS</title>
</head>
<body>
<?php
$server="localhost";
$sqlid="b100143cs";
$sqlpass="godlytalias";
$connect=mysql_connect($server,$sqlid,$sqlpass);
$db=mysql_select_db("db_b100143cs",$connect);

$code=mysql_query("update Courses set courseName='$_POST[cname]',credits='$_POST[cr]' WHERE courseCode='$_POST[courses]'");
if(!$code)
{
echo "DATABASE ERROR:".mysql_error();
}
else
{
header('LOCATION: course.php');
}

?>
</body>
</html>
