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
		/* Delete existing derivative preferences */
		$ret = GalleryDerivativePreferencesMap::removeMapEntry(
		    array('itemId' => $item->getId()));
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		/* Add the thumbnail size back in */
		$ret = GalleryDerivativePreferencesMap::addMapEntry(
	            array('order' => 0,
			  'itemId' => $item->getId(),
			  'derivativeType' => DERIVATIVE_TYPE_IMAGE_THUMBNAIL,
			  'derivativeCommands' => 'scale ' . $form['thumbnail']['size']));
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		    if (empty($form['resizes'][$i]['active'])) {
			continue;
		    }
		    
		    $ret = GalleryDerivativePreferencesMap::addMapEntry(
	                array('order' => $i,
			      'itemId' => $item->getId(),
			      'derivativeType' => DERIVATIVE_TYPE_IMAGE_RESIZE,
			      'derivativeCommands' => 'scale ' . $form['resizes'][$i]['size']));
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    
		/* Figure out where to redirect upon success */
		$redirectParams['view'] = 'core:ItemAdmin';
		$redirectParams['subView'] = 'core:ItemEditImage';
		$redirectParams['itemId'] = $itemId;
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

	if ($formName == 'ItemEditImage' && empty($form['action']['undo'])) {

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
	    
	    list ($ret, $preferences) =
		GalleryDerivativePreferencesMap::fetchPreferencesForItem($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach ($preferences as $preference) {
		if (preg_match('/scale (\d+)/',
			       $preference['derivativeCommands'],
			       $matches)) {
		    $size = $matches[1];
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
	}

	/* Render the HTML body */
	$this->_initTemplate(dirname(__FILE__) . '/templates');
	$this->_setTemplateVariable('form', $form);
	$this->_setTemplateVariable('itemId', $itemId);
	$this->_setTemplateVariable('controller', 'core:ItemEditImage');
	$html = $this->_renderTemplate('core', 'ItemEditImage.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
