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

class ItemEditImageController extends GalleryController {

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
							  array('core.all', 'core.change'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$command = null;
	/* Figure out which command we're taking */
	if (isset($form['action']['scale']) &&
	        is_numeric($form['scale']['size']) &&
	        $form['scale']['size'] > 0) {
	    $command = "scale " . $form[scale][size];
	} else if (isset($form['action']['rotate']['clockwise'])) {
	    $command = "rotate -90";
	} else if (isset($form['action']['rotate']['counterClockwise'])) {
	    $command = "rotate 90";
	} else if (isset($form['action']['rotate']['flip'])) {
	    $command = "rotate 180";
	}

	/*
	 * If we have a command, then apply it to the correct object.
	 */
	if (!empty($command)) {
	    /* Check to see if we have a preferred source */
	    list ($ret, $results) = GalleryDerivativeHelper::fetchPreferredsByItemIds(
                array($item->getId()));
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    
	    $preferred = null;
	    if (!empty($results[$item->getId()])) {
		$preferred = $results[$item->getId()];
	    }

	    /*
	     * If we don't have a preferred and we're preserving, then create
	     * one
	     */
	    $lockIds = array();
	    if (empty($preferred) && empty($form['preserveOriginal'])) {
		/* Apply change directly to the raw image */
	    } else {
		/* If we have no preferred, then create one */
		if (empty($preferred)) {
		    list ($ret, $preferred) = $gallery->newEntity('GalleryDerivativeImage');
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		    
		    $ret = $preferred->create($item->getId(), DERIVATIVE_TYPE_IMAGE_PREFERRED);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		    
		    $preferred->setDerivativeSourceId($item->getId());
		    $preferred->setDerivativeMimeType($item->getMimeType());
		} else {
		    /*
		     * Otherwise, lock the preferred so that we can modify it
		     */
		    list ($ret, $lockIds[]) = $gallery->acquireWriteLock($preferred->getId());
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}

		$ret = $preferred->mergeCommand($command);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}
		
		$ret = $preferred->save();
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		if (!empty($lockIds)) {
		    $ret = $gallery->releaseLocks($lockIds);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
		
		/* Figure out where to redirect upon success */
//		$redirectParams['view'] = 'core:ItemAdmin';
//		$redirectParams['subView'] = 'core:ItemEditImage';
//		$redirectParams['itemId'] = $itemId;
	    }
	}

	if (!empty($redirectParams)) {
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemEditImage');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

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
	$ret = GalleryUserHelper::assertHasItemPermission($itemId,
							  $gallery->getActiveUserId(),
							  array('core.all', 'core.change'));
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
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (empty($results)) {
	    $hasPreferredSource = false;
	} else {
	    $hasPreferredSource = true;
	}
							     
	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('hasPreferredSource', $hasPreferredSource);
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('item', $item->getMemberData());
	$this->_setTemplateVariable('controller', 'core:ItemEditImage');
	$html = $this->_renderTemplate('core', 'ItemEditImage.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
