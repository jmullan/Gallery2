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
	{g->text text="Account Activation"}
      </h2>
    </div>
  </div>

  {if isset($form.error.unknownUser)}
  <div class="gbAdmin">
    <div class="gbDataEntry"}>
      <div class="giError">
	{g->text text="This user cannot be activated."}
      </div>
    </div>
    <div class="gbDataEntry"}>
      <span>
	{g->text text="This can happen if the URL you entered is not correct or you already activated this account. Please check if your mailclient broke the link into several lines and append them without spaces."}
      </span>
    </div>
  </div>
 {else}
  <div class="gbAdmin">
    <div class="gbDataEntry"}>
      <span>
	{g->text text="Your account has been activated."}
      </span>
    </div>
    <div class="gbDataEntry"}>
      <span>
	{g->text text="You can now login to your account with your username and password."}
      </span>
    </div>
  </div>
 {/if}
</div>
