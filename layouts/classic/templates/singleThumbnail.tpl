  <a href="{galleryUrl view=core:ShowItem itemId=$children[$child].id}">
    {if !empty($children[$child].thumbnail)}
    {assign var="thumbnail" value=$children[$child].thumbnail}
    <img src="{galleryUrl view=core:DownloadItem itemId=$thumbnail.id}"
      {if ($thumbnail.width && $thumbnail.height)}
      width="{$thumbnail.width}"
      height="{$thumbnail.height}"
      {/if}
      {if !empty($children[$child].title)}
      alt="{$children[$child].title}"
      {else}
      alt="{$children[$child].pathComponent}"
      border="0"
      {/if}
      >
    {else}
    {$children[$child].id}
    {/if}
  </a>
  {if (!empty($children[$child].moduleSummaries)) }
  {foreach from=$children[$child].moduleSummaries item=summary}
  <br>
  {$summary}
  {/foreach}
  {/if}
