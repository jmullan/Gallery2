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
 * This module allows gallery administrator
 * to maintain MIME types and corresponding file extensions
 *
 * @package Mime
 */
class MimeModule extends GalleryModule {

    function MimeModule() {
        global $gallery;    
        $this->setId('mime');               /* this must match the directory name */
        $this->setName('MIME maintenance'); /* this is the module name            */
        $this->setDescription($gallery->i18n('Maintain MIME types and file extensions'));
        $this->setVersion('0.9.4');
        $this->setGroup('data', $this->translate('Extra Data'));
        $this->setCallbacks('getSiteAdminViews');
        $this->setRequiredCoreApi(array(5, 0));
        $this->setRequiredModuleApi(array(0, 10));    
    }

    /**
     * @see GalleryModule::isRecommendedDuringInstall
     */
    function isRecommendedDuringInstall() {
        return false;
    }

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {
        /* We don't require any special configuration */
        return array(GalleryStatus::success(), true);
    }
    
    /**
     * @see GalleryModule::getSiteAdminViews
     */
    function getSiteAdminViews() {
        global $gallery;
        return array(GalleryStatus::success(),
               array(array('name' => $this->translate('MIME Types'),
                           'view' => 'mime:MimeAdmin')));
    }
}
?>
