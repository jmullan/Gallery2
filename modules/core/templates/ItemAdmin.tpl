{g->form action_controller="$controller" enctype=$enctype}
  {g->input type="hidden" name="form.formName"}{$form.formName}{/g->input}
  {g->input type="hidden" name="itemId"}{$ItemAdmin.item.id}{/g->input}
  
  {g->main}
    {g->breadcrumb}
      {foreach from=$ItemAdmin.parents item=parent}
	{g->item}
	  {g->title}
	    {g->link url_view='core:ShowItem' url_itemId=$parent.id}
	      {$parent.title|default:$parent.pathComponent}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/foreach}
      {g->item}
	{g->title}
	  {g->link url_view='core:ShowItem' url_itemId=$ItemAdmin.item.id}
	    {$ItemAdmin.item.title|default:$ItemAdmin.item.pathComponent}
	  {/g->link}
	{/g->title}
      {/g->item}
    {/g->breadcrumb}

    {g->sidebar}
      {g->box style="sidebar"}
	{g->element}
	  {if empty($ItemAdmin.thumbnail)}
	    {g->text text="No Thumbnail"}
	  {else}
	    {g->image item=$ItemAdmin.item image=$ItemAdmin.thumbnail}
	  {/if}
	{/g->element}
	{g->footer}
	  {$ItemAdmin.item.title}
	{/g->footer}
      {/g->box}

      {g->box style="sidebar"}
	{g->title}
	  {g->text text="Options"}
	{/g->title}

	{g->listing}
	  {foreach from=$ItemAdmin.subViewChoices item=choice}
	    {g->item}
	      {g->title}
		{g->link url_view='core:ItemAdmin' url_subView=$choice.view url_itemId=$ItemAdmin.item.id}
		  {$choice.name}
		{/g->link}
	      {/g->title}
	    {/g->item}
	  {/foreach}
	{/g->listing}
      {/g->box}

      {g->box style="sidebar"}
	{g->title}
	  {g->text text="Navigation"}
	{/g->title}
	{g->listing}
	  {if ($ItemAdmin.itemType == 'item')}
	    {g->item}
	      {g->title}
		{g->link url_view='core:ShowItem' url_itemId=$ItemAdmin.item.id}
		  {g->text text="Back to Item View"}
		{/g->link}
	      {/g->title}
	    {/g->item}
	    {g->item}
	      {g->title}
		{g->link url_view='core:ShowItem' url_itemId=$ItemAdmin.parent.id}
		  {g->text text="Back to Album View"}
		{/g->link}
	      {/g->title}
	    {/g->item}
	  {else}
	    {g->item}
	      {g->title}
		{g->link url_view='core:ShowItem' url_itemId=$ItemAdmin.item.id}
		  {g->text text="Back to Album View"}
		{/g->link}
	      {/g->title}
	    {/g->item}
	  {/if}
	{/g->listing}
      {/g->box}
    {/g->sidebar}

    {include file=$ItemAdmin.viewBodyFile l10Domain=$ItemAdmin.viewL10Domain}
  {/g->main}
{/g->form}
