<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

$gItemId = GalleryUtilities::getRequestVariables('gItemId');
if (empty($gItemId)) {
    $gItemId = $gallery->getConfig('core.id.rootAlbum');
}

/* Load the item */
list ($ret, $item) = $gallery->loadEntitiesById($gItemId);
if ($ret->isError()) {
    print $ret->getAsHtml();
    return;
}

/* Update the view count */
$ret = $item->incrementViewCount();
if ($ret->isError()) {
    print $ret->getAsHtml();
    return;
}

/* Find the right layout for this item  */
$layout = $item->getLayout();
if (empty($layout)) {
    $layout = $gallery->getConfig('core.default.layout');
}

/* Pass some data to the layout */
$gallery->setLayoutData('itemId', $gItemId);
$gallery->setLayoutData('item', $item);

/* Pass control to the layout engine */
include($gallery->getConfig('core.directory.layouts') .
	$layout . '/layout.inc');
?>
