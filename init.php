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
$galleryBase = dirname(__FILE__) . '/';

/*
 * Load and initialize the core module
 */
require_once($galleryBase . 'modules/core/module.inc');
$coreModule = new CoreModule();
$ret = $coreModule->init();
/* XXX: this is unclean; we should handle this better. */
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

/*
 * Extract the global gallery instance from the core module.  This bends the OO
 * model slightly, but it's a necessity to bootstrap ourselves up.
 */
$gallery =& $coreModule->getGallery();

/*
 * Set our global configuration values.  These are mostly (entirely?) code path
 * locations as everything else is configurable via the application itself.
 */

/* Gallery paths */
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

/* Load all active modules */
list ($ret, $moduleStatus) = $gallery->getModuleStatus();
if ($ret->isError()) {
    $ret = $ret->wrap(__FILE__, __LINE__);
    print $ret->getAsHtml();
    return;
}

foreach ($moduleStatus as $moduleName => $status) {
    if (empty($status['active'])) {
	continue;
    }
    
    list ($ret, $module) = $gallery->loadModule($moduleName);
    /* XXX: this is unclean; we should handle this better. */
    if ($ret->isError()) {
	$ret = $ret->wrap(__FILE__, __LINE__);
	print $ret->getAsHtml();
	return;
    }
}

/*
 * Fake being the admin user for now.  When we get in gear, we'll pull
 * this information from the session.
 */
$gallery->setActiveUserId(4);
?>
