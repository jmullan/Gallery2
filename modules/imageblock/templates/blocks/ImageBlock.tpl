{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !isset($useDefaults)} {assign var="useDefaults" value=true} {/if}
{if !isset($showHeading)} {assign var="showHeading" value=true} {/if}
{if !isset($showTitle)} {assign var="showTitle" value=true} {/if}
{if !isset($showDate)} {assign var="showDate" value=false} {/if}
{if !isset($showViews)} {assign var="showViews" value=false} {/if}
{if !isset($showOwner)} {assign var="showOwner" value=false} {/if}

{g->callback type="imageblock.LoadImageBlock"
	     blocks=$blocks|default:null maxSize=$maxSize|default:null
	     itemId=$itemId|default:null linkTarget=$linkTarget|default:null}

{if !empty($ImageBlockData)}
<div class="{$class}">
  {include file="gallery:modules/imageblock/templates/ImageBlock.tpl"}
</div>
{/if}
