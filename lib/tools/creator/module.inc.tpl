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
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */
/**
 * @package {$moduleName}
 * @version $Revision$ $Date$
 * @author {$authorFullName}
 */

/**
 * {$moduleName}
 *
 * Describe your new module here!
 *
 * @package {$ucModuleId}
 */
class {$ucModuleId}Module extends GalleryModule {ldelim}

    function {$ucModuleId}Module() {ldelim}
	global $gallery;

	$this->setId('{$moduleId}');
	$this->setName($gallery->i18n('{$moduleName}'));
	$this->setDescription($gallery->i18n('My {$moduleName} module'));
	$this->setVersion('1.0.0');
	$this->setCallbacks('getItemLinks');
	$this->setGroup('other', $this->translate('Other'));
	$this->setRequiredCoreApi(array(6, 0));
	$this->setRequiredModuleApi(array(2, 2));
    {rdelim}

    /**
     * @see GalleryModule::autoConfigure
     */
    function autoConfigure() {ldelim}
	/* We don't require any special configuration */
	return array(GalleryStatus::success(), true);
    {rdelim}

    /**
     * @see GalleryModule::getItemLinks()
     */
    function getItemLinks($items, $wantsDetailedLinks, $permissions) {ldelim}
	$links = array();
	foreach ($items as $item) {ldelim}
	    $params['view'] = '{$moduleId}.MyPage';
	    $params['itemId'] = $item->getId();
	    $links[$item->getId()][] =
		array('text' => $this->translate('{$moduleName}'), 'params' => $params);
	{rdelim}

	return array(GalleryStatus::success(), $links);
    {rdelim}
{rdelim}
?>
