{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Add Comment"}
    {/g->title}
  {/g->banner}

  {if isset($form.action.preview)}
    {g->box style="admin"}
      {g->title}
	{g->text text="Comment Preview"}
      {/g->title}
      
      {g->box style="comment"}
	{g->title}
	  {$form.subject}
	{/g->title}
	{g->element}
	  {$form.comment}
	{/g->element}
      {/g->box}
    {/g->box}
  {/if}

  {g->box style="admin"}
    {g->box}
      {g->title}
	{g->text text="Posted by"}
      {/g->title}
      {g->element}
	{g->text text="%s (%s)" arg1=$AddComment.user.fullName arg2=$AddComment.host}
      {/g->element}
    {/g->box}

    {g->box}
      {g->title}
	{g->text text="Subject"}
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
	{g->text text="You must enter a subject!"}
      {/g->error}
    {/if}

    {g->box}
      {g->title}
	{g->text text="Comment"}
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
	{g->text text="You must enter a comment!"}
      {/g->error}
    {/if}
  {/g->box}

  {g->element}
    {g->input type="submit" name="form.action.preview"}{g->text text="preview"}{/g->input}
    {g->input type="submit" name="form.action.add"}{g->text text="save"}{/g->input}
    {g->input type="submit" name="form.action.cancel"}{g->text text="cancel"}{/g->input}
  {/g->element}
{/g->pagebox}
