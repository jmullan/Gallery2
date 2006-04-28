{*
 * $Revision: 1.5 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<h2>{$theme.item.title|markup}</h2>

{if !count($theme.children)}
  <p><strong>{g->text text="This album is empty."}</strong></p>
  <p><a href="{g->url arg1="view=core.ItemAdmin" arg2="subView=core.ItemAdd"
		      arg3="itemId=`$theme.item.id`"}">{g->text text="Add a photo!"}</a></p>
{else}
  <div class="gallery-albums">
    {assign var="currentYear" value=""}
    {foreach from=$theme.children item=child}

	{* Year separator *}
	{if $theme.params.groupByYear}
	  {capture name=year}{g->date format="%Y" timestamp=$child.originationTimestamp}{/capture}
	  {if $smarty.capture.year != $currentYear}
	    <h3 style="clear: both;">{$smarty.capture.year}</h3>
	    {assign var="currentYear" value=$smarty.capture.year}
	  {/if}
	{/if}

	{if $child.canContainChildren}
	  <div class="gallery-album">
	    <div class="gallery-thumb">
		<a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$child.id`"}">
		{if isset($child.thumbnail)}
		  {g->image item=$child image=$child.thumbnail}
		{else}
		  {g->text text="no thumbnail"}
		{/if}
		</a>
	    </div>

	    <h4><a href="{g->url arg1="view=core.ShowItem"
	    arg2="itemId=`$child.id`"}">{$child.title|default:$child.pathComponent|markup}</a></h4>

	    <div class="meta">
	      {if ($child.childCount > 0)}
		{g->text text="%d Images" arg1=$child.descendentCount}
	      {/if}
	    </div>

	    <p>{if isset($child.summary)}{$child.summary|entitytruncate:256|markup}{/if}</p>
	  </div>
	{/if}
    {/foreach}
    <div class="clear"></div>
  </div>

  <div class="gallery-items">
    {foreach from=$theme.children item=child}
      {if !$child.canContainChildren}
	<div class="gallery-thumb">
	  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$child.id`"}">
	  {if isset($child.thumbnail)}
	    {g->image item=$child image=$child.thumbnail}
	  {else}
	    {g->text text="no thumbnail"}
	  {/if}
	  </a>
	</div>
      {/if}
    {/foreach}
    <div class="clear"></div>
  </div>
{/if}

<br style="clear: both;" />

{* Navigator *}
{if $theme.totalPages > 1}
{g->block type="core.Navigator" navigator=$theme.navigator prefix="&laquo; " suffix=" &raquo;"
	  currentPage=$theme.currentPage totalPages=$theme.totalPages}
{/if}

{* Description *}
{if !empty($theme.item.description)}
  <hr/>
  <p>{$theme.item.description|markup}</p>
{/if}


{* Show any other album blocks (comments, etc) *}
{foreach from=$theme.params.albumBlocks item=block}
  {g->block type=$block.0 params=$block.1}
{/foreach}


{* System Links only on the root page *}
{if empty($theme.parents)}
  <div class="gbSystemLinks">
    {g->block type="core.SystemLinks"
	      order="core.SiteAdmin core.YourAccount core.Login core.Logout"
	      othersAt=4}
  </div>
{/if}

{* Guest preview mode *}
{g->block type="core.GuestPreview" class="gbBlock"}

{* Our emergency edit link, if the user all blocks containing edit links *}
{g->block type="core.EmergencyEditItemLink" class="gbBlock" checkAlbumBlocks=true}

