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
 * This controller will handle the creation of resizes for an image
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemCreateResizesController extends GalleryController {

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

	if (isset($form['action']['save'])) {

	    /* Validate the input data. */
	    $error = false;
	    if (!is_numeric($form['thumbnail']['size'])) {
		$error = true;
	    }
	    foreach ($form['resizes'] as $resize) {
		if (!empty($resize['active']) && !is_numeric($resize['size'])) {
		    $error = true;
		    break;
		}
	    }

	    if (!$error) {
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
		$redirectParams['view'] = 'core:ItemAdmin';
		$redirectParams['subView'] = 'core:ItemCreateResizes';
		$redirectParams['itemId'] = $item->getId();
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemCreateResizes');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for the sizes to create
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemCreateResizesView extends GalleryView {

    /**
     *
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

	if ($form['formName'] == 'ItemCreateResizes') {

	    /* Complain if we have any invalid data */
	    if (empty($form['thumbnail']['size'])) {
		$form['error']['thumbnail']['size']['missing'] = 1;
	    } else if (!is_numeric($form['thumbnail']['size']) ||
		       $form['thumbnail']['size'] <= 0) {
		$form['error']['thumbnail']['size']['invalid'] = 1;
	    }

	    for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		if (empty($form['resizes'][$i]['active'])) {
		    /* Force it to a value, but don't check the data */
		    $form['resizes'][$i]['active'] = 0;
		    continue;
		}

		if (empty($form['resizes'][$i]['size'])) {
		    $form['error']['resizes'][$i]['size']['missing'] = 1;
		} else if (!is_numeric($form['resizes'][$i]['size']) ||
			   $form['resizes'][$i]['size'] <= 0) {
		    $form['error']['resizes'][$i]['size']['invalid'] = 1;
		}
	    }
	    
	} else {
	    /* First time around, load the form with item data */
	    $form = array();

	    /* Load the resizes */
	    list ($ret, $resizes) =
		GalleryDerivativeHelper::fetchResizesByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
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
		return array($ret->wrap(__FILE__, __LINE__), null);
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

	    /* Tag on a few form blanks */
	    if (empty($form['resizes'])) {
		$extraBlanks = 3;
	    } else {
		$extraBlanks = max(2 - sizeof($form['resizes']), 0) + 1;
	    }

	    while ($extraBlanks-- > 0) {
		$form['resizes'][] = array('active' => 0, 'size' => '');
	    }

	}
							     
	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('controller', 'core:ItemCreateResizes');
	$html = $template->render('ItemCreateResizes.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
