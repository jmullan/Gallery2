  {galleryFormOpen controller="core:CoreModuleAdmin"}
  <table>

    <tr>
      <td colspan="2">
	<h2>Sorting</h2>
	{galleryText text="These are default values.  They can be overridden in each album"}
      </td>
    </tr>

    <tr>
      <td>
	{galleryText text="Sort criteria:"}
      </td>
      <td>
	<select name="form.default.orderBy">
	  <option value="title"> {galleryText text="title"}
	  <option value="creationTimestamp"> {galleryText text="creation date"}
	  <option value="modificationTimestamp"> {galleryText text="last changed date"}
	  <option value="description"> {galleryText text="description"}
	  <option value="keywords"> {galleryText text="keywords"}
	</select>
      </td>
    </tr>

    <tr>
      <td>
	{galleryText text="Sort direction:"}
      </td>
      <td>
	<select name="form.default.orderDirection">
	  <option value="asc"> {galleryText text="ascending"}
	  <option value="desc"> {galleryText text="descending"}
	</select>
      </td>
    </tr>

  </table>
  {galleryFormClose}
  
