<?php
/*
 * $RCSfile$
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
 * @package NokiaUpload
 * @author Jerome Rannikko <jeromer@hotpop.com>
 */

/**
 * Error codes and other constants for NokiaUpload module. 
 * These are defined in the Image Upload Server API document
 * available at forum.nokia.com.
 */

/* Set this to true to make Upload module (LoginHelper and NewDirectoryHelper)read 
 * parameters from GET. Normally they are only read from POST but if you allow GET, 
 * you can use desktop browser for easier debugging. */
define('NOKIAUPLOAD_DEBUG', false);

define('NOKIAUPLOAD_ERR_NOERR', '0');
define('NOKIAUPLOAD_ERR_UNKNOWN', '1');

/* Login (section 5.2) */
define('NOKIAUPLOAD_PROTOCOLVERSION', '1.00');
define('NOKIAUPLOAD_ERR_AUTH', '2');

/* New Directory (section 5.4) */
define('NOKIAUPLOAD_ERR_DIRCREATE', '2');

/* Upload (section 5.5) */
define('NOKIAUPLOAD_ERR_NOSPACE', '2'); // Not enough space left in server.
define('NOKIAUPLOAD_ERR_TOOBIG', '3');  // Too large image.

/* Directory Listing (section 5.6) */
define('NOKIAUPLOAD_ERR_DIRLIST', '2');

?>
