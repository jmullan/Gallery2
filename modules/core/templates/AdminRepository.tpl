{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Repository"} </h2>
</div>

{if !empty($status.error)}
<div class="gbBlock"><h2 class="giError">
  {$status.error}
  {g->text text="Please make sure that your internet connection is set up properly or try again later."}
</h2></div>
{/if}

{if !empty($status)}
<div class="gbBlock"><h2 class="giSuccess">
  {if isset($status.indexUpdated)}
    {g->text text="The repository index has been successfully updated."}
  {elseif isset($status.noUpgradeAvailable)}
    {g->text text="All plugins are already up-to-date."}
  {/if}
</h2></div>
{/if}

<div class="gbTabBar">
  <span class="o"><span>
    <a href="{g->url arg1="view=core.SiteAdmin" arg2="subView=core.AdminPlugins"}">
      {g->text text="Plugins"}
    </a>
  </span></span>

  <span class="giSelected o"><span>
    {g->text text="Get More Plugins"}
  </span></span>
</div>

<div class="gbBlock">
  <h3>{g->text text="Get More Plugins"}</h3>
  <p class="giDescription">
    {capture name="noPersonalInfoTransmitted"}<b>{g->text text="No personal information about you or your Gallery installation is sent to the Gallery server at any time."}</b>{/capture}
    {g->text text="The Gallery Plugin Repository contains the latest modules and themes provided by the Gallery team.  You can download and install new plugins to try them out, then delete them if you don't like them.  You must periodically download a new plugin list from the Gallery server to find out about any available updates. %s On slower connections the process might take a minute or two." arg1=$smarty.capture.noPersonalInfoTransmitted}
  </p>
</div>

{if !$AdminRepository.writeable.modules || !$AdminRepository.writeable.themes}
<div class="gbBlock">
  <h3>{g->text text="Configure your Gallery"}</h3>
  <p class="giDescription">
    {g->text text="Before you can proceed, you have to change some permissions so that Gallery can install plugins for you.  It's easy.  Just execute the following in a shell or via your ftp client:"}
  </p>
  <p class="gcBackground1" style="border-width: 1px; border-style: dotted; padding: 4px">
    <b>
      cd gallery2<br/>
      {if !$AdminRepository.writeable.modules}chmod 777 modules<br/>{/if}
      {if !$AdminRepository.writeable.themes}chmod 777 themes<br/>{/if}
    </b>
  </p>
  <p class="giDescription">
    {g->text text="If you have trouble changing permissions, ask your system administrator for assistance.  When you've fixed the permissions, click the Continue button to proceed."}
  </p>
</div>
<div class="gbBlock gcBackground1">
  <input class="inputTypeSubmit" type="button" onclick="document.location='{g->url arg1="view=core.SiteAdmin" arg2="subView=core.AdminRepository"}'" value="{g->text text="Continue"}" />
</div>
{else}
<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit" name="{g->formVar var="form[action][update]"}" value="{if isset($AdminRepository.indexMetaData)}{g->text text="Update Plugin List"}{else}{g->text text="Download Plugin List"}{/if}"/>
  {if isset($AdminRepository.indexMetaData)}
  {capture assign="updateDate"}{g->date style="datetime" timestamp=$AdminRepository.indexMetaData.timestamp}{/capture}
  {g->text text="(last updated: %s)" arg1=$updateDate}
  {/if}
</div>

{if isset($AdminRepository.indexMetaData)}
  {if $AdminRepository.coreUpgradeAvailable}
<div class="gbBlock">
  <h3>{g->text text="Upgrade Gallery"}</h3>
  <p class="giDescription">
    {g->text text="A new version of Gallery is available, but it cannot be upgraded through this interface. Upgrading it might make some of your current plugins stop working, but others that rely on the features of the new version may become available. Here are the recommended steps for upgrading:"}
  </p>
  <p>
    <ol>
      <li>{g->text text="Review plugin compatibility (on the Themes and Modules tabs)"}</a></li>
      <li>{g->text text="%sDownload%s Gallery core" arg1="<a href=\"http://codex.gallery2.org/index.php/Download\">" arg2="</a>"}</li>
      <li>{g->text text="Read the %supgrade instructions%s and perform the upgrade" arg1="<a href=\"http://codex.gallery2.org/index.php/CoreUpgradeInstructions\">" arg2="</a>"}</li>
    </ol>
  </p>
</div>
  {/if}
{/if}

<div class="gbBlock">
  {if isset($AdminRepository.browseData)}
  <p class="giDescription">
    {if $AdminRepository.coreUpgradeAvailable}
      {if isset($AdminRepository.showIncompatible)}
        {g->text text="Incompatible plugins are marked with an exclamation icon."}
      {else}
	{capture name="listLink"}<a href="{g->url arg1="view=core.SiteAdmin"
	  arg2="subView=core.AdminRepository"
	  arg3="coreApi=`$AdminRepository.latestCoreApiVersion`" arg4="themeApi=`$AdminRepository.latestThemeApiVersion`"
	  arg5="moduleApi=`$AdminRepository.latestModuleApiVersion`" arg6="showIncompatible=true"}">{/capture}
	{g->text text="A new core module version is available. There may be plugins that are incompatible with the installed core module, which are not shown here. You can view a %scomplete list%s of plugins, including incompatible ones, which are marked with a red icon." arg1=$smarty.capture.listLink arg2="</a>"}
      {/if}
    {/if}
  </p>
  <table class="gbDataTable">
    {assign var="group" value=""}
    {foreach from=$AdminRepository.browseData key=pluginId item=plugin}
      {if $group != $plugin.groupLabel}
	{if !empty($group)}
	  <tr><td> &nbsp; </td></tr>
	{/if}
	<tr>
	  <th colspan="6"><h2>{$plugin.groupLabel}</h2></th>
	</tr><tr>
	  <th> &nbsp; </th>
    {if $plugin.type == 'themes'}
	  <th> {g->text text="Theme Name"} </th>
    {else}
	  <th> {g->text text="Module Name"} </th>
    {/if}
	  <th> {g->text text="Latest"} </th>
	  <th> {g->text text="Installed"} </th>
	  <th> {g->text text="Description"} </th>
	  <th> {g->text text="Actions"} </th>
	</tr>
      {/if}
      {assign var="group" value=$plugin.groupLabel}

      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {if !$plugin.isCompatible}
	  <img src="{g->url href="modules/core/data/module-incompatible.gif"}" width="13"
	       height="13" alt="{g->text text="Incompatible Plugin"}" />
	  {/if}
	</td>

	<td>
	  {$plugin.name}
	</td>

	<td align="center">
	  {$plugin.repositoryVersion}
	</td>

	<td align="center">
	  {$plugin.localVersion}
	</td>

	<td>
	  {$plugin.description}
	  {if !$plugin.isCompatible}
	    <br/>
	    <span class="giError">
	      {g->text text="Incompatible plugin!"}
	      {if $plugin.api.required.core != $plugin.api.provided.core}
		<br/>
		{g->text text="Core API Required: %s (available: %s)"
			 arg1=$plugin.api.required.core arg2=$plugin.api.provided.core}
	      {/if}
	      {if $plugin.api.required.plugin != $plugin.api.provided.plugin}
		<br/>
		{g->text text="Plugin API Required: %s (available: %s)"
			 arg1=$plugin.api.required.plugin arg2=$plugin.api.provided.plugin}
	      {/if}
	    </span>
	  {/if}
	</td>

	<td>
	  {if !empty($plugin.action) && $plugin.isCompatible}
	    {strip}
	      <a href="{g->url arg1="view=core.SiteAdmin" arg2="subView=core.AdminRepositoryDownload" arg3="pluginType=`$plugin.type`" arg4="pluginId=`$pluginId`"}">
		{$plugin.action}
	      </a>
	    {/strip}
	  {else}
	    &nbsp;
	  {/if}
	</td>
      </tr>
    {/foreach}
  </table>
  {/if}
</div>

{if isset($AdminRepository.indexMetaData)}
<div class="gbBlock">
  <h3>{g->text text="Upgrade All Plugins"}</h3>
  <p class="giDescription">
    {g->text text="Gallery can automatically upgrade your themes and modules to the latest available versions. No new plugins will be downloaded."}
  </p>
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit" name="{g->formVar var="form[action][upgradeAll]"}" value="{g->text text="Upgrade All"}"/>
</div>
{/if}
{/if} {* modules/themes are writeable *}
