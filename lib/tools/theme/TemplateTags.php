<?php
/*
 * $RCSfile$
 *
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2003 Bharat Mediratta
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

$tags['style'] = array('type' => 'content', 'flag' => 'non-block');
$tags['image'] = array('type' => 'content', 'params' => array('item' => 'array()', 'image' => 'array()'), 'flag' => 'non-block');

// Magic component tag
$tags['component'] = array('type' => 'transparent');

// Built-in content filters
$tags['input'] = array('type' => 'content', 'flag' => 'builtin');
$tags['form'] = array('type' => 'content', 'flag' => 'builtin');
$tags['select'] = array('type' => 'content', 'flag' => 'builtin');
$tags['textarea'] = array('type' => 'content', 'flag' => 'builtin');
$tags['link'] = array('type' => 'content', 'flag' => 'builtin');

// Text style content filters
$tags['error'] = array('type' => 'content');
$tags['status'] = array('type' => 'content');
$tags['textmodifier'] = array('type' => 'content');

// Top level content tags
$tags['globalheader'] = array('type' => 'content');
$tags['main'] = array('type' => 'content', 'children' => array('header?', 'footer?', 'pathbar?', 'sidebar*', 'component*'));
$tags['globalfooter'] = array('type' => 'content');

// Attributes of main
$tags['header'] = array('type' => 'child');
$tags['footer'] = array('type' => 'child');
$tags['pathbar'] = array('type' => 'child', 'children' => array('item+'));
$tags['sidebar'] = array('type' => 'child', 'params' => array('side' => ''), 'children' => array('component+'));

// Boxes that can only contain components
$tags['bannerbox'] = array('type' => 'component', 'children' => array('title?', 'description?', 'component*'));
$tags['linksbox'] = array('type' => 'component', 'children' => array('item+'));
$tags['infobox'] = array('type' => 'component', 'children' => array('item+'));
$tags['listingbox'] = array('type' => 'component', 'children' => array('title?', 'item+'));
$tags['imagebox'] = array('type' => 'component', 'children' => array('title?', 'description?', 'body'));

// Boxes that can contain a body
$tags['detailedbox'] = array('type' => 'component', 'children' => array('title', 'description', 'body'));
$tags['tabbedbox'] = array('type' => 'component', 'children' => array('title?', 'item+', 'body'));
$tags['simplebox'] = array('type' => 'component', 'children' => array('title?', 'body'));
$tags['widget1box'] = array('type' => 'component', 'children' => array('title?', 'widget1+'));
$tags['widget2box'] = array('type' => 'component', 'children' => array('title?', 'widget2+'));

// Widgetbox children
$tags['widget1'] = array('type' => 'child', 'children' => array('title?', 'body'));
$tags['widget2'] = array('type' => 'child', 'children' => array('title?', 'description?', 'body'));
    
// grid layout components
$tags['table'] = array('type' => 'component', 'params' => array('width' => '100%'), 'children' => array('row+'));
$tags['row'] = array('type' => 'child', 'params' => array('rowspan' => '1'), 'children' => array('column+'));
$tags['column'] = array('type' => 'attribute', 'params' => array('valign' => '', 'width' => '', 'header' => 'false', 'colspan' => '1', 'rowspan' => '1'));

// generic attributes
$tags['title'] = array('type' => 'attribute');
$tags['description'] = array('type' => 'attribute');
$tags['body'] = array('type' => 'attribute');
$tags['item'] = array('type' => 'attribute', 'params' => array('selected' => 'false'));

/*
 * Assign flags wherever they're not set.
 */
foreach (array_keys($tags) as $tagName) {
    if (!isset($tags[$tagName]['flags'])) {
	$tags[$tagName]['flags'] = array();
    }
}

$parentMap = array();
foreach ($tags as $tagName => $tagInfo) {
    if (!empty($tagInfo['children'])) {
	foreach ($tagInfo['children'] as $childName) {
	    // strip off regexp marks
	    $childName = preg_replace("/\W/", "", $childName);
	    $parentMap[$childName][$tagName] = 1;
	}

	if ($tagName != 'component' &&
	        $tagInfo['type'] == 'component' &&
	        $tagInfo['flag'] != 'specialized') {
	    /* Components can be used inside a component block or a body block */
	    $parentMap[$tagName]['component'] = 1;
	    $parentMap[$tagName]['body'] = 1;
	}
	
    }

    if (!isset($parentMap[$tagName])) {
	$parentMap[$tagName] = array();
    }
}

