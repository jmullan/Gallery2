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
 * See docs/EMBEDDING for more information on using this class.
 * Three interaction modes:
 *  1) GalleryEmbed::init(array(..)) followed by GalleryEmbed::handleRequest()
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
     * @param array (optional--required before calling handleRequest) (
     *   'embedUri' => URI to access G2 via CMS application (example: index.php?module=gallery2)
     *   'relativeG2Path' => relative path from CMS (dir with embedUri) to G2 base dir
     *   'loginRedirect' => URI for redirect to CMS login view (example: /cms/index.php)
     *   'embedSessionString' => (optional) To support cookieless browsing, pass in key=value for
     *                CMS session key and session id value to be added as query parameter in urls
     *   'gallerySessionId' => (optional) To support cookieless browsing, pass in G2 session id
     *                    (when cookies not in use, CMS must track this value between requests)
     *   'activeUserId' => (optional) external user id of active user
     *                                (empty string for anonymous/guest user)
     *   'activeLanguage' => (optional) language code in use for this session
     * )
     * @return object GalleryStatus a status object
     * @static
     */
    function init($initParams=array()) {
	$ret = GalleryInitFirstPass($initParams);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (empty($initParams)) {
	    $ret = GalleryInitSecondPass();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	GalleryCapabilities::set('login', false);
	if (isset($initParams['loginRedirect'])) {
	    GalleryCapabilities::set('loginRedirect', array('href' => $initParams['loginRedirect']));
	}

	if (isset($initParams['activeUserId'])) {
	    $ret = GalleryEmbed::checkActiveUser($initParams['activeUserId']);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

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
	if ($gallery->isStorageInitialized()) {
	    $storage =& $gallery->getStorage();
	    $ret = $storage->commitTransaction();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
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
     * @return array ('isDone' => boolean,
     *                [optional: 'headHtml' => string, 'bodyHtml' => string,
     *                           'sidebarHtml' => string, 'layoutData' => array])
     * @static
     */
    function handleRequest() {
	return GalleryMain(true);
    }

    /**
     * Ensure G2 session has same active user as CMS session.
     * No need to call directly if activeUserId is passed to init().
     *
     * @param string external user id of active user (null or empty for anonymous/guest user)
     * @return object GalleryStatus a status object
     * @private
     */
    function checkActiveUser($activeUserId) {
	global $gallery;
	$session =& $gallery->getSession();

	$idInSession = $session->get('embed.id.externalUser');
	if ($idInSession == $activeUserId) {
	    return GalleryStatus::success();
	}

	if (empty($activeUserId)) {
	    // Logout..
	    $ret = $session->reset();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $session->put('embed.id.externalUser', '');
	} else {
	    // Set G2 active user..
	    list ($ret, $user) = GalleryCoreApi::loadEntityByExternalId($activeUserId, 'GalleryUser');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $session->put('core.id.activeUser', $user->getId());
	    $session->put('embed.id.externalUser', $activeUserId);
	}

	return GalleryStatus::success();
    }

    /**
     * Login the specified user in the G2 session.
     * This method is not usually needed (passing activeUserId to init() or calling
     * checkActiveUser will login the user as needed); this method included for completeness.
     *
     * @param string external user id
     * @return object GalleryStatus a status object
     * @static
     */
    function login($extUserId) {
	global $gallery;
	list ($ret, $user) = GalleryCoreApi::loadEntityByExternalId($extUserId, 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$gallery->setActiveUser($user);
	$session =& $gallery->getSession();
	$session->put('embed.id.externalUser', $extUserId);
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
     * @param string external user id
     * @param array user data (username required; others optional)
     *              ['username' => string, 'email' => string, 'fullname' => string,
     *               'language' => string, 'password' => string,
     *               'hashedpassword' => string, 'hashmethod' => string,
     *               'creationtimestamp' => integer]
     * @return object GalleryStatus a status object
     * @static
     */
    function createUser($extUserId, $args) {
	if (empty($extUserId) || empty($args['username'])) {
	    return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__);
	}
	list ($ret, $user) = GalleryCoreApi::newFactoryInstance('GalleryEntity', 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (!isset($user)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}

	$ret = $user->create($args['username']);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	GalleryEmbed::_setUserData($user, $args, true);
	$ret = $user->save(); 
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/modules/core/classes/ExternalIdMap.class');
	$ret = ExternalIdMap::addMapEntry(array('externalId' => $extUserId,
			      'entityType' => 'GalleryUser', 'entityId' => $user->getId()));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Update a G2 user.
     *
     * @param string external user id
     * @param array user data
     *              ['username' => string, 'email' => string, 'fullname' => string,
     *               'language' => string, 'password' => string,
     *               'hashedpassword' => string, 'hashmethod' => string,
     *               'creationtimestamp' => integer]
     * @return object GalleryStatus a status object
     * @static
     */
    function updateUser($extUserId, $args) {
	list ($ret, $user) = GalleryCoreApi::loadEntityByExternalId($extUserId, 'GalleryUser');
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
    function _setUserData(&$user, $args, $create = false) {
	if (!empty($args['password'])) {
	    $user->changePassword($args['password']);
	} elseif (isset($args['hashmethod']) && $args['hashmethod'] == 'md5'
		&& !empty($args['hashedpassword'])) {
	    $user->setHashedPassword($args['hashedpassword']);
	} elseif ($create) {
	    // Create a random password..
	    $user->changePassword('G' . rand(100000,999999) . '2');
	}

	if (isset($args['username'])) {
	    $user->setUserName($args['username']);
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
	if (isset($args['creationtimestamp'])) {
	    $user->setCreationTimestamp($args['creationtimestamp']);
	}
    }

    /**
     * Delete a G2 user.
     *
     * @param string external user id
     * @return object GalleryStatus a status object
     * @static
     */
    function deleteUser($extUserId) {
	list ($ret, $user) = GalleryCoreApi::loadEntityByExternalId($extUserId, 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::deleteEntityById($user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/modules/core/classes/ExternalIdMap.class');
	$ret = ExternalIdMap::removeMapEntry(
			      array('externalId' => $extUserId, 'entityType' => 'GalleryUser'));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Create a G2 group.
     *
     * @param string external group id
     * @param string group name
     * @return object GalleryStatus a status object
     * @static
     */
    function createGroup($extGroupId, $groupName) {
	if (empty($extGroupId) || empty($groupName)) {
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
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/modules/core/classes/ExternalIdMap.class');
	$ret = ExternalIdMap::addMapEntry(array('externalId' => $extGroupId,
			      'entityType' => 'GalleryGroup', 'entityId' => $group->getId()));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Delete a G2 group.
     *
     * @param string external group id
     * @return object GalleryStatus a status object
     * @static
     */
    function deleteGroup($extGroupId) {
	list ($ret, $group) = GalleryCoreApi::loadEntityByExternalId($extGroupId, 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::deleteEntityById($group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/modules/core/classes/ExternalIdMap.class');
	$ret = ExternalIdMap::removeMapEntry(
			      array('externalId' => $extGroupId, 'entityType' => 'GalleryGroup'));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }
	
    /**
     * Update a G2 Group.
     *
     * @param string external group id
     * @param array group data
     *              ['groupname' => string]
     * @return object GalleryStatus a status object
     * @static
     */
    function updateGroup($extGroupId, $args) {
	list ($ret, $group) = GalleryCoreApi::loadEntityByExternalId($extGroupId, 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (isset($args['groupname'])) {
	    $group->setGroupName($args['groupname']);
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
     * @param string external user id
     * @param string external group id
     * @return object GalleryStatus a status object
     * @static
     */
    function addUserToGroup($extUserId, $extGroupId) {
	list ($ret, $user) = GalleryCoreApi::loadEntityByExternalId($extUserId, 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $group) = GalleryCoreApi::loadEntityByExternalId($extGroupId, 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	/* First check if the user is not already a member of the group */
	list($ret, $membership) = GalleryCoreApi::fetchGroupsForUser($user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	/* Only add user to group if not already done so */
	if (!isset($membership[$group->getId()])) {
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
     * @param string external user id
     * @param string external group id
     * @return object GalleryStatus a status object
     * @static
     */
    function removeUserFromGroup($extUserId, $extGroupId) {
	list ($ret, $user) = GalleryCoreApi::loadEntityByExternalId($extUserId, 'GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	list ($ret, $group) = GalleryCoreApi::loadEntityByExternalId($extGroupId, 'GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$ret = GalleryCoreApi::removeUserFromGroup($user->getId(), $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	return GalleryStatus::success();
    }

    /**
     * Return the SystemContent block for a specific module
     * 
     * @param string module id
     * @return array object GalleryStatus
     *               string html content
     */
    function getSystemContent($moduleId, $contentId) {
	global $gallery;

	/* Load the module list */
	list ($ret, $moduleStatus) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($moduleStatus[$moduleId]) && !empty($moduleStatus[$moduleId]['active'])) {
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    /* Load our templating engine */
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/modules/core/classes/GalleryTemplate.class');
	    $template = new GalleryTemplate(dirname(__FILE__));
	    $template->setVariable('l10Domain', 'module_' . $moduleId);

	    /* Load all module-related content for these items */
	    list ($ret, $systemContent) = $module->loadSystemContent($template);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (! empty($systemContent[$contentId])) {
		return $template->fetch($systemContent[$contentId]);
	    } else {
		return array(GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__), '');
	    }
	}

	return array(GalleryStatus::success(), '');
    }
}
?>
