{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if empty($item)} {assign var=item value=$theme.item} {/if}

{if !empty($item.keywords)}
<div class="{$class}">
  {g->text text="Keywords:"}
  {foreach from=$item.keywords|split:'/\s+/':true item=keyword}
    <a href="{g->url arg1="view=keyalbum.KeywordAlbum" arg2="keyword=$keyword"
		     arg3="highlightId=`$item.id`"}">{$keyword}</a>
  {/foreach}
</div>
{/if}
