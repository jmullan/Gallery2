{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to sidebar.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{if $layout.show.sidebar}
<div id="gsSidebar">
  <div class="gbMenu">
    {if $layout.show.sidebarGreeting}
    <h3 class="giTitle">
      {g->text text="Greetings, %s!" arg1=$layout.user.fullName|default:$layout.user.userName}
    </h3>
    {/if}

    {* System links *}
    <ul>
      {foreach from=$layout.systemLinks item=link}
      <li>
	<a href="{$link.url}">{$link.text}</a>
      </li>
      {/foreach}
    </ul>
  </div>

  {* Search form, if module is activated *}
  {if isset($layout.systemContentFiles.search)}
    {assign var=moduleFile value=$layout.systemContentFiles.search}
    {include file="gallery:$moduleFile" l10Domain="modules_search"} 
  {/if}

  {* Item actions *}
  {if ($layout.show.sidebarActions && !empty($layout.itemLinks))}
  <div class="gbMenu">
    <h3 class="giTitle">{g->text text="Actions"}</h3>
    <ul>
      {foreach from=$layout.itemLinks item=link}
      <li><a href="{$link.url}">{$link.text}</a></li>
      {/foreach}
    </ul>
  </div>
  {/if}

  {* Peer items *}
  {if $layout.show.sidebarPeers}
  <div class="gbMenu">
    <h3 class="giTitle"> {$layout.parent.title|default:$layout.parent.pathComponent|markup}</h3>
    <p class="giDescription">
      {g->text one="(%d item)" many="(%d items)" count=$layout.peerCount arg1=$layout.peerCount}
    </p>

    <ul>
      {assign var="lastIndex" value=0}
      {foreach from=$layout.peers item=peer}
      {assign var="title" value=$peer.title|default:$peer.pathComponent|markup}
      {if ($peer.peerIndex - $lastIndex > 1)}
      <li>...</li>
      {/if}

      {if ($peer.id == $layout.item.id)}
      <li class="giSelected">
	{g->text text="%d. %s" arg1=$peer.peerIndex arg2=$title|entitytruncate:14}
      </li>
      {else}
      <li><a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$peer.id`"}">
	{g->text text="%d. %s" arg1=$peer.peerIndex arg2=$title|entitytruncate:14}</a></li>
      {/if}
      {assign var="lastIndex" value=$peer.peerIndex}
      {/foreach}
    </ul>
  </div>
  {/if}

  {* System content *}
  {foreach from=$layout.systemContentFiles key=moduleId item=moduleFile}
  {if ($moduleId != 'search')}
  {include file="gallery:$moduleFile" l10Domain="modules_$moduleId"}
  {/if}
  {/foreach}
</div>
{/if}
