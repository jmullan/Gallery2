{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Log in to your account"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="User name"}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="text" name="form.username"}{$form.username}{/gallery->input}
	  
	  {if isset($form.error.username.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a username"}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Password"}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="password" name="form.password"}{/gallery->input}
	  {if isset($form.error.password.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a password"}
	    {/gallery->error}
	  {/if}
	  
	  {if isset($form.error.invalidPassword)}
	    {gallery->error}
	      {gallery->text text="Your login information is incorrect.  Please try again."}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.login"}{gallery->text text="Login"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}
