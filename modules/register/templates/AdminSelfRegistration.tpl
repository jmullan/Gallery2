<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
        {g->text text="Selfregistration Settings"}
      </div>
    </div>
    
    <div class="spacer">
      &nbsp;
    </div>
  </div>
  
 <div class="gbAdmin">
  {if isset($status)}
    <div class="gsStatus">
      {if isset($status.saved)}
        <div class="giStatus">
		{g->text text="Settings saved successfully"}
	</div>
      {/if}
    </div>
  {/if}

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="Selfregistration is an extension to Gallery2. It allows user to register for an account and optionally sends a confirmation email."}
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Confirmation policy"}
    </div>
  
    <div class="giDescription">
     {g->text text="The selfregistration module can accept new registrations instantly or require the user to click a confirmation link in an email that is sent by the module."}
    </div>
    
    <table style="admin_widgets">
      <tr>
	<td>
	  {g->text text="Choose your preferred policy:"}
	</td>

	<td>
 	  <select name="{g->formVar var="form[emailconfirmation]"}">
	    {html_options options=$Selfregistration.emailConfirmationList selected=$form.emailconfirmation }
	  </select>
	</td>
      </tr>
    </table>
  </div>


  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="eMail details"}
    </div>
    
    <div class="giDescription">
     {g->text text="If you choose to send confirmation emails, please specify subject and sender as they should appear to the users."}
    </div>
    
    <table style="admin_widgets">
      <tr>
	<td>
	  {g->text text="eMail-Subject:"}
	</td>

	<td>
	  <input type="text" name="{g->formVar var="form[subject]"}" value="{$form.subject}"/>
	</td>
      </tr>
	
      <tr>
	<td>
	  {g->text text="Sender eMail-address (From):"}
	</td>

	<td>
	  <input type="text" name="{g->formVar var="form[from]"}" value="{$form.from}"/>
	</td>
      </tr>

      <tr>
	<td>
	  {g->text text="Really send emails? ('No' for only pretending to do so):"}
	</td>

	<td>
 	  <select name="{g->formVar var="form[reallysend]"}">
	    {html_options options=$Selfregistration.reallySendList selected=$form.reallysend}
	  </select>
	</td>
      </tr>

	
    </table>


  <div class="gbButtons">
    <span>
      <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
      <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
    </span>
   </div>
  </div>
  </div>

</div>
