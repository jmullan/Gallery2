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
 * This controller will handle the addition of an item as a children to
 * another item.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 * @todo Add support for other ways of adding images (from server, from http...)
 */
class ItemAddChildrenController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.addDataItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$platform = $gallery->getPlatform();

	list ($ret, $lockIds[]) = $gallery->acquireReadLock($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * See if the album has a thumbnail.  If not, we'll create one during
	 * this upload.
	 */
	list ($ret, $thumbnailTable) =
	    GalleryDerivativeHelper::fetchThumbnailsByItemIds($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$albumNeedsThumbnail = empty($thumbnailTable) ? true : false;
	
	if (isset($form['action']['addFromComputer'])) {

	    /* Upload any new files */
	    for ($i = 1; $i <= $form['uploadBoxCount']; $i++) {
		$file = $form['fileUpload'][$i];
		if (!empty($file['tmp_name']) && !empty($file['size'])) {
		    
		    /* Get the mime type and file extension from the upload info. */
		    $mimeType = $file['type'];
		    $extension = GalleryUtilities::getFileExtension($file['name']);

		    /*
		     * If we don't get useful data from that, take a swing at
		     * it using the file name.
		     */
		    if ($mimeType == 'application/octet-stream' ||
			    $mimeType == 'application/unknown') {
			$mimeType = GalleryUtilities::convertExtensionToMime($extension);
		    }

		    /*
		     * Assume that we've got a working mime type, go ahead and
		     * get an appropriate GalleryDataItem from the
		     * GalleryFactory.
		     */
		    list ($ret, $newItem) = GalleryItemHelper::newItemByMimeType($mimeType);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = $newItem->create($item->getId(),
					    $file['tmp_name'],
					    $mimeType,
					    basename($file['name']));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $newItem->setTitle(basename($file['name']));
		    if (isset($file['caption'])) {
			$newItem->setSummary(substr($file['caption'], 0, 255));
			$newItem->setDescription($file['caption']);
		    }

		    $ret = $newItem->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /*
		     * Now create thumbnails and resizes according to the
		     * wishes of the parent album.
		     */
		    list ($ret, $preferences) =
			GalleryDerivativePreferencesMap::fetchPreferencesForItem($item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }


		    foreach ($preferences as $preference) {
			/*
			 * Validate the stored preferences to make sure that
			 * they're supported by an active toolkit.
			 */
			list ($ret, $isSupported, $outputMimeType) =
			    GalleryToolkitHelper::isSupportedOperationSequence($mimeType,
									       $preference['derivativeOperations']);

			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			/* Not supported?  Try the next preference */
			if (!$isSupported) {
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

			$ret = $derivative->create($newItem->getId(), $preference['derivativeType']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$derivative->setDerivativeMimeType($outputMimeType);
			$derivative->setDerivativeSourceId($newItem->getId());
			$derivative->setDerivativeOperations($preference['derivativeOperations']);
			
			$ret = $derivative->save();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			/*
			 * Create a thumbnail for the album, if necessary.
			 * XXX: this needs to be refactored 
			 */
			if ($albumNeedsThumbnail && $preference['derivativeType'] == DERIVATIVE_TYPE_IMAGE_THUMBNAIL) {
			    list ($ret, $derivative) = 
				GalleryFactory::newInstance('GalleryEntity', 'GalleryDerivativeImage');
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }

			    if (!isset($derivative)) {
				return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					     null);
			    }  

			    $ret = $derivative->create($item->getId(), $preference['derivativeType']);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }

			    $derivative->setDerivativeMimeType($outputMimeType);
			    $derivative->setDerivativeSourceId($newItem->getId());
			    $derivative->setDerivativeOperations($preference['derivativeOperations']);
			
			    $ret = $derivative->save();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
				
			    $albumNeedsThumbnail = false;
			}
		    }
		}
	    }

	    /* Figure out where to redirect upon success */
	    $redirectParams['view'] = 'core:ItemAdmin';
	    $redirectParams['subView'] = 'core:ItemAddChildren';
	    $redirectParams['itemId'] = $itemId;
	}

	$ret = $gallery->releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemAddChildren');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for files to add as children to an album.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddChildrenView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.addDataItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] == 'ItemAddChildren') {

	    /* Complain if we have any invalid data */

	} else {
	    /* First time around, load the form with item data */
	    $form = array();

	    $form['uploadBoxCount'] = 4;
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('controller', 'core:ItemAddChildren');
	$html = $template->render('ItemAddChildren.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
