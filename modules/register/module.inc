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
 * @version $Revision$ $Date$
 * @package SelfRegistration
 * @author Sebastian Eichner <mailsp@sebastian-eichner.de>
 */

/**
 * The self-registration module
 *
 * @package SelfRegistration
 */
class RegisterModule extends GalleryModule {

    function RegisterModule() {
	global $gallery;

	$this->setId('register');
	$this->setName('Registration');
	$this->setDescription($gallery->i18n('New User Registration'));
	$this->setVersion('0.8.2');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('performFactoryRegistrations|getSystemLinks|' .
			    'getUserAdminViews|getSiteAdminViews');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
	
    }

    /**
     * @see GalleryModule::performFactoryRegistrations();
     */
    function performFactoryRegistrations() {
	$classDir = dirname(__FILE__) . '/classes/';

	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
						      'GalleryPendingUser',
						      'GalleryPendingUser',
						      $classDir . 'GalleryPendingUser.class');

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!isset($currentVersion)) {
	    foreach (array('confirmation' => 'admin',
			   'emailadmins' => 1,
			   'subject' => $this->translate('Account activation'),
			   'adminsubject' => $this->translate('New user registration'),
			   'from' => 'webmaster@' . $_SERVER['SERVER_NAME'])
			 as $key => $value) {
		$ret = $this->setParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }


    /**
     * @see GalleryModule::getSystemLinks
     */
    function getSystemLinks() {
	global $gallery;
	$links = array();

	list ($ret, $anonymousUserId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	// Only anonymous users will see the register link
	if ($gallery->getActiveUserId() == $anonymousUserId) {
	    $links[] = array('text' => $this->translate('Register'),
			     'params' => array('view' => 'core:UserAdmin',
					       'subview' => 'register:UserSelfRegistration',
					       'return' => 1, )
			    );
	}

	return array(GalleryStatus::success(), $links);
    }

    /**
     * @see GalleryModule::getUserAdminViews();
     */
    function getUserAdminViews($user) {
	global $gallery;
	$views = array();

	list ($ret, $anonymousUserId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	// Only anonymous users will see the register link
	if ($gallery->getActiveUserId() == $anonymousUserId) {
	    $views[] = array('name' => $this->translate('Register'),
			     'view' => 'register:UserSelfRegistration');
	}

	return array(GalleryStatus::success(), $views);
    }

    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Registration'),
				 'view' => 'register:AdminSelfRegistration')));
    }
}
?>
