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
 * @todo Add support for other ways of adding images (from server, from http...)
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
	if (isset($form['action']['addFromBrowser'])) {
	    
	    /* Upload any new files */
	    for ($i = 1; $i <= $form['uploadBoxCount']; $i++) {
		$file = $form['fileUpload'][$i];
		if (!empty($file['tmp_name']) && !empty($file['size'])) {
		    
		    /* Get the mime type from the upload info. */
		    $mimeType = $file['type'];

		    /*
		     * If we don't get useful data from that, take a swing at
		     * it using the file name.
		     */
		    if ($mimeType == 'application/octet-stream' || $mimeType == 'application/unknown') {
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

		if ($albumNeedsThumbnail) {
		    $ret = GalleryItemHelper::setThumbnailFromItem($item->getId(), $newItem->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $albumNeedsThumbnail = false;
		}
	    }

	    /* Figure out where to redirect upon success */
	    $redirectParams['view'] = 'core:ItemAdmin';
	    $redirectParams['subView'] = 'core:ItemAddChildrenConfirmation';
	    $redirectParams['itemId'] = $itemId;

	} else if (isset($form['action']['findFilesFromLocalServer'])) {
	    /* Delegate back to the same view */
	} else if (isset($form['action']['addFromLocalServer'])) {
	    /* Delegate back to the same view */
	    $dir = $form['localServerPath'];
	    foreach ($form['localServerFiles'] as $fileKey => $unused) {
		$basename = base64_decode($fileKey);
		$filename = $dir . '/' . $basename;
		    
		$extension = GalleryUtilities::getFileExtension($filename);
		$mimeType = GalleryUtilities::convertExtensionToMime($extension);

		list ($ret, $newItem) = GalleryItemHelper::addItemToAlbum($filename,
									  $basename,
									  $basename,
									  $basename,
									  $basename,
									  $mimeType,
									  $item->getId());
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		
		if ($albumNeedsThumbnail) {
		    $ret = GalleryItemHelper::setThumbnailFromItem($item->getId(), $newItem->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $albumNeedsThumbnail = false;

		}

		$status['addFromLocalServer'][] = array('fileName' => $basename,
							'id' => $newItem->getId());
	    }

	    /* Figure out where to redirect upon success */
	    $redirectParams['view'] = 'core:ItemAdmin';
	    $redirectParams['subView'] = 'core:ItemAddChildrenConfirmation';
	    $redirectParams['itemId'] = $itemId;
	}

	$ret = $gallery->releaseLocks($lockIds);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	if (!empty($status)) {
	    $session =& $gallery->getSession();
	    list ($ret, $redirectParams['statusId']) = $session->putStatus($status);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	if (!empty($redirectParams)) {
	    $urlGenerator = $gallery->getUrlGenerator();
	    $results['redirect'] = $redirectParams;
	} else {
	    if (empty($results['view'])) {
		$results['view'] = 'core:ItemAdmin';
		GalleryUtilities::putRequestVariable('subView', 'core:ItemAddChildren');
	    }
	}

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
     * @see GalleryView::renderBody
     */
    function renderBody($form) {
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
	    $form = array();

	    $form['uploadBoxCount'] = 4;
	    $form['localServerPath'] = '';
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
	    list ($ret, $mode) = $session->get('core.view.ItemAddChildren.mode');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
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

		    while (false !== ($fileName = readdir($handle))) {
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
				      'fileKey' => base64_encode($fileName));
			}
		    }
		    closedir($handle);
			  
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
	    }
	}

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('form', $form);
	$template->setVariable('mode', $mode);
	$template->setVariable('isAdmin', $isAdmin);
	$template->setVariable('localServerDirList', $localServerDirList);
	$template->setVariable('item', $item->getMemberData());
	$template->setVariable('controller', 'core:ItemAddChildren');
	$html = $template->render('ItemAddChildren.tpl');

	return array(GalleryStatus::success(), $html);
    }
}
?>
