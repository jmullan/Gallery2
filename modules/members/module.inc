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
 * @package Members
 * @author Robert Balousek <rbalousek@hotmail.com>
 */

/**
 * The implementation of the core-module
 *
 * @package Members
 */
class MembersModule extends GalleryModule {

    function MembersModule() {
	global $gallery;

	$this->setId('members');
	$this->setName('Members');
	$this->setDescription($gallery->i18n('Members List and Profiles'));
	$this->setVersion('0.8');
	$this->setGroup('gallery', $gallery->i18n('Gallery'));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;
    	
	if (!isset($currentVersion)) {
	    list ($ret, $viewSelectedGroupId) = 
		GalleryCoreApi::getPluginParameter('module', 'core', 'id.everybodyGroup');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    foreach (array('canViewMembersModule' => $viewSelectedGroupId,
			   'canViewEmailAddress' => 0) as $key => $value) {
		$ret = $this->setModuleParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall
     */
    function isRecommendedDuringInstall() {
	return true;
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
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryMembersHelper.class');
	list ($ret, $result) = GalleryMembersHelper::canViewMembersModule($gallery->getActiveUserId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$links = array();
	if ($result) {
	    $links[] = array('text' => $this->translate('Members List '),
			     'params' => array('view' => 'members:MembersList'));
	}
	return array(GalleryStatus::success(), $links);    
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Members'),
				 'view' => 'members:AdminMembers')));
    }
}
?>
