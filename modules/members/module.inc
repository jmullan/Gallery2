<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
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
	$this->setVersion('0.8.6');
	$this->setGroup('gallery', $this->translate('Gallery'));
	$this->setCallbacks('loadSystemContent|getSiteAdminViews');
	$this->setRequiredCoreApi(array(4, 0));
	$this->setRequiredModuleApi(array(0, 9));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	if (!isset($currentVersion)) {
	    list ($ret, $viewSelectedGroupId) =
		GalleryCoreApi::getPluginParameter('module', 'core', 'id.everybodyGroup');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach (array('canViewMembersModule' => $viewSelectedGroupId,
			   'canViewEmailAddress' => 0) as $key => $value) {
		$ret = $this->setParameter($key, $value);
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
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
        return array(GalleryStatus::success(),
	             array(array('name' => $this->translate('Members'),
		                 'view' => 'members:AdminMembers')));
    }

    /**
     * @see GalleryModule::loadSystemContent
     */
    function loadSystemContent(&$template) {
	global $gallery;
	$content = array();

	$view = GalleryUtilities::getRequestVariables('view');
	if ($view == 'members:MembersList' || $view == 'members:MembersProfile') {
	    return array(GalleryStatus::success(), array());
	}

	/* The "Members List" link */
        GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryMembersHelper.class');
        list ($ret, $canView) = GalleryMembersHelper::canViewMembersModule($gallery->getActiveUserId());
        if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$links = array();
        if ($canView) {
	    $links[] = array('text' => $this->translate('Members List'),
                             'params' => array('view' => 'members:MembersList',
					       'return' => true));
        }
	$MembersSystemContent['links'] = $links;

	/* The members count */
	list ($ret, $membersCount) = GalleryMembersHelper::getMembersCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$MembersSystemContent['membersCount'] = $membersCount;

	$template->setVariable('MembersSystemContent', $MembersSystemContent);

	$content = array();
	$content['members'] = 'modules/members/templates/MembersSystemContent.tpl';

	return array(GalleryStatus::success(), $content);
    }
}
?>
