{g->form action_controller=$SearchScan.controller}
  {g->input type="hidden" name="form[formName]"}SearchScan{/g->input}

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

      {foreach from=$SearchScan.modules key=moduleId item=moduleInfo}
	{g->box}
	  {g->title}
	    {$moduleInfo.name}
	  {/g->title}

	  {g->table}
	    {foreach from=$moduleInfo.options key=optionId item=optionInfo}
	      {g->row}
		{g->column}
		  {capture name=checkboxName}form[options][{$moduleId}][{$optionId}]{/capture}
		  {g->input type="checkbox" name=$smarty.capture.checkboxName}
		    {if isset($form.options.$moduleId.$optionId)}1{/if}
		  {/g->input}
		{/g->column}
		{g->column}
		  {$optionInfo.description}
		{/g->column}
	      {/g->row}
	    {/foreach}
	  {/g->table}
	{/g->box}
      {/foreach}

      {if !empty($SearchScan.searchResults)}
	{g->box}
	  {g->title}
	    {g->text text="Search Results"}
	  {/g->title}

	  {foreach from=$SearchScan.searchResults key=moduleId item=results}
	    {g->box}
	      {g->title}
		{$SearchScan.modules.$moduleId.name}
		{if ($results.count > 0)}
		  {g->text text="(Results %d - %d)"
	          arg1=$results.start
	          arg2=$results.end}
		{/if}
		{if ($results.count > $results.end)}
		  {assign var="moduleId" value=$moduleId}
		  {g->input type="submit" name="form[action][showAll][$moduleId]"}
		    {g->text text="Show all %d" arg1=$results.count}
		  {/g->input}
		{/if}
	      {/g->title}

	      {g->table}
		{assign var="searchCriteria" value=$form.searchCriteria} 
		{foreach from=$results.results item=result} 
		  {assign var=itemId value=$result.itemId} 
		  {g->row}
		    {g->column}
		      {g->link url_view="core:ShowItem" url_itemId=$itemId}
			{g->image item=$SearchScan.items.$itemId image=$SearchScan.thumbnails.$itemId}
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
	  {/foreach}
	{/g->box}
      {/if}
    {/g->pagebox}
  {/g->main}
{/g->form}
