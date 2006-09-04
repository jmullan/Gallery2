{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !empty($theme.imageViews)}
  {assign var="image" value=$theme.imageViews[$theme.imageViewsIndex]}
{/if}
{if !empty($theme.params.sidebarBlocks)}
  {g->theme include="sidebar.tpl"}
{/if}
<table class="gcBackground1" width="100%" cellspacing="0" cellpadding="0">
  <tr valign="top">
    <td>
      <div id="gsContent" class="gcBorder1">
	<div class="gbBlockTop">
	  <table>
	    <tr>
	      <td class="gsActionIcon">
		<div class="buttonShowSidebar"><a href="javascript: slideIn('sidebar')"
		 title="{g->text text="Show Sidebar"}"></a></div>
	      </td>
	      {if (isset($links) || isset($theme.itemLinks))}
		{if !isset($links)}{assign var="links" value=$theme.itemLinks}{/if}

		{foreach from=$links item=link}
		  {if $link.moduleId == "slideshow"}
		  <td class="gsActionIcon">
		    <div class="buttonViewSlideshow"><a href="{g->url params=$link.params}"
		     title="{$link.text}"></a></div>
		  </td>
		  {elseif $link.moduleId == "comment"}
		    {if $link.params.view == "comment.ShowAllComments"}
		    <td class="gsActionIcon">
		      <div class="buttonViewComments"><a href="{g->url params=$link.params}"
		       title="{$link.text}"></a></div>
		    </td>
		    {/if}
		  {/if}
		{/foreach}
	      {/if}
	    </tr>
	  </table>
	</div>

	<div class="gsContentPhoto">
	  <table align="center" cellpadding="0" cellspacing="0">
	    {if $theme.params.navigatorPhotoTop}
	    <tr>
	      <td class="gbNavigatorPhoto">
		<div class="gbNavigator">
		  {* {g->block type="core.Navigator" navigator=$theme.navigator reverseOrder=true} *}
		  {g->theme include="navigator.tpl"}
		</div>
	      </td>
	      <td>
		{g->text text="&nbsp;"}
	      </td>
	    </tr>
	    {/if}
	    <tr>
	      <td>
		<div id="gsImageView" class="gbBlock">
		  {if !empty($theme.imageViews)}
		    {capture name="fallback"}
		    <a href="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$theme.item.id`"
				     forceFullUrl=true forceSessionId=true}">
		      {g->text text="Download %s" arg1=$theme.sourceImage.itemTypeName.1}
		    </a>
		    {/capture}
		    {if ($image.viewInline)}
		      {if isset($theme.photoFrame)}
			{g->container type="imageframe.ImageFrame" frame=$theme.photoFrame
				      width=$image.width height=$image.height}
			  <div id="photo">
			  {g->image id="%ID%" item=$theme.item image=$image
				    fallback=$smarty.capture.fallback class="%CLASS%"}
			  </div>
			{/g->container}
		      {else}
			<div id="photo">
			{g->image item=$theme.item image=$image fallback=$smarty.capture.fallback}
			</div>
		      {/if}
		    {else}
		      {$smarty.capture.fallback}
		    {/if}
		  {else}
		    {g->text text="There is nothing to view for this item."}
		  {/if}
		</div>
	      </td>
	      <td align="left" width="240" valign="top">
		{if $theme.params.showMicroThumbs}
		<div class="gsContentDetail gcBorder1">
		  <div class="gbNavigatorMicroThums">
		    {g->theme include="navigatorMicroThumbs.tpl"}
		  </div>
		</div>
		{/if}
		<div class="gsContentDetail">
		  <div class="gbBlock">
		    {if !empty($theme.item.title)}
		    <h2> {$theme.item.title|markup} </h2>
		    {/if}
		    {if !empty($theme.item.description)}
		    <p class="giDescription">
		      {$theme.item.description|markup}
		    </p>
		    {/if}
		  </div>
		  <div class="gbBlock">
		    {g->block type="core.ItemInfo"
			      item=$theme.item
			      showDate=true
			      showOwner=true
			      class="giInfo"}
		  </div>
		  <div class="gbBlock">
		    {* Show the photo blocks chosen for this theme *}
		    {foreach from=$theme.params.photoUpperBlocks item=block}
		      {g->block type=$block.0 params=$block.1}
		    {/foreach}
		  </div>
		</div>
	      </td>
	    </tr>
	    {if $theme.params.navigatorPhotoBottom}
	    <tr>
	      <td class="gbNavigatorPhoto">
		<div class="gbNavigator">
		  {* {g->block type="core.Navigator" navigator=$theme.navigator reverseOrder=true} *}
		  {g->theme include="navigator.tpl"}
		</div>
	      </td>
	      <td>
		{g->text text="&nbsp;"}
	      </td>
	    </tr>
	    {/if}
	  </table>
	</div>

	{* Download link for item in original format *}
	{if !empty($theme.sourceImage) && $theme.sourceImage.mimeType != $theme.item.mimeType}
	<div class="gbBlock">
	  <a href="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$theme.item.id`"}">
	    {g->text text="Download %s in original format" arg1=$theme.sourceImage.itemTypeName.1}
	  </a>
	</div>
	{/if}

	{* Show any other photo blocks (comments, exif etc) *}
	{foreach from=$theme.params.photoBlocks item=block}
	  {if $block.0 == 'exif.ExifInfo'}
	    <div id="exif" class="gcPopupBackground"
	     style="position:absolute; left:0px; top:0px; padding:1px; visibility:hidden;">
	      <table cellspacing="0" cellpadding="0">
		<tr>
		  <td style="padding-left:5px;">
		    <h2>{g->text text="Exif"}</h2>
		  </td>
		  <td align="right">
		    <div class="buttonClose"><a href="javascript:void(0);"
		     onclick="toggleExif('photo','exif'); return false;"
		     title="{g->text text="Close"}"></a></div>
		  </td>
		</tr>
		<tr>
		  <td colspan="2" class="gcBackground2" style="padding-bottom:5px;">
		    {g->block type=$block.0 params=$block.1}
		  </td>
		</tr>
	      </table>
	    </div>
	  {else}
	    {g->block type=$block.0 params=$block.1}
	  {/if}
	{/foreach}

	{* Our emergency edit link, if the user removes all blocks containing edit links *}
	{g->block type="core.EmergencyEditItemLink" class="gbBlock"
		  checkSidebarBlocks=true checkPhotoBlocks=true}
      </div>
    </td>
  </tr>
</table>
