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
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	if ($form['formName'] != 'ItemAddUploadApplet') {
	    $form['formName'] = 'ItemAddUploadApplet';
	}

	list ($ret, $modules) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	$ItemAddUploadApplet = array();

	if (!isset($modules['remote']['active']) || !$modules['remote']['active']) {
	    $ItemAddUploadApplet['NoProtocolError'] = 1;
	} else {
	    $session =& $gallery->getSession();
	    $ItemAddUploadApplet['NoProtocolError'] = 0;
	    $ItemAddUploadApplet['cookieName'] = $session->getKey();
	    $ItemAddUploadApplet['cookieValue'] = $session->getId();
	    $ItemAddUploadApplet['cookieDomain'] = $session->getCookieDomain();
	    $ItemAddUploadApplet['cookiePath'] = $session->getCookiePath();
	    $ItemAddUploadApplet['album'] = $item->getId();
	    $ItemAddUploadApplet['defaults'] = array();
	    $ItemAddUploadApplet['overrides'] = array('toSysOut' => 'true');
	    $ItemAddUploadApplet['userAgent'] = GalleryUtilities::getServerVar('HTTP_USER_AGENT');

	    $urlGenerator =& $gallery->getUrlGenerator();
	    $ItemAddUploadApplet['g2BaseUrl'] = $urlGenerator->getCurrentUrlDir();
	}

	$template->setVariable('ItemAddUploadApplet', $ItemAddUploadApplet);
	return array(GalleryStatus::success(),
		     'modules/uploadapplet/templates/ItemAddUploadApplet.tpl',
		     'modules_uploadapplet');
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
