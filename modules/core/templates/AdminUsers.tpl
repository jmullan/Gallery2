  {galleryForm controller="$controller"}
  <table width="100%" border="0" cellspacing="3" cellpadding="3">

    <tr>
      <td colspan="2" align="center">
	{galleryBiggerFont}
	{galleryText text="User Management"}
	{/galleryBiggerFont}
	<br>
	{galleryBigFont}
	{galleryText one="There %d user in the system." 
	             many="There are %d total users in the system." 
	             count=$totalUserCount
	             arg1=$totalUserCount}
	{/galleryBigFont}
      </td>
    </tr>

    <tr>
      <td valign="top">
	{galleryLightFrame}
	<table width="100%" border="0">
	  <tr>
	    <td>
	      {galleryText text="If you know the username you'd like to work with, you can enter it here."}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {galleryInput type="input" name="form.text.username" size="20"}{$form.text.username}{/galleryInput}
	      {galleryInput type="submit" name="form.action.editFromText"}{galleryText text="Edit"}{/galleryInput}
	      {galleryInput type="submit" name="form.action.deleteFromText"}{galleryText text="Delete"}{/galleryInput}
	    </td>	
	  </tr>

	  <tr>
	    <td>
	      <br><br>
	      {galleryText text="Or you can create a new user here."}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {galleryInput type="submit" name="form.action.create"}{galleryText text="Create"}{/galleryInput}
	    </td>
	  </tr>
	</table>
	{/galleryLightFrame}
      </td>
      <td>
	{galleryLightFrame}
	<table width="100%" border="0">
	  <tr>
	    <td>
	      {galleryText text="If you don't know the username you'd like to work with, you can browse or search for it here."}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {gallerySelect name="form.list.username" size=$form['list']['pageSize']}
	      {html_options values=$form['list']['usernames'] output=$form['list']['usernames']}
	      {/gallerySelect}
	      {if (!empty($form.list.filter))}
	      <br>
	      {galleryText one="%d user matches your filter"
			   many="%d users match your filter"
			   count=$form.list.count
			   arg1=$form.list.count}
	      {/if}
	      {if ($form.list.maxPages > 1)}
	      <br>
	      {galleryText text="Viewing page %d of %d"
		arg1=$form.list.page
		arg2=$form.list.maxPages}
	      {/if}
	      {galleryInput type="hidden" name="form.list.page"}{$form.list.page}{/galleryInput}
	      {galleryInput type="hidden" name="form.list.maxPages"}{$form.list.maxPages}{/galleryInput}
	    </td>
	  </tr>

	  <tr>
	    <td align="center">
	      {galleryInput type="submit" name="form.action.editFromList"}{galleryText text="Edit"}{/galleryInput}
	      {galleryInput type="submit" name="form.action.deleteFromList"}{galleryText text="Delete"}{/galleryInput}
	    </td>
	  </tr>
	  <tr>
	    <td align="center">
	      {if ($form.list.page > 1)}
	      {galleryInput type="submit" name="form.action.firstPage"}{galleryText text="|< First"}{/galleryInput}
	      {galleryInput type="submit" name="form.action.backPage"}{galleryText text="<< Back"}{/galleryInput}
	      {/if}
	      {if ($form.list.page < $form.list.maxPages)}
	      {galleryInput type="submit" name="form.action.nextPage"}{galleryText text="Next >>"}{/galleryInput}
	      {galleryInput type="submit" name="form.action.lastPage"}{galleryText text="Last >|"}{/galleryInput}
	      {/if}
	    </td>
	  </tr>
	  <tr>
	    <td align="center">
	      {galleryInput type="submit" name="form.action.filterClear"}{galleryText text="Clear"}{/galleryInput}
	      {galleryInput type="submit" name="form.action.filterBySubstring"}{galleryText text="Filter:"}{/galleryInput}
	      {galleryInput type="text" name="form.list.filter"}{$form.list.filter}{/galleryInput}
	    </td>
	  </tr>
	</table>
	{/galleryLightFrame}
      </td>
    </tr>
  </table>
  {/galleryForm}

  