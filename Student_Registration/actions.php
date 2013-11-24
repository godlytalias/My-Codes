<?php
session_start();
?>
<html>
<head><title>COURSE PAGE</title></head>
<body>
<?php 

$server="localhost";
$sqlid="b100143cs";
$sqlpass="godlytalias";
$connect=mysql_connect($server,$sqlid,$sqlpass);
$db="db_b100143cs";
mysql_select_db($db,$connect);

if(isset($_POST['unenrolling']))
{
mysql_query("delete from takenCourses where rNo='$_SESSION[rollno]' and courseCode='$_SESSION[ccode]'");
header("location:course.php");
}


if(isset($_POST['cunenroll']))
{
echo "<font color='red' size='20' face='verdena'><b>COURSE CODE:".$_POST[course]."<hr></b></font>";
echo "<b><u>STUDENTS REGISTERED</u></b>";
$code=mysql_query("select rNo,firstName,lastName from Students where 'rNo' in (select rNo from takenCourses where courseCode='$_POST[course]')");
echo "<table border='1' cellpadding='10'>";
while($result=mysql_fetch_array($code))
{
echo "<tr><td><form action='actions.php' method='post'>";
$_SESSION[rollno]=$result[rNo];
$_SESSION[ccode]=$_POST[course];
echo "&nbsp;$result[rNo]</td><td>&nbsp;$result[firstName]&nbsp;$result[lastName]</td><td>&nbsp;<input type='submit' value='Unenroll' name='unenrolling'></td></tr>";
}
echo "</table>";
}


if(isset($_POST['unenroll']))
{
echo "<form action='actions.php' method='post'>SELECT COURSE&nbsp;&nbsp;<select name='course'>";
$code=mysql_query("select courseName,courseCode from Courses");
while($result=mysql_fetch_array($code))
{
echo "<option value='$result[courseCode]'>$result[courseName] ($result[courseCode])</option>";
}
echo "&nbsp;&nbsp;<input type='submit' value='Go' name='cunenroll'></form>";
}
if(isset($_POST['student']))
{
echo "<form action='student.php' method='post'><table><caption>Select Student:<hr></caption><tr><th>Student Name:</th><td><select name='st'>";

$code=mysql_query("select rNo,firstName,lastName from Students");
while($row=mysql_fetch_array($code))
{
echo "<option value='$row[rNo]'>$row[firstName] $row[lastName]</option>";
}
echo "</td><td><input type='submit' value='Go'></td></tr></form>";
}




if(isset($_POST['display']))
{
echo "<form action='display.php' method='post'><div container='text' style='width:350px;text-align:center;background-color:#224499'><table><tr><td><b>SELECT COURSE</b>&nbsp;&nbsp;&nbsp;</td><td>";
$course=mysql_query("SELECT courseName FROM Courses");
echo "<select name='courses'>";
while($row=mysql_fetch_array($course))
{
echo "<option value='$row[courseName]'>$row[courseName]</option>";
}
echo "</select></td></tr><tr><td></td><td align='center'><input type='submit' value='Display'></td></tr></table></div></form>";
}

if(isset($_POST['modify']))
{
echo "<form action='modify.php' method='post'><table><tr><td>Course to be modified</td><td>";
$course=mysql_query("SELECT courseCode,courseName FROM Courses");
echo "<select name='courses'>";
while($row=mysql_fetch_array($course))
{
echo "<option value='$row[courseCode]'>$row[courseName]</option>";
}
echo "</select></td></tr><tr><td>New Course name</td><td><input type='text' required='required' name='cname'></td></tr><tr><td>Credits</td><td><input type='text' required='required' name='cr' style='width:100px'></td></tr><tr><td></td><td align='center'><input type='submit' value='Modify'></td></tr></table></form>";

}


if(isset($_POST['top']))
{

$code=mysql_query("select Students.lastName,Students.firstName,d.courseName from Students inner join(select s.rNo,Courses.courseName from Courses inner join (select * from takenCourses where grade='S')as s where Courses.courseCode=s.courseCode)as d where Students.rNo=d.rNo order by d.courseName,Students.firstName");
echo "<table align='center'><caption><b><u>TOP SCORERES</u></b></caption><tr><th>COURSENAME<hr></th><th>TOPPERS<hr></th></tr>";
$cname='xxxx';
while($row=mysql_fetch_array($code))
{
echo "<tr><td>";
if($cname!=$row['courseName'])
{
echo $row['courseName'];
$cname=$row['courseName'];
}
echo "</td><td>".$row['firstName']." ".$row['lastName']."</td></tr>";
}
echo "</table>";
}


if(isset($_POST['grade']))
{
$rno=mysql_query("SELECT rNo FROM Students");
$course=mysql_query("SELECT courseCode FROM Courses");
echo "<form action='grade.php' method='post'><div container='box' style='width:275px'><fieldset><table><caption><hr>ENTER GRADE<hr></caption><tr><td>Roll Number </td><td>:<select name='rno'>";
while($row=mysql_fetch_array($rno))
{
echo "<option value='$row[rNo]'>$row[rNo]</option><br/>";
}
echo "</select></td></tr><tr><td>Course Code</td><td>:<select name='ccode'>";
while($row=mysql_fetch_array($course))
{
echo "<option value='$row[courseCode]'>$row[courseCode]</option>";
}
echo "</td></tr><tr><td>Grade</td><td><select name='grade'><option value='S'>S</option>
<option value='A'>A</option><option value='B'>B</option><option value='C'>C</option><option value='D'>D</option><option value='E'>E</option><option value='F'>F</option></td></tr><tr colspan=2><td align='center'><input type='submit' value='Enter'></td></tr></table></fieldset></div></form>";
}


mysql_close($connect);

?>

</body>
</html>

