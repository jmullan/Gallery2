{include file="modules/debug/templates/ShowTreeEntityLink.tpl" entityId=$ShowTree.entityId}

{gallery->table}
  {foreach key=key item=value from=$ShowTree.entityTable[$entityId]} 
    {if strcmp($key, '_className')} 
      {gallery->row}
	{gallery->column}
	  <i>{$key}</i>
	{/gallery->column}
	{gallery->column}
	  {$value}
	{/gallery->column}
      {/gallery->row}
    {/if} 
  {/foreach} 
{/gallery->table}

{gallery->listingbox}
  {foreach from=$ShowTree.childIds item=childId}
    {gallery->item}
      {include file="modules/debug/templates/ShowTreeEntityLink.tpl" entityId=$childId}
    {/gallery->item}
  {/foreach}
{/gallery->listingbox}

	  