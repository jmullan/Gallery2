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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the addition of an item as a children to
 * another item.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddChildrenController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.addDataItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $lockIds[]) = $gallery->acquireReadLock($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$platform = $gallery->getPlatform();

	/*
	 * See if the album has a thumbnail.  If not, we'll create one during
	 * this upload.
	 */
	list ($ret, $thumbnailTable) = GalleryDerivativeHelper::fetchThumbnailsByItemIds($item->getId());
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$albumNeedsThumbnail = empty($thumbnailTable) ? true : false;

	$status = array();
	$error = array();
	if (isset($form['action']['addFromBrowser'])) {
	    
	    /* Upload any new files */
	    for ($i = 1; $i <= $form['uploadBoxCount']; $i++) {
		$newItem = null;
		
		if (!empty($form['tmp_name'][$i]) && !empty($form['size'][$i])) {
		    $file = array('name' => $form['name'][$i],
				  'type' => $form['type'][$i],
				  'tmp_name' => $form['tmp_name'][$i],
				  'error' => $form['error'][$i],
				  'size' => $form['size'][$i],
				  'caption' => $form['caption'][$i]);
		    
		    /* Get the mime type from the upload info. */
		    $mimeType = $file['type'];

		    /*
		     * If we don't get useful data from that or its a type we don't
		     * recognize, take a swing at it using the file name.
		     */
		    if ($mimeType == 'application/octet-stream' ||
			    $mimeType == 'application/unknown' ||
			    GalleryUtilities::convertMimeToExtension($mimeType) == null) {
			$extension = GalleryUtilities::getFileExtension($file['name']);
			$mimeType = GalleryUtilities::convertExtensionToMime($extension);
		    }

		    list ($ret, $newItem) = GalleryItemHelper::addItemToAlbum($file['tmp_name'],
									      basename($file['name']),
									      basename($file['name']),
									      $file['caption'],
									      $file['caption'],
									      $mimeType,
									      $item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    $status['addFromBrowser'][] = array('fileName' => $file['name'],
							'id' => $newItem->getId());
		}

		if (isset($newItem) && $albumNeedsThumbnail) {
		    list ($ret, $success) =
			GalleryItemHelper::setThumbnailFromItem($item->getId(), $newItem->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $albumNeedsThumbnail = !$success;
		}
	    }

	    /* Figure out where to redirect upon success */
	    $redirect['view'] = 'core:ItemAdmin';
	    $redirect['subView'] = 'core:ItemAddChildrenConfirmation';
	    $redirect['itemId'] = $itemId;

	} else if (isset($form['action']['findFilesFromLocalServer'])) {
	    /* Delegate back to the same view */
	} else if (isset($form['action']['addFromLocalServer'])) {
	    /* Delegate back to the same view */
	    $dir = $form['localServerPath'];

	    foreach ($form['localServerFiles'] as $fileKey => $unused) {
		$filename = $fileKey;
		$filepath = $dir . '/' . $filename;

		list ($base, $extension) = GalleryUtilities::getFileNameComponents($filename);
		$mimeType = GalleryUtilities::convertExtensionToMime($extension);

		list ($ret, $newItem) = GalleryItemHelper::addItemToAlbum($filepath,
									  $base,
									  $base,
									  $base,
									  $base,
									  $mimeType,
									  $item->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		if ($albumNeedsThumbnail) {
		    list ($ret, $success) =
			GalleryItemHelper::setThumbnailFromItem($item->getId(), $newItem->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $albumNeedsThumbnail = !$success;
		}

		$status['addFromLocalServer'][] = array('fileName' => $filename,
							'id' => $newItem->getId());
	    }

	    /* Figure out where to redirect upon success */
	    $redirect['view'] = 'core:ItemAdmin';
	    $redirect['subView'] = 'core:ItemAddChildrenConfirmation';
	    $redirect['itemId'] = $itemId;
	} else if (isset($form['action']['findFilesFromWebPage'])) {
	    /* Delegate back to the same view */
	}

	$ret = $gallery->releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:ItemAdmin';
	    $results['delegate']['subView'] = 'core:ItemAddChildren';
	}
	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for files to add as children to an album.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddChildrenView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;

	$itemId = GalleryUtilities::getRequestVariables('itemId');
	$mode = GalleryUtilities::getRequestVariables('mode');

	/* Make sure we have permission do edit this item */
	$ret = GalleryUserHelper::assertHasItemPermission($itemId, 'core.addDataItem');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $isAdmin) = GalleryUserGroupMap::isUserInSiteAdminGroup();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $item) = $gallery->loadEntitiesById($itemId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if ($form['formName'] == 'ItemAddChildren') {

	    /* Complain if we have any invalid data */

	} else {
	    /* First time around, load the form with item data */
	    $form['uploadBoxCount'] = 4;
	    $form['localServerPath'] = '';
	    $form['webPage'] = '';
	    $form['formName'] = 'ItemAddChildren';
	}

	list ($ret, $localServerDirs) = $gallery->getModuleParameter('core', 'uploadLocalServer.dirs');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (empty($localServerDirs)) {
	    $localServerDirList = array();
	} else {
	    $localServerDirList = split(',', $localServerDirs);
	}

	/*
	 * If the mode is empty get it from the session.  If it's empty there,
	 * default to uploading from the browser.  Either way, save the user's
	 * preference in the session.
	 */
	$session =& $gallery->getSession();
	if (empty($mode)) {
	    $mode = $session->get('core.view.ItemAddChildren.mode');
	    if (empty($mode)) {
		$mode = 'fromBrowser';
	    }
	}
	$session->put('core.view.ItemAddChildren.mode', $mode);

	/* Look up the platform type */
	$platform = $gallery->getPlatform();

	/* If we're uploading from the local server, get a file list now */
	if (isset($form['action']['findFilesFromLocalServer'])) {

	    /* Validate the path */
	    $form['localServerFiles'] = array();
	    if (empty($form['localServerPath'])) {
		$form['error']['localServerPath']['missing'] = 1;
	    } else if (!$platform->file_exists($form['localServerPath']) ||
		       !$platform->is_readable($form['localServerPath'])) {
		$form['error']['localServerPath']['invalid'] = 1;
	    } else if (!GalleryUtilities::isPathInList($form['localServerPath'], $localServerDirList)) {
		$form['error']['localServerPath']['illegal'] = 1;
	    } else {
		$mimeTypeItemMap = array();
		$path = $form['localServerPath'];
		if ($platform->is_dir($path)) {
		    $handle = $platform->opendir($path);

		    while (false !== ($fileName = $platform->readdir($handle))) {
			$gallery->guaranteeTimeLimit(5);
			if ($fileName == '.' || $fileName == '..') {
			    continue;
			}

			$filePath = $path . '/' . $fileName;
			if (!$platform->is_dir($filePath) && $platform->is_readable($filePath)){
			    $mimeType = GalleryUtilities::getMimeType($fileName);
			    if (!isset($mimeTypeItemMap[$mimeType])) {
				list ($ret, $mimeTypeItemMap[$mimeType]) =
				    GalleryItemHelper::newItemByMimeType($mimeType);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null);
				}
			    }
			    
			    $form['localServerFiles'][] =
				array('dirName' => $path,
				      'fileName' => $fileName,
				      'stat' => $platform->stat($filePath),
				      'itemType' => $mimeTypeItemMap[$mimeType]->itemTypeName(),
				      'fileKey' => $fileName);
			}
		    }
		    $platform->closedir($handle);
			  
		} else if ($platform->is_file($path) && !$platform->is_link($path)) {
		    $mimeType = GalleryUtilities::getMimeType($path);
		    if (!isset($mimeTypeItemMap[$mimeType])) {
			list ($ret, $mimeTypeItemMap[$mimeType]) = GalleryItemHelper::newItemByMimeType($mimeType);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }

		    $dirName = dirname($path);
		    $fileName = basename($path);
		    $form['localServerFiles'][] =
			array('dirName' => $dirName,
			      'fileName' => $fileName,
			      'stat' => $platform->stat($path),
			      'itemType' => $mimeTypeItemMap[$mimeType]->itemTypeName(),
			      'fileKey' => htmlentities($fileName));
		}
		$localServerFileCount = sizeof($form['localServerFiles']);
	    }
	} else if (isset($form['action']['findFilesFromWebPage'])) {
	    /*
	     * If we're uploading from a web page, get a file list now.
	     * Download the web page into a temporary file and then parse it
	     */
	    if (empty($form['webPage'])) {
		$form['error']['webPage']['missing'] = 1;
	    } else {
		$baseUrlComponents = parse_url($form['webPage']);
		if ($baseUrlComponents['scheme'] != 'http') {
		    $form['error']['webPage']['invalid'] = 1;
		} else {
		    $fd = $platform->fopen($form['webPage'], 'r');

		    /* Read the web page into a buffer */
		    $buffer = '';
		    do {
			$chunk = fread($fd, 4096);
			if (strlen($chunk) == 0) {
			    break;
			}

			$buffer .= $chunk;
		    } while (true);
		    fclose($fd);

		    /*
		     * Parse the buffer.  We match:
		     *  href="foo bar"    href='foo bar'   href=foo
		     *  src="foo bar"     src='foo bar'    src=foo
		     */
		    /* Parse the buffer */
		    preg_match_all('/(?:src|href)=(?:\'(.*?)\'|\"(.*?)\"|([^\'\"]*))/i', $buffer, $matches);

		    /* Validate the URLs as best we can */
		    $webPageUrlList = array();
		    $isSupported = array();
		    $seenBefore = array();
		    foreach (array_merge($matches[1], $matches[2], $matches[3]) as $url) {
			if (isset($seenBefore[$url])) {
			    continue;
			} else {
			    $seenBefore[$url] = 1;
			}

			/*
			 * Some sites (slashdot) have images that start with //
			 * and this confuses Gallery.  Prepend the base scheme.
			 */
			if (!strncmp($url, '//', 2)) {
			    $url = $baseUrlComponents['scheme'] . ':' . $url;
			}
			
			$urlComponents = parse_url($url);
			if (empty($urlComponents['scheme'])) {
			    $urlComponents['scheme'] = $baseUrlComponents['scheme'];
			}

			if (empty($urlComponents['path'])) {
			    continue;
			}

			$mimeType = GalleryUtilities::getMimeType($urlComponents['path']);
			if ($mimeType == 'application/unknown') {
			    continue;
			}
			if (!isset($mimeTypeItemMap[$mimeType])) {
			    list ($ret, $mimeTypeItemMap[$mimeType]) = GalleryItemHelper::newItemByMimeType($mimeType);
			    if ($ret->isError()) {
				return array($ret->wrap(__FILE__, __LINE__), null);
			    }
			}

			if (empty($urlComponents['host'])) {
			    $urlComponents['host'] = $baseUrlComponents['host'];
			}

			$tmp = $urlComponents['scheme'] . '://' . $urlComponents['host'];
			if (!empty($urlComponents['path'])) {
			    if ($urlComponents['path'][0] != '/' && $tmp[strlen($tmp)-1] != '/') {
				$tmp .= '/';
			    }
			    $tmp .= $urlComponents['path'];
			}

			if (!empty($urlComponents['query'])) {
			    $tmp .= '?' . $urlComponents['query'];
			}

			$form['webPageUrls'][] =
			    array('url' => $tmp,
				  'itemType' => $mimeTypeItemMap[$mimeType]->itemTypeName());
		    }
		    $webPageUrlCount = sizeof($form['webPageUrls']);
		}
	    }
	}

	$ItemAddChildren = array();
	$ItemAddChildren['mode'] = $mode;
	$ItemAddChildren['isAdmin'] = $isAdmin;
	$ItemAddChildren['localServerDirList'] = $localServerDirList;
	if (isset($localServerFileCount)) {
	    $ItemAddChildren['localServerFileCount'] = $localServerFileCount;
	}
	if (isset($webPageUrlCount)) {
	    $ItemAddChildren['webPageUrlCount'] = $webPageUrlCount;
	}
	
	$template->setVariable('ItemAddChildren', $ItemAddChildren);

	if ($mode == 'fromBrowser') {
	    $template->setVariable('enctype', 'multipart/form-data');
	}
	$template->setVariable('controller', 'core:ItemAddChildren');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/ItemAddChildren.tpl'));
    }
}
?>
