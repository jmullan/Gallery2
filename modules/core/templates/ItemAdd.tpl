{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemAdd.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Add Items"}
      </h2>
    </div>

  </div>

  <div class="gbTabBar">
    <ul>
      {foreach from=$ItemAdd.plugins item=plugin} 
      {if $plugin.isSelected}
      <li class="giSelectedTab"> 
        <span>
        {$plugin.title}
        </span>
      </li>
      {else}
      <li>
        <span>
        <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemAdd" arg3="itemId=`$ItemAdmin.item.id`" arg4="addPlugin=`$plugin.id`"}">{$plugin.title}</a>
        </span>
      </li>
      {/if}
      {/foreach}
    </ul>
  </div>

  <input type="hidden" name="{g->formVar var="addPlugin"}" value="{$ItemAdd.addPlugin}"/>
  {include file="gallery:`$ItemAdd.pluginFile`" l10Domain=$ItemAdd.pluginL10Domain}
</div>
