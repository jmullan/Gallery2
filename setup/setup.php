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

ob_start();

if (phpversion() < "4.0.4") {
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
 * This call may fail, especially if the storage has not been
 * configured properly.  That's ok.  We'll check the storage
 * settings independently.
 */
$ret = InitializeGallery();

$platform = $gallery->getPlatform();

if (!CheckSetupPassword()) {
    error('missingPassword');
    return;
}

if (!CheckPasswordIsCorrect()) {
    message('passwordForm');
    return;
}

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
 * Make sure we can connect to the storage subsystem.
 */
list ($ret, $storage) = $gallery->getUninitializedStorage();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    error('unknownError', array('error' => $ret));
}

$ret = $storage->testAuthentication();
if ($ret->isError()) {
    if ($ret->getErrorCode() & ERROR_UNIMPLEMENTED) {
	error('configurationError');
    } else if ($ret->getErrorCode() & ERROR_STORAGE_BAD_AUTHENTICATON) {
	error('badStoragePassword');
    } else if ($ret->getErrorCode() & ERROR_STORAGE_FAILURE) {
	error('storageError', array('error' => $ret));
    } else {
	error('unknownError', array('error' => $ret));
    }
    return;
}

/*
 * Ok, we've got a connection to the database.  But we don't know if the
 * database has been created or not, so give the user the option to create it.
 */
if (empty($HTTP_POST_VARS['g2_storeAction'])) {
    message('create');
    return;
} else {
    $storeAction = $HTTP_POST_VARS['g2_storeAction'];
    if ($storeAction == 'Create New Database') {
	$ret = $storage->createStore();
	if ($ret->isError()) {
	    $ret = $ret->wrap(__FILE__, __LINE__);
	    error('storageError', array('error' => $ret));
	    return;
	}
    }
}

message('success');

/*************************************************************
 *
 * Support functions below this point
 *
 *************************************************************/
function error($messageName, $messageData=null) {
    global $message, $gallery;
    global $HTTP_POST_VARS;

    $message = $messageData;
    $message['output'] = ob_get_contents();
    ob_end_clean();

    if (!empty($gallery)) {
	$message['debug'] = $gallery->getDebugBuffer();
    }
    
    if (!empty($HTTP_POST_VARS['g2_password'])) {
	$message['password'] = $HTTP_POST_VARS['g2_password'];
    }

    include(dirname(__FILE__) . '/messages/errorHeader.php');
    include(dirname(__FILE__) . '/messages/' . $messageName . '.php');
    include(dirname(__FILE__) . '/messages/errorFooter.php');
}

function message($messageName, $messageData=null) {
    global $message, $gallery;
    global $HTTP_POST_VARS;

    $message = $messageData;
    $message['output'] = ob_get_contents();
    ob_end_clean();

    $message['debug'] = $gallery->getDebugBuffer();
    if (!empty($HTTP_POST_VARS['g2_password'])) {
	$message['password'] = $HTTP_POST_VARS['g2_password'];
    }

    include(dirname(__FILE__) . '/messages/messageHeader.php');
    include(dirname(__FILE__) . '/messages/' . $messageName . '.php');
    include(dirname(__FILE__) . '/messages/messageFooter.php');
}

function CheckSetupPassword() {
    global $gallery;

    $password = $gallery->getConfig('setup.password');
    return (!empty($password));
}

function CheckPasswordIsCorrect() {
    global $gallery;
    global $HTTP_POST_VARS;

    if (empty($HTTP_POST_VARS['g2_password'])) {
	return false;
    }
    
    return !strcmp($gallery->getConfig('setup.password'),
		   $HTTP_POST_VARS['g2_password']);
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

function InitializeGallery() {
    require(dirname(__FILE__) . '/../init.php');
    return GalleryInit();
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
    if ($fd = $platform->fopen($testfile, "w")) {
	fclose($fd);
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

