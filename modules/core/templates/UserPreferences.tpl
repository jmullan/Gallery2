{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Account Settings"}
  {/gallery->title}
{/gallery->bannerbox}

{if isset($status)}
  {gallery->detailedbox}
    {gallery->body}
      {gallery->status}
	{if isset($status.saved)}
	  {gallery->text text="Account settings saved successfully"}
	{/if}
      {/gallery->status}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Username"}
	{/gallery->title}
	{gallery->body}
	  {$UserAdmin.user.userName}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Full name"}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="text" name="form.fullName"}{$form.fullName}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Email address"}
	  {gallery->textmodifier}
	    {gallery->text text="required"}
	  {/gallery->textmodifier}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="text" name="form.email"}{$form.email}{/gallery->input}
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
	    {html_options options=$UserPreferences.languageList selected=$form.language}
	  {/gallery->select}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->body}
	  {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.undo"}{gallery->text text="Undo"}{/gallery->input}
	  {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}
