{gallery->form action_controller=$SearchShowAll.controller}
  {gallery->input type="hidden" name="form.formName"}SearchShowAll{/gallery->input}
  {gallery->input type="hidden" name="form.moduleId"}{$form.moduleId}{/gallery->input}
  {gallery->input type="hidden" name="form.page"}{$form.page}{/gallery->input}

  {gallery->main}
    {gallery->pathbar}
      {gallery->item}
	{gallery->text text="Search"}
      {/gallery->item}
    {/gallery->pathbar}

    {gallery->component}
      {gallery->bannerbox}
	{gallery->title}
	  {gallery->text text="Search the Gallery"}
	{/gallery->title}
      {/gallery->bannerbox}

      {gallery->widget1box}
	{gallery->widget1}
	  {gallery->title}
	    {gallery->text text="Search: "}
	  {/gallery->title}
	  {gallery->body}
	    {gallery->input type="text" size="50" name="form.searchCriteria"}{$form.searchCriteria}{/gallery->input}
	    {if isset($form.error.searchCriteria.missing)}
	      {gallery->error}
		{gallery->text text="You must enter some text to search for!"}
	      {/gallery->error}
	    {/if}
	    {gallery->input type="submit" name="form.action.search"}
	      {gallery->text text="Search"}
	    {/gallery->input}
	  {/gallery->body}
	{/gallery->widget1}
      {/gallery->widget1box}

      {gallery->detailedbox}
	{gallery->title}
	  {$SearchShowAll.moduleInfo.name}
	{/gallery->title}

	{gallery->body}
	  {gallery->widget1box}
	    {foreach from=$SearchShowAll.moduleInfo.options key=optionId item=optionInfo}
	      {gallery->widget1}
		{gallery->title}
		  {$optionInfo.description}
		{/gallery->title}
		{gallery->body}
		  {capture name=checkboxName}form.options.{$SearchShowAll.moduleId}.{$optionId}{/capture}
		  {gallery->input type="checkbox" name=$smarty.capture.checkboxName}
		    {if isset($form.options.$SearchShowAll.moduleId.$optionId)}1{/if}
		  {/gallery->input}
		{/gallery->body}
	      {/gallery->widget1}
	    {/foreach}
	  {/gallery->widget1box}
	{/gallery->body}
      {/gallery->detailedbox}

      {if !empty($SearchShowAll.results)}
	{gallery->detailedbox}
	  {gallery->title}
	    {gallery->text text="Search Results"}
	  {/gallery->title}

	  {gallery->body}
	    {gallery->detailedbox}
	      {gallery->title}
		{gallery->text text="Searching %s only" arg1=$SearchShowAll.moduleInfo.name}
		{gallery->input type="submit" name="form.action.scan"}
		  {gallery->text text="Search all modules"}
		{/gallery->input}
		{$SearchShowAll.moduleInfo.name}
		{if ($SearchShowAll.results.count > 0)}
		  {gallery->text text="(Results %d - %d)"
	          arg1=$SearchShowAll.results.start
	          arg2=$SearchShowAll.results.end}
		{/if}
		{if ($SearchShowAll.results.count > $SearchShowAll.results.end)}
		  {assign var="moduleId" value=$SearchShowAll.moduleId}
		  {gallery->input type="submit" name="form.action.showAll.$SearchShowAll.moduleId"}
		    {gallery->text text="Show all %d" arg1=$SearchShowAll.results.count}
		  {/gallery->input}
		{/if}
		{if ($SearchShowAll.results.count > 0)}
		  {if ($form.page > 1)}
		    {gallery->input type="submit" name="form.action.previousPage"}
		      {gallery->text text="<< Previous"}
		    {/gallery->input}
		  {/if}
		  
		  {gallery->text text="(Results %d - %d of %d, Page %d of %d)"
	          arg1=$SearchShowAll.results.start
	          arg2=$SearchShowAll.results.end
	          arg3=$SearchShowAll.results.count
	          arg4=$form.page
	          arg5=$SearchShowAll.maxPages}
		{/if}
		{if ($form.page < $SearchShowAll.maxPages)}
		  {gallery->input type="submit" name="form.action.nextPage"}
		    {gallery->text text="Next >>"}
		  {/gallery->input}
		{/if}
	      {/gallery->title}

	      {gallery->body}
		{gallery->table}
		  {assign var="searchCriteria" value=$form.searchCriteria} 
		  {foreach from=$SearchShowAll.results.results item=result} 
		    {assign var=itemId value=$result.itemId} 
		    {gallery->row}
		      {gallery->column}
			{gallery->link url_view="core:ShowItem" url_itemId=$itemId}
			  {gallery->image item=$SearchShowAll.items.$itemId image=$SearchShowAll.thumbnails.$itemId}
			{/gallery->link}
		      {/gallery->column}

		      {gallery->column}
			{gallery->table}
			  {foreach from=$result.fields item=field} 
			    {gallery->row}
			      {gallery->column}
				{$field.key}
			      {/gallery->column}
			      {gallery->column}
				{$field.value|default:"&nbsp;"|replace:$searchCriteria:"<b>$searchCriteria</b>"}
			      {/gallery->column}
			    {/gallery->row}
			  {/foreach}
			{/gallery->table}
		      {/gallery->column}
		    {/gallery->row}
		  {foreachelse} 
		    {gallery->row}
		      {gallery->column}
			{gallery->text text="No results"}
		      {/gallery->column}
		    {/gallery->row}
		  {/foreach}
		{/gallery->table}
	      {/gallery->body}
	    {/gallery->detailedbox}
	  {/gallery->body}
	{/gallery->detailedbox}
      {/if}
    {/gallery->component}
  {/gallery->main}
{/gallery->form}
