<?php
/*
 * $RCSfile$
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

/**
 * @version $Revision$ $Date$
 * @package Captcha
 * @author Stefan Ioachim <stefanioachim@gmail.com>
 * @author Bharat Mediratta <bharat@menalto.com>  
 */

/**
 * Implement UserLoginPlugin to present the HTML for the captcha image
 * and an input box for the user to type in the correct value.
 *
 * @package Captcha
 */
class CaptchaLoginPlugin extends UserLoginPlugin {

    /**
     * @see UserLoginPlugin::handleRequestBeforeLogin
     */
    function handleRequestBeforeLogin(&$form) {
	global $gallery;

	$session =& $gallery->getSession();
	$code = $session->get('captcha.key');

	$error = array();
	$success = false;
	if (isset($form['CaptchaLoginPlugin']['word']) &&
	        empty($form['CaptchaLoginPlugin']['word'])) {
	    $error[] = 'form[error][CaptchaLoginPlugin][missing]';
	} else if (isset($form['CaptchaLoginPlugin']['word']) &&
		   $form['CaptchaLoginPlugin']['word'] != $code) {
	    $error[] = 'form[error][CaptchaLoginPlugin][invalid]';
	} else {
	    $success = true;
	}

	return array(GalleryStatus::success(), $error, $success);
    }

    /**
     * @see UserLoginPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	/*
	 * Use the module's failedAttemptThreshold parameter to match against the
	 * captcha.failedAttempts stored in the session to figure out whether or not we need to
	 * show the captcha.
	 */
	list ($ret, $failedAttemptThreshold) =
	    GalleryCoreApi::getPluginParameter('module', 'captcha', 'failedAttemptThreshold');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	$session =& $gallery->getSession();

	$failedAttempts = $session->get('captcha.failedAttempts');
	if (!isset($failedAttempts)) {
	    $failedAttempts = 0;
	}

	if (isset($form['error'])) {
	    $failedAttempts++;
	    $session->put('captcha.failedAttempts', $failedAttempts);
	}

	if ($failedAttempts > $failedAttemptThreshold) {
	    /* Generate a new code */
	    list($usec, $sec) = explode(' ', microtime());
	    srand((float) $sec + ((float) $usec * 100000));
	    $random_num = rand ();
	    $datekey = date('H i s');
	    $rcode = hexdec(md5(GalleryUtilities::getServerVar('HTTP_USER_AGENT') .
				$random_num . $datekey));
	    $code = substr($rcode, 2, 6);
	    $session->put('captcha.key', $code);

	    return array(GalleryStatus::success(),
			 'modules/captcha/templates/CaptchaLoginPlugin.tpl',
			 'modules_captcha');
	} else {
	    /* They haven't failed enough to require the captcha yet */
	    return array(GalleryStatus::success(), null, null);
	}
    }
}
?>