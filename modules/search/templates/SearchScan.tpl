      {galleryForm controller=$controller method="GET"}
      {galleryInput type="hidden" name="formName"}SearchScan{/galleryInput}

      <!-- Embed the hidden return fields -->
      {foreach from=$return key=key item=value}
      {galleryInput type="hidden" name=$key|string_format:"return.%s"}{$value}{/galleryInput}
      {/foreach}

      {galleryThinFrame width="100%"}
    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td colspan="2" align="center">
	    {galleryHighlight1}
	    {galleryBiggerFontSize}
	    <center>
	    {galleryText text="Search the Gallery"}
	    </center>
	    {/galleryBiggerFontSize}

	    {if !empty($return)}
	    <center>
	    <a href="{galleryUrl view=$return.view itemId=$return.itemId}">
	      [{galleryText text="Back to Gallery"}]
	    </a>
	    </center>
	    {/galleryHighlight1}
	    {/if}
	  </td>
	</tr>

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
	    {galleryHighlight2}
	    {galleryBigFontSize}
	    {$moduleInfo.name}
	    {/galleryBigFontSize}
	    {/galleryHighlight2}
	  </td>
	</tr>
	
	<!-- {foreach from=$moduleInfo.options key=optionId item=optionInfo} -->
	<tr>
	  <td>
	    &nbsp;
	  </td>
	  <td>
	    {capture name=checkboxName}form.options.{$moduleId}.{$optionId}{/capture}
	    {galleryInput type="checkbox" name=$smarty.capture.checkboxName}
	    {if isset($form.options.$moduleId.$optionId)}1{/if}
	    {/galleryInput}
	    {$optionInfo.description}
	  </td>
	</tr>
	<!-- {/foreach} -->
	<!-- {/foreach} -->
    </table>
    {/galleryThinFrame}

    <br>

    <!-- {if !empty($searchResults)} -->
    {galleryThinFrame}
    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td colspan="6">
	    {galleryHighlight1}
	    {galleryBiggerFontSize}
	    <center>
	      {galleryText text="Search Results"}
	    </center>
	    {/galleryBiggerFontSize}
	    {/galleryHighlight1}
	  </td>
	</tr>

	<!-- {foreach from=$searchResults key=moduleId item=results} -->
	<tr>
	  <td colspan="6">
	    {galleryHighlight2}
	    {galleryBigFontSize}
	    {$modules.$moduleId.name}
	    {/galleryBigFontSize}
	    &nbsp;
	    &nbsp;
	    &nbsp;
	    {if ($results.count > 0)}
	    {galleryText text="(Results %d - %d)"
	                 arg1=$results.start
	                 arg2=$results.end}
	    {/if}
	    {if ($results.count > $results.end)}
	    {assign var="moduleId" value=$moduleId}
	    {galleryInput type="submit" name="form.action.showAll.$moduleId"}
	    {galleryText text="Show all %d" arg1=$results.count}
	    {/galleryInput}
	    {/if}
	    {/galleryHighlight2}
	  </td>
	</tr>

	<tr>
	  <td colspan="6">
	    &nbsp;
	  </td>
	</tr>

	<!-- {foreach from=$results.ids item=resultId} -->
	<tr>
	  <td rowspan="2">
	    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	  </td>
	  <td rowspan="2" valign="top">
	    <a href="{galleryUrl view=core:ShowItem itemId=$resultId}">
	      {if isset($searchResultThumbnails.$resultId)}
	      <img src="{galleryUrl view=core:DownloadItem itemId=$searchResultThumbnails.$resultId.id}"
	      {if ! empty($searchResultThumbnails.$resultId.width)}
	      width="{$searchResultThumbnails.$resultId.width}"
	      height="{$searchResultThumbnails.$resultId.height}"
	      {/if}
	      border="0"
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
	    {$searchResultItems.$resultId.title|default:"&nbsp;"|replace:$form.searchCriteria:"<b>$form[searchCriteria]</b>"}
	  </td>
	</tr>
	
	<tr>
	  <td valign="top" align="right">
	    <b>{galleryText text="Description: "}</b>
	  </td>
	  <td valign="top">
	    {$searchResultItems.$resultId.description|default:"&nbsp;"|replace:$form.searchCriteria:"<b>$form[searchCriteria]</b>"}
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
    {/galleryThinFrame}
    <!-- {/if} -->

    {/galleryForm}
    