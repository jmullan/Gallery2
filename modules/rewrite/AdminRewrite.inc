<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2004 Bharat Mediratta
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
 * @package Rewrite
 * @version $Revision$ $Date$
 * @author Douglas Cau <douglas@cau.se>
 */

/**
 * Required class
 */
require_once(dirname(__FILE__) . '/classes/RewriteHelper.class');

/**
 * @package Rewrite
 * @subpackage UserInterface
 */
class AdminRewriteController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest(&$form) {
	global $gallery;
	$platform = $gallery->getPlatform();
	
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$status = array();
	$error = array();
	
	if (isset($form['action']['save'])) {
	    /* Save settings */
	    list ($ret, $rewriteLocation) =
		    GalleryCoreApi::getPluginParameter('module', 'rewrite', 'rewriteLocation');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    
	    $dupe = array();
	    
	    foreach ($form['prefix'] as $view => $prefix) {
		if (strlen($prefix)) {
		    $form['prefix'][$view] = $platform->legalizePathComponent($prefix);

		    if ($platform->is_dir(dirname(dirname(dirname(__FILE__))) . '/' .
			    $form['prefix'][$view]) || isset($dupe[$form['prefix'][$view]])) {
			$error[] = 'form[error][badPrefix]';
			break;
		    }
		    
		    $dupe[$form['prefix'][$view]] = 1;
		} else {
		    unset($form['prefix'][$view]);
		}
	    }
	    
	    if (empty($error)) {
		$ret = GalleryCoreApi::setPluginParameter('module', 'rewrite', 'prefixMap',
			serialize($form['prefix']));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    
		$redirect['view'] = 'core:SiteAdmin';
		$redirect['subView'] = 'rewrite:AdminRewrite';
		$status['saved'] = 1;
	    }
	} else if (isset($form['action']['reset'])) {
	    $ret = GalleryCoreApi::setPluginParameter('module', 'rewrite', 'prefixMap',
		    serialize(array()));
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'rewrite:AdminRewrite';
	    $status['saved'] = 1;
	} else if (isset($form['action']['cancel'])) {
	    $redirect['view'] = 'core:SiteAdmin';
	    $redirect['subView'] = 'rewrite:AdminRewrite';
	}
	
	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	} else {
	    $results['delegate']['view'] = 'core:SiteAdmin';
	    $results['delegate']['subView'] = 'rewrite:AdminRewrite';
	}
	$results['status'] = $status;
	$results['error'] = $error;
	
	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package Rewrite
 * @subpackage UserInterface
 */
class AdminRewriteView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
    	global $gallery;
    	$urlGenerator = $gallery->getUrlGenerator();
    	$AdminRewrite = array();
	
	/* Settings */
	if ($form['formName'] != 'AdminRewrite') {
	    $form['formName'] = 'AdminRewrite';
	    list ($ret, $override) = RewriteHelper::getPrefixMap();
	    if ($ret->isError()) {
		return array($ret-wrap(__FILE__, __LINE__), null);
	    }
	    
	    foreach ($urlGenerator->_viewPrefixRegistry['reverse'] as $view => $prefix) {
		$form['prefix'][$view] = isset($override[$view]) ? $override[$view] : $prefix;
	    }
	    
	    ksort($form['prefix'], SORT_STRING);
	}
	
	/* Current prefixes in the urlGenerator */
	$AdminRewrite['prefix'] = array();
	foreach ($urlGenerator->_viewPrefixRegistry['reverse'] as $view => $prefix) {
	    $AdminRewrite['prefix'][$view] = isset($override[$view]) ? $override[$view] : $prefix;
	}
	
	/* Warn if ShortUrls is turned on */
	list ($ret, $useShortUrls) =
		GalleryCoreApi::getPluginParameter('module', 'core', 'misc.useShortUrls');
	if ($ret->isError()) {
	    return $ret->wrap(__FILE__, __LINE__);
	}
	if ($useShortUrls == 'true') {
	    $form['error']['shortUrls'] = 1;
	}

	$template->setVariable('AdminRewrite', $AdminRewrite);
	$template->setVariable('controller', 'rewrite:AdminRewrite');

	return array(GalleryStatus::success(),
		array('body' => 'modules/rewrite/templates/AdminRewrite.tpl'));
    }
}

?>
