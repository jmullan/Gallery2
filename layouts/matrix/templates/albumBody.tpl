<div id="gsHeader">
  <div class="gbTitleBanner">
    <!-- img banner -->
  </div>

  {include file="layouts/matrix/templates/pathbar.tpl"}
</div>

<div id="gsAlbumContents">
  <div class="gbTopFlag">
    <div class="gbTitleBanner">
      <div class="giTitle">
	{$layout.item.title|markup}
      </div>
      <div class="giDescription">
	{$layout.item.description|markup}
      </div>
    </div>

    <div class="giInfo">
      <span>
	{capture name=creationTimestamp}
	{g->date timestamp=$layout.item.creationTimestamp}
	{/capture}
	{g->text text="Date: %s" arg1=$smarty.capture.creationTimestamp}
      </span>

      <span>
	{g->text one="Size: %d item" 
	         many="Size: %d items" 
	         count=$layout.totalChildCount 
	         arg1=$layout.totalChildCount}
	{g->text one="(%d item total)"
	         many="(%d items total)"
	         count=$layout.totalDescendentCount
	         arg1=$layout.totalDescendentCount}
      </span>
	
      <span>
	{g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
      </span>
    </div>

    {include file="layouts/matrix/templates/itemNavigator.tpl"}

    <div class="gsSpacer">
      &nbsp;
    </div>
  </div>
      
  <div class="gsSpacer">
    &nbsp;
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

    <div class="giTitle">
      {if $child.canContainChildren}
      {g->text text="Album: %s" arg1=$child.title|default:$child.pathComponent}
      {else}
      {$child.title|default:$child.pathComponent|markup}
      {/if}
    </div>

    <div class="giDescription">
      {$child.summary|truncate:256|markup}
    </div>

    <div class="giInfo">
      <span>
	{capture name=modificationTimestamp}
	{g->date timestamp=$child.modificationTimestamp}
	{/capture}
	{g->text text="Date: %s" arg1=$smarty.capture.modificationTimestamp}
      </span>

      {if ($child.canContainChildren && $layout.showAlbumOwner) || (!$child.canContainChildren && $layout.showImageOwner)}
      <span>
	{g->text text="Owner: %s" arg1=$layout.owners[$child.ownerId].fullName|default:$owner.userName}
      </span>
      {/if}

      {if ($child.childCount > 0) }
      <span>
	{g->text one="Size: %d item"
	many="Size: %d items"
	count=$child.childCount
	arg1=$child.childCount}
	{g->text one="(%d item total)"
	many="(%d items total)"
	count=$child.descendentCount
	arg1=$child.descendentCount}
      </span>
      {/if}

      {if ($layout.viewCounts[$child.id] > 0) }
      <span>
	{g->text one="Viewed: %d time"
	many="Viewed: %d times"
	count=$layout.viewCounts[$child.id]
	arg1=$layout.viewCounts[$child.id]}
      </span>
      {/if}
    </div>
  </div>

  {counter}
  {if ($child.canContainChildren || ($childrenInColumnCount % $layout.columnSize == 0))}
  <div class="gsSpacer">
    &nbsp;
  </div>
  {counter start=0 print=no assign=childrenInColumnCount}
  {/if}
  {foreachelse}
  <div>
    {g->text text="This album is empty"}
  </div>
  {/foreach}

  <div class="gsSpacer">
    &nbsp;
  </div>

  {if !empty($layout.moduleItemDetailFiles)}
  {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
  {include file=$detailFile l10Domain="modules_$moduleId"}
  {/foreach}
  {/if}

  <div class="gbBottomFlag">
    <div class="giActionSelect">
      {if isset($layout.moduleItemLinks[$layout.item.id])}
      <select onchange="javascript:if (this.value) location.href=this.value">
	<option label="{g->text text="&laquo; album actions &raquo;"}" value="">{g->text text="&laquo; album actions &raquo;"}</option>
        {foreach from=$layout.moduleItemLinks[$layout.item.id] item=link}
        <option label="{$link.text}" value="{$link.url}">{$link.text}</option>
        {/foreach}
      </select>
      {/if}
    </div>

    <div class="giHorizontalLinks">
      <div class="giTitle">
	{g->text text="Page"}
      </div>
      
      {assign var="lastPage" value=0}
      {foreach name=jumprange from=$layout.jumprange item=page}
      {if ($page - $lastPage >= 2)}
      <span>
	{if ($page - $lastPage == 2)}
	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`" arg3="page=`$page-1`"}">
	  {$page-1}
	</a>
	{else}
	...
	{/if}
      </span>
      {/if}
	  
      {if ($layout.currentPage == $page)}
      <span>
	{$page}
      </span>
      {else}
      <span> 
	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`" arg3="page=$page"}">
	  {$page}
	</a>
      </span>
      {/if}
      {assign var="lastPage" value=$page}
      {/foreach}
    </div>
  </div>
</div>

{include file="layouts/matrix/templates/sidebar.tpl"}
