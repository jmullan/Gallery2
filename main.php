<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

/* Start profiling. */
list ($usec, $sec) = explode(" ", microtime());
$start = ((float)$usec + (float)$sec);

/* Initialize Gallery */
require(dirname(__FILE__) . '/init.php');

/* Figure out the target module/page */
list($gPage, $gModule) =
    GalleryUtilities::getRequestVariables('gPage', 'gModule');

/* Make sure that the requested module/page combo is clean */
if (ereg("[^[:alnum:]_.]", $gPage) || ereg("[^[:alnum:]_.]", $gModule)) {
    $gModule = 'core';
    $gPage = 'SecurityViolation';
}

if (empty($gModule) || empty($gPage)) {
    $gModule = 'core';
    $gPage = 'ShowItem';
}

/* Pass control to that module/page and record its output */
include($gallery->getConfig('core.directory.modules') .
	$gModule . '/' . $gPage . '.inc');

/* Stop profiling */
list ($usec, $sec) = explode(" ", microtime());
$stop = ((float)$usec + (float)$sec);
$elapsed = $stop - $start;

/* Display the global output */
$smarty = $gallery->getSmarty();
if ($gallery->getDebug()) {
    $master['profile'] = "Page generation: $elapsed secs";
    if ($gallery->getDebug() == 'buffered') {
	$master['debug'] = $gallery->getDebugBuffer();
    }
}
$master['layout'] = $gallery->getLayoutData('output');

$smarty->assign('master', $master);
$smarty->display('global.tpl');
?>
