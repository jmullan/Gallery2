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

    $platform = $gallery->getPlatform();
    $slash = $platform->getDirectorySeparator();
    
    $gallery->setConfig('code.gallery.base', $galleryBase);
    $gallery->setConfig('code.gallery.layouts',
			$galleryBase . 'layouts' . $slash);
    $gallery->setConfig('code.gallery.themes',
			$galleryBase . 'themes' . $slash);
    $gallery->setConfig('code.gallery.modules',
			$galleryBase . 'modules' . $slash);
    $gallery->setConfig('code.gallery.lib',
			$galleryBase . 'lib' . $slash);
    $gallery->setConfig('code.gallery.setup',
			$galleryBase . 'setup' . $slash);

    /* Smarty paths */
    $gallery->setConfig('code.smarty.base',
			$galleryBase . 'lib' . $slash . 'smarty' . $slash);

    /* Load our local configuration */
    require_once(dirname(__FILE__) . $slash . 'config.php');

    /* Sanitize the data path */
    $dataBase = $gallery->getConfig('data.gallery.base');
    if ($dataBase{strlen($dataBase)-1} != $slash) {
	$dataBase .= $slash;
	$gallery->setConfig('data.gallery.base', $dataBase);
    }

    /* Set our various data paths */
    $gallery->setConfig('data.gallery.albums',
			$dataBase . 'albums' . $slash);
    $gallery->setConfig('data.gallery.cache',
			$dataBase . 'cache'. $slash);
    $gallery->setConfig('data.gallery.tmp',
			$dataBase . 'tmp' . $slash);
    $gallery->setConfig('data.smarty.base',
			$dataBase . 'smarty' . $slash);
    $gallery->setConfig('data.smarty.templates_c',
			$dataBase . 'smarty' . $slash . 'templates_c' . $slash);

    /* Check for the existance of various functions that we care about */
    foreach (array('dgettext', 'dngettext')
	     as $functionName) {
	$key = 'function.exists.' . $functionName;
	$gallery->setConfig($key, function_exists($functionName) ? 1 : 0);
    }

    /*
     * During the setup process, we may have bogus database credentials.  So,
     * anything that can be set without using the database should be defined
     * *above* this point.  Once we start trying to load modules we'll expect
     * to error out if our credentials are bad, and we still want all the core
     * functionality (paths, settings, etc) to be set properly.
     */

    /* Let the core module install itself, if necessary */
    $ret = $coreModule->install();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* Load the module list */
    GalleryProfiler::start('GalleryInit.load-modules');
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
    GalleryProfiler::stop('GalleryInit.load-modules');

    return GalleryStatus::success();
}

/*
 * This function serves as a glue layer between Smarty and Gallery.  Smarty
 * expects callbacks to be functions, whereas Gallery really wants everything
 * to be OO with classes and methods.  Gallery routes all Smarty callbacks to
 * this function, which figures out which template adapter method to call.
 *
 * To add new Smarty callbacks to Gallery, you must do the following:
 * - add the function definition to the GalleryAdapterTemplate API
 * - register a new block or function callback in Gallery::getSmarty()
 * - add a new case to the switch statement here.
 */
function galleryTemplateCallback($params, $content) {
    global $gallery;

    /*
     * For function callbacks, the second parameter is a reference to Smarty.
     * For blocks, the second parameter is the content that goes inside the
     * block, and the third parameter is the Smarty reference.
     *
     * We don't use the Smarty reference, so we'll assume that the second
     * parameter is the content, but only use it when we're dealing with a
     * block tag (like galleryForm).
     *
     * One idiosyncracy: block functions are called twice, once at the start
     * and once at the end.  The first time around, the $content parameter is
     * null.  To simplify our system, we're going to ignore the first call.
     * So, if $content is null, we'll just return.  Note that if this is a
     * function call, $content actually contains a smarty instance so it won't
     * be empty.
     */
    $content = func_get_arg(1);
    if (is_object($content)) {
	$content = false;
    } else {
	if ($content === null) {
	    /* Ignore the first of a two part call */
	    return;
	}
    }

    $templateAdapter = $gallery->getTemplateAdapter();
    $function = $params['__function'];
    unset($params['__function']);

    print $templateAdapter->callMethod($function, $params, $content);
}
?>
