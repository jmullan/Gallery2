{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<rss version="2.0" xmlns:media="http://search.yahoo.com/mrss">
  <channel>
    <title> {* unused for now *} </title>
    <link>{g->url forceFullUrl=true}</link>
    <description> {* unused for now *} </description>
    <language> {* unused for now *} </language>
    {foreach from=$SlideshowMediaRss.items item=i}
    <item>
      <title type="html">{$i.item.title|markup|escape:html}</title>
      <link>{g->url arg1="view=core.ShowItem" arg2="itemId=`$i.item.id`" forceFullUrl=true}</link>
      <guid>{$i.item.id}</guid>
      <media:thumbnail url="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$i.thumbnail.id`" arg3="serialNumber=`$i.thumbnail.serialNumber`" forceFullUrl=true}" {if !empty($i.thumbnail.height)}height="{$i.thumbnail.height}" width="{$i.thumbnail.width}"{/if} type="{$i.thumbnail.mimeType}"/>
      {if !empty($i.image.mimeType)}
      <media:content url="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$i.image.id`" arg3="serialNumber=`$i.image.serialNumber`" forceFullUrl=true}" {if !empty($i.image.height)}height="{$i.image.height}" width="{$i.image.width}"{/if} type="{$i.image.mimeType}"/>
      {/if}
      <description type="html">{$i.item.summary|markup|escape:html}</description>
    </item>
    {/foreach}
  </channel>
</rss>
