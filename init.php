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

/*
 * Specify that when an assertion fails, we terminate right away.
 */
assert_options(ASSERT_BAIL, 1);

/*
 * Figure out the Gallery base directory here, from our filename.
 */
$gallerybase = dirname(__FILE__) . '/';

/*
 * Load all the core Gallery classes
 */
require_once($gallerybase . 'include/classes/GalleryUtilities.class');
require_once($gallerybase . 'include/classes/GalleryStatus.class');
require_once($gallerybase . 'include/classes/GalleryPersistent.class');
require_once($gallerybase . 'include/classes/GalleryEntity.class');
require_once($gallerybase . 'include/classes/GalleryChildEntity.class');
require_once($gallerybase . 'include/classes/GalleryFileSystemEntity.class');
require_once($gallerybase . 'include/classes/GalleryItem.class');
require_once($gallerybase . 'include/classes/GalleryAlbumItem.class');
require_once($gallerybase . 'include/classes/GalleryDataContainer.class');
require_once($gallerybase . 'include/classes/GalleryDerivative.class');
require_once($gallerybase . 'include/classes/GalleryComment.class');
require_once($gallerybase . 'include/classes/GalleryDataItem.class');
require_once($gallerybase . 'include/classes/Gallery.class');
require_once($gallerybase . 'include/classes/GalleryGraphics.class');
require_once($gallerybase . 'include/classes/GalleryGraphicsFactory.class');
require_once($gallerybase . 'include/classes/GalleryItemFactory.class');
require_once($gallerybase . 'include/classes/GalleryLock.class');
require_once($gallerybase . 'include/classes/GalleryStorage.class');
require_once($gallerybase . 'include/classes/GalleryStorageFactory.class');
require_once($gallerybase . 'include/classes/GalleryUser.class');
require_once($gallerybase . 'include/classes/GalleryGroup.class');
require_once($gallerybase . 'include/classes/GalleryImageContainer.class');
require_once($gallerybase . 'include/classes/GalleryDerivativeImage.class');
require_once($gallerybase . 'include/classes/GalleryMovieContainer.class');
require_once($gallerybase . 'include/classes/GalleryMovieItem.class');
require_once($gallerybase . 'include/classes/GalleryPhotoItem.class');
require_once($gallerybase . 'include/classes/GalleryUnknownContainer.class');
require_once($gallerybase . 'include/classes/GalleryUnknownItem.class');
require_once($gallerybase . 'include/classes/GalleryPlatform.class');
require_once($gallerybase . 'include/classes/GalleryPlatformFactory.class');
require_once($gallerybase . 'include/classes/GallerySearchResult.class');
require_once($gallerybase . 'include/classes/GalleryItemPropertiesMap.class');
require_once($gallerybase . 'include/classes/GalleryUserGroupMap.class');
require_once($gallerybase . 'include/classes/GalleryPermissionMap.class');
require_once($gallerybase . 'include/classes/GalleryViewCountMap.class');

/*
 * Set up our Gallery global.  It's important to use a reference here because
 * the constructor registers a shutdown function and ties it to the instance
 * in the constructor.  This global should be the only one that Gallery
 * requires.  Everything else should be inside it so that we do not pollute the
 * namespace (important when we're embedded inside another application).
 */
$gallery =& new Gallery();
$gallery->setConfig('core.directory.base', $gallerybase);
$gallery->setConfig('core.directory.layouts', $gallerybase . 'layouts/');
$gallery->setConfig('core.directory.modules', $gallerybase . 'modules/');

/* Configure the Platform */
if (substr(PHP_OS, 0, 3) == 'WIN') {
    $gallery->setConfig('platform.type', 'windows');
} else {
    $gallery->setConfig('platform.type', 'unix');
}

/* Load our local configuration */
require_once($gallerybase . 'config.php');
?>
