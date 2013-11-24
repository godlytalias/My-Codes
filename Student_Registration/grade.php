<html>
<title>GRADE ENTERED</title>
<body>
<?php
$connect=mysql_connect("localhost","b100143cs","godlytalias");
$db=mysql_select_db("db_b100143cs",$connect);
$result=mysql_query("INSERT INTO takenCourses VALUES('$_POST[rno]','$_POST[ccode]','$_POST[grade]')");
if(!$result)
{
echo "Database entry failed - ".mysql_error();
}
else
{
echo "SUCCESSFULLY ENTERED";
}
echo "<br/><br/><form action='course.php'><input type='submit' value='Go Back'></form>";
?>

</body>
</html>
