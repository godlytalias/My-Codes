function check()
{
if (document.forms["studentform"]["fname"].value=="")
{
if (document.studentform.rNo.value=="")
{
alert("ENTER A FIRST NAME & ROLL NO.");
document.studentform.fname.focus();
return false;
}
else
{
alert("ENTER A FIRST NAME");
document.studentform.fname.focus();
return false;
}
}
if (document.studentform.rNo.value=="")
{
alert("ENTER A ROLL NO.");
document.studentform.rNo.focus();
return false;
}
return true;
}


function mouseon()
{
document.myForm.im.src="goi.gif";
}

function mouseout()
{
document.myForm.im.src="goo.png";
}
