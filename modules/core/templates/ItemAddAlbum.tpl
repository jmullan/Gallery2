{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemAddAlbum.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Add Sub-Album"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Name"}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <div class="giDescription">
	{g->text text="The name of this album on your hard disk.  It must be unique in this album.  Only use alphanumeric characters, underscores or dashes.  You will be able to rename it later."}
      </div>

      {strip}
	{foreach from=$ItemAdmin.parents item=parent}
	  {$parent.pathComponent}/
	{/foreach}
	{$ItemAdmin.item.pathComponent}/
      {/strip}
      <input type="text" size="10" name="{g->formVar var="form[pathComponent]"}" value="{$form.pathComponent}"/>

      {if !empty($form.error.pathComponent.invalid)}
      <div class="giDescription">
	{g->text text="Your name contains invalid characters.  Please enter another."}
      </div>
      {/if}
      
      {if !empty($form.error.pathComponent.missing)}
      <div class="giDescription">
	{g->text text="You must enter a name for this album."}
      </div>
      {/if}
      
      {if !empty($form.error.pathComponent.collision)}
      <div class="giDescription">
	{g->text text="The name you entered is already in use.  Please enter another."}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Title"}
      </div>
      
      <div class="giDescription">
	{g->text text="This is the album title."}
      </div>

      <input type="text" size="40" name="{g->formVar var="form[title]"}" value="{$form.title}"/>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Summary"}
      </div>

      <div class="giDescription">
	{g->text text="This is the album summary."}
      </div>

      <input type=text size=40 name="{g->formVar var="form[summary]"}" value="{$form.summary}"/>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Keywords"}
      </div>

      <div class="giDescription">
	{g->text text="Keywords are not visible, but are searchable."}
      </div>

      <textarea rows=2 cols=60 name="{g->formVar var="form[keywords]"}">{$form.keywords}</textarea>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Description"}
      </div>

      <div class="giDescription">
	{g->text text="This is the long description of the album."}
      </div>

      <textarea rows=4 cols=60 name="{g->formVar var="form[description]"}">{$form.description}</textarea>
    </div>

    <div class="gbBottomFlag">
      <div class="giActionSelect">
	<input type="submit" name="{g->formVar var="form[action][create]"}" value="{g->text text="Create"}"/>
      </div>
    </div>
  </div>
</div>
