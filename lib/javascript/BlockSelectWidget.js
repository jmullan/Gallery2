/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2005 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
/*
 * Author: Ariel Garza (primary development)
 * Author: Bharat Mediratta (minor adjustments for namespacing, bugfixes)
 */
var bsw_WIDGET_BLOCKS = new Array();
var bsw_FORM_TARGETS = new Array();
var bsw_HEADER_TEXT = new Array();
var bsw_UPDATE_LEVEL = 0;

function bsw_Block(key, id, description) {
    if (!bsw_WIDGET_BLOCKS[key]) {
	bsw_WIDGET_BLOCKS[key] = new Array();
    }
    bsw_WIDGET_BLOCKS[key][id] = this;

    this.key = key;
    this.id = id;
    this.description = description;
    this.parameters = new Array();

    this.addVariable = function(varName, varDefaultValue, varDescription, varType, varExtra) {
	this.parameters[varName] = new Array();
	this.parameters[varName]['description'] = varDescription;
	this.parameters[varName]['defaultValue'] = varDefaultValue;
	this.parameters[varName]['type'] = varType;
	this.parameters[varName]['extra'] = varExtra;
    };
}

/**
 * Add a definition for a block that is available for user selection.
 * @param id The id of the block.
 * @param description A short description of the block.
 */
function bsw_addAvailableBlock(key, id, description) {
    var availableEl = document.getElementById("blocksAvailableList_" + key);
    var block = new bsw_Block(key, id, description);

    var blockOptionEl = document.createElement("option");
    blockOptionEl.appendChild(document.createTextNode(block.description));
    blockOptionEl.value = block.id;
    availableEl.appendChild(blockOptionEl);

    return block;
}

var bsw_PREF_ID = 1;
var bsw_USER_BLOCKS = new Array();
var bsw_USER_BLOCK_POSITIONS = new Array();
function bsw_BlockPreference(key, blockId, values) {
    this.id = bsw_PREF_ID++;

    if (!bsw_USER_BLOCKS[key]) {
	bsw_USER_BLOCKS[key] = new Array();
    }
    if (!bsw_USER_BLOCK_POSITIONS[key]) {
	bsw_USER_BLOCK_POSITIONS[key] = new Array();
    }
    bsw_USER_BLOCKS[key][this.id] = this;
    bsw_USER_BLOCK_POSITIONS[key].push(this.id);

    this.blockKey = key;
    this.blockId = blockId;
    this.parameters = new Array();

    this.setParameterValue = function(paramName, value) {
	this.parameters[paramName] = value;
    };

    this.toString = function() {
	var result = "[" + this.blockId;
	for (var paramName in this.parameters) {
	    var paramValue = this.parameters[paramName];
	    var defaultValue =
		bsw_WIDGET_BLOCKS[key][blockId]['parameters'][paramName]['defaultValue'];
	    if (paramValue != defaultValue) {
		result += " " + paramName + "=" + paramValue;
	    }
	}

	result += "]";

	return result;
    };

    /* Set the defaults */
    for (var value in bsw_WIDGET_BLOCKS[key][blockId]['parameters']) {
	this.setParameterValue(value,
			       bsw_WIDGET_BLOCKS[key][blockId]['parameters'][value]['defaultValue']);
    }

    /* Override whatever we're specifically changing */
    for (var value in values) {
	this.setParameterValue(value, values[value]);
    }
}

/**
 * Add a block to the list of blocks that are used by the album.
 * @param blockId The id of the block.  This must match a previously defined block id.
 * @param values The values that are assigned for the block.
 */
function bsw_addUserBlockPreference(key, blockId, values) {
    var usedEl = document.getElementById("blocksUsedList_" + key);
    var blockPref = new bsw_BlockPreference(key, blockId, values);

    var block = bsw_WIDGET_BLOCKS[key][blockPref.blockId];

    if (block != undefined) {
	var blockOptionEl = document.createElement("option");
	blockOptionEl.appendChild(document.createTextNode(block.description));
	blockOptionEl.value = blockPref.id;

	usedEl.appendChild(blockOptionEl);
    } else {
	// debug
	// alert('undefined block type: ' + blockId);
    }
}

function bsw_initAdminForm(key, parameterText, valueText) {
    var availableEl = document.getElementById("blocksAvailableList_" + key);
    var usedEl = document.getElementById("blocksUsedList_" + key);
    var usedBlockString = document.getElementById("albumBlockValue_" + key).value;
    bsw_createBlockPrefsFromString(key, usedBlockString);
    bsw_resizeBlocksUsedList(key);
    bsw_selectNone(key);

    bsw_HEADER_TEXT[key] = new Array();
    bsw_HEADER_TEXT[key]['parameter'] = parameterText;
    bsw_HEADER_TEXT[key]['value'] = valueText;
}

