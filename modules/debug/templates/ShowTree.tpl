      {galleryForm view="$view" method="GET"}
      {galleryInput type="hidden" name="formName"}FilterMembers{/galleryInput}
      {galleryInput type="hidden" name="itemId"}{$itemId}{/galleryInput}
  
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {galleryBiggerFontSize}
	      {galleryText text="Debug Tree"}
	      {/galleryBiggerFontSize}
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
	    {galleryText text="Filter members-names with regexp:"}
	    {galleryInput type="text" size="20" name="form.filterMembers"}{$form.filterMembers}{/galleryInput}
	    {galleryInput type="submit" name="form.action.filter"}
	    {galleryText text="Filter"}
	    {/galleryInput}
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
	      <a href="{galleryUrl view="core:ShowItem" itemId=$entity.itemId}">
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
    {/galleryForm}

