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
 * @package RandomHighlight
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * RandomHighlight module - periodically change the album highlight
 *
 * @package RandomHighlight
 */
class RandomHighlightModule extends GalleryModule {

    function RandomHighlightModule() {
	global $gallery;
	$this->setId('randomhighlight');
	$this->setName('Random Highlight');
	$this->setDescription($gallery->i18n('Periodically change the album highlight'));
	$this->setVersion('0.9.3');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('getSiteAdminViews');
	$this->setRequiredCoreApi(array(5, 0));
	$this->setRequiredModuleApi(array(0, 10));
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	global $gallery;

	list ($ret, $params) =
	    GalleryCoreApi::fetchAllPluginParameters('module', 'randomhighlight');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	foreach (array('duration' => 7200 /* 2 hours */) as $key => $value) {
	    if (!isset($params[$key])) {
		$ret = $this->setParameter($key, $value);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
	    }
	}

	switch ($currentVersion) {
	case '0.5':
	case '0.8.1':
	case '0.8.2':
	case '0.8.3':
	case '0.8.4':
	case '0.8.5':
	case '0.8.6':
	    /* Changed from RandomHighlightDerivativeImage entity type to onLoadHandler */
	    $storage =& $gallery->getStorage();
	    $query = 'UPDATE [GalleryEntity]
		SET [::entityType] = \'GalleryDerivativeImage\',
		    [::onLoadHandlers] = \'|RandomHighlight|\'
		WHERE [GalleryEntity::entityType] = \'RandomHighlightDerivativeImage\'
		  AND [GalleryEntity::onLoadHandlers] IS NULL';
	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $handlers) = $storage->getFunctionSql('CONCAT',
		array('[GalleryEntity::onLoadHandlers]', "'RandomHighlight|'"));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $query = 'UPDATE [GalleryEntity]
		SET [::entityType] = \'GalleryDerivativeImage\',
		    [::onLoadHandlers] = ' . $handlers . '
		WHERE [GalleryEntity::entityType] = \'RandomHighlightDerivativeImage\'
		  AND [GalleryEntity::onLoadHandlers] IS NOT NULL';
	    $ret = $storage->execute($query);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	case '0.9.0':
	case '0.9.1':
	case '0.9.2':
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::performFactoryRegistrations()
     */
    function performFactoryRegistrations() {
	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'GalleryOnLoadHandler', 'RandomHighlightModule', 'RandomHighlight',
	    'modules/randomhighlight/module.inc', 'randomhighlight', null);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$ret = GalleryCoreApi::registerFactoryImplementation(
	    'ItemEditOption', 'RandomHighlightOption', 'RandomHighlightOption',
	    'modules/randomhighlight/RandomHighlightOption.inc', 'randomhighlight',
	    array('ItemEditAlbum'));
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	return GalleryStatus::success();
    }

    /**
     * @see GalleryModule::getOnLoadHandlerIds()
     */
    function getOnLoadHandlerIds() {
	return array('RandomHighlight');
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall()
     */
    function isRecommendedDuringInstall() {
	return true;
    }

    /**
     * @see GalleryModule::autoConfigure()
     */
    function autoConfigure() {
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    }

    /**
     * @see GalleryModule::getSiteAdminViews()
     */
    function getSiteAdminViews() {
	return array(GalleryStatus::success(),
		     array(array('name' => $this->translate('Random Highlight'),
				 'view' => 'randomhighlight:RandomHighlightSiteAdmin')));
    }

    /**
     * Check age and pick new highlight if needed..
     */
    function onLoad(&$thumbnail) {
	static $loop = array();
	$picknew = false;
	$id = $thumbnail->getId();
	list ($ret, $duration) = $this->getParameter('duration');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if (time() - $thumbnail->getModificationTimestamp() > $duration && !isset($loop[$id])) {
	    /* Lock and refresh to ensure another request didn't just update highlight */
	    list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($id);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $loop[$id] = true;
	    list ($ret, $refresh) = $thumbnail->refresh();
	    if ($ret->isError()) {
		GalleryCoreApi::releaseLocks($lockId);
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    if ($refresh->getSerialNumber() == $thumbnail->getSerialNumber()) {
		$picknew = true;
	    }
	}
	if ($picknew) {
	    list ($ret, $album) = GalleryCoreApi::loadEntitiesById($thumbnail->getParentId());
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($album);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    list ($ret, $thumbnails) = GalleryCoreApi::fetchThumbnailsByItemIds($childIds);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    if (empty($thumbnails)) {
		return GalleryStatus::success();
	    }
	    $thumbnails = array_values($thumbnails);
	    $highlight = $thumbnails[rand(0, count($thumbnails)-1)];

	    $thumbnail->setDerivativeSourceId($highlight->getId());
	    GalleryCoreApi::estimateDerivativeDimensions($thumbnail, $highlight);
	    $thumbnail->save();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $ret = GalleryCoreApi::expireDerivativeTreeBySourceIds(array($thumbnail->getId()));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	if (isset($lockId)) {
	    $ret = GalleryCoreApi::releaseLocks($lockId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	return GalleryStatus::success();
    }
}
?>
