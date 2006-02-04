function search_HighlightResults(criteria) {
    criteria = criteria.replace(/([.*+?^${}()|[\]\/\\])/g, '\\$1')
    var regex = new RegExp("(" + criteria + ")", "ig");

    var spans = document.getElementsByTagName("span");
    for (var i = 0; i < spans.length; i++) {
	if (spans[i].className != "ResultData") {
	    continue;
	}
	for (j = 0; j < spans[i].childNodes.length; j++) {
	    if (spans[i].childNodes[j].nodeName == "#text") {
		node = spans[i].childNodes[j];
		var spanEl = document.createElement("span");
		spanEl.innerHTML =
		    node.nodeValue.replace(regex, "<span class=\"giSearchHighlight\">$1</span>");
		node.parentNode.insertBefore(spanEl, node);
		node.parentNode.removeChild(node);
	    }
	}
    }
}
