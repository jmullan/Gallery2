{g->listing}
  {g->item}
    {g->title}
      {if isset($ShowTree.parentIds.$parentIndex)}
	{* Show my link and move on to the next parent *}
	{include file="modules/debug/templates/ShowTreeEntityLink.tpl" entityId=$ShowTree.parentIds.$parentIndex}
	{include file="modules/debug/templates/ShowTreeEntity.tpl" parentIndex=$parentIndex+1}
      {else}
	{* Show my link *}
	{include file="modules/debug/templates/ShowTreeEntityLink.tpl" entityId=$ShowTree.entityId}

	{* Show my data *}
	{g->table}
	  {assign var="entityId" value=$ShowTree.entityId}
	  {foreach key=key item=value from=$ShowTree.entityTable.$entityId} 
	    {if strcmp($key, '_className')} 
	      {g->row}
		{g->column}
		  <i>{$key}</i>
		{/g->column}
		{g->column}
		  {$value}
		{/g->column}
	      {/g->row}
	    {/if} 
	  {/foreach} 
	{/g->table}
	
	{* Show my children *}
	{g->listing}
	  {foreach from=$ShowTree.childIds item=childId}
	    {g->item}
	      {g->title}
		{include file="modules/debug/templates/ShowTreeEntityLink.tpl" entityId=$childId}
	      {/g->title}
	    {/g->item}
	  {/foreach}
	{/g->listing}
      {/if}
    {/g->title}
  {/g->item}
{/g->listing}
