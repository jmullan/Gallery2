<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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
/**
 * @version $Revision$ $Date$
 * @package Gallery
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * First pass of initialization.
 *
 * Do the following:
 * - Create and bootstrap the Core
 * - Set all of our paths correctly (modules, themes, layouts, etc)
 * - Check for the existence of key functions (eg, dgettext)
 *
 * Do not attempt anything database related!
 */
function GalleryInitFirstPass() {
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
    $ret = $coreModule->bootstrap();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /*
     * Set our global configuration values.  These are mostly filesystem paths
     * as everything else is configurable via the application itself.
     */

    /* Assign $gallery from global, for ease of use */
    $gallery =& $GLOBALS['gallery'];

    $platform = $gallery->getPlatform();
    $slash = $platform->getDirectorySeparator();
    
    /* Load our local configuration */
    include(dirname(__FILE__) . $slash . 'config.php');

    /* Sanitize the data path */
    $dataBase = $gallery->getConfig('data.gallery.base');
    if ($dataBase{strlen($dataBase)-1} != $slash) {
	$dataBase .= $slash;
	$gallery->setConfig('data.gallery.base', $dataBase);
    }

    /* Set our various data paths */
    $gallery->setConfig('data.gallery.albums', $dataBase . 'albums' . $slash);
    $gallery->setConfig('data.gallery.cache', $dataBase . 'cache'. $slash);
    $gallery->setConfig('data.gallery.tmp', $dataBase . 'tmp' . $slash);
    $gallery->setConfig('data.smarty.base', $dataBase . 'smarty' . $slash);
    $gallery->setConfig('data.smarty.templates_c', $dataBase . 'smarty' . $slash . 'templates_c' . $slash);

    return GalleryStatus::success();
}

/**
 * Initialize our storage subsystem.
 */
function GalleryInitStorage() {
    global $gallery;
    
    /* Init our storage */
    $ret = $gallery->initStorage();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    return GalleryStatus::success();
}

/**
 * Second pass of initialization.
 *
 * Do the following:
 * - Install the core, if necessary
 * - Attach to our session
 * - Load all modules
 */
function GalleryInitSecondPass() {
    global $gallery;

    list ($ret, $coreModule) = GalleryCoreApi::loadPlugin('module', 'core');
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    
    /*
     * During the setup process, we may have bogus database credentials.  So,
     * anything that can be set without using the database should be defined
     * *above* this point.  Once we start trying to load modules we'll expect
     * to error out if our credentials are bad, and we still want all the core
     * functionality (paths, settings, etc) to be set properly.
     */

    /* Let the core module install itself, if necessary */
    list ($ret, $coreWasInstalled) = $coreModule->install();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* Initialize our session */
    $ret = $gallery->initSession();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    $session =& $gallery->getSession();

    /*
     * Set our active user id.  Check to see if we have one in our session.  If
     * not, make us the anonymous user.  If we don't have a session, this will
     * initiate one for us.
     */
    $activeUserId = $session->get('core.id.activeUser');
    if (empty($activeUserId)) {
	/* No active user -- be anonymous */
	list ($ret, $activeUserId) =
		GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}

	$session->put('core.id.activeUser', $activeUserId);
    }
    $gallery->setActiveUserId($activeUserId);

    /* Initialize our translator */
    $ret = $gallery->initTranslator();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    /* Now it's safe to init the core */
    $ret = $coreModule->init();
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }
    
    /* Load the module list */
    list ($ret, $moduleStatus) = GalleryCoreApi::getPluginStatus('module');
    if ($ret->isError()) {
	return $ret->wrap(__FILE__, __LINE__);
    }

    foreach ($moduleStatus as $moduleId => $status) {
	if (empty($status['active'])) {
	    /* If we just installed the core module then try auto configuring this module. */
	    if ($coreWasInstalled) {
		list ($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId, false);
		if ($ret->isError()) {
		    return $ret->wrap(__FILE__, __LINE__);
		}

		if ($module->canBeAutoInstalled()) {
		    list ($ret, $success) = $module->install();
		    if ($ret->isError()) {
			/*
			 * Auto configuration is totally optional.  But even so, it shouldn't fail unless
			 * something catastrophic went wrong.  And even if it does fail, the user can always
			 * try again using the AdminModules view.  So let's just eat the error and not worry
			 * about it.
			 */
			GalleryCoreApi::unloadPlugin('module', $moduleId);
			continue;
		    }
		    
			  
		    list ($ret, $success) = $module->autoConfigure();
		    if ($ret->isError()) {
			/* As above, we don't want to fail even if there is an error */
			GalleryCoreApi::unloadPlugin('module', $moduleId);
			continue;
		    }

		    if ($success) {
			/* Auto config was successful -- activate the module */
			$ret = $module->activate();
			if ($ret->isError()) {
			    /* As above, we don't want to fail even if there is an error */
			    GalleryCoreApi::unloadPlugin('module', $moduleId);
			    continue;
			}

			/* Now initialize it */
			$module->init();
			if ($ret->isError()) {
			    /* As above, we don't want to fail even if there is an error */
			    GalleryCoreApi::unloadPlugin('module', $moduleId);
			    continue;
			}
		    }
		}
	    }
	} else {
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', $moduleId);
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }
	}

    }

    return GalleryStatus::success();
}
?>
