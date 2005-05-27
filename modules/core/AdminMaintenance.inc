<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
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
 * @package GalleryCore
 * @subpackage UserInterface
 * @author Bharat Mediratta <bharat@menalto.com>
 */

GalleryCoreApi::relativeRequireOnce('modules/core/classes/helpers/MaintenanceHelper_simple.class');

/**
 * This controller will send the user to the chosen subView in the AdminMaintenance
 *
 * @package GalleryCore
 * @subpackage UserInterface
 *
 */
class AdminMaintenanceController extends GalleryController {

    /**
     * @see GalleryController::handleRequest
     */
    function handleRequest($form) {
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$results = array();
	$status = array();
	$error = array();

	if (isset($form['action']['runTask'])) {
	    $taskId = GalleryUtilities::getRequestVariables('taskId');

	    list ($ret, $tasks) = MaintenanceHelper_simple::fetchTasks();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    list ($ret, $immediateView) = $this->getImmediateStatusView();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (isset($tasks[$taskId])) {
		list ($ret, $success, $details) = $tasks[$taskId]->run($immediateView);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$ret = MaintenanceHelper_simple::addRun($taskId, time(), $success, $details);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}

		$redirect['view'] = 'core.SiteAdmin';
		$redirect['subView'] = 'core.AdminMaintenance';
		$status['run'] = array('taskId' => $taskId, 'success' => $success);
	    }
	}

	if (!empty($redirect)) {
	    $results['redirect'] = $redirect;
	    if (isset($immediateView->_template)) {  /* check if $immediateView was used */
		$results['sendLateRedirect'] = $immediateView;
	    }
	} else {
	    $results['delegate']['view'] = 'core.SiteAdmin';
	    $results['delegate']['subView'] = 'core.AdminMaintenance';
	}

	$results['status'] = $status;
	$results['error'] = $error;

	return array(GalleryStatus::success(), $results);
    }

    /**
     * @see GalleryController::canUseImmediateView
     */
    function canUseImmediateView() {
	return true;
    }
}

/**
 * This view will show available options to administer the groups of Gallery
 *
 * @package GalleryCore
 * @subpackage UserInterface
 */
class AdminMaintenanceView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	$ret = GalleryCoreApi::assertUserIsSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Load some standard form parameters */
	if ($form['formName'] != 'AdminMaintenance') {
	    $form['formName'] = 'AdminMaintenance';
	}

	list ($ret, $tasks) = MaintenanceHelper_simple::fetchTasks();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	$AdminMaintenance = array();
	foreach ($tasks as $taskId => $task) {
	    list ($ret, $info) = MaintenanceHelper_simple::fetchLastRun($taskId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    $AdminMaintenance['tasks'][$taskId] = $task->getInfo();
	    if (isset($info)) {
		$AdminMaintenance['tasks'][$taskId]['runId'] = $info['runId'];
		$AdminMaintenance['tasks'][$taskId]['timestamp'] = $info['timestamp'];
		$AdminMaintenance['tasks'][$taskId]['success'] = $info['success'];
		$AdminMaintenance['tasks'][$taskId]['details'] = $info['details'];
	    } else {
		$AdminMaintenance['tasks'][$taskId]['runId'] = null;
		$AdminMaintenance['tasks'][$taskId]['timestamp'] = null;
		$AdminMaintenance['tasks'][$taskId]['success'] = null;
		$AdminMaintenance['tasks'][$taskId]['details'] = null;
	    }
	}

	$template->setVariable('AdminMaintenance', $AdminMaintenance);
	$template->setVariable('controller', 'core.AdminMaintenance');

	$template->javascript('lib/javascript/BlockToggle.js');
	return array(GalleryStatus::success(),
		     array('body' => 'modules/core/templates/AdminMaintenance.tpl'));
    }
}

class MaintenanceTask {

    /**
     * Return internationalized text about this task
     * @return array('title' => ..., 'description' => ..., 'l10Domain' => ...)
     */
    function getInfo() {
	return array();
    }

    /**
     * Execute the task
     * @param object GalleryImmediateStatusView to show task progress
     * @return array object GalleryStatus a status code
     *               boolean success or failure
     *               array string output text
     */
    function run(&$immediateView) {
	return array(GalleryStatus::error(ERROR_UNIMPLEMENTED, __FILE__, __LINE__), null, null);
    }
}
?>
