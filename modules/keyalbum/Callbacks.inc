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
	    $onlyPublic = (bool)$params['onlyPublic'];
	    $sizeLimit = (int)$params['sizeLimit'];
	    $param = 'allKeywords' . ($onlyPublic ? '.public' : '')
		. ($sizeLimit ? '.' . $sizeLimit : '');
	    list ($ret, $lastUpdated) =
		GalleryCoreApi::getPluginParameter('module', 'keyalbum', $param . '.time');
	    if ($ret) {
		return $ret;
	    }
	    /* Cache keyword list for one day */
	    if (time() - $lastUpdated > 3600 * 24) {
		$ret = KeyAlbumCallbacks::_findAllKeywords($param, $onlyPublic, $sizeLimit,
							   $params['maxCloudFontEnlargement']);
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
	    $block['keyalbum']['keywords'] = !empty($keywords) ? unserialize($keywords) : array();

	    return null;

	case 'SplitKeywords':
	    list ($ret, $split) = GalleryCoreApi::getPluginParameter('module', 'keyalbum', 'split');
	    if ($ret) {
		return $ret;
	    }
	    $split = '/[' . $split . ']+/';
	    $keywords = array();
	    foreach (preg_split($split, $params['keywords']) as $keyword) {
		$keywords[] = trim($keyword);
	    }

	    $block =& $smarty->_tpl_vars['block'];
	    $block['keyalbum']['keywords'] = $keywords;

	    return null;
	}

	return GalleryCoreApi::error(ERROR_BAD_PARAMETER);
    }

    /**
     * Get all unique keywords and store in a module parameter.
     * @param string $param save result to this plugin paramter
     * @param boolean $onlyPublic true to only get keywords from public items
     * @param int $sizeLimit max number of keywords (least common are dropped; 0 = no limit)
     * @param int $maxWeight max value for font enlargement in keyword cloud
     * @return object GalleryStatus a status code
     * @static
     */
    function _findAllKeywords($param, $onlyPublic, $sizeLimit, $maxWeight) {
	global $gallery;

	$query = '
	SELECT DISTINCT
	  [GalleryItem::keywords]
	FROM
	  [GalleryItem]
	';
	$keywords = $aclIds = array();
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
	list ($ret, $split) = GalleryCoreApi::getPluginParameter('module', 'keyalbum', 'split');
	if ($ret) {
	    return $ret;
	}
	$split = '/[' . $split . ']+/';
	$maxCount = 1;
	while ($result = $searchResults->nextResult()) {
	    if ($result[0]) {
		foreach (preg_split($split, $result[0]) as $keyword) {
		    $keyword = trim($keyword);
		    if (!isset($keywords[$keyword])) {
			$keywords[$keyword] = array('name' => $keyword, 'count' => 1);
		    } else if (++$keywords[$keyword]['count'] > $maxCount) {
			$maxCount = $keywords[$keyword]['count'];
		    }
		}
	    }
	}
	if ($sizeLimit > 0 && count($keywords) > $sizeLimit) {
	    /* Sort by frequency and drop least common */
	    uasort($keywords, create_function('$a,$b', '$c = $a[\'count\']; $d = $b[\'count\']; '
						    . 'return $c > $d ? -1 : ($c == $d ? 0 : 1);'));

	    array_splice($keywords, $sizeLimit);
	}
	ksort($keywords);
	$keywords = array_values($keywords);

	/* Compute weights, used for font enlargement in keyword cloud */
	foreach ($keywords as $i => $keyword) {
	    $keywords[$i]['weight'] = round($keyword['count'] / $maxCount * $maxWeight);
	    unset($keywords[$i]['count']);
	}

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
