      {gallery->form controller=$controller method="GET"}
      {gallery->input type="hidden" name="form.formName"}SearchShowAll{/gallery->input}
      {gallery->input type="hidden" name="form.moduleId"}{$form.moduleId}{/gallery->input}
      {gallery->input type="hidden" name="form.page"}{$form.page}{/gallery->input}

      <!-- Embed the hidden return fields -->
      {foreach from=$return key=key item=value}
      {gallery->input type="hidden" name=return.$key}{$value}{/gallery->input}
      {/foreach}

      {gallery->thinFrame width="100%"}
    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td colspan="2" align="center">
	    {gallery->highlight1}
	    {gallery->biggerFontSize}
	    <center>
	    {gallery->text text="Search the Gallery"}
	    </center>
	    {/gallery->biggerFontSize}

	    {if !empty($return)}
	    <center>
	    <a href="{gallery->url view=$return.view itemId=$return.itemId}">
	      [{gallery->text text="Back to Gallery"}]
	    </a>
	    </center>
	    {/gallery->highlight1}
	    {/if}
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->text text="Search for: "}
	    {gallery->input type="text" size="50" name="form.searchCriteria"}{$form.searchCriteria}{/gallery->input}
	    {gallery->input type="submit" name="form.action.search"}
	    {gallery->text text="Search"}
	    {/gallery->input}
	  </td>
	</tr>

	<!-- {if isset($form.error.searchCriteria.missing)} -->
	<tr>
	  <td colspan="2">
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter some text to search for!"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->
	
	<tr>
	  <td colspan="2">
	    {gallery->highlight2}
	    {gallery->bigFontSize}
	    {$moduleInfo.name}
	    {/gallery->bigFontSize}
	    {/gallery->highlight2}
	  </td>
	</tr>
	
	<!-- {foreach from=$moduleInfo.options key=optionId item=optionInfo} -->
	<tr>
	  <td>
	    &nbsp;
	  </td>
	  <td>
	    {capture name=checkboxName}form.options.{$moduleId}.{$optionId}{/capture}
	    {gallery->input type="checkbox" name=$smarty.capture.checkboxName}
	    {if isset($form.options.$moduleId.$optionId)}1{/if}
	    {/gallery->input}
	    {$optionInfo.description}
	  </td>
	</tr>
	<!-- {/foreach} -->
    </table>
    {/gallery->thinFrame}

    <br>

    <!-- {if !empty($searchResults)} -->
    {gallery->thinFrame}
    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td colspan="6">
	    {gallery->highlight1}
	    {gallery->biggerFontSize}
	    <center>
	      {gallery->text text="Search Results"}
	    </center>
	    {/gallery->biggerFontSize}
	    {gallery->bigFontSize}
	    <center>
	      {gallery->text text="Searching %s only" arg1=$moduleInfo.name}
	      <br>
	      {gallery->input type="submit" name="form.action.scan"}
	      {gallery->text text="Search all modules"}
	      {/gallery->input}
	    </center>
	    {/gallery->bigFontSize}
	    {/gallery->highlight1}
	  </td>
	</tr>

	<tr>
	  <td colspan="6">
	    {gallery->highlight2}
	    {gallery->bigFontSize}
	    {$moduleInfo.name}
	    {/gallery->bigFontSize}
	    &nbsp;
	    &nbsp;
	    &nbsp;
	    {if ($searchResults.count > 0)}
	    {if ($form.page > 1)}
	    {gallery->input type="submit" name="form.action.previousPage"}
	    {gallery->text text="<< Previous"}
	    {/gallery->input}
	    {/if}
	    
	    {gallery->text text="(Results %d - %d of %d, Page %d of %d)"
	                 arg1=$searchResults.start
	                 arg2=$searchResults.end
	                 arg3=$searchResults.count
	                 arg4=$form.page
	                 arg5=$maxPages}
	    {/if}

	    {if ($form.page < $maxPages)}
	    {gallery->input type="submit" name="form.action.nextPage"}
	    {gallery->text text="Next >>"}
	    {/gallery->input}
	    {/if}

	    {/gallery->highlight2}
	  </td>
	</tr>

	<tr>
	  <td colspan="6">
	    &nbsp;
	  </td>
	</tr>

	<!-- {foreach from=$searchResults.ids item=resultId} -->
	<tr>
	  <td rowspan="2">
	    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	  </td>
	  <td rowspan="2" valign="top">
	    <a href="{gallery->url view=core:ShowItem itemId=$resultId}">
	      {if isset($searchResultThumbnails.$resultId)}
	      <img src="{gallery->url view=core:DownloadItem itemId=$searchResultThumbnails.$resultId.id}"
	      {if ! empty($searchResultThumbnails.$resultId.width)}
	      width="{$searchResultThumbnails.$resultId.width}"
	      height="{$searchResultThumbnails.$resultId.height}"
	      {/if}
	      border="0"
	      >
	      {else}
	      {gallery->text text="No thumbnail"}
	      {/if}
	    </a>
	  </td>
	  <td width="10" rowspan="2">
	    &nbsp;
	  </td>
	  <td valign="top" align="right">
	    <b>{gallery->text text="Title: "}</b>
	  </td>
	  <td width="10" rowspan="2">
	    &nbsp;
	  </td>
	  <td valign="top" width="100%">
	    {$searchResultItems.$resultId.title|default:"&nbsp;"|replace:$form.searchCriteria:"<b>$`form.searchCriteria`</b>"}
	  </td>
	</tr>
	
	<tr>
	  <td valign="top" align="right">
	    <b>{gallery->text text="Description: "}</b>
	  </td>
	  <td valign="top">
	    {$searchResultItems.$resultId.description|default:"&nbsp;"|replace:$form.searchCriteria:"<b>$`form.searchCriteria`</b>"}
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
	    {gallery->text text="No results"}
	  </td>
	</tr>
	<!-- {/foreach} -->
    </table>
    {/gallery->thinFrame}
    <!-- {/if} -->

    {/gallery->form}
    