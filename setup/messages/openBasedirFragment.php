<?php
$openBasedir = ini_get('open_basedir');
if (empty($openBasedir)) {
    return;
}
?>

    I noticed that your server has the following open_basedir setting:
    <br><br>
      <pre>    <?php echo $openBasedir ?></pre>
    <br>

    The open_basedir PHP setting restricts the directories that Gallery
    is allowed to write into.  The directory you specified above must be
    inside one of the directories in the open_basedir list.

    <br>
    
    Refer to the <a href="http://php.net/open_basedir">PHP website</a>
    for more information on this topic, or talk to your system administrator.
