      {gallery->form view="$view" method="GET"}
      {gallery->input type="hidden" name="formName"}FilterMembers{/gallery->input}
      {gallery->input type="hidden" name="itemId"}{$itemId}{/gallery->input}
  
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {gallery->biggerFontSize}
	      {gallery->text text="Debug Tree"}
	      {/gallery->biggerFontSize}
	    </center>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->text text="Filter members-names with regexp:"}
	    {gallery->input type="text" size="20" name="form.filterMembers"}{$form.filterMembers}{/gallery->input}
	    {gallery->input type="submit" name="form.action.filter"}
	    {gallery->text text="Filter"}
	    {/gallery->input}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	   <table>
	   {foreach from=$entityTree item=entity}
	    <tr valign="top">
	     <td>
	      <a href="{gallery->url view="core:ShowItem" itemId=$entity.itemId}">
	      <strong>{$entity.completePath}</strong>
	      </a>
	     </td>
	     <td>
	      <table cellpadding="0" cellspacing="0">
	      {foreach item=data key=member from=$entity.members}
	       <tr>
		<td><em>{$member}:</em>&nbsp;</td>
		<td>{$data}</td>
	       </tr>
	      {/foreach}
	      </table>
	     </td>
	    </tr>
	    <tr valign="top">
	     <td colspan="2"><hr noshade size="1"></td>
	    </tr>
	   {/foreach}
	   </table>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

    </table>
    {/gallery->form}

