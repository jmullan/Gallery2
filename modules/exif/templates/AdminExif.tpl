{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="EXIF Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.added.summary)}
	{g->text one="Added %d property to the Summary view"
	         many="Added %d properties to the Summary view"
	         count=$status.added.summary
	         arg1=$status.added.summary}
      {/if}
      {if isset($status.removed.summary)}
	{g->text one="Removed %d property from the Summary view"
	         many="Removed %d properties from the Summary view"
	         count=$status.removed.summary
	         arg1=$status.removed.summary}
      {/if}
      {if isset($status.restored.summary)}
	{g->text text="Restored the default properties for the Summary view"}
      {/if}
      {if isset($status.added.detailed)}
	{g->text one="Added %d property to the Detailed view"
	         many="Added %d properties to the Detailed view"
	         count=$status.added.detailed
	         arg1=$status.added.detailed}
      {/if}
      {if isset($status.removed.detailed)}
	{g->text one="Removed %d property from the Detailed view"
	         many="Removed %d properties from the Detailed view"
	         count=$status.removed.detailed
	         arg1=$status.removed.detailed}
      {/if}
      {if isset($status.restored.detailed)}
	{g->text text="Restored the default properties for the Detailed view"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text text="Gallery can display the EXIF data that is embedded in photos taken by most digital cameras."}
    {/g->description}
  {/g->box}

  {g->box style="admin"}
    {g->title}
      {g->text text="Summary and Detailed EXIF displays"}
    {/g->title}
    {g->description}
      {g->text text="There can be a great deal of EXIF information stored in photos from modern digital cameras.  We display that data in two different views, summary and detailed.  You can choose which properties are displayed in each view."}
    {/g->description}

    {g->table style="admin_widgets"}
      {g->row}
	{g->column header="true"}
	  {g->text text="Available"}
	{/g->column}
	{g->column header="true"}
	  {g->text text="Summary"}
	{/g->column}
	{g->column header="true"}
	  {g->text text="Detailed"}
	{/g->column}
      {/g->row}
      {g->row}
	{g->column}
	  {g->select name="form[available][]" size="20" multiple="true"}
	    {html_options options=$AdminExif.availableList}
	  {/g->select}
	{/g->column}
	{g->column}
	  {g->select name="form[summary][]" size="20" multiple="true"}
	    {html_options options=$AdminExif.summaryList}
	  {/g->select}
	{/g->column}
	{g->column}
	  {g->select name="form[detailed][]" size="20" multiple="true"}
	    {html_options options=$AdminExif.detailedList}
	  {/g->select}
	{/g->column}
      {/g->row}
      {g->row}
	{g->column}
	  {g->input type="submit" name="form[action][availableToSummary]"}
	    {g->text text="Add to Summary"}
	  {/g->input}
	  {g->input type="submit" name="form[action][availableToDetailed]"}
	    {g->text text="Add to Detailed"}
	  {/g->input}
	{/g->column}
	{g->column}
	  {g->input type="submit" name="form[action][removeFromSummary]"}
	    {g->text text="Remove"}
	  {/g->input}
	  {g->input type="submit" name="form[action][resetSummary]"}
	    {g->text text="Restore Defaults"}
	  {/g->input}
	{/g->column}
	{g->column}
	  {g->input type="submit" name="form[action][removeFromDetailed]"}
	    {g->text text="Remove"}
	  {/g->input}
	  {g->input type="submit" name="form[action][resetDetailed]"}
	    {g->text text="Restore Defaults"}
	  {/g->input}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}
{/g->pagebox}