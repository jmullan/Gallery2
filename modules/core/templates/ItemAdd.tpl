{*
 * $Revision$ $Date$
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

  {if (! $ItemAdd.hasToolkit)}
  <div id="gsStatus">
   <div class="giWarning">
      {g->text text="You don't have any Graphics Toolkit activated that can handle JPEG images.  If you add images, you will probably not have any thumbnails."}
      {capture name="url"}
      {g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminModules"}
      {/capture}
      {if $ItemAdd.isAdmin}
      {g->text text="Visit the <a href=\"%s\">Modules</a> page to activate a Graphics Toolkit." arg1=$smarty.capture.url}
      {/if}
   </div>
  </div>
  {/if}

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
