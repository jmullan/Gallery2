      {gallery->form controller="$controller"}
    <table>

	<tr>
	  <td colspan="2" align="center">
	    {gallery->biggerFontSize}
	    {gallery->text text="Gallery Settings"}
	    {/gallery->biggerFontSize}
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->bigFontSize}
	    {gallery->text text="Defaults"}
	    {/gallery->bigFontSize}
	    <br>
	    {gallery->text text="These are default values.  They can be overridden in each album."}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {gallery->text text="Album sort order:"}
	  </td>
	  <td>
	    {gallery->select name="default.orderBy"}
	    {html_options options=$orderByList selected=$form.default.orderBy}
	    {/gallery->select}
	    {gallery->select name="default.orderDirection"}
	    {html_options options=$orderDirectionList selected=$form.default.orderDirection}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {gallery->text text="Default layout"}
	  </td>
	  <td>
	    {gallery->select name="default.layout"}
	    {html_options values=$layoutList selected=$form.default.layout output=$layoutList}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {gallery->text text="Default theme"}
	  </td>
	  <td>
	    {gallery->select name="default.theme"}
	    {html_options values=$themeList selected=$form.default.theme output=$themeList}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->bigFontSize}
	    {gallery->text text="Language settings"}
	    {/gallery->bigFontSize}
	    <br>
	    {gallery->text text="Select language defaults for Gallery. Individual users can override this setting in their personal preferences."}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {gallery->text text="Default language"}
	  </td>
	  <td>
	    {gallery->select name="default.language"}
	    {html_options options=$languageList selected=$form.default.language}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->bigFontSize}
	    {gallery->text text="Filesystem Permissions"}
	    {/gallery->bigFontSize}
	    <br>
	    {gallery->text text="Here you can specify the default permissions for files and directories that Gallery creates. This doesn't apply to files/directories that Gallery has already created."}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {gallery->text text="New directories"}
	  </td>
	  <td>
	    {gallery->select name="permissions.directory"}
	    {html_options values=$permissionsDirectoryList selected=$form.permissions.directory output=$permissionsDirectoryList}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {gallery->text text="New files"}
	  </td>
	  <td>
	    {gallery->select name="permissions.file"}
	    {html_options values=$permissionsFileList selected=$form.permissions.file output=$permissionsFileList}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {gallery->bigFontSize}
	    {gallery->text text="Session Settings"}
	    {/gallery->bigFontSize}
	    <br>
	    {gallery->text text="Specify the lifetime of the session here."}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {gallery->text text="Lifetime"}
	  </td>
	  <td>
	    {gallery->select name="session.lifetime"}
	    {html_options options=$sessionTimeList selected=$form.session.lifetime}
	    {/gallery->select}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {gallery->text text="Inactivity Timeout"}
	  </td>
	  <td>
	    {gallery->select name="session.inactivityTimeout"}
	    {html_options options=$sessionTimeList selected=$form.session.inactivityTimeout}
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
	    {gallery->input type="submit" name="actionSave"}{gallery->text text="Save Changes"}{/gallery->input}
	    {gallery->input type="submit" name="actionReset"}{gallery->text text="Reset"}{/gallery->input}
	  </td>
	</tr>

    </table>
    {/gallery->form}
    
