{g->form action_controller=$SearchShowAll.controller}
  {g->input type="hidden" name="form[formName]"}SearchShowAll{/g->input}
  {g->input type="hidden" name="form[moduleId]"}{$form.moduleId}{/g->input}
  {g->input type="hidden" name="form[page]"}{$form.page}{/g->input}

  {g->main}
    {g->breadcrumb}
      {g->item}
	{g->title}
	  {g->text text="Search"}
	{/g->title}
      {/g->item}
    {/g->breadcrumb}

    {g->pagebox}
      {g->banner}
	{g->title}
	  {g->text text="Search the Gallery"}
	{/g->title}
      {/g->banner}
      
      {g->box}
	{g->title}
	  {g->text text="Search: "}
	{/g->title}

	{g->element}
	  {g->input type="text" size="50" name="form[searchCriteria]"}{$form.searchCriteria}{/g->input}
	{/g->element}

	{if isset($form.error.searchCriteria.missing)}
	  {g->error}
	    {g->text text="You must enter some text to search for!"}
	  {/g->error}
	{/if}

	{g->element}
	  {g->input type="submit" name="form[action][search]"}
	    {g->text text="Search"}
	  {/g->input}
	{/g->element}
      {/g->box}

      {g->box}
	{g->title}
	  {$SearchShowAll.moduleInfo.name}
	{/g->title}

	{g->table}
	  {foreach from=$SearchShowAll.moduleInfo.options key=optionId item=optionInfo}
	    {g->row}
	      {g->column}
		{capture name=checkboxName}form.options.{$SearchShowAll.moduleId}.{$optionId}{/capture}
		{g->input type="checkbox" name=$smarty.capture.checkboxName}
		  {if isset($form.options.$SearchShowAll.moduleId.$optionId)}1{/if}
		{/g->input}
	      {/g->column}
	      {g->column}
		{$optionInfo.description}
	      {/g->column}
	    {/g->row}
	  {/foreach}
	{/g->table}

	{if !empty($SearchShowAll.results)}
	  {g->box}
	    {g->title}
	      {g->text text="Search Results"}
	    {/g->title}
	    
	    {g->box}
	      {g->title}
		{g->text text="Searching %s only" arg1=$SearchShowAll.moduleInfo.name}
		{g->input type="submit" name="form[action][scan]"}
		  {g->text text="Search all modules"}
		{/g->input}
		{$SearchShowAll.moduleInfo.name}
		{if ($SearchShowAll.results.count > 0)}
		  {g->text text="(Results %d - %d)"
	          arg1=$SearchShowAll.results.start
	          arg2=$SearchShowAll.results.end}
		{/if}
		{if ($SearchShowAll.results.count > $SearchShowAll.results.end)}
		  {assign var="moduleId" value=$SearchShowAll.moduleId}
		  {g->input type="submit" name="form[action][showAll][$SearchShowAll][moduleId]"}
		    {g->text text="Show all %d" arg1=$SearchShowAll.results.count}
		  {/g->input}
		{/if}
		{if ($SearchShowAll.results.count > 0)}
		  {if ($form.page > 1)}
		    {g->input type="submit" name="form[action][previousPage]"}
		      {g->text text="&laquo; Back"}
		    {/g->input}
		  {/if}
		  
		  {g->text text="(Results %d - %d of %d, Page %d of %d)"
	          arg1=$SearchShowAll.results.start
	          arg2=$SearchShowAll.results.end
	          arg3=$SearchShowAll.results.count
	          arg4=$form.page
	          arg5=$SearchShowAll.maxPages}
		{/if}
		{if ($form.page < $SearchShowAll.maxPages)}
		  {g->input type="submit" name="form[action][nextPage]"}
		    {g->text text="Next &raquo;"}
		  {/g->input}
		{/if}
	      {/g->title}

	      {g->table}
		{assign var="searchCriteria" value=$form.searchCriteria} 
		{foreach from=$SearchShowAll.results.results item=result} 
		  {assign var=itemId value=$result.itemId} 
		  {g->row}
		    {g->column}
		      {g->link url_view="core:ShowItem" url_itemId=$itemId}
			{g->image item=$SearchShowAll.items.$itemId image=$SearchShowAll.thumbnails.$itemId}
		      {/g->link}
		    {/g->column}
		    
		    {g->column}
		      {g->table}
			{foreach from=$result.fields item=field} 
			  {g->row}
			    {g->column}
			      {$field.key}
			    {/g->column}
			    {g->column}
			      {$field.value|default:"&nbsp;"|replace:$searchCriteria:"<b>$searchCriteria</b>"}
			    {/g->column}
			  {/g->row}
			{/foreach}
		      {/g->table}
		    {/g->column}
		  {/g->row}
		{foreachelse} 
		  {g->row}
		    {g->column}
		      {g->text text="No results"}
		    {/g->column}
		  {/g->row}
		{/foreach}
	      {/g->table}
	    {/g->box}
	  {/g->box}
	{/if}
      {/g->box}
    {/g->pagebox}
  {/g->main}
{/g->form}
