{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to render.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html><head><title></title>
{g->style}
</head>
<body onLoad="window.parent.image_loaded()">
<table width="100%" height="100%"><tr>
<td align="center" valign="middle">{g->image item=$layout.item image=$layout.image}</td>
</tr></table>
</body></html>
