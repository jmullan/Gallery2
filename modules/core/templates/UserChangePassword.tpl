{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to UserChangePassword.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="Change Password"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.changedPassword)}
    <div class="giStatus">
      {g->text text="Password changed successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="You must enter your current password to prove that it's you, then enter your new password twice to make sure that you didn't make a mistake."}
    </p>
  
    <div class="gbDataEntry">
      <h3 class="giTitle">
        {g->text text="Current Password"}
      <span class="giSubtitle">
        {g->text text="(required)"}
      </span>
      </h3>

      <input type="password" name="{g->formVar var="form[currentPassword]"}"/>

      {if isset($form.error.currentPassword.missing)}
      <div class="giError">
        {g->text text="You must enter your current password"}
      </div>
      {/if}
      {if isset($form.error.currentPassword.incorrect)}
      <div class="giError">
        {g->text text="Incorrect password"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
        {g->text text="New Password"}
      <span class="giSubtitle">
        {g->text text="(required)"}
      </span>
      </h3>

      <input type="password" name="{g->formVar var="form[password1]"}"/>

      {if isset($form.error.password1.missing)}
      <div class="giError">
        {g->text text="You must enter a new password"}
      </div>
      {/if}
    </div>

    <div class="gbDataEntry">
      <h3 class="giTitle">
        {g->text text="Verify New Password"}
      <span class="giSubtitle">
        {g->text text="(required)"}
      </span>
      </h3>
        
      <input type="password" name="{g->formVar var="form[password2]"}"/>

      {if isset($form.error.password2.missing)}
      <div class="giError">
        {g->text text="You must enter your new password again!"}
      </div>
      {/if}
      
      {if isset($form.error.password2.mismatch)}
      <div class="giError">
        {g->text text="The passwords you entered did not match"}
      </div>
      {/if}
    </div>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Change"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  </div>
</div>
