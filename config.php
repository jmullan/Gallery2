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

/* Turn on debug mode */
$gallery->setDebug('buffered');

/*
 * Set our configuration.  These values will be set by the config wizard,
 * eventually.
 */

/*
 * Start with a path to a webserver-writeable directory for gallery data
 * For now, base it off the base Gallery location
 */
$galleryBase = $gallery->getConfig('core.directory.base');
$galleryData = $galleryBase . '../gallerydata/';

$gallery->setConfig('core.directory.data', $galleryData);
$gallery->setConfig('core.directory.temp', $galleryData . 'temp');
$gallery->setConfig('core.directory.cache', $galleryData . 'cache');
$gallery->setConfig('core.directory.albums', $galleryData . 'albums');
$gallery->setConfig('core.permissions.directory', 0777);
$gallery->setConfig('core.permissions.file', 0777);
$gallery->setConfig('core.expectedStatus', 0);
$gallery->setConfig('core.default.orderBy', 'id');
$gallery->setConfig('core.default.orderDirection', 1);
$gallery->setConfig('core.default.layout', 'basic');

/* Configure Smarty */
$gallery->setConfig('smarty.directory.base', $galleryBase . 'include/smarty/');
$gallery->setConfig('smarty.directory.config', $galleryBase . 'smarty/config');
$gallery->setConfig('smarty.directory.templates', $galleryBase . 'templates');

$smartyData = $galleryData . 'smarty/';
$gallery->setConfig('smarty.directory.data', $smartyData);
$gallery->setConfig('smarty.directory.templates_c', $smartyData . 'templates_c');
$gallery->setConfig('smarty.directory.cache', $smartyData . 'cache');

/*
 * XXX: If we have used the ReInitializeGallery test case, then
 * id 1 is the anonymous user
 * id 2 is the all user group
 * id 3 is the admin user group
 * id 4 is the root album id
 * id 5 is an admin user
 *
 * Under normal circumstances, the config wizard will create these as
 * necessary and then either hardcode or let you choose the right id
 * as appropriate.
 */
$gallery->setConfig('core.id.anonymousUser', 1);
$gallery->setConfig('core.id.allUserGroup', 2);
$gallery->setConfig('core.id.adminGroup', 3);
$gallery->setConfig('core.id.rootAlbum', 5);

/*
 * Fake being the admin user for now.  When we get in gear, we'll pull
 * this information from the session.
 */
$gallery->setActiveUserId(4);

/* Configure the Storage sub-system */
$dbConfig['type'] = 'mysql';
$dbConfig['hostname'] = 'localhost';
$dbConfig['database'] = 'g2dev';
$dbConfig['username'] = 'g2dev';
$dbConfig['password'] = 'g2dev';
$dbConfig['tablePrefix'] = 'g2_';
$dbConfig['columnPrefix'] = 'g_';
$gallery->setConfig('core.storage.config', $dbConfig);
$gallery->setConfig('core.storage.type', 'database');

/* storage capabilities are unused right now */
// $dbConfig['capabilities']['fullTextIndexes'] = 1;  // MySQL 3.23.23+
// $dbConfig['capabilities']['blobIndexes'] = 1;      // MySQL 3.23.2+

/* Configure the Graphics toolkit */
$gallery->setConfig('core.graphics.type', 'netpbm');
$toolkitConfig['path'] = '/usr/local/bin';
$toolkitConfig['fileTypes'] = array('jpg', 'jpeg', 'gif', 'png');
$toolkitConfig['jpegImageQuality'] = 75;
$toolkitConfig['expectedStatus'] = 0;
$toolkitConfig['functions'] = (IMAGE_FUNCTION_RESIZE |
			       IMAGE_FUNCTION_ROTATE |
			       IMAGE_FUNCTION_SCALE |
			       IMAGE_FUNCTION_CROP);
$gallery->setConfig('core.graphics.config', $toolkitConfig);
?>
