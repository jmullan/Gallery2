<?php
/*
 * $Id$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
?>
<div id="box">
  <div id="header">
    <img src="images/logo.png" height="95" width="167">
    <?php echo _('<span style="color:ae0000; font-style: italic;">Alpha</span> Installer')?>
  </div>
  <div id="navbar">
    <h2>Install Steps</h2>
    <?php echo $navbar; ?>
  </div>
  <div id="main">
    <?php include(dirname(__FILE__) . '/steps/' . $content); ?>
  </div>
  <div id="bottom">
    <table class="statusTable">
      <tr>
         <td colspan="2">
           <h4>Installation Status</h4>
         </td>
      </tr>
      <tr>
        <?php
        $progressBarColor = ($percentage >= 100) ? '#fd6704' : '#fd6704';
        if ($percentage != 0) { ?>
        <td width="<?php echo $percentage ?>%" align="center" bgcolor="<?php print $progressBarColor; ?>" style="border: 1px solid #ddd">&nbsp;</td>
        <?php }
        if ($percentage != 100) { ?>
        <td width="<?php echo 100 - $percentage ?>%" bgcolor="#eeeeee" style="border: 1px solid #ddd; <?php echo ($percentage == 0) ? '' : 'border-left: 0px;'?>">&nbsp;<td>
         <?php } ?>
      </tr>
      <tr>
        <td <?php echo ($percentage != 0 && $percentage != 100) ? 'colspan="2"' : '';?> ><span class="statusLine"><?php print _('Install ') . $percentage ._('% complete')?></span></td>
      </tr>
    </table>
  </div>  
<!--<table width="100%" cellpadding="0" cellspacing="0">
<tr><td valign="bottom" align="center" class="bold" style="padding-bottom: 10px;"><?php echo _('Welcome to the Gallery2 <span style="color:ae0000; font-style: italic;">Alpha</span> Installer!')?>
</td>
<td align="center" width="167"><img src="images/logo.png" height="95" width="167"></td>
</tr></table>
<hr style="margin-bottom: 20px;">

<?php echo $navbar; ?>

<div style="clear: both; margin-top: 20px;">
<table width="300" cellpadding="0" cellspacing="0">
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
-->
</div>
<div id="footer">
&copy;<?php echo date('Y') ?> Gallery :: <a target="_blank" href="http://gallery.sourceforge.net/">gallery.sourceforge.net</a> :: <strong>YOUR</strong> PHOTOS ON <strong>YOUR</strong> WEBSITE

<!--<br />
<img src="images/motto.png" height="25" width="230" />-->
</div>
