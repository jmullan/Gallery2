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
    {foreach from=$moduleItemLinks item=itemLinks key=loopId}
    {if ($loopId == $child.id)}
    <br>
    {gallerySelect onChange="javascript:location.href=this.value"}
    <option value=""> {galleryText text="<< Action >>"}
    {foreach from=$itemLinks item=module}
    {foreach from=$module item=link}
    <option value="{$link.url}"> {$link.text}
    {/foreach}
    {/foreach}
    {/gallerySelect}
    {/if}
    {/foreach}
