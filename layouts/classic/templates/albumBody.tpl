{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{include file="gallery:layouts/classic/templates/pathbar.tpl" l10Domain="layouts_classic"}

<table width="100%" cellspacing="0" cellpadding="0">
  <tr valign="top"><td id="gsSidebarCol">
    {include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"}
  </td><td>

  <div id="gsContent" class="gcBorder1">
    <div class="gbBlock gcBackground1">
      <table width="100%">
	<tr><td style="width: 40%">
	  {if !empty($layout.item.title)}
	    <h2> {$layout.item.title|markup} </h2>
	  {/if}
	  {if !empty($layout.item.description)}
	    <p class="giDescription">
	      {$layout.item.description|markup}
	    </p>
	  {/if}
	</td><td>
	  <p class="giInfo">
	    {capture name=originationTimestamp}
	      {g->date timestamp=$layout.item.originationTimestamp}
	    {/capture}
	    {g->text text="Date: %s" arg1=$smarty.capture.originationTimestamp}
	    <br/>

	    {g->text one="Size: %d item" many="Size: %d items"
		     count=$layout.childCount arg1=$layout.childCount}
	    {if $layout.descendentCount > $layout.childCount}
	    <span style="white-space: nowrap">
	      {g->text one="(%d item total)" many="(%d items total)"
		       count=$layout.descendentCount arg1=$layout.descendentCount}
	    </span>
	    {/if}
	    <br/>
	    {if $layout.params.showAlbumOwner}
	      {g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
	      <br/>
	    {/if}
	  </p>
	</td></tr>
      </table>
    </div>

    {include file="gallery:layouts/classic/templates/itemNavigator.tpl" l10Domain="layouts_classic"}

    {if !count($layout.children)}
    <div class="gbBlock giDescription">
      {g->text text="This album is empty."}
    </div>
    {else}

    {assign var="childrenInColumnCount" value=0}
    <div class="gbBlock">
    <table id="gsThumbMatrix" width="100%"><tr valign="top">
      {foreach from=$layout.children item=child}

      {* Move to a new row *}
      {if ($childrenInColumnCount == $layout.params.columns)}
	</tr><tr valign="top">
	{assign var="childrenInColumnCount" value=0}
      {/if}

      {assign var=childrenInColumnCount value="`$childrenInColumnCount+1`"}
      <td class="{if $child.canContainChildren}giAlbumCell gcBackground1{else}giItemCell{/if}">
	{if $child.canContainChildren}
	  {assign var=frameType value="albumFrame"}
	{else}
	  {assign var=frameType value="itemFrame"}
	{/if}
	{if isset($layout.$frameType) && isset($child.thumbnail)}
	  {g->block type="imageframe" frame=$layout.$frameType}
	    <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$child.id`"}">
	      {g->image item=$child image=$child.thumbnail id="%ID%" class="%CLASS%"}
	    </a>
	  {/g->block}
	{else}
	  <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$child.id`"}">
	    {if isset($child.thumbnail)}
	      {g->image item=$child image=$child.thumbnail class="giThumbnail"}
	    {else}
	      {g->text text="no thumbnail"}<br/>
	    {/if}
	  </a>
	{/if}
      </td><td>

	{if !empty($child.title)}
	  <p class="giTitle">
	    {$child.title|markup}
	  </p>
	{/if}

	{if !empty($child.summary)}
	  <p class="giDescription">
	    {$child.summary|entitytruncate:256|markup}
	  </p>
	{/if}

	<p class="giInfo">
	  {capture name=childTimestamp}{g->date timestamp=$child.originationTimestamp}{/capture}
	  {g->text text="Date: %s" arg1=$smarty.capture.childTimestamp}
	  <br/>

	  {if ($child.canContainChildren && $layout.params.showAlbumOwner)
	   || (!$child.canContainChildren && $layout.params.showImageOwner)}
	    {g->text text="Owner: %s" arg1=$layout.ownerMap[$child.ownerId].fullName|default:$layout.ownerMap[$child.ownerId].userName}
	    <br/>
	  {/if}

	  {if ($child.canContainChildren && $child.childCount > 0)}
	    {g->text one="Size: %d item" many="Size: %d items"
		     count=$child.childCount arg1=$child.childCount}
	    {if $child.descendentCount > $child.childCount}
	    <span style="white-space: nowrap">
	      {g->text one="(%d item total)" many="(%d items total)"
		       count=$child.descendentCount arg1=$child.descendentCount}
	    </span>
	    {/if}
	    <br/>
	  {/if}

	  {if ($child.viewCount > 0)}
	    {g->text text="Views: %d" arg1=$child.viewCount}
	    <br/>
	  {/if}

	  {foreach from=$child.itemSummaries item=summary}
	    {$summary}
	    <br/>
	  {/foreach}
	</p>

	{if !empty($child.itemLinks)}
	  <select onchange="{literal}if (this.value) { newLocation = this.value; this.options[0].selected = true; location.href= newLocation; }{/literal}">
	    <option label="{if $child.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}" value="">{if $child.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}</option>

	    {foreach from=$child.itemLinks item=link}
	      <option label="{$link.text}" value="{g->url param=$link.params}">{$link.text}</option>
	    {/foreach}
	  </select>
	{/if}
      </td>

      {if $layout.params.showSubalbums}
      <td class="tree">
	{if !empty($layout.tree[$child.id])}
	  <h4> {g->text text="Subalbums:"} </h4>
	  <ul>
	    {assign var="empty" value=""}
	    {assign var="depth" value=0}
	    {foreach from=$layout.tree[$child.id] item=node}
	      {if $node.depth > $depth}
		<li><ul>
	      {elseif $node.depth < $depth}
		{$empty|indent:$depth-$node.depth:"</ul></li>"}
	      {/if}
	      {assign var="depth" value=$node.depth}
	      <li>
		<a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$node.id`"}">
		{$layout.treeItems[$node.id].title|default:$layout.treeItems[$node.id].pathComponent|markup}
		</a>
	      </li>
	    {/foreach}
	    {$empty|indent:$depth:"</ul></li>"}
	  </ul>
	{/if}
      </td>
      {/if}
      {/foreach}

      {* flush the rest of the row with empty cells *}
      {section name="flush" start=$childrenInColumnCount loop=$layout.params.columns}
	<td>&nbsp;</td>
      {/section}
    </tr></table>
    </div>
    {/if}

    {if !empty($layout.itemDetailFiles)}
      {foreach from=$layout.itemDetailFiles key=moduleId item=detailFile}
	{include file="gallery:$detailFile" l10Domain="modules_$moduleId"}
      {/foreach}
    {/if}

    {include file="gallery:layouts/classic/templates/itemNavigator.tpl" l10Domain="layouts_classic"}

    {if !empty($layout.jumprange)}
    <div id="gsPages" class="gbBlock gcBackground1">
      {g->text text="Page:"}
      {assign var="lastPage" value=0}
      {foreach name=jumprange from=$layout.jumprange item=page}
        {if ($page - $lastPage >= 2)}
          <span>
          {if ($page - $lastPage == 2)}
            <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$layout.item.id`"
             arg3="page=`$page-1`"}">{$page-1}</a>
          {else}
            ...
          {/if}
          </span>
        {/if}

        <span>
        {if ($layout.currentPage == $page)}
          {$page}
        {else}
          <a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$layout.item.id`"
           arg3="page=$page"}">{$page}</a>
        {/if}
        </span>
        {assign var="lastPage" value=$page}
      {/foreach}
    </div>
    {/if}
  </div>
  </td></tr>
</table>
