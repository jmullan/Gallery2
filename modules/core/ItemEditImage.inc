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
 * This controller will handle the editing of an image
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemEditImageController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest() {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.changeProperties');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Check to see if we have a preferred source */
	list ($ret, $results) = GalleryDerivativeHelper::fetchPreferredsByItemIds(
            array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$preferred = null;
	if (!empty($results[$item->getId()])) {
	    $preferred = $results[$item->getId()];
	}


	$remapSourceIds = array();
	$command = null;
	/* Figure out which command we're taking */
	if (isset($form['action']['scale']) &&
	        is_numeric($form['scale']['size']) &&
	        $form['scale']['size'] > 0) {
	    $command = "scale " . $form['scale']['size'];
	} else if (isset($form['action']['rotate']['clockwise'])) {
	    $command = "rotate 90";
	} else if (isset($form['action']['rotate']['counterClockwise'])) {
	    $command = "rotate -90";
	} else if (isset($form['action']['rotate']['flip'])) {
	    $command = "rotate 180";
	} else if (isset($form['action']['revertToOriginal'])) {
	    if (!empty($preferred)) {
		$ret = $gallery->deleteEntityById($preferred->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$remapSourceIds = array($preferred->getId(), $item->getId(), null);
	    }
	}

	/*
	 * If we have a command, then apply it to the correct object.
	 */
	if (!empty($command)) {
	    /*
	     * If we don't have a preferred and we're preserving, then create
	     * one
	     */
	    $lockIds = array();
	    if (empty($preferred) && empty($form['preserveOriginal'])) {

		/*
		 * We have no preferred image, and we're not preserving the
		 * original.  So, we're changing the original image here.  Make
		 * the appropriate change, then break 
		 *
		 */

		/* Get the path of the source */
		list($ret, $sourcePath) = $item->fetchPath();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		list($ret, $graphics) = $gallery->getGraphics();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		/* Apply change directly to the raw image */
		$pieces = split(' ', $command);
		switch (array_shift($pieces)) {
		case 'rotate':
		    $ret = $graphics->rotateImage($item->getMimeType(),
						  $sourcePath, $sourcePath, $pieces[0]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $modified = true;
		    break;

		case 'scale':
		    $ret = $graphics->scaleImage($item->getMimeType(),
						 $sourcePath, $sourcePath, $pieces[0]);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    break;
		}

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
	    } else {
		/* If we have no preferred, then create one */
		if (empty($preferred)) {
		    list ($ret, $preferred) = GalleryFactory::newInstance('GalleryEntity', 'GalleryDerivativeImage');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
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

		$ret = $preferred->mergeCommand($command);
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

		$ret = GalleryDerivativeHelper::expireDerivativeTreeBySourceIds(
	            array($preferred->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/*
		 * Perform a final check -- if the new derivative is exactly
		 * the same as the original then delete it.
		 */
		$derivativeCommands = $preferred->getDerivativeCommands();
		if (empty($derivativeCommands)) {
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
		}
	    }

	    /* Figure out where to redirect upon success */
	    $redirectParams['view'] = 'core:ItemAdmin';
	    $redirectParams['subView'] = 'core:ItemEditImage';
	    $redirectParams['itemId'] = $itemId;
	}

	/* Check to see if we need to remap any derivative source ids */
	if (!empty($remapSourceIds)) {
	    $ret = GalleryDerivativeHelper::remapSourceIds($remapSourceIds[0],
							   $remapSourceIds[1]);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $urlGenerator->generateUrl($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemEditImage');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will show options to edit an image
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemEditImageView extends GalleryView {

    /**
     * @see GalleryView::renderBody
     */
    function renderBody() {
	global $gallery;

	list ($itemId, $formName) =
	    GalleryUtilities::getRequestVariables('itemId', 'formName');
	$form = GalleryUtilities::getFormVariables('form.');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.changeProperties');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($formName == 'ItemEditImage') {

	    /* Complain if we have any invalid data */
	    if (!empty($form['action']['scale'])) {
		if (empty($form['scale']['size'])) {
		    $form['error']['scale']['size']['missing'] = 1;
		} else if (!is_numeric($form['scale']['size']) ||
			   $form['scale']['size'] <= 0) {
		    $form['error']['scale']['size']['invalid'] = 1;
		}
	    }
	    
	} else {
	    /* First time around, load the form with item data */
	    $form = array();
	    $form['scale']['size'] = '';
	    $form['preserveOriginal'] = 1;
	}

	/* Check to see if we have a preferred source */
	list ($ret, $results) = GalleryDerivativeHelper::fetchPreferredsByItemIds(
            array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (empty($results)) {
	    $hasPreferredSource = false;
	} else {
	    $hasPreferredSource = true;
	}
							     
	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('hasPreferredSource', $hasPreferredSource);
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('controller', 'core:ItemEditImage');
	$html = $template->render('ItemEditImage.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
