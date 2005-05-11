{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="URL Rewrite Administration"} </h2>
</div>

{if !empty($status)}
<div class="gbBlock"><h2 class="giSuccess">
  {if isset($status.rulesSaved)}
    {g->text text="Successfully saved URL styles"}
  {/if}

  {if isset($status.setupSaved)}
    {g->text text="Successfully saved the configuration"}
  {/if}
</div>
{/if}

{if !empty($form.error)}
<div class="gbBlock">
  <h2 class="giError"> {g->text text="An error occured while trying to save your settings:"} </h3>

  <div class="giError">
  {if isset($form.error.cantWrite.gallery)}
    {g->text text="Cannot write to the Gallery .htaccess file"}
  {/if}

  {if isset($form.error.cantWrite.embedded)}
    {g->text text="Cannot write to the embedded .htaccess file"}
  {/if}

  {if isset($form.error.dupe)}
    {g->text text="Duplicate URL patterns."}
  {/if}

  {if isset($form.error.empty)}
    {g->text text="Empty URL pattern."}
  {/if}

  {if isset($form.error.badKeyword)}
    {g->text text="Bad keyword."}
  {/if}
  </div>
</div>
{/if}

<ul class="gbTabBar">
  {if ($AdminRewrite.mode == 'rules')}
    <li class="giSelected"><span>
      {g->text text="Rules"}
    </span></li>
  {else}
    <li><span>
      <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=rewrite:AdminRewrite"
       arg3="mode=rules"}">{g->text text="Rules"}</a>
    </span></li>
  {/if}

  {if ($AdminRewrite.mode == 'setup')}
    <li class="giSelected"><span>
      {g->text text="Setup"}
    </span></li>
  {else}
    <li><span>
      <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=rewrite:AdminRewrite"
       arg3="mode=setup"}">{g->text text="Setup"}</a>
    </span></li>
  {/if}

  {if ($AdminRewrite.mode == 'test')}
    <li class="giSelected"><span>
      {g->text text="Test"}
    </span></li>
  {else}
    <li><span>
      <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=rewrite:AdminRewrite"
       arg3="mode=test"}">{g->text text="Test"}</a>
    </span></li>
  {/if}
</ul>

{if $AdminRewrite.mode == 'rules'}
<div class="gbBlock">
  <p class="giDescription">
      {g->text text="Short URLs are compiled out of predefined keywords. Modules may provide additional keywords. Keywords are escaped with % (eg: %itemId%)."}
  </p>

  <table class="gbDataTable">
  {assign var="group" value=""}
  {foreach from=$AdminRewrite.shortUrls item=module key=moduleId}
  {if !empty($group)}
    <tr><td> &nbsp; </td></tr>
  {/if}
  {assign var="group" value=$module.name}
  <tr><th colspan="6"><h2>{$module.name}</h2></th></tr>
  <tr>
    <th colspan="2" style="text-align: center;"> {g->text text="Active"} </th>
    <th> {g->text text="Help"} </th>
    <th> {g->text text="View"} </th>
    <th> {g->text text="URL Pattern"} </th>
    <th> {g->text text="Additional Keywords"} </th>
  </tr>

  {foreach from=$form.shortUrls.$moduleId item=rule key=index}
  {cycle values="gbEven,gbOdd" assign="rowClass"}
  <tr class="{$rowClass}">
    <td>
      {if isset($form.error.dupe[$rule.pattern]) || isset($form.error.empty.$moduleId.$index)}
        <img src="{g->url href="modules/core/data/module-inactive.gif"}" width="13" height="13"
	       alt="{g->text text="Status: Error"}" />
      {elseif isset($rule.active)}
        <img src="{g->url href="modules/core/data/module-active.gif"}" width="13" height="13"
	     alt="{g->text text="Status: Active"}" />
      {else}
        <img src="{g->url href="modules/core/data/module-install.gif"}" width="13" height="13"
	     alt="{g->text text="Status: Not Active"}" />
      {/if}
    </td>
    <td>
      <input type="checkbox" name="{g->formVar var="form[shortUrls][$moduleId][$index][active]"}" {if isset($rule.active)}checked="checked"{/if}/>
      {if isset($rule.match)}
        <input type="hidden" name="{g->formVar var="form[shortUrls][$moduleId][$index][match]}" value="{$rule.match}" />
      {/if}
    </td>
    <td style="text-align: center;">
      <span id="shortUrls-{$moduleId}-{$index}-toggle"
	    class="giBlockToggle gcBackground1 gcBorder2"
	    style="border-width: 1px;"
	    onclick="BlockToggle('shortUrls-{$moduleId}-{$index}-help', 'shortUrls-{$moduleId}-{$index}-toggle', 'table-row')">+</span>
    </td>
    <td>
      {$AdminRewrite.shortUrls.$moduleId.rules.$index.name|default:""}
    </td>
    <td>
      {if isset($AdminRewrite.shortUrls.$moduleId.rules.$index.locked)}
        {$rule.pattern}
        <input type="hidden" name="{g->formVar var="form[shortUrls][$moduleId][$index][pattern]"}" value="{$rule.pattern}" />
      {else}
        <input type="text" size="40" name="{g->formVar var="form[shortUrls][$moduleId][$index][pattern]"}" value="{$rule.pattern}" />
      {/if}
    </td>
    <td>
      {foreach from=$AdminRewrite.shortUrls.$moduleId.rules.$index.keywords key=keyword item=prefs}
        %{$keyword}%
      {/foreach}
    </td>
  </tr>
  <tr class="{$rowClass}" style="display: none;" id="shortUrls-{$moduleId}-{$index}-help">
    <td colspan="2">
      &nbsp;
    </td>
    <td colspan="4">
      <b>{g->text text="Help"}</b><br/>
      {if isset($AdminRewrite.shortUrls.$moduleId.rules.$index.help)}
        {$AdminRewrite.shortUrls.$moduleId.rules.$index.help}
      {else}
        <i>{g->text text="No help available"}</i>
      {/if}<br/><br/>
      <b>{g->text text="Keywords"}</b><br/>
      {assign var="hasKeywordHelp" value=false}
      {foreach from=$AdminRewrite.shortUrls.$moduleId.rules.$index.keywords key=keyword item=prefs}
        {if isset($prefs.help)}
          %{$keyword}% : {$prefs.help}<br/>
          {assign var="hasKeywordHelp" value=true}
        {/if}
      {/foreach}
      {if !$hasKeywordHelp}
        <i>{g->text text="No keyword help available"}</i>
      {/if}
    </td>
  </tr>
  {/foreach}

  {/foreach}
  </table>
