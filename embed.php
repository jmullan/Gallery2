<?php
/*
 * $RCSfile$
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
/**
 * @package GalleryMain
 * @version $Revision$ $Date$
 * @author Alan Harder <alan.harder@sun.com>
 */

define('G2_EMBED', 1);
require(dirname(__FILE__) . '/main.php');

class GalleryEmbed {

    /**
     * Initialize Gallery; must be called before other GalleryEmbed methods can be used.
     *
     * @param string URI to access G2 via CMS application (example: index.php?module=gallery2)
     * @param string relative path from CMS (dir with embedUri) to G2 base dir
     * @param string URI for redirect to CMS login view (example: /cms/index.php)
     * @param string (optional) To support cookieless browsing, pass in key=value for CMS
                      session key and session id value to be added as query parameter in urls
     * @param string (optional) To support cookieless browsing, pass in G2 session id (when
     *                cookies not in use, CMS must track this value between requests)
     * @return array object GalleryStatus a status object
     *               string G2 session id
     * @static
     */
    function init($embedUri, $relativeG2Path, $loginRedirect,
		  $embedSessionString=null, $g2SessionId=null) {
	$ret = GalleryInitFirstPass(
			  array('embedUri' => $embedUri, 'relativeG2Path' => $relativeG2Path,
				'SID' => $g2SessionId, 'embedSessionString' => $embedSessionString));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	GalleryCapabilities::set('login', false);
	GalleryCapabilities::set('loginRedirect', array('href' => $loginRedirect));
	global $gallery;
	$session =& $gallery->getSession();
	return array(GalleryStatus::success(), $session->getId());
    }

    /**
     * Process the G2 request.
     * Return value contains 'isDone'=>true if output has already been sent
     * (redirect, or output from G2 immediate view like core:DownloadItem) and
     * CMS should not send any additional output.  If isDone is false then check
     * headHtml and bodyHtml keys for content to display via CMS.
     *
     * @param string username of active user (null or empty for anonymous/guest user)
     * @return array ('isDone' => boolean,
     *                [optional: 'headHtml' => string, 'bodyHtml' => string])
     * @static
     */
    function handleRequest($activeUserName) {
	$ret = GalleryEmbed::_checkActiveUser($activeUserName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryMain(true);
    }

    /**
     * Ensure G2 session has same active user as CMS session.
     * @param string username of active user (null or empty for anonymous/guest user)
     * @return object GalleryStatus a status code
     * @private
     */
    function _checkActiveUser($activeUserName) {
	global $gallery;
	$session =& $gallery->getSession();

	list ($ret, $anonymousUserId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$g2UserName = null;
	$g2UserId = $session->get('core.id.activeUser');
	if (!empty($g2UserId) && $g2UserId == $anonymousUserId) {
	    $g2UserId = null; // Empty for anonymous/guest
	}
	if (!empty($g2UserId)) {
	    list ($ret, $user) = GalleryCoreApi::loadEntitiesById($g2UserId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $g2UserName = $user->getUserName();
	}

	if ( (empty($activeUserName) && empty($g2UserName)) || ($activeUserName == $g2UserName) ) {
	    // All is ok..
	} else if (empty($activeUserName)) {
	    // Logout..
	    $ret = $session->reset();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	} else {
	    // Set G2 active user..
	    list ($ret, $user) = GalleryCoreApi::fetchUserByUserName($activeUserName);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $session->put('core.id.activeUser', $user->getId());
	}
	return GalleryStatus::success();
    }

    /**
     * Reset the G2 session.
     * This is the only GalleryEmbed method that should be called without a prior init().
     *
     * @return object GalleryStatus a status object
     * @static
     */
    function logout() {
	require_once(dirname(__FILE__) . '/modules/core/classes/GallerySession.class');
	$hasSession = !empty($_COOKIE[SESSION_ID_PARAMETER]);
	if (!$hasSession) {
	    require_once(dirname(__FILE__) . '/modules/core/classes/GalleryUtilities.class');
	    $hasSession = GalleryUtilities::hasRequestVariable(SESSION_ID_PARAMETER);
	}
	if ($hasSession) {
	    $ret = GalleryInitFirstPass();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    global $gallery;
	    $session =& $gallery->getSession();
	    $ret = $session->reset();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $ret = $session->save();
	    if ($ret->isError()) {
	        return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	return GalleryStatus::success();
    }
}
?>
