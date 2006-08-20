<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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

/**
 * @package KeyAlbum
 * @author Alan Harder <alan.harder@sun.com>
 * @version $Revision$ $Date$
 */
class KeyAlbumCallbacks {

    function callback($params, &$smarty, $callback, $userId) {

	switch ($callback) {
	case 'LoadKeywords':
	    $onlyPublic = $params['onlyPublic'];
	    $param = 'allKeywords' . ($onlyPublic ? '.public' : '');
	    list ($ret, $lastUpdated) =
		GalleryCoreApi::getPluginParameter('module', 'keyalbum', $param . '.time');
	    if ($ret) {
		return $ret;
	    }
	    if (time() - $lastUpdated > 3600 * 24) {
		$ret = KeyAlbumCallbacks::_findAllKeywords($onlyPublic);
		if ($ret) {
		    return $ret;
		}
	    }
	    list ($ret, $keywords) =
		GalleryCoreApi::getPluginParameter('module', 'keyalbum', $param);
	    if ($ret) {
		return $ret;
	    }

	    $block =& $smarty->_tpl_vars['block'];
	    $block['keyalbum']['keywords'] = unserialize($keywords);

	    return null;
	}

	return GalleryCoreApi::error(ERROR_BAD_PARAMETER);
    }

    /**
     * Get all unique keywords and store in a module parameter.
     * @param boolean true to only get keywords from public items
     * @return object GalleryStatus a status code
     * @static
     */
    function _findAllKeywords($onlyPublic) {
	global $gallery;

	$query = '
	SELECT DISTINCT
	  [GalleryItem::keywords]
	FROM
	  [GalleryItem]
	';
	$aclIds = array();
	if ($onlyPublic) {
	    list ($ret, $guestId) = GalleryCoreApi::getAnonymousUserId();
	    if ($ret) {
		return $ret;
	    }
	    list ($ret, $aclIds) = GalleryCoreApi::fetchAccessListIds('core.view', $guestId);
	    if ($ret) {
		return $ret;
	    }
	    if (empty($aclIds)) {
		$query = '';
	    } else {
		$query .= ' INNER JOIN [GalleryAccessSubscriberMap]
		  ON [GalleryItem::id] = [GalleryAccessSubscriberMap::itemId]
		WHERE
		  [GalleryAccessSubscriberMap::accessListId] IN ('
		  . GalleryUtilities::makeMarkers(count($aclIds)) . ')
		';
	    }
	}
	list ($ret, $searchResults) = $gallery->search($query, $aclIds);
	if ($ret) {
	    return $ret;
	}
	while ($result = $searchResults->nextResult()) {
	    if ($result[0]) {
		foreach (preg_split('/[\s,;]+/', $result[0]) as $keyword) {
		    $keywords[$keyword] = true;
		}
	    }
	}
	$keywords = array_keys($keywords);
	sort($keywords);

	$param = 'allKeywords' . ($onlyPublic ? '.public' : '');
	$ret = GalleryCoreApi::setPluginParameter('module', 'keyalbum',
						  $param, serialize($keywords));
	if ($ret) {
	    return $ret;
	}
	$ret = GalleryCoreApi::setPluginParameter('module', 'keyalbum', $param . '.time', time());
	if ($ret) {
	    return $ret;
	}
	return null;
    }
}
?>
