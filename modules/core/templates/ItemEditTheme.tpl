{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <h3>{g->text text="Choose a theme"}</h3>
  <p class="giDescription">
    {g->text text="Themes control the look and feel of the album.  You can choose a different theme for each album.  If you don't choose a theme, we'll use the %s theme by default." arg1="<b>`$ThemeSettingsForm.theme.name`</b>"}
  </p>

  <b>{g->text text="Theme"}</b>
  <select name="{g->formVar var="form[theme]"}">
    {html_options options=$ItemEditTheme.themeList selected=$form.theme}
  </select><br/>
  {g->changeInDescendents module="theme" text="Use this theme in all subalbums"}
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][chooseTheme]"}" value="{g->text text="Choose Theme"}"/>
</div>

{capture assign="message"}<h3>{g->text text="Configure the %s theme" arg1="<b>`$ItemEditTheme.themeList[$ItemEditTheme.theme]`</b>"}</h3>{g->text text="These settings only apply to the theme for this album."}{/capture}
{g->block type="core.ThemeSettingsForm" class="gbBlock" message=$message formId="itemAdminForm"}

{if !empty($ThemeSettingsForm.settings)}
<div>
  {g->changeInDescendents module="theme"
   text="Use these settings in all subalbums that use the %s theme" arg1=$ThemeSettingsForm.theme.name}
</div>
{/if}

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Theme Settings"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][undo]"}" value="{g->text text="Reset"}"/>
</div>