</div>

<div class="gbBlock gcBackground1">
  <input type="submit"class="inputTypeSubmit" name="{g->formVar var="form[action][saveRules]"}" value="{g->text text="Save"}"/>
</div>
{/if}

{if $AdminRewrite.mode == 'setup'}
<div class="gbBlock">
  <h3> {g->text text="Approved referers"} </h3>

  <p class="giDescription">
    {g->text text="Some rules only apply if the referer (the site that linked to the item) is something other than Gallery itself. Hosts in the list below will be treated as friendly referers."}<br/>
  </p>

  <table class="gbDataTable"><tr>
    <td><input type="text" name="{g->formVar var="form[dummy]"}" size="60" value="{$AdminRewrite.serverName}" disabled/></td>
  {counter start=0 assign="i"}
  {foreach from=$form.allow item=host}
  </tr><tr>
    <td><input type="text" name="{g->formVar var="form[allow][$i]"}" size="60" value="{$host}"/></td>
    {counter print=false}
  {/foreach}
  </tr><tr>
    <td><input type="text" name="{g->formVar var="form[allow][$i]"}" size="60"/></td>
  </tr><tr>
    <td><input type="text" name="{g->formVar var="form[allow][`$i+1`]"}" size="60"/></td>
  </tr><tr>
    <td><input type="text" name="{g->formVar var="form[allow][`$i+2`]"}" size="60"/></td>
  </tr></table>
</div>

{if $AdminRewrite.isEmbedded}
<div class="gbBlock">
  <h3> {g->text text="Embedded Setup"} </h3>

  <p class="giDescription">
    {g->text text="For URL Rewrite to work in an embedded environment you need to set up an extra htaccess file to hold the mod_rewrite rules."}
  </p>

  <input type="hidden" name="{g->formVar var="form[embedded][save]"}" value="true">
  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Htaccess path:"}
    </td><td>
      <input type="text" size="60" name="{g->formVar var="form[embedded][htaccessPath]"}" value="{$form.embedded.htaccessPath}"/>
      {if isset($form.error.invalidDir)}
        <div class="giError">
          {g->text text="Invalid directory."}
        </div>
      {/if}
    </td>
  </tr><tr>
    <td>
      {g->text text="Public path:"}
    </td><td>
      {$AdminRewrite.host}<input type="text" size="40" name="{g->formVar var="form[embedded][publicPath]"}" value="{$form.embedded.publicPath}"/>
      {if isset($form.error.invalidPath)}
        <div class="giError">
          {g->text text="Invalid path."}
        </div>
      {/if}
    </td>
  </tr></table>
