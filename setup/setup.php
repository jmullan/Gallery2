<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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

/* Turn on displaying errors, if possible */
@ini_set('display_errors', 1);

require_once(dirname(__FILE__) . '/security.inc');

ob_start();

if (phpversion() < '4.0.4') {
    error('oldPhp');
    return;
}

if (!CheckFileDirective()) {
    error('brokenFile');
    return;
}
 
if (!CheckConfigFileExists()) {
    error('missingConfig');
    return;
}

/*
 * Do the first pass of our initialization.  This doesn't do anything database
 * related.
 */
$ret = InitFirstPass();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    error('unknownError', array('error' => $ret));
    return;
}

$platform = $gallery->getPlatform();

$dirStatus = CheckDirectories();
if (!empty($dirStatus)) {
    list ($err, $key, $dir) = $dirStatus;
    $stat = $platform->stat($dir);
    switch($err) {
    case 'missing':
	error('missingDir',
		array('dir' => $dir,
		      'stat' => $stat));
	return;

    case 'not-a-dir':
	error('notADir',
		array('dir' => $dir,
		      'stat' => $stat));
	return;

    case 'not-writeable':
	error('notWriteable',
		array('dir' => $dir,
		      'stat' => $stat));
	return;

    case 'cant-mkdir':
	error('cantMkdir',
		array('dir' => $dir,
		      'stat' => $stat));
	return;
	
    case 'cant-write-into':
	error('cantWriteInto',
		array('dir' => $dir,
		      'stat' => $stat));
	return;
    }
}

/*
 * Verify database settings
 */
$storeConfig = $gallery->getConfig('storage.config');
if (empty($storeConfig['tablePrefix'])) {
    error('missingPrefix', array('type' => 'table'));
    return;
} else if (empty($storeConfig['columnPrefix'])) {
    error('missingPrefix', array('type' => 'column'));
    return;
}

/*
 * Make sure we can connect to the storage subsystem.
 */
$ret = $gallery->initStorage();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    error('storageError', array('error' => $ret));
    return;
}

message('success');

/*************************************************************
 *
 * Support functions below this point
 *
 *************************************************************/
function error($messageName, $messageData=null) {
    global $message, $gallery;
    global $_POST;

    $message = $messageData;
    $message['output'] = ob_get_contents();
    ob_end_clean();

    if (!empty($gallery)) {
	$message['debug'] = $gallery->getDebugBuffer();
    }
    
    if (!empty($_POST['g2_password'])) {
	$message['password'] = $_POST['g2_password'];
    }

    include(dirname(__FILE__) . '/messages/errorHeader.inc');
    include(dirname(__FILE__) . '/messages/' . $messageName . '.inc');
    include(dirname(__FILE__) . '/messages/errorFooter.inc');
}

function message($messageName, $messageData=null) {
    global $message, $gallery;

    $message = $messageData;
    $message['output'] = ob_get_contents();
    ob_end_clean();

    $message['debug'] = $gallery->getDebugBuffer();
    if (!empty($_POST['g2_password'])) {
	$message['password'] = $_POST['g2_password'];
    }

    include(dirname(__FILE__) . '/messages/messageHeader.inc');
    include(dirname(__FILE__) . '/messages/' . $messageName . '.inc');
    include(dirname(__FILE__) . '/messages/messageFooter.inc');
}

function CheckSetupPassword() {
    global $gallery;

    $password = $gallery->getConfig('setup.password');
    return (!empty($password));
}

function CheckPasswordIsCorrect() {
    global $gallery;

    if (empty($_POST['g2_password'])) {
	return false;
    }
    
    return !strcmp($gallery->getConfig('setup.password'),
		   $_POST['g2_password']);
}

function CheckConfigFileExists() {
    global $gallery;
    return file_exists(dirname(__FILE__) . '/../config.php');
}

function CheckFileDirective() {
    if (strstr(__FILE__, 'setup/setup.php') ||
	strstr(__FILE__, 'setup\\setup.php')) {
	return 1;
    } else {
	return 0;
    }
}

function InitFirstPass() {
    require(dirname(__FILE__) . '/../init.php');
    return GalleryInitFirstPass();
}

function InitSecondPass() {
    return GalleryInitSecondPass();
}

function CheckDirectories() {
    global $gallery, $platform;

    /* Make sure that our base path exists, is a directory and is writeable */
    $dataBase = $gallery->getConfig('data.gallery.base');
    if (!$platform->file_exists($dataBase)) {
	return array('missing', 'data.gallery.base', $dataBase);
    }

    if (!$platform->is_dir($dataBase)) {
	return array('not-a-dir', 'data.gallery.base', $dataBase);
    }

    if (!$platform->is_writeable($dataBase)) {
	return array('not-writeable', 'data.gallery.base', $dataBase);
    }

    $testfile = $dataBase . '/setup' . rand(1, 10000);
    if ($fd = $platform->fopen($testfile, 'w')) {
	$platform->fclose($fd);
	$platform->unlink($testfile);
    } else {
	return array('cant-write-into', 'data.gallery.base', $dataBase);
    }

    /* Create the sub directories, if necessary */
    foreach (array('data.gallery.albums',
		   'data.gallery.cache',
		   'data.gallery.tmp',
		   'data.smarty.base',
		   'data.smarty.templates_c') as $key) {
	$dir = $gallery->getConfig($key);

	if ($platform->file_exists($dir) && !$platform->is_dir($dir)) {
   	    return array('not-a-dir', $key, $dir);
	}

	if (!$platform->file_exists($dir)) {
	    if (!$platform->mkdir($dir)) {
		return array('cant-mkdir', $key, $dir);
		return GalleryStatus::success();
	    }
	}

	if (!$platform->is_writeable($dir)) {
	    return array('not-writeable', $key, $dir);
	}
    }
}

