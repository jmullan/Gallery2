{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to UserPreferences.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Account Settings"}
      </div>
    </div>
  </div>

  {if isset($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Account settings saved successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Username"}
      </div>

      {$UserAdmin.user.userName}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Full name"}
      </div>

      <input type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}"/>
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Email address"}
      </div>
      <div class="giSubtitle">
	{g->text text="required"}
      </div>

      <input type="text" name="{g->formVar var="form[email]"}" value="{$form.email}"/>

      {if isset($form.error.email.missing)}
      <div class="giError">
	{g->text text="You must enter an email address"}
      </div>
      {/if}
    </div>
      
    {if $UserPreferences.translationsSupported}
    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Language"}
      </div>

      <select name="{g->formVar var="form[language]"}">
	  {html_options options=$UserPreferences.languageList selected=$form.language}
      </select>
    </div>
    {/if}
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>
