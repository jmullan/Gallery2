      {galleryHeavyFrame}
    <a href="{galleryUrl view=core:ShowItem itemId=$child.id}">
      {if !empty($child.thumbnail)}
      {assign var="thumbnail" value=$child.thumbnail}
      <img src="{galleryUrl view=core:DownloadItem itemId=$thumbnail.id}"
      {if ($thumbnail.width && $thumbnail.height)}
           width="{$thumbnail.width}"
           height="{$thumbnail.height}"
      {/if}
      {if !empty($child.title)}
           alt="{$child.title}"
      {else}
           alt="{$child.pathComponent}"
      {/if}
           border="0"
      >
      {else}
      <i>{galleryText text="No thumbnail"}</i>
      {/if}
    </a>
    {/galleryHeavyFrame}
