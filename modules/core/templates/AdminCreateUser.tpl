{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Create A New User"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Username"}
	  {gallery->textmodifier}
	    {gallery->text text="required"}
	  {/gallery->textmodifier}
	{/gallery->title}
	{gallery->body}
	  {gallery->input size="32" type="text" name="form.userName"}{$form.userName}{/gallery->input}
	  {if isset($form.error.userName.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a username"}
	    {/gallery->error}
	  {/if}
	  
	  {if isset($form.error.userName.exists)}
	    {gallery->error}
	      {gallery->text text="Username '%s' already exists" arg1=$form.userName}
	    {/gallery->error}
	  {/if}
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

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Language"}
	{/gallery->title}
	{gallery->body}
	  {gallery->select name="form.language"}
	    {html_options options=$AdminCreateUser.languageList selected=$form.language}
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

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.create"}{gallery->text text="Create User"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}