/* Generate GalleryTemplateAdapter code */
ob_start();
miscMethods();
foreach ($tags as $tagName => $tagInfo) {
    if ($tagInfo['flag'] == 'non-block') {
	nonBlockTag($tagName, $tagInfo);
    } else {
	blockTag($tagName, $tagInfo);
    }
}
$buf = ob_get_contents();
ob_end_clean();

$fd = fopen("GalleryTemplateAdapter.inc", "w");
fwrite($fd, $buf);
fclose($fd);

/* Generate GalleryTheme code */
ob_start();
foreach ($tags as $tagName => $tagInfo) {
    $paramDocs = array();
    $paramDocs[] = 'array the template context';
    switch($tagInfo['type']) {
    case 'child':
    case 'content':
    case 'component':
	if ($tagInfo['flag'] == 'builtin') {
	    /* This method is built into GalleryTheme -- don't make a stub for it */
	    break;
	}
	    
	$args = array();
	if (isset($tagInfo['children'])) {
	    foreach ($tagInfo['children'] as $childName) {
		preg_match('/(\W)$/', $childName, $matches);
		if (sizeof($matches) > 1) {
		    $modifier = $matches[1];
		} else {
		    $modifier = '';
		}
		$childName = preg_replace('/\W$/', '', $childName);
		switch($modifier) {
		case '?':
		    $paramDocs[] = sprintf('array optional ("params" => array, "content" => %s content)', $childName);
		    $args[] = '$' . $childName;
		    break;
		
		case '':
		    $paramDocs[] = sprintf('array mandatory ("params" => array, "content" => %s content)', $childName);
		    $args[] = '$' . $childName;
		    break;
		
		case '*':
		    $paramDocs[] = sprintf('array optional (array("params" => array, "content" => %s content), ...)',
					   $childName);
		    $args[] = '$' . $childName . '_array';
		    break;
		
		case '+':
		    $paramDocs[] = sprintf('array mandatory (array("params" => array, "content" => %s content), ...)',
					   $childName);
		    $args[] = '$' . $childName . '_array';
		    break;
		
		default:
		    trigger_error("Unknown modifier: $modifier");
		}
	    }
	} else {
	    if ($tagInfo['flag'] != 'non-block') {
		$args[] = '$content';
		$paramDocs[] = 'string optional content';
	    }
	} 

	printf('    /**');
	print "\n";

	printf('     * %s theme method', $tagName);
	print "\n";

	foreach ($paramDocs as $doc) {
	    printf('     * @param %s', $doc);
	    print "\n";
	}

	printf('     * @return string HTML content');
	print "\n";
	
	printf('     */');
	print "\n";

	if ($tagInfo['flag'] == 'non-block') {
	    printf('    function %s($context) {', $tagName);
	    print "\n";
	} else {
	    printf('    function %s($context, %s) {', $tagName, join(', ', $args));
	    print "\n";
	}
	printf('        trigger_error("Undefined theme function: %s", E_USER_ERROR);', $tagName);
	print "\n";
	printf('    }');
	print "\n";
	print "\n";
	break;
	
    case 'attribute':
    case 'transparent':
	/* These are not themeable */
	break;
	
    default:
	trigger_error("Invalid tag type ($tagInfo[type])!");
    }
}
$buf = ob_get_contents();
ob_end_clean();

$fd = fopen("GalleryTheme.inc", "w");
fwrite($fd, $buf);
fclose($fd);


function miscMethods() {
    global $tags;
    
    printf('function getBlockMethods() {');
    print "\n";
    printf('    static $_blockMethods = ');
    print "\n";
    printf('        array(');
    print "\n";
    foreach ($tags as $tagName => $tagInfo) {
	if ($tagInfo['flag'] != 'non-block') {
	    $value = sprintf('"%s",', $tagName);
	    $comment = 'type: ' . $tagInfo['type'];
	    if (isset($tagInfo['children'])) {
		$comment .= ', contains (' . join(' ', $tagInfo['children']) . ')';
	    }
	    if ($tagInfo['flag'] == 'obsolete') {
		$comment .= ' (obsolete)';
	    }
	    printf('        %-20s // %s', $value, $comment);
	    print "\n";
	}
    }
    printf('        );');
    print "\n";
    printf('    return $_blockMethods;');
    print "\n";
    printf('}');
    print "\n";
}


