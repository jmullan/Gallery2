{gallery->bannerbox}
  {gallery->title}
    {gallery->text text="Use as parent's thumbnail?"}
  {/gallery->title}
{/gallery->bannerbox}

{gallery->detailedbox}
  {gallery->description}
    {gallery->text text="You can make use this item as the thumbnail for its parent album."}
  {/gallery->description}

  {gallery->body}
    {gallery->input type="submit" name="form.action.makeHighlight"}{gallery->text text="Yes, highlight this item!"}{/gallery->input}
  {/gallery->body}
{/gallery->detailedbox}
