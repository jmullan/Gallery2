<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
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

GalleryCoreApi::requireOnce('modules/notification/classes/NotificationHelper.class');

/**
 * This controller handles event / method preferences for the user on a per-item basis.
 * @package Notification
 * @subpackage UserInterface
 * @author Zimzat <zimzat@zimzat.com>
 * @author Tim Almdal <tnalmdal@shaw.ca>
 * @version $Revision$
 */
class NotificationItemAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	$status = $error = array();
	
	/* Check that the user is logged in */
	list ($ret, $userId) = NotificationHelper::getUserIdCheck();
	if ($ret) {
	    return array($ret, null);
	}

	/* Is the user an administrator */
	list ($ret, $isAdminGroup) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret) {
	    return array($ret, null);
	}

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId, 'GalleryItem');
	if ($ret) {
	    return array($ret, null);
	}

	$returnOption = 'redirect';

	if (!empty($form['action']['save'])) {
	    foreach ($form['notifications'] as $i => $notification) {
		if (empty($notification['oldSubscribed']) ^ empty($notification['subscribed'])) {
		    list ($ret, $hints) = 
			GalleryCoreApi::getFactoryDefinitionHints('NotificationEvent_1_0',
								  $notification['name']);
		    if ($ret) {
			return array($ret, null);
		    }

		    if (empty($notification['subscribed'])) {
			$ret = NotificationHelper::unsubscribe($userId, $itemId, $hints[0], 
						    $notification['name'], $notification['handler'],
						    !empty($notification['recursive']));
		    } else {
			$authorized = $isAdminGroup;
			if (!$authorized) {
			    list ($ret, $instance) = GalleryCoreApi::newFactoryInstanceById(
						    'NotificationEvent_1_0', $notification['name']);
			    if ($ret) {
				return array($ret, null);
			    }

			    $permission = $instance->getPermission();
			    if (!empty($permission)) {
				list ($ret, $authorized) = 
				    GalleryCoreApi::hasItemPermission($itemId, $permission);
				if ($ret) {
				    return array($ret, null);
				}
			    }
			}
			if ($authorized) {
			    $ret = NotificationHelper::subscribe($userId, $itemId, $hints[0], 
						    $notification['name'], $notification['handler'],
						    !empty($notification['recursive']));
			} else {
			    $error[] = 'form[error][notifications][' . $i . '][notAuthorized]';
			    $ret = null;
			}
		    }
		    if ($ret) {
			return array($ret, null);
		    }
		}
	    }

	    if (empty($error)) {
		/* Alert of the changes we have done. */
		$status['saved'] = 1;
		$returnOption = 'redirect';
	    } else {
		$returnOption = 'delegate';
	    }
	}

	$results[$returnOption] = array('view' => 'core.ItemAdmin', 
					'subView' => 'notification.NotificationItemAdmin',
					'itemId' => $itemId);
	$results['status'] = $status;
	$results['error'] = $error;

	return array(null, $results);
    }
}

/**
 * This view shows all event / method preferences for the user on a per-item basis.
 */
class NotificationItemAdminView extends GalleryView {
    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	if ($form['formName'] != 'NotificationItemAdmin') {
	    $ret = $this->_initializeForm($form);
	    if ($ret) {
		return array($ret, null);
	    }
	}

	$template->setVariable('controller', 'notification.NotificationItemAdmin');
	return array(null, 
		     array('body' => 'modules/notification/templates/NotificationItemAdmin.tpl'));
    }

    /**
     * Helper function to initialize the form
     * @param array $form the form values
     * @param boolean $isAdminGroup flag for whether the uers is in the Admin group or not.
     * @return GalleryStatus
     */
    function _initializeForm(&$form) {
	$form['formName'] = 'NotificationItemAdmin';
	
	/* Check that the user is logged in */
	list ($ret, $userId) = NotificationHelper::getUserIdCheck();
	if ($ret) {
	    return $ret;
	}

	/* Is the user an administrator */
	list ($ret, $isAdminGroup) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret) {
	    return $ret;
	}

	list ($ret, $notifications) = NotificationHelper::getEnabledNotifications();
	if ($ret) {
	    return $ret;
	}

	$itemId = (int)GalleryUtilities::getRequestVariables('itemId');
	list ($ret, $item) = GalleryCoreApi::loadEntitiesById($itemId, 'GalleryItem');
	if ($ret) {
	    return $ret;
	}

	/* Subscriptions */
	list ($ret, $subscriptions) = NotificationHelper::getSubscriptions($userId, $itemId);
	if ($ret) {
	    return $ret;
	}

	/* Events */
	$form['notifications'] = array();
	$i = 0;
	foreach ($notifications as $notificationName => $notification) {
	    list ($ret, $instance) = GalleryCoreApi::newFactoryInstanceById(
						     'NotificationEvent_1_0', $notificationName);
	    if ($ret) {
		return $ret;
	    }

	    if ($instance->isGlobal($item)) {
		continue;
	    }

	    if (!$isAdminGroup) {
		$permission = $instance->getPermission();
		if (empty($permission)) {
		    continue;
		}
		list ($ret, $authorized) = GalleryCoreApi::hasItemPermission($itemId, $permission);
		if ($ret) {
		    return $ret;
		}
		if (!$authorized) {
		    continue;
		}
	    }

	    list ($ret, $description) = $instance->getDescription();
	    if ($ret) {
		return $ret;
	    }
	    foreach ($notification as $handlerName => $status) {
		if (empty($status['enabled']) 
			|| (empty($status['public']) && !$isAdminGroup)) {
		    continue;
		}

		list ($ret, $handler) = 
		    GalleryCoreApi::newFactoryInstance('NotificationHandler_1_0', $handlerName);
		if ($ret) {
		    return $ret;
		}
		list ($ret, $handlerDescription) = $handler->getDescription();
		if ($ret) {
		    return $ret;
		}
		$form['notifications'][++$i] = array('name' => $notificationName,
						 'description' => $description,
						 'handler' => $handlerName,
						 'handlerDescription' => $handlerDescription,
					'subscribed' => !empty($subscriptions[$notificationName]));
	    }
	}

	return null;
    }
}
?>
