{g->pagebox}
  {g->banner}
    {g->title} {g->text text="Image Block Admin"} {/g->title}
  {/g->banner}
  {if isset($status.saved)}
    {g->success}{g->text text="Settings saved successfully"}{/g->success}
  {/if}
  {g->box style="admin"}
    {g->title} {g->text text="Image Blocks"} {/g->title}
    {g->description} {/g->description}
    {g->element}
      {g->input type="checkbox" name="form[randomImage]"}{$form.randomImage}{/g->input}
      {g->text text="Random Image"}
    {/g->element}{g->element}
      {g->input type="checkbox" name="form[recentImage]"}{$form.recentImage}{/g->input}
      {g->text text="Newest Image"}
    {/g->element}{g->element}
      {g->input type="checkbox" name="form[viewedImage]"}{$form.viewedImage}{/g->input}
      {g->text text="Most Viewed Image"}
    {/g->element}{g->element}
      {g->input type="checkbox" name="form[randomAlbum]"}{$form.randomAlbum}{/g->input}
      {g->text text="Random Album"}
    {/g->element}{g->element}
      {g->input type="checkbox" name="form[recentAlbum]"}{$form.recentAlbum}{/g->input}
      {g->text text="Newest Album"}
    {/g->element}{g->element}
      {g->input type="checkbox" name="form[viewedAlbum]"}{$form.viewedAlbum}{/g->input}
      {g->text text="Most Viewed Album"}
    {/g->element}
  {/g->box}
  {g->box style="admin"}
    {g->element}
      {g->input type="submit" name="form[action][save]"}
        {g->text text="save"}
      {/g->input}
      {g->input type="submit" name="form[action][reset]"}
        {g->text text="reset"}
      {/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}
