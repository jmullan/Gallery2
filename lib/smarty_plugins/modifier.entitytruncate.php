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
 * NOTE: Portions of this file are copied from the Smarty modifier.truncate.php
 * file and are bound by their license, found in lib/smarty/COPYING.lib
 */

/**
 * Smarty truncate modifier plugin.  This differs from the standard Smarty plugin
 * in that it respects HTML entities and doesn't split them.
 *
 * Type:     modifier<br>
 * Name:     entitytruncate<br>
 * Purpose:  Truncate a string to a certain length if necessary,
 *           optionally splitting in the middle of a word, and
 *           appending the $etc string.  Won't split an HTML entity.
 *
 * @param string the input string
 * @param integer what to truncate it to (max length upon return)
 * @param string what to use to indicate that there was more (default: "...")
 * @param boolean break words or not?
 * @return string 
 */
function smarty_modifier_entitytruncate($string, $length, $etc='...', $breakWords=false) {
    return GalleryUtilities::entityTruncate($string, $length, true, $etc, $breakWords);
}
?>