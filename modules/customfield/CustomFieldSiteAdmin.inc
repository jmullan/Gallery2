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
 * @version $Revision$ $Date$
 * @package CustomField
 * @author Alan Harder <alan.harder@sun.com>
 */

require_once(dirname(__FILE__) . '/classes/CustomFieldHelper.class');

/**
 * @package CustomField
 * @subpackage UserInterface
 */
class CustomFieldSiteAdminController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	/* Make sure we have adequate permissions */
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$status = array();
	if (isset($form['action']['save'])) {
	    list ($ret, $param) = CustomFieldHelper::loadParameters();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach (array('common', 'album', 'photo') as $set) {
		$newParam[$set] = array();
		foreach ($form[$set]['index'] as $newidx => $oldidx) {
		    $newParam[$set][] = array('field' => $param[$set][$oldidx]['field'],
					      'summary' => isset($form[$set]['summary'][$newidx]),
					      'detail' => isset($form[$set]['detail'][$newidx]),
					      'choices' => $param[$set][$oldidx]['choices']);
		}
	    }
	    $ret = CustomFieldHelper::saveParameters($newParam);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $status['saved'] = 1;
	} else if (isset($form['action']['add'])) {
	    foreach ($form['action']['add'] as $set => $tmp) {}
	    list ($ret, $param) = CustomFieldHelper::loadParameters();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($param as $list) {
		$idx = CustomFieldHelper::findParameter($list, $form[$set]['newField']);
		if ($idx >= 0) {
		    $status['error']['duplicate'] = 1;
		    break;
		}
	    }
	    if (empty($status)) {
		$param[$set][] = array('field' => $form[$set]['newField'],
				       'summary' => false, 'detail' => true, 'choices' => array());
		$ret = CustomFieldHelper::saveParameters(array($set => $param[$set]));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status['added'] = 1;
	    }
	} else if (isset($form['action']['go'])) {
	    foreach ($form['action']['go'] as $set => $tmp) {}
	    list ($ret, $param) = CustomFieldHelper::loadParameters();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $idx = CustomFieldHelper::findParameter($param[$set], $form[$set]['goField']);
	    if ($idx < 0) {
		return array(GalleryStatus::error(ERROR_MISSING_OBJECT, __FILE__, __LINE__), null);
	    }
	    switch ($form[$set]['goAction']) {

	    case 'common':
		// Remove from $set, add to common; no db change
		$param['common'][] = $param[$set][$idx];
		unset($param[$set][$idx]);
		$ret = CustomFieldHelper::saveParameters(
		    array('common' => $param['common'], $set => $param[$set]));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		break;

	    case 'remove':
		// Remove from $set; delete from all items
		unset($param[$set][$idx]);
		$ret = CustomFieldHelper::saveParameters(array($set => $param[$set]));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$ret = CustomFieldHelper::deleteField($form[$set]['goField']);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$status['removed'] = 1;
		break;

	    case 'album':
		// Remove from common, add to album; delete from non-album items
	    case 'photo':
		// Remove from common, add to photo; delete from non-photo items
		$newSet = $form[$set]['goAction'];
		$param[$newSet][] = $param[$set][$idx];
		unset($param[$set][$idx]);
		$ret = CustomFieldHelper::saveParameters(
		    array('common' => $param['common'], $newSet => $param[$newSet]));
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$ret = CustomFieldHelper::deleteField($form[$set]['goField'], $newSet);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		break;

	    default:
		return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null);
	    }
	    if (empty($status)) {
		$status['moved'] = 1;
	    }
	} else if (isset($form['action']['picklist'])) {
	    $choices = array();
	    foreach (array_map('trim', explode("\n", $form['picklist'])) as $tmp) {
		if (!empty($tmp)) {
		    $choices[] = $tmp;
		}
	    }
	    list ($ret, $param) = CustomFieldHelper::loadParameters();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    foreach ($param as $set => $list) {
		$idx = CustomFieldHelper::findParameter($list, $form['pickField']);
		if ($idx >= 0) {
		    $param[$set][$idx]['choices'] = $choices;
		    $ret = CustomFieldHelper::saveParameters(array($set => $param[$set]));
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		    $status['picklist'] = 1;
		    break;
		}
	    }
	} /* else $form['action']['reset'] */

	/* Figure out where to redirect upon success */
	$results['return'] = 1;
	$results['redirect']['view'] = 'core:SiteAdmin';
	$results['redirect']['subView'] = 'customfield:CustomFieldSiteAdmin';
	$results['status'] = $status;
	$results['error'] = array();

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * @package CustomField
 * @subpackage UserInterface
 */
class CustomFieldSiteAdminView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	if ($form['formName'] != 'CustomFieldSiteAdmin') {
	    $form['formName'] = 'CustomFieldSiteAdmin';

	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'customfield');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $form['set'] = array();
	    $form['set'][] = array('key' => 'common', 'name' => $module->translate('Common Fields'));
	    $form['set'][] = array('key' => 'album', 'name' => $module->translate('Album Fields'));
	    $form['set'][] = array('key' => 'photo', 'name' => $module->translate('Photo Fields'));
	    $form['count']['set'] = count($form['set']);

	    list ($ret, $param) = CustomFieldHelper::loadParameters();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    foreach ($param as $set => $list) {
		$form['count'][$set] = count($list);
	    }
	    $form['fields'] = $param;
	}
	$template->setVariable('controller', 'customfield:CustomFieldSiteAdmin');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/customfield/templates/SiteAdmin.tpl'));
    }
}
?>
