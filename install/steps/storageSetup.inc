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
Storage directory set successfully.
</h2>
<?php } ?>

<h1>Storage Setup</h1>

<p> <?php print _("Gallery needs to store data in a directory on your server. It will use this directory to store your images as well as other important data. For security, we suggest that you place this directory <b>outside</b> the path to your webserver, so that it cannot be accessed directly via the web. This is necessary if you wish to have your images accessible only via Gallery<b>*</b>. If you access your site via FTP, you might not have this option.") ?> </p>

<p> <?php print _("The directory also needs to be writable to by Gallery. For help with permissions, see <b>FutureLinkToSomewhere</b>?.") ?> </p>

<form name="storage_form" method="POST" action="<?php print $_SERVER['PHP_SELF'] . '?step=5&action=create' ?>">
<table border="0">
<tr>
<td style="text-align: left;"><?php print _('Directory path:') ?></td>
<td><input name="dir" type="text" size="50" value="<?php print isset($_SESSION['dir']) ? $_SESSION['dir'] : dirname(dirname(dirname(__FILE__))) . '/g2data' ?>" /></td>
</tr>
</table>
</form>

<?php if ($status[$step]) { ?>
<div class="go">
<span class="goToNext"><a href="javascript:document.storage_form.submit()"><?php print _('Change') ?></a></span>
<span class="goToNext"><a href="index.php?step=6"><?php print _('Go to Step 6&raquo;') ?></a></span>
</div>
<?php } else { ?>
<div class="go">
<span class="goToNext"><a href="javascript:document.storage_form.submit()"><?php print _('Update') ?></a></span>
</div>
<?php } ?>
 
<p style="text-align: left;"><strong>*</strong> This is sometimes known as an <b>image firewall</b>.</p>

