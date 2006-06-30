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

/* Show all errors. */
@ini_set('display_errors', 1);

/*
 * Disable magic_quotes runtime -- it causes problems with legitimate quotes
 * in our SQL, as well as reading/writing the config.php
 */
@ini_set('magic_quotes_runtime', 0);

require_once(dirname(__FILE__) . '/UpgradeStep.class');
require_once(dirname(__FILE__) . '/StatusTemplate.class');
require_once(dirname(__FILE__) . '/../bootstrap.inc');

/*
 * If gettext isn't enabled, subvert the _() text translation function
 * and just pass the string on through in English
 */
if (!function_exists('_')) {
    function _($s) {
	return $s;
    }
}

$error = false;

/* Our install steps, in order */
$stepOrder = array();
$stepOrder[] = 'Welcome';
$stepOrder[] = 'Authenticate';
$stepOrder[] = 'SystemChecks';
$stepOrder[] = 'UpgradeCoreModule';
$stepOrder[] = 'UpgradeOtherModules';
$stepOrder[] = 'CleanCache';
$stepOrder[] = 'Finished';

foreach ($stepOrder as $stepName) {
    $className = $stepName . 'Step';
    require("steps/$className.class");
}

/* Prevent session fixation attack by only accepting sessionIds of existing sessions */
$sessionName = session_name();
$sessionId = GalleryUtilities::getRequestVariablesNoPrefix($sessionName);
if (empty($sessionId)) {
    $sessionId = !empty($_COOKIE[$sessionName]) ? $_COOKIE[$sessionName] : '';
}
/* Remember whether cookies are supported */
areCookiesSupported();
/* Sanitize the sessionId */
if (!empty($sessionId)) {
    if (function_exists('preg_replace')) {
	$sessionId = preg_replace('/[^a-zA-Z0-9]/', '', $sessionId);
    } else {
	$sessionId = ereg_replace('/[^a-zA-Z0-9]/', '', $sessionId);
    }
    /* Make sure we don't use invalid data at a later point */
    foreach (array($_GET, $_POST, $_REQUEST, $_COOKIE) as $superGlobal) {
	unset($superGlobal[$sessionName]);
    }
    /*
     * md5 has a 128 bit (32 * 4bit) string, but we want to allow for other possible
     * hash functions too which possibly have hash strings of only 10 characters
     */
    if (strlen($sessionId) >= 10) {
	session_id($sessionId);
    }
}

if (!@ini_get('session.save_handler')) {
    @ini_set('session.save_handler', 'files');
    session_start();
} else if (!ini_get('session.auto_start')) {
    session_start();
} /* In case of session.auto_start we can't prevent showing errors for invalid sessionIds */

if (!isset($_SESSION['path'])) {
    /* Empty session -> either new or a session fixation attack. Better regenerate */
    regenerateSession();
    $_SESSION['path'] = __FILE__;
} else if ($_SESSION['path'] != __FILE__) {
    /* Security error!  This session is not valid for this copy of the upgrader. Start over. */
    regenerateSession();
    session_unset();
    $_SESSION['path'] = __FILE__;
}

require_once(dirname(__FILE__) . '/../init.inc');
/* Check if config.php is ok */
$storageConfig = @$gallery->getConfig('storage.config');
if (!empty($storageConfig)) {
    /* We want to avoid using the cache */
    GalleryDataCache::setFileCachingEnabled(false);

    $ret = GalleryInitFirstPass(array('debug' => 'buffered', 'noDatabase' => 1));
    if ($ret) {
	print $ret->getAsHtml();
	return;
    }

    $translator =& $gallery->getTranslator();
    if (!$translator->canTranslate()) {
	unset($translator);
    } else {
	if (empty($_SESSION['language'])) {
	    $_SESSION['language'] = GalleryTranslator::getLanguageCodeFromRequest();
	}
	$translator->init($_SESSION['language'], true);
	/* Select domain for translation */
	bindtextdomain('gallery2_upgrade', dirname(__FILE__) . '/locale');
	textdomain('gallery2_upgrade');
	if (function_exists('bind_textdomain_codeset')) {
	    bind_textdomain_codeset('gallery2_upgrade', 'UTF-8');
	}
	/* Set the appropriate charset in our HTTP header */
	if (!headers_sent()) {
	    header('Content-Type: text/html; charset=UTF-8');
	}
    }

    /* Preallocate at least 5 minutes for the upgrade */
    $gallery->guaranteeTimeLimit(300);

    /* Check to see if we have a database.  If we don't, then go to the installer */
    $storage =& $gallery->getStorage();
    list ($ret, $isInstalled) = $storage->isInstalled();
    if ($ret || !$isInstalled) {
	$error = true;
    }
} else {
    $error = true;
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

if (!$error) {
    $currentStep =& $steps[$stepNumber];
} else {
    require_once(dirname(__FILE__) . '/steps/RedirectToInstallerStep.class');
    $currentStep =& new RedirectToInstallerStep();
}

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

    /* Render the output */
    $template = new StatusTemplate();
    $template->renderHeaderBodyAndFooter($templateData);
}

