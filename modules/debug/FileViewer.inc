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
 * @package Debug
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This view will display a file.  Inspired by a contribution from Jesse Mullan
 *
 * @package Debug
 * @subpackage UserInterface
 */
class FileViewerView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate()
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	$platform = $gallery->getPlatform();

	list ($file, $line) = GalleryUtilities::getRequestVariables('file', 'line');

	/* Make sure the file is on the approved list */
	$legal = false;
	$manifest = GalleryUtilities::readManifest();
	if (isset($manifest[$file]) && $manifest[$file]['viewable']) {
	    $lines = $platform->file(dirname(__FILE__) . '/../../' . $file);
	    $actualChecksum = sprintf("%u", crc32(join("", $lines)));
	    if ($actualChecksum == $manifest[$file]['checksum']) {
		$legal = true;
	    }
	}

	$FileViewer = array();

	if ($legal) {
	    $bodyFile = 'FileViewerLegalFile.tpl';
	    $FileViewer['fileName'] = $file;
	    $FileViewer['currentLine'] = $line;
	    $FileViewer['lines'] = $lines;
	} else {
	    $bodyFile = 'FileViewerIllegalFile.tpl';
	}
	$template->setVariable('FileViewer', $FileViewer);

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'debug');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$template->title($module->translate('Gallery Debug File Viewer'));
	return array(GalleryStatus::success(),
		     array('body' => 'modules/debug/templates/' . $bodyFile));
    }
}
?>
