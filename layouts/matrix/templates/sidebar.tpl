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
  {if $layout.show.peerSidebarBox}
    {g->box style="sidebar"}
      {g->title}
	{$layout.parent.title|default:$layout.parent.pathComponent}
      {/g->title}
      {g->subtitle}
	{g->text one="(%d item)" many="(%d items)" count=$layout.totalPeerCount arg1=$layout.totalPeerCount}
      {/g->subtitle}

      {g->listing}
	{assign var="lastIndex" value=0}
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
		{g->link arg1="view=core:ShowItem" arg2="itemId=`$peer.peer.id`"}
		  {g->text text="%d. %s" arg1=$peer.index arg2=$title|truncate:14}
		{/g->link}
	      {/g->title}
	    {/g->item}
	  {/if}
	  {assign var="lastIndex" value=$peer.index}
	{/foreach}
      {/g->listing}
    {/g->box}
  {/if}

  {* Extra modules system content *}
  {foreach from=$layout.moduleSystemContentFiles key=moduleId item=moduleFile}
    {if ($moduleId != 'core')}
      {g->box style="sidebar"}
	{include file=$moduleFile l10Domain="modules_$moduleId"}
      {/g->box}
    {/if}
  {/foreach}
{/g->sidebar}
