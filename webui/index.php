<!DOCTYPE HTML>
<html>
<head>
<style type="text/css">
.switchdiv {
	margin: 5px;
}
body {
	padding: 20px;
}
</style>
</head>
<body>
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
<div class="btn-group" role="group" aria-label="...">
	<button type="button" class="btn btn-default active" id="yellowbankbtn" onClick="bankButtonClicked(this.id)">Yellow bank</button>
	<button type="button" class="btn btn-default" id="redbankbtn" onClick="bankButtonClicked(this.id)">Red bank</button>
</div>
<?php
for ($i = 1; $i <= 36; $i++) {
	echo '<div class="switchdiv">';
	echo $i.": ";
	echo '<input type="checkbox" name="deskswitch" id="'.$i.'" data-size="mini">';
	echo '<br/>';
	echo '</div>';
}
?>
<link href="css/bootstrap.min.css" rel="stylesheet">
<link href="js/bootstrap.min.js" rel="stylesheet">
<link href="css/bootstrap-switch.css" rel="stylesheet">
<script src="js/jquery.js"></script>
<script src="js/bootstrap-switch.js"></script>
<script>
bankvalue = 0;
$("[name='deskswitch']").bootstrapSwitch();
$("[name='deskswitch']").on('switchChange.bootstrapSwitch', function (event, state) {
	//this.id;
});
function bankButtonClicked(id) {
	classname = document.getElementById(id).className;
	if (classname.substring(classname.length-6) != "active") {
		document.getElementById(id).className += " active";
		if (id == "yellowbankbtn") {
			bankvalue = 0;
			document.getElementById("redbankbtn").className = "btn btn-default";
		} else if (id == "redbankbtn") {
			bankvalue = 1;
			document.getElementById("yellowbankbtn").className = "btn btn-default";
		}
	}
}
</script>
</body>
</html>