<?php
/*
 * $RCSfile
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
 * @package Debug
 * @subpackage UserInterface
 * @author Ernesto Baschny <ernst@baschny.de>
 */

/**
 * This controller will show a tree of elements starting with the current
 * item
 *
 * @package Debug
 * @subpackage UserInterface
 */
class ShowTreeView extends GalleryView {

    /**
     * 
     */
    function renderHead() {
	/* Render the HTML head */
	$template = $this->getTemplate();
	$html = $template->render('DebugHead.tpl');

	return array(GalleryStatus::success(), $html);
    }

    /**
     * 
     */
    function renderBody() {
	global $gallery;

	$form = GalleryUtilities::getFormVariables('form.');
	$return = GalleryUtilities::getFormVariables('return.');
	$formName = GalleryUtilities::getRequestVariables('formName');

	$filterMembers = '';
	if ($formName == 'FilterMembers' && !empty($form['filterMembers'])) {
	    $filterMembers = $form['filterMembers'];
	} else {
		$form['filterMembers'] = '';
	}

	list ($ret, $item) = $this->_getItem();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Make sure we have permission do view things on this item */
	$ret = GalleryUserHelper::assertHasItemPermission($item->getId(), 'core.all');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/*
	 * Build the entityTree, starting at the current item. 
	 * (making a non-recursive pre-order transversal)
	 *  $entityTree[]['classname']
	 *  $entityTree[]['itemId']
	 *  $entityTree[]['level']
	 *  $entityTree[]['members']
	 */
	$entityTree = array();
	$current = 0;
	$maxLevel = 0;
	$startItem = array('level' => 0,
			   'itemId' => $item->getId(),
			   'className' => get_class($item),
			   'members' => DebugHelper::filterMembers($item->getMemberData(), $filterMembers),
			   'completePath' => $item->getPathComponent()
		     );
	$entityTree = array($startItem);
	while ($current < count($entityTree)) {
	    $currentItemId = $entityTree[$current]['itemId'];
	    $currentLevel = $entityTree[$current]['level'];
	    $currentPath = $entityTree[$current]['completePath'];

	    /* Get the childIds of the current item */
	    list ($ret, $childIds) =
		GalleryChildEntityHelper::fetchChildIds($currentItemId);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    if (!empty($childIds)) {
		/* Load the children */
		$childItems = array();
		list ($ret, $childItems) = $gallery->loadEntitiesById($childIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		$newlevel = $currentLevel + 1;
		if ($newlevel > $maxLevel) {
		    $maxLevel = $newlevel;
		}
		$childrenList = array();
		foreach ($childItems as $child) {
		    $childId = $child->getId();
		    if (is_subclass_of($child, "GalleryFileSystemEntity")
			 || get_class($child) == strtolower("GalleryFileSystemEntity")) {
			$thisPath = $currentPath . "/" . $child->getPathComponent();
		    } else {
			$itemType = get_class($child);
			if (is_subclass_of($child, "GalleryDerivativeImage")
			     || get_class($child) == strtolower("GalleryDerivativeImage")) {
			    switch ($child->getDerivativeType()) {
			    case DERIVATIVE_TYPE_IMAGE_THUMBNAIL:
				$itemType = "Thumbnail";
				break;
			    case DERIVATIVE_TYPE_IMAGE_RESIZE:
				$itemType = "Resized";
				break;
			    case DERIVATIVE_TYPE_IMAGE_PREFERRED:
				$itemType = "Preferred";
				break;
			    }
			}
			$thisPath = $currentPath . " (" . $itemType . ")";
		    }
		    $childrenList[] = array('level' => $newlevel,
					    'itemId' => $childId,
					    'className' => get_class($child),
					    'members' => DebugHelper::filterMembers($child->getMemberData(), $filterMembers),
					    'completePath' => $thisPath
				      );
		}
		/* put child items after currentItem in the array */
		$entityTree = array_merge(
				  array_slice($entityTree, 0, $current + 1),
				  $childrenList,
				  array_slice($entityTree, $current + 1)
			      );
	    }
	    $current++;
	}

	/* Render the HTML body */
	$template = $this->getTemplate();
	$template->setVariable('view', 'debug:ShowTree');
	$template->setVariable('itemId', $item->getId());
	$template->setVariable('form', $form);
	$template->setVariable('return', $return);
	$template->setVariable('maxLevel', $maxLevel);
	$template->setVariable('entityTree', $entityTree);
	$html = $template->render('ShowTree.tpl');

	return array(GalleryStatus::success(), $html);
    }

    /**
     * Filter the keys of an array using a regular expression.
     *
     * @param array key => values
     * @param string regular expression
     * @return array
     */
    function _filterMembers($members, $filter) {
	if (!empty($filter)) {
	    $newMembers = array();
	    foreach ($members as $member => $data) {
		if (preg_match("/" . $filter . "/i", $member)) {
		    $newMembers[$member] = $data;
		}
	    }
	    $members = $newMembers;
	}
	return $members;
    }

}
?>
