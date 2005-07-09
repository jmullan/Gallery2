{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}

{*
 * The image block has a ton of optional parameters.  If we try to pass them
 * in here, we'll have to deal with the fact that many of them may not be defined
 * so instead, let the callback handle that.
 *}
{g->callback type="imageblock.LoadImageBlock"}

{if !empty($ImageBlockSystemContent)}
<div class="{$class}">
  {include file="gallery:modules/imageblock/templates/ImageBlock.tpl"}
</div>
{/if}
