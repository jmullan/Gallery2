{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to UserPreferences.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="Account Settings"}
      </h2>
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
      <h3 class="giTitle">
        {g->text text="Username"}
      </h3>
      <p class="giDescription">
      {$UserAdmin.user.userName}
      </p>
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
        {g->text text="Full Name"}
      </h3>

      <input type="text" name="{g->formVar var="form[fullName]"}" value="{$form.fullName}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
        {g->text text="E-mail Address"}
        <span class="giSubtitle">
          {g->text text="(required)"}
        </span>
      </h3>
      
      <input type="text" name="{g->formVar var="form[email]"}" value="{$form.email}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>

      {if isset($form.error.email.missing)}
      <div class="giError">
        {g->text text="You must enter an email address"}
      </div>
      {/if}
    </div>
      
    {if $UserPreferences.translationsSupported}
    <div class="gbDataEntry">
      <h3 class="giTitle">
        {g->text text="Language"}
      </h3>

      <select name="{g->formVar var="form[language]"}" class="giActionSelect" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';">
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
