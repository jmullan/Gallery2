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

function GalleryInit() {
    /*
     * Specify that when an assertion fails, we terminate right away.
     */
    assert_options(ASSERT_BAIL, 1);

    /*
     * Figure out the Gallery base directory here, from our filename.
     */
    $galleryBase = dirname(__FILE__) . '/';

    /*
     * Load and initialize the core module
     */
    require_once($galleryBase . 'modules/core/module.inc');
    $coreModule = new CoreModule();
    $ret = $coreModule->init();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /*
     * Set our global configuration values.  These are mostly filesystem paths
     * as everything else is configurable via the application itself.
     */

    /* Gallery paths */
    $gallery =& $GLOBALS['gallery'];
    $gallery->setConfig('code.gallery.base', $galleryBase);
    $gallery->setConfig('code.gallery.layouts', $galleryBase . 'layouts/');
    $gallery->setConfig('code.gallery.styles', $galleryBase . 'styles/');
    $gallery->setConfig('code.gallery.modules', $galleryBase . 'modules/');
    $gallery->setConfig('code.gallery.lib', $galleryBase . 'lib/');
    $gallery->setConfig('code.gallery.setup', $galleryBase . 'setup/');

    /* Smarty paths */
    $gallery->setConfig('code.smarty.base', $galleryBase . 'lib/smarty/');
    $gallery->setConfig('config.smarty.templates', $galleryBase . 'templates');

    /* Load our local configuration */
    require_once(dirname(__FILE__) . '/config.php');

    /* Sanitize the data path */
    $dataBase = $gallery->getConfig('data.gallery.base');
    if ($dataBase{strlen($dataBase)-1} != '/') {
	$dataBase .= '/';
	$gallery->setConfig('data.gallery.base', $dataBase);
    }

    /* Set our various data paths */
    $gallery->setConfig('data.gallery.albums', $dataBase . 'albums/');
    $gallery->setConfig('data.gallery.cache', $dataBase . 'cache/');
    $gallery->setConfig('data.gallery.tmp', $dataBase . 'tmp/');
    $gallery->setConfig('data.smarty.base', $dataBase . 'smarty/');
    $gallery->setConfig('data.smarty.templates_c', $dataBase . 'smarty/templates_c/');

    /*
     * During the setup process, we may have bogus database credentials.  So,
     * anything that can be set without using the database should be defined
     * *above* this point.  Once we start trying to load modules we'll expect
     * to error out if our credentials are bad, and we still want all the core
     * functionality (paths, settings, etc) to be set properly.
     */

    /* Load the module list */
    list ($ret, $moduleStatus) = $gallery->getModuleStatus();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    foreach ($moduleStatus as $moduleName => $status) {
	if (empty($status['active'])) {
	    continue;
	}
    
	list ($ret, $module) = $gallery->loadModule($moduleName);
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
    }

    /*
     * Fake being the admin user for now.  When we get in gear, we'll pull
     * this information from the session.
     */
    $gallery->setActiveUserId(4);

    return GalleryStatus::success();
}
?>
