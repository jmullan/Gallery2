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
/*
 *  Fade In Script by Louis St-Amour (CSpotkill@CSpotkill.com) based on code from clagnut.com
 */

function CheckIfComplete(ImageId) {
	ImageObj = document.getElementById(ImageId);
	if (!ImageObj.complete) {
		window.setTimeout("CheckIfComplete('"+ImageId+"')", 100);
	}
}

function start() {
	if (SidebarFound = document.getElementById('gsSidebar')) {
		DivColl = SidebarFound.getElementsByTagName('div')
		for (var t = 0; t < DivColl.length; t++) {
			var divClass = DivColl[t].className;
			if (divClass == 'giThumbImage') {
				var anchorCollTemp = DivColl[t].getElementsByTagName('a');
				var imageCollTemp = anchorCollTemp[0].getElementsByTagName('img');
				var theimage = imageCollTemp[0];
				theimage.id = 'gbSidebarImage';
				CheckIfComplete('gbSidebarImage');
				var ImageFromId = document.getElementById('gbSidebarImage');
				setOpacity(ImageFromId, 0);
				ImageFromId.style.visibility = 'visible';
				fadeIn('gbSidebarImage', 0);
			}
		}
	}
	if (SingleImageDiv = document.getElementById('gsSingleImageId')) {
		var imageCollTemp = SingleImageDiv.getElementsByTagName('img');
		var theimage = imageCollTemp[0];
		theimage.id = 'gTheSingleImage';
		CheckIfComplete('gTheSingleImage');
		var ImageFromId = document.getElementById('gTheSingleImage');
		setOpacity(ImageFromId, 0);
		ImageFromId.style.visibility = 'visible';
		fadeIn('gTheSingleImage', 0);
	}
	if (ThumbMatrix = document.getElementById('gbThumbMatrix')) {
		rowColl = ThumbMatrix.getElementsByTagName('tr');
		var ImageNumber = 0;
		for (var r = 0; r < rowColl.length; r++) {
			var itemColl = rowColl[r].getElementsByTagName('td');
			for (var i = 0; i < itemColl.length; i++) {
				var itemClass = itemColl[i].className; 
				if (itemClass == 'gbItemImage' || itemClass == 'gbItemAlbum') {
					ImageNumber++;
					var div = itemColl[i].getElementsByTagName('div');
					var images = div[0].getElementsByTagName('img');
					var theimage = images[0];
					theimage.id = 'gbImageNo' + ImageNumber;
					CheckIfComplete('gbImageNo' + ImageNumber);
					var ImageFromId = document.getElementById('gbImageNo' + ImageNumber);
					setOpacity(ImageFromId, 0);
					ImageFromId.style.visibility = 'visible';
					window.setTimeout("fadeIn('gbImageNo" + ImageNumber + "', 0)", (ImageNumber*400));
		         	//elemColl[i].style[styleName] = styleValue;
				}
			}
		}
	}
}

function fadeIn(objId,opacity) {
  if (document.getElementById) {
    obj = document.getElementById(objId);
    if (opacity <= 100) {
      setOpacity(obj, opacity);
      opacity += 10;
      window.setTimeout("fadeIn('"+objId+"',"+opacity+")", 100);
    }
  }
}

function setOpacity(obj, opacity) {
  opacity = (opacity == 100)?99.999:opacity;
  
  // IE/Win
  obj.style.filter = "alpha(opacity:"+opacity+")";
  
  // Safari<1.2, Konqueror
  obj.style.KHTMLOpacity = opacity/100;
  
  // Older Mozilla and Firefox
  obj.style.MozOpacity = opacity/100;
  
  // Safari 1.2, newer Firefox and Mozilla, CSS3
  obj.style.opacity = opacity/100;
}

if (document.getElementById) {
document.write("<style type='text/css'>.giThumbImage img {visibility:hidden;} #gsSingleImageId img {visibility:hidden;} </style>");
//window.onload = function() {start()}
}