/**
 * Find admin user and set as active user
 * @return object GalleryStatus a status code
 */
function selectAdminUser() {
    global $gallery;

    list ($ret, $siteAdminGroupId) =
	GalleryCoreApi::getPluginParameter('module', 'core', 'id.adminGroup');
    if ($ret) {
	return $ret;
    }
    list ($ret, $adminUserInfo) = GalleryCoreApi::fetchUsersForGroup($siteAdminGroupId, 1);
    if ($ret) {
	return $ret;
    }
    if (empty($adminUserInfo)) {
	return GalleryCoreApi::error(ERROR_MISSING_VALUE);
    }
    $adminUserInfo = array_keys($adminUserInfo);
    list ($ret, $adminUser) = GalleryCoreApi::loadEntitiesById($adminUserInfo[0]);
    if ($ret) {
	return $ret;
    }

    $gallery->setActiveUser($adminUser);
    $session =& $gallery->getSession();
    $session->put('isUpgrade', true);
    return null;
}

/**
 * Mini url generator for upgrader
 */
function generateUrl($uri, $print=true) {
    if (strncmp($uri, 'index.php', 9) && strncmp($uri, '../' . GALLERY_MAIN_PHP, 11)) {
	/* upgrade/images/*, upgrade/styles/*, ... URLs */
	global $gallery;
	/* Add @ here in case we haven't yet upgraded config.php to include galleryBaseUrl */
	$baseUrl = @$gallery->getConfig('galleryBaseUrl');
	if (!empty($baseUrl)) {
	     $uri = $baseUrl . 'upgrade/' . $uri;
	}
    } else if (!strncmp($uri, 'index.php', 9)) {
	/* If session.use_trans_sid is on then it will add the session id. */
	if (!areCookiesSupported() && !ini_get('session.use_trans_sid')) {
	    /*
	     * Don't use SID since it's a constant and we change (regenerate) the session id
	     * in the request
	     */
	    $sid = session_name() . '=' . session_id();
	    $uri .= !strpos($uri, '?') ? '?' : '&amp;';
	    $uri .= $sid;
	}
    }

    if ($print) {
	print $uri;
    }
    return $uri;
}

/**
 * Regenerate the session id to prevent session fixation attacks
 * Must be called before starting to output any data since it tries to send a cookie
 */
function regenerateSession() {
    /* 1. Generate a new session id */
    $newSessionId = md5(uniqid(substr(rand() . serialize($_REQUEST), 0, 114)));
    $sessionData = array();
    if (!empty($_SESSION) && is_array($_SESSION)) {
	foreach ($_SESSION as $key => $value) {
	    $sessionData[$key] = $value;
	}
    }
    /* 2. Delete the old session */
    session_unset();
    session_destroy();
    /* Create the new session with the old data, send cookie */
    session_id($newSessionId);
    $sessionName = session_name();
    /* Make sure we don't use invalid data at a later point */
    foreach (array($_GET, $_POST, $_REQUEST, $_COOKIE) as $superGlobal) {
	unset($superGlobal[$sessionName]);
    }
    session_start();
    foreach ($sessionData as $key => $value) {
	$_SESSION[$key] = $value;
    }
}

/**
 * Are cookies supported by the current user-agent?
 */
function areCookiesSupported() {
    static $areCookiesSupported;

    /* Remember the state since we might unset $_COOKIE */
    if (!isset($areCookiesSupported)) {
	$areCookiesSupported = !empty($_COOKIE[session_name()]);
    }

    return $areCookiesSupported;
}

/*
 * We don't store the steps in the session in raw form because that
 * will break in environments where session.auto_start is on since
 * it will try to instantiate the classes before they've been defined
 */
$_SESSION['upgrade_steps'] = serialize($steps);
?>
