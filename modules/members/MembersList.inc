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
 * @package Members
 * @subpackage UserInterface
 * @author Robert Balousek <rbalousek@hotmail.com>
 */

/**
 * This view will allow users to view the member list
 *
 * @package Members
 * @subpackage UserInterface
 */
class MembersListView extends GalleryView {

    /**
     * @see GalleryView::loadTemplate
     */
    function loadTemplate(&$template, &$form) {
	global $gallery;
	
	if ($form['formName'] != 'MembersList') {
	    /* Set some defaults */
	    $form['text']['userName'] = '';
	    $form['text']['userId'] = '';
	    $form['formName'] = 'MembersList';
	    $MembersList = array();
	}
	
	if (!isset($form['list']['page']) || $form['list']['page'] < 1) {
	    $form['list']['page'] = 1;
	}
	
	/* Fetch the user count every time we reload */
	list ($ret, $totalUserCount) = GalleryCoreApi::fetchUserCount();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$form['list']['count'] = $totalUserCount;
	$form['list']['pageSize'] = $totalUserCount > 30 ? 30 : $totalUserCount + 2;
	
	/* Figure out our max pages, make sure our current page fits in it */
	$form['list']['maxPages'] = ceil($form['list']['count'] / $form['list']['pageSize']);
	if ($form['list']['page'] > $form['list']['maxPages']) {
            $form['list']['page'] = $form['list']['maxPages'];
	}
	
	/* Calculate the next/back pages */
	$form['list']['nextPage'] = min($form['list']['page']+1, $form['list']['maxPages']);
	$form['list']['backPage'] = max(1, $form['list']['page']-1);
        $form['list']['startingUser'] = ($form['list']['page'] - 1) * $form['list']['pageSize'];
	
	list ($ret, $groupId) =
            GalleryCoreApi::getPluginParameter('module', 'core', 'id.allUserGroup');
	if ($ret->isError()) {
            return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	list ($ret, $userNames) = GalleryCoreApi::fetchUsersForGroup($groupId,
								     $form['list']['pageSize'],
								     $form['list']['startingUser']);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $users) = GalleryCoreApi::loadEntitiesById(array_keys($userNames));
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	$MembersList['users'] = array();
	foreach ($users as $user) {
	    $MembersList['users'][$user->getId()] = $user->getMemberData();
	}
	
	$form['list']['totalUserCount'] = $totalUserCount;

	/* Render the HTML body */
	$template->setVariable('MembersList', $MembersList);

	list ($ret, $navigationView) = GalleryView::loadView('core:Navigation');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	list ($ret, $ignored) = $navigationView->loadTemplate($template, $form);
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	
	return array(GalleryStatus::success(),
		     array('head' => 'modules/members/templates/MembersListHead.tpl',
			   'body' => 'modules/members/templates/MembersList.tpl'));
    }
}
?>
