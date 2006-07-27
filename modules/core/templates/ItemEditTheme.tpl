{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{capture assign="message"}{g->text text="This album is configured to use the <b>%s</b> theme. These settings only apply to the theme for this album." arg1=$ThemeSettingsForm.theme.name}{/capture}
{g->block type="core.ThemeSettingsForm" class="gbBlock" message=$message formId="itemAdminForm"}

{if !empty($ThemeSettingsForm.settings)}
<div>
  {g->changeInDescendents module="theme"
   text="Use these settings in all subalbums that use %s theme" arg1=$ThemeSettingsForm.theme.name}
  <blockquote><p>
    {g->text text="Note: to set the same theme for all subalbums, check the appropriate box in <b>Album</b> tab"}
  </p></blockquote>
</div>
{/if}

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][undo]"}" value="{g->text text="Reset"}"/>
</div>
