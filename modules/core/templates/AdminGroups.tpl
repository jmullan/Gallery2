  {gallery->form controller="$controller"}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td colspan="2" align="center">
	{gallery->biggerFontSize}
	{gallery->text text="Group Management"}
	{/gallery->biggerFontSize}
	<br>
	{gallery->bigFontSize}
	{gallery->text one="There is %d group in the system." 
	             many="There are %d total groups in the system." 
	             count=$totalGroupCount
	             arg1=$totalGroupCount}
	{/gallery->bigFontSize}
      </td>
    </tr>

    <tr>
      <td valign="top">
	{gallery->lightFrame}
	<table width="100%" border="0">
	  <tr>
	    <td>
	      {gallery->text text="If you know the group name you'd like to work with, you can enter it here."}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {gallery->input type="text" name="form.text.groupName" size="20"}{$form.text.groupName}{/gallery->input}
	      {gallery->input type="submit" name="form.action.editFromText"}{gallery->text text="Edit"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.deleteFromText"}{gallery->text text="Delete"}{/gallery->input}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {gallery->input type="submit" name="form.action.addRemoveUsersFromText"}{gallery->text text="Add/Remove Users"}{/gallery->input}
	    </td>	
	  </tr>

	  {if isset($form.error.text.noSuchGroup)}
	  <tr>
	    <td align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="Group '%s' does not exist."
	                   arg1=$form.text.groupName}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}

	  {if isset($form.error.text.noGroupSpecified)}
	  <tr>
	    <td align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="You must enter a group name"}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}

	  <tr>
	    <td>
	      <br><br>
	      {gallery->text text="Or you can create a new group here."}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {gallery->input type="submit" name="form.action.create"}{gallery->text text="Create"}{/gallery->input}
	    </td>
	  </tr>
	</table>
	{/gallery->lightFrame}
      </td>
      <td>
	{gallery->lightFrame}
	<table width="100%" border="0">
	  <tr>
	    <td>
	      {gallery->text text="If you don't know the group name you'd like to work with, you can browse or search for it here."}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {gallery->select name="form.list.groupId" size=$form.list.pageSize}
	      {html_options options=$form.list.groupNames}
	      {/gallery->select}
	      {if (!empty($form.list.filter))}
	      <br>
	      {gallery->text one="%d group matches your filter"
			   many="%d groups match your filter"
			   count=$form.list.count
			   arg1=$form.list.count}
	      {/if}
	      {if ($form.list.maxPages > 1)}
	      <br>
	      {gallery->text text="Viewing page %d of %d"
		arg1=$form.list.page
		arg2=$form.list.maxPages}
	      {/if}
	      {gallery->input type="hidden" name="form.list.page"}{$form.list.page}{/gallery->input}
	      {gallery->input type="hidden" name="form.list.maxPages"}{$form.list.maxPages}{/gallery->input}
	    </td>
	  </tr>

	  {if isset($form.error.list.noGroupSelected)}
	  <tr>
	    <td align="center">
	      {gallery->errorFontColor}
	      {gallery->text text="You must select a group"}
	      {/gallery->errorFontColor}
	    </td>
	  </tr>
	  {/if}

	  <tr>
	    <td align="center">
	      {gallery->input type="submit" name="form.action.editFromList"}{gallery->text text="Edit"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.addRemoveUsersFromList"}{gallery->text text="Add/Remove Users"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.deleteFromList"}{gallery->text text="Delete"}{/gallery->input}
	    </td>
	  </tr>
	  <tr>
	    <td align="center">
	      {if ($form.list.page > 1)}
	      {gallery->input type="submit" name="form.action.firstPage"}{gallery->text text="|< First"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.backPage"}{gallery->text text="<< Back"}{/gallery->input}
	      {/if}
	      {if ($form.list.page < $form.list.maxPages)}
	      {gallery->input type="submit" name="form.action.nextPage"}{gallery->text text="Next >>"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.lastPage"}{gallery->text text="Last >|"}{/gallery->input}
	      {/if}
	    </td>
	  </tr>
	  <tr>
	    <td align="center">
	      {gallery->input type="submit" name="form.action.filterClear"}{gallery->text text="Clear"}{/gallery->input}
	      {gallery->input type="submit" name="form.action.filterBySubstring"}{gallery->text text="Filter:"}{/gallery->input}
	      {gallery->input type="text" name="form.list.filter"}{$form.list.filter}{/gallery->input}
	    </td>
	  </tr>
	</table>
	{/gallery->lightFrame}
      </td>
    </tr>
  </table>
  {/gallery->form}

  