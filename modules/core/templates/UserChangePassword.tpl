{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to UserChangePassword.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsContents">
  <div id="gsAdminContents">
    <div class="gbTopFlag">
      <div class="gbTitle">
        <h2 class="giTitle">
          {g->text text="Change Password"}
        </h2>
      </div>
    </div>
  
    {if isset($status)}
    <div id="gsStatus">
      {if isset($status.changedPassword)}
      <div class="giStatus">
        {g->text text="Password changed successfully"}
      </div>
      {/if}
    </div>
    {/if}
  
    <div class="gbAdmin">
      <div class="giDescription">
        {g->text text="You must enter a new password twice to change passwords."}
      </div>
    
      <div class="gbDataEntry">
        <h3 class="giTitle">
          {g->text text="Password"}
        <span class="giSubtitle">
          {g->text text="(required)"}
        </span>
        </h3>
  
        <input type="password" name="{g->formVar var="form[password1]"}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
  
        {if isset($form.error.password1.missing)}
        <div class="giError">
          {g->text text="You must enter a password"}
        </div>
        {/if}
      </div>
  
      <div class="gbDataEntry">
        <h3 class="giTitle">
          {g->text text="Verify Password"}
        <span class="giSubtitle">
          {g->text text="(required)"}
        </span>
        </h3>
          
        <input type="password" name="{g->formVar var="form[password2]"}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>
  
        {if isset($form.error.password2.missing)}
        <div class="giError">
          {g->text text="You must enter your password again!"}
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
      <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Change"}" class="button"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}" class="button"/>
    </div>
  </div>
</div>