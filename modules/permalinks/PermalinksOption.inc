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
* Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
*/

/**
 * @version $Revision$ $Date$
 * @package Permalinks
 * @subpackage UserInterface
 * @author Pierre-Luc Paour <gallery@paour.com>
 */

GalleryCoreApi::relativeRequireOnce('modules/permalinks/classes/PermalinksMap.class');
GalleryCoreApi::relativeRequireOnce('modules/permalinks/classes/helpers/PermalinksMapHelper.class');

/**
 * This edit option allows you to create Permalinks for your item
 *
 * @package Permalinks
 * @subpackage UserInterface
 *
 */
class PermalinksOption extends ItemEditOption {
    
    /**
     * @see ItemEditOption::handleRequestAfterEdit
     */
    function handleRequestAfterEdit($form, &$item, &$preferred) {
	global $gallery;
	
	$warning = array();
	$error = array();

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'permalinks');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	
	if (!empty($form['PermalinksOption']['aliasName'])) {
	    $ret = PermalinksMapHelper::createAlias($form['PermalinksOption']['aliasName'], $item->getId());
	    if ($ret->isError()) {
		if (!($ret->getErrorCode() & ERROR_STORAGE_FAILURE)) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		
		/* Set our error status and fall back to the view. */
		$error[] = 'form[error][PermalinksOption][exists]';
	    } else {
		$warning[] = $module->translate('Permalink created successfully');
	    }
	}
	
	if (isset($form['PermalinksOption']['delete'])) {
	    foreach($form['PermalinksOption']['delete'] as $name => $status) {
		$ret = PermalinksMapHelper::deleteAlias($name);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}
		
		$warning[] = $module->translate('Permalink(s) deleted successfully');
	    }
	}
	
	return array(GalleryStatus::success(), $error, $warning);
    }
    
    /**
     * @see ItemEditOption::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	global $gallery;
	
	$ItemEditPermalinks = array();
	
	list($ret, $aliases) = PermalinksMapHelper::fetchAliasesForItem($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	
	$PermalinksOption['aliases'] = $aliases;
	
	$template->setVariable('PermalinksOption', $PermalinksOption);
	return array(GalleryStatus::success(),
		'modules/permalinks/templates/PermalinksOption.tpl', 'modules_permalinks');
    }
    
    /**
     * @see ItemEditOption::isAppropriate
     */
    function isAppropriate($item, $thumbnail) {
	return array(GalleryStatus::success(), GalleryUtilities::isA($item, 'GalleryItem'));
    }
}
?>
