{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="EXIF Settings"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->description}
      {g->text text="Gallery can display the EXIF data that is embedded in photos taken by most digital cameras."}
    {/g->description}
  {/g->box}

  {g->tabbedbox}
    {g->tabset}
      {if $AdminExif.mode == 'general'}
	{g->item selected="true"}
	  {g->title}
	    {g->text text="Module Settings"}
	  {/g->title}
	{/g->item}
      {else}
	{g->item}
	  {g->title}
	    {g->link url_view="core:SiteAdmin" url_subView="exif:AdminExif" url_mode="general"}
	      {g->text text="Module Settings"}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/if}

      {if $AdminExif.mode == 'simpleAndAdvanced'}
	{g->item selected="true"}
	  {g->title}
	    {g->text text="Simple/Advanced"}
	  {/g->title}
	{/g->item}
      {else}
	{g->item}
	  {g->title}
	    {g->link url_view="core:SiteAdmin" url_subView="exif:AdminExif" url_mode="simpleAndAdvanced"}
	      {g->text text="Simple/Advanced"}
	    {/g->link}
	  {/g->title}
	{/g->item}
      {/if}
    {/g->tabset}

    {g->element}
      {if $AdminExif.mode == 'general'}
	{g->box style="admin"}
	  {g->title}
	    {g->text text="Basic settings"}
	  {/g->title}

	{/g->box}
      {/if}

      {if $AdminExif.mode == 'simpleAndAdvanced'}
	{g->box style="admin"}
	  {g->description}
	    {g->text text="There can be a great deal of EXIF information stored in photos from modern digital cameras.  We display that data in two different views, simple and advanced.  You can choose which properties are displayed in each view."}
	  {/g->description}

	  {g->table style="admin_listing" evenodd="true"}
	    {g->row}
	      {g->column header="true"}
		{g->text text="Property"}
	      {/g->column}
	      {g->column header="true"}
		{g->text text="Simple Only"}
	      {/g->column}
	      {g->column header="true"}
		{g->text text="Simple And Advanced"}
	      {/g->column}
	      {g->column header="true"}
		{g->text text="Hidden"}
	      {/g->column}
	    {/g->row}
	    {foreach from=$AdminExif.keys key=key item=data}
	      {g->row}
		{g->column}
		  {$data.title}
		{/g->column}
		{g->column}
		  {g->input type="radio" name="form[$key]"}
		    {if $AdminExif.keys[$key].status == 'simple'}
		      1
		    {/if}
		  {/g->input}
		{/g->column}
		{g->column}
		  {g->input type="radio" name="form[$key]"}
		    {if $AdminExif.keys[$key].status == 'advanced'}
		      1
		    {/if}
		  {/g->input}
		{/g->column}
		{g->column}
		  {g->input type="radio" name="form[$key]"}
		    {if $AdminExif.keys[$key].status == 'hidden'}
		      1
		    {/if}
		  {/g->input}
		{/g->column}
	      {/g->row}
	    {/foreach}
	  {/g->table}
	{/g->box}
      {/if}
    {/g->element}
  {/g->tabbedbox}
{/g->pagebox}