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
 * Access point for external application in which Gallery is embedded.
 * Three interaction modes:
 *  1) GalleryEmbed::init(g2Request=true) followed by GalleryEmbed::handleRequest()
 *  2) GalleryEmbed::init() followed by other GalleryEmbed/G2 calls,
 *     end with GalleryEmbed::done() <-- REQUIRED
 *  3) Single GalleryEmbed::logout() call
 *
 * @package GalleryMain
 * @version $Revision$ $Date$
 * @author Alan Harder <alan.harder@sun.com>
 */

define('G2_EMBED', 1);
require(dirname(__FILE__) . '/main.php');

class GalleryEmbed {

    /**
     * Initialize Gallery; must be called before most GalleryEmbed methods can be used.
     *
     * @param array (
     *   'embedUri' => URI to access G2 via CMS application (example: index.php?module=gallery2)
     *   'relativeG2Path' => relative path from CMS (dir with embedUri) to G2 base dir
     *   'loginRedirect' => URI for redirect to CMS login view (example: /cms/index.php)
     *   'embedSessionString' => (optional) To support cookieless browsing, pass in key=value for
     *                CMS session key and session id value to be added as query parameter in urls
     *   'gallerySessionId' => (optional) To support cookieless browsing, pass in G2 session id
     *                    (when cookies not in use, CMS must track this value between requests)
     * )
     * @param boolean (optional) if false, call GalleryInitSecondPass too
     * @return object GalleryStatus a status object
     * @static
     */
    function init($initParams, $g2Request=false) {
	$ret = GalleryInitFirstPass($initParams);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (!$g2Request) {
	    $ret = GalleryInitSecondPass();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	GalleryCapabilities::set('login', false);
	GalleryCapabilities::set('loginRedirect', array('href' => $initParams['loginRedirect']));
	return GalleryStatus::success();
    }

    /**
     * Complete the G2 transaction.
     *
     * @return object GalleryStatus a status object
     * @static
     */
    function done() {
	global $gallery;
	$session =& $gallery->getSession();
	$ret = $session->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$storage =& $gallery->getStorage();
	$ret = $storage->commitTransaction();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Process the G2 request.
     * Return value contains 'isDone'=>true if output has already been sent
     * (redirect, or output from G2 immediate view like core:DownloadItem) and
     * CMS should not send any additional output.  If isDone is false then check
     * headHtml and bodyHtml keys for content to display via CMS.
     * Include activeUserName parameter if integration is not calling GalleryEmbed::login()
     * at CMS login time.
     *
     * @param string (optional) username of active user (empty string for anonymous/guest user)
     * @return array object GalleryStatus a status object
     *               array ('isDone' => boolean,
     *                      [optional: 'headHtml' => string, 'bodyHtml' => string])
     * @static
     */
    function handleRequest($activeUserName=null) {
	if (isset($activeUserName)) {
	    $ret = GalleryEmbed::_checkActiveUser($activeUserName);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$data = GalleryMain(true);
	return array(GalleryStatus::success(), $data);
    }

    /**
     * Ensure G2 session has same active user as CMS session.  Do not call directly.
     *
     * @param string username of active user (null or empty for anonymous/guest user)
     * @return object GalleryStatus a status object
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
     * Login the specified user in the G2 session.
     * If this method is called at CMS login time then activeUserName parameter to
     * handleRequest() is not required (but a G2 session is created at CMS login time,
     * even though user may not visit any G2 pages).
     *
     * @param string username
     * @return object GalleryStatus a status object
     * @static
     */
    function login($userName) {
	global $gallery;
	list ($ret, $user) = GalleryCoreApi::fetchUserByUserName($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$gallery->setActiveUser($user);
	return GalleryStatus::success();
    }

    /**
     * Reset the G2 session.  Do not call init() before this method.
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

    /**
     * Retrieve G2 session id.  This method can be called after init() or handleRequest().
     *
     * @return string session id
     * @static
     */
    function getSessionId() {
	global $gallery;
	$session =& $gallery->getSession();
	return $session->getId();
    }

    /**
     * Create a G2 user.
     *
     * @param string username
     * @param array (optional) additional data
     *              ['email' => string, 'fullname' => string,
     *               'language' => string, 'password' => string,
     *               'hashedpassword' => string, 'hashmethod' => string]
     * @return object GalleryStatus a status object
     * @static
     */
    function createUser($userName, $args=array()) {
	if (empty($userName)) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__);
	}
	list ($ret, $user) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (!isset($user)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}

	$ret = $user->create($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	GalleryEmbed::_setUserData($user, $args);
	$ret = $user->save(); 
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Update a G2 user.
     *
     * @param string username
     * @param array user data
     *              ['username' => string, 'email' => string, 'fullname' => string,
     *               'language' => string, 'password' => string,
     *               'hashedpassword' => string, 'hashmethod' => string]
     * @return object GalleryStatus a status object
     * @static
     */
    function updateUser($userName, $args) {
	list ($ret, $user) = GalleryCoreApi::fetchUserByUserName($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	GalleryEmbed::_setUserData($user, $args);
	$ret = $user->save(); 
	if ($ret->isError()) {
	    GalleryCoreApi::releaseLocks($lockId);
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::releaseLocks($lockId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Set values in user object based on given args.
     *
     * @param object GalleryUser user
     * @param array additional user data
     * @private
     */
    function _setUserData(&$user, $args) {
	if (!empty($args['password'])) {
	    $user->changePassword($args['password']);
	} elseif (isset($args['hashmethod']) && $args['hashmethod'] == 'md5'
		&& !empty($args['hashedpassword'])) {
	    $user->setHashedPassword($args['hashedpassword']);
	} else {
	    // Create a random password..
	    $user->changePassword('G' . rand(100000,999999) . '2');
	}

	if (isset($args['username'])) {
	    $user->setuserName($args['username']);
	}
	if (isset($args['email'])) {
	    $user->setEmail($args['email']);
	}
	if (isset($args['fullname'])) {
	    $user->setFullName($args['fullname']);
	}
	if (isset($args['language'])) {
	    list ($languageCode) = GalleryTranslator::getSupportedLanguageCode($args['language']);
	    $user->setLanguage($languageCode);
	}
    }

    /**
     * Delete a G2 user.
     *
     * @param string username
     * @return object GalleryStatus a status object
     * @static
     */
    function deleteUser($userName) {
	list ($ret, $user) = GalleryCoreApi::fetchUserByUserName($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::deleteEntityById($user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Create a G2 group.
     *
     * @param string group name
     * @return object GalleryStatus a status object
     * @static
     */
    function createGroup($groupName) {
	if (empty($groupName)) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__);
	}
	list ($ret, $group) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (!isset($group)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}

	$ret = $group->create($groupName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = $group->save(); 
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Delete a G2 group.
     *
     * @param string group name
     * @return object GalleryStatus a status object
     * @static
     */
    function deleteGroup($groupName) {
	list ($ret, $group) = GalleryCoreApi::fetchGroupByGroupName($groupName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::deleteEntityById($group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }
	
	/**
     * Update a G2 Group.
     *
     * @param string groupname
     * @param array group data
     *              ['groupname' => string]
     * @return object GalleryStatus a status object
     * @static
     */
    function updateGroup($groupName, $args) {
	list ($ret, $group) = GalleryCoreApi::fetchGroupByGroupName($groupName);;
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (isset($args['groupname'])) {
	    $group->setgroupName($args['groupname']);
	}
	$ret = $group->save(); 
	if ($ret->isError()) {
	    GalleryCoreApi::releaseLocks($lockId);
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::releaseLocks($lockId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Add a user to a G2 group.
     *
     * @param string username
     * @param string group name
     * @return object GalleryStatus a status object
     * @static
     */
    function addUserToGroup($userName, $groupName) {
	list ($ret, $user) = GalleryCoreApi::fetchUserByUserName($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $group) = GalleryCoreApi::fetchGroupByGroupName($groupName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	/* First check if the user is not already a member of the group */
	list($ret, $memberShips) = GalleryCoreApi::fetchGroupsForUser($user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	/* Only add user to group if not already done so */
	if (!isset($memberShips[$group->getId()])) {
	    $ret = GalleryCoreApi::addUserToGroup($user->getId(), $group->getId());
	    if ($ret->isError()) {
	    	return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	return GalleryStatus::success();
    }

    /**
     * Remove a user from a G2 group.
     *
     * @param string username
     * @param string group name
     * @return object GalleryStatus a status object
     * @static
     */
    function removeUserFromGroup($userName, $groupName) {
	list ($ret, $user) = GalleryCoreApi::fetchUserByUserName($userName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $group) = GalleryCoreApi::fetchGroupByGroupName($groupName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::removeUserFromGroup($user->getId(), $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }
}
?>
