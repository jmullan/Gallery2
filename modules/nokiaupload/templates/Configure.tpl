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
	{g->text text="Nokia Image Upload Configuration"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="This module creates a target album for uploaded images.  All users who perform an upload are automatically added to a group with upload access to this album.  The album and group will be created using the information below."}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="User Group"}
      </h3>

      <div class="giDescription">
	{g->text text="Enter a name for the group"}
      </div>
      <input type="text" name="{g->formVar var="form[group]"}" value="{$form.group}" size="30"/>

      {if isset($form.error.group.missing)}
      <div class="giError">
	{g->text text="Missing group name"}
      </div>
      {/if}
      {if isset($form.error.group.duplicate)}
      <div class="giError">
	{g->text text="Group name already exists"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Upload Album"}
      </h3>

      <div class="giDescription">
	{g->text text="Enter a title for the Upload Album"}
      </div>
      <input type="text" name="{g->formVar var="form[album]"}" value="{$form.album}" size="30"/>

      {if isset($form.error.album.missing)}
      <div class="giError">
	{g->text text="Missing album title"}
      </div>
      {/if}

      <div class="giDescription" style="margin-top:6px">
	{g->text text="Choose a location for the Upload Album"}
      </div>
      <select name="{g->formVar var="form[parent]"}">
	{foreach from=$NokiaUploadConfigure.albumTree item=album}
	  <option value="{$album.data.id}" {if $album.data.id==$form.parent}selected="selected"{/if}>
	    {"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"|repeat:$album.depth}--
	    {$album.data.title|default:$album.data.pathComponent}
	  </option>
	{/foreach}
      </select>
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Configure"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>
