<?php
/*
 * $RCSfile
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
 * @package Comment
 * @author Bharat Mediratta <bharat@menalto.com>
 */

/**
 * This controller will handle the setting of options specific to the comment-module
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class AdminCommentsController extends GalleryController {

    /**
     * @see GalleryController::handleRequest()
     */
    function handleRequest() {
	global $gallery;

	/* Make sure we have adequate permissions */
	$ret = GalleryUserHelper::assertSiteAdministrator();
	if ($ret->isError()) {
	    return array($ret->wrap(__FILE__, __LINE__), null);
	}

	/* ... take some action here ... */

	/* Figure out where to redirect upon success */
	$redirectParams['view'] = 'core:SiteAdmin';
	$redirectParams['subView'] = 'comment:AdminComments';

	$urlGenerator = $gallery->getUrlGenerator();
	$results['redirect'] = $urlGenerator->generateUrl($redirectParams);

	return array(GalleryStatus::success(), $results);
    }
}

/**
 * This view will prompt for settings specific to the comment module
 *
 * @package Comment
 * @subpackage UserInterface
 *
 */
class AdminCommentsView extends GalleryView {

    /**
     * @see GalleryView::renderBody()
     */
    function renderBody() {
	global $gallery;

	/* Render the HTML body */
	$template = $this->_getTemplate();
	$template->setVariable('controller', 'comment:AdminComments');
	$html = $template->render('AdminComments.tpl');
	
	return array(GalleryStatus::success(), $html);
    }
}
?>
