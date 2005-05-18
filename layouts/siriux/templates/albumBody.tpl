{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{include file="gallery:layouts/siriux/templates/pathbar.tpl"}

<div class="gbBlock">
  <h2> {$layout.item.title|markup} </h2>
  <p class="giDescription"> {$layout.item.description|markup} </p>

  {if (sizeof($layout.children) == 0)}
    <p class="giDescription"> {g->text text="This album is empty."} </p>
  {else}

  {* Albums (in Root Album) *}
  {assign var="currentYear" value="0"}

  <div class="gallery-albums">
    {foreach from=$layout.children item=child}
      {if $child.canContainChildren}
	{if !$layout.parents}
	  {capture name=year}{g->date format="%Y" timestamp=$child.originationTimestamp}{/capture}
	  {if $smarty.capture.year != $currentYear}
	    <h3 class="gcBorder1"> {$smarty.capture.year} </h3>
	    {assign var="currentYear" value=$smarty.capture.year}
	  {/if}
	{/if}

	<div class="gallery-album">
	  <div class="gallery-thumb">
	    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$child.id`"}">
	      {if isset($child.thumbnail)}
		{g->image item=$child image=$child.thumbnail class="gcBorder1"}
	      {else}
		{g->text text="no thumbnail"}
	      {/if}
	    </a>
	  </div>

	  <h4>
	    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$child.id`"}">
	      {$child.title|default:$child.pathComponent|markup}
	    </a>
	  </h4>

	  <div class="meta">
	    {if ($child.childCount > 0)}
	      {$child.descendentCount} {g->text text="Images"}
	    {/if}
	  </div>

	  <p class="giDescription">
	    {if isset($child.summary)}
	      {$child.summary|entitytruncate:256|markup}
	    {/if}
	  </p>
	</div>
      {/if}
    {/foreach}
  </div>

  {* Non-Album Items (Photos) *}
  <div class="gallery-items">
    {foreach from=$layout.children item=child}
      {if !$child.canContainChildren}
	<div class="gallery-thumb">
	  <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$child.id`"}">
	    {if isset($child.thumbnail)}
	      {g->image item=$child image=$child.thumbnail class="gcBorder1"}
	    {else}
	      {g->text text="no thumbnail"}
	    {/if}
	  </a>
	</div>
      {/if}
    {/foreach}
  </div>
  {/if}
</div>
<br style="clear: both"/>

{include file="gallery:layouts/siriux/templates/itemNavigator.tpl"}

{* System Links only on the root page *}
{if !$layout.parents}
  {include file="gallery:layouts/siriux/templates/systemLinks.tpl"}
{/if}

{* Item Links *}
{include file="gallery:layouts/siriux/templates/itemLinks.tpl"}
