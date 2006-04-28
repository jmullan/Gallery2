<?php
/*
 * $RCSfile: MyPageHelper.class.tpl,v $
 *
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
 * @version $Revision$ $Date$
 * @package {$ucModuleId}
 * @subpackage Helpers
 * @author {$authorFullName}
 */

/**
 * This is a sample page generated by the Gallery 2 module creator.
 *
 * @package {$ucModuleId}
 * @subpackage UserInterface
 *
 */
class MyPageHelper {ldelim}

    /**
     * Load a text value out of the database for a given item id.
     *
     * @param int the item id
     * @return array object GalleryStatus a status code
     *               string the value
     */
    function getItemValue($itemId) {ldelim}
	global $gallery;

	$query = '
        SELECT
          [{$mapName}::itemValue]
        FROM
          [{$mapName}]
        WHERE
          [{$mapName}::itemId] = ?
        ';

	list ($ret, $searchResults) = $gallery->search($query, array($itemId));
	if ($ret) {ldelim}
	    return array($ret->wrap(__FILE__, __LINE__), null);
	{rdelim}

        if ($searchResults->resultCount() != 0) {ldelim}
	    $result = $searchResults->nextResult();
	    $data = $result[0];
	{rdelim} else {ldelim}
	    $data = '';
	{rdelim}

	return array(null, $data);
    {rdelim}
{rdelim}
?>
