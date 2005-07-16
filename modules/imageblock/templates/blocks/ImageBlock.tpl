{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !isset($show)} {assign var=show value=""} {/if}
{if !isset($showHeading)} {assign var=showHeading value=true} {/if}
{if $showHeading} {assign var=show value="$show|heading"} {/if}

{g->callback type="imageblock.LoadImageBlock"
	     blocks=$blocks|default:null show=$show|default:null maxSize=$maxSize|default:null
	     itemId=$itemId|default:null linkTarget=$linkTarget|default:null}

{if !empty($ImageBlockData)}
<div class="{$class}">
  {include file="gallery:modules/imageblock/templates/ImageBlock.tpl"}
</div>
{/if}
