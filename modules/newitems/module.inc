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
 * @package NewItems
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * Add new/updated image in summary info for new/updated items.
 * New sort option to put new items in front, follwed by another sort.
 * Thanks to Felix Rabinovich (virshu) for the idea.
 *
 * @package NewItems
 */
class NewItemsModule extends GalleryModule {

    function NewItemsModule() {
	global $gallery;

	$this->setId('newitems');
	$this->setName($gallery->i18n('New Items'));
	$this->setDescription($gallery->i18n('Highlight new/updated Gallery items'));
	$this->setVersion('0.2.1');
	$this->setGroup('display', $gallery->i18n('Display'));
	$this->setCallbacks('performFactoryRegistrations|getSiteAdminViews|getItemSummaries');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	/* Register sort order */
	GalleryCoreApi::registerFactoryImplementation(
	    'GallerySortInterface_1_0', 'NewItemsSortOrder', 'NewItems',
	    dirname(__FILE__) . '/classes/NewItemsSortOrder.class');
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	if (!isset($currentVersion)) {
	    foreach (array('days.new' => '7',
			   'days.updated' => '7' )
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
     * @see GalleryModule::deactivate()
     */
    function deactivate() {
	require_once(dirname(__FILE__) . '/classes/NewItemsHelper.class');
	list ($ret, $count) = NewItemsHelper::fetchAlbumCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	list ($ret, $default) = GalleryCoreApi::getPluginParameter('module', 'core', 'default.orderBy');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($count > 0 || $default == 'NewItems') {
	    // Can't deactivate if NewItems sort is in use..
	    return array(GalleryStatus::success(),
			 array('view' => 'core:SiteAdmin',
			       'subView' => 'newitems:NewItemsSiteAdmin'));
	}

	list ($ret, $redirect) = parent::deactivate();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), $redirect);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('New Items'),
				 'view' => 'newitems:NewItemsSiteAdmin')));
    }

    /**
     * @see GalleryModule::getItemSummaries()
     */
    function getItemSummaries($items) {
	global $gallery;
	$urlGenerator = $gallery->getUrlGenerator();
	$newImage = $urlGenerator->generateUrl(
				   array('href' => 'modules/newitems/images/new.gif'), false);
	$updatedImage = $urlGenerator->generateUrl(
				       array('href' => 'modules/newitems/images/updated.gif'), false);

	list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters('module', 'newitems');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$newTime = time() - $param['days.new'] * 86400;
	$updatedTime = time() - $param['days.updated'] * 86400;

	$newAltString = $this->translate('New');
	$updatedAltString = $this->translate('Updated');

	$summaries = array();
	foreach ($items as $item) {
	    if ($param['days.new'] > 0 && $item->getCreationTimestamp() > $newTime) {
		$summaries[$item->getId()] = sprintf('<img src="%s" alt="%s"/>',
						     $newImage,
						     $newAltString);
	    } else if ($param['days.updated'] > 0 && $item->getModificationTimestamp() > $updatedTime) {
		$summaries[$item->getId()] = sprintf('<img src="%s" alt="%s"/>',
						     $updatedImage,
						     $updatedAltString);
	    }
	}
	return array(GalleryStatus::success(), $summaries);
    }
}
?>
