<p> <?php print _("Please choose a username and password for your administrator account. You can change the name and password later, as well as add additional administrator users.") ?> </p>

<form>
<table border="0">
<tr>
<td style="text-align: left;"><?php print _('Database type:') ?></td>
<td style="text-align: left;">
<select>
<option value="mysqlt">MySQL (v3.23.34a and newer)</option>
<option value"mysql">MySQL (older than v3.23.34a)</option>
<option>PosgreSQL v7.x</option>
<option>PosgreSQL v6.x (not well tested)</option>
</select>
</td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Hostname:') ?></td>
<td style="text-align: left;"><input type="text" value="localhost" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Username:') ?></td>
<td style="text-align: left;"><input type="text" value="" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('DB Password:') ?></td>
<td style="text-align: left;"><input type="password" value="" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('Table Prefix:') ?></td>
<td style="text-align: left;"><input type="text" value="g2_" /></td>
</tr>
<tr>
<td style="text-align: left;"><?php print _('Column Prefix:') ?></td>
<td style="text-align: left;"><input type="text" value="g_" /></td>
</tr>
</table>
</form>

<p>
<span class="bold" style="background-color: #d8d8d8; border: 1px solid #000000; padding: 3px;"><a href="index.php?step=7"><?php print _('Go to Step 7&rarr;') ?></a></span>
</p>
