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
 * This controller will handle the addition of an item as a children to
 * another item.
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class ItemAddFromServer extends ItemAddPlugin {

    /**
     * @see ItemAddPlugin::handleRequest
     */
    function handleRequest($form, &$item) {
	global $gallery;
	$this->_platform =& $gallery->getPlatform();
	$this->_dirSep = $this->_platform->getDirectorySeparator();

	$status = array();
	$error = array();

	if (isset($form['action']['addFromLocalServer'])
		&& (!empty($form['localServerFiles']) || !empty($form['localServerDirectories']))) {
	    /* Add the selected items */
	    $dir = trim($form['localServerPath']);

	    $textFields = array(
			    'title' => (isset($form['set']['title'])) ? 1 : 0,
			    'description' => (isset($form['set']['description'])) ? 1 : 0,
			    'summary' => (isset($form['set']['summary'])) ? 1 : 0,
		    );


	    if (!empty($form['localServerFiles'])) {
		foreach ($form['localServerFiles'] as $fileKey => $unused) {
		    $useSymLink =
			(isset($form['localServerFiles'][$fileKey]['useSymlink'])) ? 1 : 0;

		    $file = array('fileName' => $fileKey, 'useSymLink' => $useSymLink);

		    if (isset($form['localServerFiles'][$fileKey]['selected'])) {
			$ret = $this->addItem($item->getId(), $dir, $file,
				$textFields, $status, $error);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), $error, $status);
			}
		    }
		}
	    }

	    if (!empty($form['localServerDirectories'])) {
		foreach ($form['localServerDirectories'] as $directory => $unused) {
		    /* Skip current or parent directory entries */
		    if ($directory == "." || $directory == "..") {
			continue;
		    }

		    $useSymLink =
			(isset($form['localServerDirectories'][$directory]['useSymlink'])) ? 1 : 0;

		    $newDir = array('dirName' => $directory, 'useSymLink' => $useSymLink);

		    if (isset($form['localServerDirectories'][$directory]['selected'])) {
			$ret = $this->addDirectory($item->getId(), $newDir,
				$textFields, $status, $error);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), $error, $status);
			}
		    }
		}
	    }

	}

	return array(GalleryStatus::success(), $error, $status);
    }

    function addItem($parentId, $dir, $file, $textFields, &$status, &$error) {
	global $gallery;

	$filename = $file['fileName'];

	$useSymlink = $file['useSymLink'];

	/* Build up the file path with the right style of directory separator */
	$filepath = $dir;
	if ($filepath[strlen($filepath)-1] != $this->_dirSep) {
	    $filepath .= $this->_dirSep;
	}

	/* Unescape any special chars in the file name and path */
	$filename = urldecode(GalleryUtilities::htmlEntityDecode($filename));
	$filepath = urldecode(GalleryUtilities::htmlEntityDecode($filepath));
	$filepath .= $filename;

	list ($base, $extension) = GalleryUtilities::getFileNameComponents($filename);
	list ($ret, $mimeType) = GalleryCoreApi::convertExtensionToMime($extension);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	GalleryUtilities::sanitizeInputValues($base);

	list ($ret, $lockIds[]) = GalleryCoreApi::acquireReadLock($parentId);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$title = ($textFields['title']) ? $base : '';
	$summary = ($textFields['summary']) ? $base : '';
	$description = ($textFields['description']) ? $base : '';

	list ($ret, $newItem) = GalleryCoreApi::addItemToAlbum($filepath,
							       $filename,
							       $title,
							       $summary,
							       $description,
							       $mimeType,
							       $parentId,
							       $useSymlink);

	/*
	 * Release the lockIds before checking $ret from addItemToAlbum
	 * and possibly returning
	 */
	GalleryCoreApi::releaseLocks($lockIds);

	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$status['addedFiles'][] = array('fileName' => $filename,
					'id' => $newItem->getId(),
					'warnings' => array());

	return GalleryStatus::success();
    }

    function addDirectory($parentId, $directory, $textFields, &$status, &$error) {
	global $gallery;

	/* Unescape any special chars in the file path */
	$path = urldecode(GalleryUtilities::htmlEntityDecode($directory['dirName']));

	/* Get directory name */
	$dirName = basename($path);

	/* Make sure we have permission to edit this item */
	$ret = GalleryCoreApi::assertHasItemPermission($parentId, 'core.addAlbumItem');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	list ($ret, $lockIds[]) = GalleryCoreApi::acquireReadLock($parentId);
	if ($ret->isError()) {
	   return $ret->wrap(__FILE__, __LINE__);
	}

	/* Create new Album */
	$dirTitle = ($textFields['title']) ? $dirName : null;
	$dirSummary = ($textFields['summary']) ? $dirName : null;
	$dirDescription = ($textFields['description']) ? $dirName : null;
	list ($ret, $instance) =
	       GalleryCoreApi::createAlbum($parentId, $dirName, $dirTitle,
			$dirSummary, $dirDescription, "");
	if ($ret->isError()) {
	    if ($ret->getErrorCode() & ERROR_COLLISION) {
		$error[] = 'form[error][pathComponent][collision]';
		/* HACKHACK - This should cause the upload to abort */
		return GalleryStatus::success();
	    } else {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

	if (!isset($instance)) {
	    return GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__);
	}

	if (empty($error)) {
	    $ret = GalleryCoreApi::addUserPermission($instance->getId(), $instance->getOwnerId(),
		    'core.all', false);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    /* Prepare our status message */
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	    $status['editMessage'] = $module->translate('Album created successfully.');
	}
	GalleryCoreApi::releaseLocks($lockIds);

	$newId = $instance->getId();

	list ($ret, $localServerDirs) =
		GalleryCoreApi::getPluginParameter('module', 'core', 'uploadLocalServer.dirs');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	if (empty($localServerDirs)) {
	    $localServerDirList = array();
	} else {
	    $localServerDirList = split(',', $localServerDirs);
	}

	/* Look into the directory, add anything we find */
	$handle = $this->_platform->opendir($path);

	while (false !== ($fileName = $this->_platform->readdir($handle))) {
	    $gallery->guaranteeTimeLimit(5);

	    if ($fileName == '.' || $fileName == '..' || $fileName == 'CVS') {
		continue;
	    } else {
		$filePath = $path . $this->_dirSep . $fileName;
	    }
	    if ($this->_platform->is_readable($filePath)) {
		if ($this->_platform->is_dir($filePath)) {

		    $filePath = $this->_platform->realpath($filePath);
		    $legal = GalleryUtilities::isPathInList($filePath, $localServerDirList);

		    if ($legal) {
			$newDir = array('dirName' => $filePath,
				'useSymLink' => $directory['useSymLink']);
			$ret = $this->addDirectory($newId, $newDir, $textFields, $status, $error);
			if ($ret->isError()) {
			    return $ret->wrap(__FILE__, __LINE__);
			}
		    }
		} else {
		    $newFile = array('fileName' => $fileName, 'useSymLink' => $directory['useSymLink']);
		    $ret = $this->addItem($newId, $path, $newFile, $textFields, $status, $error);
		    if ($ret->isError()) {
			return $ret->wrap(__FILE__, __LINE__);
		    }
		}
	    }
	}
	$this->_platform->closedir($handle);

	return GalleryStatus::success();
    }


    /**
     * @see ItemAdd:loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	global $gallery;

	if ($form['formName'] != 'ItemAddFromServer') {
	    /* First time around, load the form with item data */
	    $form['localServerPath'] = '';
	    $form['formName'] = 'ItemAddFromServer';
	}

	list ($ret, $localServerDirs) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'uploadLocalServer.dirs');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}
	if (empty($localServerDirs)) {
	    $localServerDirList = array();
	} else {
	    $localServerDirList = split(',', $localServerDirs);
	}

	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
	}

	/* Look up the platform type */
	$platform = $gallery->getPlatform();
	$slash = $platform->getDirectorySeparator();

	if (isset($form['action']['startOver'])) {
	    $form['localServerFiles'] = array();
	} else if (isset($form['action']['findFilesFromLocalServer'])) {
	    /* If we're uploading from the local server, get a file list now */
	    $form['localServerPath'] = trim($form['localServerPath']);
	    $form['localServerPath'] = GalleryUtilities::htmlEntityDecode($form['localServerPath']);
	    $form['localServerPath'] = $platform->realpath($form['localServerPath']);

	    /* Validate the path */
	    $form['localServerFiles'] = array();
	    if (empty($form['localServerPath'])) {
		$form['error']['localServerPath']['missing'] = 1;
	    } else if (!$platform->file_exists($form['localServerPath']) ||
		       !$platform->is_readable($form['localServerPath'])) {
		$form['error']['localServerPath']['invalid'] = 1;
	    } else if (!GalleryUtilities::isPathInList($form['localServerPath'],
						       $localServerDirList)) {
		$form['error']['localServerPath']['illegal'] = 1;
	    } else {
		$mimeTypeItemMap = array();
		$path = $form['localServerPath'];
		if ($platform->is_dir($path)) {
		    $handle = $platform->opendir($path);

		    /* Add path to the recent path list */
		    $session =& $gallery->getSession();
		    $recentPaths = $session->get('core.view.ItemAdd.ItemAddFromServer.recentPaths');
		    $recentPaths[$form['localServerPath']] = 1;
		    $session->put('core.view.ItemAdd.ItemAddFromServer.recentPaths', $recentPaths);

		    while (false !== ($fileName = $platform->readdir($handle))) {
			$gallery->guaranteeTimeLimit(5);

			if ($fileName == '.') {
			    continue;
			}

			if ($fileName == '..') {
			    $filePath = $platform->realpath($path . $slash . '..');
			} else {
			    $filePath = $path . '/' . $fileName;
			}

			if ($platform->is_readable($filePath)) {
			    if ($platform->is_dir($filePath)) {

				$filePath = $platform->realpath($filePath);
				$legal = GalleryUtilities::isPathInList($filePath,
									$localServerDirList);
				$form['localServerFiles'][] =
				    array('type' => 'directory',
					  'fileName' => $fileName,
					  'fileKey' => $filePath,
					  'legal' => $legal);
			    } else {
				list ($ret, $mimeType) = GalleryCoreApi::getMimeType($fileName);
				if ($ret->isError()) {
				    return array($ret->wrap(__FILE__, __LINE__), null, null);
				}
				if (!isset($mimeTypeItemMap[$mimeType])) {
				    list ($ret, $mimeTypeItemMap[$mimeType]['instance']) =
					GalleryCoreApi::newItemByMimeType($mimeType);
				    if ($ret->isError()) {
					return array($ret->wrap(__FILE__, __LINE__), null, null);
				    }

				    $mimeTypeItemMap[$mimeType]['names'] =
					$mimeTypeItemMap[$mimeType]['instance']->itemTypeName();
				}

				$form['localServerFiles'][] =
				    array('type' => 'file',
					  'fileName' => $fileName,
					  'stat' => $platform->stat($filePath),
					  'itemType' => $mimeTypeItemMap[$mimeType]['names'][0],
					  'unknown' => GalleryUtilities::isA(
					      $mimeTypeItemMap[$mimeType]['instance'],
					      'GalleryUnknownItem'),
					  'fileKey' => $fileName);
			    }
			}
		    }
		    $platform->closedir($handle);

		} else if ($platform->is_file($path) && !$platform->is_link($path)) {
		    list ($ret, $mimeType) = GalleryCoreApi::getMimeType($path);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		    if (!isset($mimeTypeItemMap[$mimeType])) {
			list ($ret, $mimeTypeItemMap[$mimeType]['instance']) =
			    GalleryCoreApi::newItemByMimeType($mimeType);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
			$mimeTypeItemMap[$mimeType]['names'] =
			    $mimeTypeItemMap[$mimeType]['instance']->itemTypeName();
		    }

		    $fileName = basename($path);
		    $form['localServerFiles'][] =
			array('fileName' => $fileName,
			      'stat' => $platform->stat($path),
			      'itemType' => $mimeTypeItemMap[$mimeType]['names'][0],
			      'unknown' => GalleryUtilities::isA(
						  $mimeTypeItemMap[$mimeType]['instance'],
						  'GalleryUnknownItem'),
			      'fileKey' => htmlentities($fileName));
		}
	    }
	}

	$ItemAddFromServer = array();

	if (!empty($form['localServerFiles'])) {
	    $accumulator = '';
	    foreach ($platform->splitPath($form['localServerPath']) as $element) {
		$accumulator .= $element;
		$ItemAddFromServer['pathElements'][] = array(
		    'name' => $element, 'path' => $accumulator,
		    'legal' => GalleryUtilities::isPathInList($accumulator, $localServerDirList));
		if (count($ItemAddFromServer['pathElements']) > 1) {
		    $accumulator .= $slash;
		}
	    }
	}

	$ItemAddFromServer['pathSeparator'] = $slash;
	$ItemAddFromServer['localServerDirList'] = $localServerDirList;
	$ItemAddFromServer['localServerFileCount'] =
	    isset($localServerFileCount) ? $localServerFileCount : null;

	$session =& $gallery->getSession();
	$recentPaths = $session->get('core.view.ItemAdd.ItemAddFromServer.recentPaths');
	if (!isset($recentPaths)) {
	    $recentPaths = array();
	}
	$ItemAddFromServer['recentPaths'] = array_keys($recentPaths);

	/*
	 * Set the ItemAdmin form's encoding type specially since legal paths may contain special
	 * characters like ampersands (&)
	 */
	if ($template->hasVariable('ItemAdmin')) {
	    $ItemAdmin =& $template->getVariableByReference('ItemAdmin');
	    $ItemAdmin['enctype'] = 'multipart/form-data';
	} else {
	    $ItemAdmin['enctype'] = 'multipart/form-data';
	    $template->setVariable('ItemAdmin', $ItemAdmin);
	}

	if (!isset($form['set'])) {
	    $form['set'] = array('title' => 1, 'summary' => 0, 'description' => 0);
	}

	/* Do we want to allow symlinks? */
	$ItemAddFromServer['showSymlink'] = $platform->isSymlinkSupported();

	$template->setVariable('ItemAddFromServer', $ItemAddFromServer);


	return array(GalleryStatus::success(),
		     'modules/core/templates/ItemAddFromServer.tpl',
		     'modules_core');
    }

    /**
     * @see ItemAddPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'core');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(GalleryStatus::success(), $module->translate('From Local Server'));
    }
}
?>
