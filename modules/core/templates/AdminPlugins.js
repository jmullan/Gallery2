function updatePluginState(pluginType, pluginId, state, visualChanges) {
    var pluginKey = pluginType + "-" + pluginId;
    icon = document.getElementById("plugin-icon-" + pluginKey);
    icon.src = stateData[state]['img.src'];
    icon.alt = stateData[state]['img.alt'];
    for (var i in allActions) {
	var node = document.getElementById("action-" + allActions[i] + "-" + pluginKey);
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

    if (visualChanges && stateData[state]['message']) {
	addMessage(pluginType, pluginId, stateData[state]['message']['text'], stateData[state]['message']['type']);

	if (stateData[state]['callback']) {
	    callback = stateData[state]['callback'] + '("' + pluginType + '", "' + pluginId + '")';
	    eval(callback);
	}
    }
}

function copyVersionToInstalledVersion(pluginType, pluginId) {
    versionEl = document.getElementById("plugin-" + pluginType + "-" + pluginId + "-version");
    installedVersionEl = document.getElementById("plugin-" + pluginType + "-" + pluginId + "-installedVersion");
    installedVersionEl.innerHTML = versionEl.innerHTML;
}

function eraseInstalledVersion(pluginType, pluginId) {
    installedVersionEl = document.getElementById("plugin-" + pluginType + "-" + pluginId + "-installedVersion");
    installedVersionEl.innerHTML = '';
}

function setPluginBusyStatus(pluginType, pluginId, makeBusy) {
    var pluginKey = pluginType + "-" + pluginId;
    var row = document.getElementById("plugin-row-" + pluginKey);
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

    var handleSuccess = function(response) {
	eval("var result = " + response.responseText)
	if (result['status'] == 'success') {
	    for (var stateChangePluginType in result['states']) {
		for (var stateChangePluginId in result['states'][stateChangePluginType]) {
		    updatePluginState(stateChangePluginType, stateChangePluginId,
				      result['states'][stateChangePluginType][stateChangePluginId], true);
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

    var handleFailure = function(response) {
	// Ignore for now
    }

    var callback = {
	success: handleSuccess,
	failure: handleFailure,
	scope: this
    }

    url += '&rnd=' + Math.random();
    YAHOO.util.Connect.asyncRequest('GET', url, callback);
    setPluginBusyStatus(pluginType, pluginId, true);

    return false;
}

var STATUS_BOX_ID = "gbPluginStatusUpdates";
function addMessage(pluginType, pluginId, messageText, messageType) {
    var pluginStatus = document.createElement("div");
    var detailsId = "plugin-status-details-" + pluginType + "-" + pluginId;
    if (document.getElementById(detailsId)) {
	document.getElementById(STATUS_BOX_ID).removeChild(document.getElementById(detailsId));
    }

    pluginStatus.className = messageType;
    pluginStatus.id = detailsId;
    pluginStatus.style.whiteSpace = "nowrap";
    var text = messageText.replace('__PLUGIN__', pluginNames[pluginType][pluginId]);

    pluginStatus.appendChild(document.createTextNode(text));

    var containerEl = document.getElementById(STATUS_BOX_ID);
    containerEl.appendChild(pluginStatus);
    containerEl.style.display = "block";

    var statusDimensions = YAHOO.util.Dom.getRegion(containerEl);
    var bodyDimensions = YAHOO.util.Dom.getRegion(document.body);
    containerEl.style.left = (((bodyDimensions.right - bodyDimensions.left) -
	                       (statusDimensions.right - statusDimensions.left)) / 2) + "px";

    updateStatusPosition();
    setTimeout("removeMessage('" + pluginStatus.id + "')", 3000);
}

function removeMessage(pluginStatusId) {
    var containerEl = document.getElementById(STATUS_BOX_ID);
    var statusMessage = document.getElementById(pluginStatusId);
    if (statusMessage != null) {
	containerEl.removeChild(statusMessage);
    }

    if (containerEl.childNodes.length == 0) {
	containerEl.style.display = "none";
    }
}

function updateStatusPosition() {
    var containerEl = document.getElementById(STATUS_BOX_ID);
    containerEl.style.top = document.getElementsByTagName("html")[0].scrollTop + "px";
}
