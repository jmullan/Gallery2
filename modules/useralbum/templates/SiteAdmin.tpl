{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SiteAdmin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="User Album Settings"}
      </h2>
    </div>
  </div>

  {if isset($status.saved)}
  <div id="gsStatus">
    <div class="giStatus">
      {g->text text="Settings saved successfully"}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="A new top level album will be added each time a new user is created.  The user will have full permissions on the album.  Select view permissions for the albums below."}
    </p>

    <table class="gbDataTable">
      <tr>
        <td> {g->text text="User albums viewable by"} </td>
        <td>
	  <select name="{g->formVar var="form[view]"}">
	    {html_options options=$UserAlbumSiteAdmin.viewList selected=$form.view}
	  </select>
	</td>
      </tr><tr>
	<td> {g->text text="Full size images viewable"} </td>
	<td>
	  <select name="{g->formVar var="form[fullsize]"}">
	    {html_options options=$UserAlbumSiteAdmin.sizeList selected=$form.fullsize}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
  </div>
</div>
