<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
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
 * @package ImageBlock
 * @author Jay Rossiter <cryptographite@users.sf.net>
 */

/**
 * @package ImageBlock
 * @subpackage UserInterface
 */
class ImageBlockOption extends ItemEditOption {

    /**
     * @see ItemEditOption::handleRequestAfterEdit
     */
    function handleRequestAfterEdit($form, &$item, &$preferred) {
	$error = array();
	$warning = array();

	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ImageBlockHelper.class');

	if (empty($form['ImageBlockOption']['isDisabled']) ||
		$form['ImageBlockOption']['isDisabled'] == 'off') {
	    $isDisabled = false;
	} else {
	    $isDisabled = true;
	}

	if (empty($form['ImageBlockOption']['isRecursive']) ||
		$form['ImageBlockOption']['isRecursive'] == 'on') {
	    $isRecursive = true;
	} else {
	    $isRecursive = false;
	}

	$ret = ImageBlockHelper::setDisabledFlag($item, $isRecursive, $isDisabled);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	return array(GalleryStatus::success(), $error, $warning);
    }

    /**
     * @see ItemEditOption::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/ImageBlockHelper.class');
	list($ret, $form['ImageBlockOption']['isDisabled']) =
	    ImageBlockHelper::getDisabledFlag($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	return array(GalleryStatus::success(),
		     'modules/imageblock/templates/ImageBlockOption.tpl',
		     'modules_imageblock');
    }

    /**
     * @see ItemEditOption::isSupported
     */
    function isAppropriate($item, $thumbnail) {
	return array(GalleryStatus::success(), GalleryUtilities::isA($item, 'GalleryAlbumItem'));
    }
}
?>
