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

class GalleryStub {
    var $_hash;
    function setConfig($key, $value) {
	$this->_hash[$key] = $value;
    }

    function getConfig($key) {
	return $this->_hash[$key];
    }

    function setDebug() { }
    function setDebugLogFile() { }
    function setProfile() { }
}

$gallery = new GalleryStub();

/* Load config.php */
if (file_exists(dirname(__FILE__) . '/../../config.php')) {
    include(dirname(__FILE__) . '/../../config.php');
} else {
    include(dirname(__FILE__) . '/messages/messageHeader.inc');
    include(dirname(__FILE__) . '/messages/missingConfig.inc');
    include(dirname(__FILE__) . '/messages/messageFooter.inc');
    exit;
}

$setupPassword = $gallery->getConfig('setup.password');
if (empty($setupPassword)) {
    include(dirname(__FILE__) . '/messages/messageHeader.inc');
    include(dirname(__FILE__) . '/messages/missingPassword.inc');
    include(dirname(__FILE__) . '/messages/messageFooter.inc');
    exit;
}

if (passwordProvided()) {
    if (passwordIsCorrect()) {
	savePasswordCookie();
	redirectBackToSelf();
	exit;
    } else {
	askForPassword();
	exit;
    }
} else if (!isset($_COOKIE['g2Setup'])) {
    askForPassword();
    exit;
} else if ($_COOKIE['g2Setup'] == md5($setupPassword)) {
    unset($gallery);
    return;
} else {
    askForPassword();
    exit;
}

function passwordProvided() {
    return isset($_POST['g2_password']); 
}

function passwordIsCorrect() {
    global $gallery;
    return $_POST['g2_password'] == $gallery->getConfig('setup.password');
}

function savePasswordCookie() {
    global $gallery;

    $path = preg_replace('|/setup.*|', '/setup', $_SERVER['PHP_SELF']); 
    header(sprintf('Set-Cookie: %s=%s; path=%s',
		   'g2Setup',
		   md5($gallery->getConfig('setup.password')),
		   $path));
}

function askForPassword() {
    global $message, $gallery;

    $message = array();
    if (!empty($_POST['g2_password'])) {
	$message['password'] = $_POST['g2_password'];
    }

    include(dirname(__FILE__) . '/messages/messageHeader.inc');
    include(dirname(__FILE__) . '/messages/passwordForm.inc');
    include(dirname(__FILE__) . '/messages/messageFooter.inc');
}

function redirectBackToSelf() {
    $url = $_SERVER['PHP_SELF'];
    if (isset($_SERVER['QUERY_STRING'])) {
	$url .= '?' . $_SERVER['QUERY_STRING'];
    }
    header(sprintf('Location: %s', $url));
}