    {gallery->form controller="$controller" enctype="multipart/form-data"}
    {gallery->input type="hidden" name="form.formName"}ItemAddChildren{/gallery->input}
    {gallery->input type="hidden" name="itemId"}{$item.id}{/gallery->input}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {gallery->biggerFontSize}
	      {gallery->text text="Add Items to this Album"}
	      {/gallery->biggerFontSize}
	    </center>
	    <br>
	    {gallery->text text="Gallery can handle files of any format.  However, it can only create automatic resizes and thumbnails for certain types of files."}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {if $mode != 'fromBrowser'}
	    <a href="{gallery->url view="core:ItemAdmin" 
	                           subView="core:ItemAddChildren" 
	                           itemId=$item.id
	                           mode="fromBrowser"}">
	      {/if}
	      {gallery->text text="From Web Browser"}
	      {if $mode != 'fromBrowser'}
	    </a>
	    {/if}
	    &nbsp;
	    /
	    &nbsp;
	    {if $mode != 'fromLocalServer'}
	    <a href="{gallery->url view="core:ItemAdmin" 
                                   subView="core:ItemAddChildren" 
	                           itemId=$item.id
                                   mode="fromLocalServer"}">
	      {/if}
	      {gallery->text text="From Local Server"}
	      {if $mode != 'fromLocalServer'}
	    </a>
	    {/if}
	    &nbsp;
	    /
	    &nbsp;
	    {if $mode != 'fromWebPage'}
	    <a href="{gallery->url view="core:ItemAdmin" 
                                   subView="core:ItemAddChildren" 
	                           itemId=$item.id
	                           mode="fromWebPage"}">
	      {/if}
	      {gallery->text text="From Web Page"}
	      {if $mode != 'fromWebPage'}
	    </a>
	    {/if}
	  </td>
	</tr>

	<!-- {if $mode == 'fromBrowser'} -->
	<tr>
	  <td>
	    {gallery->text one="Upload a file directly from your computer."
	                   many="Upload up to %d files directly from your computer."
	                   count=$form.uploadBoxCount
	                   arg1=$form.uploadBoxCount}
	    {gallery->text text="Enter the full path to the file and an optional caption in the boxes below."}
	    {gallery->input type="hidden" name="form.uploadBoxCount"}{$form.uploadBoxCount}{/gallery->input}
	  </td>
	</tr>

	<tr>
	  <td>
	    <table border="0" cellspacing="2" cellpadding="0">
	      <!-- {section name="uploadBoxes" loop=$form.uploadBoxCount} -->
	      <!-- {assign var=iteration value=$smarty.section.uploadBoxes.iteration} -->
		<tr>
		  <td align="right">
		    <b>
		      {gallery->text text="File: "}
		    </b>
		  </td>
		  <td>
		    {gallery->input name=form.fileUpload.$iteration type="file" size="60"}{/gallery->input}
		  </td>
		</tr>
		<tr>
		  <td align="right" valign="top">
		    <b>
		      {gallery->text text="Caption: "}
		    </b>
		  </td>
		  <td>
		    {gallery->textArea rows="2" cols="60" name=form.fileUpload.$iteration.caption}{/gallery->textArea}
		  </td>
		</tr>

		<!-- {if empty($smarty.section.uploadBoxes.last)} -->
		<tr>
		  <td>
		    &nbsp;
		  </td>
		</tr>
	        <!-- {/if} -->
		<!-- {/section} -->

		<tr>
		  <td>
		    &nbsp;
		  </td>
		  <td>
		    {gallery->input type="submit" name="form.action.addFromBrowser"}{gallery->text text="Add Items"}{/gallery->input}
		  </td>
		</tr>
	    </table>
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if $mode == 'fromLocalServer'} -->
	<tr>
	  <td>
	  {gallery->text text="Transfer files that are already on your server into your Gallery.  The files must already have been uploaded to your server some other way (like FTP) and must be placed in a directory where they are accessibly by anybody on the server.  If you're on Unix this means that the files and the directory the files are in should have modes of at least 755."}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Server Path"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type=text size=80 name="form.path"}{$form.path}{/gallery->input}
	    {if $platform == 'unixplatform'}
	    <br>
	    {gallery->text text="Example: /var/www/htdocs/upload"}
	    <br>
	    {gallery->text text="Example: /tmp/images"}
	    {/if}
	    {if $platform == 'winntplatform'}
	    <br>
	    {gallery->text text="Example: c:\\windows\\temp\\images"}
	    <br>
	    {gallery->text text="Example: c:\\ftp"}
	    {/if}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type="submit" name="form.action.addFromLocalServer"}{gallery->text text="Find Files"}{/gallery->input}
	  </td>
	</tr>

	<!-- {/if} -->

	<!-- {if $mode == 'fromWebPage'} -->
	<tr>
	  <td>
	  {gallery->text text="Not implemented yet"}
	  </td>
	</tr>
	<!-- {/if} -->

    </table>
    {/gallery->form}
