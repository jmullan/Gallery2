{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
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
		<div class="buttonShowSidebar"><a href="javascript: slideIn('sidebar')" title="Show Sidebar"></a></div>
	      </td>
	      {if (isset($links) || isset($theme.itemLinks))}
		{if !isset($links)}{assign var="links" value=$theme.itemLinks}{/if}

		{foreach from=$links item=link}
		  {if $link.moduleId == "cart"}
		  <td class="gsActionIcon">
		    <div class="buttonCart"><a href="{g->url params=$link.params}" title="{$link.text}"></a></div>
		  </td>
		  {elseif $link.moduleId == "comment"}
		    {if $link.params.view == "comment.AddComment" }
		    <td class="gsActionIcon">
		      <div class="buttonAddComment"><a href="{g->url params=$link.params}" title="{$link.text}"></a></div>
		    </td>
		    {elseif $link.params.view == "comment.ShowAllComments"}
		    <td class="gsActionIcon">
		      <div class="buttonViewComments"><a href="{g->url params=$link.params}" title="{$link.text}"></a></div>
		    </td>
		    {/if}
		  {elseif $link.moduleId == "slideshow"}
		  <td class="gsActionIcon">
		    <div class="buttonViewSlideshow"><a href="{g->url params=$link.params}" title="{$link.text}"></a></div>
		  </td>
		  {/if}
		{/foreach}
	      {/if}
	    </tr>
	  </table>
	</div>

	{if empty($theme.parents)}
	{/if}

	{if !empty($theme.navigator)}
	<div class="gbNavigator">
	  {* {g->block type="core.Navigator" navigator=$theme.navigator reverseOrder=true} *}
	  {g->theme include="navigator.tpl"}
	</div>
	{/if}

	<table width="100%" cellspacing="0" cellpadding="0">
	  <tr>
	    <td width="30%" valign="top">
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
			    showSize=true
			    showOwner=true
			    class="giInfo"}
		</div>
		<div class="gbBlock">
		  {* Show the album blocks chosen for this theme *}
		  {foreach from=$theme.params.albumBlocks2 item=block}
		    {g->block type=$block.0 params=$block.1}
		  {/foreach}
		</div>
	      </div>
	    </td>
	    <td>
	      {if !count($theme.children)}
	      <div class="giDescription gbEmptyAlbum">
		<h3 class="emptyAlbum">
		  {g->text text="This album is empty."}
		  {if isset($theme.permissions.core_addDataItem)}
		  <br/>
		  <a href="{g->url arg1="view=core.ItemAdmin" arg2="subView=core.ItemAdd" arg3="itemId=`$theme.item.id`"}">
		    {g->text text="Add a photo!"}
		  </a>
		  {/if}
		</h3>
	      </div>
	      {else}
	      {assign var="childrenInColumnCount" value=0}
	      <div class="gsContentAlbum">
		<table id="gsThumbMatrix" width="100%">
		  <tr valign="top">
		    {foreach from=$theme.children item=child}

		    {* Move to a new row *}
		    {if ($childrenInColumnCount == $theme.params.columns)}
		  </tr>
		  <tr valign="top">
		    {assign var="childrenInColumnCount" value=0}
		    {/if}

		    {assign var=childrenInColumnCount value="`$childrenInColumnCount+1`"}
		    <td class="{if $child.canContainChildren}giAlbumCell{else}giItemCell{/if}"
			style="width: {$theme.columnWidthPct}%">
		      {if ($child.canContainChildren || $child.entityType == 'GalleryLinkItem')}
		      {assign var=frameType value="albumFrame"}
		      {else}
		      {assign var=frameType value="itemFrame"}
		      {/if}
		      <div>
			{if isset($theme.params.$frameType) && isset($child.thumbnail)}
			{g->container type="imageframe.ImageFrame" frame=$theme.params.$frameType
				      width=$child.thumbnail.width height=$child.thumbnail.height}
			  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$child.id`"}">
			    {g->image id="%ID%" item=$child image=$child.thumbnail class="%CLASS% giThumbnail"}
			  </a>
			{/g->container}
			{elseif isset($child.thumbnail)}
			  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$child.id`"}">
			    {g->image item=$child image=$child.thumbnail class="giThumbnail"}
			  </a>
			{else}
			  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$child.id`"}" class="giMissingThumbnail">
			    {g->text text="no thumbnail"}
			  </a>
			{/if}
		      </div>

		      {g->block type="core.ItemLinks" item=$child links=$child.itemLinks}

		      {if !empty($child.title)}
			{if $child.canContainChildren}
			<table cellpadding="0" cellspacing="0">
			  <tr>
			    <td class="giTitleIcon">
			      <img src="{g->url href='themes/carbon/images/'}album.gif" alt=""/>
			    </td>
			    <td>
			      <p class="giTitle">{g->text text="%s" arg1=$child.title|markup}</p>
			    </td>
			  </tr>
			</table>
			{else}
			<p class="giTitle">{$child.title|markup}</p>
			{/if}
		      {/if}

		      {if !empty($child.summary)}
		      <p class="giDescription">
			{$child.summary|markup|entitytruncate:256}
		      </p>
		      {/if}

		      {if ($child.canContainChildren && $theme.params.showAlbumOwner) ||
			  (!$child.canContainChildren && $theme.params.showImageOwner)}
		      {assign var="showOwner" value=true}
		      {else}
		      {assign var="showOwner" value=false}
		      {/if}
		      {g->block type="core.ItemInfo"
				item=$child
				showDate=true
				showOwner=$showOwner
				showSize=true
				showViewCount=true
				showSummaries=true
				class="giInfo"}
		    </td>
		    {/foreach}

		    {* flush the rest of the row with empty cells *}
		    {section name="flush" start=$childrenInColumnCount loop=$theme.params.columns}
		    <td>&nbsp;</td>
		    {/section}
		  </tr>
		</table>
	      </div>
	      {/if}
	    </td>
	  </tr>
	</table>

	{if !empty($theme.navigator)}
	<div class="gbNavigator">
	  {* {g->block type="core.Navigator" navigator=$theme.navigator reverseOrder=true} *}
	  {g->theme include="navigator.tpl"}
	</div>
	{/if}

	{* g->block type="core.GuestPreview" class="gbBlock" *}

	{* Our emergency edit link, if the user all blocks containing edit links *}
	{g->block type="core.EmergencyEditItemLink" class="gbBlock"
		  checkSidebarBlocks=true
		  checkAlbumBlocks=true}

	{* Show any other album blocks (comments, etc) *}
	{foreach from=$theme.params.albumBlocks item=block}
	  {g->block type=$block.0 params=$block.1}
	{/foreach}
      </div>
    </td>
  </tr>
</table>
