<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Gallery Layouts"}
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  {if isset($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.activated)}
	{g->text text="Successfully activated layout %s" arg1=$status.activated}
      {/if}
      {if isset($status.deactivated)}
	{g->text text="Successfully deactivated layout %s" arg1=$status.deactivated}
      {/if}
      {if isset($status.savedLayout)}
	{g->text text="Successfully saved layout settings"}
      {/if}
      {if isset($status.restoredLayout)}
	{g->text text="Restored layout settings"}
      {/if}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="gbTabBar">
      <ul>
	{if ($AdminLayouts.mode == 'config')}
	<li class="giSelectedTab"> 
		<span>
	  {g->text text="All Layouts"}
		</span>
	</li>
        {else}
        <li>
	  <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=config"}">{g->text text="All Layouts"}</a>
	</li>
        {/if}

        {foreach from=$AdminLayouts.layouts key=layoutId item=layout}
        {if $AdminLayouts.layouts.$layoutId.active}
        {if ($AdminLayouts.mode == 'editLayout') && ($AdminLayouts.layoutId == $layoutId)}
        <li class="giSelectedTab">
            <span>
	  {g->text text=$layout.name l10Domain=$layout.l10Domain}
            </span>
	</li>
	{else}
        <li>
	  <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=editLayout" arg4="layoutId=$layoutId"}">{g->text text=$layout.name l10Domain=$layout.l10Domain}</a>
        </li>
        {/if}
        {/if}
        {/foreach}
      </ul>
    </div>

    <div class="gbSpacer">
      &nbsp;
    </div>

    {if ($AdminLayouts.mode == 'config')}
    <div class="gbAdmin">
      <div class="giTitle">
	{g->text text="Layout Configuration"}
      </div>

      <div class="giDescription">
	{g->text text="Gallery has layouts that can change the way that you navigate around your albums.  You can download and install new layouts, or you can disable layouts if you don't want to use them.  By default, new layouts are disabled.  They must be enabled before you can use them."}
      </div>

      <table class="gbDataTable">
	<tr>
	  <th> {g->text text="Layout Name"} </th>
	  <th> {g->text text="Version"} </th>
	  <th> {g->text text="Description"} </th>
	  <th> {g->text text="Actions"} </th>
	</tr>

	{foreach from=$AdminLayouts.layouts key=layoutId item=layout}
	<tr class="{cycle values="gbEven,gbOdd"}">
	  <td>
	    {$layout.name}
	  </td>

	  <td align="center">
	    {$layout.version}
	  </td>

	  <td>
	    {g->text text=$layout.description l10Domain=$layout.l10Domain}
	  </td>

	  <td>
	    <div class="giHorizontalLinks">
	      {if (isset($layout.actions.activate))}
	      <span>
		<a href="{g->url arg1="controller=core:AdminLayouts" arg2="form[action][activate]=1" arg3="layoutId=$layoutId"}">{g->text text="activate"}</a>
	      </span>
	      {/if}

	      {if (isset($layout.actions.deactivate))}
	      <span>
		<a href="{g->url arg1="controller=core:AdminLayouts" arg2="form[action][deactivate]=1" arg3="layoutId=$layoutId"}">{g->text text="deactivate"}</a>
	      </span>
	      {/if}
	    </div>
	  </td>
	</tr>
	{/foreach}
      </table>
    </div>
    {/if}

    {if ($AdminLayouts.mode == "editLayout")}
    <div class="gbAdmin">
      <div class="giTitle">
	{g->text text="%s Layout Settings" arg1=$AdminLayouts.layouts[$AdminLayouts.layoutId].name}
      </div>

      <div class="giDescription">
	{g->text text="These are the global settings for the layout.  They can be overridden at the album level."}
      </div>

      {if !empty($AdminLayouts.settings)}
      <table>
	{foreach from=$AdminLayouts.settings item=setting}
	{assign var="settingKey" value=$setting.key}
	<tr class="{cycle values="gbEven,gbOdd"}">
	  <td>
	    {g->text text=$setting.name l10Domain=$layout.l10Domain}
	  </td>

	  <td>
	    {if ($setting.type == 'text-field')}
	    <input type="text" size="6" name="{g->formVar var="form[key][$settingKey]"}" value="{$form.key.$settingKey}"/>
	    {elseif ($setting.type == 'single-select')}
	    <select name="{g->formVar var="form[key][$settingKey]"}">
		{html_options options=$setting.choices selected=$setting.value}
	    </select>
	    {/if}
	  </td>
	</tr>

	{if isset($form.error.key.$settingKey.invalid)}
	<tr>
	  <td colspan="2">
	    <div class="giError">
	      {$form.errorMessage.$settingKey}
	    </div>
	  </td>
	</tr>
	{/if}
	{/foreach}
      </table>
      {else}
      <span>
	{g->text text="There are no settings for this layout"}
      </span>
      {/if}
    </div>

    <div class="gbBottomFlag">
      <div class="giActionSelect">
	<input type="hidden" name="{g->formVar var="layoutId"}" value="{$AdminLayouts.layoutId}"/>
	<input type="hidden" name="{g->formVar var="mode"}" value="editLayout"/>
	<input type="submit" name="{g->formVar var="form[action][saveLayout]"}" value="{g->text text="Save"}"/>
	<input type="submit" name="{g->formVar var="form[action][undoLayout]"}" value="{g->text text="Undo"}"/>
      </div>
    </div>
    {/if}
  </div>
</div>
