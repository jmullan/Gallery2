{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Add Comment"}
  {/gallery->title}
{/gallery->bannerbox}

{if ($form.action.preview)}
  {gallery->detailedbox}
    {gallery->title}
      {gallery->text text="Comment Preview"}
    {/gallery->title}

    {gallery->body}
      {gallery->detailedbox}
	{gallery->title}
	  {$form.subject}
	{/gallery->title}
	{gallery->body}
	  {$form.comment}
	{/gallery->body}
      {/gallery->detailedbox}
    {/gallery->body}
  {/gallery->detailedbox}
{/if}

{gallery->detailedbox}
  {gallery->body}
    {gallery->widget2box}
      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Posted by"}
	{/gallery->title}
	{gallery->body}
	  {gallery->text text="%s (%s)" arg1=$AddComment.user.fullName arg2=$AddComment.host}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Subject"}
	  {gallery->textmodifier}
	    {gallery->text text="required"}
	  {/gallery->textmodifier}
	{/gallery->title}
	{gallery->body}
	  {gallery->input type="text" size="60" name="form.subject"}{$form.subject}{/gallery->input}
	  {if isset($form.error.subject.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a subject!"}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget2}

      {gallery->widget2}
	{gallery->title}
	  {gallery->text text="Comment"}
	  {gallery->textmodifier}
	    {gallery->text text="required"}
	  {/gallery->textmodifier}
	{/gallery->title}
	{gallery->body}
	  {gallery->textarea rows="15" cols="60" name="form.comment"}{$form.comment}{/gallery->textarea}
	  {if isset($form.error.comment.missing)}
	    {gallery->error}
	      {gallery->text text="You must enter a comment!"}
	    {/gallery->error}
	  {/if}
	{/gallery->body}
      {/gallery->widget2}
    {/gallery->widget2box}
  {/gallery->body}
{/gallery->detailedbox}

{gallery->detailedbox}
  {gallery->body}
    {gallery->input type="submit" name="form.action.preview"}{gallery->text text="preview"}{/gallery->input}
    {gallery->input type="submit" name="form.action.add"}{gallery->text text="save"}{/gallery->input}
    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="cancel"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}
