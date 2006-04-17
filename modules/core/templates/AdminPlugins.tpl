{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<script type="text/javascript" src="{g->url href="lib/prototype/prototype.js"}"></script>
<script type="text/javascript">
  //<![CDATA[
  var pluginNames = {ldelim} "module" : {ldelim} {rdelim}, "theme" : {ldelim} {rdelim} {rdelim}
  {foreach name=names from=$AdminPlugins.plugins item=plugin}
  pluginNames["{$plugin.type}"]["{$plugin.id}"] = "{$plugin.name}";
  {/foreach}

  var stateData = {ldelim}
    "inactive" : {ldelim}
      "img.src" : "{g->url href="modules/core/data/module-inactive.gif"}",
      "img.alt" : "{g->text text="Status: Inactive"}",
      "actions" : {ldelim} "activate": 1, "uninstall" : 1 {rdelim},
      "message" : {ldelim} "type" : "giSuccess", "text" : "{g->text text="__PLUGIN__ deactivated"}" {rdelim}
    {rdelim},
    "active" : {ldelim}
      "img.src" : "{g->url href="modules/core/data/module-active.gif"}",
      "img.alt" : "{g->text text="Status: Active"}",
      "actions" : {ldelim} "deactivate": 1, "uninstall" : 1  {rdelim},
      "message" : {ldelim} "type" : "giSuccess", "text" : "{g->text text="__PLUGIN__ activated"}" {rdelim}
    {rdelim},
    "uninstalled" : {ldelim}
      "img.src" : "{g->url href="modules/core/data/module-install.gif"}",
      "img.alt" : "{g->text text="Status: Not Installed"}",
      "actions" : {ldelim} "install": 1 {rdelim},
      "message" : {ldelim} "type" : "giSuccess", "text" : "{g->text text="__PLUGIN__ uninstalled"}" {rdelim}
    {rdelim},
    "unupgraded" : {ldelim}
      "img.src" : "{g->url href="modules/core/data/module-upgrade.gif"}",
      "img.alt" : "{g->text text="Status: Upgrade Required (Inactive)"}",
      "actions" : {ldelim} "upgrade": 1 {rdelim}
    {rdelim},
    "incompatible" : {ldelim}
      "img.src" : "{g->url href="modules/core/data/module-incompatible.gif"}",
      "img.alt" : "{g->text text="Status: Incompatible Plugin (Inactive)"}",
      "actions" : {ldelim} {rdelim}
    {rdelim},
    "unconfigured" : {ldelim}
      "img.src" : "{g->url href="modules/core/data/module-inactive.gif"}",
      "img.alt" : "{g->text text="Status: Inactive (Configuration Required)"}",
      "actions" : {ldelim} "configure" : 1, "uninstall" : 1 {rdelim},
      "message" : {ldelim} "type" : "giWarning", "text" : "{g->text text="__PLUGIN__ needs configuration"}" {rdelim}
    {rdelim}
  {rdelim};
  var errorPageUrl = '{g->url arg1="view=core.ErrorPage" htmlEntities=0}';

{literal}
  var contexts = {"module": {}, "theme": {}};
  var allActions = ["install", "configure", "upgrade", "activate", "deactivate", "uninstall"];
  function updatePluginState(pluginType, pluginId, state, noAlertMessage) {
    var pluginKey = pluginType + "-" + pluginId;
    icon = $("plugin-icon-" + pluginKey);
    icon.src = stateData[state]['img.src'];
    icon.alt = stateData[state]['img.alt'];
    for (var i in allActions) {
      var node = $("action-" + allActions[i] + "-" + pluginKey);
      if (node) {
	node.style.display = stateData[state]['actions'][allActions[i]] ? 'inline' : 'none';
      }
    }

    var re = new RegExp().compile('gbLink-' + pluginId + '_');
    var links = document.getElementsByTagName("li");
    for (i in links) {
      if (re.test(links[i].className)) {
        links[i].style.display = (state == 'active') ? 'block' : 'none';
      }
    }

    if (!noAlertMessage && stateData[state]['message']) {
      addMessage(pluginType, pluginId, stateData[state]['message']['text'], stateData[state]['message']['type']);
    }
  }

  function setPluginBusyStatus(pluginType, pluginId, makeBusy) {
    var pluginKey = pluginType + "-" + pluginId;
    var row = $("plugin-row-" + pluginKey);
    if (makeBusy) {
      row.className = row.className + " gbBusy";
    } else {
      row.className = row.className.replace(" gbBusy", "");
    }
  }

  function performPluginAction(pluginType, pluginId, url) {
    if (contexts[pluginId]) {
      return;
    }

    contexts[pluginType][pluginId] = Array();

    var callback = function(response) {
      if (response.readyState != 4) {
	return;
      }

      eval("var result = " + response.responseText)
      if (result['status'] == 'success') {
	for (var stateChangePluginType in result['states']) {
          for (var stateChangePluginId in result['states'][stateChangePluginType]) {
            updatePluginState(stateChangePluginType, stateChangePluginId,
	                      result['states'][stateChangePluginType][stateChangePluginId], false);
	  }
        }
      } else if (result['status'] == 'redirect') {
	document.location.href = result['redirect'];
      } else if (result['status'] == 'error') {
	document.location.href = errorPageUrl;
      }

      setPluginBusyStatus(pluginType, pluginId, false);
      delete(contexts[pluginType][pluginId]);
    }

    url += '&rnd=' + Math.random();
    new Ajax.Request(url, {method: 'get', parameters: '', onComplete: callback});
    setPluginBusyStatus(pluginType, pluginId, true);

    return false;
  }

  var STATUS_BOX_ID = "gbPluginStatusUpdates";
  addMessage = function(pluginType, pluginId, messageText, messageType) {
    var pluginStatus = document.createElement("div");
    var detailsId = "plugin-status-details-" + pluginType + "-" + pluginId;
    if ($(detailsId)) {
      $(STATUS_BOX_ID).removeChild($(detailsId));
    }

    pluginStatus.className = messageType;
    pluginStatus.id = detailsId;
    pluginStatus.style.whiteSpace = "nowrap";
    var text = messageText.replace('__PLUGIN__', pluginNames[pluginType][pluginId]);

    pluginStatus.appendChild(document.createTextNode(text));

    var containerEl = $(STATUS_BOX_ID);
    containerEl.appendChild(pluginStatus);
    containerEl.style.display = "block";

    var statusDimensions = Element.getDimensions(containerEl);
    var bodyDimensions = Element.getDimensions(document.body);
    containerEl.style.left = ((bodyDimensions.width - statusDimensions.width) / 2) + "px";

    updateStatusPosition();
    setTimeout("removeMessage('" + pluginStatus.id + "')", 3000);
  }

  removeMessage = function(pluginStatusId) {
    var containerEl = $(STATUS_BOX_ID);
    var statusMessage = $(pluginStatusId);
    if (statusMessage != null) {
      containerEl.removeChild(statusMessage);
    }

    if (containerEl.childNodes.length == 0) {
      containerEl.style.display = "none";
    }
  }

  updateStatusPosition = function() {
    var containerEl = $(STATUS_BOX_ID);
    containerEl.style.top = document.getElementsByTagName("html")[0].scrollTop + "px";
  }

  Event.observe(window, "scroll", updateStatusPosition, false);
  //]]>
</script>
{/literal}

<div id="gbPluginStatusUpdates"></div>

<div class="gbBlock gcBackground1">
  <h2> {g->text text="Gallery Plugins"} </h2>
</div>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="Gallery features come as separate plugins.  You can download and install plugins to add more features to your Gallery, or you can disable features if you don't want to use them.  In order to use a feature, you must install, configure (if necessary) and activate it.  If you don't wish to use a feature, you can deactivate it."}
  </p>

  {capture name=legend}
  <div style="width: 100%; text-align: right">
    <img src="{g->url href="modules/core/data/module-active.gif"}" width="13" height="13" alt="" />
    <span style="margin-right: 10px; vertical-align: top">
      {g->text text="up to date"}
    </span>

    <img src="{g->url href="modules/core/data/module-inactive.gif"}" width="13" height="13" alt="" />
    <span style="margin-right: 10px; vertical-align: top">
      {g->text text="disabled"}
    </span>

    <img src="{g->url href="modules/core/data/module-upgrade.gif"}" width="13" height="13" alt="" />
    <span style="margin-right: 10px; vertical-align: top">
      {g->text text="upgrade required"}
    </span>

    <img src="{g->url href="modules/core/data/module-install.gif"}" width="13" height="13" alt="" />
    <span style="margin-right: 10px; vertical-align: top">
      {g->text text="not installed"}
    </span>

    <img src="{g->url href="modules/core/data/module-incompatible.gif"}" width="13" height="13" alt="" />
    <span style="margin-right: 10px; vertical-align: top">
      {g->text text="incompatible"}
    </span>
  </div>
  {/capture}
  {$smarty.capture.legend}

  <table class="gbDataTable">
    {assign var="group" value=""}
    {foreach from=$AdminPlugins.plugins item=plugin}
      {if $group != $plugin.group}
	{if !empty($group)}
	  <tr><td> &nbsp; </td></tr>
	{/if}
	<tr>
	  <th colspan="6"><h2>{$plugin.groupLabel}</h2></th>
	</tr><tr>
	  <th> &nbsp; </th>
	  <th> {g->text text="Plugin Name"} </th>
	  <th> {g->text text="Version"} </th>
	  <th> {g->text text="Installed"} </th>
	  <th> {g->text text="Description"} </th>
	  <th> {g->text text="Actions"} </th>
	</tr>
      {/if}
      {assign var="group" value=$plugin.group}

      <tr id="plugin-row-{$plugin.type}-{$plugin.id}" class="{cycle values="gbEven,gbOdd"}">
	<td style="display: relative;">
	  <img id="plugin-icon-{$plugin.type}-{$plugin.id}" src="" width="13" height="13" alt="" />
	</td>

	<td>
	  {$plugin.name}
	</td>

	<td align="center">
	  {$plugin.version}
	</td>

	<td align="center">
	  {$plugin.installedVersion}
	</td>

	<td>
	  {$plugin.description}
	  {if $plugin.state == 'incompatible'}
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

	<td style="width: 150px">
          {if ($plugin.type == 'module' && $plugin.id == 'core') || $plugin.state == 'incompatible' || ($plugin.type == 'theme' && $plugin.id == $AdminPlugins.defaultTheme)}
	    &nbsp;
	  {else}
            <span id="action-install-{$plugin.type}-{$plugin.id}">
              <a style="cursor: pointer" onclick="performPluginAction('{$plugin.type}', '{$plugin.id}', '{g->url arg1="view=core.PluginCallback" arg2="pluginId=`$plugin.id`" arg3="pluginType=`$plugin.type`" arg4="command=install"}')">
                {g->text text="install"}
              </a>
            </span>
            <span id="action-upgrade-{$plugin.type}-{$plugin.id}">
              <a style="cursor: pointer" onclick="performPluginAction('{$plugin.type}', '{$plugin.id}', '{g->url arg1="view=core.PluginCallback" arg2="pluginId=`$plugin.id`" arg3="pluginType=`$plugin.type`" arg4="command=upgrade"}')">
                {g->text text="upgrade"}
              </a>
            </span>
            <span id="action-configure-{$plugin.type}-{$plugin.id}">
              <a style="cursor: pointer" onclick="performPluginAction('{$plugin.type}', '{$plugin.id}', '{g->url arg1="view=core.PluginCallback" arg2="pluginId=`$plugin.id`" arg3="pluginType=`$plugin.type`" arg4="command=configure"}')">
                {g->text text="configure"}
              </a> |
            </span>
            <span id="action-activate-{$plugin.type}-{$plugin.id}">
              <a style="cursor: pointer" onclick="performPluginAction('{$plugin.type}', '{$plugin.id}', '{g->url arg1="view=core.PluginCallback" arg2="pluginId=`$plugin.id`" arg3="pluginType=`$plugin.type`" arg4="command=activate"}')">
                {g->text text="activate"}
              </a> |
            </span>
            <span id="action-deactivate-{$plugin.type}-{$plugin.id}">
              <a style="cursor: pointer" onclick="performPluginAction('{$plugin.type}', '{$plugin.id}', '{g->url arg1="view=core.PluginCallback" arg2="pluginId=`$plugin.id`" arg3="pluginType=`$plugin.type`" arg4="command=deactivate"}')">
                {g->text text="deactivate"}
              </a> |
            </span>
            <span id="action-uninstall-{$plugin.type}-{$plugin.id}">
              <a style="cursor: pointer" onclick="performPluginAction('{$plugin.type}', '{$plugin.id}', '{g->url arg1="view=core.PluginCallback" arg2="pluginId=`$plugin.id`" arg3="pluginType=`$plugin.type`" arg4="command=uninstall"}')">
                {g->text text="uninstall"}
              </a>
            </span>
	  {/if}
          <script type="text/javascript"> updatePluginState('{$plugin.type}', '{$plugin.id}', '{$plugin.state}', true); </script>
	</td>
      </tr>
    {/foreach}
  </table>
  {$smarty.capture.legend}
</div>
