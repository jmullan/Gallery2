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
      {if isset($status.movedUp.summary)}
	{g->text one="Moved %d property up in the Summary view"
	         many="Moved %d properties up in the Summary view"
	         count=$status.movedUp.summary
	         arg1=$status.movedUp.summary}
      {/if}
      {if isset($status.movedDown.summary)}
	{g->text one="Moved %d property down in the Summary view"
	         many="Moved %d properties down in the Summary view"
	         count=$status.movedDown.summary
	         arg1=$status.movedDown.summary}
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
      {if isset($status.movedUp.detailed)}
	{g->text one="Moved %d property up in the Detailed view"
	         many="Moved %d properties up in the Detailed view"
	         count=$status.movedUp.detailed
	         arg1=$status.movedUp.detailed}
      {/if}
      {if isset($status.movedDown.detailed)}
	{g->text one="Moved %d property down in the Detailed view"
	         many="Moved %d properties down in the Detailed view"
	         count=$status.movedDown.detailed
	         arg1=$status.movedDown.detailed}
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
      {if isset($form.error.available.missing) || isset($form.error.summary.missing) || isset($form.error.detailed.missing)}
	{g->row}
	  {g->column colspan="3"}
	    {g->error}
	      {if isset($form.error.available.missing)}
		{g->text text="You must select at least one value in the available column"}
	      {/if}
	      {if isset($form.error.summary.missing)}
		{g->text text="You must select at least one value in the summary column"}
	      {/if}
	      {if isset($form.error.detailed.missing)}
		{g->text text="You must select at least one value in the detailed column"}
	      {/if}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}
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
	  {g->input type="submit" name="form[action][moveUpSummary]"}
	    {g->text text="Up"}
	  {/g->input}
	  {g->input type="submit" name="form[action][moveDownSummary]"}
	    {g->text text="Down"}
	  {/g->input}
	{/g->column}
	{g->column}
	  {g->input type="submit" name="form[action][removeFromDetailed]"}
	    {g->text text="Remove"}
	  {/g->input}
	  {g->input type="submit" name="form[action][moveUpDetailed]"}
	    {g->text text="Up"}
	  {/g->input}
	  {g->input type="submit" name="form[action][moveDownDetailed]"}
	    {g->text text="Down"}
	  {/g->input}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}
  
  {g->box style="admin"}
    {g->title}
      {g->text text="Reset to Defaults"}
    {/g->title}
    {g->description}
      {g->text text="Restore the original values for the Summary and Detailed views.  Use with caution, there is no undo!"}
    {/g->description}
    {g->element}
      {g->input type="submit" name="form[action][resetSummary]"}
	{g->text text="Restore Summary Defaults"}
      {/g->input}
      {g->input type="submit" name="form[action][resetDetailed]"}
	{g->text text="Restore Detailed Defaults"}
      {/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}