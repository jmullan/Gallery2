{gallery->form action_controller=$SearchScan.controller}
  {gallery->input type="hidden" name="form.formName"}SearchScan{/gallery->input}

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

      {foreach from=$SearchScan.modules key=moduleId item=moduleInfo}
	{gallery->detailedbox}
	  {gallery->title}
	    {$moduleInfo.name}
	  {/gallery->title}

	  {gallery->body}
	    {gallery->widget1box}
	      {foreach from=$moduleInfo.options key=optionId item=optionInfo}
		{gallery->widget1}
		  {gallery->title}
		    {$optionInfo.description}
		  {/gallery->title}
		  {gallery->body}
		    {capture name=checkboxName}form.options.{$moduleId}.{$optionId}{/capture}
		    {gallery->input type="checkbox" name=$smarty.capture.checkboxName}
		      {if isset($form.options.$moduleId.$optionId)}1{/if}
		    {/gallery->input}
		  {/gallery->body}
		{/gallery->widget1}
	      {/foreach}
	    {/gallery->widget1box}
	  {/gallery->body}
	{/gallery->detailedbox}
      {/foreach}

      {if !empty($SearchScan.searchResults)}
	{gallery->detailedbox}
	  {gallery->title}
	    {gallery->text text="Search Results"}
	  {/gallery->title}

	  {gallery->body}
	    {foreach from=$SearchScan.searchResults key=moduleId item=results}
	      {gallery->detailedbox}
		{gallery->title}
		  {$SearchScan.modules.$moduleId.name}
		  {if ($results.count > 0)}
		    {gallery->text text="(Results %d - %d)"
	            arg1=$results.start
	            arg2=$results.end}
		  {/if}
		  {if ($results.count > $results.end)}
		    {assign var="moduleId" value=$moduleId}
		    {gallery->input type="submit" name="form.action.showAll.$moduleId"}
		      {gallery->text text="Show all %d" arg1=$results.count}
		    {/gallery->input}
		  {/if}
		{/gallery->title}

		{gallery->body}
		  {gallery->table}
		    {assign var="searchCriteria" value=$form.searchCriteria} 
		    {foreach from=$results.results item=result} 
		      {assign var=itemId value=$result.itemId} 
		      {gallery->row}
			{gallery->column}
			  {gallery->link url_view="core:ShowItem" url_itemId=$itemId}
			    {gallery->image item=$SearchScan.items.$itemId image=$SearchScan.thumbnails.$itemId}
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
	    {/foreach}
	  {/gallery->body}
	{/gallery->detailedbox}
      {/if}
    {/gallery->component}
  {/gallery->main}
{/gallery->form}
