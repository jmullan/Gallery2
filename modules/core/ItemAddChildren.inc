<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

class ItemAddChildrenController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all', 'core.addItem'));
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
	
	if (isset($form['action']['addFromComputer'])) {

	    /* Upload any new files */
	    for ($i = 1; $i <= $form['uploadBoxCount']; $i++) {
		$file = $form['fileUpload'][$i];
		if (!empty($file['tmp_name']) && !empty($file['size'])) {
		    
		    /* Get the mime type from the upload info. */
		    $mimeType = $file['type'];

		    /*
		     * If we don't get useful data from that, take a swing at
		     * it using the file name.
		     */
		    if ($mimeType == 'application/octet-stream' ||
			    $mimeType == 'application/unknown') {
			list ($base, $extension) =
			    GalleryUtilities::getFileNameComponents($file['name']);
			$mimeType = GalleryUtilities::convertExtensionToMime($extension);
		    }

		    /*
		     * Assume that we've got a working mime type, go ahead and
		     * get an appropriate GalleryDataItem from the
		     * GalleryFactory.
		     */
		    list ($ret, $newItem) =
			GalleryFactory::newInstanceByHint('GalleryDataItem', $mimeType);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $ret = $newItem->create($item->getId(),
					     $file['tmp_name'],
					     $gallery->getActiveUserId(),
					     $mimeType,
					     GalleryUtilities::getFileBase($file['name']));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $newItem->setTitle(basename($file['name']));
		    $newItem->setSummary(substr($file['caption'], 0, 64));
		    $newItem->setDescription($file['caption']);

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
			list ($ret, $derivative) = 
			    GalleryFactory::newInstance('GalleryEntity', 'GalleryDerivativeImage');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$ret = $derivative->create($newItem->getId(), $preference['derivativeType']);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$derivative->setDerivativeMimeType($newItem->getMimeType());
			$derivative->setDerivativeSourceId($newItem->getId());
			$derivative->setDerivativeCommands($preference['derivativeCommands']);
			
			$ret = $derivative->save();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
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
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemAddChildren');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class ItemAddChildrenView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	list ($itemId, $formName) =
	    GalleryUtilities::getRequestVariables('itemId', 'formName');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all', 'core.addItem'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($formName == 'ItemAddChildren') {

	    /* Complain if we have any invalid data */

	} else {
	    /* First time around, load the form with item data */
	    $form = array();

	    $form['uploadBoxCount'] = 4;
	}

	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('item', $item->getMemberData());
	$this->_setTemplateVariable('controller', 'core:ItemAddChildren');
	$html = $this->_renderTemplate('core', 'ItemAddChildren.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
