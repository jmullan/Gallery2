<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

/*
 * Bootstrap code: We have to load a few classes just so that the GalleryModule
 * parent class exists. This is only because we are the core module; other
 * modules should not have to do stuff like this.
 */
$classDir = dirname(__FILE__) . '/classes/';
require_once($classDir . 'GalleryModule.class');

class CoreModule extends GalleryModule {

    var $_gallery;

    function CoreModule() {
	$this->setName('core');
	$this->setDescription('Core Gallery functionality');
	$this->setVersion('1.0');
    }

    /**
     * @see GalleryModule::init();
     */
    function init() {
	$classDir = dirname(__FILE__) . '/classes/';

	/* Load all the core Gallery classes */
	require_once($classDir . 'Gallery.class');
	require_once($classDir . 'GalleryController.class');
	require_once($classDir . 'GalleryDerivativeHelper.class');
	require_once($classDir . 'GalleryItemPropertiesMap.class');
	require_once($classDir . 'GalleryLayout.class');
	require_once($classDir . 'GalleryLock.class');
	require_once($classDir . 'GalleryModuleMap.class');
	require_once($classDir . 'GalleryModuleParameterMap.class');
	require_once($classDir . 'GalleryPermissionMap.class');
	require_once($classDir . 'GalleryProfiler.class');
	require_once($classDir . 'GallerySession.class');
	require_once($classDir . 'GalleryStatus.class');
	require_once($classDir . 'GalleryTemplateAdapter.class');
	require_once($classDir . 'GalleryTheme.class');
	require_once($classDir . 'GalleryUserGroupMap.class');
	require_once($classDir . 'GalleryUserHelper.class');
	require_once($classDir . 'GalleryGroupHelper.class');
	require_once($classDir . 'GalleryUtilities.class');
	require_once($classDir . 'GalleryView.class');
	require_once($classDir . 'GalleryViewCountMap.class');

	/*
	 * Set up our Gallery global.  It's important to use a reference here because
	 * the constructor registers a shutdown function and ties it to the instance in
	 * the constructor.  This global should be the only one that Gallery requires.
	 * Everything else should be inside it so that we do not pollute the namespace
	 * (especially important when we're embedded inside another application).
	 */
	$gallery =& new Gallery();
	$GLOBALS['gallery'] =& $gallery;
	$gallery->setCoreModule($this);

	/* Configure the Platform */
	if (substr(PHP_OS, 0, 3) == 'WIN') {
	    $gallery->setConfig('platform.type', 'windows');
	} else {
	    $gallery->setConfig('platform.type', 'unix');
	}

	/* Register all core permissions */
	$gallery->addRegistry('GalleryPermissionMap',
			      array('id' => 'core.all',
				    'description' => 'Full',
				    'itemAdmin' => true),
			      array('id' => 'core.view',
				    'description' => 'View',
				    'itemAdmin' => false),
			      array('id' => 'core.viewResizes',
				    'description' => 'View Resizes',
				    'itemAdmin' => false),
			      array('id' => 'core.viewSource',
				    'description' => 'View Original',
				    'itemAdmin' => false),
			      array('id' => 'core.viewAll',
				    'description' => 'View All',
				    'itemAdmin' => false),
			      array('id' => 'core.insert',
				    'description' => 'Insert',
				    'itemAdmin' => true),
			      array('id' => 'core.change',
				    'description' => 'Change',
				    'itemAdmin' => true),
			      array('id' => 'core.move',
				    'description' => 'Move',
				    'itemAdmin' => true),
			      array('id' => 'core.changeText',
				    'description' => 'Change Text',
				    'itemAdmin' => true),
			      array('id' => 'core.delete',
				    'description' => 'Delete',
				    'itemAdmin' => true));

	$this->_gallery =& $gallery;

	/* Register our entity implementations */
	$gallery->addRegistry('GalleryEntity.GalleryAlbumItem',
			      $classDir . 'GalleryAlbumItem.class');
	$gallery->addRegistry('GalleryEntity.GalleryUser',
			      $classDir . 'GalleryUser.class');
	$gallery->addRegistry('GalleryEntity.GalleryGroup',
			      $classDir . 'GalleryGroup.class');
	$gallery->addRegistry('GalleryEntity.GalleryDerivative',
			      $classDir . 'GalleryDerivative.class');
	$gallery->addRegistry('GalleryEntity.GalleryDerivativeImage',
			      $classDir . 'GalleryDerivativeImage.class');
	$gallery->addRegistry('GalleryEntity.GalleryMovieItem',
			      $classDir . 'GalleryMovieItem.class');
	$gallery->addRegistry('GalleryEntity.GalleryPhotoItem',
			      $classDir . 'GalleryPhotoItem.class');
	$gallery->addRegistry('GalleryEntity.GalleryUnknownItem',
			      $classDir . 'GalleryUnknownItem.class');

	return parent::init();
    }

