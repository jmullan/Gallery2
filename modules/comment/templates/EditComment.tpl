{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit comment"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->box}
      {g->title}
	{g->text text="Commenter"}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}

      {g->element}
	{* got to put this in a body tag somewhere *}
	{g->input type="hidden" name="commentId"}{$EditComment.comment.id}{/g->input}

	{g->input type="text" name="form.commenterName"}{$form.commenterName}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.commenterName.missing)} 
      {g->error}
	{g->text text="You must enter a username."}
      {/g->error}
    {/if} 
      
    {if isset($form.error.commenterName.invalid)} 
      {g->error}
	{g->text text="The username you entered is invalid."}
      {/g->error}
    {/if} 

    {g->box}
      {g->title}
	{g->text text="Host: "}
      {/g->title}
      {g->element}
	{g->input type="text" name="form.host"}{$form.host}{/g->input}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Date: "}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}

      {g->element}
	{g->input type="text" name="form.date"}{$form.date}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.date.invalid)} 
      {g->error}
	{g->text text="The date you entered is invalid."}
      {/g->error}
    {/if} 

    {if isset($form.error.date.missing)} 
      {g->error}
	{g->text text="You must enter a date"}
      {/g->error}
    {/if} 

    {g->box}
      {g->title}
	{g->text text="Subject: "}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}

      {g->element}
	{g->input type="text" size="60" name="form.subject"}{$form.subject}{/g->input}
      {/g->element}
    {/g->box}

    {if isset($form.error.subject.missing)} 
      {g->error}
	{g->text text="You must enter a subject"}
      {/g->error}
    {/if} 

    {g->box}
      {g->title}
	{g->text text="Comment: "}
      {/g->title}
      {g->subtitle}
	{g->text text="required"}
      {/g->subtitle}
      {g->element}
	{g->textarea rows="15" cols="60" name="form.comment"}{$form.comment}{/g->textarea}
      {/g->element}
    {/g->box}

    {if isset($form.error.comment.missing)} 
      {g->error}
	{g->text text="You must enter a comment"}
      {/g->error}
    {/if} 
  {/g->box}

  {g->box}
    {g->element}
      {g->input type="submit" name="form.action.save"}{g->text text="Save"}{/g->input}
      {g->input type="submit" name="form.action.cancel"}{g->text text="Cancel"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}
