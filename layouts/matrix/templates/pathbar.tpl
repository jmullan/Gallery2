{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to pathbar.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsSystemLinks">
  <ul>
  {if $layout.show.sidebarGreeting}
  <li>
    {g->text text="Welcome, %s" arg1=$layout.user.fullName|default:$layout.user.userName}
  </li>
  {/if}
  {foreach from=$layout.systemLinks item=item}
  <li>
    <a href="{g->url params=$item.params}">{$item.text}</a>
  </li>
  {/foreach}
  </ul>
</div>

<ul class="gbBreadCrumb">
  {section name=parent loop=$layout.parents}
  <li {if $smarty.section.parent.first}class="giBreadCrumbFirst"{/if}>
    {if ! $smarty.section.parent.last}
    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`" arg3="highlightId=`$layout.parents[parent.index_next].id`"}">{$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}</a>
    {else}
    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.parents[parent].id`" arg3="highlightId=`$layout.item.id`"}">{$layout.parents[parent].title|default:$layout.parents[parent].pathComponent|markup}</a>
    {/if}
  </li>
  {/section}
  <li {if empty($layout.parents)}class="giBreadCrumbFirst"{/if}>
    {$layout.item.title|default:$layout.item.pathComponent|markup}
  </li>
</ul>
