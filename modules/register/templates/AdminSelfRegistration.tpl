{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminSelfRegistration.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="Self Registration Settings"}
      </h2>
    </div>
  </div>
  
  {if isset($status.saved)}
    <div id="gsStatus">
      <div class="giStatus">
	{g->text text="Settings saved successfully"}
      </div>
    </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Self Registration allows users to register for an account and optionally sends a confirmation email."}
    </p>
  </div>

  <div class="gbAdmin">
    <h3> {g->text text="Confirmation Policy"} </h3>
    <p class="giDescription">
     {g->text text="The Self Registration module can accept new registrations instantly or require the user to click a confirmation link in an email that is sent by the module."}
    </p>
    
    <table style="admin_widgets">
      <tr>
	<td>
	  {g->text text="Choose your preferred policy:"}
	</td>
	<td>
	  <select name="{g->formVar var="form[emailconfirmation]"}">
	    {html_options options=$SelfRegistration.emailConfirmationList selected=$form.emailconfirmation}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <h3> {g->text text="Email details"} </h3>
    <p class="giDescription">
      {g->text text="If you choose to send confirmation emails, please specify subject and sender as they should appear to the users."}
    </p>
    
    <table style="admin_widgets">
      <tr>
	<td>
	  {g->text text="Email Subject:"}
	</td>
	<td>
	  <input type="text" name="{g->formVar var="form[subject]"}" value="{$form.subject}" size="30"/>
	</td>
      </tr>
      <tr>
	<td>
	  {g->text text="Sender Email address (From):"}
	</td>
	<td>
	  <input type="text" name="{g->formVar var="form[from]"}" value="{$form.from}" size="30"/>
	</td>
      </tr>
      <tr>
	<td>
	  {g->text text="Really send emails? ('No' for only pretending to do so):"}
	</td>
	<td>
	  <select name="{g->formVar var="form[reallysend]"}">
	    {html_options options=$SelfRegistration.reallySendList selected=$form.reallysend}
	  </select>
	</td>
      </tr>
    </table>

  <div class="gbButtons">
    <span>
      <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Reset"}"/>
    </span>
   </div>
  </div>
</div>
