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
<?php if (count($errorMsg) > 0) { ?>
<p class="error">
<?php print implode("<br />\n", $errorMsg); ?>
</p>
<?php } ?>

<?php if ($status[$step]) { ?>
<h2 class="success">
Database set up successfully!</h2>
<?php } ?>

<h1>Database Setup</h1>

<p> <?php print _("Please choose a username and password for your administrator account. You can change the name and password later, as well as add additional administrator users.") ?> </p>

<form name="database_form" method="POST" action="<?php print $_SERVER['PHP_SELF'] . '?step=6&action=create' ?>">
<table border="0">
<tr>
<td style="text-align: left;"><?php print _('Database type:') ?></td>
<td style="text-align: left;">
<select name="dbtype">
<?php
$db = 'mysqlt';
if (isset($_SESSION['db'])) {
	$db = $_SESSION['db']['dbtype'];
}
$dbtypes = array ('mysqlt' => _("MySQL (v3.23.34a and newer)"),
				  'mysql'  => _("MySQL (older than v3.23.34a)"),
				  'pgsql7' => _("PostgreSQL v7.x"),
				  'pgsql6' => _("PostgreSQL v6.x (not well tested)")
				  );
foreach ($dbtypes as $key => $val) {
	$selected = ($db === $key) ? ' selected' : '';
	print "<option value=\"$key\"$selected>$val</option>\n";
}
?>
</select>
</td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Hostname:') ?></td>
<td style="text-align: left;"><input name="host" type="text" value="<?php isset($_SESSION['db']['host']) ? $_SESSION['db']['host'] : 'localhost'; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Username:') ?></td>
<td style="text-align: left;"><input name="uname" type="text" value="<?php isset($_SESSION['db']['uname']) ? $_SESSION['db']['uname'] : ''; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Password:') ?></td>
<td style="text-align: left;"><input name="pass" type="password" value="<?php isset($_SESSION['db']['pass']) ? $_SESSION['db']['pass'] : ''; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('Table Prefix:') ?></td>
<td style="text-align: left;"><input name="tPrefix" type="text" value="<?php isset($_SESSION['db']['tPrefix']) ? $_SESSION['db']['tPrefix'] : 'g2_'; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('Column Prefix:') ?></td>
<td style="text-align: left;"><input name="cPrefix" type="text" value="<?php isset($_SESSION['db']['cPrefix']) ? $_SESSION['db']['cPrefix'] : 'g_'; ?>" /></td>
</tr>
</table>
</form>

<?php if ($status[$step]) { ?>
<div class="go">
<span class="goToNext"><a href="javascript:document.database_form.submit()"><?php print _('Update') ?></a></span>
<span class="goToNext"><a href="index.php?step=7"><?php print _('Go to Step 7&raquo;') ?></a></span>
</p>
<?php } else { ?>
<p>
<span class="goToNext"><a href="javascript:document.database_form.submit()"><?php print _('Update') ?></a></span>
</p>
<?php } ?>
