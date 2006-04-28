<?php
/*
 * $RCSfile: module.inc.tpl,v $
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2006 Bharat Mediratta
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
 * @version $Revision: 1.3 $ $Date: 2006/03/17 17:10:34 $
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
	$this->setRequiredCoreApi(array(7, 0));
	$this->setRequiredModuleApi(array(3, 0));
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

	return array(null, $links);
    {rdelim}
{rdelim}
?>
