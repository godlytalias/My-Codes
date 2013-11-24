<?php session_start();
?>
<html>
<head><title><?php echo $_SESSION['name'];?>
</title>
</head>
<body>
<?php $url="http://www.".$_SESSION['domain'];
echo "<iframe src='$url' name='tab' width='100%' height='500' scrolling='yes'></iframe><br/>
<a href='http://www.youtube.com' target='tab'>Youtube</a><br/>";
?>
</body>
</html>
