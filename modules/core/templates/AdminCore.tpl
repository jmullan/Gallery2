      {galleryForm controller="$controller"}
    <table>

	<tr>
	  <td colspan="2" align="center">
	    {galleryBiggerFont}
	    {galleryText text="Gallery Settings"}
	    {/galleryBiggerFont}
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {galleryBigFont}
	    {galleryText text="Defaults"}
	    {/galleryBigFont}
	    <br>
	    {galleryText text="These are default values.  They can be overridden in each album."}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {galleryText text="Album sort order:"}
	  </td>
	  <td>
	    {gallerySelect name="default.orderBy"}
	    {html_options options=$orderByList selected=$form.default.orderBy}
	    {/gallerySelect}
	    {gallerySelect name="default.orderDirection"}
	    {html_options options=$orderDirectionList selected=$form.default.orderDirection}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {galleryText text="Default layout"}
	  </td>
	  <td>
	    {gallerySelect name="default.layout"}
	    {html_options values=$layoutList selected=$form.default.layout output=$layoutList}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {galleryText text="Default theme"}
	  </td>
	  <td>
	    {gallerySelect name="default.theme"}
	    {html_options values=$themeList selected=$form.default.theme output=$themeList}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {galleryBigFont}
	    {galleryText text="Language settings"}
	    {/galleryBigFont}
	    <br>
	    {galleryText text="Select language defaults for Gallery. Individual users can override this setting in their personal preferences."}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {galleryText text="Default language"}
	  </td>
	  <td>
	    {gallerySelect name="default.language"}
	    {html_options options=$languageList selected=$form.default.language}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {galleryBigFont}
	    {galleryText text="Filesystem Permissions"}
	    {/galleryBigFont}
	    <br>
	    {galleryText text="Here you can specify the default permissions for files and directories that Gallery creates. This doesn't apply to files/directories that Gallery has already created."}
	  </td>
	</tr>

	<tr>	
	  <td align="right">
	    {galleryText text="New directories"}
	  </td>
	  <td>
	    {gallerySelect name="permissions.directory"}
	    {html_options values=$permissionsDirectoryList selected=$form.permissions.directory output=$permissionsDirectoryList}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {galleryText text="New files"}
	  </td>
	  <td>
	    {gallerySelect name="permissions.file"}
	    {html_options values=$permissionsFileList selected=$form.permissions.file output=$permissionsFileList}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {galleryBigFont}
	    {galleryText text="Graphics Toolkit"}
	    {/galleryBigFont}
	    <br>
	    {galleryText text="Choose a graphics toolkit to use.  You can only choose from the list of currently active toolkits."}
	  </td>
	</tr>

	<!-- {if !empty($graphicsTypeList)} -->
	<tr>
	  <td align="right">
	    {galleryText text="Toolkit"}
	  </td>
	  <td>
	    {gallerySelect name="graphics.type"}
	    {html_options options=$graphicsTypeList selected=$form.graphics.type}
	    {/gallerySelect}
	  </td>
	</tr>
	<!-- {else} -->
	<tr>
	  <td colspan="2">
	    {galleryErrorFontColor}
	    {galleryText text="No Graphics toolkits detected!"}
	    <a href="{galleryUrl view=core:SiteAdmin subView=core:AdminModules}">
	      [{galleryText text="Activate a toolkit here"}]
	    </a>
	    {/galleryErrorFontColor}
	  </td>
	</tr>
	<!-- {/if} -->

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2">
	    {galleryBigFont}
	    {galleryText text="Session Settings"}
	    {/galleryBigFont}
	    <br>
	    {galleryText text="Specify the lifetime of the session here."}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {galleryText text="Lifetime"}
	  </td>
	  <td>
	    {gallerySelect name="session.lifetime"}
	    {html_options options=$sessionTimeList selected=$form.session.lifetime}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>
	  <td align="right">
	    {galleryText text="Inactivity Timeout"}
	  </td>
	  <td>
	    {gallerySelect name="session.inactivityTimeout"}
	    {html_options options=$sessionTimeList selected=$form.session.inactivityTimeout}
	    {/gallerySelect}
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td colspan="2" align="center">
	    {galleryInput type="submit" name="actionSave"}{galleryText text="Save Changes"}{/galleryInput}
	    {galleryInput type="submit" name="actionReset"}{galleryText text="Reset"}{/galleryInput}
	  </td>
	</tr>

    </table>
    {/galleryForm}
    
