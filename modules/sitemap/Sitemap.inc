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
 * Create an appropriate Google Sitemap for this site.
 * @package Sitemap
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 * @version $Revision$ $Date$
 */
class SitemapView extends GalleryView {

    /**
     * @see GalleryView::isImmediate
     */
    function isImmediate() {
	return true;
    }

    /**
     * @see GalleryView::renderImmediate
     */
    function renderImmediate($status, $error) {
	list ($ret, $rootId) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'id.rootAlbum');
	if ($ret) {
	    return $ret;
	}

	$ret = $this->renderSitemap($rootId);
	if ($ret) {
	    return $ret;
	}
    }

    /**
     * Output a site map rooted at the given id
     *
     * @param int $rootId
     * @return object GalleryStatus a status code
     */
    function renderSitemap($rootId) {
	global $gallery;
	$urlGenerator =& $gallery->getUrlGenerator();
	$phpVm = $gallery->getPhpVm();

	/*
	 * Ideas:
	 *  - Calculate priority by using a percentage of item view count to max view counts
	 */

	/*
	 * Don't use a template for this as we may wind up trying to buffer
	 * way too much data
	 */
	$phpVm->header('Content-type: application/xhtml+xml');
	print '<?xml version=\'1.0\' encoding=\'UTF-8\'?>';
	print "\n";
	print '<urlset xmlns="http://www.google.com/schemas/sitemap/0.84" ';
	print 'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" ';
	print 'xsi:schemaLocation="http://www.google.com/schemas/sitemap/0.84 ';
	print 'http://www.google.com/schemas/sitemap/0.84/sitemap.xsd">';
	print "\n";

	list ($ret, $aclIds) = GalleryCoreApi::fetchAccessListIds(
	    'core.view', $gallery->getActiveUserId());
	if ($ret) {
	    return array($ret, null);
	}
	if (!empty($aclIds)) {
	    $aclMarkers = GalleryUtilities::makeMarkers(count($aclIds));

	    $phpVm = $gallery->getPhpVm();

	    $data = array();
	    $query = sprintf('
	    SELECT
              [GalleryItem::id],
	      [GalleryEntity::modificationTimestamp],
              ((%s - [GalleryEntity::creationTimestamp]) /
               [GalleryEntity::serialNumber]) as SecondsPerChange
	    FROM
	      [GalleryItem], [GalleryEntity], [GalleryItemAttributesMap],
              [GalleryAccessSubscriberMap]
	    WHERE
              [GalleryItem::id] = [GalleryEntity::id]
              AND
              [GalleryItem::id] = [GalleryItemAttributesMap::itemId]
              AND
	      ([GalleryItem::id] = ?
               OR
               [GalleryItemAttributesMap::parentSequence] LIKE ?
               OR
	       [GalleryItemAttributesMap::parentSequence] LIKE ?)
	      AND
	      [GalleryItem::id] = [GalleryAccessSubscriberMap::itemId]
	      AND
	      [GalleryAccessSubscriberMap::accessListId] IN (%s)
            ORDER BY [GalleryEntity::modificationTimestamp] ASC
	    ', $phpVm->time(), $aclMarkers);
	    $data[] = $rootId;
	    $data[] = $rootId . '/%';
	    $data[] = '%/' . $rootId . '/%';
	    $data = array_merge($data, $aclIds);

	    list ($ret, $searchResults) = $gallery->search($query, $data);
	    if ($ret) {
		return $ret;
	    }

	    $frequencyTable = array(
		3600 => 'hourly',
		24 * 3600 => 'daily',
		7 * 24 * 3600 => 'weekly',
		30 * 24 * 3600 => 'monthly',
		365 * 24 * 3600 => 'yearly');
	    while ($result = $searchResults->nextResult()) {
		$loc = $urlGenerator->generateUrl(
		    array('view' => 'core.ShowItem', 'itemId' => $result[0]),
		    array('forceSessionId' => false, 'forceFullUrl' => true));
		$lastmod = gmstrftime('%Y-%m-%dT%H:%M:%S+00:00', $result[1]);
		$changefreq = 'never';
		foreach ($frequencyTable as $comparison => $value) {
		    if ($result[2] <= $comparison) {
			$changefreq = $value;
			break;
		    }
		}
 		printf('<url><loc>%s</loc><lastmod>%s</lastmod><changefreq>%s</changefreq></url>',
 		       $loc, $lastmod, $changefreq);
		print "\n";
	    }
	}
	print '</urlset>';

	return null;
    }
}
?>
