<?php
/*
 * $RCSfile$
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

/**
 * @version $Revision$ $Date$
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This edit plugin allows you to customize the photo's thumbnail
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemEditPhotoThumbnail extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	global $gallery;

	$status = null;
	$error = array();

	if (isset($form['action']['crop'])) {
	    /* Load the thumbnail */
	    list ($ret, $thumbnails) =
		GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
		
	    if (!empty($thumbnails)) {
		$thumbnail = $thumbnails[$item->getId()];

		list ($ret, $lock) = GalleryCoreApi::acquireWriteLock($thumbnail->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		list ($ret, $thumbnail) = $thumbnail->refresh();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		$cropX = !empty($form['crop']['x']) ? $form['crop']['x'] : 0;
		$cropY = !empty($form['crop']['y']) ? $form['crop']['y'] : 0;
		$cropWidth = !empty($form['crop']['width']) ? $form['crop']['width'] : $item->getWidth();
		$cropHeight = !empty($form['crop']['height']) ? $form['crop']['height'] : $item->getHeight();

		// TODO: Remove the crop if it's the same dimensions as the original
		list ($ret, $operations) =
		    GalleryCoreApi::mergeDerivativeOperations($thumbnail->getDerivativeOperations(),
							      sprintf('crop|%s,%s,%s,%s',
								      $cropX,
								      $cropY,
								      $cropWidth,
								      $cropHeight),
							      true);
		
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		$thumbnail->setDerivativeOperations($operations);

		$ret = $thumbnail->save();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		$ret = GalleryCoreApi::releaseLocks($lock);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		/* Figure out where to redirect upon success */
		list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		$status = $module->translate('Thumbnail cropped successfully');
	    }
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	global $gallery;

	$ItemEditPhotoThumbnail = array();
	$ItemEditPhotoThumbnail['showApplet'] = $thumbnail != null;

	list ($ret, $ItemEditPhotoThumbnail['isAdmin']) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'ItemEditPhotoThumbnail') {
	    /* First time around, reset the form */
	    $form['formName'] = 'ItemEditPhotoThumbnail';
	}
	
	$targetThumbnailSize = 0;
	$crop = array();
	if (preg_match('/thumbnail\|(\d+)/',
		       $thumbnail->getDerivativeOperations(),
		       $matches)) {
	    $targetThumbnailSize = $matches[1];
	}
	    
	if (preg_match('/crop\|(\d+),(\d+),(\d+),(\d+)/',
		       $thumbnail->getDerivativeOperations(),
		       $matches)) {
	    $crop['left'] = $matches[1];
	    $crop['top'] = $matches[2];
	    $crop['width'] = $matches[3];
	    $crop['height'] = $matches[4];
	}
	    
	list ($ret, $source) = GalleryCoreApi::loadEntitiesById($thumbnail->getDerivativeSourceId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	    
	/*
	 * Try to find a derivative that is close to 600x450 pixels that we can use.  Failing that, use
	 * the original image.
	 */
	list ($ret, $derivativeTable) =
	    GalleryCoreApi::fetchDerivativesBySourceIds(array($item->getId()),
							array(DERIVATIVE_TYPE_IMAGE_RESIZE));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$selected = array();
	if (!empty($derivativeTable[$item->getId()])) {
	    $lowestDelta = null;
	    $targetPixels = 600 * 450;
	    foreach ($derivativeTable[$item->getId()] as $derivative) {
		list ($width, $height) = array($derivative->getWidth(), $derivative->getHeight());
		if (empty($width)) {
		    /* Perhaps this derivative hasn't been calculated yet .. try calculating it */
		    list ($ret, $derivative) =
			GalleryCoreApi::rebuildDerivativeCacheIfNotCurrent($derivative->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    list ($width, $height) = array($derivative->getWidth(), $derivative->getHeight());
		    if (empty($width)) {
			/* We have no idea .. skip it */
			continue;
		    }
		}
		$delta = abs($targetPixels - ($width * $height));

		if ($lowestDelta == null || $delta < $lowestDelta) {
		    $selected = $derivative->getId();
		    $lowestDelta = $delta;
		}
	    }
	}

	if (empty($selected)) {
	    $selected = $source->getId();
	}

	/*
	 * It's possible that the source was created before we had an appropriate image toolkit, so its
	 * dimensions can be set to zero, which will cause us problems.  In that case, try rescanning it.
	 */
	$width = $source->getWidth();
	if (empty($width)) {
	    list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($source->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    list ($ret, $source) = $source->refresh();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $ret = $source->rescan();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $ret = $source->save();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $ret = GalleryCoreApi::releaseLocks($lockId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	$width = $source->getWidth();
	if (empty($width)) {
	    $ItemEditPhotoThumbnail['editThumbnail']['can']['crop'] = false;
	} else {
	    $ItemEditPhotoThumbnail['editThumbnail']['can']['crop'] = true;
	    if (empty($crop)) {
		$crop['left'] = 0;
		$crop['top'] = 0;
		$crop['width'] = $source->getWidth();
		$crop['height'] = $source->getHeight();
	    }

	    /*
	     * When we make the url for the image, force the session id into it.  Otherwise, the IE JVM will
	     * send a request without the session cookie, then the server will make a new session and send
	     * that cookie back to the JVM, which will overwrite the browser's session with it, effectively
	     * logging out the user.
	     */
	    $urlGenerator = $gallery->getUrlGenerator();
	    $url = $urlGenerator->generateUrl(array('view' => 'core:DownloadItem', 'itemId' => $selected), true);
	    
	    $ItemEditPhotoThumbnail['editThumbnail']['appletCodeBase'] =
		GalleryUtilities::convertPathToUrl(dirname(__FILE__)) . '/plugins';
	    $ItemEditPhotoThumbnail['editThumbnail']['appletJarFile'] = 'ImageCrop.jar';
	    $ItemEditPhotoThumbnail['editThumbnail']['imageUrl'] = $url;
	    $ItemEditPhotoThumbnail['editThumbnail']['imageWidth'] = $source->getWidth();
	    $ItemEditPhotoThumbnail['editThumbnail']['imageHeight'] = $source->getHeight();
	    $ItemEditPhotoThumbnail['editThumbnail']['cropLeft'] = $crop['left'];
	    $ItemEditPhotoThumbnail['editThumbnail']['cropTop'] = $crop['top'];
	    $ItemEditPhotoThumbnail['editThumbnail']['cropWidth'] = $crop['width'];
	    $ItemEditPhotoThumbnail['editThumbnail']['cropHeight'] = $crop['height'];
	    $ItemEditPhotoThumbnail['editThumbnail']['targetThumbnailSize'] = $targetThumbnailSize;

	    $aspectlist = array();
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    $aspectRatioList[] = array('label' => $module->translate('Screen 4x3'),
				       'width' => 4,
				       'height' => 3);
	    $aspectRatioList[] = array('label' => $module->translate('Photo 5x3'),
				       'width' => 5,
				       'height' => 3);
	    $aspectRatioList[] = array('label' => $module->translate('Photo 6x4'),
				       'width' => 6,
				       'height' => 4);
	    $aspectRatioList[] = array('label' => $module->translate('Photo 7x5'),
				       'width' => 7,
				       'height' => 5);
	    $aspectRatioList[] = array('label' => $module->translate('Photo 10x8'),
				       'width' => 10,
				       'height' => 8);
	    $aspectRatioList[] = array('label' => $module->translate('HDTV 16x9'),
				       'width' => 16,
				       'height' => 9);
	    $aspectRatioList[] = array('label' => $module->translate('CinemaScope 2.35x1'),
				       'width' => 47,
				       'height' => 20);
	    $aspectRatioList[] = array('label' => $module->translate('Square 1x1'),
				       'width' => 1,
				       'height' => 1);
	    $aspectRatioList[] = array('label' => $module->translate('As Image'),
				       'width' => $item->getWidth(),
				       'height' => $item->getHeight());
	    $ItemEditPhotoThumbnail['editThumbnail']['aspectRatioList'] = $aspectRatioList;

	    $orientationList = array();
	    $orientationList['landscape'] = $module->translate("Landscape");
	    $orientationList['portrait'] = $module->translate("Portrait");
	    $ItemEditPhotoThumbnail['editThumbnail']['orientationList'] = $orientationList;


	    /*
	     * Figure out which aspect ratio / orientation is closest to the current crop
	     * settings so that we can start out with those values selected in the dropdowns.
	     */
	    $currentAspect = round($crop['width'] / $crop['height'], 2);
	    $i = 0;

	    /* Set defaults */
	    $selectedAspect = 0;
	    $selectedOrientation = "portrait";
	    $ItemEditPhotoThumbnail['editThumbnail']['cropRatioWidth'] = $aspectRatioList[0]['width'];
	    $ItemEditPhotoThumbnail['editThumbnail']['cropRatioHeight'] = $aspectRatioList[0]['height'];
	    
	    foreach ($aspectRatioList as $aspect) {
		$landscapeCompare = round($aspect['width'] / $aspect['height'], 2);
		$portraitCompare = round($aspect['height'] / $aspect['width'], 2);
		if (abs($currentAspect - $landscapeCompare) <= 0.03) {
		    $selectedAspect = $i;
		    $selectedOrientation = "landscape";
		    break;
		} else if (abs($currentAspect - $portraitCompare) <= 0.03) {
		    $selectedAspect = $i;
		    $selectedOrientation = "portrait";
		    break;
		}
		$i++;
	    }
	    $ItemEditPhotoThumbnail['editThumbnail']['selectedAspect'] = $selectedAspect;
	    $ItemEditPhotoThumbnail['editThumbnail']['selectedOrientation'] = $selectedOrientation;
	    $ItemEditPhotoThumbnail['editThumbnail']['cropRatioWidth'] = $aspectRatioList[$selectedAspect]['width'];
	    $ItemEditPhotoThumbnail['editThumbnail']['cropRatioHeight'] = $aspectRatioList[$selectedAspect]['height'];
	} 

	$template->setVariable('ItemEditPhotoThumbnail', $ItemEditPhotoThumbnail);
	$template->setVariable('controller', 'core:ItemEditPhotoThumbnail');
	return array(GalleryStatus::success(), 'modules/core/templates/ItemEditPhotoThumbnail.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	return ($thumbnail != null && GalleryUtilities::isA($item, 'GalleryPhotoItem'));
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('Crop Thumbnail'));
    }
}
?>
