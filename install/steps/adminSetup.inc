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
<p class="success">
Admin user "<?php print $_SESSION['uname']?>" updated successfully.
</p>
<?php } ?>

<p> <?php print _("Every Gallery will have at least one administrator user who has full access to view/modify everything. Please choose a username and password for your main administrator account. You can add additional users later.") ?> </p>

<form name="admin_form" method="POST" action="<?php print $PHP_SELF . '?step=4&action=create' ?>">
<table border="0">
<tr>
<td style="text-align: left;"><?php print _('Admin username:') ?></td>
<td><input name="uname" type="text" value="<?php print isset($_SESSION['uname']) ? $_SESSION['uname'] : _('admin') ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('Password:') ?></td>
<td><input name="passA" type="password" value="<?php print isset($_SESSION['pass']) ? $_SESSION['pass'] : '' ?>" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('(type again)') ?></td>
<td><input name="passB" type="password" value="<?php print isset($_SESSION['pass']) ? $_SESSION['pass'] : '' ?>" /></td>
</tr>
</table>
</form>

<?php if ($status[$step]) { ?>
<p>
<span class="bold" style="background-color: #d8d8d8; border: 1px solid #000000; padding: 3px;"><a href="javascript:document.admin_form.submit();"><?php print _('Change') ?></a></span>
<span class="bold" style="background-color: #d8d8d8; border: 1px solid #000000; padding: 3px;"><a href="index.php?step=5"><?php print _('Go to Step 5&rarr;') ?></a></span>
</p>
<?php } else { ?>
<p>
<span class="bold" style="background-color: #d8d8d8; border: 1px solid #000000; padding: 3px;"><a href="javascript:document.admin_form.submit();"><?php print _('Create') ?></a></span>
</p>
<?php } ?>