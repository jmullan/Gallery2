<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * This controller will handle the editing of a photo
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 * @version $Revision$ $Date$
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

	    /* Validate the input data */
	    for ($i = 0; $i < sizeof($form['resizes']); $i++) {
		if (empty($form['resizes'][$i]['active'])) {
		    continue;
		}

		if (empty($form['resizes'][$i]['width'])
			|| empty($form['resizes'][$i]['height'])) {
		    $error[] = sprintf('form[error][resizes][%d][size][missing]', $i);
		} else if (!($tmp = rtrim($form['resizes'][$i]['width'], '%'))
			|| !is_numeric($tmp) || $tmp <= 0
			|| !($tmp = rtrim($form['resizes'][$i]['height'], '%'))
			|| !is_numeric($tmp) || $tmp <= 0) {
		    $error[] = sprintf('form[error][resizes][%d][size][invalid]', $i);
		}
	    }

	    if (empty($error)) {
		/* Get and delete all current resizes */
		list ($ret, $resizesTable) =
		    GalleryCoreApi::fetchResizesByItemIds(array($item->getId()));
		if ($ret) {
		    return array($ret, null, null, null);
		}
		foreach ($resizesTable as $resizes) {
		    foreach ($resizes as $resize) {
			$postFilter = $resize->getPostFilterOperations();
			$ret = GalleryCoreApi::deleteEntityById($resize->getId());
			if ($ret) {
			    return array($ret, null, null, null);
			}
		    }
		}

		list ($ret, $source) = GalleryCoreApi::fetchPreferredSource($item);
		if ($ret) {
		    return array($ret, null, null, null);
		}

		/*
		 * Make sure that we have a toolkit before adding back the resizes
		 */
		list ($ret, $toolkit, $outputMimeType) =
		    GalleryCoreApi::getToolkitByOperation($source->getMimeType(), 'scale');
		if ($ret) {
		    return array($ret, null, null, null);
		}

		if (isset($toolkit)) {
		    /* Add the new resizes */
		    for ($i = 0; $i < sizeof($form['resizes']); $i++) {
			if (empty($form['resizes'][$i]['active'])) {
			    continue;
			}

			list ($ret, $derivative) =
			    GalleryCoreApi::newFactoryInstanceByHint('GalleryDerivative',
								     $source->getEntityType());
			if ($ret) {
			    return array($ret, null, null, null);
			}

			if (!isset($derivative)) {
			    return array(GalleryCoreApi::error(ERROR_MISSING_OBJECT),
					 null, null, null);
			}

			$ret = $derivative->create($item->getId(), DERIVATIVE_TYPE_IMAGE_RESIZE);
			if ($ret) {
			    return array($ret, null, null, null);
			}

			$operations = 'scale|' . $form['resizes'][$i]['width'] . ',' .
			    $form['resizes'][$i]['height'];

			list ($ret, $newOperations, $newOutputMimeType) =
			    GalleryCoreApi::makeSupportedViewableOperationSequence(
				$outputMimeType, $operations);
			if ($ret) {
			    return array($ret, null, null, null);
			}

			if ($newOperations && $newOutputMimeType) {
			    $derivative->setMimeType($newOutputMimeType);
			    $derivative->setDerivativeOperations($newOperations);
			} else {
			    $derivative->setMimeType($outputMimeType);
			    $derivative->setDerivativeOperations($operations);
			}

			$derivative->setDerivativeSourceId($source->getId());
			if (isset($postFilter)) {
			    $derivative->setPostFilterOperations($postFilter);
			}

			$ret = $derivative->save();
			if ($ret) {
			    return array($ret, null, null, null);
			}
		    }
		}

		/* Figure out where to redirect upon success */
		list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
		if ($ret) {
		    return array($ret, null, null, null);
		}
		$status = $module->translate('Changes saved successfully');
	    }
	}

	return array(null, $error, $status, false);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	global $gallery;

	if ($form['formName'] != 'ItemEditPhoto') {
	    /* First time around, reset the form */
	    $form['formName'] = 'ItemEditPhoto';

	    /* Load the resizes */
	    list ($ret, $resizes) = GalleryCoreApi::fetchResizesByItemIds(array($item->getId()));
	    if ($ret) {
		return array($ret, null, null);
	    }

	    if (!empty($resizes)) {
		foreach ($resizes[$item->getId()] as $resize) {
		    if (preg_match('/(?:scale|resize)\|(\d+%?)(?:,(\d+%?))?/',
				   $resize->getDerivativeOperations(), $matches)) {
			$width = $matches[1];
			$height = empty($matches[2]) ? $width : $matches[2];
			$form['resizes'][] = array('active' => 1,
						   'width' => $width, 'height' => $height);
		    }
		}
	    }
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

	$ItemEditPhoto = array();

	/* Check to see if we have a preferred source */
	list ($ret, $results) =
	    GalleryCoreApi::fetchPreferredsByItemIds(array($item->getId()));
	if ($ret) {
	    return array($ret, null, null);
	}

	$sourceMimeTypes = array($item->getMimeType());
	if (empty($results)) {
	    $ItemEditPhoto['editPhoto']['hasPreferredSource'] = false;
	} else {
	    $preferred = $results[$item->getId()];
	    if (preg_match("/(rotate|resize|scale)\|/", $preferred->getDerivativeOperations())) {
		$ItemEditPhoto['editPhoto']['hasPreferredSource'] = true;
	    } else {
		$ItemEditPhoto['editPhoto']['hasPreferredSource'] = false;
	    }
	    $sourceMimeTypes[] = $preferred->getMimeType();
	}

	/* Figure out what options we can provide */
	list ($ret, $ItemEditPhoto['editSizes']['can']['createResizes']) =
	    $this->_checkForOperation('resize', $sourceMimeTypes);
	if ($ret) {
	    return array($ret, null, null);
	}

	$template->setVariable('ItemEditPhoto', $ItemEditPhoto);
	$template->setVariable('controller', 'core.ItemEditPhoto');
	return array(null,
		     'modules/core/templates/ItemEditPhoto.tpl', 'modules_core');
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
	if ($ret) {
	    return array($ret, null);
	}

	return array(null, $module->translate('Photo'));
    }
}
?>
