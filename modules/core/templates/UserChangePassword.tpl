{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Change Password"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.changedPassword)}
	  {gallery->text text="Password changed successfully"}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text text="You must enter a new password twice to change passwords."}
  {/gallery->description}

  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Password"}
	  {gallery->textmodifier}
	    {gallery->text text="required"}
	  {/gallery->textmodifier}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="password" name="form.password1"}{/gallery->input}
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
	  {gallery->input type="password" name="form.password2"}{/gallery->input}

	  {if isset($form.error.password2.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter your password again!"}
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
	  {gallery->input type="submit" name="form.action.save"}{gallery->text text="Change"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}
