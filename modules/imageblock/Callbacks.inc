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
class ImageBlockCallbacks {
    /**
     */
    function callback($params, &$smarty, $callback, $userId=null) {
	switch($callback) {
	case 'LoadImageBlock':
	    GalleryCoreApi::relativeRequireOnce('modules/imageblock/classes/ImageBlockHelper.class');

	    /*
	     * ImageBlockHelper expects a GalleryTemplate, but Smarty callbacks don't provide
	     * one, so create a temporary wrapper.
	     * TODO: rework this so we don't create a new smarty instance (in GalleryTemplate
	     *       constructor) only to replace it with our current instance
	     */
	    $template = new GalleryTemplate(dirname(__FILE__));
	    $template->_smarty = &$smarty;

	    /*
	     * Just use our current set of template vars as the params.  We may wind up passing some
	     * extra data into loadImageBlocks but it will just ignore what it doesn't understand.
	     */
	    $template->setVariable('heading', 1);
	    $ret = ImageBlockHelper::loadImageBlocks($template, $smarty->_tpl_vars);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }

	    return GalleryStatus::success();
	}

	return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__);
    }
}
?>
