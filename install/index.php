<?php
/*
 * ATTENTION:
 *
 * If you're seeing this in your browser, and are trying to install Gallery,
 * you either do not have PHP installed, or if it is installed, it is not
 * properly enabled. Please visit the following page for assistance:
 *
 * http://gallery.sourceforge.net/
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

if (!function_exists('_')) {
	function _($s) {
		return $s;
	}
}

if (isset($_GET['authenticate'])) {
	$auth = $_GET['authenticate'];
	if (isset($_SESSION['auth']) && $auth === $_SESSION['auth']) {
		$auth .= "\r\n";
		header("Content-Type: text/plain");
		header("Content-Length: " . strlen($auth));
		header("Content-Description: Download login.txt to your computer.");
		header("Content-Disposition: attachment; filename=login.txt");
		print $auth;
		exit;
	} else {
		header("Location: index.php?step=1&auth=nomatch");
	}
}

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
foreach (array_keys($navtext) as $curr) {
	array_push($status, false);
}
if (isset($_SESSION['status'])) {
	$status = $_SESSION['status'];
}

printNavBar();
if (isset($_GET['step'])) {
	$step = $_GET['step'];
} else {
	$step = 0;
}

// make percentage a nice round multiple of 5
if (0 == count($navtext) || $step < 2) {
	$percentage = 0;
} else {
	$percentage = round((100 * ($step - 1) / (count($navtext) - 2)) / 5) * 5;
}

// items to include in HTTP headers
$rand = '';
if ($step == 1 && !isset($_GET['auth'])) {
	for ($len=64, $rand=''; strlen($rand) < $len; $rand .= chr(!mt_rand(0,2) ? mt_rand(48,57) : (!mt_rand(0,1) ? mt_rand(65,90) : mt_rand(97,122))));
	$rand = md5($rand);
	$_SESSION['auth'] = $rand;
} elseif ($step == 2) {
	$authFile = dirname(__FILE__) . '/../login.txt';
	if (!file_exists($authFile)) {
		header("Location: index.php?step=1&auth=nofile");
	} elseif (!is_readable($authFile)) {
		header("Location: index.php?step=1&auth=noperms");
	} elseif (!isset($_SESSION['auth'])) {
		header("Location: index.php?step=1&auth=nocookie");
	} else {
		$fileAuth = trim(file_get_contents($authFile));
		if (!($fileAuth === $_SESSION['auth'])) {
			header("Location: index.php?step=1&auth=nomatch");
		}
	}
}

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

$_SESSION['status'] = $status;

function Welcome() {
	global $content, $navbar, $percentage, $step, $status;
	
	$content = 'welcome.inc';
	include(dirname(__FILE__) . '/body.inc');
	include(dirname(__FILE__) . '/foot.inc');
	
	$status[$step] = true;
}

function Authenticate($rand) {
	global $content, $navbar, $percentage, $step, $status;
	
	$content = 'authenticate.inc';
	include(dirname(__FILE__) . '/body.inc');
	include(dirname(__FILE__) . '/foot.inc');
	
	$status[$step] = true;
}

function InstallCheck() {
	global $content, $navbar, $percentage, $step, $status;
	
	$content = 'installCheck.inc';
	include(dirname(__FILE__) . '/body.inc');
	include(dirname(__FILE__) . '/foot.inc');
}

function SystemCheck() {
	global $content, $navbar, $percentage, $step, $status;
	
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
	global $content, $navbar, $percentage, $step, $status;

	$content = 'adminSetup.inc';
	include(dirname(__FILE__) . '/body.inc');
	include(dirname(__FILE__) . '/foot.inc');
}

function StorageSetup() {
	global $content, $navbar, $percentage, $step, $status;

	$content = 'storageSetup.inc';
	include(dirname(__FILE__) . '/body.inc');
	include(dirname(__FILE__) . '/foot.inc');
}

function DatabaseSetup() {
	global $content, $navbar, $percentage, $step, $status;

	$content = 'databaseSetup.inc';
	include(dirname(__FILE__) . '/body.inc');
	include(dirname(__FILE__) . '/foot.inc');
}

function Finish() {
	global $content, $navbar, $percentage, $step, $status;

	$content = 'finish.inc';
	include(dirname(__FILE__) . '/body.inc');
	include(dirname(__FILE__) . '/foot.inc');
}


function printNavBar() {
	
	global $navbar;
	global $navtext;
	global $status;
	
	// XXX need to modify for RTL
	$navbar .= "<center><div style=\"text-align: center; align: center; width: 85%; padding-bottom: 20px;\">\n";
	foreach (array_keys($navtext) as $step) {
		if ($step != 0) {
			$navbar .= "<div class=\"nav_arrow\">&rarr;</div>\n";
		}
		$navbar .= "<div class=\"navitem\">\n";
		if ($step == 0) {
			$num = '&nbsp;&nbsp;';
		} else {
			$num = $step;
		}
		
		$navbar .= "<span class=\"nav_num\">$num</span><span class=\"nav_text\"><a href=\"index.php?step=$step\">$navtext[$step]</a></span>\n";
		$navbar .= "</div>\n";
	}
	$navbar .= "</div>\n";
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
