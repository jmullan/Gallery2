
Congratulations, we&rsquo;ve successfully connected to your storage system.  This
means that the authentication information you entered in your gallery/config.php
is valid.

<p>

<form method="POST">
<?php foreach ($HTTP_POST_VARS as $key => $value) { ?>
<?php if ($key == 'submit') { continue; } ?>
    <input type="hidden" name="<?php echo $key ?>" value="<?php echo $value ?>">
<?php } ?>

If this is a first time installation, and you&rsquo;re not installing Gallery into
a shared database, we can create your database for you.  This is probably the
most common installation option.
<br>
<b> Note: </b> If your database already exists, <b>this
will not cause any harm</b>, it&rsquo;ll just print out an error message.
 <br>
<input type="submit" name="g2_storeAction" value="Create New Database">


<p>

If this is an upgrade, or you&rsquo;ve configured Gallery to use a pre-existing
database (like if you&rsquo;re putting it into the same database that your CMS
or another application uses), you can just continue.  This won&rsquo;t affect
your database at all.
<br>
<b> Note: </b> If you don&rsquo;t create the database and it turns out
that the one you specified doesn&rsquo;t already exist, then Gallery will
fail with an error message like "unknown database" when you try to use it.
(that&rsquo;s ok -- you can just re-run this config process).

<br>
<input type="submit" name="g2_storeAction" value="Continue">


</form>
