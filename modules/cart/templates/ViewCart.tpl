{g->form arg1="controller=`$ViewCart.controller`"}
  {g->input type="hidden" name="form[formName]"}{$form.formName}{/g->input}

  {g->main}
    {g->pagebox}

      {g->banner}
	{g->title}
	  {g->text text="View Your Cart"}
	{/g->title}
      {/g->banner}

      {if isset($status)}
	{g->success}
	  {if isset($status.cartModified)}
	    {g->text text="Cart updated successfully"}
	  {/if}
	{/g->success}
      {/if}
      
      {g->box}
	{g->table evenodd="true"}
	  {g->row header="true"}
	    {g->column header="true"}
	      {g->text text="Quantity"}
	    {/g->column}

	    {g->column colspan="2" align="center" header="true"}
	      {g->text text="Item"}
	    {/g->column}

	    {g->column header="true"}
	      {g->text text="Delete"}
	    {/g->column}
	  {/g->row}

	  {foreach from=$ViewCart.items item=item}
	    {g->row}
	      {g->column}
		{g->input type="text" size="3" name="form[counts][`$item.id`]"}{$form.counts[$item.id]}{/g->input}
	      {/g->column}

	      {g->column}
		{g->link arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}
		  {if isset($ViewCart.thumbnails[$item.id])}
		    {g->image item=$ViewCart.items[$item.id] image=$ViewCart.thumbnails[$item.id]}
		  {else}
		    {g->text text="No thumbnail"}
		  {/if}
		{/g->link}
	      {/g->column}

	      {g->column}
		{g->table}
		  {g->row}
		    {g->column valign="top"}
		      {g->text text="Title"}
		    {/g->column}

		    {g->column}
		      {$item.title}
		    {/g->column}
		  {/g->row}

		  {g->row}
		    {g->column valign="top"}
		      {g->text text="Summary"}
		    {/g->column}

		    {g->column}
		      {$item.summary}
		    {/g->column}
		  {/g->row}
		{/g->table}
	      {/g->column}

	      {g->column align="center"}
		{g->input type="checkbox" name="form[delete][`$item.id`]"}{/g->input}
	      {/g->column}
	    {/g->row}
	  {/foreach}
        {/g->table}
      {/g->box}

      {g->box}
	{g->element}
	  {g->input type="submit" name="form[action][update]"}{g->text text="Update Cart"}{/g->input}
	  {g->input type="submit" name="form[action][empty]"}{g->text text="Empty Cart"}{/g->input}
	{/g->element}
      {/g->box}

    {/g->pagebox}
  {/g->main}
{/g->form}
