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

	<!-- {if empty($localServerDirList)} -->
	<tr>
	  <td>
	    <i>
	      {gallery->text text="For security purposes, you can't use this feature until the Gallery Site Administrator configures a set of legal upload directories."}
	      {if $isAdmin} 
	      <a href="{gallery->url view="core:SiteAdmin" subView="core:AdminCore"}">
		[{gallery->text text="site admin"}]
	      </a>
	      {/if}
	    </i>
	  </td>
	</tr>
	<!-- {else} -->
	<tr>
	  <td>
	    {gallery->bigFontSize}
	    {gallery->text text="Server Path"}
	    {/gallery->bigFontSize}
	  </td>
	</tr>

	<tr>
	  <td>
	    {gallery->input type=text size=80 name="form.localServerPath"}{$form.localServerPath}{/gallery->input}

	    {if isset($form.error.localServerPath.missing)}
	    <br>
	    {gallery->errorFontColor}
	    {gallery->text text="You must enter a directory."}
	    {/gallery->errorFontColor}
	    {/if}

	    {if isset($form.error.localServerPath.invalid)}
	    <br>
	    {gallery->errorFontColor}
	    {gallery->text text="The directory you entered is invalid.  Make sure that the directory is readable by all users."}
	    {/gallery->errorFontColor}
	    {/if}

	    {if isset($form.error.localServerPath.illegal)}
	    <br>
	    {gallery->errorFontColor}
	    {gallery->text text="The directory you entered is illegal.  It must be a sub directory of one of the directories listed below."}
	    {/gallery->errorFontColor}
	    {/if}

	    <br>
	    <b> {gallery->text text="Legal Directories"} </b>
	    {if $isAdmin}
	    <a href="{gallery->url view="core:SiteAdmin" subView="core:AdminCore"}">
	      [{gallery->text text="modify"}]
	    </a>
	    {/if}
	    {foreach from=$localServerDirList item=dir}
	    <br>
	    {$dir}
	    {/foreach}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>
	<!-- {/if} -->

	<!-- {if !empty($form.localServerFiles)} -->
	<tr>
	  <td>
	    <table>
	      {foreach from=$form.localServerFiles item=file}
		<tr>
		  <td>
		    {$file.fileName}
		    {gallery->text one="(type: %s, size: %d byte)"
		                   many="(type: %s, size: %d bytes)"
		                   count=$file.stat.size
		                   arg1=$file.itemType
		                   arg2=$file.stat.size}
		  </td>
		</tr>
	      {/foreach}
	    </table>
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    {gallery->input type="submit" name="form.action.findFilesFromLocalServer"}{gallery->text text="Find Files"}{/gallery->input}
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
