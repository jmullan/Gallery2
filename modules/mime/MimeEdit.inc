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
 * @package Mime
 * @author Felix Rabinovich <Felix@Rabinovich.org> 
 */

/**
 * @package Mime
 * @subpackage Administration
 */
class MimeEditController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
        global $gallery;
    
        $ret = GalleryCoreApi::assertUserIsSiteAdministrator();
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
        $subView = isset($form['action']['apply']) ? 'mime:MimeEdit' : 'mime:MimeAdmin';
        $error = array();
        
        if (isset($form['action']['save']) || isset($form['action']['apply'])) {
            if (empty($form['mimeType'])) {
                $error[] = 'form[error][mimeType][missing]';
            } else {
                $allEmpty = true;
                foreach ($form['extension'] as $ext) {
                    if (!empty($ext)) {
                        $allEmpty = false;
                        $mimeTypeMap[] = array('extension' => $ext, 'mimeType' => $form['mimeType'],
                            'viewable' => (int) isset($form['viewable']));
                    }
                }
                if ($allEmpty) {
                    $error[] = 'form[error][ext][missing]';
                } else {
                    $ret = GalleryCoreApi::removeMimeType(array('mimeType' => $form['mimeType']));
                    if ($ret->isError()) {
                        return array($ret->wrap(__FILE__, __LINE__), null);
                    }
                    foreach ($mimeTypeMap as $mimeType) {
                        $ret = GalleryMimeTypeMap::addMapEntry($mimeType);    
                        if ($ret->isError()) {
                            return array($ret->wrap(__FILE__, __LINE__), null);
                        }
                    }
                }
            }
        }

        if (empty($error)) {
            $results['redirect'] = array('view' => 'core:SiteAdmin', 'subView' => $subView);
        } else {
            $results['delegate'] = array('view' => 'core:SiteAdmin', 'subView' => 'mime:MimeEdit');
        }
        $results['status'] = array('mimeType' => $form['mimeType']);
        $results['error'] = $error;
    
        return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Mime
 * @subpackage Administration
 */
class MimeEditView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
        global $gallery;
	    $form['formName'] = 'MimeEdit';
        
    	$status = $template->getVariable('status');
        $mimeType = $status['mimeType'];
        list ($ret, $extensions) = GalleryCoreApi::convertMimeToExtensions($mimeType);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }

        $MimeEdit['mimeType'] = $mimeType;
        $MimeEdit['extensions'] = $extensions;
        list ($ret, $MimeEdit['viewable']) = GalleryCoreApi::isViewableMimeType($mimeType);
        if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
        }
        $template->setVariable('controller', 'mime:MimeEdit');
        $template->setVariable('MimeEdit', $MimeEdit);
        return array(GalleryStatus::success(),
             array('body' => 'modules/mime/templates/MimeEdit.tpl'));
    }
}
?>
