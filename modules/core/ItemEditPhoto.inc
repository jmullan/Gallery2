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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the editing of a photo
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class ItemEditPhoto extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	global $gallery;

	$status = null;
	$error = array();

	if (isset($form['action']['save'])) {

	    /* Validate the input data. */
	    if (empty($form['thumbnail']['size'])) {
		$error[] = 'form[error][thumbnail][size][missing]';
	    } else if (!is_numeric($form['thumbnail']['size'])) {
		$error[] = 'form[error][thumbnail][size][invalid]';
	    }

	    for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		if (empty($form['resizes'][$i]['active'])) {
		    continue;
		}

		if (empty($form['resizes'][$i]['width']) || empty($form['resizes'][$i]['height'])) {
		    $error[] = sprintf('form[error][resizes][%d][size][missing]', $i);
		} else if (!is_numeric($form['resizes'][$i]['width'])
			   || !is_numeric($form['resizes'][$i]['height'])
			   || $form['resizes'][$i]['width'] <= 0
			   || $form['resizes'][$i]['height'] <= 0) {
		    $error[] = sprintf('form[error][resizes][%d][size][invalid]', $i);
		}
	    }

	    if (empty($error)) {
		/* Load the thumbnail */
		list ($ret, $thumbTable) =
		    GalleryCoreApi::fetchThumbnailsByItemIds(array($item->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		if (isset($thumbTable[$item->getId()])) {
		    /* Change the thumbnail */
		    $thumbnail = $thumbTable[$item->getId()];
		    $thumbnail->setDerivativeOperations(
			preg_replace('/((^|;)thumbnail\|)\d+/', '${1}' . $form['thumbnail']['size'],
				     $thumbnail->getDerivativeOperations()));

		    if ($thumbnail->isModified()) {
			list ($ret, $lockId) = GalleryCoreApi::acquireWriteLock($thumbnail->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
			$thumbnail->expireCache();
			$ret = $thumbnail->save();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
			$ret = GalleryCoreApi::releaseLocks(array($lockId));
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
		    }
		} else {
		    list ($ret, $source) = GalleryCoreApi::fetchPreferredSource($item);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    /* Create the thumbnail */
		    list ($ret, $toolkit, $outputMimeType) =
			GalleryCoreApi::getToolkitByOperation($source->getMimeType(), 'thumbnail');
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    if (isset($toolkit)) {
			list ($ret, $thumbnail) =
			    GalleryCoreApi::newFactoryInstanceByHint('GalleryDerivative', $source->getEntityType());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}

			if (!isset($thumbnail)) {
			    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					 null, null);
			}

			$ret = $thumbnail->create($item->getId(), DERIVATIVE_TYPE_IMAGE_THUMBNAIL);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}

			$thumbnail->setMimeType($outputMimeType);
			$thumbnail->setDerivativeSourceId($source->getId());
			$thumbnail->setDerivativeOperations('thumbnail|' . $form['thumbnail']['size']);

			$ret = $thumbnail->save();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
		    }
		}

		/* Get and delete all current resizes */
		list ($ret, $resizesTable) =
		    GalleryCoreApi::fetchResizesByItemIds(array($item->getId()));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		foreach ($resizesTable as $resizes) {
		    foreach ($resizes as $resize) {
			$postFilter = $resize->getPostFilterOperations();
			$ret = GalleryCoreApi::deleteEntityById($resize->getId());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
		    }
		}

		list ($ret, $source) = GalleryCoreApi::fetchPreferredSource($item);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		/*
		 * Make sure that we have a toolkit before adding back the resizes
		 */
		list ($ret, $toolkit, $outputMimeType) =
		    GalleryCoreApi::getToolkitByOperation($source->getMimeType(), 'scale');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		if (isset($toolkit)) {
		    /* Add the new resizes */
		    for ($i = 0; $i < sizeof($form['resizes']); $i++) {
			if (empty($form['resizes'][$i]['active'])) {
			    continue;
			}

			list ($ret, $derivative) =
			    GalleryCoreApi::newFactoryInstanceByHint('GalleryDerivative', $source->getEntityType());
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}

			if (!isset($derivative)) {
			    return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__),
					 null, null);
			}

			$ret = $derivative->create($item->getId(), DERIVATIVE_TYPE_IMAGE_RESIZE);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}

			$derivative->setMimeType($outputMimeType);
			$derivative->setDerivativeSourceId($source->getId());
			$derivative->setDerivativeOperations(
			     'scale|' . $form['resizes'][$i]['width']
				. ',' . $form['resizes'][$i]['height']);
			if (isset($postFilter)) {
			    $derivative->setPostFilterOperations($postFilter);
			}

			$ret = $derivative->save();
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
		    }
		}

		/* Figure out where to redirect upon success */
		list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		$status = $module->translate('Changes saved successfully');
	    }
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	global $gallery;

	$ItemEditPhoto = array();

	list ($ret, $ItemEditPhoto['isAdmin']) = GalleryCoreApi::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'ItemEditPhoto') {
	    /* First time around, reset the form */

	    /* Load the resizes */
	    list ($ret, $resizes) = GalleryCoreApi::fetchResizesByItemIds(array($item->getId()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!empty($resizes)) {
		foreach ($resizes[$item->getId()] as $resize) {
		    if (preg_match('/(?:scale|resize)\|(\d+)(?:,(\d+))?/',
				   $resize->getDerivativeOperations(),
				   $matches)) {
			$width = $matches[1];
			$height = empty($matches[2]) ? $width : $matches[2];
			$form['resizes'][] = array('active' => 1,
						   'width' => $width, 'height' => $height);
		    }
		}
	    }

	    if (!empty($thumbnail)) {
		if (preg_match('/thumbnail\|(\d+)/',
			       $thumbnail->getDerivativeOperations(),
			       $matches)) {
		    $size = $matches[1];
		}
		$form['thumbnail']['size'] = $size;
	    }

	    $form['formName'] = 'ItemEditPhoto';
	}

	/* Tag on a few form blanks */
	$extraBlanks = 3;
	if (isset($form['resizes'])) {
	    foreach ($form['resizes'] as $resize) {
		if (!isset($resize['active'])) {
		    $extraBlanks--;
		}
	    }
	}

	while ($extraBlanks-- > 0) {
	    $form['resizes'][] = array('active' => 0, 'width' => '', 'height' => '');
	}

	/* Make sure that 'active' is set to a value */
	for ($i = 0; $i < sizeof($form['resizes']); $i++) {
	    if (!isset($form['resizes'][$i]['active'])) {
		$form['resizes'][$i]['active'] = false;
	    }
	}

	/* Figure out what options we can provide */
	list ($ret, $toolkit) =
	    GalleryCoreApi::getToolkitByOperation($item->getMimeType(), 'thumbnail');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$ItemEditPhoto['editSizes']['can']['createThumbnail'] = isset($toolkit);

	/* Figure out what options we can provide */
	list ($ret, $toolkit) = GalleryCoreApi::getToolkitByOperation($item->getMimeType(), 'scale');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$ItemEditPhoto['editSizes']['can']['createResizes'] = isset($toolkit);

	$template->setVariable('ItemEditPhoto', $ItemEditPhoto);
	$template->setVariable('controller', 'core:ItemEditPhoto');
	return array(GalleryStatus::success(), 'modules/core/templates/ItemEditPhoto.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	return (GalleryUtilities::isA($item, 'GalleryPhotoItem'));
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('Photo'));
    }
}
?>
