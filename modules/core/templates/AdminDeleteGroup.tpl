{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Delete a group"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->title}
    {gallery->text text="Are you sure?"}
  {/gallery->title}

  {gallery->description}
    {gallery->text text="This will completely remove <b>%s</b> from Gallery.  There is no undo!"
    arg1=$AdminDeleteGroup.group.groupName}
  {/gallery->description}

  {gallery->body}
    {gallery->input type="hidden" name="groupId"}{$AdminDeleteGroup.group.id}{/gallery->input}
    {gallery->input type="submit" name="form.action.delete"}{gallery->text text="Delete"}{/gallery->input}
    {gallery->input type="submit" name="form.action.cancel"}{gallery->text text="Cancel"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}
