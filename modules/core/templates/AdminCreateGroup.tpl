{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminCreateGroup.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Create A New Group"}
      </div>
    </div>

  </div>

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Group Name"}
      </div>
      
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input type="text" name="{g->formVar var="form[groupName]"}" value="{$form.groupName}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
      <script type="text/javascript">document.forms[0]['{g->formVar var="form[groupName]"}'].focus();</script>

      {if isset($form.error.groupName.missing)}
      <div class="giError">
	{g->text text="You must enter a group name"}
      </div>
      {/if}
    
      {if isset($form.error.groupName.exists)}
      <div class="giError">
	{g->text text="Group '%s' already exists" arg1=$form.groupName}
      </div>
      {/if}
    </div>
  </div>

  <div class="gbBottomFlag">
    <div class="gbButtons">
      <input type="submit" name="{g->formVar var="form[action][create]"}" value="{g->text text="Create Group"}" class="button"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}" class="button"/>
    </div>
  </div>
</div>

