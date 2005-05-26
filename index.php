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
 * @package Gallery
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/*
 * This script will just redirect to main.php. But the Location header requires
 * an absolute url to conform with HTTP/1.1
 */

require(dirname(__FILE__) . '/modules/core/classes/GalleryUrlGenerator.class'); 

/* The REQUEST_URI can either be /path/index.php or just /path/. Get rid of index.php.* */
$path = preg_replace('|^(/(?:[^?#/]+/)*).*|', '$1', GalleryUrlGenerator::getCurrentRequestUri());

header('Location: ' . GalleryUrlGenerator::makeUrl($path) . GALLERY_MAIN_PHP);
?>
