<center><div id="box">

<table width="100%" cellpadding="0" cellspacing="0">
<tr><td valign="bottom" align="center" class="bold" style="padding-bottom: 10px;"><?php echo _('Welcome to the Gallery2<span style="color:ae0000; font-style: italic;">Alpha</span> Installer!')?>
</td>
<td align="center" width="167"><img src="images/logo.png" height="95" width="167"></td>
</tr></table>
<hr style="margin-bottom: 20px;">

<?php echo $navbar; ?>

<div style="clear: both; margin-top: 20px;">
<table align="center" width="300" cellpadding="0" cellspacing="0">
<tr>
<?php
$progressBarColor = ($percentage >= 100) ? '#fd6704' : '#fd6704';
if ($percentage != 0) { ?>
<td width="<?php echo $percentage ?>%" align="center" bgcolor="<?php print $progressBarColor; ?>" style="border: 1px solid black">&nbsp;</td>
<?php }
if ($percentage != 100) { ?>
<td width="<?php echo 100 - $percentage ?>%" bgcolor="#d8d8d8" style="border: 1px solid black; <?php echo ($percentage == 0) ? '' : 'border-left: 0px;'?>">&nbsp;<td>
 <?php } ?>
</tr>
<tr><td <?php echo ($percentage != 0 && $percentage != 100) ? 'colspan="2"' : '';?> align="center"><?php print _('Install ') . $percentage ._('% complete')?></td></tr>
</table>
</div>

<hr>

<?php include(dirname(__FILE__) . '/steps/' . $content); ?>

</div>

<div style="text-align: center;">
&copy;<?php echo date('Y') ?> Gallery :: <a target="_blank" href="http://gallery.sourceforge.net/">gallery.sourceforge.net</a><br />
<img src="images/motto.png" height="25" width="230" />
</div>
</center>