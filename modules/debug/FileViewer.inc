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

	list ($file, $line) = GalleryUtilities::getRequestVariables('file', 'line');

	list ($ret, $modules) = GalleryPluginMap::getPluginStatus('module');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Make sure the file is on the approved list */
	$moduleDir = $gallery->getConfig('code.gallery.modules');
	$platform = $gallery->getPlatform();
	$approved = false;
	$approvedChecksum = 0;
	$legal = false;
	foreach ($modules as $moduleId => $moduleStatus) {
	    if (empty($moduleStatus['active'])) {
		continue;
	    }

	    $approvedListFile = $moduleDir . $moduleId . '/debug/viewableFiles.txt';
	    if ($platform->file_exists($approvedListFile)) { 
		foreach ($platform->file($approvedListFile) as $approvedFile) {
		    list ($approvedChecksum, $octets, $approvedFile) = split(' ', $approvedFile);
		    $approvedFile = trim($approvedFile);
		    if ($approvedFile == $file) {
			$approved = true;
			break 2;
		    }
		}
	    }
	}

	if ($approved) {
	    $base = $gallery->getConfig('code.gallery.base');
	    $lines = $platform->file($base . '/' . $file);
	    $actualChecksum = sprintf("%u", crc32(join("", $lines)));
	    if ($approvedChecksum == $actualChecksum) {
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

	return array(GalleryStatus::success(),
		     'modules/debug/templates/FileViewerHead.tpl',
		     'modules/debug/templates/' . $bodyFile);
    }
}
?>
