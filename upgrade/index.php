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
$stepOrder[] = 'CleanCache';
$stepOrder[] = 'Finished';

foreach ($stepOrder as $stepName) {
    $className = $stepName . 'Step';
    require("steps/$className.class");
}

session_start();

require_once(dirname(__FILE__) . '/../init.php');
$ret = GalleryInitFirstPass(array('debug' => 'buffered',
				  'noDatabase' => 1));
if ($ret->isError()) {
    print $ret->getAsHtml();
    return;
}

/* We want to avoid using the cache */
GalleryDataCache::setFileCachingEnabled(false);

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
    // Load up template data from the current step
    $templateData = array();

    // Round percentage to the nearest 5
    $templateData['percentComplete'] =		  
	(int)((100 * ($stepNumber / (sizeof($steps)-1))) / 5) * 5;
    $templateData['errors'] = array();
    $currentStep->loadTemplateData($templateData);

    // Render our page
    include('templates/MainPage.html');
}

/*
 * We don't store the steps in the session in raw form because that
 * will break in environments where session.auto_start is on since
 * it will try to instantiate the classes before they've been defined
 */
$_SESSION['upgrade_steps'] = serialize($steps);
?>