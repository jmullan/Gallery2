<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
	<title>Untitled</title>
	<link rel="STYLESHEET" type="text/css" href="/style.css">
	<style>
		td {
			font-family: "OCR A Extended", monospace;
		}
	</style>
</head>
<body>
<?php
global $_REQUEST;
$foundit = FALSE;
$approved = file('debugfiles.txt');
foreach ($approved as $okay ) {
	$okay = str_replace("\r", "", $okay);
	$okay = str_replace("\n", "", $okay);
	trim($okay);
	if (strcmp($okay,$_REQUEST["file"])==0) {
		$foundit = TRUE;
?>
<h1><?php echo $_REQUEST["file"] . ':' . $_REQUEST["line"]; ?></h1>
<table>
<?php
		$i=0;
		$file = file($_REQUEST["file"]);
		foreach ($file as $line ) {
			$i++;
?>
	<tr>
		<td align="right">
			<?php if ($i == $_REQUEST["line"] ) {echo '<strong>';} ?>
			<a name="line<?php echo $i; ?>"><?php echo $i; ?></a>
			<?php if ($i == $_REQUEST["line"] ) {echo '</strong>';}; ?>
		</td>
		<td align="left">
			<?php if ($i == $_REQUEST["line"] ) {echo '<strong>';} ?>
			<?php $line = str_replace("/t", "    ", $line); ?>
			<?php echo str_replace(" ", "&nbsp;", $line); ?>
			<?php if ($i == $_REQUEST["line"] ) {echo '</strong>';} ?>
		</td>
	</tr>
<?php
		}
?>
</table>
<?php
	}
}
if (!$foundit) {
	echo 'Please add ' . $_REQUEST["file"] . ' to the list of approved files before you ask me to give it to you.';
}
?>
</body>
</html>
