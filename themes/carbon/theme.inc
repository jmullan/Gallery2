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
 * Carbon theme
 * @package Themes
 * @subpackage Carbon
 * @author Mustafa Incel (based on Matrix by Bharat Mediratta <bharat@menalto.com>)
 * @version $Revision$ $Date$
 */
class CarbonTheme extends GalleryTheme {

    function CarbonTheme() {
	global $gallery;

	$this->setId('carbon');
	$this->setName($gallery->i18n('Carbon'));
	$this->setDescription($gallery->i18n('Gallery2 theme by mincel.com'));
	$this->setVersion('1.1.1');
	$this->setRequiredCoreApi(array(7, 0));
	$this->setRequiredThemeApi(array(2, 1));
	$this->setStandardSettings(
	    array('rows' => 3, 'columns' => 3,
		  'showImageOwner' => 0, 'showAlbumOwner' => 1,
		  'albumFrame' => '', 'itemFrame' => '', 'photoFrame' => '',
		  'colorpack' => '',
		  'showMicroThumbs' => 1,
		  'sidebarBlocks' => serialize(array(
			array('search.SearchBlock', array('showAdvancedLink' => true)),
			array('core.ItemLinks', array('useDropdown' => false)),
			array('core.PeerList', array()),
			array('imageblock.ImageBlock', array()))),
		  'albumBlocks' => serialize(array(
			array('comment.ViewComments', array()))),
		  'photoBlocks' => serialize(array(
			array('exif.ExifInfo', array()),
			array('comment.ViewComments', array()))),
		  'navigatorPhotoTop' => 1, 'navigatorPhotoBottom' => 1,
		  'photoProperties' => 1, 'fullSize' => 1,
		  'albumBlocks2' => serialize(array()),
		  'photoBlocks2' => serialize(array()),
		  'sidebarTop' => 106, 'maxMicroThumbs' => 12,
		  'extraLink' => '', 'extraLinkUrl' => '', 'copyright' => '',
	));
    }

    /**
     * @see GalleryTheme::getSettings
     */
    function getSettings($itemId=null) {
	list ($ret, $settings, $params) = parent::getSettings($itemId);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our custom settings */
	$settings[] = array('key' => 'navigatorPhotoTop',
			    'name' => $this->translate('Show top photo navigator'),
			    'type' => 'checkbox',
			    'value' => $params['navigatorPhotoTop']);
	$settings[] = array('key' => 'navigatorPhotoBottom',
			    'name' => $this->translate('Show bottom photo navigator'),
			    'type' => 'checkbox',
			    'value' => $params['navigatorPhotoBottom']);
	$settings[] = array('key' => 'photoProperties',
			    'name' => $this->translate('Show \'Photo Properties\' icon'),
			    'type' => 'checkbox',
			    'value' => $params['photoProperties']);
	$settings[] = array('key' => 'fullSize',
			    'name' => $this->translate('Show \'Full Size\' icon'),
			    'type' => 'checkbox',
			    'value' => $params['fullSize']);
	$settings[] = array('key' => 'albumBlocks2',
			    'name' => $this->translate('Blocks to show on album pages (below description)'),
			    'type' => 'block-list',
			    'typeParams' => array('packType' => 'block-list'),
			    'value' => $params['albumBlocks2']);
	$settings[] = array('key' => 'photoBlocks2',
			    'name' => $this->translate('Blocks to show on photo pages (below description)'),
			    'type' => 'block-list',
			    'typeParams' => array('packType' => 'block-list'),
			    'value' => $params['photoBlocks2']);
	$settings[] = array('key' => 'sidebarTop',
			    'name' => $this->translate('Sidebar top position'),
			    'type' => 'text-field',
			    'typeParams' => array('size' => 2),
			    'value' => $params['sidebarTop']);
	$settings[] = array('key' => 'maxMicroThumbs',
			    'name' => $this->translate('Maximum number of micro navigation thumbnails'),
			    'type' => 'text-field',
			    'typeParams' => array('size' => 2),
			    'value' => $params['maxMicroThumbs']);
	$settings[] = array('key' => 'extraLink',
			    'name' => $this->translate('Extra link for top navigation bar'),
			    'type' => 'text-field',
			    'typeParams' => array('size' => 30),
			    'value' => $params['extraLink']);
	$settings[] = array('key' => 'extraLinkUrl',
			    'name' => $this->translate('URL for the extra link'),
			    'type' => 'text-field',
			    'typeParams' => array('size' => 30),
			    'value' => $params['extraLinkUrl']);
	$settings[] = array('key' => 'copyright',
			    'name' => $this->translate('Copyright message to display on footer'),
			    'type' => 'text-field',
			    'typeParams' => array('size' => 30),
			    'value' => $params['copyright']);

	return array(null, $settings, $params);
    }

