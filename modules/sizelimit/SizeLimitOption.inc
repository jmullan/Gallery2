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
 * @package SizeLimit
 * @author Felix Rabinovich <felix@rabinovich.org>
 */

/**
 * This ItemEditOption allows the user to set size limits for an album.
 *
 * @package SizeLimit
 * @subpackage UserInterface
 */
class SizeLimitOption extends ItemEditOption {

    /**
     * @see ItemEditOption::isAppropriate
     */
    function isAppropriate($item, $thumbnail) {
        return array(GalleryStatus::success(), true);
    }
    
    /**
     * @see ItemEditOption::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {        
        /* 
         * Get the parameters for this album;
         * we are assuming that both $height and $width are either in or out...
         */
        $SizeLimitOption = array();
        list ($ret, $params) = GalleryCoreApi::fetchAllPluginParameters(
            'module', 'sizelimit', $item->getId());
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
        /* if there aren't any - assume 'no limits' */
        if (!isset($params['height']) || $params['height'] == 0) {
            $SizeLimitOption['dimensionChoice'] = 'unlimited';
            $SizeLimitOption['height'] = '';
            $SizeLimitOption['width'] = '';
        } else {
            $SizeLimitOption['dimensionChoice'] = 'explicit';
            $SizeLimitOption['height'] = $params['height'];
            $SizeLimitOption['width'] = $params['width'];
        }
        
        /* Now do the same for size */
        if (!isset($params['size']) || $params['size'] == 0) {
            $SizeLimitOption['sizeChoice'] = 'unlimited';
            $SizeLimitOption['filesize'] = '';
        } else {
            $SizeLimitOption['sizeChoice'] = 'explicit';
            $SizeLimitOption['filesize'] = $params['size'];
        }

        $SizeLimitOption['keepOriginal'] = 
            (isset($params['keepOriginal']) && $params['keepOriginal'] == 1);
        
        $template->setVariable('SizeLimitOption', $SizeLimitOption);
        return array(GalleryStatus::success(),
		     'modules/sizelimit/templates/SizeLimitOption.tpl',
		     'modules_sizelimit');
    }

    /**
     * @see ItemEditOption::handleRequestAfterEdit
     */
    function handleRequestAfterEdit($form, &$item, &$preferred) {
        $error = array();
        $warning = array();
        $setOriginal = false;
        switch ($form['SizeLimitOption']['dimensionChoice']) {
            case 'unlimited':
                /* delete parameter from plugin table */
    	        $ret = GalleryCoreApi::removePluginParameter('module', 'sizelimit', 'height', $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
    	        $ret = GalleryCoreApi::removePluginParameter('module', 'sizelimit', 'width', $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
    	        $ret = GalleryCoreApi::removePluginParameter('module', 'sizelimit', 
                    'keepOriginal', $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
                break;
                
            case 'explicit':
                /* figure out x and y and set them... */
                $dimensions = GalleryUtilities::getRequestVariables('SizeLimitOption_dimensions');
                $height = $dimensions['height'];
                $width = $dimensions['width'];
                /* Validate the input data. */
                if (!is_numeric($height) && !is_numeric($width)) {
                    $error[] = 'form[error][SizeLimitOption][dimensions][missing]';
                    break;
                }
                if (!is_numeric($height)) {
                    $height = $width;
                }
                if (!is_numeric($width)) {
                    $width = $height;
                }
    	        $ret = GalleryCoreApi::setPluginParameter('module', 'sizelimit', 'height', $height, $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
    	        $ret = GalleryCoreApi::setPluginParameter('module', 'sizelimit', 'width', $width, $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
                $setOriginal = true;
                break;
        }
        
        switch ($form['SizeLimitOption']['sizeChoice']) {
            case 'unlimited':
                /* delete parameter from plugin table */
    	        $ret = GalleryCoreApi::removePluginParameter('module', 'sizelimit', 
                    'size', $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
    	        $ret = GalleryCoreApi::removePluginParameter('module', 'sizelimit', 
                    'keepOriginal', $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
                break;
                
            case 'explicit':
                /* Validate the input data. */
                if (!is_numeric($form['SizeLimitOption']['filesize']) || 
                    $form['SizeLimitOption']['filesize'] < 1) {
                    $error[] = 'form[error][SizeLimitOption][filesize][invalid]';
                    break;
                }
                /* figure out x and y and set them... */
                $filesize = $form['SizeLimitOption']['filesize'];
    	        $ret = GalleryCoreApi::setPluginParameter('module', 'sizelimit', 'size', 
                    $filesize, $item->getId());
                if ($ret->isError()) {
                    return array($ret->wrap(__FILE__, __LINE__), null);
                }
                $setOriginal = true;
                break;
        }
        
        if ($setOriginal) {
            $ret = GalleryCoreApi::setPluginParameter('module', 'sizelimit', 'keepOriginal', 
                isset($form['SizeLimitOption']['keepOriginal']) ? 1 : 0, $item->getId());
            if ($ret->isError()) {
                return array($ret->wrap(__FILE__, __LINE__), null);
            }
        }
        return array(GalleryStatus::success(), $error, $warning);
    }
}
?>
