
    <br><br>
    <table border=1>
      <tr>
        <td>Directory</td>
        <td><?php echo $message['dir'] ?></td>
      </tr>
      <tr>
        <td>Owner userid</td>
        <td><?php echo $message['stat'][4] ?></td>
      </tr>
      <tr>
        <td>Owner group</td>
        <td><?php echo $message['stat'][5] ?></td>
      </tr>
      <tr>
        <td>Permissions</td>
        <td><?php displayPerms($message['stat'][2]) ?></td>
      </tr>
    <table>
    <br>

<?php
/*
 * This function is lifted from:
 *  http://www.php.net/manual/en/function.fileperms.php
 *
 * where it was posted by "pwalker@pwccanada.com".  I modified it slightly to
 * make it conform to our code standards and to add the octal permission.
 * Thanks, pwalker.
 */
function displayPerms($mode) {

    /* Determine Type */
    if ($mode & 0x1000) { 
	$type='p'; /* FIFO pipe */
    } else if ($mode & 0x2000) {
	$type='c'; /* Character special */
    } else if ($mode & 0x4000) {
	$type='d'; /* Directory */
    } else if ($mode & 0x6000) {
	$type='b'; /* Block special */
    } else if ($mode & 0x8000) {
	$type='-'; /* Regular */
    } else if ($mode & 0xA000) {
	$type='l'; /* Symbolic Link */
    } else if ($mode & 0xC000) {
	$type='s'; /* Socket */
    } else {
	$type='u'; /* UNKNOWN */
    }

    /* Determine permissions */
    $owner['read'] = ($mode & 00400) ? 'r' : '-';
    $owner['write'] = ($mode & 00200) ? 'w' : '-';
    $owner['execute'] = ($mode & 00100) ? 'x' : '-';
    $group['read'] = ($mode & 00040) ? 'r' : '-';
    $group['write'] = ($mode & 00020) ? 'w' : '-';
    $group['execute'] = ($mode & 00010) ? 'x' : '-';
    $world['read'] = ($mode & 00004) ? 'r' : '-';
    $world['write'] = ($mode & 00002) ? 'w' : '-';
    $world['execute'] = ($mode & 00001) ? 'x' : '-';

    /* Adjust for SUID, SGID and sticky bit */
    if ($mode & 0x800) {
	$owner['execute'] = ($owner[execute]=='x') ? 's' : 'S';
    }

    if ($mode & 0x400) {
	$group['execute'] = ($group[execute]=='x') ? 's' : 'S';
    }
    
    if ($mode & 0x200) {
	$world['execute'] = ($world[execute]=='x') ? 't' : 'T';
    }
    
    $mode &= 0x0FFF;
    printf("%o ", $mode);
    
    printf("(%1s", $type);
    printf("%1s%1s%1s", $owner['read'], $owner['write'], $owner['execute']);
    printf("%1s%1s%1s", $group['read'], $group['write'], $group['execute']);
    printf("%1s%1s%1s)", $world['read'], $world['write'], $world['execute']);

}
?>