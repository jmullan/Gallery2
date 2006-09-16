{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Download %s" arg1=$AdminRepositoryDownload.pluginName} </h2>
</div>

{if isset($form.packages.empty)}
<div class="giError">
  {g->text text="No packages have been selected."}
</div>
{/if}

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="Download the latest base package in order to use this plugin.  Language packages are optional.  You only need to download the ones that you want to use on your site."}
  </p>
  <p>
    <h3> {g->text text="Base package"} </h3>
    {assign var="base" value=$AdminRepositoryDownload.upgradeData.base}
    {if $base.relation == "older"}
      {if empty($base.currentVersion)}
        <input type="hidden" name="{g->formVar var="form[downloadBaseFiles]"}" value="true" />
        <input type="checkbox" checked="checked" disabled="true" />
        {g->text text="%s (version %s)" arg1="<b>`$AdminRepositoryDownload.pluginName`</b>" arg2=$base.newVersion}
      {else}
        <input type="checkbox" name="{g->formVar var="form[upgradeBaseFiles]"}" value="true" checked="checked" />
        {g->text text="%s (version: %s, currently installed: %s)" arg1="<b>`$AdminRepositoryDownload.pluginName`</b>" arg2=$base.newVersion arg3=$base.currentVersion}
      {/if}
    {else}
      <input type="hidden" name="{g->formVar var="form[downloadBaseFiles]"}" value="true" />
      <input type="checkbox" value="false" checked="checked" disabled="true" />
      {g->text text="%s (currently installed version %s is up to date)" arg1="<b>`$AdminRepositoryDownload.pluginName`</b>" arg2=$base.currentVersion}
    {/if}
    <br />
  </p>
  <p>
    {literal}
    <script type="text/javascript">
      // <![CDATA[
      function getLangpackCheckboxes(className) {
	var result = []
        var inputs = document.getElementsByTagName("input");
	for (var i in inputs) {
	  if (inputs[i].className == className) {
	    result.push(inputs[i]);
	  }
        }
        return result;
      }

      function selectAll() {
        var checkboxes = getLangpackCheckboxes("downloadable_langpack");
        for (var i in checkboxes) {
	  checkboxes[i].checked = "checked";
	}
	document.getElementById("selectAllLink").style.display = "none";
	document.getElementById("selectNoneLink").style.display = "inline";
      }

      function selectNone() {
        var checkboxes = getLangpackCheckboxes("downloadable_langpack");
        for (var i in checkboxes) {
	  checkboxes[i].checked = null;
	}
	document.getElementById("selectAllLink").style.display = "inline";
	document.getElementById("selectNoneLink").style.display = "none";
      }

      function hideUpToDate() {
        var checkboxes = getLangpackCheckboxes("uptodate_langpack");
        for (var i in checkboxes) {
	  checkboxes[i].parentNode.style.display = "none";
	}
	document.getElementById("showUpToDateLink").style.display = "inline";
	document.getElementById("hideUpToDateLink").style.display = "none";
	var el = document.getElementById("noDownloadableLangpacks");
	if (el) {
	  el.style.display = "block";
	}
      }

      function showUpToDate() {
        var checkboxes = getLangpackCheckboxes("uptodate_langpack");
        for (var i in checkboxes) {
	  checkboxes[i].parentNode.style.display = "block";
	}
	document.getElementById("showUpToDateLink").style.display = "none";
	document.getElementById("hideUpToDateLink").style.display = "inline";
	var el = document.getElementById("noDownloadableLangpacks");
	if (el) {
	  el.style.display = "hidden";
	}
      }
      // ]]>
    </script>
    {/literal}

    <h3> {g->text text="Language packages"}
    {g->text text="(select: %sall%s %snone%s | up to date packages: %shide%s %sshow%s)"
      arg1="<a id=\"selectAllLink\" href=\"javascript:selectAll()\">"
      arg2="</a>"
      arg3="<a style=\"display: none\" id=\"selectNoneLink\" href=\"javascript:selectNone()\">"
      arg4="</a>"
      arg5="<a style=\"display: none\" id=\"hideUpToDateLink\" href=\"javascript:hideUpToDate()\">"
      arg6="</a>"
      arg7="<a id=\"showUpToDateLink\" href=\"javascript:showUpToDate()\">"
      arg8="</a>"}
    <br/>
    </h3>

    {foreach from=$AdminRepositoryDownload.upgradeData.languages key=code item=pack}
    <div  {if $pack.relation != "older"}style="display: none"{/if}>
      {if $pack.relation == "older"}
	<input id="checkbox_{$code}" class="downloadable_langpack" type="checkbox" name="{g->formVar var="form[languages][]"}" value="{$code}" />
        <label for="checkbox_{$code}">
	{if $pack.currentVersion}
	  {g->text text="%s (version: %s, currently installed: %s)"
	      arg1="<b>`$pack.name`</b>" arg2=$pack.newVersion arg3=$pack.currentVersion}
	{else}
  	  {g->text text="%s (version: %s)" arg1="<b>`$pack.name`</b>" arg2=$pack.newVersion}
	{/if}
        </label>
	{assign var="atLeastOnePack" value=true}
      {else}
	<input class="uptodate_langpack" type="checkbox" name="{g->formVar var="form[languages][]"}" value="{$code}" disabled="true" />
	{g->text text="%s (version %s is up to date)" arg1="<b>`$pack.name`</b>" arg2=$pack.newVersion}
      {/if}
      <br />
    </div>
    {/foreach}

    {if empty($atLeastOnePack)}
    <div id="noDownloadableLangpacks">
      <p>
        <i>{g->text text="There are no language packs available for download."}</i>
      </p>
    </div>
    {/if}
  </p>
</div>

<div class="gbBlock gcBackground1">
  <input class="inputTypeSubmit" type="submit" name="{g->formVar var="form[action][download]"}" value="{g->text text="Download"}"/>
  <input class="inputTypeSubmit" type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
  <input type="hidden" name="{g->formVar var="form[pluginType]"}" value="{$AdminRepositoryDownload.pluginType}" />
  <input type="hidden" name="{g->formVar var="form[pluginId]"}" value="{$AdminRepositoryDownload.pluginId}" />
</div>
