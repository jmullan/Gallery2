{gallery->sidebar side="right"}
  {gallery->component}
    {* Module links *}
    {gallery->listingbox}
      {gallery->title}
	{gallery->text text="Greetings, %s!" arg1=$layout.user.fullName|default:$layout.user.userName}
      {/gallery->title}
      {foreach from=$layout.moduleSystemLinks item=module}
	{foreach from=$module item=link}
	  {gallery->item}
	    {gallery->link params=$link.params}{$link.text}{/gallery->link}
	  {/gallery->item}
	{/foreach}
      {/foreach}
    {/gallery->listingbox}

    {* List of peer items *}
    {gallery->detailedbox}
      {gallery->title}
	{$layout.parent.title|default:$layout.parent.pathComponent}
      {/gallery->title}
      {gallery->description}
	{gallery->textmodifier}
	  {gallery->text one="(%d item)" many="(%d items)" count=$layout.totalPeerCount arg1=$layout.totalPeerCount}
	{/gallery->textmodifier}
      {/gallery->description}
      {gallery->body}
	{gallery->listingbox}
	  {foreach from=$layout.peers item=peer}
	    {assign var="title" value=$peer.peer.title|default:$peer.peer.pathComponent}
	    {if ($peer.index - $lastIndex > 1)}
	      {gallery->item}
		...
	      {/gallery->item}
	    {/if}

	    {if ($peer.peer.id == $layout.item.id)}
	      {gallery->item selected="true"}
		{gallery->text text="%d. %s" arg1=$peer.index arg2=$title|truncate:14}
	      {/gallery->item}
	    {else}
	      {gallery->item}
		{gallery->link url_view="core:ShowItem" url_itemId=$peer.peer.id}
		{gallery->text text="%d. %s" arg1=$peer.index arg2=$title|truncate:14}
		{/gallery->link}
	      {/gallery->item}
	    {/if}
	    {assign var="lastIndex" value=$peer.index}
	  {/foreach}
	{/gallery->listingbox}
      {/gallery->body}
    {/gallery->detailedbox}

    {* Extra modules system content *}
    {foreach from=$layout.moduleSystemContentFiles key=moduleName item=moduleFile}
      {if ($moduleName != 'core')}
	{gallery->simplebox}
	  {gallery->body}
	    {include file=$moduleFile l10Domain="module_$moduleName"}
	  {/gallery->body}
	{/gallery->simplebox}
      {/if}
    {/foreach}
  {/gallery->component}
{/gallery->sidebar}
