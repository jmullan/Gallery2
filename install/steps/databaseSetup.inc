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
<?php

if ($status[$step]) { ?>
<h2 class="success">
Database set up successfully.
</h2>
<?php } ?>

<h1>Database Setup</h1>

<p> <?php print _("Please choose a username and password for your administrator account. You can change the name and password later, as well as add additional administrator users.") ?> </p>

<form name="database_form" method="POST" action="<?php print $_SERVER['PHP_SELF'] . '?step=6&action=create' ?>">
<table border="0">
<tr>
<td style="text-align: left;"><?php print _('Database type:') ?></td>
<td style="text-align: left;">
<select name="type">
<?php
$db = 'mysqlt';
if (isset($_SESSION['db']['type'])) {
	$db = $_SESSION['db']['type'];
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
<td style="text-align: left;"><input name="hostname" type="text" value="<?php print isset($_SESSION['db']['hostname']) ? $_SESSION['db']['hostname'] : 'localhost'; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Username:') ?></td>
<td style="text-align: left;"><input name="username" type="text" value="<?php print isset($_SESSION['db']['username']) ? $_SESSION['db']['username'] : 'root'; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Password:') ?></td>
<td style="text-align: left;"><input name="password" type="password" value="<?php print isset($_SESSION['db']['password']) ? $_SESSION['db']['password'] : ''; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Name:') ?></td>
<td style="text-align: left;"><input name="database" type="text" value="<?php print isset($_SESSION['db']['database']) ? $_SESSION['db']['database'] : 'gallery'; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('Table Prefix:') ?></td>
<td style="text-align: left;"><input name="tablePrefix" type="text" value="<?php print isset($_SESSION['db']['tablePrefix']) ? $_SESSION['db']['tablePrefix'] : 'g2_'; ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('Column Prefix:') ?></td>
<td style="text-align: left;"><input name="columnPrefix" type="text" value="<?php print isset($_SESSION['db']['columnPrefix']) ? $_SESSION['db']['columnPrefix'] : 'g_'; ?>" /></td>
</tr>
</table>
</form>

<?php if ($status[$step]) { ?>
<div class="go">
<span class="goToNext"><a href="javascript:document.database_form.submit()"><?php print _('Update') ?></a></span>
<span class="goToNext"><a href="index.php?step=7"><?php print _('Go to Step 7&raquo;') ?></a></span>
</div>
<?php } else { ?>
<div class="go">
<span class="goToNext"><a href="javascript:document.database_form.submit()"><?php print _('Update') ?></a></span>
</div>
<?php } ?>
