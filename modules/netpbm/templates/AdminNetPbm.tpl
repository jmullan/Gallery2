      {gallery->form controller="$controller"}
      {gallery->input type="hidden" name="formName"}AdminNetPbm{/gallery->input}

      <!-- Embed the hidden return fields -->
      {foreach from=$return key=key item=value}
      {gallery->input type="hidden" name=return.$key}{$value}{/gallery->input}
      {/foreach}
      
    <table>

	<tr>
	  <td colspan="2" align="center">
	    {gallery->biggerFontSize}
	    {gallery->text text="NetPBM Settings"}
	    {/gallery->biggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->text text="NetPBM is a graphics toolkit that can be used to process images that you upload to Gallery.  You must install the NetPBM binaries on your machine, then enter the path to them in the text box below.  If you're on a Unix machine, don't forget to make the binaries executable (<i>chmod 755 *</i> in the NetPBM directory should do it)"}
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->bigFontSize}
	    {gallery->text text="Defaults"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {gallery->text text="Path to NetPBM:"}
	  </td>
	  <td>
	    {gallery->input type="text" name="form.path"}{$form.path}{/gallery->input}
	  </td>
	</tr>

	<!-- {if isset($form.error.path.missing)} -->
	<tr>
	  <td colspan="2" align="center">
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a path to your NetPBM binaries"}
	    {/gallery->errorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>	
	  <td align="right">
	    {gallery->text text="PNM to JPEG converter"}
	  </td>
	  <td>
	    {gallery->select name="form.pnmtojpeg"}
	    {html_options values=$pnmToJpegList selected=$form.pnmtojpeg output=$pnmToJpegList}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {gallery->text text="JPEG Quality"}
	  </td>
	  <td>
	    {gallery->select name="form.jpegQuality"}
	    {html_options values=$jpegQualityList selected=$form.jpegQuality output=$jpegQualityList}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2" align="center">
	    {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save Settings"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.test"}{gallery->text text="Test Settings"}{/gallery->input}
	    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

    {if !empty($tests)}
    <tr>
      <td align="center" colspan="2">
	<table width="50%" cellpadding="0" cellspacing="0" border="1">
	    <tr>
	      <td colspan="2" align="center">
		{gallery->bigFontSize}
		{gallery->text text="NetPBM binary test results"}
		{/gallery->bigFontSize}
	      </td>
	    </tr>
	    <tr>
	      <th> {gallery->text text="Binary Name"} </th>
	      <th> {gallery->text text="Pass/Fail"} </th>
	    </tr>
	{foreach from=$tests item=test}
	<tr>
	  <td align="center" valign="top">
	    {$test.name}
	  </td>
	  <td align="center">
	    {if ($test.success)}
	    {gallery->successFontColor}{gallery->text text="Passed"}{/gallery->successFontColor}
	    {else}
	    {gallery->errorFontColor}{gallery->text text="Failed"}{/gallery->errorFontColor}
	    {/if}
	  </td>
	</tr>

	{if empty($test.success) && !empty($test.results)}
	<tr>
	  <td colspan="2">
	    {gallery->text text="Error messages:"}
	    <br>
	    {foreach from=$test.results item=line}
	    <pre>{$line}</pre>
	    {/foreach}
	  </td>
	</tr>
	{/if}

	{/foreach}
      </table>
      </td>
    </tr>
    {/if}

  </table>
    {/gallery->form}
    
