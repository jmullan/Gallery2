{gallery->form action_controller="$controller" enctype=$enctype}
  {gallery->input type="hidden" name="form.formName"}{$form.formName}{/gallery->input}
  {gallery->input type="hidden" name="itemId"}{$ItemAdmin.item.id}{/gallery->input}
  
  {gallery->main}
    {gallery->pathbar}
      {foreach from=$ItemAdmin.parents item=parent}
	{gallery->item}
	  {gallery->link url_view='core:ShowItem' url_itemId=$parent.id}
	    {$parent.title|default:$parent.pathComponent}
	  {/gallery->link}
	{/gallery->item}
      {/foreach}
      {gallery->item}
	{gallery->link url_view='core:ShowItem' url_itemId=$ItemAdmin.item.id}
	  {$ItemAdmin.item.title|default:$ItemAdmin.item.pathComponent}
	{/gallery->link}
      {/gallery->item}
    {/gallery->pathbar}

    {gallery->sidebar}
      {gallery->component}
	{gallery->simplebox}
	  {gallery->body}
	    {if empty($ItemAdmin.thumbnail)}
	      {gallery->text text="No Thumbnail"}
	    {else}
	      {gallery->image item=$ItemAdmin.item image=$ItemAdmin.thumbnail}
	    {/if}
	    {$ItemAdmin.item.title}
	  {/gallery->body}
	{/gallery->simplebox}

	{gallery->simplebox}
	  {gallery->body}
	    {gallery->listingbox}
	      {gallery->title}
		{gallery->text text="Options"}
	      {/gallery->title}

	      {foreach from=$ItemAdmin.subViewChoices item=choice}
		{gallery->item}
		  {gallery->link url_view='core:ItemAdmin' url_subView=$choice.view url_itemId=$ItemAdmin.item.id}
		    {$choice.name}
		  {/gallery->link}
		{/gallery->item}
	      {/foreach}
	    {/gallery->listingbox}
	  {/gallery->body}
	{/gallery->simplebox}

	{gallery->simplebox}
	  {gallery->body}
	    {gallery->listingbox}
	      {gallery->title}
		{gallery->text text="Navigation"}
	      {/gallery->title}
	      {if ($ItemAdmin.itemType == 'item')}
		{gallery->item}
		  {gallery->link url_view='core:ShowItem' url_itemId=$ItemAdmin.item.id}
		    {gallery->text text="Back to Item View"}
		  {/gallery->link}
		{/gallery->item}
		{gallery->item}
		  {gallery->link url_view='core:ShowItem' url_itemId=$ItemAdmin.parent.id}
		    {gallery->text text="Back to Album View"}
		  {/gallery->link}
		{/gallery->item}
	      {else}
		{gallery->item}
		  {gallery->link url_view='core:ShowItem' url_itemId=$ItemAdmin.item.id}
		    {gallery->text text="Back to Album View"}
		  {/gallery->link}
		{/gallery->item}
	      {/if}
	    {/gallery->listingbox}
	  {/gallery->body}
	{/gallery->simplebox}
      {/gallery->component}
    {/gallery->sidebar}

    {gallery->component}
      {include file=$ItemAdmin.viewBodyFile l10Domain=$ItemAdmin.viewL10Domain}
    {/gallery->component}
  {/gallery->main}
{/gallery->form}
