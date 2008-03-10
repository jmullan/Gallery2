<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
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

GalleryCoreApi::requireOnce('modules/slideshow/classes/SlideshowHelper.class');

/**
 * Display the slideshow
 * @package Slideshow
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 * @version $Revision$
 */
class SlideshowView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$Slideshow = array();

	list ($itemListString, $startId) =
	    GalleryUtilities::getRequestVariables('itemList', 'startId');
	if (isset($startId)) {
	    $startId = (int)$startId;
	}
	if (!empty($itemListString)) {
	    foreach (explode('|', $itemListString) as $id) {
		$itemIds[] = (int)$id;
	    }
	    list ($ret, $items, $start) = SlideshowHelper::buildItemsSlideshow($itemIds, $startId);
	    if ($ret) {
		return array($ret, null);
	    }
	} else {
	    /* Build slideshow for an album */
	    list ($ret, $item) = $this->getItem();
	    if ($ret) {
		return array($ret, null);
	    }
	    list ($ret, $items, $start) = SlideshowHelper::buildAlbumSlideshow($item, $startId);
	    if ($ret) {
		return array($ret, null);
	    }
	}

	$Slideshow['items'] = $items;
	$Slideshow['count'] = count($items);
	$Slideshow['start'] = $start;
	$template->setVariable('Slideshow', $Slideshow);

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'slideshow');
	if ($ret) {
	    return array($ret, null);
	}
	if (!empty($Slideshow['item']['title'])) {
	    $template->title($module->translate(array('text' => 'Slideshow for %s',
						      'arg1' => $Slideshow['item']['title'])));
	} else {
	    $template->title($module->translate('Slideshow'));
	}

        $template->javascript('lib/yui/yahoo-dom-event.js');
	$template->javascript('modules/slideshow/data/lytebox.js');
	$template->link(array('rel' => 'stylesheet',
			      'href' => 'modules/slideshow/data/lytebox.css',
			      'type' => 'text/css',
			      'media' => 'screen'));
	return array(null, array('body' => 'modules/slideshow/templates/Slideshow.tpl',
				 'useFullScreen' => true));
    }
}
?>
