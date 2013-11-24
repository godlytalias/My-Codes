<!DOCTYPE html>
<?php
session_start();
$conn=mysql_connect("localhost","b100143cs","godlytalias");
$db=mysql_select_db("db_b100143cs",$conn);
$result=mysql_query("select firstName,lastName,email from email where userName='$_SESSION[user]'");
$result=mysql_fetch_array($result);
$_SESSION['name']=$result['firstName']." ".$result['lastName'];
?>
<html>
<head><title><?php echo $result['firstName']; ?></title></head>
<?php
$mail=explode("@",$result['email']);
$_SESSION['domain']=$mail[1];
header('location:frames.html');
?>
</html>
