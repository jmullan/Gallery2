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

class GalleryStub {
    var $_hash;
    var $_debug;
    function setConfig($key, $value) {
	$this->_hash[$key] = $value;
    }
    
    function getConfig($key) {
	if (isset($this->_hash[$key])) {
	    return $this->_hash[$key];
	}
	return null;
    }
    
    function setDebug($value) {
	$this->_debug = $value;
    }

    function getDebug() {
	return $this->_debug;
    }
    
    function setDebugLogFile() { }
}

$gallery = new GalleryStub();

// load in config.php if there
$configFile = dirname(__FILE__) . '/../config.php';
if (is_file($configFile) && is_readable($configFile)) {
    require_once($configFile);
}

class InstallStep {
    var $_stepNumber;
    var $_isComplete;
    var $_isInError;
    
    function isComplete() {
	return $this->_isComplete;
    }

    function setComplete($complete) {
	$this->_isComplete = $complete;
    }

    function canBeVisited() {
	return true;
    }

    function setInError($inError) {
	$this->_isInError = $inError;
    }

    function isInError() {
	return $this->_isInError;
    }

    function stepName() {
	return _('Unknown');
    }

    function setStepNumber($stepNumber) {
	$this->_stepNumber = $stepNumber;
    }
    
    function getStepNumber() {
	return $this->_stepNumber;
    }

    function loadTemplateData(&$templateData) {
	return null;
    }

    function getActions() {
	return array();
    }

    function setIsLastStep($lastStep) {
	$this->_isLastStep = $lastStep;
    }

    function isLastStep() {
	return $this->_isLastStep;
    }

    function loadGalleryObject(&$gallery) {
    }

    function sanitize($string) {
	if (get_magic_quotes_gpc()) {
	    $string = stripslashes($string);
	}
	return $string;
    }
}

// if gettext isn't enabled, subvert the _() text translation function
// and just pass the string on through in English
if (!function_exists('_')) {
    function _($s) {
	return $s;
    }
}

$stepOrder[] = 'Welcome';
$stepOrder[] = 'Authenticate';
$stepOrder[] = 'InstallChecks';
$stepOrder[] = 'SystemChecks';
$stepOrder[] = 'AdminUserSetup';
$stepOrder[] = 'StorageSetup';
$stepOrder[] = 'DatabaseSetup';
$stepOrder[] = 'CreateConfigFile';

foreach ($stepOrder as $stepName) {
    $className = $stepName . 'Step';
    require("steps/$className.class");
}

session_start();

// If we don't have our steps in our session, initialize them now.
if (!isset($_GET['startOver']) && isset($_SESSION['steps'])) {
    $steps =& $_SESSION['steps'];
} else {
    for ($i = 0; $i < sizeof($stepOrder); $i++) {
	$className = $stepOrder[$i] . 'Step';
	$step = new $className();
	$step->setStepNumber($i);
	$step->setInError(false);
	$step->setComplete(false);
	$step->setIsLastStep($i == sizeof($stepOrder) - 1);
	$steps[] = $step;
    }
    $_SESSION['steps'] =& $steps;
}

if (isset($_GET['step'])) {
    $stepNumber = (int)$_GET['step'];
} else {
    $stepNumber = 0;
}

// Make sure all steps up to the current one are ok and load our gallery object
for ($i = 0; $i < $stepNumber; $i++) {
    if ($steps[$i]->isComplete()) {
	$steps[$i]->loadGalleryObject($gallery);
    } else {
	$stepNumber = $i;
	break;
    }
}
$currentStep =& $steps[$stepNumber];

// Load up template data from the current step
$templateData = array();

// Round percentage to the nearest 5
$templateData['percentComplete'] =		  
    (int)((100 * ($stepNumber / sizeof($steps))) / 5) * 5;
$templateData['errors'] = array();
$templateData['installerDir'] =
    str_replace($_SERVER['DOCUMENT_ROOT'], '', dirname(__FILE__));
$currentStep->loadTemplateData($templateData);

// Render our page
include('templates/MainPage.html');
?>

