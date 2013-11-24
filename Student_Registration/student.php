<html>
<?php
$connect=mysql_connect("localhost","b100143cs","godlytalias");
$db=mysql_select_db("db_b100143cs",$connect);
?>
<head>
<title><?php 
$code=mysql_query("select firstName,extract(year from DOB),DOB,lastName from Students where rNo='$_POST[st]'");
$name=mysql_fetch_array($code);
$n=$name['firstName'].$name['lastName'];
echo $n;
echo "</title>
</head>
<body>";

echo "<table border='1'><tr><th>FIRST NAME</th><td>".$name['firstName']."</td></tr>
<tr><th>LAST NAME</th><td>".$name['lastName']."</td></tr>
<tr><td>ROLL NO.</td><td>".$_POST[st]."</td></tr>
<tr><td>DATE OF BIRTH</td><td>".$name['DOB']."</td></tr>
<tr><td>AGE</td><td>";
$d=(date('y')+2000)-($name['extract(year from DOB)']);
echo $d."</td></tr></table>";
echo "<table border='2'><tr><th width='500px'>COURSES TAKEN</th><th>GRADES SCORED</th></tr>";
$code=mysql_query("SELECT d.grade,Courses.courseName,Courses.credits from Courses inner join (select grade,courseCode from takenCourses where rNo='$_POST[st]') as d where d.courseCode=Courses.courseCode");
echo mysql_error();
$no=0;
(float)$sum=00.0;
while ($course=mysql_fetch_array($code))
{
echo "<tr><td>".$course['courseName']."</td><td align='center'>".$course['grade']."</td></tr>";
$no=$no+$course['credits'];
if(!strcmp($course['grade'],'S'))
{
$sum=$sum+(10*$course['credits']);
continue;}
if(!strcmp($course['grade'],'A'))
{$sum=$sum+(9.0*$course['credits']);
continue;}
if(!strcmp($course['grade'],'B'))
{$sum=$sum+(8.0*$course['credits']);
continue;}
if(!strcmp($course['grade'],'C'))
{$sum=$sum+(7.0*$course['credits']);
continue;}
if(!strcmp($course['grade'],'D'))
{$sum=$sum+(6.0*$course['credits']);
continue;}
if(!strcmp($course['grade'],'E'))
{$sum=$sum+(5.0*$course['credits']);
continue;}
}

(float)$cgpa=(float)$sum/$no;
echo "</table><table align='center' border='1' cellpadding='10'><tr><th>CGPA</th><td>".$cgpa."</td></tr></table>";
?>
<div container='button' style='width:100px;float:right'> <form action='course.php'><input type='submit' value='Go Back'></form></div></body>
</html>
