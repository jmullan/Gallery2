<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2002 Bharat Mediratta
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

/* Turn on debug mode */
$gallery->setDebug('buffered');

/* Connection information for the GalleryStorage sub-system */
$dbConfig['type'] = 'mysql';
$dbConfig['hostname'] = 'localhost';
$dbConfig['database'] = 'g2dev';
$dbConfig['username'] = 'g2dev';
$dbConfig['password'] = 'g2dev';
$dbConfig['tablePrefix'] = 'g2_';
$dbConfig['columnPrefix'] = 'g_';
$gallery->setConfig('storage.config', $dbConfig);
$gallery->setConfig('storage.type', 'database');

?>
