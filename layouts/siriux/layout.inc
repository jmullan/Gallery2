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
 * @package Gallery
 * @author Nico Kaiser <nico@siriux.net>
 */

/* Load parent class */
GalleryCoreApi::relativeRequireOnce('layouts/matrix/layout.inc');

/**
 * siriux.net Layout for Gallery
 *
 * @package GalleryLayout
 * @subpackage Layout
 */
class SiriuxLayout extends MatrixLayout {

    /**
     * Constructor
     */
    function SiriuxLayout() {
	global $gallery;

	$this->setId('siriux');
	$this->setName('Siriux');
	$this->setDescription($gallery->i18n('Siriux.net Gallery layout'));
	$this->setVersion('0.9.2');
	$this->setL10Domain('layouts_siriux');
	$this->setRequiredLayoutApi(array(0, 8));
	$this->setRequiredCoreApi(array(5, 0));
    }


    /**
     * @see MatrixLayout::_loadAlbumTemplate
     */
    function _loadAlbumTemplate(&$template, $item, $params) {
	list ($ret, $matrixResult) = parent::_loadAlbumTemplate($template, $item, $params);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (is_array($matrixResult)) {
	    /* Return now if we are doing a redirect */
	    return array(GalleryStatus::success(), $matrixResult);
	}

	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['back']) && isset($layout['navigator']['first'])) {
	    $layout['navigator']['back'] = $layout['navigator']['first'];
	}
	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['next']) && isset($layout['navigator']['last'])) {
	    $layout['navigator']['next'] = $layout['navigator']['last'];
	}

	$template->head('layouts/matrix/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/siriux/layout.css');
	return array(GalleryStatus::success(),
		     array('body' => 'layouts/siriux/templates/albumBody.tpl'));
    }

    /**
     * @see MatrixLayout::_loadSingleTemplate
     */
    function _loadSingleTemplate(&$template, $item, $params) {
	list ($ret, $matrixResult) = parent::_loadSingleTemplate($template, $item, $params);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (is_array($matrixResult)) {
	    /* Return now if we are doing a redirect */
	    return array(GalleryStatus::success(), $matrixResult);
	}

	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['back']) && isset($layout['navigator']['first'])) {
	    $layout['navigator']['back'] = $layout['navigator']['first'];
	}
	$layout =& $template->getVariableByReference('layout');
	if (!isset($layout['navigator']['next']) && isset($layout['navigator']['last'])) {
	    $layout['navigator']['next'] = $layout['navigator']['last'];
	}

	$template->head('layouts/matrix/templates/head.tpl');
	$template->style('templates/layout.css');
	$template->style('layouts/siriux/layout.css');
	return array(GalleryStatus::success(),
		     array('body' => 'layouts/siriux/templates/singleBody.tpl'));
    }
}
?>
