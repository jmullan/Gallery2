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
<?php }

if (!$authenticated) {?>
<p>
<?php print _("In order to verify your identity, you'll need to upload a text file called <b>login.txt</b> to your <tt>gallery</tt> directory on your webserver (or wherever you have Gallery installed). It must contain the following randomly generated word:"); ?>
</p>

<p class="bold"><?php print $rand; ?></p>

<p>
<?php print _("<a href=\"index.php?step=1&action=authDownload&name=login.txt\">Click here</a> if you need to download <b>login.txt</b>. This password will remain valid for the next 5 minutes."); ?>
</p>

<p>
<?php print _("Once you've uploaded the file, click below to continue."); ?>
</p>

<p>
<span class="bold" style="background-color: #d8d8d8; border: 1px solid #000000; padding: 3px;"><a href="index.php?step=1&action=authCheck"><?php print _('Authenticate me!'); ?></a></span>
</p>
<?php } else { ?>
<p class="success">
<?php print _("Authentication successful!") ?>
</p>

<p>
<span class="bold" style="background-color: #d8d8d8; border: 1px solid #000000; padding: 3px;"><a href="index.php?step=2"><?php print _('Go to Step 2&rarr;') ?></a></span>
</p>
<?php } ?>