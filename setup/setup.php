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

ob_start();

if (phpversion() < "4.0.4") {
    error('oldPhp');
    return;
}

if (!CheckFileDirective()) {
    error('brokenFile');
    return;
}
 
if (!CheckConfigFileExists()) {
    error('missingConfig');
    return;
}

/*
 * This call may fail, especially if the storage has not been
 * configured properly.  That's ok.  We'll check the storage
 * settings independently.
 */
$ret = InitializeGallery();

list ($ret, $platform) = $gallery->getPlatform();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    error('unknownError', array('error' => $ret));
}

if (!CheckSetupPassword()) {
    error('missingPassword');
    return;
}

if (!CheckPasswordIsCorrect()) {
    message('passwordForm');
    return;
}

$dirStatus = CheckDirectories();
if (!empty($dirStatus)) {
    list ($err, $key, $dir) = $dirStatus;
    $stat = $platform->stat($dir);
    switch($err) {
    case 'missing':
	error('missingDir',
		array('dir' => $dir,
		      'stat' => $stat));
	return;

    case 'not-a-dir':
	error('notADir',
		array('dir' => $dir,
		      'stat' => $stat));
	return;

    case 'not-writeable':
	error('notWriteable',
		array('dir' => $dir,
		      'stat' => $stat));
	return;

    case 'cant-mkdir':
	error('cantMkdir',
		array('dir' => $dir,
		      'stat' => $stat));
	return;
	
    case 'cant-write-into':
	error('cantWriteInto',
		array('dir' => $dir,
		      'stat' => $stat));
	return;
    }
}

/*
 * Make sure we can connect to the storage subsystem.
 */
list ($ret, $storage) = $gallery->getUninitializedStorage();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    error('unknownError', array('error' => $ret));
}

$ret = $storage->testAuthentication();
if ($ret->isError()) {
    if ($ret->getErrorCode() & ERROR_UNIMPLEMENTED) {
	error('configurationError');
    } else if ($ret->getErrorCode() & ERROR_STORAGE_BAD_AUTHENTICATON) {
	error('badStoragePassword');
    } else if ($ret->getErrorCode() & ERROR_STORAGE_FAILURE) {
	error('storageError', array('error' => $ret));
    } else {
	error('unknownError', array('error' => $ret));
    }
    return;
}

/*
 * Ok, we've got a connection to the database.  But we don't know if the
 * database has been created or not, so give the user the option to create it.
 */
if (empty($HTTP_POST_VARS['g2_storeAction'])) {
    message('createOrConfigure');
    return;
} else {
    $storeAction = $HTTP_POST_VARS['g2_storeAction'];
    if ($storeAction == 'Create New Store') {
	$ret = $storage->createStore();
	if ($ret->isError()) {
	    $ret = $ret->wrap(__FILE__, __LINE__);
	    error('storageError', array('error' => $ret));
	    return;
	}

	$gallery->reset();
	list ($ret, $storage) = $gallery->getStorage();
	if ($ret->isError()) {
	    $ret = $ret->wrap(__FILE__, __LINE__);
	    error('storageError', array('error' => $ret));
	    return;
	}

	$ret = $storage->configureStore('core');
	if ($ret->isError()) {
	    $ret = $ret->wrap(__FILE__, __LINE__);
	    error('storageError', array('error' => $ret));
	    return;
	}
    } else if ($storeAction == 'Upgrade') {
	$gallery->reset();
	list ($ret, $storage) = $gallery->getStorage();
	if ($ret->isError()) {
	    $ret = $ret->wrap(__FILE__, __LINE__);
	    error('storageError', array('error' => $ret));
	    return;
	}

	$ret = $storage->configureStore('core');
	if ($ret->isError()) {
	    $ret = $ret->wrap(__FILE__, __LINE__);
	    error('storageError', array('error' => $ret));
	    return;
	}
    } else {
	message('createOrConfigure');
    }
}

/*
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
	       'graphics.type' => 'netpbm')
	 as $key => $value) {

    list ($ret, $oldValue) = $gallery->getModuleParameter('core', $key);
    if ($ret->isError()) {
	error('unknownError', array('error' => $ret));
	return;
    }

    if ($oldValue == '') {
	$ret = $gallery->setModuleParameter('core', $key, $value);
	if ($ret->isError()) {
	    error('unknownError', array('error' => $ret));
	    return;
	}
    }
}

/* Create all our core users, groups and items. */
$ret = CreateAllUsersGroup();
if ($ret->isError()) {
    error('unknownError', array('error' => $ret));
    return;
}

$ret = CreateAllAdminsGroup();
if ($ret->isError()) {
    error('unknownError', array('error' => $ret));
    return;
}

$ret = CreateAnonymousUser();
if ($ret->isError()) {
    error('unknownError', array('error' => $ret));
    return;
}

$ret = CreateAdminUser();
if ($ret->isError()) {
    error('unknownError', array('error' => $ret));
    return;
}

$ret = CreateRootAlbumItem();
if ($ret->isError()) {
    error('unknownError', array('error' => $ret));
    return;
}

message('success');

/*************************************************************
 *
 * Support functions below this point
 *
 *************************************************************/
function error($messageName, $messageData=null) {
    global $message, $gallery;
    global $HTTP_POST_VARS;

    $message = $messageData;
    $message['output'] = ob_get_contents();
    ob_end_clean();

    $message['debug'] = $gallery->getDebugBuffer();
    if (!empty($HTTP_POST_VARS['g2_password'])) {
	$message['password'] = $HTTP_POST_VARS['g2_password'];
    }

    include(dirname(__FILE__) . '/messages/errorHeader.php');
    include(dirname(__FILE__) . '/messages/' . $messageName . '.php');
    include(dirname(__FILE__) . '/messages/errorFooter.php');
}

