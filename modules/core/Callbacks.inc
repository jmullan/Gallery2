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
class CoreCallbacks {
    function callback($params, &$smarty, $callback, $userId=null) {
	global $gallery;

	$block =& $smarty->_tpl_vars['block'];

	switch($callback) {
	case 'LoadLanguageSelector':
	    $languageList = array();
	    $translator =& $gallery->getTranslator();
	    $supportedLanguages = $translator->getSupportedLanguages();
	    foreach ($supportedLanguages as $language => $countryList) {
		foreach ($countryList as $country => $languageData) {
		    $languageList[$language . '_' . $country] = $languageData['description'];
		}
	    }

	    list ($ret, $language) = $gallery->getActiveLanguageCode();
	    if ($ret->isError()) {
		return $ret->wrap(__FILE__, __LINE__);
	    }

	    $block['core']['LanguageSelector'] =
		array('list' => $languageList, 'language' => $language);
	    return GalleryStatus::success();

	case 'ShouldShowEmergencyEditItemLink':
	    $theme =& $smarty->_tpl_vars['theme'];
	    $block['core']['ShouldShowEmergencyEditItemLink'] = true;
	    foreach (array('checkSidebarBlocks' => 'sidebarBlocks',
			   'checkAlbumBlocks' => 'albumBlocks',
			   'checkPhotoBlocks' => 'photoBlocks')
		     as $key => $value) {
		if (!empty($params[$key])) {
		    foreach ($theme['params'][$value] as $entry) {
			if ($entry[0] == 'core.ItemLinks') {
			    $block['core']['ShouldShowEmergencyEditItemLink'] = false;
			    break 2;
			}
		    }
		}
	    }
	}

	return GalleryStatus::error(ERROR_BAD_PARAMETER, __FILE__, __LINE__);
    }
}
?>
