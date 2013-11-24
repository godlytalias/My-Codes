<?php
session_start();
setcookie('programmer','Godly T.Alias',time()+60)?>
<html>
<head><title>COURSE PAGE</title>
<script type="text/javascript" src="validate.js"></script><link rel="stylesheet" type="text/css" href="course.css">
</head>
<body>
<?php
if(isset($_SESSION['VIEWS']))
{$_SESSION['VIEWS']=$_SESSION['VIEWS']+1;}
else
{
$_SESSION['VIEWS']=1;
}
?>
<table><tr><td><hr><b>STUDENT REGISTRATION</b><hr></td></tr></table><div container="buttons" style="float:left;width:100px;height:385px;background-color:#997777">
<form action="actions.php" method='post'>
<br/>
<input type="submit" style="width:95px;height:40px" value="Enter Grade" name="grade"><br/><br/>
<input type="submit" style="width:95px;height:40px" value="Modify" name="modify"><br/><br/>
<input type="submit" style="width:95px;height:40px" value="Display" name="display"><br/><br/>
<input type="submit" style="width:95px;height:40px" value="Top Scorers" name="top"><br/><br/>
<input type='submit' style="width:95px;height:40px" value='Student' name='student'><br/><br/>
<input type='submit' style='width:95px;height:40px' value='Unenroll' name='unenroll'></form></div>
<div container="details" style="float:centre;width:600px;height:385px;background-color:#777777">

<form action="entervalue.php" method='post' name='studentform' onSubmit='return check()'>
<fieldset>
<legend><b>DETAILS OF STUDENT</b></legend>
<table>
<tr><td>FIRST NAME</td><td>:&nbsp;<input type='text' name="fname" style="width:250px"></td></tr>
<tr><td>LAST NAME</td><td>:&nbsp;<input type='text' name="lname" style="width:250px"></td></tr>
<tr><td>ROLL NO.</td><td>:&nbsp;<input type='text' name="rNo" style="width:150px"></td></tr>
<tr><td>DATE OF BIRTH</td><td>:&nbsp;<select name='dobd'>
<?php
 for($d=1;$d<=31;$d++)
{
echo "<option value='$d'>$d</option>";
}
echo "</select>&nbsp;<select name='dobm'><option value=01>January</option><option value=02>February</option><option value=03>March</option><option value=04>April</option><option value=05>May</option><option value=06>June</option><option value=07>July</option><option value=08>August</option><option value=09>September</option><option value=10>October</option><option value=11>November</option><option value=12>December</option></select>&nbsp;<select name='doby'>";
for($d=1988;$d<=date('Y');$d++)
{
echo "<option value='$d'>$d</option>";
}

?>
</select></td></tr>
<tr><td></td><td><input type='submit' name='student' value='Add Student'></td></tr>
</table></form><form action="entervalue.php" method='post'></fieldset>
<fieldset><legend><b>COURSE DETAILS</b></legend><table>
<tr><td>COURSE NAME</td><td>:&nbsp;<input type='text' name="cname" required='required' style="width:200px"></td></tr>
<tr><td>COURSE CODE</td><td>:&nbsp;<input type='text' name="ccode" required='required' style="width:50px"></td></tr>
<tr><td>CREDITS</td><td>:&nbsp;<input type='text' name="cr" required='required' style="width:25px"></td></tr>

<tr><td></td><td><input type='submit' style="align:right" value='Add Course' name='course'></td></form>

</table>
</fieldset>
</div>
<?php echo "<h6 align='right'>PAGEVIEWS=".$_SESSION['VIEWS']; ?>
</body>
</html>

