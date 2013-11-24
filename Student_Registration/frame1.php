<?php session_start();
?>
<html>
<head><title><?php echo $_SESSION['name'];?>
</title></head>
<body>
<?php 
echo '<a href="http://www.google.co.in">Google</a>';?>
<iframe src="http://www.google.co.in" name="tab" width="100%" height="500" scrolling='yes'></iframe><br/>
<a href="http://www.facebook.com" target="tab">Facebook</a><br/>
</body>
</html>

