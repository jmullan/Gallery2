<?php
/*
 * ATTENTION:
 *
 * If you're seeing this in your browser, and are trying to install Gallery,
 * you either do not have PHP installed, or if it is installed, it is not
 * properly enabled. Please visit the following page for assistance:
 *
 *    http://gallery.sourceforge.net/
 *
 * ----------------------------------------------------------------------------
 *
 * $Id$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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

//XXX ENABLED FOR DEBUGGING
@ini_set('display_errors', 1);

session_start();

// if gettext isn't enabled, subvert the _() text translation function
// and just pass the string on through in English
if (!function_exists('_')) {
    function _($s) {
	return $s;
    }
}

if (isset($_GET['step'])) {
    $step = $_GET['step'];
} else {
    $step = 0;
}

// steps and status: each step's status is true if it's been completed (though
// authentication is re-checked at every step)
$navbar = '';
$navtext = array (_('Welcome'),
		  _('Authenticate'),
		  _('Install Checks'),
		  _('System Checks'),
		  _('Admin User Setup'),
		  _('Storage Setup'),
		  _('Database Setup'),
		  _('Finish'));
$status = array();
$visited = array();
foreach (array_keys($navtext) as $curr) {
    array_push($status, false);
    array_push($visited, false);
}
if (isset($_SESSION['status'])) {
    $status = $_SESSION['status'];
}
if (isset($_SESSION['visited'])) {
    $visited = $_SESSION['visited'];
}
$status[0] = true;
$visited[0] = true;

// authentication key download
if ($step == 1 && isset($_GET['action']) && $_GET['action'] == 'authDownload') {
    if (isset($_SESSION['auth'])) {
	$auth = $_SESSION['auth'];
	$auth .= "\r\n";
	header("Content-Type: text/plain");
	header("Content-Length: " . strlen($auth));
	header("Content-Description: Download login.txt to your computer.");
	header("Content-Disposition: attachment; filename=login.txt");
	print $auth;
	exit;
    } else {
	header("Location: index.php?step=1&auth=nosession");
    }
}

// authenticate
$authenticated = false;
if ($step > 1 || ($step == 1 && (!isset($_GET['error']) && ((isset($_GET['action']) && !($_GET['action'] === 'new')) || !isset($_GET['action']))))) {
    $authFile = dirname(__FILE__) . '/login.txt';
    if (!file_exists($authFile)) {
	header('Location: index.php?step=1&error=nofile');
    } elseif (!is_readable($authFile)) {
	header('Location: index.php?step=1&error=noperms');
    } elseif (!isset($_SESSION['auth'])) {
	header('Location: index.php?step=1&error=nosession');
    } else {
	$fileAuth = trim(file_get_contents($authFile));
	if (!($fileAuth === $_SESSION['auth'])) {
	    header('Location: index.php?step=1&error=nomatch');
	} else {
	    $authenticated = true;
	    $status[1] = true;
	}
    }
}

// pre-header functionality
// XXX split this into unique functions
$errorMsg = array();
if ($step == 1) {
    if (isset($_GET['error'])) {
	$error = $_GET['error'];
	// uh oh...
	if ($error === 'nofile') {
	    $installerDir = str_replace($_SERVER['DOCUMENT_ROOT'], '', dirname(__FILE__));
	    array_push($errorMsg, _("<b>Error:</b> could not locate <b>login.txt</b>. Please place it in your <tt>$installerDir/</tt> directory."));
	    $keyGen = false;
	} elseif ($error === 'noperms') {
	    array_push($errorMsg, _('<b>Error:</b> your <b>login.txt</b> file is not readable. Please give Gallery read permissions on the file.'));
	    $keyGen = false;
	} elseif ($error === 'nosession') {
	    array_push($errorMsg, _('<b>Error:</b> session expired. Please download a new authentication string from below and try again.'));
	    $keyGen = true;
	} elseif ($error === 'nomatch') {
	    array_push($errorMsg, _('<b>Error:</b> your <b>login.txt</b> key does not match correctly. Please download a new authentication string from below and try again.'));
	    $keyGen = true;
	}
    } elseif ($authenticated) {
	$keyGen = false;
    } else {
	$keyGen = true;
    }
    
    if ($keyGen == true || !isset($_SESSION['auth'])) {
	for ($len=64, $rand=''; strlen($rand) < $len;
	     $rand .= chr(!mt_rand(0,2) ? mt_rand(48,57) : (!mt_rand(0,1) ? mt_rand(65,90) : mt_rand(97,122))));
	$rand = md5($rand);
	$_SESSION['auth'] = $rand;
    } else {
	$rand = $_SESSION['auth'];
    }
} elseif ($step == 2) {
    $status[$step] = true;
} elseif ($step == 3) {
    $status[$step] = true;
} elseif ($step == 4) {
    if (isset($_GET['action']) && $_GET['action'] === 'create') {
	$status[$step] = false;
    }
    if (isset($_POST['uname']) && isset($_POST['passA']) && isset($_POST['passB'])) {
	if (empty($_POST['uname'])) {
	    array_push($errorMsg, _('Error: you must enter a username!'));
	} else {
	    $_SESSION['uname'] = $_POST['uname'];
	}
	if (empty($_POST['passA']) || empty($_POST['passB'])) {
	    if (empty($_POST['passA']) && empty($_POST['passB'])) {
		array_push($errorMsg, _('Error: you must enter a password!'));
	    } else {
		array_push($errorMsg, _('Error: you must enter your password twice.'));
		$_SESSION['passA'] = $_POST['passA'];
		$_SESSION['passB'] = $_POST['passB'];
	    }
	} elseif ($_POST['passA'] !== $_POST['passB']) {
	    array_push($errorMsg, _('Error: passwords do not match. Please enter them again.'));
	} else {
	    $_SESSION['passA'] = $_POST['passA'];
	    $_SESSION['passB'] = $_POST['passB'];
	}
	if (count($errorMsg) == 0) {
	    $status[$step] = true;
	}
    }
} elseif ($step == 5) {
    if (isset($_GET['action']) && $_GET['action'] === 'create') {
	$status[$step] = false;
    }
    if (isset($_POST['dir'])) {
	$dir = $_POST['dir'];
	$_SESSION['dir'] = $dir;
	if (empty($dir)) {
	    array_push($errorMsg, _('Error: you must specify a data directory.'));
	} else {
	    if (!is_dir($dir)) {
		//$tmp = umask(0022);
		//umask($tmp);
		// XXX implement auto-create on request
		array_push($errorMsg, _('Error: the directory you specified does not exist. Please create it.'));
	    } else {
		if (!is_readable($dir)) {
		    array_push($errorMsg, _("Error: Gallery cannot access the directory you specified. Please change its permissions."));
		} elseif (!is_writable($dir) || !is_executable($dir)) {
		    array_push($errorMsg, _("Error: Gallery cannot write to the directory you specified. Please change its permissions."));
		}
	    }
	}
	if (count($errorMsg) == 0) {
	    $status[$step] = true;
	}
    }
} elseif ($step == 6) {
    
    $type         = isset($_POST['type'])         ? $_POST['type']         : 'mysqlt';
    $hostname     = isset($_POST['hostname'])     ? $_POST['hostname']     : 'localhost';
    $username     = isset($_POST['username'])     ? $_POST['username']     : 'root';
    $password     = isset($_POST['password'])     ? $_POST['password']     : '';
    $database     = isset($_POST['database'])     ? $_POST['database']     : 'gallery2';
    $tablePrefix  = isset($_POST['tablePrefix'])  ? $_POST['tablePrefix']  : 'g2_';
    $columnPrefix = isset($_POST['columnPrefix']) ? $_POST['columnPrefix'] : 'g_';
    
    $_SESSION['db'] = array ('type'         => $type,
			     'hostname'     => $hostname,
			     'username'     => $username,
			     'password'     => $password,
			     'database'     => $database,
			     'tablePrefix'  => $tablePrefix,
			     'columnPrefix' => $columnPrefix
			     );
    
    if (empty($type)) {
	array_push($errorMsg, "Error: you must select a database type.");
    }
    if (empty($hostname)) {
	array_push($errorMsg, "Error: you must specify a database host.");
    }
    if (empty($username)) {
	array_push($errorMsg, "Error: you must specify a database username.");
    }
    if (empty($database)) {
	array_push($errorMsg, "Error: you must specify a database name.");
    }
    
    if (isset($_GET['action']) && $_GET['action'] === 'create') {
	$status[$step] = count($errorMsg) == 0 ? true : false;
    }
}

if ($step == 7 || ($status[7] && count($errorMsg) == 0 && isset($_GET['action']) && $_GET['action'] === 'create')) {
    writeConfigFile();
}

// make percentage a nice round multiple of 5
$numDone = array_sum($status) - 1;
if (0 == count($navtext) || $numDone < 1) {
    $percentage = 0;
} else {
    $percentage = round((100 * ($numDone) / (count($status) - 1)) / 5) * 5;
}

printNavBar();

// this can be cleaned up
include(dirname(__FILE__) . '/head.inc');
if ($step < 1) {
    Welcome();
} elseif ($step == 1) {
    Authenticate($rand);
} elseif ($step == 2) {
    InstallCheck();
} elseif ($step == 3) {
    SystemCheck();
} elseif ($step == 4) {
    AdminSetup();
} elseif ($step == 5) {
    StorageSetup();
} elseif ($step == 6) {
    DatabaseSetup();
} elseif ($step == 7) {
    Finish();
} else {
    Welcome();
}

$visited[$step] = true;
$_SESSION['status'] = $status;
$_SESSION['visited'] = $visited;

function Welcome() {
    global $content, $navbar, $percentage, $step, $status, $errorMsg;
	
    $content = 'welcome.inc';    
    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function Authenticate($rand) {
    global $content, $navbar, $percentage, $step, $status, $errorMsg, $authenticated;

    $content = 'authenticate.inc';
    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function InstallCheck() {
    global $content, $navbar, $percentage, $step, $status, $errorMsg;
	
    $content = 'installCheck.inc';
    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function SystemCheck() {
    global $content, $navbar, $percentage, $step, $status, $errorMsg;
	
    $errors = array();
	
    if (phpversion() < '4.1.0') {
	$error['oldPhp'] = true;
    }
    if (!CheckFileDirective()) {
	$error['brokenFile'] = true;
    }

    $content = 'systemCheck.inc';

    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function AdminSetup() {
    global $content, $navbar, $percentage, $step, $status, $errorMsg;

    $content = 'adminSetup.inc';
    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function StorageSetup() {
    global $content, $navbar, $percentage, $step, $status, $errorMsg;

    $content = 'storageSetup.inc';
    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function DatabaseSetup() {
    global $content, $navbar, $percentage, $step, $status, $errorMsg;

    $content = 'databaseSetup.inc';
    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function Finish() {
    global $content, $navbar, $percentage, $step, $status, $errorMsg;

    $content = 'finish.inc';
    include(dirname(__FILE__) . '/body.inc');
    include(dirname(__FILE__) . '/foot.inc');
}

function writeConfigFile() {

    global $status, $errorMsg;
    $status[7] = 0;
    
    $configFilePath = realpath(dirname(__FILE__) . '/../config.php');
    $configText = '';
    
    if (is_file($configFilePath)) {
	if (!is_readable($configFilePath)) {
	    array_push($errorMsg, "Error: Unable to read the <b>config.php</b> configuration file in your <tt>gallery</tt> directory. Please change its permissions.");
	} elseif (!is_writable($configFilePath)) {
	    array_push($errorMsg, "Error: Unable to write to the <b>config.php</b> configuration file in your <tt>gallery</tt> directory. Please change its permissions.");
	}
    } else {
 	if (!is_writable(dirname($configFilePath))) {
	    print "moo";
	    array_push($errorMsg, "Error: Unable to create <b>config.php</b> in your <tt>gallery</tt> directory. Make sure that Gallery has write permissions for that directory, or please create a <b>config.php</b> file there and make sure Gallery can write to it.");
	}
    }
    
    if (count($errorMsg) == 0) {
	if (!$f = @fopen($configFilePath, 'wt')) {
	    array_push($errorMsg, "Error: Unable to create <b>config.php</b> in your <tt>gallery</tt> directory. Make sure that Gallery has write permissions for that directory, or please create a <b>config.php</b> file there and make sure Gallery can write to it.");
	} else {
	    // XXX need some for() loop action on this razzmatazz
	    $g = @fopen('text/configHeader.inc', 'rt');
	    $configText .= fread($g, filesize('text/configHeader.inc'));
	    fclose($g);
	    $configText .= "// [setup.password] Initial password for the 'admin' user\n";
	    $configText .= "\$gallery->setConfig('setup.password', '{$_SESSION['passA']}');\n\n";
	    $configText .= "// [data.gallery.base] Path to Gallery data storage directory\n";	    
	    $configText .= "\$gallery->setConfig('data.gallery.base', '{$_SESSION['dir']}');\n\n";
	    $configText .= "// [storage.type] Data storage mechanism (currently 'database' only) \n";
	    $configText .= "\$gallery->setConfig('storage.type', 'database');\n\n";
	    $configText .= "// [storage.config] Data storage configuration settings\n";
	    $configText .= "\$storeConfig['type'] = '{$_SESSION['db']['type']}';\n";
	    $configText .= "\$storeConfig['hostname'] = '{$_SESSION['db']['hostname']}';\n";
	    $configText .= "\$storeConfig['database'] = '{$_SESSION['db']['database']}';\n";
	    $configText .= "\$storeConfig['username'] = '{$_SESSION['db']['username']}';\n";
	    $configText .= "\$storeConfig['password'] = '{$_SESSION['db']['password']}';\n";
	    $configText .= "\$storeConfig['tablePrefix'] = '{$_SESSION['db']['tablePrefix']}';\n";
	    $configText .= "\$storeConfig['columnPrefix'] = '{$_SESSION['db']['columnPrefix']}';\n";
	    $configText .= "\$gallery->setConfig('storage.config', \$storeConfig);\n\n";
	    $configText .= "// [debug] Debugging settings (intended for developers)\n";
	    $configText .= "\$gallery->setDebug(false);\n\n";
	    $g = @fopen('text/configFooter.inc', 'rt');
	    $configText .= fread($g, filesize('text/configHeader.inc'));
	    fclose($g);
	    fwrite($f, $configText);
	    fclose($f);
	}
    }

    if (count($errorMsg) == 0) {
	$status[7] = true;
    }
}

function printNavBar() {
	
    global $navbar, $navtext, $status, $visited;
	
    // XXX need to modify for RTL
    $navbar .= "<ol>\n";
    foreach (array_keys($navtext) as $step) {
	if ($step != 0) {
	    $navbar .= "\n";
	}
	$navbar .= "<li class=\"navitem\">\n";
	if ($step == 0) {
	    $num = '&nbsp;';
	} else {
	    $num = $step;
	}
	$navbar .= "<span class=\"nav_num\">$num</span>&nbsp;<span class=\"nav_text\">";
	if ($step < 1 || $status[$step-1] || $visited[$step]) {
	    $navbar .= "<a href=\"index.php?step=$step\">$navtext[$step]</a>";
	} else {
	    $navbar .= $navtext[$step];
	}
	$navbar .= '</span>';
	if ($step > 0) {
	    if ($status[$step]) {
		$navbar .= " <span class=\"success\">&#10003;</span>";
	    } elseif ($visited[$step]) {
		$navbar .= " <span class=\"error\">&#10007;</span>";
	    }
	}
	$navbar .= "</li>\n";
    }
    $navbar .= "</ol>\n";
}

function CheckFileDirective() {
    if (strstr(__FILE__, 'install/index.php') ||
	strstr(__FILE__, 'install\\install.php')) {
	return 1;
    } else {
	return 0;
    }
}

?>
