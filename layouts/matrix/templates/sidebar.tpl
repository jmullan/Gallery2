{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to sidebar.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsSidebar">
  {* Module links *}
  <div class="gbMenu">
    <div class="giTitle">
      {g->text text="Greetings, %s!" arg1=$layout.user.fullName|default:$layout.user.userName}
    </div>

    <ul>
      {foreach from=$layout.moduleSystemLinks item=module}
      {foreach from=$module item=link}
      <li>
	<a href="{g->url params=$link.params}">{$link.text}</a>
      </li>
      {/foreach}
      {/foreach}
    </ul>
  </div>

  {* Album actions, if there are any *}
  {if (isset($layout.moduleItemLinks[$layout.item.id]))}
  <div class="gbMenu">
    <div class="giTitle">
      {g->text text="Actions"}
    </div>

    <ul>
      {foreach from=$layout.moduleItemLinks[$layout.item.id] item=link}
      <li>
        <a href="{$link.url}">{$link.text}</a>
      </li>
      {/foreach}
    </ul>
  </div>
  {/if}

  {* List of peer items *}
  {if $layout.show.peerSidebarBox}
  <div class="gbMenu">
    <p><span class="giTitle">{$layout.parent.title|default:$layout.parent.pathComponent}</span><br />
    <span class="giDescription">{g->text one="(%d item)" many="(%d items)" count=$layout.totalPeerCount arg1=$layout.totalPeerCount}</span></p>

    <ul>
      {assign var="lastIndex" value=0}
      {foreach from=$layout.peers item=peer}
      {assign var="title" value=$peer.peer.title|default:$peer.peer.pathComponent}
      {if ($peer.index - $lastIndex > 1)}
      <li>...</li>
      {/if}

      {if ($peer.peer.id == $layout.item.id)}
      <li class="giSelected">{g->text text="%d. %s" arg1=$peer.index arg2=$title|truncate:14}</li>
      {else}
      <li><a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$peer.peer.id`"}">{g->text text="%d. %s" arg1=$peer.index arg2=$title|truncate:14}</a></li>
      {/if}
      {assign var="lastIndex" value=$peer.index}
      {/foreach}
    </ul>
  </div>
  {/if}

  {* Extra modules system content *}
  {foreach from=$layout.moduleSystemContentFiles key=moduleId item=moduleFile}
  {if ($moduleId != 'core')}
  {include file="gallery:$moduleFile" l10Domain="modules_$moduleId"}
  {/if}
  {/foreach}
</div>
