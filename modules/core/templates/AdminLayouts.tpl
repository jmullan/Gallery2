{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Gallery Layouts"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.activated)}
	{g->text text="Successfully activated layout %s" arg1=$status.activated}
      {/if}
      {if isset($status.deactivated)}
	{g->text text="Successfully deactivated layout %s" arg1=$status.deactivated}
      {/if}
      {if isset($status.installed)}
	{g->text text="Successfully installed layout %s" arg1=$status.installed}
      {/if}
      {if isset($status.uninstalled)}
	{g->text text="Successfully uninstalled layout %s" arg1=$status.uninstalled}
      {/if}
      {if isset($status.savedLayout)}
	{g->text text="Successfully saved layout settings"}
      {/if}
      {if isset($status.savedDefaults)}
	{g->text text="Successfully saved default album settings"}
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
          <span>
          <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=config"}">{g->text text="All Layouts"}</a>
          </span>
        </li>
        {/if}

        {if ($AdminLayouts.mode == 'defaults')}
        <li class="giSelectedTab"> 
          <span>
          {g->text text="Defaults"}
          </span>
        </li>
        {else}
        <li>
          <span>
          <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=defaults"}">{g->text text="Defaults"}</a>
          </span>
        </li>
        {/if}

        {foreach from=$AdminLayouts.layouts key=layoutId item=layout}
        {if $layout.active}
        {if ($AdminLayouts.mode == 'editLayout') && ($AdminLayouts.layoutId == $layoutId)}
        <li class="giSelectedTab">
          <span>
            {g->text text=$layout.name l10Domain=$layout.l10Domain}
          </span>
        </li>
        {else}
        <li>
          <span>
          <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=editLayout" arg4="layoutId=$layoutId"}">{g->text text=$layout.name l10Domain=$layout.l10Domain}</a>
          </span>
        </li>
        {/if}
        {/if}
        {/foreach}
      </ul>
    </div>

    {if ($AdminLayouts.mode == 'config')}
    <div class="gbAdmin">
    
      <table class="gbDataTable">
        <tr>
	  <th> &nbsp; </th>
          <th> {g->text text="Layout Name"} </th>
          <th> {g->text text="Version"} </th>
	  <th> {g->text text="Installed"} </th>
          <th> {g->text text="Description"} </th>
          <th> {g->text text="Actions"} </th>
        </tr>

        {foreach from=$AdminLayouts.layouts key=layoutId item=layout}
        <tr class="{cycle values="gbEven,gbOdd"}">
	  <td>
	    {if $layout.state == 'install'}
            <img src="{g->url href="modules/core/data/module-install.gif"}" width="13" height="13" alt="{g->text text="Status: Not
Installed"}" />
            {/if}
	    {if $layout.state == 'active'}
	    <img src="{g->url href="modules/core/data/module-active.gif"}" width="13" height="13" alt="{g->text text="Status: Active"}" />
	    {/if}
	    {if $layout.state == 'inactive'}
	    <img src="{g->url href="modules/core/data/module-inactive.gif"}" width="13" height="13" alt="{g->text text="Status: Inactive"}" />
	    {/if}
	    {if $layout.state == 'upgrade'}
	    <img src="{g->url href="modules/core/data/module-upgrade.gif"}" width="13" height="13" alt="{g->text text="Status: Upgrade Required (Inactive)"}" />
	    {/if}
	    {if $layout.state == 'incompatible'}
	    <img src="{g->url href="modules/core/data/module-incompatible.gif"}" width="13" height="13" alt="{g->text text="Status: Incompatible Layout (Inactive)"}" />
	    {/if}
	  </td>

          <td {if ($layoutId == $AdminLayouts.defaultLayoutId)}style="font-weight: bold"{/if}>
            {$layout.name}
            {if ($layoutId == $AdminLayouts.defaultLayoutId)}
            {/if}
          </td>

          <td align="center" {if ($layoutId == $AdminLayouts.defaultLayoutId)}style="font-weight: bold"{/if}>
            {$layout.version}
          </td>

          <td align="center" {if ($layoutId == $AdminLayouts.defaultLayoutId)}style="font-weight: bold"{/if}>
            {$layout.installedVersion}
          </td>

          <td {if ($layoutId == $AdminLayouts.defaultLayoutId)}style="font-weight: bold"{/if}>
            {g->text text=$layout.description l10Domain=$layout.l10Domain}
	    {if $layout.state == 'incompatible'}
	    <br />
	    <span class="giError">
	      {g->text text="Incompatible layout!"}
	      {if $layout.api.required.core != $layout.api.provided.core}
		<br/>
		{g->text text="Core API Required: %s (available: %s)"
			 arg1=$layout.api.required.core arg2=$layout.api.provided.core}
	      {/if}
	      {if $layout.api.required.layout != $layout.api.provided.layout}
		<br/>
		{g->text text="Layout API Required: %s (available: %s)"
			 arg1=$layout.api.required.layout arg2=$layout.api.provided.layout}
	      {/if}
	    </span>
	    {/if}
          </td>

          <td {if ($layoutId == $AdminLayouts.defaultLayoutId)}style="font-weight: bold"{/if}>
            {if ($layoutId == $AdminLayouts.defaultLayoutId)}
            {g->text text="(default)"}
            {/if}
	    {if (!empty($layout.action))}
	    {foreach name=actions from=$layout.action item=action}
	    {strip}
	    {if !$smarty.foreach.actions.first}
	    <br/>
	    {/if}
	    <a href="{g->url params=$action.params}">
	      {$action.text}
	    </a>
	    {/strip}
	    {/foreach}
	    {else}
	    &nbsp;
	    {/if}
	  </td>
        </tr>
        {/foreach}
      </table>
    </div>
    {/if}

    {if ($AdminLayouts.mode == 'defaults')}
    <div class="gbAdmin">
      <h3 class="giTitle">
        {g->text text="Defaults"}
      </h3>

      <p class="giDescription">
        {g->text text="These are default display settings for albums in your gallery.  They can be overridden in each album."}
      </p>

      <table class="gbDataTable">
        <tr>
          <td>
            {g->text text="Default sort order"}
          </td>
          <td>
            <select name="{g->formVar var="form[default][orderBy]"}" onChange="pickOrder()">
                {html_options options=$AdminLayouts.orderByList selected=$form.default.orderBy}
            </select>
            <select name="{g->formVar var="form[default][orderDirection]"}">
                {html_options options=$AdminLayouts.orderDirectionList selected=$form.default.orderDirection}
            </select>
            {g->text text="with"}
            <select name="{g->formVar var="form[default][presort]"}">
                {html_options options=$AdminLayouts.presortList selected=$form.default.presort}
            </select>
            <script type="text/javascript">
            function pickOrder() {ldelim}
                var list = '{g->formVar var="form[default][orderBy]"}';
                var index = document.forms[0].elements[list].selectedIndex;
                list = '{g->formVar var="form[default][orderDirection]"}';
                document.forms[0].elements[list].disabled = (index == 0) ?1:0;
                list = '{g->formVar var="form[default][presort]"}';
                document.forms[0].elements[list].disabled = (index == 0) ?1:0;
              {rdelim}
              pickOrder();
            </script>
          </td>
        </tr>

        <tr>
          <td>
            {g->text text="Default layout"}
          </td>

          <td>
            <select name="{g->formVar var="form[default][layout]"}">
              {html_options options=$AdminLayouts.layoutList selected=$form.default.layout}
            </select>
          </td>
        </tr>

        <tr>
          <td>
            {g->text text="Default theme"}
          </td>

          <td>
            <select name="{g->formVar var="form[default][theme]"}">
              {html_options options=$AdminLayouts.themeList selected=$form.default.theme}
            </select>
          </td>
        </tr>

        <tr>
          <td>
            {g->text text="New albums"}
          </td>

          <td>
	    <select name="{g->formVar var="form[default][newAlbumsUseDefaults]"}">
	      {html_options options=$AdminLayouts.newAlbumsUseDefaultsList selected=$form.default.newAlbumsUseDefaults}
            </select>
          </td>
        </tr>
      </table>
    </div>

    <div class="gbBottomFlag">
      <div class="gbButtons">
        <input type="hidden" name="{g->formVar var="mode"}" value="defaults"/>
        <input type="submit" name="{g->formVar var="form[action][saveDefaults]"}" value="{g->text text="Save"}"/>
      </div>
    </div>
    {/if}

    {if ($AdminLayouts.mode == "editLayout")}
    <div class="gbAdmin">
      <h3 class="giTitle">
        {g->text text="%s Layout Settings" arg1=$AdminLayouts.layouts[$AdminLayouts.layoutId].name}
      </h3>

      <p class="giDescription">
        {g->text text="These are the global settings for the layout.  They can be overridden at the album level."}
      </p>

     {if isset($AdminLayouts.customTemplate)}

        {include file="gallery:`$AdminLayouts.customTemplate`" l10Domain=$AdminLayouts.layouts[$AdminLayouts.layoutId].l10Domain}

     {else}
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
            {elseif ($setting.type == 'checkbox')}
            <input type="checkbox" name="{g->formVar var="form[key][$settingKey]"}" 
            {if !empty($setting.value)}checked="checked"{/if}
            />
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
     {/if}
    </div>

    {if isset($AdminLayouts.customTemplate) || !empty($AdminLayouts.settings)}
    <div class="gbBottomFlag">
      <div class="gbButtons">
        <input type="hidden" name="{g->formVar var="layoutId"}" value="{$AdminLayouts.layoutId}"/>
        <input type="hidden" name="{g->formVar var="mode"}" value="editLayout"/>
        <input type="submit" name="{g->formVar var="form[action][saveLayout]"}" value="{g->text text="Save"}"/>
        <input type="submit" name="{g->formVar var="form[action][undoLayout]"}" value="{g->text text="Undo"}"/>
      </div>
    </div>
    {/if}
    {/if}
  </div>
</div>
