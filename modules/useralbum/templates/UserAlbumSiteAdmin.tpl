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
      {g->text text="An album will be created for each user.  The user will have full permissions on the album."}
    </p>

    <table class="gbDataTable">
      <tr>
	<td> {g->text text="Create albums"} </td>
	<td>
	  <select name="{g->formVar var="form[create]"}">
	    {html_options options=$UserAlbumSiteAdmin.createList selected=$form.create}
	  </select>
	</td>
      </tr><tr>
      <tr>
	<td> {g->text text="Albums viewable by"} </td>
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
	    <option value="{$album.data.id}"{if $album.data.id==$form.targetLocation}
	     selected="selected"{/if}>
	      {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}--
	      {$album.data.title|default:$album.data.pathComponent}
	    </option>
	    {/foreach}
	  </select>
	</td>
      </tr><tr>
	<td> {g->text text="Login page"} </td>
	<td> <input type="checkbox" id="loginRedirect" name="{g->formVar var="form[loginRedirect]"}"
	      {if !empty($form.loginRedirect)}checked="checked"{/if}/>
	     <label for="loginRedirect"> {g->text text="Jump to user album after login"} </label>
	</td>
      </tr><tr>
	<td> {g->text text="Link to user album"} </td>
	<td> <input type="checkbox" id="homeLink" name="{g->formVar var="form[homeLink]"}"
	      {if !empty($form.homeLink)}checked="checked"{/if}/>
	     <label for="homeLink"> {g->text text="Show link"} </label>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}"
     value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}"
     value="{g->text text="Reset"}"/>
  </div>
</div>
