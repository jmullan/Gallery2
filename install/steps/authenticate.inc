<?php if (!empty($errorMsg)) { ?>
<p class="error">
<?php print $errorMsg; ?>
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