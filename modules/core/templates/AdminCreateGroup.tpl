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
	{g->text text="Create A New Group"}
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

      <input type="text" name="{g->formVar var="form[groupName]"}" value="{$form.groupName}"/>
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
      <input type="submit" name="{g->formVar var="form[action][create]"}" value="{g->text text="Create Group"}"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
    </div>
  </div>
</div>

