{g->pagebox}
  {g->banner}
    {g->title} {g->text text="Panorama Settings"} {/g->title}
  {/g->banner}
  {if isset($status.saved)}
    {g->success}{g->text text="Settings saved successfully"}{/g->success}
  {/if}
  {if isset($status.reset)}
    {g->success}{g->text text="Items reset successfully"}{/g->success}
  {/if}
  {if isset($form.error.width)}
    {g->error}{g->text text="Invalid width value"}{/g->error}
  {/if}
  {if isset($status.deactivated)}
    {g->error}{g->text text="Reset panorama items to enable deactivation (see below)"}{/g->error}
  {/if}
  {g->box style="admin"}
    {g->description}
      {g->text text="The panorama viewer can be activated in two ways: the first allows album administrators to select individual images for panorama display (Panorama section in \"edit photo\"), overriding the normal display of the entire image.  The second method retains the normal image display but gives users an option in the \"item actions\" to view the image in the panorama viewer."}
    {/g->description}
    {g->element}
      {g->input type="checkbox" name="form[itemType]"}{$form.itemType}{/g->input}
      {g->text text="Add ability to assign applet as primary display for wide images"}
    {/g->element}{g->element}
      {g->input type="checkbox" name="form[itemLink]"}{$form.itemLink}{/g->input}
      {g->text text="Add \"view panorama\" option in item actions for wide images"}
    {/g->element}{g->element}
      {g->text text="Width of panorama viewer: "}
      {g->input type="text" size="6" name="form[width]"}{$form.width}{/g->input}
    {/g->element}{g->element}<br>
      {g->input type="submit" name="form[action][save]"}
        {g->text text="Save"}
      {/g->input}
      {g->input type="submit" name="form[action][undo]"}
        {g->text text="Undo"}
      {/g->input}
    {/g->element}
  {/g->box}
  {if $form.count>0}
    {g->box style="admin"}
      {g->description}
        {g->text text="This gallery contains items activated for panorama view.  These must be reset to standard items before this module can be deactivated.  You can reset all items here.  Warning: there is no undo."}
      {/g->description}
      {g->element}
        {g->input type="submit" name="form[action][reset]"}
          {g->text text="Reset all items"}
        {/g->input}
      {/g->element}
    {/g->box}
  {/if}
{/g->pagebox}
