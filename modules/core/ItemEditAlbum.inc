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

class ItemEditAlbumController extends GalleryController {

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
							  array('core.all', 'core.changeProperties'));
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
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		/* Add the thumbnail size back in */
		$ret = GalleryDerivativePreferencesMap::addMapEntry(
	            array('order' => 0,
			  'itemId' => $item->getId(),
			  'derivativeType' => DERIVATIVE_TYPE_IMAGE_THUMBNAIL,
			  'derivativeCommands' => 'scale ' . $form['thumbnail']['size']));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
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
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
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
	    $templateAdapter = $gallery->getTemplateAdapter();
	    $results['redirect'] = $templateAdapter->url($redirectParams);
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemEditAlbum');
	    }
	}

	return array(GalleryStatus::success(), $results);
    }
}

class ItemEditAlbumView extends GalleryView {

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
							  array('core.all', 'core.changeProperties'));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($formName == 'ItemEditAlbum' && empty($form['action']['undo'])) {

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
	
	/* Set up our theme selection list */
	$themeList = array();
	$themeDir = $gallery->getConfig('code.gallery.themes');
	if ($dir = $platform->opendir($themeDir)) {
	    while (($subdir = readdir($dir)) !== false) {
		if ($subdir{0} == '.' || $subdir == 'CVS') {
		    continue;
		}

		if ($platform->is_dir("$themeDir$subdir")) {
		    $file = "$themeDir$subdir/theme.inc";
		    if ($platform->file_exists($file)) {
			$themeList[] = $subdir;
		    }
		}
	    }
	    closedir($dir);
	}

	/* Render the HTML body */
	$template = $this->getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('layoutList', $layoutList);
	$template->setVariable('themeList', $themeList);
	$template->setVariable('orderByList', $orderByList);
	$template->setVariable('orderDirectionList', $orderDirectionList);
	$template->setVariable('controller', 'core:ItemEditAlbum');
	$html = $template->render('ItemEditAlbum.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
