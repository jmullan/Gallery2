<?php
/*
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/**
 * @version $Revision$ $Date$
 * @package Ecard
 * @author Nico Kaiser <nico@siriux.net>
 * @author Dariush Molavi <dari@nukedgallery.net>
 */

/**
 * eCard plugin
 * 
 * @package Ecard
 */

class EcardModule extends GalleryModule {

    function EcardModule() {
	global $gallery;
	
	$this->setId('ecard');
	$this->setName($gallery->i18n('eCard'));
	$this->setDescription($gallery->i18n('Send photos as eCards'));
	
	$this->setVersion('0.0.9');
	$this->setGroup('commerce', $gallery->i18n('Commerce'));
	$this->setCallbacks('getItemLinks|getSiteAdminViews');
	$this->setRequiredCoreApi(array(7, 0));
	$this->setRequiredModuleApi(array(3, 0));
    }
    
    /**
     * @see GalleryModule::upgrade
     */
    function upgrade($currentVersion) {
	global $gallery;

	if (!isset($currentVersion)) {
	    $currentVersion = '0';
	}

	/* Set default parameters */
	list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters('module', 'ecard');
	if ($ret) {
	    return $ret;
	}
	foreach (array(
		'from' => 'Gallery &lt;gallery&gt;',
		'subject' => 'You have been sent an eCard',
		'bcc' => '',
		'header' => 'Hi %toName%!<br />%fromName% (%from%) has sent you an eCard:',
		'footer' => 'This eCard was sent with Gallery 2 - Your photos on your website',
		'format' => 'html',
		'validation.level' => 'HIGH')
		as $key => $value) {
	    if (!isset($params[$key])) {
		$ret = $this->setParameter($key, $value);
		if ($ret) {
		    return $ret;
		}
	    }
	}
	

	switch ($currentVersion) {

	case '0':
	case '0.0.6':
	case '0.0.7':
	    list ($ret, $coreParams) = GalleryCoreApi::fetchAllPluginParameters('module', 'core');
	    if ($ret) {
		return $ret;
	    }

	    /* Register our permissions */
	    $ret = GalleryCoreApi::registerPermission($this->getId(), 
		'ecard.send', $gallery->i18n('[ecard] Send eCards'), 0, array());
	    if ($ret) {
		return $ret;
	    }
	    /* Give everybody permission by default */
	    $ret = GalleryCoreApi::addGroupPermission(
		$coreParams['id.rootAlbum'], $coreParams['id.everybodyGroup'],
		'ecard.send', true);
	    if ($ret) {
		return $ret;
	    }
	    break;

	case '0.0.8':
		break;
	case 'end of upgrade path':
	    break;

	default:
	    return GalleryCoreApi::error(ERROR_BAD_PLUGIN, __FILE__, __LINE__,
		sprintf('Unknown module version %s', $currentVersion));
	}
	
	return null;
    }
        
    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items, $wantsDetailedLinks, $permissions) {
	$links = array();
	foreach ($items as $item) {
	    if (GalleryUtilities::isA($item, 'GalleryPhotoItem') && !isset($permissions[$item->getId()]['ecard.send']) && isset($wantsDetailedLinks[$item->getId()])) {
		$params['view'] = 'ecard.SendEcard';
		$params['itemId'] = $item->getId();
		$params['return'] = 1;
		$links[$item->getId()][] = array('text' => $this->translate('Send as eCard'), 'params' => $params);
	    }
	}

	return array(null, $links);
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	return array(null, array(array('name' => $this->translate('eCard'),
				       'view' => 'ecard.AdminEcard')));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'CaptchaAdminOption', 'EcardCaptchaAdminOption', 'EcardCaptchaAdminOption',
	    'modules/ecard/classes/EcardCaptchaAdminOption.class', 'ecard', null);
	if ($ret) {
	    return $ret;
	}

	return null;
    }

    /**
     * @see GalleryModule::activate
     */
    function activate($postActivationEvent=true) {

	list ($ret, $redirect) = parent::activate($postActivationEvent);
	if ($ret) {
	    return array($ret, null);
	}

	return array(null, array());
    }

}
?>