function bsw_reInitAdminForm(key) {
    /*
     * Don't reinitialize if we're already inside an update.  This can happen
     * if the albumBlockValue element calls us in its onchange() handler
     */
    if (bsw_UPDATE_LEVEL == 0) {
	var usedBlockString = document.getElementById("albumBlockValue_" + key).value;
	bsw_USER_BLOCK_POSITIONS[key] = new Array();
	bsw_createBlockPrefsFromString(key, usedBlockString);
	bsw_selectNone(key);
    }
}

/**
 * Set all selected indexes to -1 and disable all buttons
 */
function bsw_selectNone(key) {
    document.getElementById("blocksAvailableList_" + key).selectedIndex = 0;
    document.getElementById("blocksUsedList_" + key).selectedIndex = -1;

    document.getElementById("bsw_AddButton_" + key).className = "bsw_ButtonDisabled";
    document.getElementById("bsw_RemoveButton_" + key).className = "bsw_ButtonDisabled";
    document.getElementById("bsw_MoveUpButton_" + key).className = "bsw_ButtonDisabled";
    document.getElementById("bsw_MoveDownButton_" + key).className = "bsw_ButtonDisabled";
}

/**
 * Once a selection has been made in the list of available blocks, the button to
 * add it to the list of used blocks should be enabled and all other buttons should
 * be disabled.
 */
function bsw_selectToUse(key) {
    if (document.getElementById("blocksAvailableList_" + key).selectedIndex <= 0) {
	document.getElementById("bsw_AddButton_" + key).className = "bsw_ButtonDisabled";
	return;
    }

    document.getElementById("bsw_AddButton_" + key).className = "bsw_ButtonEnabled";
    document.getElementById("bsw_RemoveButton_" + key).className = "bsw_ButtonDisabled";
    document.getElementById("bsw_MoveUpButton_" + key).className = "bsw_ButtonDisabled";
    document.getElementById("bsw_MoveDownButton_" + key).className = "bsw_ButtonDisabled";

    document.getElementById("blocksUsedList_" + key).selectedIndex = -1;
}

/**
 * Once a selection has been made in the list of used blocks, the applicable buttons should be
 * enabled and all other buttons should be disabled.
 */
function bsw_selectToChange(key) {
    document.getElementById("bsw_AddButton_" + key).className = "bsw_ButtonDisabled";
    document.getElementById("bsw_RemoveButton_" + key).className = "bsw_ButtonEnabled";

    var usedEl = document.getElementById("blocksUsedList_" + key);
    if (usedEl.selectedIndex > 0) {
	document.getElementById("bsw_MoveUpButton_" + key).className = "bsw_ButtonEnabled";
    } else {
	document.getElementById("bsw_MoveUpButton_" + key).className = "bsw_ButtonDisabled";
    }

    if (usedEl.selectedIndex < usedEl.options.length - 1) {
	document.getElementById("bsw_MoveDownButton_" + key).className = "bsw_ButtonEnabled";
    } else {
	document.getElementById("bsw_MoveDownButton_" + key).className = "bsw_ButtonDisabled";
    }

    document.getElementById("blocksAvailableList_" + key).selectedIndex = 0;

    bsw_showBlockOptions(key);
}

/**
 * Move a block from the available list to the used list.
 */
function bsw_addBlock(key) {
   var availableEl = document.getElementById("blocksAvailableList_" + key);
   var block = bsw_WIDGET_BLOCKS[key][availableEl.options[availableEl.selectedIndex].value];

   bsw_addUserBlockPreference(key, block.id, new Array());
   bsw_updateAlbumBlockValue(key);
   bsw_selectNone(key);
   bsw_resizeBlocksUsedList(key);
}

/**
 * Move a block from the used list back to the availabe list.
 */
function bsw_removeBlock(key) {
    var usedEl = document.getElementById("blocksUsedList_" + key);
    var optionEl = usedEl.options[usedEl.selectedIndex];

    bsw_USER_BLOCKS[key][optionEl.value] == null;
    bsw_USER_BLOCK_POSITIONS[key].splice(usedEl.selectedIndex, 1);
    usedEl.removeChild(optionEl);
    bsw_showBlockOptions(key);
    bsw_updateAlbumBlockValue(key);
    bsw_resizeBlocksUsedList(key);
}

