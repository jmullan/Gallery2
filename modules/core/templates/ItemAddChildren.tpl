    {galleryForm controller="$controller" enctype="multipart/form-data"}
    {galleryInput type="hidden" name="formName"}ItemEditAlbum{/galleryInput}
    {galleryInput type="hidden" name="itemId"}{$item.id}{/galleryInput}
    <table border="0" cellspacing="0" cellpadding="0">
	<tr>
	  <td>
	    <center>
	      {galleryBiggerFont}
	      {galleryText text="Add Items to this Album"}
	      {/galleryBiggerFont}
	    </center>
	    <br>
	    {galleryText text="Gallery can handle files of any format.  However, it can only create automatic resizes and thumbnails for certain types of files."}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	  {galleryBigFont}
	  {galleryText text="Add Files From Your Computer"}
	  {/galleryBigFont}
	  <br>
	  {galleryText one="Upload a file directly from your computer."
	               many="Upload up to %d files directly from your computer."
	               count=$form.uploadBoxCount
	               arg1=$form.uploadBoxCount}
	  {galleryText text="Enter the full path to the file and an optional caption in the boxes below."}
	  {galleryInput type="hidden" name="form.uploadBoxCount"}{$form.uploadBoxCount}{/galleryInput}
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
		      {galleryText text="File: "}
		    </b>
		  </td>
		  <td>
		    {galleryInput name=form.fileUpload.$iteration type="file" size="60"}{/galleryInput}
		  </td>
		</tr>
		<tr>
		  <td align="right" valign="top">
		    <b>
		      {galleryText text="Caption: "}
		    </b>
		  </td>
		  <td>
		    {galleryTextArea rows="2" cols="60" name=form.fileUpload.$iteration.caption}{/galleryTextArea}
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
		    {galleryInput type="submit" name="form.action.addFromComputer"}{galleryText text="Add Items"}{/galleryInput}
		  </td>
		</tr>
	    </table>
	  </td>
	</tr>
	  
	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	  {galleryBigFont}
	  {galleryText text="Add From Your Server"}
	  {/galleryBigFont}
	  <br>
	  {galleryText text="Not implemented yet"}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	  {galleryBigFont}
	  {galleryText text="Add From a Website"}
	  {/galleryBigFont}
	  <br>
	  {galleryText text="Not implemented yet"}
	  </td>
	</tr>

    </table>
    {/galleryForm}
