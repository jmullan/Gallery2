{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Edit a user"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Username"}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="hidden" name="form.userName"}{$form.userName}{/gallery->input}
	  {gallery->input type="hidden" name="userId"}{$AdminEditUser.user.id}{/gallery->input}
	  {$form.userName}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Full Name"}
	{/gallery->title}
	{gallery->body}
	  {gallery->input size="32" type="text" name="form.fullName"}{$form.fullName}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}

      {if $AdminEditUser.show.email}
	{gallery->widget2}
	  {gallery->title}
	    {gallery->text text="Email Address"}
	    {gallery->textmodifier}
	      {gallery->text text="required"}
	    {/gallery->textmodifier}
	  {/gallery->title}
	  {gallery->body}
	    {gallery->input size="32" type="text" name="form.email"}{$form.email}{/gallery->input}
	    
	    {if isset($form.error.email.missing)}
	      {gallery->error}
		{gallery->text text="You must enter an email address"}
	      {/gallery->error}
	    {/if}
	    
	  {/gallery->body}
	{/gallery->widget2}
      {/if}

      {if $AdminEditUser.show.language}
	{gallery->widget2}
	  {gallery->title}
	    {gallery->text text="Language"}
	  {/gallery->title}
	  {gallery->body}
	    {gallery->select name="form.language"}
	      {html_options options=$AdminEditUser.languageList selected=$form.language}
	    {/gallery->select}
	  {/gallery->body}
	{/gallery->widget2}

	{gallery->widget2}
	  {gallery->title}
	    {gallery->text text="Password"}
	    {gallery->textmodifier}
	      {gallery->text text="required"}
	    {/gallery->textmodifier}
	  {/gallery->title}
	  {gallery->body}
	    {gallery->input size="32" type="password" name="form.password1"}{/gallery->input}

	    {if isset($form.error.password1.missing)}
	      {gallery->error}
		{gallery->text text="You must enter a password"}
	      {/gallery->error}
	    {/if}
	    
	  {/gallery->body}
	{/gallery->widget2}
      {/if}

      {if $AdminEditUser.show.password}
	{gallery->widget2}
	  {gallery->title}
	    {gallery->text text="Verify Password"}
	    {gallery->textmodifier}
	      {gallery->text text="required"}
	    {/gallery->textmodifier}
	  {/gallery->title}
	  {gallery->body}
	    {gallery->input size="32" type="password" name="form.password2"}{/gallery->input}

	    {if isset($form.error.password2.missing)}
	      {gallery->error}
		{gallery->text text="You must enter the password a second time"}
	      {/gallery->error}
	    {/if}
	    
	    {if isset($form.error.password2.mismatch)}
	      {gallery->error}
		{gallery->text text="The passwords you entered did not match"}
	      {/gallery->error}
	    {/if}
	  {/gallery->body}
	{/gallery->widget2}
      {/if}

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.save"}{gallery->text text="edit user"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.undo"}{gallery->text text="undo"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="cancel"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}
