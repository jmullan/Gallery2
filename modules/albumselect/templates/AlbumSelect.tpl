{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<select onchange="{literal}javascript:if (this.value) { var newLocation = this.value; this.options[0].selected = true; location.href = newLocation; }{/literal}" class="giActionSelect">
<option value="">
  {g->text text="&laquo; Jump to Album &raquo;"}
</option>
{foreach from=$AlbumSelectSystemContent.tree item=node}
  {assign var="title" value=$AlbumSelectSystemContent.titles[$node.id]}
  <option value="{g->url arg1="view=core:ShowItem" arg2="itemId=`$node.id`"}">
    {$title|entitytruncate:20|indent:$node.depth:"-- "|markup}
  </option>
{/foreach}
</select>
