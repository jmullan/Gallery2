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
class ItemAddFromWeb extends ItemAddPlugin {

    /**
     * @see ItemAddPlugin::handleRequest
     */
    function handleRequest($form, &$item, $options) {
	global $gallery;

	$status = array();
	$error = array();

	if (isset($form['action']['findFilesFromWebPage'])) {
	    /* Delegate back to the same view */
	} else if (isset($form['action']['addFromWebPage'])) {
	    $platform = $gallery->getPlatform();
	    foreach (array_keys($form['webPageUrls']) as $url) {
		/* Copy the file locally */
		$tmpDir = $gallery->getConfig('data.gallery.tmp');
		$tmpFile = $platform->tempnam($tmpDir, 'add');

		$successfullyCopied = false;
		$url = GalleryUtilities::htmlEntityDecode($url);
		list ($successfullyCopied, $response, $headers) = GalleryCoreApi::fetchWebFile($url, $tmpFile);

		/* Add it */
		if ($successfullyCopied && strpos($response, '404 Not Found') === false) {
		    list ($base, $extension) = GalleryUtilities::getFileNameComponents(basename($url));
		    $mimeType = GalleryCoreApi::convertExtensionToMime($extension);

		    // If we can't get a mime type, try stripping off the query string
		    if ($mimeType == 'application/unknown') {
			if (strstr($url, "?")) {
			    $tmpUrl = preg_replace("/\?.*$/", "", $url);
			    if (!empty($tmpUrl)) {
				$url = $tmpUrl;
				list ($base, $extension) = GalleryUtilities::getFileNameComponents(basename($url));
				$mimeType = GalleryCoreApi::convertExtensionToMime($extension);
			    }
			}
		    }

		    list ($ret, $newItem) = GalleryCoreApi::addItemToAlbum($tmpFile,
									   basename($url),
									   $base,
									   $base,
									   $base,
									   $mimeType,
									   $item->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $warnings = array();
		    foreach ($options as $option) {
			list ($ret, $optionErrors, $optionWarnings) = $option->handleRequestAfterAdd($form, $newItem);
			if ($ret->isError()) {
			    return array($ret->wrap(__FILE__, __LINE__), null, null);
			}
			$error = array_merge($error, $optionErrors);
			$warnings = array_merge($warnings, $optionWarnings);
		    }

		    $status['addedFiles'][] = array('fileName' => $url,
						    'id' => $newItem->getId(),
						    'warnings' => $warnings);
		}
		@$platform->unlink($tmpFile);
	    }
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemAdd:loadTemplate
     */
    function loadTemplate(&$template, &$form, $item) {
	global $gallery;

	if ($form['formName'] != 'ItemAddFromWeb') {
	    /* First time around, load the form with item data */
	    $form['webPage'] = '';
	    $form['formName'] = 'ItemAddFromWeb';
	}

	if (isset($form['action']['findFilesFromWebPage'])) {
	    /*
	     * If we're uploading from a web page, get a file list now.
	     * Download the web page into a temporary file and then parse it
	     */
	    if (empty($form['webPage'])) {
		$form['error']['webPage']['missing'] = 1;
	    } else {
		$baseUrlComponents = parse_url($form['webPage']);
		if (empty($baseUrlComponents['scheme']) || $baseUrlComponents['scheme'] != 'http') {
		    $form['error']['webPage']['invalid'] = 1;
		} else {
		    list ($buffer, $response, $headers, $actualUrl) =
			GalleryCoreApi::fetchWebPage($form['webPage']);
		    if (!isset($buffer) || strpos($response, '404 Not Found') !== false) {
			$form['error']['webPage']['unavailable'] = 1;
		    } else {
			if (isset($actualUrl) && $actualUrl != $form['webPage']) {
			    $form['webPage'] = $actualUrl;
			    $baseUrlComponents = parse_url($form['webPage']);
			}

			/* Add path to the recent path list */
			$session =& $gallery->getSession();
			$recentPaths = $session->get('core.view.ItemAddFromWeb.recentPaths');
			$recentPaths[$form['webPage']] = 1;
			$session->put('core.view.ItemAddFromWeb.recentPaths', $recentPaths);

			if (isset($headers['Content-Type']) &&
			    strncmp($headers['Content-Type'], 'text', 4)) {
			    /*
			     * If the buffer does not contain text(/html) then just offer
			     * to add this url, rather than parsing the contents.
			     */
			    $matches = array( array(), array($form['webPage']), array(), array() );
			} else {
			    /*
			     * Parse the buffer.  We match:
			     *  href="foo bar"    href='foo bar'   href=foo
			     *  src="foo bar"     src='foo bar'    src=foo
			     */
			    preg_match_all('/(?:src|href)=(?:\'(.*?)\'|\"(.*?)\"|([^\'\"\> ]*))/i',
					   $buffer, $matches);
			}

			/* Validate the URLs as best we can */
			$webPageUrlList = array();
			$isSupported = array();
			$seenBefore = array();
			$form['webPageUrls'] = array();
			foreach (array_merge($matches[1], $matches[2], $matches[3]) as $url) {
			    if (empty($url) || isset($seenBefore[$url])) {
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
			    /*
			     * parse_url() isn't guaranteed to be reliable on relative urls, so try to make them
			     * absolute if possible.
			     */
			    if ($url[0] == '/') {
				$tmp = $baseUrlComponents['scheme'] . '://' . $baseUrlComponents['host'];
				if (!empty($baseUrlComponents['port'])) {
				    $tmp .= ':' . $baseUrlComponents['port'];
				}
				$url = $tmp . $url;
			    } else if (!preg_match('/^\w+:/', $url)) {
				$tmp = $baseUrlComponents['scheme'] . '://' . $baseUrlComponents['host'];
				if (!empty($baseUrlComponents['port'])) {
				    $tmp .= ':' . $baseUrlComponents['port'];
				}

				/*
				 * The current url might be one of:
				 *   http://example.com/path/to/file.html
				 *   http://example.com/path/to/
				 *
				 * If it's a directory, it should have a trailing slash at this point.
				 * Either way, we want the base path to be:
				 *   http://example.com/path/to/
				 */
				if (isset($baseUrlComponents['path'])) {
				    $basePath = $baseUrlComponents['path'];
				} else {
				    $basePath = '/';
				}
				if (!preg_match('/\/$/', $basePath)) {
				    $basePath = dirname($basePath);
				    if ($basePath != '/') {
					$basePath .= '/';
				    }
				}
				$tmp .= $basePath;
				$url = $tmp . $url;
			    }

			    $urlComponents = parse_url($url);
			    if (empty($urlComponents['scheme'])) {
				$urlComponents['scheme'] = $baseUrlComponents['scheme'];
			    }

			    if (empty($urlComponents['path'])) {
				continue;
			    }

			    $mimeType = GalleryCoreApi::getMimeType($urlComponents['path']);
			    if ($mimeType == 'application/unknown') {
				/*
				 * Try again with end of the query string -- just in case.  Some sites, like
				 * Google's image search feature puts the file name at the end of the query
				 * string.
				 */
				if (empty($urlComponents['query'])) {
				    continue;
				}

				$mimeType = GalleryCoreApi::getMimeType($urlComponents['query']);
				if ($mimeType == 'application/unknown') {
				    continue;
				}
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

			    if (empty($urlComponents['host'])) {
				$urlComponents['host'] = $baseUrlComponents['host'];
			    }

			    $tmp = $urlComponents['scheme'] . '://' . $urlComponents['host'];
			    if (!empty($urlComponents['port'])) {
				$tmp .= ':' . $urlComponents['port'];
			    }
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
				      'itemType' => $mimeTypeItemMap[$mimeType]['names'][0]);
			}
			$webPageUrlCount = sizeof($form['webPageUrls']);
		    }
		}
	    }
	}

	$ItemAddFromWeb = array();
	$ItemAddFromWeb['webPageUrlCount'] = isset($webPageUrlCount) ? $webPageUrlCount : 0;

	$session =& $gallery->getSession();
	$recentPaths = $session->get('core.view.ItemAdd.ItemAddFromWeb.recentPaths');
	if (!isset($recentPaths)) {
	    $recentPaths = array();
	}
	$ItemAddFromWeb['recentPaths'] = array_keys($recentPaths);

	$template->setVariable('ItemAddFromWeb', $ItemAddFromWeb);
	return array(GalleryStatus::success(),
		     'modules/core/templates/ItemAddFromWeb.tpl',
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

	return array(GalleryStatus::success(), $module->translate('From Web Page'));
    }
}
?>
