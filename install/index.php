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
 * Copyright (C) 2000-2005 Bharat Mediratta
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

/* Show all errors. */
@ini_set('display_errors', 1);

/*
 * Disable magic_quotes runtime -- it causes problems with legitimate quotes
 * in our SQL, as well as reading/writing the config.php
 */
@ini_set('magic_quotes_runtime', 0);

require_once(dirname(__FILE__) . '/GalleryStub.class');
require_once(dirname(__FILE__) . '/InstallStep.class');
require_once(dirname(dirname(__FILE__)) . '/modules/core/classes/GalleryUtilities.class');

/*
 * If gettext isn't enabled, subvert the _() text translation function
 * and just pass the string on through in English
 */
if (!function_exists('_')) {
    function _($s) {
	return $s;
    }
}

/* Our install steps, in order */
$stepOrder[] = 'Welcome';
$stepOrder[] = 'Authenticate';
$stepOrder[] = 'SystemChecks';
$stepOrder[] = 'Multisite';
$stepOrder[] = 'AdminUserSetup';
$stepOrder[] = 'StorageSetup';
$stepOrder[] = 'DatabaseSetup';
$stepOrder[] = 'CreateConfigFile';
$stepOrder[] = 'InstallCoreModule';
$stepOrder[] = 'InstallOtherModules';
$stepOrder[] = 'Secure';
$stepOrder[] = 'Finished';

foreach ($stepOrder as $stepName) {
    $className = $stepName . 'Step';
    require("steps/$className.class");
}

if (!ini_get('session.auto_start')) {
    session_start();
}

if (!isset($_SESSION['path'])) {
    $_SESSION['path'] = __FILE__;
} else if ($_SESSION['path'] != __FILE__) {
    /* Security error!  This session is not valid for this copy of the installer. Start over. */
    session_unset();
    $_SESSION['path'] = __FILE__;
}

if (function_exists('dgettext') && !empty($_SERVER['HTTP_ACCEPT_LANGUAGE'])) {
    require_once(dirname(dirname(__FILE__)) . '/modules/core/classes/GalleryStatus.class');
    require_once(dirname(dirname(__FILE__)) . '/modules/core/classes/GalleryTranslator.class');
    if (empty($_SESSION['language'])) {
	/* Select language based on preferences sent from browser */
	$_SESSION['language'] = GalleryTranslator::getLanguageCodeFromRequest();
    }
    $gallery = new GalleryStub();
    $translator = new GalleryTranslator();
    $translator->init($_SESSION['language']);
    unset($gallery);
    bindtextdomain('gallery2_install', dirname(__FILE__) . '/locale');
    textdomain('gallery2_install');
    if (function_exists('bind_textdomain_codeset')) {
	bind_textdomain_codeset('gallery2_install', 'UTF-8');
    }
}

/*
 * For reasons unclear to me, register_globals causes the $galleryStub variable to be put into
 * the global context on session_start, which we don't expect or want.  Possibly because we
 * declare "global $galleryStub" when we use it in our step classes.  The $steps variable does not
 * seem to be affected by this.  So unset $galleryStub here to prevent this from causing problems.
 */
unset($galleryStub);

if (!isset($_GET['startOver']) && !empty($_SESSION['install_steps'])) {
    $steps = unserialize($_SESSION['install_steps']);
    if (isset($_SESSION['galleryStub'])) {
	$galleryStub = unserialize($_SESSION['galleryStub']);
    }
}

/* If we don't have our steps in our session, initialize them now. */
if (empty($steps) || !is_array($steps)) {
    $steps = array();
    for ($i = 0; $i < count($stepOrder); $i++) {
	$className = $stepOrder[$i] . 'Step';
	$step = new $className();
	if ($step->isRelevant()) {
	    $step->setIsLastStep(false);
	    $step->setStepNumber($i);
	    $step->setInError(false);
	    $step->setComplete(false);
	    $steps[] = $step;
	}
    }

    /* Don't do this in the loop, since not all steps are relevant */
    $steps[count($steps)-1]->setIsLastStep(true);
}

$stepNumber = isset($_GET['step']) ? (int)$_GET['step'] : 0;

/* Make sure all steps up to the current one are ok */
for ($i = 0; $i < $stepNumber; $i++) {
    if (!$steps[$i]->isComplete() && !$steps[$i]->isOptional()) {
	$stepNumber = $i;
	break;
    }
}
$currentStep =& $steps[$stepNumber];

if (!empty($_GET['doOver'])) {
    $currentStep->setComplete(false);
}

/* If the current step is incomplete, the rest of the steps can't be complete either */
if (!$currentStep->isComplete()) {
    for ($i = $stepNumber+1; $i < count($steps); $i++) {
	$steps[$i]->setComplete(false);
	$steps[$i]->setInError(false);
    }
}

if ($currentStep->processRequest()) {
    /* Load up template data from the current step */
    $templateData = array();

    /* Round percentage to the nearest 5 */
    $templateData['errors'] = array();
    $currentStep->loadTemplateData($templateData);
    $stepsComplete = max($stepNumber - ($currentStep->isComplete() ? 0 : 1), 0);
    $templateData['percentComplete'] = (int)((100 * ($stepsComplete / (count($steps)-1))) / 5) * 5;

    /* Fetch our page into a variable */
    ob_start();
    include(dirname(__FILE__) . '/templates/MainPage.html');
    $html = ob_get_contents();
    ob_end_clean();

    /* Add session ids if we don't have cookies */
    $html = addSessionIdToUrls($html);
    print $html;
}

/**
 * Add the session id to our url, if necessary
 */
function addSessionIdToUrls($html) {
    /*
     * SID is empty if we have a session cookie.
     * If session.use_trans_sid is on then it will add the session id.
     */
    $sid = SID;
    if (!empty($sid) && !ini_get('session.use_trans_sid')) {
	$html = preg_replace('/href="(.*\?.*)"/', 'href="$1&amp;' . $sid . '"', $html);
    }
    return $html;
}

function processAutoCompleteRequest() {
    $path = !empty($_GET['path']) ? $_GET['path'] : '';
    /* Undo the damage caused by magic_quotes */
    if (get_magic_quotes_gpc()) {
	$path = stripslashes($path);
    }
                    
    /* Find all matching paths */
    $dirList = array();
    if (file_exists($path) && is_dir($path) && ($dir = opendir($path))) {
	if ($path{strlen($path)-1} != DIRECTORY_SEPARATOR) {
	    $path .= DIRECTORY_SEPARATOR;
	}
	while (($file = readdir($dir)) !== false) {
	    if ($file == '.' || $file == '..') {
		continue;
	    }
	    $file = $path . $file;
	    if (is_dir($file)) {
		$dirList[] = $file;
	    }
	}
	closedir($dir);
	sort($dirList);
    }

    header("Content-Type: text/plain");
    print implode("\n", $dirList);
}

/*
 * We don't store the steps in the session in raw form because that
 * will break in environments where session.auto_start is on since
 * it will try to instantiate the classes before they've been defined
 */
$_SESSION['install_steps'] = serialize($steps);
if (isset($galleryStub)) {
    $_SESSION['galleryStub'] = serialize($galleryStub);
}
?>
