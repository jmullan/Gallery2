      {galleryForm view="$view" method="GET"}
      {galleryInput type="hidden" name="formName"}Search{/galleryInput}

      <!-- Embed the hidden return fields -->
      {foreach from=$return key=key item=value}
      {galleryInput type="hidden" name=$key|string_format:"return.%s"}{$value}{/galleryInput}
      {/foreach}
      
    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td colspan="2" align="center">
	    {galleryBiggerFontSize}
	    {galleryText text="Search the Gallery"}
	    {/galleryBiggerFontSize}
	  </td>
	</tr>

	<!-- {if !empty($return)} -->
	<tr>
	  <td colspan="2" align="center">
	    <a href="{galleryUrl view=$return.view itemId=$return.itemId}">
	      [{galleryText text="Back to Gallery"}]
	    </a>
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td colspan="2">
	    {galleryText text="Search for: "}
	    {galleryInput type="text" size="50" name="form.searchCriteria"}{$form.searchCriteria}{/galleryInput}
	    {galleryInput type="submit" name="form.action.search"}
	    {galleryText text="Search"}
	    {/galleryInput}
	  </td>
	</tr>

	<!-- {if isset($form.error.searchCriteria.missing)} -->
	<tr>
	  <td colspan="2">
	    {galleryErrorFontColor}
	    {galleryText text="You must enter some text to search for!"}
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->
	
	<!-- {foreach from=$modules key=moduleId item=moduleInfo} -->
	<tr>
	  <td colspan="2">
	    {galleryBigFontSize}
	    {$moduleInfo.name}
	    {/galleryBigFontSize}
	  </td>
	</tr>
	
	<!-- {foreach from=$moduleInfo.options key=optionId item=optionInfo} -->
	<tr>
	  <td>
	    &nbsp;
	  </td>
	  <td>
	    {capture name=checkboxName}form.options.{$moduleId}.{$optionId}{/capture}
	    {galleryInput type="checkbox" name=$smarty.capture.checkboxName}{$optionInfo.enabled}{/galleryInput}
	    {$optionInfo.description}
	  </td>
	</tr>
	<!-- {/foreach} -->
	<!-- {/foreach} -->
    </table>


    <!-- {if isset($searchResults)} -->
    <table border="0" cellspacing="0" cellpadding="0" width="100%">

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="6" align="center">
	    {galleryBiggerFontSize}
	    {galleryText text="Search Results"}
	    {/galleryBiggerFontSize}
	  </td>
	</tr>

	<!-- {foreach from=$searchResults key=moduleId item=resultIds} -->
	<tr>
	  <td colspan="6">
	    {galleryBigFontSize}
	    {$modules.$moduleId.name}
	    {/galleryBigFontSize}
	  </td>
	</tr>

	<!-- {foreach from=$resultIds item=resultId} -->
	<tr>
	  <td width="20" rowspan="2">
	    &nbsp;
	  </td>
	  <td rowspan="2" valign="top">
	    <a href="{galleryUrl view=core:ShowItem itemId=$resultId}">
	      {if isset($searchResultThumbnails.$resultId)}
	      <img src="{galleryUrl view=core:DownloadItem itemId=$searchResultThumbnails.$resultId.id}"
	      {if ! empty($searchResultThumbnails.$resultId.width)}
	      width="{$searchResultThumbnails.$resultId.width}"
	      height="{$searchResultThumbnails.$resultId.height}"
	      {/if}
	      >
	      {else}
	      {galleryText text="No thumbnail"}
	      {/if}
	    </a>
	  </td>
	  <td width="10" rowspan="2">
	    &nbsp;
	  </td>
	  <td valign="top" align="right">
	    <b>{galleryText text="Title: "}</b>
	  </td>
	  <td width="10" rowspan="2">
	    &nbsp;
	  </td>
	  <td valign="top" width="100%">
	    {$searchResultItems.$resultId.title|default:"&nbsp;"}
	  </td>
	</tr>
	
	<tr>
	  <td valign="top" align="right">
	    <b>{galleryText text="Description: "}</b>
	  </td>
	  <td valign="top">
	    {$searchResultItems.$resultId.description|default:"&nbsp;"}
	  </td>
	</tr>

	<!-- {* spacer row *} -->
	<tr>
	  <td colspan="6">
	    &nbsp;
	  </td>
	</tr>

	<!-- {foreachelse} -->
	<tr>
	  <td width="20">
	    &nbsp;
	  </td>
	  <td colspan="5">
	    {galleryText text="No results"}
	  </td>
	</tr>
	<!-- {/foreach} -->
	<!-- {/foreach} -->
    </table>
    <!-- {/if} -->
    {/galleryForm}
    