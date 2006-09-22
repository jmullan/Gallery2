{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if $forItem|default:true} {* Links for keywords of current item *}
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

{else} {* Select box or cloud for all available keywords *}
{g->callback type="keyalbum.LoadKeywords" onlyPublic=$onlyPublic|default:true
	     maxCloudFontEnlargement=$maxCloudFontEnlargement|default:5}

{if !empty($block.keyalbum.keywords)}
<div class="{$class}">
  {if $showCloud|default:false}
    {foreach from=$block.keyalbum.keywords item=keyword}
      &nbsp;<a href="{g->url arg1="view=keyalbum.KeywordAlbum" arg2="keyword=`$keyword.name`"}">
	{if $keyword.weight > 0}
	  <font size="+{$keyword.weight}px">{$keyword.name}</font>
	{else}
	  {$keyword.name}
	{/if}
      </a>&nbsp;
    {/foreach}
  {else}
  <select onchange="if (this.value) {ldelim} var newLocation = this.value; this.options[0].selected = true; location.href = newLocation; {rdelim}">
    <option value="">
      {g->text text="&laquo; Keyword Album &raquo;"}
    </option>
    {foreach from=$block.keyalbum.keywords item=keyword}
      <option value="{g->url arg1="view=keyalbum.KeywordAlbum" arg2="keyword=`$keyword.name`"}">
	{$keyword.name}
      </option>
    {/foreach}
  </select>
  {/if}
</div>
{/if}
{/if}
