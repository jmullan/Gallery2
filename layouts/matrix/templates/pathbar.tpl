{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if $layout.show.pathbar}
<div id="gsSystemLinks" class="gcBorder1">
  <div>
    {if $layout.show.sidebarGreeting}
    <span style="font-weight: normal">
      {g->text text="Welcome, %s" arg1=$user.fullName|default:$user.userName}
    </span>
    {/if}
    {foreach from=$layout.systemLinks item=item}
    <span>
      <a href="{g->url params=$item.params}">{$item.text}</a>
    </span>
    {/foreach}
  </div>

  <ul class="gbBreadCrumb">
    {section name=parent loop=$layout.parents}
    <li{if $smarty.section.parent.first} class="firstChild"{/if}>
      {if !$smarty.section.parent.last}
	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`"
	 arg3="highlightId=`$layout.parents[parent.index_next].id`"}">
	  {$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}
	</a>
      {else}
	<a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`"
	 arg3="highlightId=`$layout.item.id`"}">
	  {$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}
	</a>
      {/if}
    </li>
    {/section}
    <li{if empty($layout.parents)} class="firstChild"{/if}>
      {$layout.item.title|default:$layout.item.pathComponent|markup}
    </li>
  </ul>
</div>
{/if}
