{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if $layout.show.pathbar}
<div class="breadcrumb">
  <a href="/"> {g->text text="Home"} </a>
  /
  {section name=parent loop=$layout.parents}
    {if !$smarty.section.parent.last}
      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`"
       arg3="highlightId=`$layout.parents[parent.index_next].id`"}">
	{$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}
      </a>
    {else}
      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`"
       arg3="highlightId=`$layout.item.id`"}">
	{$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}
      </a>
    {/if}
    /
  {/section}
</div>
{/if}
