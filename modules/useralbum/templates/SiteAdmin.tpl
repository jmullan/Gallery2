{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
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
	  <select name="{g->formVar var="form[fullSize]"}">
	    {html_options options=$UserAlbumSiteAdmin.sizeList selected=$form.fullSize}
	  </select>
	</td>
      </tr><tr>
	<td> {g->text text="Location for new user albums"} </td>
	<td>
      <select name="{g->formVar var="form[targetLocation]"}">
        {foreach from=$UserAlbumSiteAdmin.targetLocation item=album}
	<option value="{$album.data.id}"{if $album.data.id==$form.targetLocation} selected="selected"{/if}>
          {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}--
	  {$album.data.title|default:$album.data.pathComponent}
	</option>
        {/foreach}
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
