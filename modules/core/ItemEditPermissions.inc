<?php
/*
 * $RCSfile
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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

class ItemEditPermissionsController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all', 'core.changePermissions'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['delete'])) {
	    /* Handle delete actions */ 
	    if (isset($form['permission']['id']) &&
		(isset($form['group']['id']) || isset($form['user']['id']))) {

		$permission = $form['permission']['id'];
		if (isset($form['group']['id'])) {
		    $ret = GalleryPermissionMap::removeGroupPermission($itemId,
								       $form['group']['id'],
								       $permission);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list ($ret, $group) = $gallery->loadEntitiesById($form['group']['id']);
		    if ($ret->isSuccess()) {
			$redirectParams['form.group.groupName'] = $group->getGroupName();
		    }
		    $redirectParams['form.group.permission'] = $form['permission']['id'];
		}
		
		if (isset($form['user']['id'])) {
		    $ret = GalleryPermissionMap::removeUserPermission($itemId,
								      $form['user']['id'],
								      $permission);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list ($ret, $user) = $gallery->loadEntitiesById($form['user']['id']);
		    if ($ret->isSuccess()) {
			$redirectParams['form.user.userName'] = $user->getUserName();
		    }
		    $redirectParams['form.user.permission'] = $form['permission']['id'];
		}

		/* Figure out where to redirect upon success */
		$redirectParams['view'] = 'core:ItemAdmin';
		$redirectParams['subView'] = 'core:ItemEditPermissions';
		$redirectParams['itemId'] = $itemId;
	    }
	} else if (isset($form['action']['addUserPermission'])) {

	    /* Handle create user permission actions */
	    if (empty($form['user']['userName'])) {
		GalleryUtilities::putRequestVariable('form.error.user.missingUser', 1);
	    } else {
		/* Validate the user */
		list ($ret, $user) =
		    GalleryUserHelper::fetchUserByUserName($form['user']['userName']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			GalleryUtilities::putRequestVariable('form.error.user.invalidUser', 1);
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		/* Validate the permission */
		$permission = $form['user']['permission'];
		$allPermissions = GalleryPermissionMap::getAllRegisteredPermissions();
		if (empty($allPermissions[$permission])) {
		    GalleryUtilities::putRequestVariable('form.error.user.invalidPermission', 1);
		    $permission = null;
		}

		if (!empty($permission) && !empty($user)) {
		    /* Don't add the permission if it already exists */
		    list ($ret, $hasIt) =
			GalleryPermissionMap::hasPermission($itemId,
							    array($user->getId()),
							    null,
							    array($permission));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (!$hasIt) {
			$ret = GalleryPermissionMap::addUserPermission($itemId,
								       $user->getId(),
								       $permission);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    /* Figure out where to redirect upon success */
		    $redirectParams['view'] = 'core:ItemAdmin';
		    $redirectParams['subView'] = 'core:ItemEditPermissions';
		    $redirectParams['itemId'] = $itemId;
		    $redirectParams['form.user.userName'] = $user->getUserName();
		}
	    }
	} else if (isset($form['action']['addGroupPermission'])) {

	    /* Handle create group permission actions */
	    if (empty($form['group']['groupName'])) {
		GalleryUtilities::putRequestVariable('form.error.group.missingGroup', 1);
	    } else {
		/* Validate the group */
		list ($ret, $group) =
		    GalleryGroupHelper::fetchGroupByGroupName($form['group']['groupName']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			GalleryUtilities::putRequestVariable('form.error.group.invalidGroup', 1);
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		/* Validate the permission */
		$permission = $form['group']['permission'];
		$allPermissions = GalleryPermissionMap::getAllRegisteredPermissions();
		if (empty($allPermissions[$permission])) {
		    GalleryUtilities::putRequestVariable('form.error.group.invalidPermission', 1);
		    $permission = null;
		}

		if (!empty($permission) && !empty($group)) {
		    /* Don't add the permission if it already exists */
		    list ($ret, $hasIt) =
			GalleryPermissionMap::hasPermission($itemId,
							    null,
							    array($group->getId()),
							    array($permission));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (!$hasIt) {
			$ret = GalleryPermissionMap::addGroupPermission($itemId,
									$group->getId(),
									$permission);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    /* Figure out where to redirect upon success */
		    $redirectParams['view'] = 'core:ItemAdmin';
		    $redirectParams['subView'] = 'core:ItemEditPermissions';
		    $redirectParams['itemId'] = $itemId;
		    $redirectParams['form.group.groupName'] = $group->getGroupName();
		}
	    }
	} else if (isset($form['action']['changeOwner'])) {
	    if (empty($form['owner']['ownerName'])) {
		GalleryUtilities::putRequestVariable('form.error.owner.missingUser', 1);
	    } else {
		/* Validate the user */
		list ($ret, $user) =
		    GalleryUserHelper::fetchUserByUserName($form['owner']['ownerName']);
		if ($ret->isError()) {
		    if ($ret->getErrorCode() & ERROR_MISSING_OBJECT) {
			GalleryUtilities::putRequestVariable('form.error.owner.invalidUser', 1);
		    } else {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		if (!empty($user)) {
		    list ($ret, $lockId) = $gallery->acquireWriteLock($item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $item->refresh();
		    $item->setOwnerId($user->getId());
		    $ret = $item->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		
		    $ret = $gallery->releaseLocks($lockId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Figure out where to redirect upon success */
		    $redirectParams['view'] = 'core:ItemAdmin';
		    $redirectParams['subView'] = 'core:ItemEditPermissions';
		    $redirectParams['itemId'] = $itemId;
		}
	    }
	}

	if (!empty($redirectParams)) {
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemEditPermissions');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class ItemEditPermissionsView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	list ($itemId, $formName) =
	    GalleryUtilities::getRequestVariables('itemId', 'formName');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all', 'core.changePermissions'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($formName == 'ItemEditPermissions') {
	    /* Complain if we have any invalid data */
	} else {
	    /*
	     * First time around, load the form with item data.  Note that
	     * userName and groupName can be passed in to this form so don't
	     * initialize them unless they don't exist.
	     */
	    if (empty($form['user']['userName'])) {
		$form['user']['userName'] = '';
	    }
	    
	    if (empty($form['group']['groupName'])) {
		$form['group']['groupName'] = '';
	    }
	    
	    $form['owner']['ownerName'] = '';
	}

	/* Get all available permissions */
	$allPermissions =
	    GalleryPermissionMap::getAllRegisteredPermissions();
	ksort($allPermissions);

	/* Get all permissions for the item. */
	list ($ret, $permissions) = 
	    GalleryPermissionMap::fetchAllPermissionsForItem($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Figure out all the unique user/group ids and load those */
	$userAndGroupEntityIds = array();
	foreach ($permissions as $permission) {
	    if (!empty($permission['userId'])) {
		$userAndGroupEntityIds[$permission['userId']] = 1;
	    }
	    if (!empty($permission['groupId'])) {
		$userAndGroupEntityIds[$permission['groupId']] = 1;
	    }
	}

	list ($ret, $userAndGroupEntities) =
	    $gallery->loadEntitiesById(array_keys($userAndGroupEntityIds));

	/* Convert them into a hash map by entity id */
	foreach ($userAndGroupEntities as $entity) {
	    $userAndGroupEntityMap[$entity->getId()] = $entity->getMemberData();
	}

	/* Figure out the admin group id */
	list ($ret, $adminGroupId) =
	    $gallery->getModuleParameter('core', 'id.adminGroup');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	/*
	 * Now create the separate user and group permission maps.
	 *
	 * Silently ignore any permissions that we come across that aren't part
	 * of the permission registry.  They may be permission associated with 
	 * modules that are not currently active.
	 */
	$userPermissions = array();
	$groupPermissions = array();
	foreach ($permissions as $permission) {
	    if (!empty($permission['userId']) && isset($allPermissions[$permission['permission']])) {
		$userPermissions[] =
		    array('permission' =>
			  array('id' => $permission['permission'],
				'description' => $allPermissions[$permission['permission']]),
			  'user' => $userAndGroupEntityMap[$permission['userId']],
			  'deleteable' => 1);
	    }
	    
	    if (!empty($permission['groupId']) && isset($allPermissions[$permission['permission']])) {
		$deleteable = 1;
		if ($permission['groupId'] == $adminGroupId &&
		        $permission['permission'] == 'core.all') {
		    $deleteable = 0;
		}
		$groupPermissions[] =
		    array('permission' =>
			  array('id' => $permission['permission'],
				'description' => $allPermissions[$permission['permission']]),
			  'group' => $userAndGroupEntityMap[$permission['groupId']],
			  'deleteable' => $deleteable);
	    }
	}

	/* Figure out the owner */
	list ($ret, $owner) = $gallery->loadEntitiesById($item->getOwnerId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	list ($ret, $isAdmin) =
	    GalleryUserGroupMap::isUserInSiteAdminGroup($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if ($isAdmin) {
	    $canChangeOwner = true;
	} else {
	    $canChangeOwner = false;
	}
	
	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('item', $item->getMemberData());
	$this->_setTemplateVariable('owner', $owner->getMemberData());
	$this->_setTemplateVariable('canChangeOwner', $canChangeOwner);
	$this->_setTemplateVariable('userPermissions', $userPermissions);
	$this->_setTemplateVariable('groupPermissions', $groupPermissions);
	$this->_setTemplateVariable('allPermissions', $allPermissions);
	$this->_setTemplateVariable('controller', 'core:ItemEditPermissions');
	$html = $this->_renderTemplate('core', 'ItemEditPermissions.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
