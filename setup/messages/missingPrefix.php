    In your database configuration, you left the 
    <b>
    <?php if ($message['type'] == 'table') { ?>
      table
    <?php } else { ?>
      column
    <?php } ?>
    prefix</b> empty.  Gallery requires you to use a prefix here to avoid conflicts
    with reserved words in the database.  This should be just a few characters like
    <i>g_</i> or <i>g2_</i>  Please specify a prefix and try again.


