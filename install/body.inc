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
    <img src="images/g2Logo_install_head.png" />
  </div>
  <div id="help"><a target="_blank" href="../README.html">Installer Help File</a></div>
  <div id="navbar">
    <h2>Install Steps</h2>
    <?php echo $navbar; ?>
  </div>
  <?php if (count($errorMsg) > 0) { ?>
  <?php } ?>
  <div id="main">
    <h2 class="error">
      <?php print implode("<br />\n", $errorMsg); ?>
    </h2>
    
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
