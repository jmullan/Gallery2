<?php
/*
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
 * Regenerate the session id to prevent session fixation attacks
 * Must be called before starting to output any data since it tries to send a cookie
 */
function regenerateSession() {
    /* 1. Generate a new session id */
    $newSessionId = md5(uniqid(substr(rand() . serialize($_REQUEST), 0, 114)));
    $sessionData = array();
    if (!empty($_SESSION) && is_array($_SESSION)) {
	foreach ($_SESSION as $key => $value) {
	    $sessionData[$key] = $value;
	}
    }
    /* 2. Delete the old session */
    session_unset();
    session_destroy();
    /* Create the new session with the old data, send cookie */
    session_id($newSessionId);
    $sessionName = session_name();
    /* Make sure we don't use invalid data at a later point */
    foreach (array($_GET, $_POST, $_REQUEST, $_COOKIE) as $superGlobal) {
	unset($superGlobal[$sessionName]);
    }
    session_start();
    foreach ($sessionData as $key => $value) {
	$_SESSION[$key] = $value;
    }
}

/**
 * Are cookies supported by the current user-agent?
 */
function areCookiesSupported() {
    static $areCookiesSupported;

    /* Remember the state since we might unset $_COOKIE */
    if (!isset($areCookiesSupported)) {
	$areCookiesSupported = !empty($_COOKIE[session_name()]);
    }

    return $areCookiesSupported;
}

?>