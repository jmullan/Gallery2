<?php
/*
 * Gallery - a web based photo album viewer and editor 
 * Copyright (C) 2000-2004 Bharat Mediratta
 *
 * This program is free software;you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY;without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id$
 */

/*
 * Matrix Layout for Gallery 2
 * by Ross A. Reyman, Jon Huang, and Chad Kieffer
 *
 * /layouts/matrix/layout.css
 *
 * This css file provides positioning support for the matrix layout.
 * Specifically, it is used by templates in layouts/matrix/templates/.
 *
 */
header("Content-type: text/css");
?>

/* ******************************************************************************************
 * Standard CSS definitions, redefine HTML tags
 */

form, div, h1, h2, h3, h4, h5, h6  {
    margin: 0;
    padding: 0;
}

/* ******************************************************************************************
 * GALLERY
 * Category 1: Gallery		
 * declare Gallery Module Borders, etc
 */

#gallery { }


/* ******************************************************************************************
 * SECTIONS
 * Category 2: section definitions
 * declare section styles		   
 */

#gsHeader {
	display: block;
	clear: both;
	margin: 0 16px 0 0;
	padding: 0 0 0 8px;
}

#gsFooter {
	display: block;
	clear: both;
	margin: 0 15px 0 0;
	padding: 8px;
}

#gsSidebar, #gsAdminSidebar {
	float: left;
	width: 20%;
}

#gsSystemLinks {
	float: right;
	margin: 0;
	padding: 6px 8px;
}

#gsSystemLinks ul {
	list-style-type: none;
	position: relative;
	display: inline;
	margin: 0 15px 0 0;
	padding: 0;
}

#gsSystemLinks ul li {
	display: inline;
	margin: 0 0 0 10px;
	background-image: none;
}

#gsContents {
    width: 100%;
}

#gsContents:after {
	content: ".";
	display: block;
	height: 0;
	visibility: hidden;
}

/* Hides from IE-mac \*/
* html .#gsContents {height: 1%;}
/* End hide from IE-mac */

#gsAlbumContents, #gsAdminContents, #gsOtherContents {
    float: left;
    width: 78%;
}

/* html #gsAlbumContents {overflow: auto;}*/ /* style for IE */

.gbExif {
    padding: 8px 14px;
}

.gbCustomFields {
    padding: 8px 14px;
}

/* .gbDataTable	*/
/*      count from 0 � first row is even...     */

.gsOtherContents table.gbDataTable {
    width: 97%;
}

.gsOtherContents .giActionSelect, .gbDataEntry .giActionSelect {
	display: inline;
	margin: 4px 0 0 2px;
}

table.gbDataTable th {
    padding: 4px;
}

.gbCartInfo li {
    margin: 0 0 0 -20px;
    background-image: none;
}

table.gbDataTable td {
     padding: 4px;
}

#gsComments {
    position: relative;
    clear: both;
    padding: 8px 14px;
}

#gsSearchContents .gbItemImage {
    clear: left;
}

#gsStatus {
	margin: 0;
	padding: 8px;
	text-align: left;
}

#gsItemImages {
	display: block;
	clear: both;
}

#gsAlbumImages {
	display: block;
	clear: both;
}

/* ******************************************************************************************
 * BOXES
 * Category 3: box definitions			   
 * This also includes Category 4: items that are defined 
 * with respect to sections.
 */

.gbDataEntry {
    margin: 6px 0px;
}

ul.gbAdminList {
    margin: 0;
    padding: 1px 0;
}

ul.gbAdminList li {
    margin: 0;
    padding: 1px 0;
    background-image: none;
}

ul.gbAdminList li label { }

/*	tabs for admin pages	*/
.gbTabBar {
	float: left;
	width: 100%;
	margin: 0 0 8px 0;
	padding: 0;
}

.gbTabBar ul {
	margin: 0;
	padding: 10px 10px 0 0;
}

.gbTabBar li {
	margin: 0;
	padding: 0 0 0 8px;
	float: left;
}

.gbTabBar span {
	padding: 6px 12px 4px 4px;
	display: block;
	float: left;
}

/* commented Backslash Hack hides rule from IE5-Mac \*/
.gbTabBar a {float: none;}
/* End IE5-Mac hack */

/*      first and default module settings */

.gbMenu {
    margin: 16px 0 0 8px;
	padding: 0 0 16px 0;
}

/*      subsequent menu modules can have different settings */
.gbMenu + .gbMenu {
	margin-top: 0;
	padding-top: 12px;
}


/*	icons for admin menu	*/
.gbMenu li {
	padding: 6px 0 0 0;
	background-image: none;
}

.gbMenu ul, .gbMenu ol {
	margin: 0;
	padding: 0;
}

.gbMenu:after {
	content: ".";
	display: block;
	height: 0;
	clear: both;
	visibility: hidden;
}

/* Hides from IE-mac \*/
* html .gbMenu {height: 1%;}
/* End hide from IE-mac */

/*	text inside the title bar */
.giTitle { }

/*      horizontal history links - 'trail of breadcrumbs' */
.gbBreadCrumb {
	margin: 0;
	padding: 6px 8px;
}

.gbBreadCrumb li {
	display: inline;
	padding: 0 0 0 14px;
}

.gbBreadCrumb li.giBreadCrumbFirst {
	padding: 0;
}

/*      inside gsAlbumContents or gsAdmiinContents */

.gbTopFlag, .gbBottomFlag {
	margin: 0;
	padding: 4px 0 4px 0;
}

.gbTopFlag:after, .gbBottomFlag:after {
    content: ".";
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
}

