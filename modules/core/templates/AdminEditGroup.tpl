{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminEditGroup.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Edit a group"}
      </h2>
    </div>
    
  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Group Name"}
      </h3>
      
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input class="giFormGroupname" type="text" name="{g->formVar var="form[groupName]"}" value="{$form.groupName}"/>
      <input type="hidden" name="{g->formVar var="groupId"}" value="{$AdminEditGroup.group.id}"/>

      {if isset($form.error.groupName.missing)}
      <div class="giError">
	{g->text text="You must enter a group name"}
      </div>
      {/if}
    </div>
  </div>

  <div class="gbBottomFlag">
    <div class="giActionSelect">
      <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
      <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
    </div>
  </div>
</div>
