{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminModules.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Gallery Modules"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  {if isset($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.installed)}
	{g->text text="Successfully installed module %s" arg1=$status.installed}
      {/if}
      {if isset($status.activated)}
	{g->text text="Successfully activated module %s" arg1=$status.activated}
      {/if}
      {if isset($status.deactivated)}
	{g->text text="Successfully deactivated module %s" arg1=$status.deactivated}
      {/if}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="Gallery features come as separate modules.  You can download and install modules to add more features to your Gallery, or you can disable features if you don't want to use them.  In order to use a feature, you must install, configure (if necessary) and activate it.  If you don't wish to use a feature, you can deactivate it."}
    </div>

    <table>
      <tr>
	<th> {g->text text="Module Name"} </th>
	<th> {g->text text="Version"} </th>
	<th> {g->text text="Description"} </th>
	<th> {g->text text="Actions"} </th>
      </tr>

      {foreach from=$AdminModules.modules item=module}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {$module.name}
	</td>

	<td align="center">
	  {$module.version}
	</td>

	<td>
	  {g->text text=$module.description l10Domain=$module.l10Domain}
	</td>

	<td>
	  {if (!empty($module.action))}
	  {if (empty($module.action.controller)) }
	  <a href="{g->url arg1="return=true" arg2="view=core:SiteAdmin" arg3="subView=`$module.action.view`"}">
	    {$module.action.text}
	  </a>
	  {else}
	  <a href="{g->url arg1="controller=`$module.action.controller`" arg2="moduleId=`$module.action.moduleId`" arg3="action=`$module.action.action`"}">
	    {$module.action.text}
	  </a>
	  {/if}
	  {else}
	  &nbsp;
	  {/if}
	</td>
      </tr>
      {/foreach}
    </table>
  </div>
</div>
