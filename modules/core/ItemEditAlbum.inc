<?php
/*
 * $RCSfile
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
 * This controller will handle the changes users make to an album.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemEditAlbumController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.changeProperties');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (isset($form['action']['undo'])) {

	    /* Redirect back to the current page to reset the form */
	    $redirectParams['view'] = 'core:ItemAdmin';
	    $redirectParams['subView'] = 'core:ItemEditAlbum';
	    $redirectParams['itemId'] = $itemId;
	    
	} else if (isset($form['action']['save'])) {
	    /* Validate the input data. */
	    $error = false;
	    if (!is_numeric($form['thumbnail']['size'])) {
		GalleryUtilities::putRequestVariable('form.error.thumbnail.size.invalid', 1);
		$error = true;
	    }

	    for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		if (!empty($form['resizes'][$i]['active'])) {
		    if (empty($form['resizes'][$i]['size'])) {
			GalleryUtilities::putRequestVariable('form.error.resizes.' . $i . '.size.missing', 1);
			$error = true;
		    } else if (!is_numeric($form['resizes'][$i]['size'])) {
			GalleryUtilities::putRequestVariable('form.error.resizes.' . $i . '.size.invalid', 1);
			$error = true;
		    }
		}
	    }

	    if (!$error) {
		/* Delete existing derivative preferences */
		$ret = GalleryDerivativePreferencesMap::removeMapEntry(
		    array('itemId' => $item->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Add the thumbnail size back in */
		$ret = GalleryDerivativePreferencesMap::addMapEntry(
	            array('order' => 0,
			  'itemId' => $item->getId(),
			  'derivativeType' => DERIVATIVE_TYPE_IMAGE_THUMBNAIL,
			  'derivativeOperations' => 'thumbnail|' . $form['thumbnail']['size']));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Add the resize-sizes back in */
		for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		    if (empty($form['resizes'][$i]['active'])) {
			continue;
		    }
		    
		    $ret = GalleryDerivativePreferencesMap::addMapEntry(
	                array('order' => $i,
			      'itemId' => $item->getId(),
			      'derivativeType' => DERIVATIVE_TYPE_IMAGE_RESIZE,
			      'derivativeOperations' => 'scale|' . $form['resizes'][$i]['size']));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		/* Load the children if we might need them */
		if (   isset($form['recreateThumbnails'])
		    || isset($form['recreateResizes']) ) {
			/* Get the child id => child types */
			list ($ret, $childIds) = $item->fetchChildIds();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$childItems = array();
			if (!empty($childIds)) {
			    /* Load the children */
			    list ($ret, $childItems) = $gallery->loadEntitiesById($childIds);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
		}

		$lockIds = array();

		/* Recreate the thumbnails, if requested to do so */

		/*
		 * TODO: it's possible for the data item not to have
		 * resizes/thumbnails because it was created when there were no
		 * graphics toolkits.  Improve this code to detect that
		 * situation and build new thumbnails/resizes
		 */
		if (isset($form['recreateThumbnails'])) {
		    /* Load the thumbnail of the children */
		    list ($ret, $thumbTable) =
			    GalleryDerivativeHelper::fetchThumbnailsByItemIds($childIds);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    foreach ($childItems as $child) {
			$childId = $child->getId();
			if (!isset($thumbTable[$childId])) {
			    continue;
			}
			
			$thumbnail = $thumbTable[$childId];

			/*
			 * Change the thumbnail
			 * XXX: we should make sure that we have a toolkit for this!
			 */
			$thumbnail->setDerivativeOperations('thumbnail|' . $form['thumbnail']['size']);

			if ($thumbnail->isModified()) {
			    list ($ret, $lockIds[]) = $gallery->acquireWriteLock($thumbnail->getId());
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			    $thumbnail->expireCache();
			    $ret = $thumbnail->save();
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}
		    }
		}

		/* Recreate the resizes, if requested to do so */
		/* XXX: We should not delete resizes that we will be adding */
		/*      again moments later again */
		if (isset($form['recreateResizes'])) {
		    /* Get and delete all current resizes */
		    list ($ret, $resizesTable) =
			GalleryDerivativeHelper::fetchResizesByItemIds($childIds);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    foreach ($resizesTable as $resizes) {
			foreach ($resizes as $resize) {
			    $ret = $gallery->deleteEntityById($resize->getId());
			}
		    }

		    /* Add the new resizes */
		    foreach ($childItems as $child) {
			$childId = $child->getId();

			if (!GalleryUtilities::isA($child, 'GalleryDataItem')) {
			    continue;
			}

			/*
			 * Make sure that we have a toolkit before adding back
			 * the resizes
			 */
			list ($ret, $toolkit, $outputMimeType) =
			    GalleryToolkitHelper::getToolkitByOperation($child->getMimeType(), 'scale');
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			if (isset($toolkit)) {
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

				$ret = $derivative->create($childId, DERIVATIVE_TYPE_IMAGE_RESIZE);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}

				$derivative->setDerivativeMimeType($outputMimeType);
				$derivative->setDerivativeSourceId($child->getId());
				$derivative->setDerivativeOperations('scale|' . $form['resizes'][$i]['size']);

				$ret = $derivative->save();
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
			    }
			}
		    }
		}

		$ret = $gallery->releaseLocks($lockIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Save basic settings */
		$item->setLayout($form['layout']);
		$item->setTheme($form['theme']);
		$item->setOrderBy($form['orderBy']);
		$item->setOrderDirection($form['orderDirection']);

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
		
		/* Figure out where to redirect upon success */
		$redirectParams['view'] = 'core:ItemAdmin';
		$redirectParams['subView'] = 'core:ItemEditAlbum';
		$redirectParams['itemId'] = $itemId;
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemEditAlbum');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for settings of an album
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemEditAlbumView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.changeProperties');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'ItemEditAlbum') {
	    /* First time around, load the form with item data */
	    $form = array();

	    $form['orderBy'] = $item->getOrderBy();
	    $form['orderDirection'] = $item->getOrderDirection();
	    $form['layout'] = $item->getLayout();
	    $form['theme'] = $item->getTheme();
	    
	    list ($ret, $preferences) =
		GalleryDerivativePreferencesMap::fetchPreferencesForItem($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach ($preferences as $preference) {
		if (preg_match('/(scale|thumbnail)\|(\d+)/',
			       $preference['derivativeOperations'],
			       $matches)) {
		    $size = $matches[2];
		}

		switch($preference['derivativeType']) {
		case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
		    $form['thumbnail']['size'] = $size;
		    break;
		    
		case DERIVATIVE_TYPE_IMAGE_RESIZE:
		    if (empty($size)) {
			$form['resizes'][] = array('active' => 0, 'size' => '');
		    } else {
			$form['resizes'][] = array('active' => 1, 'size' => $size);
		    }
		    break;
		}
	    }

	    /* Tag on a few form blanks */
	    if (empty($form['resizes'])) {
		$extraBlanks = 3;
	    } else {
		$extraBlanks = max(2 - sizeof($form['resizes']), 0) + 1;
	    }

	    while ($extraBlanks-- > 0) {
		$form['resizes'][] = array('active' => 0, 'size' => '');
	    }
	    $form['recreateThumbnails'] = false;
	    $form['recreateResizes'] = false;
	}

	list ($ret, $module) = $gallery->loadModule('core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$platform = $gallery->getPlatform();

	/* Set up our sort order selection list */
	$orderByList = array();
	$orderByList[''] = $module->translate('* No Sort Order *');
	$orderByList['title'] = $module->translate('Title');
	$orderByList['summary'] = $module->translate('Summary');
	$orderByList['creationTimestamp'] = $module->translate('Creation Date');
	$orderByList['modificationTimestamp'] = $module->translate('Last Changed Date');
	$orderByList['description'] = $module->translate('Description');
	$orderByList['keywords'] = $module->translate('Keywords');

	/* Set up our sort direction selection list */
	$orderDirectionList = array();
	$orderDirectionList['asc'] = $module->translate("Ascending");
	$orderDirectionList['desc'] = $module->translate("Descending");

	/* Set up our layout selection list */
	$layoutList = array();
	$layoutDir = $gallery->getConfig('code.gallery.layouts');
	if ($dir = $platform->opendir($layoutDir)) {
	    while (($file = readdir($dir)) !== false) {
		if ($file{0} == '.' || $file == 'CVS') {
		    continue;
		}
		$layoutInc = "$layoutDir$file/layout.inc";
		if ($platform->file_exists($layoutInc)) {
		    $layoutList[] = $file;
		}
	    }
	    closedir($dir);
	}
	
	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('layoutList', $layoutList);
	$template->setVariable('themeList', GalleryTheme::getThemes());
	$template->setVariable('orderByList', $orderByList);
	$template->setVariable('orderDirectionList', $orderDirectionList);
	$template->setVariable('controller', 'core:ItemEditAlbum');
	$html = $template->render('ItemEditAlbum.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
