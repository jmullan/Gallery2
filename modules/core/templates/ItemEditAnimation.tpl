{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit Animation"}
    {/g->title}
  {/g->banner}

  {g->box style="admin"}
    {g->title}
      {g->text text="Sizes"}
    {/g->title}

    {g->description}
      {g->text text="In order for Gallery to properly display this animation, it has to know the animation's width and height.  If you have installed a graphics toolkit that can handle animation types, then these values may already be set.  If not, they may be set to 0.  If you do not enter the correct values here, the animation may appear distorted when viewed in your web browser.  Note that changing these values do <b>not</b> change the animation itself so experimentation won't cause harm."}
    {/g->description}

    {g->table style="admin_widgets"}
      {g->row}
	{g->column}
	  {g->text text="Width"}
	{/g->column}
	{g->column}
	  {g->input type="text" size="5" name="form[width]"}
	    {$form.width}
	  {/g->input}
        {/g->column}
      {/g->row}
      
      {if isset($form.error.width.invalid)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="You must enter a value greater than or equal to 0"}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}

      {g->row}
	{g->column}
	  {g->text text="Height"}
	{/g->column}
	{g->column}
	  {g->input type="text" size="5" name="form[height]"}
	    {$form.height}
	  {/g->input}
        {/g->column}
      {/g->row}

      {if isset($form.error.height.invalid)}
	{g->row}
	  {g->column colspan="2"}
	    {g->error}
	      {g->text text="You must enter a value greater than or equal to 0"}
	    {/g->error}
	  {/g->column}
	{/g->row}
      {/if}

    {/g->table}
	  
    {g->element}
      {g->input type="submit" name="form[action][save]"}
	{g->text text="Save"}
      {/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}
