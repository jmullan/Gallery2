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

class SlideshowAppletView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate()
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'slideshowapplet');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	list ($ret, $modules) = GalleryCoreApi::fetchPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	$startId = null;

	/*$itemListString = GalleryUtilities::getRequestVariables('itemList');
	if (!empty($itemListString)) {
	    // Build slideshow using specified items..
	    $item = explode('|', $itemListString);
	} else {*/
	    // Build slideshow for an album..
	    list ($ret, $item) = $this->_getItem();
	    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!$item->getCanContainChildren()) {
			// Photo: do slideshow of parent album, start at this photo
			$startId = $item->getId();
			list ($ret, $item) = GalleryCoreApi::loadEntitiesById($item->getParentId());
			if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			}
	    }
	//}

	$GRApplet = array();
	$GRApplet['extra'] = array();

	if (!isset($modules['remote']['active']) || !$modules['remote']['active']) {
	    $GRApplet['NoProtocolError'] = 1;
	} else {
	    $session =& $gallery->getSession();
	    $GRApplet['NoProtocolError'] = 0;
	    $GRApplet['cookieName'] = $session->getKey();
	    $GRApplet['cookieValue'] = $session->getId();
	    $GRApplet['cookieDomain'] = $session->getCookieDomain();
	    $GRApplet['cookiePath'] = $session->getCookiePath();
	    $GRApplet['album'] = $item->getId();
	    $GRApplet['defaults'] = array();
	    $GRApplet['overrides'] = array('toSysOut' => 'true');
	    $GRApplet['userAgent'] = GalleryUtilities::getServerVar('HTTP_USER_AGENT');
	    $GRApplet['galleryVersion'] = 2;
	    $GRApplet['code'] = 'com.gallery.GalleryRemote.GRAppletSlideshow';

	    if (isset($startId)) {
	    	// format the start_from as album_picture, that's what GR expects
	    	$GRApplet['extra']['gr_slideshow_start_from'] = $item->getId().'_'.$startId;
	    }

	    $urlGenerator =& $gallery->getUrlGenerator();
	    $GRApplet['g2BaseUrl'] = $urlGenerator->getCurrentUrlDir();
	}

	$template->setVariable('GRApplet', $GRApplet);

	//$template->title($module->translate('Slideshow'));
	return array(GalleryStatus::success(),
		     array('body' => 'modules/slideshowapplet/templates/SlideshowApplet.tpl'));
    }

    /**
     * @see GalleryView::getViewDescription()
     */
    function getViewDescription() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'slideshowapplet');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	return array(GalleryStatus::success(), $module->translate('slideshow (fullscreen)'));
    }
}
?>
