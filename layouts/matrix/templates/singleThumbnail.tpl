    <a href="{gallery->url view=core:ShowItem itemId=$child.id}">
      {if !empty($child.thumbnail)}
      {assign var="thumbnail" value=$child.thumbnail}
      <img src="{gallery->url view=core:DownloadItem itemId=$thumbnail.id}"
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
      <br>
      <i>{gallery->text text="No thumbnail"}</i>
      <br>
      {/if}
    </a>
    {foreach from=$moduleItemLinks item=itemLinks key=loopId}
    {if ($loopId == $child.id)}
    <br>
    {gallery->select onChange="if (this.value) javascript:location.href=this.value"}
    <option value=""> {gallery->text text="<< Action >>"}
    {foreach from=$itemLinks item=module}
    {foreach from=$module item=link}
    <option value="{$link.url}"> {$link.text}
    {/foreach}
    {/foreach}
    {/gallery->select}
    {/if}
    {/foreach}
