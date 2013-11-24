<html>
<head><title>STUDENT DETAILS</title></head>
<body>
<h3><b>Course Code :</b>
<?php
$connect=mysql_connect("localhost","b100143cs","godlytalias");
$db=mysql_select_db("db_b100143cs",$connect);
$code=mysql_query("SELECT 'courseCode' FROM Courses WHERE courseName='$_POST[courses]'");
$print=mysql_fetch_array($code);
echo $print[courseCode]."</h3><hr>";

echo "<br/><table border='1'><tr><th>ROLL NO.</th><th>FIRST NAME</th><th>LAST NAME</th><th>GRADE</th></tr>";
$code=mysql_query("SELECT s.rNo,t.grade,s.firstName,s.lastName FROM Students AS s,takenCourses AS t WHERE s.rNo=t.rNo AND t.courseCode='$print[courseCode]'");

echo mysql_error();
while($row=mysql_fetch_array($code))
{
echo "<tr><td>".$row[rNo]."</td><td>".$row[firstName]."</td><td>".$row[lastName]."</td><td>".$row[grade]."</td></tr>";
}
echo "</table>";
?>
</body>
</html>
