<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
 * Metamorphose applet Copyright (C) 2000 Rüdiger Appel
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
	$this->setVersion('0.8.2');
	$this->setGroup('display', $this->translate('Display'));
	$this->setCallbacks('performFactoryRegistrations|getSiteAdminViews');
	$this->setRequiredCoreApi(array(0, 8));
	$this->setRequiredModuleApi(array(0, 8));
	
    }

    /**
     * @see GalleryModule::performFactoryRegistrations
     */
    function performFactoryRegistrations() {
	GalleryCoreApi::registerFactoryImplementation('GalleryEntity',
	    'RandomHighlightDerivativeImage', 'RandomHighlightDerivativeImage',
	    dirname(__FILE__) . '/classes/RandomHighlightDerivativeImage.class');
	GalleryCoreApi::registerFactoryImplementation('ItemEditPlugin',
	    'ItemEditRandomHighlight', 'ItemEditRandomHighlight',
	    dirname(__FILE__) . '/ItemEditRandomHighlight.inc');
    }

    /**
     * @see GalleryModule::upgrade()
     */
    function upgrade($currentVersion) {
	if (!isset($currentVersion)) {
	    $ret = $this->setParameter('duration', 10 * 60 * 60); /* 10 minutes */
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}
	return GalleryStatus::success();
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
     * @see GalleryModule::deactivate()
     */
    function deactivate() {
	require_once(dirname(__FILE__) . '/classes/RandomHighlightHelper.class');
	list ($ret, $count) = RandomHighlightHelper::fetchItemCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if ($count > 0) {
	    // Can't deactivate if randomhighlight derivatives exist..
	    return array(GalleryStatus::success(),
			 array('view' => 'core:SiteAdmin',
			       'subView' => 'randomhighlight:SiteAdminRandomHighlight'));
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
		     array(array('name' => $this->translate('Random Highlight'),
				 'view' => 'randomhighlight:SiteAdminRandomHighlight')));
    }
}
?>
