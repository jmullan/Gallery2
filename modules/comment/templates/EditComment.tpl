{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Edit comment"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->widget2box}
  {gallery->widget2}
    {gallery->title}
      {gallery->text text="Commenter"}
      {gallery->textmodifier}
	{gallery->text text="required"}
      {/gallery->textmodifier}
    {/gallery->title}
    {gallery->body}
      {* got to put this in a body tag somewhere *}
      {gallery->input type="hidden" name="commentId"}{$EditComment.comment.id}{/gallery->input}

      {gallery->input type="text" name="form.commenterName"}{$form.commenterName}{/gallery->input}
      {if isset($form.error.commenterName.missing)} 
	{gallery->error}
	  {gallery->text text="You must enter a username."}
	{/gallery->error}
      {/if} 

      {if isset($form.error.commenterName.invalid)} 
	{gallery->error}
	  {gallery->text text="The username you entered is invalid."}
	{/gallery->error}
      {/if} 
    {/gallery->body}
  {/gallery->widget2}

  {gallery->widget2}
    {gallery->title}
      {gallery->text text="Host: "}
    {/gallery->title}
    {gallery->body}
      {gallery->input type="text" name="form.host"}{$form.host}{/gallery->input}
    {/gallery->body}
  {/gallery->widget2}

  {gallery->widget2}
    {gallery->title}
      {gallery->text text="Date: "}
      {gallery->textmodifier}
	{gallery->text text="required"}
      {/gallery->textmodifier}
    {/gallery->title}
    {gallery->body}
      {gallery->input type="text" name="form.date"}{$form.date}{/gallery->input}
      {if isset($form.error.date.invalid)} 
	{gallery->error}
	  {gallery->text text="The date you entered is invalid."}
	{/gallery->error}
      {/if} 

      {if isset($form.error.date.missing)} 
	{gallery->error}
	  {gallery->text text="You must enter a date"}
	{/gallery->error}
      {/if} 
    {/gallery->body}
  {/gallery->widget2}

  {gallery->widget2}
    {gallery->title}
      {gallery->text text="Subject: "}
      {gallery->textmodifier}
	{gallery->text text="required"}
      {/gallery->textmodifier}
    {/gallery->title}
    {gallery->body}
      {gallery->input type="text" size="60" name="form.subject"}{$form.subject}{/gallery->input}
      {if isset($form.error.subject.missing)} 
	{gallery->error}
	  {gallery->text text="You must enter a subject"}
	{/gallery->error}
      {/if} 
    {/gallery->body}
  {/gallery->widget2}

  {gallery->widget2}
    {gallery->title}
      {gallery->text text="Comment: "}
      {gallery->textmodifier}
	{gallery->text text="required"}
      {/gallery->textmodifier}
    {/gallery->title}
    {gallery->body}
      {gallery->textarea rows="15" cols="60" name="form.comment"}{$form.comment}{/gallery->textarea}
      {if isset($form.error.comment.missing)} 
	{gallery->error}
	  {gallery->text text="You must enter a comment"}
	{/gallery->error}
      {/if} 
    {/gallery->body}
  {/gallery->widget2}

  {gallery->widget2}
    {gallery->body}
      {gallery->input type="submit" name="form.action.save"}{gallery->text text="Save"}{/gallery->input}
      {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
    {/gallery->body}
  {/gallery->widget2}
{/gallery->widget2box}
