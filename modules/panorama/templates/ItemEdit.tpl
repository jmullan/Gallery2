{g->box style="admin"}
  {g->description}
    {g->text text="Note that panorama view only applies to full size photo, not resizes."}
  {/g->description}
  {g->element}
    {g->input type="checkbox" name="form[isPanorama]"}{$form.isPanorama}{/g->input}
    {g->text text="Activate panorama viewer applet for this photo"}
  {/g->element}
  {g->box}
    {g->description} {/g->description}
    {g->element}
      {g->input type="submit" name="form[action][save]"}{g->text text="Save"}{/g->input}
    {/g->element}
  {/g->box}
{/g->box}