    /**
     * @see GalleryTheme::validateSettings
     */
    function validateSettings($settings) {
	$error = parent::validateSettings($settings);
	if (empty($settings['sidebarTop']) || !is_numeric($settings['sidebarTop'])) {
	    $error['sidebarTop'] = $this->translate('You must enter a number greater than 0');
	}
	if (empty($settings['maxMicroThumbs']) || !is_numeric($settings['maxMicroThumbs'])) {
	    $error['maxMicroThumbs'] = $this->translate('You must enter a number greater than 0');
	}
	foreach (array('albumBlocks2') as $blockKey) {
	    if (isset($standard[$blockKey])) {
		if (!empty($settings[$blockKey])) {
		    list ($success, $newValue) =
			$this->packSetting('block-list', $settings[$blockKey]);
		    if (!$success) {
			$error[$blockKey] =
			    $this->translate('Format: [module.BlockName param=value] ...');
		    }
		}
	    }
	}
	foreach (array('photoBlocks2') as $blockKey) {
	    if (isset($standard[$blockKey])) {
		if (!empty($settings[$blockKey])) {
		    list ($success, $newValue) =
			$this->packSetting('block-list', $settings[$blockKey]);
		    if (!$success) {
			$error[$blockKey] =
			    $this->translate('Format: [module.BlockName param=value] ...');
		    }
		}
	    }
	}
	return $error;
    }

