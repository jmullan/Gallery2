{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}

{include file="gallery:layouts/matrix/templates/pathbar.tpl"}

<div id="gsContents">
  {include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"}

  <div id="gsAlbumContents">
    
    <div class="gbTopFlag">
      <table class="gbTitleBanner">
        <tr>
          <td>
            <h1 class="giTitle">
              {$layout.item.title|default:$layout.item.pathComponent|markup}
            </h1>
            <p class="giDescription">
              {$layout.item.description|markup}
            </p>      
          </td>
  
          <td>
            <ul class="giInfo">
              <li>
                {capture name=itemTimestamp}{g->date timestamp=$layout.item.originationTimestamp}{/capture}
                {g->text text="Date: %s" arg1=$smarty.capture.itemTimestamp}
              </li>
    
              <li>
                {g->text one="Size: %d item" many="Size: %d items"
                         count=$layout.childCount arg1=$layout.childCount}
                {if $layout.descendentCount > $layout.childCount}
                  {g->text one="(%d item total)" many="(%d items total)"
                           count=$layout.descendentCount arg1=$layout.descendentCount}
                {/if}
              </li>    
              {if $layout.showAlbumOwner}
              <li>
                {g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
              </li>
              {/if}
            </ul>
          </td>
        </tr>
      </table>
    </div>
    
    <div class="gbNavBar">
      {include file="gallery:layouts/matrix/templates/itemNavigator.tpl"}
    </div>
    
    {if count($layout.children) > 0}
    {assign var="childrenInColumnCount" value=0}
    <table id="gbThumbMatrix">
      <tr>
        {foreach from=$layout.children item=child}

        {* Move to a new row *}
        {if ($childrenInColumnCount == $layout.columnSize)}
      </tr>
      <tr>
        {assign var="childrenInColumnCount" value=0}
        {/if}

        {assign var=childrenInColumnCount value="`$childrenInColumnCount+1`"}
        <td class="{if $child.canContainChildren}gbItemAlbum{else}gbItemImage{/if}">
          <div class="giThumbImage">
	    {capture name="link"}<a href="{g->url arg1="view=core:ShowItem"
						  arg2="itemId=`$child.id`"}">{/capture}
	    {if $child.canContainChildren}
	      {assign var=frameType value="albumFrame"}
	    {else}
	      {assign var=frameType value="itemFrame"}
	    {/if}
	    {if isset($layout.frame.$frameType) && isset($child.thumbnail)}
	      {include file=$layout.frame.template ImageFrame_data=$layout.frame.data
		       ImageFrame_frame=$layout.frame.$frameType item=$child image=$child.thumbnail
		       ImageFrame_pre=$smarty.capture.link ImageFrame_post="</a>"}
	    {else}
	      {$smarty.capture.link}
              {if isset($child.thumbnail)}
              {g->image item=$child image=$child.thumbnail}
              {else}
              {g->text text="no thumbnail"}
              {/if}
	      </a>
	    {/if}
	</div></td><td class="info">

          <h2 class="giTitle">
            {$child.title|default:$child.pathComponent|markup}
          </h2>

          <p class="giDescription">
            {$child.summary|entitytruncate:256|markup}
          </p>

          <ul class="giInfo">
            <li>
              {capture name=originationTimestamp}
              {g->date timestamp=$child.originationTimestamp}
              {/capture}
              {g->text text="Date: %s" arg1=$smarty.capture.originationTimestamp}
            </li>
            
            {if ($child.canContainChildren && $layout.showAlbumOwner) || (!$child.canContainChildren && $layout.showImageOwner)}
            <li>
              {g->text text="Owner: %s"
                       arg1=$layout.ownerMap[$child.ownerId].fullName|default:$layout.ownerMap[$child.ownerId].userName}
            </li>
            {/if}

            {if ($child.canContainChildren && $child.childCount > 0)}
            <li>
              {g->text one="Size: %d item" many="Size: %d items"
                       count=$child.childCount arg1=$child.childCount}
              {if $child.descendentCount > $child.childCount}
                {g->text one="(%d item total)" many="(%d items total)"
                         count=$child.descendentCount arg1=$child.descendentCount}
              {/if}
            </li>
            {/if}

            {if ($child.viewCount > 0)}
            <li>
              {g->text text="Views: %d" arg1=$child.viewCount}
            </li>
            {/if}

            {foreach from=$child.itemSummaries item=summary}
            <li>
              {$summary}
            </li>
            {/foreach}
          </ul>

            {if !empty($child.itemLinks)}
            <select onchange="{literal}javascript:if (this.value) { newLocation = this.value; this.options[0].selected = true; location.href= newLocation; }{/literal}" class="giActionSelect">
              <option label="{if $child.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}" value="">{if $child.canContainChildren}{g->text text="&laquo; album actions &raquo;"}{else}{g->text text="&laquo; item actions &raquo;"}{/if}</option>

              {foreach from=$child.itemLinks item=link}
              <option label="{$link.text}" value="{$link.url}">{$link.text}</option>
              {/foreach}
            </select>
            {/if}
        </td>
	{if $layout.showSubalbums}
	<td class="tree">
	  {if !empty($layout.tree[$child.id])}
	    <h3 class="giTitle"> {g->text text="Subalbums:"} </h3>
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
		<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$node.id`"}">
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
        {section name="flush" start=$childrenInColumnCount loop=$layout.columnSize}
        <td>&nbsp;</td>
        {/section}
      </tr>
    </table>
    {else}
    <div id="gsStatus">
      <p class="giEmpty">
      {g->text text="This album is empty."}
      </p>
    </div>
    {/if}

    {if !empty($layout.itemDetailFiles)}
    {foreach from=$layout.itemDetailFiles key=moduleId item=detailFile}
    {include file="gallery:$detailFile" l10Domain="modules_$moduleId"}
    {/foreach}
    {/if}

    <div class="gbBottomFlag">
      <div class="gbNavBar">
        {include file="gallery:layouts/matrix/templates/itemNavigator.tpl"}
      </div>
      <ul class="giHorizontalLinks">
        {if !empty($layout.jumprange)}
	<li>{g->text text="Page:"}</li>
	{/if}
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
        <li class="giSelected">
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
