{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminDeleteUser.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Delete a user"}
      </div>
    </div>
    
    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Are you sure?"}
    </div>

    <div class="giDescription">
      {g->text text="This will completely remove <b>%s</b> from Gallery.  There is no undo!"
      arg1=$AdminDeleteUser.user.userName}
    </div>

    <div class="gbBottomFlag">
      <div class="giActionSelect">
	<input type="hidden" name="{g->formVar var="userId"}" value="{$AdminDeleteUser.user.id}"/>
	<input type="submit" name="{g->formVar var="form[action][delete]"}" value="{g->text text="Delete"}"/>
	<input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
      </div>
    </div>
  </div>
</div>
