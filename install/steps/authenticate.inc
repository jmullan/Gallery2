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

if (!$authenticated) {?>
<h2>Authenticate</h2>
<p>
<?php print _("In order to verify your identity, you'll need to upload a text file called <strong>login.txt</strong> to your <tt>gallery</tt> directory on your webserver (or wherever you have Gallery installed). It must contain the following randomly generated word:"); ?>
</p>

<p class="bold"><?php print $rand; ?></p>

<p>
<?php print _("<a href=\"index.php?step=1&action=authDownload&name=login.txt\">Click here</a> if you need to download <strong>login.txt</strong>. This password will remain valid for the next 5 minutes."); ?>
</p>

<p>
<?php print _("Once you've uploaded the file, click below to continue."); ?>
</p>

<div class="go">
<span class="goToNextL"><a href="index.php?step=1&action=authCheck"><?php print _('Authenticate me!'); ?></a></span>
</div>
<?php } else { ?>
<h2 class="success">
<?php print _("Authentication successful!") ?>
</h2>
<div class="go">
  <span class="goToNextL">
    <a href="index.php?step=2"><?php print _('Go to Step 2&raquo;') ?></a>
  </span>
</div>
<?php } ?>