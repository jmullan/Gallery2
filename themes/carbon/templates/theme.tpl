{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="{g->language}">
  <head>
    {* Let Gallery print out anything it wants to put into the <head> element *}
    {g->head}

    {if $theme.pageType == 'album' || $theme.pageType == 'photo'}
    <meta name="keywords" content="{$theme.item.keywords}" />
    <meta name="description" content="{$theme.item.description|markup:strip}" />
    {/if}

    {* If Gallery doesn't provide a header, we use the album/photo title (or filename) *}
    {if empty($head.title)}
      <title>{$theme.item.title|default:$theme.item.pathComponent|markup:strip}</title>
    {/if}

    {* Include this theme's style sheet and javascript *}
    <link rel="stylesheet" type="text/css" href="{g->theme url="theme.css"}"/>
    <script type="text/javascript" src="{g->url href='themes/carbon/theme.js'}"></script>
  </head>
  <body class="gallery">
    <div {g->mainDivAttributes}>
      {*
       * Some module views (eg slideshow) want the full screen.  So for those, we don't draw
       * a header, footer, navbar, etc.  Those views are responsible for drawing everything.
       *}
      {if $theme.useFullScreen}
	{include file="gallery:`$theme.moduleTemplate`" l10Domain=$theme.moduleL10Domain}
      {else}
      <div id="gsHeader">
	<table width="100%" cellspacing="0" cellpadding="0">
	  <tr>
	    <td align="left" valign="top" width="50%">
	      <a href="{g->url}"><img src="{g->url href="images/galleryLogo_sm.gif"}"
	       width="107" height="48" alt=""/></a>
	    </td>
	    <td align="right" valign="top">
	      {g->theme include="ads.tpl"}
	    </td>
	  </tr>
	</table>
      </div>

      <div id="gsNavBar" class="gcBorder1">
	<div class="gbSystemLinks">
	  {if !empty($theme.params.extraLink) && !empty($theme.params.extraLinkUrl)}
	  <span class="block-core-SystemLink">
	    <a href="{$theme.params.extraLinkUrl}">{$theme.params.extraLink}</a>
	  </span>
	  {g->text text="&laquo;"}
	  {/if}
	  {g->block type="core.SystemLinks"
		    order="core.SiteAdmin core.YourAccount core.Login core.Logout"
		    separator="&laquo;"
		    othersAt=4}
	  <span class="block-core-SystemLink">
	    <a href="javascript: toggleSidebar('sidebar')">{g->text text="Sidebar"}</a>
	  </span>
	</div>

	<div class="gbBreadCrumb">
	  {g->block type="core.BreadCrumb" separator="&raquo;"}
	</div>
      </div>

      {* Include the appropriate content type for the page we want to draw. *}
      {if $theme.pageType == 'album'}
	{g->theme include="album.tpl"}
      {elseif $theme.pageType == 'photo'}
	{g->theme include="photo.tpl"}
      {elseif $theme.pageType == 'admin'}
	{g->theme include="admin.tpl"}
      {elseif $theme.pageType == 'module'}
	{g->theme include="module.tpl"}
      {elseif $theme.pageType == 'progressbar'}
	{g->theme include="progressbar.tpl"}
      {/if}

      <div id="gsFooter" class="gcBorder1">
	<table width="100%" cellspacing="0" cellpadding="0">
	  <tr>
	    <td align="left" width="50%">
	      {g->logoButton type="validation"}
	      {g->logoButton type="gallery2"}
	      {g->logoButton type="gallery2-version"}
	      {g->logoButton type="donate"}
	      <a href="http://www.mincel.com/carbon"><img src="{g->theme url="images/carbon.gif"}"
	       alt="{g->text text="Carbon"} {$theme.params._version}"
	       title="{g->text text="Carbon"} {$theme.params._version}"
	       style="border-style: none" width="80" height="15"/></a>
	    </td>
	    <td align="right">
	      {strip}
	      {if !empty($theme.params.copyright)}
		{$theme.params.copyright}
	      {/if}
	      {/strip}
	      {g->block type="core.GuestPreview"}
	    </td>
	  </tr>
	</table>
      </div>
      {/if}  {* end of full screen check *}
    </div>

    {*
     * Give Gallery a chance to output any cleanup code, like javascript that needs to be run
     * at the end of the <body> tag.  If you take this out, some code won't work properly.
     *}
    {g->trailer}

    {* Put any debugging output here, if debugging is enabled *}
    {g->debug}
  </body>
</html>