function blockTag($tagName, $tagInfo) {
    global $parentMap;
    
    printf('function %s($params, $content, &$smarty) {', $tagName);
    print "\n";

    printf('    if (!isset($content)) {');
    print "\n";
    if (isset($tagInfo['children'])) {
	printf('        /* Prepare space for output from child tags */');
	print "\n";
	foreach ($tagInfo['children'] as $childName) {
	    $childName = preg_replace('/\W$/', '', $childName);
	    printf('        $this->_content["%s"][] = array();', $childName);
	    print "\n";
	}
    }
    printf('        return;');
    print "\n";
    printf('    }');
    print "\n";
    print "\n";
    printf('    $context = $this->_getContext($params, $smarty);');
    print "\n";


    if ($tagInfo['type'] == 'child' ||
	$tagInfo['type'] == 'attribute' || 
	$tagInfo['type'] == 'transparent') {
	if (!empty($parentMap[$tagName])) {
	    printf('    /* Make sure that we are being called in the right context */');
	    print "\n";
	    printf('    if (empty($context["stack"])) {');
	    print "\n";
	    printf('        $smarty->trigger_error("%s tag must be used inside one of: %s", E_USER_ERROR);',
		   $tagName, join(", ", array_keys($parentMap[$tagName])));
	    print "\n";
	    printf('    }');
	    print "\n";
	    print "\n";
	
	    $comps = array();
	    foreach ($parentMap[$tagName] as $parentName => $junk) {
		$comps[] = sprintf('$context["stack"][0] != "%s"', $parentName);
	    }
	    printf('    if (%s) {', join(' && ', $comps));
	    print "\n";
	    printf('        $smarty->trigger_error("%s tag found inside {$context[\'stack\'][0]}, but must be used inside one of: %s", E_USER_ERROR);',
		   $tagName,
		   join(", ", array_keys($parentMap[$tagName])));
	    print "\n";
	    printf('    }');
	    print "\n";
	}
    }
    
    $args = array();
    if (isset($tagInfo['children'])) {
	foreach ($tagInfo['children'] as $childName) {
	    preg_match('/(\W)$/', $childName, $matches);
	    if (sizeof($matches) > 1) {
		$modifier = $matches[1];
	    } else {
		$modifier = '';
	    }
	    $childName = preg_replace('/\W$/', '', $childName);

	    printf('    $_%s = array_pop($this->_content["%s"]);', $childName, $childName);
	    print "\n";

	    switch($modifier) {
	    case '?':
	    case '':
		printf('    if (empty($_%s)) {', $childName);
		print "\n";
		printf('        $_%s = array("name" => "%s", "params" => array(), "content" => "");', $childName, $tagName);
		//printf('        $_%s = "";', $childName, $tagName);
		print "\n";
		printf('    } else {', $childName);
		print "\n";
		printf('        $_%s = $_%s[0];', $childName, $childName);
		print "\n";
		printf('    }');
		print "\n";
		break;

	    case '*':
	    case '+':
		break;

	    default:
		trigger_error("Unknown modifier: $modifier");
	    }
	    $args[] = sprintf('$_%s', $childName);
	}
    } else {
	$args[] = '$content';
    }

    if (isset($tagInfo['params'])) {
	printf('    foreach (array_keys($params) as $key) {');
	print "\n";
	foreach ($tagInfo['params'] as $paramName => $paramDefault) {
	    $check[] = sprintf('$key != "%s"', $paramName);
	}
	printf('        if (%s) {', join(' && ', $check));
	print "\n";
	printf('            $smarty->trigger_error("invalid parameter $key for %s tag, must be one of: %s", E_USER_ERROR);',
	       $tagName, join(', ', array_keys($tagInfo['params'])));
	print "\n";
	printf('        }');
	print "\n";
	printf('    }');
	print "\n";
	foreach ($tagInfo['params'] as $paramName => $paramDefault) {
	    printf('    if (!isset($params["%s"])) {', $paramName);
	    print "\n";
	    printf('        $params["%s"] = "%s";', $paramName, $paramDefault);
	    print "\n";
	    printf('    }');
	    print "\n";
	}
    }

    switch($tagInfo['type']) {
    case 'content':
	printf('    return $this->_theme->%s($context, %s);', $tagName, join(', ', $args));
	print "\n";
	break;

    case 'component':
	printf('    if ($context["stack"][0] == "component") {');
	print "\n";
	printf('        $this->_content["%s"][sizeof($this->_content["%s"])-1][] = array("name" => "%s", "params" => $params, "content" => $this->_theme->%s($context, %s));',
	       "component", "component", $tagName, $tagName, join(', ', $args));
	print "\n";
	printf('    } else /* body */ {');
	print "\n";
	/* Body is a content block so just return content to it */
	printf('        return $this->_theme->%s($context, %s);', $tagName, join(', ', $args));
	print "\n";
	printf('    }');
	print "\n";
	printf('    return;');
	print "\n";
	break;

    case 'child':
	printf('    $this->_content["%s"][sizeof($this->_content["%s"])-1][] = array("name" => "%s", "params" => $params, "content" => $this->_theme->%s($context, %s));',
	       $tagName, $tagName, $tagName, $tagName, join(', ', $args));
	print "\n";
	printf('    return;');
	print "\n";
	break;
	
    case 'attribute':
	printf('    $this->_content["%s"][sizeof($this->_content["%s"])-1][] = array("name" => "%s", "params" => $params, "content" => $content);', $tagName, $tagName, $tagName);
	print "\n";
	printf('    return;');
	print "\n";
	break;

    case 'transparent':
	printf('    /* Structural tag -- does nothing */');
	print "\n";
	printf('    return;');
	print "\n";
	break;

    default:
	trigger_error("Invalid tag type: $tagInfo[type]");
	break;
    }
	
    printf('}');
    print "\n";
    print "\n";
}

