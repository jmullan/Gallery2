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
 * @subpackage UserInterface
 * @author Felix Rabinovich <felix@rabinovich.org>
 */

/**
 * This ItemAddOption uses the size limit values and resizes
 * gallery item when the image is uploaded.
 *
 * @package SizeLimit
 * @subpackage UserInterface
 */
GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/SizeLimitHelper.class');

class SetSizeOption extends ItemAddOption {

    /**
     * @see ItemAddOption::isAppropriate
     */
    function isAppropriate() {
        return array(GalleryStatus::success(), true);
    }

    /**
     * @see ItemAddOption::handleRequestAfterAdd
     */
    function handleRequestAfterAdd($form, &$item) {
        /* we should come here only if we are adding a photo, not sub-album */
        $albumId = $item->getParentId();        
        list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'sizelimit');
        if ($ret->isError()) {
            return $ret->wrap(__FILE__, __LINE__);
        }
            
        list ($ret, $param) = GalleryCoreApi::fetchAllPluginParameters(
            'module', 'sizelimit', $albumId);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null, null);
        }
        $preserveOriginal = isset($param['keepOriginal']) && $param['keepOriginal'];
        $warnings = array();
        
        if (isset($param['height']) && $param['width'] > 0) {
            $args = array($param['width'], $param['height']);
            if (!$preserveOriginal) {
                $ret = SizeLimitHelper::applyLimits($item, 'resize', $args);
            } else {
                $ret = SizeLimitHelper::buildDerivativeWithLimits($item, 'resize', $args);                
            }
            if ($ret->isError()) {
                if ($ret->getErrorCode() | ERROR_UNSUPPORTED_FILE_TYPE) {
                    $warnings[] = $module->translate(array('text' => 'WARNING: Cannot resize mime type %s',
                        'arg1' => $item->getMimeType()));
                } else {
                    return array($ret->wrap(__FILE__, __LINE__), null, null);
                }
            }
        }

        if (isset($param['size']) && $param['size'] > 0) {
            $args = array($param['size']);
            /* compare the item size (in kilobytes) */
            if (($item->getSize() >> 10) > $param['size']) {
                if (!$preserveOriginal) {
                    $ret = SizeLimitHelper::applyLimits($item, 'compress', $args);
                } else {
                    $ret = SizeLimitHelper::buildDerivativeWithLimits($item, 'compress', $args);                
                }
                if ($ret->isError()) {
                    if ($ret->getErrorCode() | ERROR_UNSUPPORTED_FILE_TYPE) {
                        $warnings[] = $module->translate(
                            array('text' => 'WARNING: Cannot compress mime type %s',
                            'arg1' => $item->getMimeType()));
                    } else {
                        return array($ret->wrap(__FILE__, __LINE__), null, null);
                    }
                }
            }
        }
        return array(GalleryStatus::success(), array(), $warnings);
    }
}
?>
