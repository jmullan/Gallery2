{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Selfregistration Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Settings saved successfully"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->description}
      {g->text text="Selfregistration is an extension to Gallery2. It allows user to register for an account and optionally sends a confirmation email."}
    {/g->description}
  {/g->box style="admin"}

  {g->box style="admin"}
    {g->title}
      {g->text text="Confirmation policy"}
    {/g->title}
  
    {g->description}
     {g->text text="The selfregistration module can accept new registrations instantly or require the user to click a confirmation link in an email that is sent by the module."}
    {/g->description}
    
    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Choose your preferred policy:"}
	{/g->column}

	{g->column}
 	  {g->select name="form[emailconfirmation]"}
	    {html_options options=$Selfregistration.emailConfirmationList selected=$form.emailconfirmation }
	  {/g->select}
	{/g->column}
      {/g->row}
    {/g->table}
  {/g->box}


  {g->box style="admin"}
    {g->title}
      {g->text text="eMail details"}
    {/g->title}
    
    {g->description}
     {g->text text="If you choose to send confirmation emails, please specify subject and sender as they should appear to the users."}
    {/g->description}
    
    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="eMail-Subject:"}
	{/g->column}

	{g->column}
	  {g->input type="text" name="form[subject]"}{$form.subject}{/g->input}
	{/g->column}
      {/g->row}
	
      {g->row}
	{g->column}
	  {g->text text="Sender eMail-address (From):"}
	{/g->column}

	{g->column}
	  {g->input type="text" name="form[from]"}{$form.from}{/g->input}
	{/g->column}
      {/g->row}
	
    {/g->table}
  {/g->box}

  {g->box style="admin"}
    {g->element}
      {g->input type="submit" name="form[action][save]"}{g->text text="Save Settings"}{/g->input}
      {g->input type="submit" name="form[action][cancel]"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}

{/g->pagebox}
