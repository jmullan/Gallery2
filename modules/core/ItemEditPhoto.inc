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
 * This controller will handle the editing of a photo
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemEditPhotoController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	list ($itemId, $mode) = GalleryUtilities::getRequestVariables('itemId', 'mode');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Check to see if we have a preferred source */
	list ($ret, $preferredTable) = GalleryDerivativeHelper::fetchPreferredsByItemIds(
            array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$preferred = null;
	if (!empty($preferredTable[$item->getId()])) {
	    $preferred = $preferredTable[$item->getId()];
	}

	$status = array();
	$error = array();

	$remapSourceIds = array();
	$operation = null;
	/* Figure out which command we're taking */
	switch ($mode) {
	case 'editPhoto':
	    if (isset($form['action']['scale'])) {
		if (empty($form['scale']['size'])) {
		    $error[] = 'form.error.scale.size.missing';
		} else if (!is_numeric($form['scale']['size']) || $form['scale']['size'] < 1) {
		    $error[] = 'form.error.scale.size.invalid';
		} else {
		    $operation = 'scale';
		    $args = array($form['scale']['size']);
		}
	    } else if (isset($form['action']['rotate']['clockwise'])) {
		$operation = 'rotate';
		$args = array(90);
	    } else if (isset($form['action']['rotate']['counterClockwise'])) {
		$operation = 'rotate';
		$args = array(-90);
	    } else if (isset($form['action']['rotate']['flip'])) {
		$operation = 'rotate';
		$args = array(180);
	    } else if (isset($form['action']['revertToOriginal'])) {
		if (!empty($preferred)) {
		    $ret = $gallery->deleteEntityById($preferred->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $remapSourceIds = array($preferred->getId(), $item->getId(), null);

		    /* Figure out where to redirect upon success */
		    $redirect['view'] = 'core:ItemAdmin';
		    $redirect['subView'] = 'core:ItemEditPhoto';
		    $redirect['mode'] = $mode;
		    $redirect['itemId'] = $itemId;
		    $status['editPhoto']['revertedPhoto'] = 1;
		}
	    }

	    /*
	     * If we have a command, then apply it to the correct object.
	     */
	    if (!empty($operation)) {
		/*
		 * If we don't have a preferred and we're preserving, then create
		 * one
		 */
		$lockIds = array();
		if (empty($preferred) && empty($form['preserveOriginal'])) {

		    /*
		     * We have no preferred photo, and we're not preserving the
		     * original.  So, we're changing the original photo here.  Make
		     * the appropriate change, then expire the derivative tree. 
		     */

		    /* Get the path of the source */
		    list($ret, $sourcePath) = $item->fetchPath();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Get the appropriate toolkit */
		    list ($ret, $toolkit) =
			GalleryToolkitHelper::getToolkitByOperation($item->getMimeType(), $operation);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (!isset($toolkit)) {
			/* This should never happen */
			return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null);
		    }

		    /* Perform the operation */
		    list ($ret, $outputMimeType) =
			$toolkit->performOperation($item->getMimeType(),
						   $operation,
						   $sourcePath,
						   $sourcePath,
						   $args);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $item->setMimeType($outputMimeType);
		
		    /* Get the item to rescan its data object */
		    $ret = $item->rescan();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Save the item, if it's modified */
		    if ($item->isModified()) {
			list ($ret, $lockId) = $gallery->acquireWriteLock($item->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    
			$ret = $item->save();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$ret = $gallery->releaseLocks($lockId);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    $ret = GalleryDerivativeHelper::expireDerivativeTreeBySourceIds(array($item->getId()));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Remember the source id for later */
		    $sourceId = $item->getId();
		} else {
		    /* If we have no preferred, then create one */
		    if (empty($preferred)) {
			list ($ret, $preferred) = GalleryFactory::newInstance('GalleryEntity', 'GalleryDerivativeImage');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    
			if (!isset($preferred)) {
			    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					 null);
			}
		
			$ret = $preferred->create($item->getId(), DERIVATIVE_TYPE_IMAGE_PREFERRED);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    
			$preferred->setDerivativeSourceId($item->getId());
			$preferred->setDerivativeMimeType($item->getMimeType());
			$remapSourceIds = array($item->getId(), $preferred->getId());
		    } else {
			/*
			 * Otherwise, lock the preferred so that we can modify it
			 */
			list ($ret, $lockIds[]) = $gallery->acquireWriteLock($preferred->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$ret = $preferred->expireCache();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    $ret = $preferred->mergeOperation($operation, $args);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		
		    $ret = $preferred->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (!empty($lockIds)) {
			$ret = $gallery->releaseLocks($lockIds);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    /*
		     * Perform a final check -- if the new derivative is exactly
		     * the same as the original then delete it.
		     */
		    $derivativeOperations = $preferred->getDerivativeOperations();
		    if (empty($derivativeOperations)) {
			$ret = $gallery->deleteEntityById($preferred->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			/*
			 * If we were remapping the source ids, that means that we
			 * just created a new preferred, so stop doing that.
			 * Otherwise, remap the preferred id back to the item id.
			 */
			if (empty($remapSourceIds)) {
			    $remapSourceIds = array($preferred->getId(), $item->getId(), null);
			} else {
			    $remapSourceIds = array();
			}

			/* Remember the new source id for later */
			$sourceId = $item->getId();
		    } else {
			/* Remember the preferred id for later */
			$sourceId = $preferred->getId();
		    }
		}

		/*
		 * It's possible that the operation we did will cause damage to derivatives down
		 * the tree, (eg, when we rotate a source that has a cropped derivative -- the
		 * cropping rules will no longer apply and can be broken such that the toolkit
		 * will fail to be able to generate the image).  So remove the crop operation from
		 * any derived images in that case.
		 */
		if ($operation == 'rotate') {
		    $ret = GalleryDerivativeHelper::pruneDerivativeOperations(array($item->getId()), array('crop'));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		/* Figure out where to redirect upon success */
		$redirect['view'] = 'core:ItemAdmin';
		$redirect['subView'] = 'core:ItemEditPhoto';
		$redirect['mode'] = $mode;
		$redirect['itemId'] = $itemId;
		switch ($operation) {
		case 'rotate':
		    $status['editPhoto']['rotatedPhoto'] = 1;
		    break;

		case 'scale':
		    $status['editPhoto']['scaledPhoto'] = 1;
		    break;
		}
	    }

	    /* Check to see if we need to remap any derivative source ids */
	    if (!empty($remapSourceIds)) {
		$ret = GalleryDerivativeHelper::remapSourceIds($remapSourceIds[0],
							       $remapSourceIds[1]);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	case 'editSizes':
	    if (isset($form['action']['save'])) {

		/* Validate the input data. */
		if (empty($form['thumbnail']['size'])) {
		    $error[] = 'form.error.thumbnail.size.missing';
		} else if (!is_numeric($form['thumbnail']['size'])) {
		    $error[] = 'form.error.thumbnail.size.invalid';
		}


		for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		    if (empty($form['resizes'][$i]['active'])) {
			continue;
		    }

		    if (empty($form['resizes'][$i]['size'])) {
			$error[] = sprintf('form.error.resizes.%d.size.missing', $i);
		    } else if (!is_numeric($form['resizes'][$i]['size']) || $form['resizes'][$i]['size'] <= 0) {
			$error[] = sprintf('form.error.resizes.%d.size.invalid', $i);
		    }
		}
	    
		if (empty($error)) {
		    /* Load the thumbnail */
		    list ($ret, $thumbTable) =
			GalleryDerivativeHelper::fetchThumbnailsByItemIds($item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (isset($thumbTable[$item->getId()])) {
			/* Change the thumbnail */
			$thumbnail = $thumbTable[$item->getId()];
			$thumbnail->setDerivativeOperations('thumbnail|' . $form['thumbnail']['size']);

			if ($thumbnail->isModified()) {
			    list ($ret, $lockId) = $gallery->acquireWriteLock($thumbnail->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    $thumbnail->expireCache();
			    $ret = $thumbnail->save();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    $ret = $gallery->releaseLocks(array($lockId));
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
		    } else {
			/* Create the thumbnail */
			list ($ret, $toolkit, $outputMimeType) =
			    GalleryToolkitHelper::getToolkitByOperation($item->getMimeType(), 'thumbnail');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			if (isset($toolkit)) {
			    list ($ret, $thumbnail) = 
				GalleryFactory::newInstance('GalleryEntity', 'GalleryDerivativeImage');
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			
			    if (!isset($thumbnail)) {
				return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					     null);
			    }  
			
			    $ret = $thumbnail->create($item->getId(), DERIVATIVE_TYPE_IMAGE_THUMBNAIL);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }

			    $thumbnail->setDerivativeMimeType($outputMimeType);
			    $thumbnail->setDerivativeSourceId($item->getId());
			    $thumbnail->setDerivativeOperations('thumbnail|' . $form['thumbnail']['size']);
			
			    $ret = $thumbnail->save();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
		    }

		    /* Get and delete all current resizes */
		    list ($ret, $resizesTable) =
			GalleryDerivativeHelper::fetchResizesByItemIds($item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    foreach ($resizesTable as $resizes) {
			foreach ($resizes as $resize) {
			    $ret = $gallery->deleteEntityById($resize->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
		    }

		    /*
		     * Make sure that we have a toolkit before adding back
		     * the resizes
		     */
		    list ($ret, $toolkit, $outputMimeType) =
			GalleryToolkitHelper::getToolkitByOperation($item->getMimeType(), 'scale');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (isset($toolkit)) {
			/* Add the new resizes */
			for ($i = 0; $i < sizeof($form['resizes']); $i++) {
			    if (empty($form['resizes'][$i]['active'])) {
				continue;
			    }

			    list ($ret, $derivative) = 
				GalleryFactory::newInstance('GalleryEntity', 'GalleryDerivativeImage');
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }

			    if (!isset($derivative)) {
				return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					     null);
			    }

			    $ret = $derivative->create($item->getId(), DERIVATIVE_TYPE_IMAGE_RESIZE);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }

			    $derivative->setDerivativeMimeType($outputMimeType);
			    $derivative->setDerivativeSourceId($item->getId());
			    $derivative->setDerivativeOperations('scale|' . $form['resizes'][$i]['size']);

			    $ret = $derivative->save();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
		    }

		    /* Figure out where to redirect upon success */
		    $redirect['view'] = 'core:ItemAdmin';
		    $redirect['subView'] = 'core:ItemEditPhoto';
		    $redirect['mode'] = $mode;
		    $redirect['itemId'] = $item->getId();
		    $status['editSizes']['saved'] = 1;
		}
	    }
	    break;

	case 'editThumbnail':
	    if (isset($form['action']['crop'])) {
		/* Load the thumbnail */
		list ($ret, $thumbnails) =
		    GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		if (!empty($thumbnails)) {
		    $thumbnail = $thumbnails[$item->getId()];

		    list ($ret, $lock) = $gallery->acquireWriteLock($thumbnail->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    list ($ret, $thumbnail) = $thumbnail->refresh();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    
		    $ret = $thumbnail->mergeOperation('crop',
						      array($form['crop']['x'],
							    $form['crop']['y'],
							    $form['crop']['width'],
							    $form['crop']['height']),
						      true);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = $thumbnail->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = $gallery->releaseLocks($lock);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Figure out where to redirect upon success */
		    $redirect['view'] = 'core:ItemAdmin';
		    $redirect['subView'] = 'core:ItemEditPhoto';
		    $redirect['mode'] = $mode;
		    $redirect['itemId'] = $item->getId();
		    $status['editThumbnail']['cropped'] = 1;
		}
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemEditPhoto';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show options to edit a photo
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemEditPhotoView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($itemId, $mode) = GalleryUtilities::getRequestVariables('itemId', 'mode');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/*
	 * If the mode is empty get it from the session.  If it's empty there,
	 * default to uploading from the browser.  Either way, save the user's
	 * preference in the session.
	 */
	$session =& $gallery->getSession();
	if (empty($mode)) {
	    $mode = $session->get('core.view.ItemEditPhoto.mode');
	    if (empty($mode)) {
		$mode = 'editPhoto';
	    }
	}
	$session->put('core.view.ItemEditPhoto.mode', $mode);
	
	$ItemEditPhoto = array();
	$ItemEditPhoto['mode'] = $mode;

	if ($form['formName'] != 'ItemEditPhoto') {
	    /* First time around, reset the form */
	    switch($mode) {
	    case 'editPhoto':
		$form['scale']['size'] = '';
		$form['preserveOriginal'] = 1;
		break;

	    case 'editSizes':
		/* Load the resizes */
		list ($ret, $resizes) =
		    GalleryDerivativeHelper::fetchResizesByItemIds(array($item->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		if (!empty($resizes)) {
		    foreach ($resizes[$item->getId()] as $resize) {
			if (preg_match('/scale\|(\d+)/',
				       $resize->getDerivativeOperations(),
				       $matches)) {
			    $size = $matches[1];
			}
			if (empty($size)) {
			    $form['resizes'][] = array('active' => 0, 'size' => '');
			} else {
			    $form['resizes'][] = array('active' => 1, 'size' => $size);
			}
		    }
		}

		/* Load the thumbnail */
		list ($ret, $thumbnails) =
		    GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		if (!empty($thumbnails)) {
		    $thumbnail = $thumbnails[$item->getId()];
		    if (preg_match('/thumbnail\|(\d+)/',
				   $thumbnail->getDerivativeOperations(),
				   $matches)) {
			$size = $matches[1];
		    }
		    $form['thumbnail']['size'] = $size;
		}
		break;
		
	    }
	    
	    $form['formName'] = 'ItemEditPhoto';
	}
	
	switch($mode) {
	case 'editPhoto':
	    /* Check to see if we have a preferred source */
	    list ($ret, $results) = GalleryDerivativeHelper::fetchPreferredsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
		
	    if (empty($results)) {
		$ItemEditPhoto['editPhoto']['hasPreferredSource'] = false;
	    } else {
		$ItemEditPhoto['editPhoto']['hasPreferredSource'] = true;
	    }
	    break;
		
	case 'editSizes':
	    /* Tag on a few form blanks */
	    $extraBlanks = 3;
	    if (isset($form['resizes'])) {
		foreach ($form['resizes'] as $resize) {
		    if (!isset($resize['active'])) {
			$extraBlanks--;
		    }
		}
	    }

	    while ($extraBlanks-- > 0) {
		$form['resizes'][] = array('active' => 0, 'size' => '');
	    }

	    /* Make sure that 'active' is set to a value */
	    for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		if (!isset($form['resizes'][$i]['active'])) {
		    $form['resizes'][$i]['active'] = false;
		}
	    }

	    break;

	case 'editThumbnail':

	    /* XXX: Get this from parent album's prefs, if we don't have a thumbnail? */
	    $targetThumbnailSize = 0;
	    $crop = array();
	    
	    /* Load the thumbnail */
	    list ($ret, $thumbnails) =
		GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    if (!empty($thumbnails)) {
		$thumbnail = $thumbnails[$item->getId()];
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

		list ($ret, $source) = $gallery->loadEntitiesById($thumbnail->getDerivativeSourceId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
	    }
	    
	    /*
	     * Try to find a derivative that is close to 600x450 pixels that we can use.  Failing that, use
	     * the original image.
	     */
	    list ($ret, $derivativeTable) =
		GalleryDerivativeHelper::fetchDerivativesBySourceIds(array($item->getId()),
                    array(DERIVATIVE_TYPE_IMAGE_RESIZE, DERIVATIVE_TYPE_IMAGE_THUMBNAIL));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
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
			    GalleryDerivativeHelper::rebuildCacheIfNotCurrent($derivative->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
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

	    if (empty($crop)) {
		$crop['left'] = 0;
		$crop['top'] = 0;
		$crop['width'] = $source->getWidth();
		$crop['height'] = $source->getHeight();
	    }

	    $urlGenerator = $gallery->getUrlGenerator();
	    $url = $urlGenerator->generateUrl(array('view' => 'core:DownloadItem', 'itemId' => $selected));
	    
	    $ItemEditPhoto['editThumbnail']['appletCodeBase'] =
		GalleryUtilities::convertPathToUrl(dirname(__FILE__)) . '/plugins';
	    $ItemEditPhoto['editThumbnail']['appletJarFile'] = 'ImageCrop.jar';
	    $ItemEditPhoto['editThumbnail']['imageUrl'] = $url;
	    $ItemEditPhoto['editThumbnail']['imageWidth'] = $source->getWidth();
	    $ItemEditPhoto['editThumbnail']['imageHeight'] = $source->getHeight();
	    $ItemEditPhoto['editThumbnail']['cropLeft'] = $crop['left'];
	    $ItemEditPhoto['editThumbnail']['cropTop'] = $crop['top'];
	    $ItemEditPhoto['editThumbnail']['cropWidth'] = $crop['width'];
	    $ItemEditPhoto['editThumbnail']['cropHeight'] = $crop['height'];
	    $ItemEditPhoto['editThumbnail']['targetThumbnailSize'] = $targetThumbnailSize;

	    $aspectlist = array();
	    list ($ret, $module) = $gallery->loadModule('core');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
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
	    $ItemEditPhoto['editThumbnail']['aspectRatioList'] = $aspectRatioList;

	    $orientationList = array();
	    $orientationList['landscape'] = $module->translate("Landscape");
	    $orientationList['portrait'] = $module->translate("Portrait");
	    $ItemEditPhoto['editThumbnail']['orientationList'] = $orientationList;


	    /*
	     * Figure out which aspect ratio / orientation is closest to the current crop
	     * settings so that we can start out with those values selected in the dropdowns.
	     */
	    $currentAspect = round($crop['width'] / $crop['height'], 2);
	    $i = 0;

	    /* Set defaults */
	    $selectedAspect = 0;
	    $selectedOrientation = "portrait";
	    $ItemEditPhoto['editThumbnail']['cropRatioWidth'] = $aspectRatioList[0]['width'];
	    $ItemEditPhoto['editThumbnail']['cropRatioHeight'] = $aspectRatioList[0]['height'];
	    
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
	    $ItemEditPhoto['editThumbnail']['selectedAspect'] = $selectedAspect;
	    $ItemEditPhoto['editThumbnail']['selectedOrientation'] = $selectedOrientation;
	    $ItemEditPhoto['editThumbnail']['cropRatioWidth'] = $aspectRatioList[$selectedAspect]['width'];
	    $ItemEditPhoto['editThumbnail']['cropRatioHeight'] = $aspectRatioList[$selectedAspect]['height'];
	}
							     
	$template->setVariable('ItemEditPhoto', $ItemEditPhoto);
	$template->setVariable('controller', 'core:ItemEditPhoto');
	return array(GalleryStatus::success(), '', 'modules/core/templates/ItemEditPhoto.tpl');
    }
}
?>
