    Gallery needs to write files into the directory below, but it
    can&rsquo;t.   This may be because the permissions of this 
    directory are too restrictive.  Try changing the modes to
    775 or 777.

    <?php include(dirname(__FILE__) . '/directoryDetailsFragment.php'); ?>
    <?php include(dirname(__FILE__) . '/openBasedirFragment.php'); ?>