function nonBlockTag($tagName, $tagInfo) {
    global $parentMap;
    
    printf('function %s($params, &$smarty) {', $tagName);
    print "\n";
    printf('    $context = $this->_getContext($params, $smarty);');
    print "\n";

    if (!empty($parentMap[$tagName])) {
	printf('    if (empty($context["stack"])) {');
	print "\n";
	printf('        $smarty->trigger_error("%s tag must be used inside one of: %s", E_USER_ERROR);',
	       $tagName, join(", ", array_keys($parentMap[$tagName])));
	print "\n";
	printf('        return "";');
	print "\n";
	printf('    }');
	print "\n";
	print "\n";
	
	$comps = array();
	foreach ($parentMap[$tagName] as $parentName => $junk) {
	    $comps[] = sprintf('$context["stack"][0] != "%s"', $parentName);
	}
	printf('    if (%s) {', join(' && ', $comps));
	print "\n";
	printf('        $smarty->trigger_error("%s tag found inside {$context[\'stack\'][0]}, but must be used inside one of: %s", E_USER_ERROR);',
	       $tagName,
	       join(", ", array_keys($parentMap[$tagName])));
	print "\n";
	printf('        return "";');
	print "\n";
	printf('    }');
	print "\n";
    }

    if (isset($tagInfo['params'])) {
	printf('    foreach (array_keys($params) as $key) {');
	print "\n";
	foreach ($tagInfo['params'] as $paramName => $paramDefault) {
	    $check[] = sprintf('$key != "%s"', $paramName);
	}
	printf('        if (%s) {', join(' && ', $check));
	print "\n";
	printf('            $smarty->trigger_error("invalid parameter $key for %s tag, must be one of: %s", E_USER_ERROR);',
	       $tagName, join(', ', array_keys($tagInfo['params'])));
	print "\n";
	printf('        }');
	print "\n";
	printf('    }');
	print "\n";
	foreach ($tagInfo['params'] as $paramName => $paramDefault) {
	    printf('    if (!isset($params["%s"])) {', $paramName);
	    print "\n";
	    printf('        $params["%s"] = "%s";', $paramName, $paramDefault);
	    print "\n";
	    printf('    }');
	    print "\n";
	}
    }
    
    printf('    return $this->_theme->%s($context);', $tagName);
    print "\n";
    printf('}');
    print "\n";
    print "\n";
}

?>