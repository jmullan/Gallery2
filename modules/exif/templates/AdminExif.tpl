{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminExif.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="EXIF Settings"}
      </h2>
    </div>
    
  </div>

  {if isset($status)}
  <div id="gsStatus">
    {if isset($status.added.summary)}
    <div class="giStatus">
      {g->text one="Added %d property to the Summary view"
	       many="Added %d properties to the Summary view"
	       count=$status.added.summary
	       arg1=$status.added.summary}
    </div>
    {/if}
    {if isset($status.removed.summary)}
    <div class="giStatus">
      {g->text one="Removed %d property from the Summary view"
	       many="Removed %d properties from the Summary view"
	       count=$status.removed.summary
	       arg1=$status.removed.summary}
    </div>
    {/if}
    {if isset($status.restored.summary)}
    <div class="giStatus">
      {g->text text="Restored the default properties for the Summary view"}
    </div>
    {/if}
    {if isset($status.movedUp.summary)}
    <div class="giStatus">
      {g->text one="Moved %d property up in the Summary view"
	       many="Moved %d properties up in the Summary view"
	       count=$status.movedUp.summary
	       arg1=$status.movedUp.summary}
    </div>
    {/if}
    {if isset($status.movedDown.summary)}
    <div class="giStatus">
      {g->text one="Moved %d property down in the Summary view"
	       many="Moved %d properties down in the Summary view"
	       count=$status.movedDown.summary
	       arg1=$status.movedDown.summary}
    </div>
    {/if}
    {if isset($status.added.detailed)}
    <div class="giStatus">
      {g->text one="Added %d property to the Detailed view"
	       many="Added %d properties to the Detailed view"
	       count=$status.added.detailed
	       arg1=$status.added.detailed}
    </div>
    {/if}
    {if isset($status.removed.detailed)}
    <div class="giStatus">
      {g->text one="Removed %d property from the Detailed view"
	       many="Removed %d properties from the Detailed view"
	       count=$status.removed.detailed
	       arg1=$status.removed.detailed}
    </div>
    {/if}
    {if isset($status.restored.detailed)}
    <div class="giStatus">
      {g->text text="Restored the default properties for the Detailed view"}
    </div>
    {/if}
    {if isset($status.movedUp.detailed)}
    <div class="giStatus">
      {g->text one="Moved %d property up in the Detailed view"
	       many="Moved %d properties up in the Detailed view"
	       count=$status.movedUp.detailed
	       arg1=$status.movedUp.detailed}
    </div>
    {/if}
    {if isset($status.movedDown.detailed)}
    <div class="giStatus">
      {g->text one="Moved %d property down in the Detailed view"
	       many="Moved %d properties down in the Detailed view"
	       count=$status.movedDown.detailed
	       arg1=$status.movedDown.detailed}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Gallery can display the EXIF data that is embedded in photos taken by most digital cameras."}
    </p>
  </div>

  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Summary and Detailed EXIF displays"}
    </h3>
    <p class="giDescription">
      {g->text text="There can be a great deal of EXIF information stored in photos from modern digital cameras.  We display that data in two different views, summary and detailed.  You can choose which properties are displayed in each view."}
    </p>

    <table class="gbDataTable">
      <tr>
	<th>
	  {g->text text="Available"}
	</th>
	<th>
	  {g->text text="Summary"}
	</th>
	<th>
	  {g->text text="Detailed"}
	</th>
      </tr>

      <tr>
	<td>
	  <select name="{g->formVar var="form[available][]"}" size="20" multiple="multiple">
	    {html_options options=$AdminExif.availableList}
	  </select>
	</td>
	<td>
	  <select name="{g->formVar var="form[summary][]"}" size="20" multiple="multiple">
	      {html_options options=$AdminExif.summaryList}
	  </select>
	</td>
	<td>
	  <select name="{g->formVar var="form[detailed][]"}" size="20" multiple="multiple">
	      {html_options options=$AdminExif.detailedList}
	  </select>
	</td>
      </tr>

      {if isset($form.error.available.missing) || isset($form.error.summary.missing) || isset($form.error.detailed.missing)}
      <tr>
	<td colspan="3">
	  <div class="giError">
	    {if isset($form.error.available.missing)}
	    {g->text text="You must select at least one value in the available column"}
	    {/if}
	    {if isset($form.error.summary.missing)}
	    {g->text text="You must select at least one value in the summary column"}
	    {/if}
	    {if isset($form.error.detailed.missing)}
	    {g->text text="You must select at least one value in the detailed column"}
	    {/if}
	  </div>
	</td>
      </tr>
      {/if}

      <tr>
	<td>
	  <input type="submit" name="{g->formVar var="form[action][availableToSummary]"}" value="{g->text text="Add to Summary"}" class="button"/>
	  <input type="submit" name="{g->formVar var="form[action][availableToDetailed]"}" value="{g->text text="Add to Detailed"}" class="button"/>
	</td>

	<td>
	  <input type="submit" name="{g->formVar var="form[action][removeFromSummary]"}" value="{g->text text="Remove"}" class="button"/>
	  <input type="submit" name="{g->formVar var="form[action][moveUpSummary]"}" value="{g->text text="Up"}" class="button"/>
	  <input type="submit" name="{g->formVar var="form[action][moveDownSummary]"}" value="{g->text text="Down"}" class="button"/>
	</td>

	<td>
	  <input type="submit" name="{g->formVar var="form[action][removeFromDetailed]"}" value="{g->text text="Remove"}" class="button"/>
	  <input type="submit" name="{g->formVar var="form[action][moveUpDetailed]"}" value="{g->text text="Up"}" class="button"/>
	  <input type="submit" name="{g->formVar var="form[action][moveDownDetailed]"}" value="{g->text text="Down"}" class="button"/>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Reset to Defaults"}
    </h3>
    <p class="giDescription">
      {g->text text="Restore the original values for the Summary and Detailed views.  Use with caution, there is no undo!"}
    </p>

    <input type="submit" name="{g->formVar var="form[action][resetSummary]"}" value="{g->text text="Restore Summary Defaults"}" class="button"/>
    <input type="submit" name="{g->formVar var="form[action][resetDetailed]"}" value="{g->text text="Restore Detailed Defaults"}" class="button"/>
  </div>
</div>
