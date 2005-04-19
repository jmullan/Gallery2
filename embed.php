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
 * Access point for external application in which Gallery is embedded.
 * See docs/EMBEDDING for more information on using the GalleryEmbed class.
 * See also modules/core/classes/GalleryEmbed.class for more details.
 * Three interaction modes:
 *  1) GalleryEmbed::init(array(..)) followed by GalleryEmbed::handleRequest()
 *  2) GalleryEmbed::init() followed by other GalleryEmbed/G2 calls,
 *     end with GalleryEmbed::done() <-- REQUIRED
 *  3) Single GalleryEmbed::logout() call
 *
 * @package GalleryMain
 * @version $Revision$ $Date$
 * @author Alan Harder <alan.harder@sun.com>
 */

define('G2_EMBED', 1);
require(dirname(__FILE__) . '/main.php');
require(dirname(__FILE__) . '/modules/core/classes/GalleryEmbed.class');

?>