function bsw_resizeBlocksUsedList(key) {
   var usedEl = document.getElementById("blocksUsedList_" + key);
   if (bsw_USER_BLOCK_POSITIONS[key]) {
       usedEl.size = Math.max(bsw_USER_BLOCK_POSITIONS[key].length, 4);
   } else {
       usedEl.size = 4;
   }
}

/**
 * This function actually moves a block in the used list.
 * @param isUp true if the block preference is being moved up.
 */
function bsw_moveBlock(key, isUp) {
    var usedEl = document.getElementById("blocksUsedList_" + key);
    var index = usedEl.selectedIndex;

    var amount = isUp ? -1 : 1;

    // First swap the preference in our positions array
    var tmpId = bsw_USER_BLOCK_POSITIONS[key][index + amount];
    bsw_USER_BLOCK_POSITIONS[key][index + amount] = bsw_USER_BLOCK_POSITIONS[key][index];
    bsw_USER_BLOCK_POSITIONS[key][index] = tmpId;

    // Now swap the select options
    var tmpVal = usedEl.options[index + amount].value;
    var tmpDesc = usedEl.options[index + amount].innerHTML;

    usedEl.options[index + amount].value = usedEl.options[index].value;
    usedEl.options[index + amount].innerHTML = usedEl.options[index].innerHTML;

    usedEl.options[index].value = tmpVal;
    usedEl.options[index].innerHTML = tmpDesc;

    usedEl.selectedIndex += amount;

    bsw_updateAlbumBlockValue(key);
    bsw_selectToChange(key);
}

/**
 * Move the selected block up.
 */
function bsw_moveUp(key) {
    var usedEl = document.getElementById("blocksUsedList_" + key);
    var index = usedEl.selectedIndex;

    if (index <= 0) {
	return;
    }

    bsw_moveBlock(key, true);
}

/**
 * Move the selected block down.
 */
function bsw_moveDown(key) {
    var usedEl = document.getElementById("blocksUsedList_" + key);
    var index = usedEl.selectedIndex;

    if (index >= usedEl.options.length - 1) {
	return;
    }

    bsw_moveBlock(key, false);
}

/**
 * Show the options for the currently selected block in the used list.
 */
function bsw_showBlockOptions(key) {
    var usedEl = document.getElementById("blocksUsedList_" + key);
    var blockOptionsEl = document.getElementById("bsw_BlockOptions_" + key);

    blockOptionsEl.innerHTML = "";
    if (usedEl.selectedIndex < 0) {
	return;
    }

    // Get the block and block preference we are dealing with
    var blockPref = bsw_USER_BLOCKS[key][usedEl.options[usedEl.selectedIndex].value];
    var block = bsw_WIDGET_BLOCKS[key][blockPref.blockId];

    // For some reason, "block.parameters.length == 0" doesn't work here.  wtf?
    var i = 0;
    for (var paramName in block.parameters) {
	i++;
    }
    if (i == 0) {
	return;
    }

    // First create the table for the parameters
    var optionTableEl = document.createElement("table");
    optionTableEl.id = "bsw_ParamTable_" + key;
    optionTableEl.className = "bsw_ParamTable";

    var headerRowEl = document.createElement("tr");
    headerRowEl.id = "bsw_ParamHeaderRow_" + key;
    headerRowEl.className = "bsw_ParamHeaderRow";

    var paramHeaderEl = document.createElement("td");
    paramHeaderEl.appendChild(document.createTextNode(bsw_HEADER_TEXT[key]['parameter']));

    var paramValueHeaderEl = document.createElement("td");
    paramValueHeaderEl.appendChild(document.createTextNode(bsw_HEADER_TEXT[key]['value']));

    optionTableEl.appendChild(headerRowEl);
    headerRowEl.appendChild(paramHeaderEl);
    headerRowEl.appendChild(paramValueHeaderEl);

    /* Now add the parameter value rows */
    for (var paramName in block.parameters) {
        var paramRowEl = document.createElement("tr");

	var paramNameEl = document.createElement("td");
	paramNameEl.appendChild(document.createTextNode(block.parameters[paramName]['description']));
	paramRowEl.appendChild(paramNameEl);

	var paramValueEl = document.createElement("td");
	paramValueEl.appendChild(bsw_getValueElement(paramName, blockPref, block));
	paramRowEl.appendChild(paramValueEl);

	optionTableEl.appendChild(paramRowEl);
    }

    blockOptionsEl.appendChild(optionTableEl);
}

