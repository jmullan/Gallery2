{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEditItem.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  {if isset($ItemEditItem.can.changePathComponent)}
  <div class="gbDataEntry">
    <h2 class="giTitle">
      {g->text text="Name"}
    </h2>
    <div class="giSubtitle">
      {g->text text="required"}
    </div>
    <p class="giDescription">
      {g->text text="The name of this item on your hard disk.  It must be unique in this album.  Only use alphanumeric characters, underscores or dashes."}
    </p>
    
    {strip}
    {foreach from=$ItemAdmin.parents item=parent}
    {if empty($parent.parentId)}
    /
    {else}
    {$parent.pathComponent}/
    {/if}
    {/foreach}
    {/strip}
    <input type="text" size="40" name="{g->formVar var="form[pathComponent]"}" value="{$form.pathComponent}"/>

    {if !empty($form.error.pathComponent.invalid)}
    <div class="giError">
      {g->text text="Your name contains invalid characters.  Please choose another."}
    </div>
    {/if}
    
    {if !empty($form.error.pathComponent.missing)}
    <div class="giError">
      {g->text text="You must enter a name for this item."}
    </div>
    {/if}
    
    {if !empty($form.error.pathComponent.collision)}
    <div class="giError">
      {g->text text="The name you entered is already in use.  Please choose another."}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Title"}
    </h3>
    <p class="giDescription">
      {g->text text="The title of this item."}
    </p>

    {include file="gallery:modules/core/templates/MarkupBar.tpl" 
             viewL10domain="modules_core" 
	     element="title"
	     firstMarkupBar="true"}
    <input id="title" type="text" size="40" name="{g->formVar var="form[title]"}" value="{$form.title}"/>
  </div>
  {if !empty($form.error.title.missingRootTitle)}
    <div class="giError">
      {g->text text="The root album must have a title."}
    </div>
  {/if}

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Summary"}
    </h3>
    <p class="giDescription">
      {g->text text="The summary of this item."}
    </p>

    {include file="gallery:modules/core/templates/MarkupBar.tpl" 
             viewL10domain="modules_core" 
	     element="summary"}
    <input id="summary" type="text" size="40" name="{g->formVar var="form[summary]"}" value="{$form.summary}"/>
  </div>

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Keywords"}
    </h3>
    <p class="giDescription">
      {g->text text="Keywords are not visible, but are searchable."}
    </p>
    <textarea rows="2" cols="60" name="{g->formVar var="form[keywords]"}">{$form.keywords}</textarea>
  </div>

  <div class="gbDataEntry">
    <h3 class="giTitle">
      {g->text text="Description"}
    </h3>
    <p class="giDescription">
      {g->text text="This is the long description of the item."}
    </p>
    {include file="gallery:modules/core/templates/MarkupBar.tpl" 
             viewL10domain="modules_core" 
	     element="description"}
    <textarea id="description" rows="4" cols="60" name="{g->formVar var="form[description]"}">{$form.description}</textarea>
  </div>
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
</div>

