{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminLayouts.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
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
        {if ($AdminLayouts.mode == 'defaults')}
        <li class="giSelectedTab"> 
          <span>
          {g->text text="Defaults"}
          </span>
        </li>
        {else}
        <li>
          <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=defaults"}">{g->text text="Defaults"}</a>
        </li>
        {/if}

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

    {if ($AdminLayouts.mode == 'config')}
    <div class="gbAdmin">
    
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
            <script type="text/javascript">
            function pickOrder() {ldelim}
                var list = '{g->formVar var="form[default][orderBy]"}';
                var index = document.forms[0].elements[list].selectedIndex;
                list = '{g->formVar var="form[default][orderDirection]"}';
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