    /**
     * @see GalleryTheme::loadTemplate
     */
    function loadTemplate($view, &$template, $item, $params, $viewResults) {
	global $gallery;
	$theme =& $template->getVariableByReference('theme');

	$urlGenerator =& $gallery->getUrlGenerator();
	$theme['themeUrl'] =
	    $urlGenerator->generateUrl(array('href' => 'themes/' . $this->getId()));

	/* By default we're not in preview mode, and are the active user */
	$theme['guestPreviewMode'] = 0;
	$theme['actingUserId'] = $gallery->getActiveUserId();

	list ($ret, $theme['markupType']) =
	    GalleryCoreApi::getPluginParameter('module', 'core', 'misc.markup');
	if ($ret) {
	    $theme['markupType'] = 'none';
	}

	$theme['params'] = $params;
	$theme['useFullScreen'] = !empty($viewResults['useFullScreen']);

	/* Unserialize our blocks and preload them if necessary */
	foreach (array('sidebarBlocks', 'albumBlocks', 'photoBlocks', 'albumBlocks2', 'photoBlocks2') as $blockKey) {
	    if (!isset($theme['params'][$blockKey])) {
		continue;
	    }

	    $theme['params'][$blockKey] = unserialize($theme['params'][$blockKey]);

	    $seen = array();
	    foreach ($theme['params'][$blockKey] as $block) {
		$seen[$block[0]][] = $block[1];
	    }

	    foreach ($seen as $blockId => $blockParams) {
		$ret = $this->preloadBlock($template, $blockId, $blockParams);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	if ($this->getId() == 'fallbackTheme') {
	    /* If theme failed to load then we're done */
	    $theme['isFallback'] = true;
	    return array(null, $viewResults);
	}

	if (!GalleryCapabilities::can('showSidebarBlocks') && !empty($params['sidebarBlocks'])) {
	    $extractedSidebarBlocks = $theme['params']['sidebarBlocks'];
	    $theme['params']['sidebarBlocks'] = array();
	}

	/* Load icon pack if available */
	list ($ret, $iconpack) = GalleryCoreApi::newFactoryInstance('IconsInterface_1_0');
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}
	if (isset($iconpack)) {
	    $ret = $iconpack->init($template);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	}

	/* Load color pack if the theme supports them (and they're available) */
	if (!empty($params['colorpack'])) {
	    list ($ret, $colorpack) = GalleryCoreApi::newFactoryInstance('ColorPackInterface_1_0');
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    if (isset($colorpack)) {
		$ret = $colorpack->selectColorPack($template, $params['colorpack']);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	/*
	 * Figure out what type of view we've got.  This is lame and not very OO.  We should
	 * create a view hierarchy that lets them implement their own showPage() method.
	 */
	switch ($view->getViewType()) {
	case VIEW_TYPE_ADMIN:
	    $theme['pageType'] = 'admin';
	    $theme['adminTemplate'] = $viewResults['body'];
	    $theme['adminL10Domain'] = $view->getL10Domain();
	    list ($ret, $result) = $this->showAdminPage(
		$template, $item, $params, $viewResults['body']);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    break;

	case VIEW_TYPE_SHOW_ITEM:
	    $this->_cacheablePage = true;
	    $session =& $gallery->getSession();

	    if ($session->get('theme.guestPreviewMode')) {
		$theme['guestPreviewMode'] = 1;
		list ($ret, $theme['actingUserId']) =
		    GalleryCoreApi::getPluginParameter('module', 'core', 'id.anonymousUser');
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    /* Albums have their own settings.  Photos use their parent album's settings */
	    if ($item->getCanContainChildren()) {
		$theme['pageType'] = 'album';

		/* If we care about pagination, then figure out the current page and total pages */
		$perPage = $this->getPageSize($params);

		$page = GalleryUtilities::getRequestVariables('page');
		if ($perPage == 0) {
		    $page = 1;
		} else if (empty($page)) {
		    /*
		     * We don't have a page number.  If we have a highlight id, then figure out what
		     * page that id is on and redirect to that page.
		     */
		    $highlightId = GalleryUtilities::getRequestVariables('highlightId');
		    if (!empty($highlightId)) {
			list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds($item);
			if ($ret) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}

			$page = 1;
			for ($i = 0; $i < sizeof($childIds); $i++) {
			    if ($childIds[$i] == $highlightId) {
				/* Found it */
				$page = ceil(($i+1) / $perPage);
				break;
			    }
			}

			/* Redirect to the new page */
			$redirect = array('view' => 'core.ShowItem', 'itemId' => $item->getId());
			if ($page != 1) {
			    $redirect['page'] = $page;
			}
			return array(null, array('redirect' => $redirect));
		    } else {
			$page = 1;
		    }
		}

		if (!empty($perPage)) {
		    if (empty($page)) {
			$page = 1;
		    }

		    /* Use the pagination to calculate the child item ids to load */
		    $start = $perPage * ($page - 1);
		    list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds(
			$item, $start, $perPage, $theme['actingUserId']);
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /*
		     * Load up our child count so that we can figure out the max pages.  We do this
		     * after we get the child ids because the 'childCount' common template data also
		     * gets the child counts for the child albums.
		     */
		    $ret = $this->loadCommonTemplateData(
			$template, $item, $params, array('childCount'), $childIds, false);
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }

		    /* Store the total pages in the theme */
		    $theme['totalPages'] = ceil($theme['childCount'] / $perPage);
		    $theme['currentPage'] = $page;

		    /* If our page is over the max, redirect the user to the max page */
		    if ($page > $theme['totalPages'] && $theme['childCount'] > 0) {
			$redirect = array('view' => 'core.ShowItem', 'itemId' => $item->getId());
			if ($theme['totalPages'] != 1) {
			    $redirect['page'] = $theme['totalPages'];
			}
			return array(null, array('redirect' => $redirect));
		    }
		} else {
		    /*
		     * No pagination; load all children (this isn't going to scale, but the theme is
		     * the boss... for now).
		     */
		    list ($ret, $childIds) = GalleryCoreApi::fetchChildItemIds(
			$item, null, null, $theme['actingUserId']);
		    if ($ret) {
			return array($ret->wrap(__FILE__, __LINE__), null);
		    }
		}

		list ($ret, $result) =
		    $this->showAlbumPage($template, $item, $params, $childIds);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    } else {
		$theme['pageType'] = 'photo';
		list ($ret, $result) = $this->showPhotoPage($template, $item, $params);
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }

	    /* Load image frames if the theme supports them (and they're available) */
	    if (!empty($params['albumFrame']) ||
		!empty($params['itemFrame']) ||
		!empty($params['photoFrame'])) {
		list ($ret, $imageframe) =
		    GalleryCoreApi::newFactoryInstance('ImageFrameInterface_1_1');
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
		if (isset($imageframe)) {
		    $frameIds = array();
		    if ($item->getCanContainChildren()) {
			foreach (array('albumFrame', 'itemFrame') as $key) {
			    if (!empty($params[$key])) {
				$frameIds[] = $theme['params'][$key] = $params[$key];
			    }
			}
		    } else {
			if (!empty($params['photoFrame'])) {
			    $frameIds[] = $theme['photoFrame'] = $params['photoFrame'];
			}
		    }
		    if (!empty($frameIds)) {
			$ret = $imageframe->init($template, $frameIds);
			if ($ret) {
			    return array($ret->wrap(__FILE__, __LINE__), null);
			}
		    }
		}
	    }
	    break;

	case VIEW_TYPE_PROGRESS_BAR:
	    /* We only use this for progressbar views (for now) */
	    $theme['pageType'] = 'progressbar';
	    list ($ret, $result) = $this->showProgressBarPage($template, $item, $params);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    break;

	default: /* VIEW_TYPE_MODULE */
	    $theme['pageType'] = 'module';
	    $theme['moduleTemplate'] = $viewResults['body'];
	    $theme['moduleL10Domain'] = $view->getL10Domain();
	    list ($ret, $result) = $this->showModulePage(
		$template, $item, $params, $viewResults['body']);
	    if ($ret) {
		return array($ret->wrap(__FILE__, __LINE__), null);
	    }
	    break;
	}

	if (!is_array($result)) {
	    $result = array('body' => sprintf('themes/%s/templates/%s', $this->getId(), $result),
			    'cacheable' => $this->_cacheablePage ? $item->getId() : false);
	}

	if (isset($extractedSidebarBlocks)) {
	    $templateAdapter =& $gallery->getTemplateAdapter();

	    /* Render the sidebar blocks and save them */
	    foreach ($extractedSidebarBlocks as $block) {
		$template->setVariable(
		    'SidebarBlock', array('type' => $block[0], 'params' => $block[1]));
		list ($ret, $result['sidebarBlocksHtml'][]) =
		    $template->fetch('gallery:modules/core/templates/SidebarBlock.tpl');
		if ($ret) {
		    return array($ret->wrap(__FILE__, __LINE__), null);
		}
	    }
	}

	return array(null, $result);
    }

    /**
     * @see GalleryTheme::showAlbumPage
     */
    function showAlbumPage(&$template, $item, $params, $childIds) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params,
	    array('owner', 'viewCount', 'childCount', 'descendentCount', 'parents',
		  'systemLinks', 'itemLinks', 'itemSummaries', 'permissions',
		  'thumbnails', 'pageNavigator', 'jumpRange'),
	     $childIds);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* Add in our extra stuff */
	$theme =& $template->getVariableByReference('theme');
	$theme['columnWidthPct'] = floor(100 / $params['columns']);

	/* Add our header and styles */
	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showPhotoPage
     */
    function showPhotoPage(&$template, $item, $params) {
	$dataTypes = array('owner', 'parents', 'systemLinks', 'itemLinks', 'permissions',
			   'itemLinksDetailed', 'itemNavigator', 'imageViews');
	if (!empty($params['showMicroThumbs'])) {
	    $dataTypes[] = 'navThumbnails';
	}
	$ret = $this->loadCommonTemplateData($template, $item, $params, $dataTypes);
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showModulePage
     */
    function showModulePage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showAdminPage
     */
    function showAdminPage(&$template, $item, $params, $templateFile) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }

    /**
     * @see GalleryTheme::showErrorPage
     */
    function showErrorPage(&$template) {
	return array(null, 'error.tpl');
    }

    /**
     * @see GalleryTheme::showProgressBarPage
     */
    function showProgressBarPage(&$template, $item, $params) {
	$ret = $this->loadCommonTemplateData(
	    $template, $item, $params, array('parents', 'systemLinks'));
	if ($ret) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	return array(null, 'theme.tpl');
    }
}
?>
