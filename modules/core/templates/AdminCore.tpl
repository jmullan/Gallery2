  {galleryForm controller="$controller"}
  <table>

    <tr>
      <td colspan="2" align="center">
	<h2>{galleryText text="Gallery Settings"}</h2>
      </td>
    </tr>

    <tr>
      <td colspan="2">
	<h3>Defaults</h3>
	{galleryText text="These are default values.  They can be overridden in each album"}
      </td>
    </tr>

    <tr>
      <td>
	{galleryText text="Album sort order:"}
      </td>
      <td>
	<select name="{galleryFormVar var="default.orderBy"}">
	  {html_options options=$orderByList selected=$form.default.orderBy}
	</select>
	<select name="{galleryFormVar var="default.orderDirection"}">
	  {html_options options=$orderDirectionList selected=$form.default.orderDirection}
	</select>
      </td>
    </tr>

    <tr>	
      <td>
	{galleryText text="Default layout"}
      </td>
      <td>
	<select name="{galleryFormVar var="default.layout"}">
	  {html_options values=$layoutList selected=$form.default.layout output=$layoutList}
	</select>
      </td>
    </tr>

    <tr>	
      <td>
	{galleryText text="Default style"}
      </td>
      <td>
	<select name="{galleryFormVar var="default.style"}">
	  {html_options values=$styleList selected=$form.default.style output=$styleList}
	</select>
      </td>
    </tr>

    <tr>
      <td>
	&nbsp;
      </td>
    </tr>

    <tr>
      <td colspan="2">
	<h3>
	  {galleryText text="Filesystem Permissions"}
	</h3>
	{galleryText text="Here you can specify the default permissions for files and
	directories that Gallery creates.  This doesn't apply to
	files/directories that Gallery has already created."}
      </td>
    </tr>

    <tr>	
      <td>
	{galleryText text="New directories"}
      </td>
      <td>
	<select name="{galleryFormVar var="permissions.directory"}">
	  {html_options values=$permissionsDirectoryList selected=$form.permissions.directory output=$permissionsDirectoryList}
	</select>
      </td>
    </tr>

    <tr>
      <td>
	{galleryText text="New files"}
      </td>
      <td>
	<select name="{galleryFormVar var="permissions.file"}">
	  {html_options values=$permissionsFileList selected=$form.permissions.file output=$permissionsFileList}
	</select>
      </td>
    </tr>

    <tr>
      <td>
	&nbsp;
      </td>
    </tr>

    <tr>
      <td colspan="2">
	<h3>
	  {galleryText text="Graphics Toolkit"}
	</h3>
	{galleryText text="Choose a graphics toolkit to use.  You can only choose
	from the list of currently active toolkits"}
      </td>
    </tr>

    <tr>
      <td>
	{galleryText text="Toolkit"}
      </td>
      <td>
	<select name="{galleryFormVar var="graphics.type"}">
	  {html_options values=$graphicsTypeList selected=$form.graphics.type output=$graphicsTypeList}
	</select>
      </td>
    </tr>

    <tr>
      <td colspan="2" align="center">
	<input type="submit" name="{galleryFormVar var="submit"}" value="{galleryText text="Save Changes"}">
	<input type="reset" name="{galleryFormVar var="reset"}" value="{galleryText text="Reset Form"}">
      </td>
    </tr>

  </table>
  {/galleryForm}
  
