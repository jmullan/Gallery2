{g->sidebar side="right"}

  {* Module links *}
  {g->box style="sidebar"}
    {g->title}
      {g->text text="Greetings, %s!" arg1=$layout.user.fullName|default:$layout.user.userName}
    {/g->title}

    {g->listing}
      {foreach from=$layout.moduleSystemLinks item=module}
	{foreach from=$module item=link}
	  {g->item}
	    {g->title}
	      {g->link params=$link.params}{$link.text}{/g->link}
	    {/g->title}
	  {/g->item}
	{/foreach}
      {/foreach}
    {/g->listing}
  {/g->box}

  {* List of peer items *}
  {g->box style="sidebar"}
    {g->title}
      {$layout.parent.title|default:$layout.parent.pathComponent}
    {/g->title}
    {g->subtitle}
      {g->text one="(%d item)" many="(%d items)" count=$layout.totalPeerCount arg1=$layout.totalPeerCount}
    {/g->subtitle}

    {g->listing}
      {foreach from=$layout.peers item=peer}
	{assign var="title" value=$peer.peer.title|default:$peer.peer.pathComponent}
	{if ($peer.index - $lastIndex > 1)}
	  {g->item}
	    {g->title}
	      ...
	    {/g->title}
	  {/g->item}
	{/if}

	{if ($peer.peer.id == $layout.item.id)}
	  {g->item selected="true"}
	    {g->title}
	      {g->text text="%d. %s" arg1=$peer.index arg2=$title|truncate:14}
	    {/g->title}
	  {/g->item}
	{else}
	  {g->item}
	    {g->title}
	      {g->link url_view="core:ShowItem" url_itemId=$peer.peer.id}
		{g->text text="%d. %s" arg1=$peer.index arg2=$title|truncate:14}
	      {/g->link}
	    {/g->title}
	  {/g->item}
	{/if}
	{assign var="lastIndex" value=$peer.index}
      {/foreach}
    {/g->listing}
  {/g->box}

  {* Extra modules system content *}
  {foreach from=$layout.moduleSystemContentFiles key=moduleName item=moduleFile}
    {if ($moduleName != 'core')}
      {g->box style="sidebar"}
	{include file=$moduleFile l10Domain="module_$moduleName"}
      {/g->box}
    {/if}
  {/foreach}
{/g->sidebar}
