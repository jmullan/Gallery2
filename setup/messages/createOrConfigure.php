
Congratulations, we&rsquo;ve successfully connected to your storage system.  This
means that the authentication information you entered in your gallery/config.php
is valid.  Now, you have two choices.

<form method="POST">
<?php foreach ($HTTP_POST_VARS as $key => $value) { ?>
<?php if ($key == 'submit') { continue; } ?>
    <input type="hidden" name="<?php echo $key ?>" value="<?php echo $value ?>">
<?php } ?>
    
<table>
 <tr>
  <td>
   If this is a first time installation, click this button to create a new
   Gallery database.  If you&rsquo;re unsure, go ahead and click here.  It won&rsquo;t
   cause any damage, though you may get an error if your database already
   exists.

   <br>

   <input type="submit" name="g2_storeAction" value="Create New Store">
  </td>
 </tr>

 <tr>
   <td>
    <br>
    <br>
    <br>
   </td>
 </tr>

 <tr>
  <td>
   If you&rsquo;re re-running the setup process on a pre-existing Gallery (eg, doing an upgrade
   or checking your settings), click this button.  You won&rsquo;t damage your
   database in any way by clicking this.

   <br>

   <input type="submit" name="g2_storeAction" value="Upgrade">
  </td>
 </tr>
</table>

</form>
