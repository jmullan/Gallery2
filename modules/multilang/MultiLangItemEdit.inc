<?php
/*
 * $RCSfile$
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
 */

/**
 * @version $Revision$ $Date$
 * @package MultiLang
 * @subpackage UserInterface
 * @author Alan Harder <alan.harder@sun.com>
 */

/**
 * This controller will handle storing multilanguage captions for GalleryItems
 *
 * @package MultiLang
 * @subpackage UserInterface
 *
 */
class MultiLangItemEdit extends ItemEditPlugin {

    /**
     * @see ItemEditPlugin::handleRequest
     */
    function handleRequest($form, &$item, &$preferred) {
	global $gallery;
	$status = null;
	$error = array();

	if (isset($form['action']['save'])) {
	    GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/MultiLangHelper.class');

	    $ret = MultiLangHelper::setItemData($item, $form['language'],
		$form['title'], $form['summary'], $form['description']);
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }

	    list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'multilang');
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null, null);
	    }
	    $status = $module->translate('Changes saved successfully');

	    $session =& $gallery->getSession();
	    $session->put('multilang.language', $form['language']);
	}

	return array(GalleryStatus::success(), $error, $status);
    }

    /**
     * @see ItemEditPlugin::loadTemplate
     */
    function loadTemplate(&$template, &$form, $item, $thumbnail) {
	global $gallery;
	$session =& $gallery->getSession();
	$translator =& $gallery->getTranslator();
	GalleryCoreApi::requireOnce(dirname(__FILE__) . '/classes/MultiLangHelper.class');

	if ($form['formName'] != 'MultiLangItemEdit') {
	    $form['formName'] = 'MultiLangItemEdit';
	    list ($ret, $form['languageData']) = MultiLangHelper::getItemData($item->getId());
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    $form['title'] = $item->getTitle();
	    $form['summary'] = $item->getSummary();
	    $form['description'] = $item->getDescription();
	}

	$supportedLanguages = $translator->getSupportedLanguages();
	$languageList = array();
	foreach ($supportedLanguages as $language => $countryList) {
	    foreach ($countryList as $country => $languageData) {
		$languageList[$language . '_' . $country] = $languageData['description'];
	    }
	}
	list ($ret, $languages) =
	    GalleryCoreApi::getPluginParameter('module', 'multilang', 'languages');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	$languages = empty($languages) ? array() : explode('|', $languages);
	sort($languages);
	foreach (array_keys($form['languageData']) as $language) {
	    /* Show all languages for item, even if no longer in languages list */
	    if (!in_array($language, $languages)) {
		$languages[] = $language;
	    }
	}

	$selectedLanguage = $session->get('multilang.language');
	if (empty($selectedLanguage)) {
	    list ($ret, $selectedLanguage) = $gallery->getActiveLanguageCode();
	    if ($ret->isError()) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	} else {
	    $session->remove('multilang.language');
	}
	$selectedLanguageIndex = $i = 0;
	foreach ($languages as $language) {
	    $form['languageList'][$language] = isset($languageList[$language])
						? $languageList[$language] : $language;
	    if ($language == $selectedLanguage) {
		$selectedLanguageIndex = $i;
	    }
	    $i++;
	}
	$form['selectedLanguage'] = $selectedLanguage;
	$form['selectedIndex'] = $selectedLanguageIndex;

	$template->setVariable('controller', 'multilang:MultiLangItemEdit');
	return array(GalleryStatus::success(), 'modules/multilang/templates/MultiLangItemEdit.tpl');
    }

    /**
     * @see ItemEditPlugin::isSupported
     */
    function isSupported($item, $thumbnail) {
	return GalleryUtilities::isA($item, 'GalleryItem');
    }

    /**
     * @see ItemEditPlugin::getTitle
     */
    function getTitle() {
	list ($ret, $module) = GalleryCoreApi::loadPlugin('module', 'multilang');
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	return array(GalleryStatus::success(), $module->translate('MultiLanguage'));
    }
}
?>