/**
 * Get the form element that is used to represent a specific block parameter
 * in the state that matches the album settings.
 * @param paramName The name of the parameter.
 * @param blockPref The block preference.
 * @param block The block definition.
 * @returns The form element for the parameter.
 */
function bsw_getValueElement(paramName, blockPref, block) {
    var prefValue = blockPref.parameters[paramName];
    var useDefault = (prefValue == null);
    var defaultValue = block.parameters[paramName]['defaultValue'];
    var elementType = block.parameters[paramName]['type'];

    var returnElement;
    if (elementType == 'boolean') {
	returnElement = document.createElement("input");
	returnElement.type = 'checkbox';

	if (prefValue == 'true') {
	    returnElement.checked = 'checked';
	}
	returnElement.onchange = function() { bsw_updatePrefValue(block.key, elementType, this); };

    } else if (elementType == 'choice') {
	returnElement = document.createElement("select");

	var option;
	i = 0;
	for (var choice in block.parameters[paramName]['extra']) {
	    option = document.createElement("option");
	    option.appendChild(document.createTextNode(choice));
	    option.value = choice;
	    option.innerHTML = block.parameters[paramName]['extra'][choice];
	    returnElement.appendChild(option);

	    if (choice == prefValue) {
		returnElement.selectedIndex = i;
	    }
	    i++;
	}

	returnElement.onchange = function() { bsw_updatePrefValue(block.key, elementType, this); };
    }

    returnElement.id = "prefValue_" + paramName;
    returnElement.blockPref = blockPref;

    return returnElement;
}

/**
 * Update a value in a block preference to match what the user has done.
 * @param element The element that was updated.
 */
function bsw_updatePrefValue(key, varType, element) {
    var paramName = element.id.substring(10);
    var blockPref = element.blockPref;

    var paramValue;
    if (varType == 'boolean') {
	paramValue = element.checked;
    } else {
	paramValue = element.options[element.selectedIndex].value;
    }

    blockPref.setParameterValue(paramName, paramValue);
    bsw_updateAlbumBlockValue(key);
}

// Create a regexp pattern that will pull out all of the block definitions
var BLOCK_REGEXP = /\[[^\]]+\]/g;

/**
 * Given a string value as stored in the gallery database, create block
 * preference objects with the supplied values.
 * @param stringValue The string representation of a block preference
 */
function bsw_createBlockPrefsFromString(key, stringValue) {
    // First we need to remove any options in used block list
    var usedEl = document.getElementById("blocksUsedList_" + key);
    for (var i = usedEl.options.length - 1; i >= 0 ; i--) {
	usedEl.removeChild(usedEl.options[i]);
    }

    // Now clear out the block array
    bsw_USER_BLOCKS[key] = new Array();

    var result = stringValue.match(BLOCK_REGEXP);
    if (result == null) {
	return;
    }

    // At this point we have a bunch of matches with the enclosing []'s
    for (var i = 0; i < result.length; i++) {
	var bits = result[i].substring(1, result[i].length - 1).split(" ");

        var blockId = bits[0];
	var prefValues = new Array();
	for (var bitIndex = 1; bitIndex < bits.length; bitIndex++) {
	    var paramBits = bits[bitIndex].split("=");
	    prefValues[paramBits[0]] = paramBits[1];
	}

	bsw_addUserBlockPreference(key, blockId, prefValues);
    }
}

/**
 * Look at the user blocks that have been selected and update the form element that
 * stores the string representation of them.
 */
function bsw_updateAlbumBlockValue(key) {
    var albumValueEl = document.getElementById("albumBlockValue_" + key);
    var value = "";

    for (var i = 0; i < bsw_USER_BLOCK_POSITIONS[key].length; i++) {
	var blockPrefId = bsw_USER_BLOCK_POSITIONS[key][i];
	var blockPref = bsw_USER_BLOCKS[key][blockPrefId];
	value += blockPref.toString() + " ";
    }

    /*
     * Don't change it unless we really need to, to avoid unnecessarily
     * propagating onchange events which can lead to recursive calls back
     * to bsw_updateAlbumBlockValue()
     */
    var newValue = value.substring(0, value.length - 1);
    if (albumValueEl.value != newValue) {
	albumValueEl.value = newValue;
	if (albumValueEl.onchange) {
	    bsw_UPDATE_LEVEL++;
	    albumValueEl.onchange();
	    bsw_UPDATE_LEVEL--;
	}
    }
}
