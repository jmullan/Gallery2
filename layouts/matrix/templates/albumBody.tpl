{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to albumBody.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsHeader">
  <div class="gbTitleBanner">
    <!-- img banner -->
  </div>
</div>

{include file="gallery:layouts/matrix/templates/sidebar.tpl"}

{include file="gallery:layouts/matrix/templates/pathbar.tpl"}

<div id="gsAlbumContents">
  {include file="gallery:layouts/matrix/templates/itemNavigator.tpl"}
  <div class="gbTopFlag">
    <div class="gbTitleBanner">
      <h1 class="giTitle">
	{$layout.item.title|markup}
      </h1>
      <p class="giDescription">
	{$layout.item.description|markup}
      </p>
    </div>

    <div class="giInfo">
      <ul>
        <li>
	{capture name=creationTimestamp}
	{g->date timestamp=$layout.item.creationTimestamp}
	{/capture}
	{g->text text="Date: %s" arg1=$smarty.capture.creationTimestamp}
        </li>

        <li>
	{g->text one="Size: %d item" 
	         many="Size: %d items" 
	         count=$layout.totalChildCount 
	         arg1=$layout.totalChildCount}
	{g->text one="(%d item total)"
	         many="(%d items total)"
	         count=$layout.totalDescendentCount
	         arg1=$layout.totalDescendentCount}
        </li>
	
        <li>
	{g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
        </li>
      </ul>
    </div>
  </div>

  {counter start=0 print=no assign=childrenInColumnCount}
  {foreach from=$layout.children item=child}
  <div class="{if $child.canContainChildren}gbItemAlbum{else}gbItemImage{/if}">
    <div class="giThumbImage">
      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$child.id`"}">
	{if isset($child.thumbnail)}
	{g->image item=$child image=$child.thumbnail}
	{else}
	{g->text text="no thumbnail"}
	{/if}
      </a>

      {if !empty($layout.moduleItemLinks[$child.id])}
      <div class="giActionSelect">
	<select onchange="javascript:if (this.value) location.href=this.value">
	  <option label="{if $child.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}" value="">{if $child.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}</option>
	  
	  {foreach from=$layout.moduleItemLinks[$child.id] item=link}
	  <option label="{$link.text}" value="{$link.url}">{$link.text}</option>
	  {/foreach}
        </select>
      </div>
      {/if}
    </div>

    <h2 class="giTitle">
      {if $child.canContainChildren}
      {g->text text="Album: %s" arg1=$child.title|default:$child.pathComponent}
      {else}
      {$child.title|default:$child.pathComponent|markup}
      {/if}
    </h2>

    <p class="giDescription">
      {$child.summary|truncate:256|markup}
    </p>

    <ul class="giInfo">
      <li>
	{capture name=modificationTimestamp}
	{g->date timestamp=$child.modificationTimestamp}
	{/capture}
	{g->text text="Date: %s" arg1=$smarty.capture.modificationTimestamp}
      </li>

      {if ($child.canContainChildren && $layout.showAlbumOwner) || (!$child.canContainChildren && $layout.showImageOwner)}
      <li>
	{g->text text="Owner: %s" arg1=$layout.owners[$child.ownerId].fullName|default:$owner.userName}
      </li>
      {/if}

      {if ($child.childCount > 0) }
      <li>
	{g->text one="Size: %d item"
	many="Size: %d items"
	count=$child.childCount
	arg1=$child.childCount}
	{g->text one="(%d item total)"
	many="(%d items total)"
	count=$child.descendentCount
	arg1=$child.descendentCount}
      </li>
      {/if}

      {if ($layout.viewCounts[$child.id] > 0) }
      <li>
	{g->text one="Viewed: %d time"
	many="Viewed: %d times"
	count=$layout.viewCounts[$child.id]
	arg1=$layout.viewCounts[$child.id]}
      </li>
      {/if}
    </ul>
  </div>

  {counter}
  {if ($child.canContainChildren || ($childrenInColumnCount % $layout.columnSize == 0))}
  {counter start=0 print=no assign=childrenInColumnCount}
  {/if}
  {foreachelse}
  <div>
    {g->text text="This album is empty"}
  </div>
  {/foreach}

  {if !empty($layout.moduleItemDetailFiles)}
  {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
  {include file="gallery:$detailFile" l10Domain="modules_$moduleId"}
  {/foreach}
  {/if}

  <div class="gbBottomFlag">
    <div class="giHorizontalLinks">
      <ul>
	  <li>{g->text text="Page:"}</li>
      {assign var="lastPage" value=0}
      {foreach name=jumprange from=$layout.jumprange item=page}
      {if ($page - $lastPage >= 2)}
      <li>
	{if ($page - $lastPage == 2)}
	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`" arg3="page=`$page-1`"}">{$page-1}</a>
	{else}
	...
	{/if}
      </li>
      {/if}
	  
      {if ($layout.currentPage == $page)}
      <li>
	{$page}
      </li>
      {else}
      <li> 
	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`" arg3="page=$page"}">{$page}</a>
      </li>
      {/if}
      {assign var="lastPage" value=$page}
      {/foreach}
      </ul>
    </div>
  </div>
</div>
