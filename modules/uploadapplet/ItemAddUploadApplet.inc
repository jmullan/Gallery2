<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
 * @package uploadapplet
 * @author Pierre-Luc Paour <gallery@paour.com>
 */

class ItemAddUploadApplet extends ItemAddPlugin {

    /**
     * @see ItemAdd:loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	global $gallery;
	
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'uploadapplet');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] != 'ItemAddUploadApplet') {
	    $form['formName'] = 'ItemAddUploadApplet';
	}

	$plugins = GalleryCoreApi::getAllFactoryImplementationIds('ItemAddPlugin');

	if (!isset($plugins['ItemAddGalleryRemote'])) {
	    $template->setVariable('NoProtocolError', 1);
	} else {
	    $cookieInfo = session_get_cookie_params();
	    $urlGenerator = $gallery->getUrlGenerator();
	    $dir = $urlGenerator->getCurrentUrlDir();
	    $session = $gallery->getSession();
	    list ($session_name, $session_id) = $session->getSessionDescriptor();
	    
	    $template->setVariable('width', 400);
	    $template->setVariable('height', 300);
	    $template->setVariable('code', 'com.gallery.GalleryRemote.GRAppletMini');
	    $template->setVariable('archive', "${dir}modules/uploadapplet/applets/GalleryRemoteAppletMini.jar," . 
		    "${dir}modules/uploadapplet/applets/GalleryRemoteHTTPClient.jar," . 
		    "${dir}modules/uploadapplet/applets/applet_img.jar");
	    $template->setVariable('url', $dir);
	    $template->setVariable('cookie_name', $session_name);
	    $template->setVariable('cookie_value', $session_id);
	    $template->setVariable('cookie_domain', $cookieInfo['domain']);
	    $template->setVariable('cookie_path', $cookieInfo['path']);
	    $template->setVariable('album', $item->getId());
	    $template->setVariable('defaults', array());
	    $template->setVariable('overrides', array("toSysOut" => "true"));
	}

	return array(GalleryStatus::success(), 'modules/uploadapplet/templates/ItemAddUploadApplet.tpl');
    }

    /**
     * @see ItemAddPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'uploadapplet');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('Upload Applet'));
    }
}
?>