function message($messageName, $messageData=null) {
    global $message, $gallery;
    global $HTTP_POST_VARS;

    $message = $messageData;
    $message['output'] = ob_get_contents();
    ob_end_clean();

    $message['debug'] = $gallery->getDebugBuffer();
    if (!empty($HTTP_POST_VARS['g2_password'])) {
	$message['password'] = $HTTP_POST_VARS['g2_password'];
    }

    include(dirname(__FILE__) . '/messages/messageHeader.php');
    include(dirname(__FILE__) . '/messages/' . $messageName . '.php');
    include(dirname(__FILE__) . '/messages/messageFooter.php');
}

function CheckSetupPassword() {
    global $gallery;

    $password = $gallery->getConfig('setup.password');
    return (!empty($password));
}

function CheckPasswordIsCorrect() {
    global $gallery;
    global $HTTP_POST_VARS;

    if (empty($HTTP_POST_VARS['g2_password'])) {
	return false;
    }
    
    return !strcmp($gallery->getConfig('setup.password'),
		   $HTTP_POST_VARS['g2_password']);
}

function CheckConfigFileExists() {
    global $gallery;
    return file_exists(dirname(__FILE__) . '/../config.php');
}

function CheckFileDirective() {
    if (strstr(__FILE__, 'setup/setup.php')) {
	return 1;
    } else {
	return 0;
    }
}

function InitializeGallery() {
    require(dirname(__FILE__) . '/../init.php');
    return GalleryInit();
}

function CheckDirectories() {
    global $gallery, $platform;

    /* Make sure that our base path exists, is a directory and is writeable */
    $dataBase = $gallery->getConfig('data.gallery.base');
    if (!$platform->file_exists($dataBase)) {
	return array('missing', 'data.gallery.base', $dataBase);
    }

    if (!$platform->is_dir($dataBase)) {
	return array('not-a-dir', 'data.gallery.base', $dataBase);
    }

    if (!$platform->is_writeable($dataBase)) {
	return array('not-writeable', 'data.gallery.base', $dataBase);
    }

    $testfile = $dataBase . '/setup' . rand(1, 1000000);
    if ($fd = $platform->fopen($testfile, "w")) {
	fclose($fd);
	$platform->unlink($testfile);
    } else {
	return array('cant-write-into', 'data.gallery.base', $dataBase);
    }

    /* Create the sub directories, if necessary */
    foreach (array('data.gallery.albums',
		   'data.gallery.cache',
		   'data.gallery.tmp',
		   'data.smarty.base',
		   'data.smarty.templates_c') as $key) {
	$dir = $gallery->getConfig($key);

	if ($platform->file_exists($dir) && !$platform->is_dir($dir)) {
   	    return array('not-a-dir', $key, $dir);
	}

	if (!$platform->file_exists($dir)) {
	    if (!$platform->mkdir($dir)) {
		return array('cant-mkdir', $key, $dir);
		return GalleryStatus::success();
	    }
	}

	if (!$platform->is_writeable($dir)) {
	    return array('not-writeable', $key, $dir);
	}
    }
}

function CreateAllUsersGroup() {
    global $gallery;

    list ($ret, $id) = $gallery->getModuleParameter('core', 'id.allUserGroup');
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
    
    $ret = $gallery->setModuleParameter('core', 'id.allUserGroup',
					$group->getId());
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    
    return GalleryStatus::success();
}

function CreateAllAdminsGroup() {
    global $gallery;

    list ($ret, $id) = $gallery->getModuleParameter('core', 'id.adminGroup');
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
					     
    $ret = $group->create('All Admins', GROUP_ALL_ADMINS);
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
	
    $ret = $group->save();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = $gallery->setModuleParameter('core', 'id.adminGroup',
					$group->getId());
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
	
    return GalleryStatus::success();
}

function CreateAnonymousUser() {
    global $gallery;

    list ($ret, $id) = $gallery->getModuleParameter('core', 'id.anonymousUser');
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
    $user->setLanguage('en_US');
	
    $ret = $user->save();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = $gallery->setModuleParameter('core', 'id.anonymousUser',
					$user->getId());
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    return GalleryStatus::success();
}

function CreateAdminUser() {
    global $gallery;

    /* Don't create if there is already a user in the admin group */
    list ($ret, $adminGroupId) = $gallery->getModuleParameter('core', 'id.adminGroup');
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
    $user->setPassword('admin');
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

function CreateRootAlbumItem() {
    global $gallery;

    /* Do we already have a root? */
    list ($ret, $rootAlbumId) =
	$gallery->getModuleParameter('core', 'id.rootAlbum');
    if ($rootAlbumId) {
	return GalleryStatus::success();
    }

    list ($ret, $adminGroupId) = $gallery->getModuleParameter('core', 'id.adminGroup');
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
    list ($ret, $groupId) =
	$gallery->getModuleParameter('core', 'id.allUserGroup');
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
    list ($ret, $groupId) =
	$gallery->getModuleParameter('core', 'id.adminGroup');
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = GalleryPermissionMap::addGroupPermission($album->getId(),
						    $groupId,
						    'core.all');
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    $ret = $gallery->setModuleParameter('core', 'id.rootAlbum',
					$album->getId());
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
	
    return GalleryStatus::success();
}
