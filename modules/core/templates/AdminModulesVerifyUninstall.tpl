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
	{g->text text="Confirm module uninstall"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {capture name=moduleName}<b>{$AdminModulesVerifyUninstall.module.name}</b>{/capture}
      {g->text text="Do you really want to uninstall the %s module?" arg1=$smarty.capture.moduleName}
    </div>
    <div class="giDescription">
      {g->text text="This will also remove any permissions and clean up any temporary data created by this module."}
    </div>
  </div>

  <div class="gbBottomFlag">
    <div class="giActionSelect">
      <input type="hidden" name="{g->formVar var="moduleId"}" value="{$AdminModulesVerifyUninstall.module.id}">
      <input type="submit" name="{g->formVar var="form[action][uninstall]"}" value="{g->text text="Uninstall"}"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
    </div>
  </div>
</div>
