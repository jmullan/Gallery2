<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package Watermark
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This edit plugin allows you to customize the watermark for an image
 *
 * @package Watermark
 * @subpackage UserInterface
 *
 */
class ItemEditWatermark extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	global $gallery;

	$status = null;
	$error = array();

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'watermark');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if (isset($form['action']['save'])) {
	    if (!(isset($form['whichDerivative']['thumbnail']) ||
		  isset($form['whichDerivative']['resize']) ||
		  isset($form['whichDerivative']['preferred']))) {
		$error[] = 'form[error][versions][missing]';
	    }

	    if (empty($error)) {
		list ($ret, $watermark) = GalleryCoreApi::loadEntitiesById($form['watermarkId']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		list ($ret, $derivativeTable) = GalleryCoreApi::fetchDerivativesByItemIds(array($item->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		/* Weed out derivatives that we don't want to modify */
		$derivatives = array();
		$add = array();
		$remove = array();
		$hasPreferred = false;
		if (isset($derivativeTable[$item->getId()])) {
		    $derivatives = $derivativeTable[$item->getId()];
		    foreach ($derivatives as $derivative) {
			switch ($derivative->getDerivativeType()) {
			case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
			    if (isset($form['whichDerivative']['thumbnail'])) {
				$add[] = $derivative->getId();
			    } else {
				$remove[] = $derivative->getId();
			    }
			    break;
		    
			case DERIVATIVE_TYPE_IMAGE_RESIZE:
			    if (isset($form['whichDerivative']['resize'])) {
				$add[] = $derivative->getId();
			    } else {
				$remove[] = $derivative->getId();
			    }
			    break;
			
			case DERIVATIVE_TYPE_IMAGE_PREFERRED:
			    $hasPreferred = true;
			    if (isset($form['whichDerivative']['preferred'])) {
				$add[] = $derivative->getId();
			    } else {
				$remove[] = $derivative->getId();
			    }
			    break;
			}
		    }
		}

		/* If they want to modify the original, and we don't have one -- create a preferred */
		if (isset($form['whichDerivative']['preferred']) && !$hasPreferred) {
		    list ($ret, $preferred) =
			GalleryCoreApi::newFactoryInstanceByHint('GalleryDerivative', $item->getEntityType());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		    
		    if (!isset($preferred)) {
			return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
				     null, null);
		    }
		
		    $ret = $preferred->create($item->getId(), DERIVATIVE_TYPE_IMAGE_PREFERRED);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $preferred->setDerivativeSourceId($item->getId());
		    $preferred->setMimeType($item->getMimeType());

		    $ret = GalleryCoreApi::remapSourceIds($item->getId(), $preferred->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $ret = $preferred->save();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    /*
		     * Add it to the list to get a watermark.
		     * TODO: just add the watermark here instead of modifying and re-saving the
		     *       preferred below.
		     */
		    $derivatives[] = $preferred;
		    $add[] = $preferred->getId();
		}

		if (!empty($derivatives)) {
		    list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock(array_merge($add, $remove));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    foreach ($derivatives as $derivative) {
			list ($ret, $derivative) = $derivative->refresh();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}

			if (in_array($derivative->getId(), $add)) {
			    list ($ret, $newPostFilters) =
				GalleryCoreApi::mergeDerivativeOperations($derivative->getPostFilterOperations(),
                                    sprintf('composite|watermark/%s,%s,%d,%d,manual,%2.3f,%2.3f',
					    $watermark->getFileName(),
					    $watermark->getMimeType(),
					    $watermark->getWidth(),
					    $watermark->getHeight(),
					    $form['xPercent'],
					    $form['yPercent']));
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null, null);
			    }
			} else if (in_array($derivative->getId(), $remove)) {
			    $newPostFilters =
				GalleryCoreApi::removeDerivativeOperation('composite',
									  $derivative->getPostFilterOperations());
			}
			$derivative->setPostFilterOperations($newPostFilters);

			if ($derivative->getDerivativeType() == DERIVATIVE_TYPE_IMAGE_PREFERRED) {
			    $preferred = $derivative;
			}

			$ret = $derivative->save(true);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
		    }

		    $ret = GalleryCoreApi::releaseLocks($lockId);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		}

		if (isset($preferred)) {
		    list ($ret, $preferred) = $preferred->refresh();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		
		    if ($preferred->hasNoOperations()) {
			$ret = GalleryCoreApi::remapSourceIds($preferred->getId(), $preferred->getDerivativeSourceId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}

			$ret = GalleryCoreApi::deleteEntityById($preferred->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
		    }
		}
		$status = $module->translate('Watermark applied successfully');
	    }
	} else if (isset($form['action']['remove'])) {
	    list ($ret, $derivativeTable) = GalleryCoreApi::fetchDerivativesByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    if (isset($derivativeTable[$item->getId()])) {
		$derivatives = $derivativeTable[$item->getId()];

		$ids = array();
		foreach ($derivatives as $derivative) {
		    $ids[] = $derivative->getId();
		}
		
		/* Lock them all */
		list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($ids);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		foreach ($derivatives as $derivative) {
		    list ($ret, $derivative) = $derivative->refresh();
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $newPostFilters =
			GalleryCoreApi::removeDerivativeOperation('composite',
								  $derivative->getPostFilterOperations());
		    $derivative->setPostFilterOperations($newPostFilters);

		    if ($derivative->getDerivativeType() == DERIVATIVE_TYPE_IMAGE_PREFERRED) {
			$preferred = $derivative;
		    }
		    
		    $ret = $derivative->save(true);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		}
		    

		$ret = GalleryCoreApi::releaseLocks($lockId);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
	    }

	    if (isset($preferred)) {
		list ($ret, $preferred) = $preferred->refresh();
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		
		if ($preferred->hasNoOperations()) {
		    $ret = GalleryCoreApi::remapSourceIds($preferred->getId(), $preferred->getDerivativeSourceId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $ret = GalleryCoreApi::deleteEntityById($preferred->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		}
	    }
	    $status = $module->translate('Watermark removed successfully');
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	global $gallery;

	$ItemEditWatermark = array();
	$ItemEditWatermark['showApplet'] = $thumbnail != null;

	list ($ret, $ItemEditWatermark['isAdmin']) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load up all watermarks */
	GalleryCoreApi::relativeRequireOnce('modules/watermark/classes/WatermarkHelper.class');
	list ($ret, $tmp) = WatermarkHelper::fetchWatermarks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$watermarks = array();
	$watermarkIds = array_keys($tmp);
	if (!empty($watermarkIds)) {
	    list ($ret, $watermarks) = GalleryCoreApi::loadEntitiesById($watermarkIds);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    for ($i = 0; $i < sizeof($watermarks); $i++) {
		$watermarks[$i] = $watermarks[$i]->getMemberData();
	    }
	}

	if ($form['formName'] != 'ItemEditWatermark') {
	    /* First time around, reset the form */
	    $form['formName'] = 'ItemEditWatermark';

	    if (!empty($watermarks)) {
		/* Get the current watermark from any of the derivatives */
		list ($ret, $derivatives) = GalleryCoreApi::fetchDerivativesByItemIds(array($item->getId()));
		if (isset($derivatives[$item->getId()])) {
		    foreach ($derivatives[$item->getId()] as $derivative) {
			$ops = $derivative->getPostFilterOperations();
			if (preg_match('{composite\|watermark/([^;]*)}', $ops, $matches)) {
			    switch ($derivative->getDerivativeType()) {
			    case DERIVATIVE_TYPE_IMAGE_PREFERRED:
				$form['whichDerivative']['preferred'] = 1;
				break;
			
			    case DERIVATIVE_TYPE_IMAGE_RESIZE:
				$form['whichDerivative']['resize'] = 1;
				break;
			
			    case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
				$form['whichDerivative']['thumbnail'] = 1;
				break;
			    }
			
			    $args = preg_split('/,/', $matches[1]);
			    $fileName = $args[0];
			    $form['xPercent'] = $args[5];
			    $form['yPercent'] = $args[6];
			    for ($i = 0; $i < sizeof($watermarks); $i++) {
				if ($watermarks[$i]['fileName'] == $fileName) {
				    $form['watermarkId'] = $watermarks[$i]['id'];
				}
			    }
			}
		    }
		}

		if (!isset($form['watermarkId'])) {
		    $form['watermarkId'] = $watermarks[0]['id'];
		}
	    }
	}

	/* Check to see if we have a preferred source */
	list ($ret, $preferredTable) =
	    GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$preferred = null;
	if (!empty($preferredTable[$item->getId()])) {
	    $preferred = $preferredTable[$item->getId()];
	}

	$ItemEditWatermark = array();
	$ItemEditWatermark['watermarks'] = $watermarks;
	$ItemEditWatermark['item'] = $item->getMemberData();
	$ItemEditWatermark['preferred'] = isset($preferred) ? $preferred->getMemberData() : null;

	$template->setVariable('ItemEditWatermark', $ItemEditWatermark);
	$template->setVariable('controller', 'core:ItemEditWatermark');
	return array(GalleryStatus::success(), 'modules/watermark/templates/ItemEditWatermark.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	if (!GalleryUtilities::isA($item, 'GalleryDataItem')) {
	    return false;
	}
	
	list ($ret, $toolkit) =
	    GalleryCoreApi::getToolkitByOperation($item->getMimeType(), 'composite');
	if ($ret->isError()) {
	    return false; // Swallow the error for now
	}
	return isset($toolkit);
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'watermark');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('Watermark'));
    }
}
?>
