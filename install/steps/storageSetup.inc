<p> <?php print _("Gallery needs to store data in a directory on your server. It will use this directory to store your images as well as other important data. For security, we suggest that you place this directory <b>outside</b> the path to your webserver, so that it cannot be accessed directly via the web. This is necessary if you wish to have your images accessible only via Gallery<b>*</b>. If you access your site via FTP, you might not have this option.") ?> </p>

<p> <?php print _("The directory also needs to be writable to by Gallery. For help with permissions, see <b>LinkToSomewhere</b>?.") ?> </p>

<form>
<table border="0">
<tr>
<td style="text-align: left;"><?php print _('Directory path:') ?></td>
<td><input type="text" size="50" value="<?php print dirname(dirname(dirname(__FILE__))) . '/g2data' ?>" /></td>
</tr>
</table>
</form>

<p>
<span class="bold" style="background-color: #d8d8d8; border: 1px solid #000000; padding: 3px;"><a href="index.php?step=6"><?php print _('Go to Step 6&rarr;') ?></a></span>
</p>

<p style="text-align: left;"><b>*</b> This is sometimes known as an <b>image firewall</b>.</p>

