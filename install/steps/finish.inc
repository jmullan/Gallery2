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

<h1>Finish</h1>

<p>
<?php print _("Congratulations! Your Gallery 2 <span style=\"color:ae0000; font-style: italic;\">Alpha</span> has successfully installed! See... that wasn't so hard, was it? Now it's time to upload some photos!") ?>
</p>

<h2>
<?php print _("Now get me to my photos!") ?>
</h2>

<div class="go">
<span class="goToNext"><a href="../main.php"><?php print _('Go to my Gallery!') ?></a></span>
</div>
