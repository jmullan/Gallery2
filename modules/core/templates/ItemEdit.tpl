{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit %s" arg1=$ItemEdit.itemTypeNames.0}

      <!-- Gotta put this somewhere; move it when we switch to pure HTML templates -->
      {g->input type="hidden" name="editPlugin"}{$ItemEdit.editPlugin}{/g->input}
      {g->input type="hidden" name="form[serialNumber]"}{$form.serialNumber}{/g->input}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.editMessage)}
	{$status.editMessage}
      {/if}
    {/g->success}
  {/if}

  {g->tabbedbox}
    {g->tabset}
      {foreach from=$ItemEdit.plugins item=plugin} 
	{if $plugin.isSelected}
	  {g->item selected="true"}
	    {g->title}
	      {$plugin.title}
	    {/g->title}
	  {/g->item}
	{else}
	  {g->item}
	    {g->title}
	      {g->link arg1="view=core:ItemAdmin" arg2="subView=core:ItemEdit" arg3="itemId=`$ItemAdmin.item.id`" arg4="editPlugin=`$plugin.id`"}
		{$plugin.title}
	      {/g->link}
	    {/g->title}
	  {/g->item}
	{/if}
      {/foreach}
    {/g->tabset}

    {include file=$ItemEdit.pluginFile l10Domain=$ItemAdmin.viewL10Domain}

  {/g->tabbedbox}
{/g->pagebox}