    /**
     * @see GalleryModule::install
     */
    function install() {
	global $gallery;

	/*
	 * Installing the core is an unusual case, since the locations where we
	 * keep track of what's versions are installed may not even exist.  So,
	 * we have to work under the assumption that the store itself is
	 * already installed and configured, and our authentication is good.
	 * So then if we ask for the version number of the core and we get a
	 * storage error, we can assume that the core's store has not yet been
	 * configured and do that now.  All other modules can simply ask for
	 * the version number and expect that to succeed.
	 */
	list ($ret, $version) = $this->getModuleParameter('version');
	if ($ret->isError() & !($ret->getErrorCode() & ERROR_STORAGE_FAILURE)) {
	    return $ret->wrap(__FILE__, __LINE__);
	} else if ($ret->isError() || $version != $this->getVersion()) {

	    /* The store requires configuration. */
	    list ($ret, $storage) = $gallery->getStorage();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $ret = $storage->configureStore('core');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	if ($version != $this->getVersion()) {
	    if (empty($version)) {
		/*
		 * This is an initial install.  
		 * Make sure that we have some reasonable defaults for the core.
		 */
		foreach (array('permissions.directory' => '0755',
			       'permissions.file' => '0644',
			       'exec.expectedStatus' => '0',
			       'default.orderBy' => 'id',
			       'default.orderDirection' => '1',
			       'default.layout' => 'classic',
			       'default.theme' => 'classic',
			       'default.language' => 'en_US',
			       'session.idParameter' => 'GALLERYSID',
			       'session.lifetime' => 25 * 365 * 86400, /* 25 years */
			       'session.inactivityTimeout' => 14 * 365 * 86400, /* two weeks */
			       )
			 as $key => $value) {

		    $ret = $this->setModuleParameter($key, $value);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}

		foreach (array("_createAllUsersGroup",
			       "_createSiteAdminsGroup",
			       "_createAnonymousUser",
			       "_createAdminUser",
			       "_createRootAlbumItem") as $func) {

		    $ret = $this->$func();
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }

	    $ret = $this->setModuleParameter('version', $this->getVersion());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	} 

	/* The core is now guaranteed to be configured and initialized */
			      
	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::getItemLinks
     */
    function getItemLinks($items, $returnUrlParams) {
	global $gallery;

	if (!is_array($items)) {
	    $items = array($items);
	}

	foreach ($returnUrlParams as $param => $value) {
	    $params['return.' . $param] = $value;
	}

	/*
	 * See if the user has any admin permissions.  If so, display the "[edit
	 * item]" link.
	 */
	$adminPermissions = array();
	$permissions = $gallery->lookupRegistry('GalleryPermissionMap');
	foreach ($permissions as $permission) {
	    if (!empty($permission['itemAdmin'])) {
		$adminPermissions[] = $permission['id'];
	    }
	}

	/*
	 * If we're a site admin, then we always have edit permission.  Else,
	 * figure out what groups we're in and use that to make the determination.
	 */
	list ($ret, $isSiteAdmin) =
	    GalleryUserGroupMap::isUserInSiteAdminGroup($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!$isSiteAdmin) {
	    list ($ret, $groupIds) = 
		GalleryUserGroupMap::fetchGroupsForUser($gallery->getActiveUserId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$links = array();
	foreach ($items as $item) {
	    if ($isSiteAdmin) {
		$hasPermission = true; 
	    } else {
		list ($ret, $hasPermission) =
		    GalleryPermissionMap::hasPermission($item->getId(),
							array($gallery->getActiveUserId()),
							$groupIds,
							$adminPermissions);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    if ($hasPermission) {
		$links[$item->getId()] =
		    array('text' => $this->translate('edit item'),
			  'params' => array_merge(array('view' => 'core:ItemAdmin',
							'itemId' => $item->getId()),
						  $params));
	    }
	}

	return array(GalleryStatus::success(), $links);
    }
    
    /**
     * @see GalleryModule::getSystemLinks
     */
    function getSystemLinks($returnUrlParams) {
	global $gallery;

	list ($ret, $anonymousUserId) = $this->getModuleParameter('id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	foreach ($returnUrlParams as $param => $value) {
	    $params['return.' . $param] = $value;
	}

	$links = array();
	if ($gallery->getActiveUserId() == $anonymousUserId) {
	    $links[] = array('text' => $this->translate('login'),
			     'params' => array_merge(array('view' => 'core:Login'),
						     $params));
	} else {
	    $links[] = array('text' => $this->translate('logout'),
			     'params' => array_merge(array('controller' => 'core:Logout'),
						     $params));
	}

	list ($ret, $isAdmin) =
	    GalleryUserGroupMap::isUserInSiteAdminGroup($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($isAdmin) {
	    $links[] = array('text' => $this->translate('site admin'),
			     'params' => array_merge(array('view' => 'core:SiteAdmin'),
						     $params));
	}

	return array(GalleryStatus::success(), $links);
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews();
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('General'),
				 'view' => 'core:AdminCore'),
			   array('name' => $this->translate('Users'),
				 'view' => 'core:AdminUsers'),
			   array('name' => $this->translate('Groups'),
				 'view' => 'core:AdminGroups'),
			   array('name' => $this->translate('Modules'),
				 'view' => 'core:AdminModules')));
    }

    /**
     * Create the initial All Users group
     *
     * @return object GalleryStatus a status code
     */
    function _createAllUsersGroup() {
	global $gallery;

	list ($ret, $id) = $this->getModuleParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}
    
	list ($ret, $group) = $gallery->newEntity('GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	$ret = $group->create('All Users', GROUP_ALL_USERS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	$ret = $this->setModuleParameter('id.allUserGroup', $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    
	return GalleryStatus::success();
    }

    /**
     * Create the Site Admins group
     *
     * @return object GalleryStatus a status code
     */
    function _createSiteAdminsGroup() {
	global $gallery;

	list ($ret, $id) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}
    
	list ($ret, $group) = $gallery->newEntity('GalleryGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	$ret = $group->create('Site Admins', GROUP_SITE_ADMINS);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	$ret = $group->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->setModuleParameter('id.adminGroup', $group->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }

    /**
     * Create the initial Anonymous User
     *
     * @return object GalleryStatus a status code
     */
    function _createAnonymousUser() {
	global $gallery;

	list ($ret, $id) = $this->getModuleParameter('id.anonymousUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (!empty($id)) {
	    return GalleryStatus::success();
	}
    
	list ($ret, $user) = $gallery->newEntity('GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	$ret = $user->create('anonymous');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$user->setFullName('Anonymous');
	
	$ret = $user->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->setModuleParameter('id.anonymousUser', $user->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * Create the initial admin user
     *
     * @return object GalleryStatus a status code
     */
    function _createAdminUser() {
	global $gallery;

	/* Don't create if there is already a user in the admin group */
	list ($ret, $adminGroupId) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	list ($ret, $results) = GalleryUserGroupMap::fetchUsersForGroup($adminGroupId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (sizeof($results) > 0) {
	    return GalleryStatus::success();
	}

	/* Create the user */
	list ($ret, $user) = $gallery->newEntity('GalleryUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	$ret = $user->create('admin');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$user->changePassword($gallery->getConfig('setup.password'));
	$user->setFullName('Gallery Administrator');
	
	$ret = $user->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Add her to the admin group */
	$ret = GalleryUserGroupMap::addUserToGroup($user->getId(),
						   $adminGroupId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * Create the root album item
     *
     * @return object GalleryStatus a status code
     */
    function _createRootAlbumItem() {
	global $gallery;

	/* Do we already have a root? */
	list ($ret, $rootAlbumId) = $this->getModuleParameter('id.rootAlbum');
	if ($rootAlbumId) {
	    return GalleryStatus::success();
	}

	list ($ret, $adminGroupId) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	list ($ret, $results) = GalleryUserGroupMap::fetchUsersForGroup($adminGroupId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (sizeof($results) == 0) {
	    $gallery->debug('There is no admin user!');
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}

	/* Pick the first admin user in the group */
	$results = array_keys($results);
	$adminId = $results[0];
	
	list ($ret, $album) = $gallery->newEntity('GalleryAlbumItem');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
					     
	$ret = $album->createRoot('root', $adminId);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	$album->setDescription("This is the top of your Gallery");

	$ret = $album->save();
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/* Give all users some stuff */
	list ($ret, $groupId) = $this->getModuleParameter('id.allUserGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	foreach (array('core.view',
		       'core.viewResizes',
		       'core.viewSource') as $permission) {
	    $ret = GalleryPermissionMap::addGroupPermission($album->getId(),
							    $groupId,
							    $permission);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	/* Grant admin users everything */
	list ($ret, $groupId) = $this->getModuleParameter('id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryPermissionMap::addGroupPermission($album->getId(),
							$groupId,
							'core.all');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = $this->setModuleParameter('id.rootAlbum', $album->getId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	
	return GalleryStatus::success();
    }
    
}
?>