/* Hides from IE-mac \*/
* html .gbTopFlag {height: 1%;}
* html .gbBottomFlag {height: 1%;}
/* End hide from IE-mac */

.gbNavBar {
    margin: 0;
    padding: 0 14px;
}

.gbNavBar .gbAdmin {
    float: right;
    padding: 3px;
}

/* Put in to fix viewCart action selector. 
 * Without this, the go button wraps because of 
 * giActionSelect below with dipslay: block.
 */
.gbAdmin .giActionSelect {
	display: inline;
}

.gbNavBar:after {
    content: ".";
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
}

/* Hides from IE-mac \*/
* html .gbNavBar {height: 2em;}
/* End hide from IE-mac */

.gbTitleBanner {
    padding: 8px 14px;
}

.gbTitleBanner h1 {
    margin: 0;
    padding: 0;
}

table.gbTitleBanner {
	margin: 0 0 0 14px;
	padding: 0;
}

table.gbTitleBanner tr td {
    width: 33%;     
}

.gbTitleBanner .giTitle {
    margin: 9px 0 0 0;
}

.gbTitle {
    padding: 12px 0 6px 14px;
}

#gbThumbMatrix { }

td.gbItemAlbum, td.gbItemImage, td.gbItemMovie, td.gbItemOther {
    width: 20%;
    padding: 14px;
}

.gsSingleImage {
    margin: 16px;
}

/*	  #gsComments	 */

.gbComment {
    margin: 0;	
    padding: 8px 0 8px 0;
}

.gbComment p {
    margin: 6px 0;
}

#gsSidebar .giThumbImage {
    margin: 4px 0;
}

/*      #gsSearchContents  */

/*      override the normal title clear so as to wrap information on the right of the thumbnail */

#gsSearchContents .gbItemImage .giTitle {
	margin: 0;
	padding: 0;
}

#gsSearchContents .gbItemImage img, #gsSearchContents .gbItemAlbum img {
    border: 0px;
}

#gsSearchContents .giTitle {
    margin: 0 14px;
    padding: 0;
}

/*      #gsAdminContents	*/

#gsAdminContents .gbAdmin {
	clear: both;
	float: left;
	width: 97%;
	margin: 0;
	padding: 8px 14px;
}

.gbButtons {
    padding: 8px;
}

input[type=submit] {
    margin: 0 3px 0 0;
    padding: 1px 3px;
}

.gbButtons input {
    margin: 8px 5px 0 5px;
}


/*      for tabular data */
#gsAdminContents .gbDataTable {
	margin: 4px 0 4px -4px;
}

/*      Status section  */

/*      error inside a gsStatus section */

#gsStatus {
    margin: 4px 0 0 4px;
}

#gsStatus .giEmpty {
    margin: 0 0 400px 0;
}

/*      Status inside a gsStatus section */


/* ******************************************************************************************
 * ITEMS
 * Category 4: item and span definitions		 
 * declares styles for items that are defined globally or  
 * with respect to boxes. items defined uniquely per	   
 * section are in the BOXES part of this file.		 
 */

/*      Global / Defaults */

.giMarkupBar input {
	margin: 0;
	padding: 0px;
}

.giDescription {
	display: block;
	margin: 0 0 6px 0;
	padding: 0;
}

.giInfo {
	display: block;
	margin: 0;
	padding: 8px 0;
}

.giInfo li {
    margin: 0;
    padding: 0;
    background-image: none;
}

/*      horizontal link styles page navigations */
.giHorizontalLinks, .giHorizontalLinksLeft {
	padding: 2px 8px;
}

.gbNavBar .giHorizontalLinks {
    float: right;
 }

.giHorizontalLinks li, .giHorizontalLinksLeft li {
	display: inline;
	padding: 0 4px;
	background-image: none;
 }
 
.giHorizontalLinksLeft {
    float: left;
    padding-left: 0;
 }

.gbExif .giHorizontalLinks, .gbExif li, .gbComment .giHorizontalLinks, .gbComment li {
    margin: 4px 0;
    padding: 0 2px 0 0;
    background-image: none;
}


/*  thumbnails */
.giThumbImage, .giThumbMovie, .giThumbOther {
	margin: 0 0 12px 0;
}

.giThumbImage img { }

select.giActionSelect {
	display: block;
	margin-top: 4px;
}

/*      .giThumbBorder {}
...giBorders...
discused the options of generating a table-based border (ie_test) and alistapart.com http://www.alistapart.com/articles/customcorners/ method. Defer until completion of initial theme.
*/

.giPageNumber {
	padding: 8px;
}

/*	  Form elements */

.giFormButton, .giFormInput {
	margin-top: 4px;
	margin-bottom: 4px;
}

.giFormCheckbox { }

/* Status class local error, warning and success */

.giError {
	clear: both;
}

.giWarning {
	clear: both;
}

.giSuccess {
	clear: both;
}

/*	  .gbTopFlag   */

/*	  .gbBottomFlag   */

.gbBottomFlag .giHorizontalLinks {
	padding: 0 4px;
}

/*	  .gbDataEntry */

.gbDataEntry .giFormButton {
	margin-top: 0;
	margin-bottom: 0;
	padding-top: 0;
	padding-bottom: 0;
}

.gbAdmin p.giDescription {
    width: 500px;
}

/*   Search page and form styles   */

.giMarkupBar {
    margin: 4px 0;
}

#gsSearchContents .gbAdmin {
    margin: 12px;
}

#gsSearchContents ul.giSearchCheck {
    margin: 16px 0;
    padding: 0;
}

#gsSearchContents ul.giSearchCheck li {
    margin: 0;
    padding: 0 8px 0 0;
    display: inline;
    background-image: none;
}
