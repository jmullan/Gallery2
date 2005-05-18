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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This view lets you make very simple callbacks to the framework to
 * get very specific data.  Eventually this will probably get refactored
 * into a much more sophisticated framework.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class SimpleCallbackView extends GalleryView {

    /**
     * @see GalleryView::isImmediate()
     */
    function isImmediate() {
        return true;
    }
    
    /**
     * @see GalleryView::isImmediate()
     */
    function renderImmediate($status, $error) {
	global $gallery;
	
	$command = GalleryUtilities::getRequestVariables('command');
	list ($ret, $anonymousUserId) = GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	header("Content-type: text/plain");
	
	switch($command) {
	case "lookupUsername":
	    if ($gallery->getActiveUserId() != $anonymousUserId) {
		$prefix = GalleryUtilities::getRequestVariables('prefix');
		list ($ret, $usernames) = GalleryCoreApi::fetchUsernames(10, null, $prefix);
		if ($ret->isSuccess()) {
		    print join("\n", $usernames);
		}
	    }
	    break;

	case "lookupGroupname":
	    if ($gallery->getActiveUserId() != $anonymousUserId) {
		$prefix = GalleryUtilities::getRequestVariables('prefix');
		list ($ret, $usernames) = GalleryCoreApi::fetchGroupNames(10, null, $prefix);
		if ($ret->isSuccess()) {
		    print join("\n", $usernames);
		}
	    }
	    break;
            
        case "lookupDirs":
	    $prefix = GalleryUtilities::getRequestVariables('prefix');
            $dirs = $this->_getAllImmediateSubdirs($prefix);
            print join("\n", $dirs);
	    break;
            
        case "lookupFiles":
	    $prefix = GalleryUtilities::getRequestVariables('prefix');
            $dirs = $this->_getAllFiles($prefix);
            print join("\n", $dirs);
	    break;
	}
        
	return GalleryStatus::success();
    }
    
    function _getAllImmediateSubdirs($path) {
        $dirList = array();
        if (!file_exists($path) || !is_dir($path)) {
            return $dirList;
        }

        if ($dir = opendir($path)) {
            while (($file = readdir($dir)) !== false) {
                if ($file == '.' || $file == '..') {
                    continue;
                }

                if ($path[strlen($path)-1] == DIRECTORY_SEPARATOR) {
                    $file = $path . $file;
                } else {
                    $file = sprintf('%s%s%s', $path, DIRECTORY_SEPARATOR, $file);
                }

                if (is_dir($file)) {
                    $dirList[] = $file;
                }
            }
            closedir($dir);
        }

        sort($dirList);
        return $dirList;
    }

    function _getAllFiles($path) {
        $dirList = array();
        $fileList = array();
        if (!file_exists($path) || !is_dir($path)) {
            return $dirList;
        }

        if ($dir = opendir($path)) {
            while (($file = readdir($dir)) !== false) {
                if ($file == '.' || $file == '..') {
                    continue;
                }

                if ($path[strlen($path)-1] == DIRECTORY_SEPARATOR) {
                    $file = $path . $file;
                } else {
                    $file = sprintf('%s%s%s', $path, DIRECTORY_SEPARATOR, $file);
                }

                if (is_dir($file)) {
                    $dirList[] = $file;
                } else if (is_file($file)) {
                    $fileList[] = $file;
                }
            }
            closedir($dir);
        }

        sort($dirList);
        sort($fileList);
        $result = array_merge($dirList, $fileList);
        return $result;
    }

}
?>
