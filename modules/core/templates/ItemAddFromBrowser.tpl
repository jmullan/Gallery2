{g->box style="admin"}
  {g->description}
    {g->text one="Upload a file directly from your computer."
    many="Upload up to %d files directly from your computer."
    count=$form.uploadBoxCount
    arg1=$form.uploadBoxCount}
    {g->text text="Enter the full path to the file and an optional caption in the boxes below."}
    {g->input type="hidden" name="form[uploadBoxCount]"}{$form.uploadBoxCount}{/g->input}
  {/g->description}

  {g->element}
    {section name="uploadBoxes" loop=$form.uploadBoxCount}
      {assign var=iteration value=$smarty.section.uploadBoxes.iteration}
      {g->box}
	{g->title}
	  {g->text text="File"}
	{/g->title}
	{g->element}
	  {g->input name="form[$iteration]" type="file" size="60"}{/g->input}
	{/g->element}
      {/g->box}

      {g->box}
	{g->title}
	  {g->text text="Caption"}
	{/g->title}
	{g->element}
	  {g->textarea rows="2" cols="60" name="form[caption][$iteration]"}{/g->textarea}
	{/g->element}
      {/g->box}
    {/section}
  {/g->element}

  {g->element}
    {g->input type="submit" name="form[action][addFromBrowser]"}{g->text text="Add Items"}{/g->input}
  {/g->element}
{/g->box}
