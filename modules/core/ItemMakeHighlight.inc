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
 * @author Ernesto Baschny <ernst@baschny.de>
 */

/**
 * This controller will make an item the highlight for its parent
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemMakeHighlightController extends GalleryController {

    /**
     * 
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$parentId = $item->getParentId();

	/* Make sure we have permission to edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($parentId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load the current album thumbnail. */ 
	list ($ret, $thumbnailTable) =
	    GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($parentId));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}


	/*
	 * Find the right source id to create our thumbnail from.  Search for
	 * it in this order:
	 * 1. The item's preferred derivative's source id
	 * 2. The item's thumbnail's source id
	 * 3. The item data itself
	 * 4. no thumbnail
	 */
	$source = null;
	$sourceMimeType = null;
	
	/* 1. The item's preferred derivative's source id */
	list ($ret, $derivatives) = GalleryDerivativeHelper::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (!empty($derivatives[$item->getId()])) {
	    $source = $derivatives[$item->getId()];
	    $sourceMimeType = $source->getDerivativeMimeType();
	}

	/* 2. The item's thumbnail's source id */
	if (!$sourceMimeType) {
	    list ($ret, $derivatives) = GalleryDerivativeHelper::fetchThumbnailsByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!empty($derivatives[$item->getId()])) {
		$source = $derivatives[$item->getId()];
		$sourceMimeType = $source->getDerivativeMimeType();
	    }
	}

	/* 3. The item data itself */
	if (!$sourceMimeType) {
	    if (GalleryUtilities::isA($item, 'GalleryDataItem')) {
		$source = $item;
		$sourceMimeType = $item->getMimeType();
	    }
	}

	/*
	 * If at this point $sourceMimeType is still null then we have no
	 * thumbnail. 
	 */
	if (isset($source)) {
	    list ($ret, $lockIds[]) = $gallery->acquireReadLock($source->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	if (isset($form['action']['makeHighlight'])) {
	    /* Delete the current thumbnail of the album */
	    if (!empty($thumbnailTable[$parentId])) {
		$parentThumbnail = $thumbnailTable[$parentId];
		$ret = $gallery->deleteEntityById($parentThumbnail->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    /* Get the derivativeOperations to generate a thumbnail for the album */
	    list ($ret, $preferences) = GalleryDerivativePreferencesMap::fetchPreferencesForItem($parentId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach ($preferences as $preference) {
		if ($preference['derivativeType'] == DERIVATIVE_TYPE_IMAGE_THUMBNAIL) {
		    $derivativeOperations = $preference['derivativeOperations'];
		    break;
		}
	    }
	    if (empty($derivativeOperations)) {
		return array(GalleryStatus::error(ERROR_MISSING_VALUE,
						  __FILE__, __LINE__),
			     null);
	    }

	    if ($sourceMimeType) {
		/*
		 * Validate the stored preferences to make sure that
		 * they're supported by an active toolkit.
		 */
		list ($ret, $isSupported, $outputMimeType) =
		    GalleryToolkitHelper::isSupportedOperationSequence($sourceMimeType,
								       $derivativeOperations);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if ($isSupported) {
		    /* Create the new thumbnail for the album */
		    list ($ret, $derivative) = 
			GalleryFactory::newInstance('GalleryEntity', 'GalleryDerivativeImage');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    if (!isset($derivative)) {
			return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				     null);
		    }

		    $ret = $derivative->create($parentId, DERIVATIVE_TYPE_IMAGE_THUMBNAIL);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $derivative->setDerivativeMimeType($outputMimeType);
		    $derivative->setDerivativeSourceId($source->getId());
		    $derivative->setDerivativeOperations($derivativeOperations);

		    $ret = $derivative->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		} else {
		    if (isset($lockIds)) {
			$ret = $gallery->releaseLocks($lockIds);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		
		    return array(GalleryStatus::error(ERROR_UNSUPPORTED_OPERATION, __FILE__, __LINE__), null);
		}
	    }
	    
	    /* Figure out where to redirect upon success */
	    $redirectParams['view'] = 'core:ItemAdmin';
	    $redirectParams['itemId'] = $item->getId();
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemDelete');
	    }
	}

	if (isset($lockIds)) {
	    $ret = $gallery->releaseLocks($lockIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
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
class ItemMakeHighlightView extends GalleryView {

    /**
     * 
     */
    function renderBody($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$parentId = $item->getParentId();

	/* Make sure we have permission do edit the parent of this item */
	$ret = GalleryUserHelper::assertHasItemPermission($parentId, 'core.edit');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] == 'ItemMakeHighlight') {

	    /* Complain if we have any invalid data */

	} else {
	    /* First time around, load the form with item data */
	    $form = array();

	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('controller', 'core:ItemMakeHighlight');
	$html = $template->render('ItemMakeHighlight.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
