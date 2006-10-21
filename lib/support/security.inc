<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

if (php_sapi_name() == 'cli') {
    /* We don't apply this security check to command-line PHP */
    return;
}

class GalleryStub {
    var $_hash;
    function setConfig($key, $value) {
	$this->_hash[$key] = $value;
    }

    function getConfig($key) {
	if (isset($this->_hash[$key])) {
	    return $this->_hash[$key];
	}
	return null;
    }

    function setDebug() { }
    function setDebugLogFile() { }
    function setProfile() { }
}

$gallery = new GalleryStub();

/* Load config.php */
if (!defined('GALLERY_CONFIG_DIR')) {
    define('GALLERY_CONFIG_DIR', dirname(dirname(dirname(__FILE__))));
}
if (file_exists(GALLERY_CONFIG_DIR . '/config.php')) {
    include(GALLERY_CONFIG_DIR . '/config.php');
} else {
    $baseUrl = '';
    render('missingConfig');
    exit;
}
if ($baseUrl = $gallery->getConfig('galleryBaseUrl')) {
    $baseUrl .= 'lib/support/';
} else {
    /*
     * This file can get included from a variety of places under lib, so
     * find our way to lib/support/
     */
    $baseUrl = $_SERVER['SCRIPT_NAME'];
    while (basename($baseUrl) != 'lib') {
	$baseUrl = dirname($baseUrl);
    }
    $baseUrl .= '/support/';
}

$setupPassword = $gallery->getConfig('setup.password');
if (empty($setupPassword)) {
    render('missingPassword');
    exit;
}

if (passwordProvided()) {
    if (passwordIsCorrect()) {
	savePasswordCookie();
	redirectBackToSelf();
	exit;
    } else {
	wrongPassword();
	exit;
    }
} else if (!isset($_COOKIE['g2Setup'])) {
    askForPassword();
    exit;
} else if ($_COOKIE['g2Setup'] == md5($setupPassword)) {
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

    header(sprintf('Set-Cookie: g2Setup=%s',
		   md5($gallery->getConfig('setup.password'))));
}

function askForPassword() {
    render('passwordForm');
}

function wrongPassword() {
    render('passwordForm', 'wrongPassword');
}

function redirectBackToSelf() {
    require_once(dirname(__FILE__) . '/../../modules/core/classes/GalleryUrlGenerator.class');
    $urlGenerator = new GalleryUrlGenerator();
    header('Location: ' . $urlGenerator->getCurrentUrl());
}

function render($renderType, $renderSubtype=null) {
    global $baseUrl;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
  <head>
    <title>Security Check</title>
    <link rel="stylesheet" type="text/css" href="<?php print $baseUrl ?>support.css"/>
  </head>
  <body>
     <div id="content">
       <div id="title">
         Security Check
       </div>

       <h2>
	  You are attempting to access a secure section of this Gallery installation.  You can't
	  proceed until you pass the security check.
       </h2>

       <?php if ($renderType == 'missingConfig'): ?>
       <div class="error">
	 You must create a config.php file in the Gallery directory before
	 you can continue configuring the application.  Use the
	 <a href="../../install">installer</a> to create one.
       </div>
       <?php endif; ?>

       <?php if ($renderType == 'missingPassword'): ?>
       <div class="error">
	 You must enter a setup password in your gallery2/config.php file in order
	 to be able to set up Gallery. If your config.php is empty, you should run
	 <a href="../../install">the installer</a> to install your Gallery.
       </div>
       <?php endif; ?>

       <?php if ($renderType == 'passwordForm'): ?>
       <form action="" method="post">
	 <p>
	   In order to verify you, we require you to enter your Gallery setup password.  This is
	   the password you entered when you installed Gallery.  It can be found in your
	   gallery/config.php file like this:
	 </p>
         <pre>
           $gallery-&gt;setConfig('setup.password', '<b>your password here</b>');
         </pre>
         <p>
	   Password:
	   <input type="password" name="g2_password"/>
	   <script type="text/javascript">document.forms[0]['g2_password'].focus();</script>
	   <input type="submit" value="Verify Me"/>
         </p>
         <?php if ($renderSubtype == 'wrongPassword'): ?>
         <div class="error">
           Wrong password!
         </div>
         <?php endif; ?>
       </form>
       <?php endif; ?>
     </div>
  </body>
</html>
<?php
}
?>
