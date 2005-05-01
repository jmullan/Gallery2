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
    {g->text text="Successfully saved Embedded Setup"}
  {/if}
</div>
{/if}

{if !empty($form.error)}
<div class="gbBlock">
  <h2> {g->text text="An error occured while trying to save your settings:"} </h3>
  
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
  <tr><th colspan="5"><h2>{$module.name}</h2></th></tr>
  <tr>
    <th> &nbsp; </th>
    <th> {g->text text="Help"} </th>
    <th> {g->text text="View"} </th>
    <th> {g->text text="URL Pattern"} </th>
    <th> {g->text text="Additional Keywords"} </th>
  </tr>
    
  {foreach from=$form.shortUrls.$moduleId item=rule key=index}
  {cycle values="gbEven,gbOdd" assign="rowClass"}
  <tr class="{$rowClass}">
    <td>
      <input type="checkbox" name="{g->formVar var="form[shortUrls][$moduleId][$index][active]"}" {if isset($rule.active)}checked{/if}/>
      {if isset($rule.match)}
        <input type="hidden" name="{g->formVar var="form[shortUrls][$moduleId][$index][match]}" value="{$rule.match}">
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
        <input type="hidden" name="{g->formVar var="form[shortUrls][$moduleId][$index][pattern]"}" value="{$rule.pattern}">
      {else}
        <input type="text" size="40" name="{g->formVar var="form[shortUrls][$moduleId][$index][pattern]"}" value="{$rule.pattern}"/>
      {/if}
    </td>
    <td>
      {foreach from=$AdminRewrite.shortUrls.$moduleId.rules.$index.keywords key=keyword item=prefs}
        %{$keyword}%
      {/foreach}
    </td>
  </tr>
  <tr class="{$rowClass}" style="display: none;" id="shortUrls-{$moduleId}-{$index}-help">
    <td>
      &nbsp;
    </td>
    <td colspan="4">
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
  {if $AdminRewrite.isEmbedded}
  <h3> {g->text text="Embedded Setup"} </h3>
  
  <p class="giDescription">
    {g->text text="For URL Rewrite to work in an embedded environment you need to set up an extra htaccess file to hold the mod_rewrite rules."}
  </p>
  
  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Htaccess path:"}
    </td><td>
      <input type="text" size="60" name="{g->formVar var="form[embedded][htaccessPath]"}" value="{$form.embedded.htaccessPath}">
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
      {$AdminRewrite.host}<input type="text" size="40" name="{g->formVar var="form[embedded][publicPath]"}" value="{$form.embedded.publicPath}">
      {if isset($form.error.invalidPath)}
        <div class="giError">
          {g->text text="Invalid path."}
        </div>
      {/if}
    </td>
  </tr></table>

  {else}
  <p class="giDescription">
    {g->text text="No configuration needed."}
  </p>
  {/if}
</div>

{if $AdminRewrite.isEmbedded}
<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit" name="{g->formVar var="form[action][saveSetup]"}" value="{g->text text="Save"}"/>
</div>
{/if}
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