</div>
{/if}

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit" name="{g->formVar var="form[action][saveSetup]"}" value="{g->text text="Save"}"/>
</div>
{/if}

{if $AdminRewrite.mode == 'test'}
<div class="gbBlock">
  <h3> {g->text text="Testing your Webserver"} </h3>

  {assign var="showTestButton" value=false}
  {if $AdminRewrite.apacheCode == REWRITE_STATUS_OK}
    <div class="giSuccess">
      {g->text text="Apache mod_rewrite is working properly."}
    </div>
  {/if}

  {if ($AdminRewrite.apacheCode == REWRITE_STATUS_APACHE_NO_MOD_REWRITE)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Apache mod_rewrite is not installed or not enabled."}
    </div>
  {/if}

  {if ($AdminRewrite.apacheCode == REWRITE_STATUS_APACHE_UNABLE_TO_TEST)}
    {assign var="showTestButton" value=true}
    {assign var="showConfig" value=true}
    <div class="giError">
      {g->text text="We are unable to properly test whether mod_rewrite is properly installed."}
    </div>
  {/if}

  {if !empty($showTestButton)}
    <br/>
    <input type="submit" class="inputTypeSubmit"
      name="{g->formVar var="form[action][test]"}" value="{g->text text="Test Webserver Again"}"/>
    <br/><br/>
  {/if}

  {if !empty($showConfig)}
    <h3>Manual Configuration</h3>

    <p class="giDescription">
      {g->text text="Gallery tries to test mod_rewrite in action. For this to work you need to edit each of these two files accordingly:"}<br/>
    </p>

    <p class="giDescription">
      <b>{$AdminRewrite.customFile}</b><br/>
      {g->text text="Line 6:"} {$AdminRewrite.customLine}
    </p>

    <p class="giDescription">
      <b>{$AdminRewrite.customFileNoOptions}</b><br/>
      {g->text text="Line 6:"} {$AdminRewrite.customLineNoOptions}
    </p>
  {/if}
</div>

{if !empty($showTestButton)}
  {include file="gallery:modules/rewrite/templates/Troubleshooting.tpl"}
{/if}

<div class="gbBlock">
  <h3> {g->text text="Testing Gallery .htaccess file"} </h3>

  {assign var="showTestButton" value=false}
  {if ($AdminRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_READY)}
    <div class="giSuccess">
      {g->text text="Gallery can write to the .htaccess file"}
    </div>
  {/if}

  {if ($AdminRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_CANT_WRITE)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Cannot write to the .htaccess file."}
    </div>
  {/if}

  {if ($AdminRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_MISSING)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="The .htaccess file does not exist."}
    </div>
  {/if}

  {if ($AdminRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_CANT_READ)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Cannot read the .htaccess file."}
    </div>
  {/if}

  {if !empty($showTestButton)}
    <br/>
    <input type="submit" class="inputTypeSubmit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test .htaccess Again"}"/>
  {/if}
</div>

{if isset($AdminRewrite.embeddedCode)}
<div class="gbBlock">
  <h3> {g->text text="Testing Embedded Gallery .htaccess file"} </h3>

  {assign var="showTestButton" value=false}
  {if ($AdminRewrite.embeddedCode == REWRITE_STATUS_HTACCESS_READY)}
    <div class="giSuccess">
      {g->text text="Gallery can write to the embedded .htaccess version."}
    </div>
  {/if}

  {if ($AdminRewrite.embeddedCode == REWRITE_STATUS_HTACCESS_CANT_WRITE)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Cannot write to the .htaccess file."}
    </div>
  {/if}

  {if ($AdminRewrite.embeddedCode == REWRITE_STATUS_HTACCESS_MISSING)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="The .htaccess file does not exist."}
    </div>
  {/if}

  {if ($AdminRewrite.embeddedCode == REWRITE_STATUS_HTACCESS_CANT_READ)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Can not read the .htaccess file."}
    </div>
  {/if}

  {if !empty($showTestButton)}
    <br/>
    <input type="submit" class="inputTypeSubmit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test .htaccess Again"}"/>
  {/if}
</div>
{/if}
{/if}
