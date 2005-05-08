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
 * @package Quotas
 * @subpackage UserInterface
 * @author Robert Balousek <volksport@users.sf.net>
 */

/**
 * This ItemAddOption enforces disk quotas
 *
 * @package Quotas
 * @subpackage UserInterface
 */

class DiskQuotaOption extends ItemAddOption {

    /**
     * @see ItemAddOption::isAppropriate
     */
    function isAppropriate() {
        return array(GalleryStatus::success(), true);
    }

    /**
     * @see ItemAddOption::handleRequestAfterAdd
     */
    function handleRequestAfterAdd($form, $items) {
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/GalleryQuotasHelper.class');

	global $gallery;
	$warnings = array();
	$errors = array();

	/* user's disk quota in KB */
        list ($ret, $quotaExists, $userDiskQuota) =
            GalleryQuotasHelper::getUserDiskQuota($gallery->getActiveUserId());
        if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null, null);
        }

        /* if user has a quota */
	if ($quotaExists) {
	    $excludedIds = array();
	    for ($j = 0; $j < count($items); $j++) {
		$excludedIds[] = $items[$j]->getId();
	    }
	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'quotas');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    for ($i = 0; $i < count($items); $i++) {
		$warnings[$i] = array();

		/* we should come here only if we are adding a data item, not sub-album */
		$albumId = $items[$i]->getParentId();

		/* calculate the item ids of the newly added items */
		array_shift($excludedIds);

		/* user's disk usage in Bytes */
		list ($ret, $userDiskUsage) =
		    GalleryQuotasHelper::getUserDiskUsage($gallery->getActiveUserId(),
							  $excludedIds);
		if ($ret->isError()) {
		    return array($ret->wrap(__FILE__, __LINE__), null, null);
		}

		/* make disk usage into KB */
		$userDiskUsage /= 1024.00;

		if ($userDiskUsage > $userDiskQuota) {
		    list ($ret, $userDiskQuotaHumanReadable, $userDiskQuotaHumanReadableUnit) =
			GalleryQuotasHelper::humanReadableFromKiloBytes($userDiskQuota);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		    $exceedString = 'Warning: You have reached your disk quota (%s %s), ';
		    $exceedString .= 'this item will not be added.';
		    $warnings[$i][] =
			$module->translate(array('text' => $exceedString,
						 'arg1' => $userDiskQuotaHumanReadable,
						 'arg2' => $userDiskQuotaHumanReadableUnit));
		    $ret = GalleryCoreApi::deleteEntityById($items[$i]->getId());
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		} else {
		    list ($ret, $userDiskQuotaHumanReadable, $userDiskQuotaHumanReadableUnit) = 
			GalleryQuotasHelper::humanReadableFromKiloBytes($userDiskQuota);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }
		    list ($ret, $userDiskUsageHumanReadable, $userDiskUsageHumanReadableUnit) = 
			GalleryQuotasHelper::humanReadableFromKiloBytes($userDiskUsage);
		    if ($ret->isError()) {
			return array($ret->wrap(__FILE__, __LINE__), null, null);
		    }

		    $usageString = 'You are using %s %s of your allotted %s %s.';
		    $warnings[$i][] = 
			$module->translate(array('text' => $usageString,
	    					 'arg1' => $userDiskUsageHumanReadable,
						 'arg2' => $userDiskUsageHumanReadableUnit,
						 'arg3' => $userDiskQuotaHumanReadable,
						 'arg4' => $userDiskQuotaHumanReadableUnit));
		}
	    }
        }
	return array(GalleryStatus::success(), $errors, $warnings);
    }

}
?>
