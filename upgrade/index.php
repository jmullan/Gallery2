<?php
/*
 * ATTENTION:
 *
 * If you're seeing this in your browser, and are trying to upgrade Gallery,
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

require_once(dirname(__FILE__) . '/UpgradeStep.class');

/*
 * if gettext isn't enabled, subvert the _() text translation function
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
$stepOrder[] = 'UpgradeCoreModule';
$stepOrder[] = 'UpgradeOtherModules';
$stepOrder[] = 'CleanCache';
$stepOrder[] = 'Finished';

foreach ($stepOrder as $stepName) {
    $className = $stepName . 'Step';
    require("steps/$className.class");
}

session_start();

if (isset($_SESSION['path'])) {
    if ($_SESSION['path'] != __FILE__) {
	/*
	 * Security error!  This session is not valid for this copy of the
	 * installer. Start over.
	 */
	session_unset();
    }
}
$_SESSION['path'] = __FILE__;

require_once(dirname(__FILE__) . '/../bootstrap.inc');
require_once(dirname(__FILE__) . '/../init.inc');
$ret = GalleryInitFirstPass(array('debug' => 'buffered',
				  'noDatabase' => 1));
if ($ret->isError()) {
    print $ret->getAsHtml();
    return;
}

/* We want to avoid using the cache */
GalleryDataCache::setFileCachingEnabled(false);
GalleryDataCache::setMemoryCachingEnabled(false);

/* Check to see if we have a database.  If we don't, then go to the installer */
$storage =& $gallery->getStorage();
list ($ret, $isInstalled) = $storage->isInstalled();
if ($ret->isError() || !$isInstalled) {
    header("Location: ../install/");
}

/* If we don't have our steps in our session, initialize them now. */
if (!isset($_GET['startOver']) && !empty($_SESSION['upgrade_steps'])) {
    $steps = unserialize($_SESSION['upgrade_steps']);
}

if (empty($steps) || !is_array($steps)) {
    $steps = array();
    for ($i = 0; $i < sizeof($stepOrder); $i++) {
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
    $steps[sizeof($steps)-1]->setIsLastStep(true);
}

if (isset($_GET['step'])) {
    $stepNumber = (int)$_GET['step'];
} else {
    $stepNumber = 0;
}

/* Make sure all steps up to the current one are ok */
for ($i = 0; $i < $stepNumber; $i++) {
    if (!$steps[$i]->isComplete() && ! $steps[$i]->isOptional()) {
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
    for ($i = $stepNumber+1; $i < sizeof($steps); $i++) {
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
    $stepsComplete = $stepNumber - ($currentStep->isComplete() ? 0 : 1);
    $templateData['percentComplete'] = (int)((100 * ($stepsComplete / (sizeof($steps)-1))) / 5) * 5;

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
	$html = preg_replace('/href="(.*\?.*)"/', 'href="$1&' . $sid . '"', $html);
    }
    return $html;
}

/*
 * We don't store the steps in the session in raw form because that
 * will break in environments where session.auto_start is on since
 * it will try to instantiate the classes before they've been defined
 */
$_SESSION['upgrade_steps'] = serialize($steps);
?>
