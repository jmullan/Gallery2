<?php
/*
 * $RCSfile
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
 *
 */
/**
 * @version $Revision$
 * @package GalleryCore
 * @subpackage Smarty_plugins
 * @author Jesse Mullan
 */

/**
 * This takes an array and looks for view, subview, and 
 *
 * Type:     function<br />
 * Name:     safecssname<br />
 * Purpose:  Removes characters from a string so that it can be used for an
 * html class name or id and be addressed via css
 *
 * @param array the items to make a link out of
 * @return string the id of the link
 */
function smarty_function_adminlinkid($params) {
    require_once('modifier.safecssname.php');
    $linkArray = $params['arg1'];
    $linkId = 'gbLink_';
    $linkId .= (!empty($linkArray['controller'])) ? smarty_modifier_safecssname($linkArray['controller']) : '';
    $linkId .= (!empty($linkArray['view'])) ? smarty_modifier_safecssname($linkArray['view']) : '';
    $linkId .= (!empty($linkArray['subView'])) ? smarty_modifier_safecssname($linkArray['subView']) : '';
    return $linkId;
}
?>