<?php
/*
 * $RCSfile
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

/*
 * Authors: Jens Tkotz, Bharat Mediratta
 */

$poFiles = findPoFiles("../../..");
$reportData = parsePoFiles($poFiles);
require(dirname(__FILE__) . '/localization/main.inc');
exit;

function findPoFiles($dir) {
    $results = array();
    if (!is_dir($dir)) {
	return $results;
    }
    
    if ($dh = opendir($dir)) {
	while (($file = readdir($dh)) !== false) {
	    if ($file == '.' || $file == '..') {
		continue;
	    }
	    $path = $dir . '/' . $file;
	    if (is_dir($path)) {
		$results = array_merge($results, findPoFiles($path));
	    } else {
		if (preg_match("/\.po$/", $file)) {
		    $results[] = $path;	
		}
	    }
	}
    }
    return $results;
}

function parsePoFiles($poFiles) {

    /*
     * Parse each .po file for relevant statistics and gather it together into a
     * single data structure.
     */
    $poData = array();
    $seenPlugins = array();
    $maxMessageCount = array();
    foreach ($poFiles as $poFile) {
	preg_match("|/(\w+/\w+)/po/(\w+_\w+).po|", $poFile, $matches);
	list ($plugin, $locale) = array($matches[1], $matches[2]);
	$seenPlugins[$plugin] = 1;

	$fuzzy = 0;
	$translated = 0;
	$untranslated = 0;
	$obsolete = 0;
	/*
	 * Untranslated:
	 *   msgid "foo"
	 *   msgstr ""
	 *
	 * Translated:
	 *   msgid "foo"
	 *   msgstr "bar"
	 *
	 * Translated:
	 *   msgid "foo"
	 *   msgstr ""
	 *   "blah blah blah"
	 *
	 * Untranslated: 
	 *   msgid "foo"
	 *   msgstr[0] ""
	 *   msgstr[1] ""
	 *   msgstr[2] ""
	 *
	 * Translated:
	 *   msgid "foo"
	 *   msgstr[0] "bar1"
	 *   msgstr[1] "bar2"
	 *   msgstr[2] "bar3"
	 *
	 * Translated, Fuzzy:
	 *   # fuzzy
	 *   msgid "foo"
	 *   msgstr "bar"
	 *  
	 * Deleted, Fuzzy:
	 *   # fuzzy
	 *   #~ msgid "foo"
	 *   #~ msgstr "bar"
	 *  
	 */
	$msgId = null;
	$nextIsFuzzy = 0;
	$lastLineWasEmptyMsgStr = 0;
	$lastLineWasEmptyMsgId = 0;
	foreach (file($poFile) as $line) {
	    /*
	     * Scan for:
	     *   msgid "foo bar"
	     *
	     * and:
	     *   msgid ""
	     *   "foo bar"
	     */
	    if (preg_match('/^msgid "(.*)"/', $line, $matches)) {
		if (empty($matches[1])) {
		    $lastLineWasEmptyMsgId = 1;
		} else {
		    $msgId = $line;
		}
		continue;
	    }

	    /*
	     * Scan for:
	     *   msgid ""
	     *   "foo bar"
	     */
	    if ($lastLineWasEmptyMsgId) {
		if (preg_match('/^\s*"(.*)"/', $line, $matches)) {
		    $msgId = $line;
		}
		$lastLineWasEmptyMsgId = 0;
		continue;
	    }

	    if (strpos($line, '#, fuzzy') === 0) {
		$nextIsFuzzy = 1;
		continue;
	    }	    

	    if (preg_match('/^#~ msgid "(.*)"/', $line, $matches)) {
		$obsolete++;
		$nextIsFuzzy = 0;
	    }

	    /*
	     * Scan for:
	     *   msgstr ""
	     *   "foo bar"
	     */
	    if ($lastLineWasEmptyMsgStr) {
		if (preg_match('/^\s*".+"/', $line)) {
		    if ($nextIsFuzzy) {
			$fuzzy++;
		    }
		    $translated++;
		} else {
		    if ($nextIsFuzzy) {
			print "ERROR: DISCARD FUZZY for [$locale, $plugin, $msgId]<br>";
		    }
		    $untranslated++;
		}
		$msgId = null;
		$nextIsFuzzy = 0;
		$lastLineWasEmptyMsgStr = 0;
	    }
		
	    /*
	     * Scan for:
	     *   msgstr "foo bar"
	     *
	     * or:
	     *   msgstr ""
	     *   "foo bar"
	     */
	    if (!empty($msgId)) {
		if (preg_match('/^msgstr/', $line)) {
		    if (preg_match('/^msgstr(.*)""/', $line)) {
			$lastLineWasEmptyMsgStr = 1;
		    } else {
			if ($nextIsFuzzy) {
			    $fuzzy++;
			}
			$translated++;
			$msgId = null;
			$nextIsFuzzy = 0;
		    }
		}
	    }
	}

	$total = $translated + $untranslated;
	$percentDone = round(($translated - $fuzzy) / $total * 100);
	$poData[$locale]['plugins'][$plugin] = array('translated' => $translated,
						     'untranslated' => $untranslated,
						     'total' => $total,
						     'fuzzy' => $fuzzy,
						     'obsolete' => $obsolete,
						     'percentDone' => $percentDone);

	/* Keep track of the largest message count we've seen per plugin */
	if (empty($maxMessageCount[$plugin]) || $total > $maxMessageCount[$plugin]) {
	    $maxMessageCount[$plugin] = $total;
	}
    }

    /* Overall total message count */
    $overallTotal = array_sum(array_values($maxMessageCount));

    foreach (array_keys($poData) as $locale) {
	$pluginTotal = 0;
	
	/* Fill in any missing locales */
	foreach (array_keys($seenPlugins) as $plugin) {
	    if (!isset($poData[$locale]['plugins'][$plugin])) {
		$poData[$locale]['plugins'][$plugin]['missing'] = 1;
		$poData[$locale]['plugins'][$plugin]['percentDone'] = 0;
	    } else {
		/*
		 * debug
		printf("[$locale, $plugin] [%d, %d]<br>",
		       $poData[$locale]['plugins'][$plugin]['translated'],
		       $poData[$locale]['plugins'][$plugin]['fuzzy']);
		*/

		$pluginTotal +=
		    $poData[$locale]['plugins'][$plugin]['translated'] -
		    $poData[$locale]['plugins'][$plugin]['fuzzy'];
	    }
	}
	uasort($poData[$locale]['plugins'], 'sortByPercentDone');

	/* Figure out total percentage */
	$poData[$locale]['percentDone'] = round($pluginTotal / $overallTotal * 100);
    }

    /* Sort locales by overall total */
    uasort($poData, 'sortByPercentDone');
    
    return $poData;
}

function sortByPercentDone($a, $b) {
    if ($a['percentDone'] == $b['percentDone']) {
	return 0;
    }
    return ($a['percentDone'] < $b['percentDone']) ? 1 : -1;
}

function percentColor($percent) {
    $border=50;
    if ($percent < $border) {
	$color = dechex(255 - $percent * 2) . "0000";
    } else {
	$color= "00" . dechex( 55 + $percent * 2 ). "00";
    }
    if (strlen($color) <6) {
	$color= "0" . $color;
    }

    return $color;
}

?>
<hr>

$total=array();
$languages=array();

foreach ($podirs as $podir) {
    $handle=opendir($podir);
    $component=substr($podir,3,-3);
    $components[]=$component;

    while ($filename = readdir($handle)) {
	if (ereg("^([a-z]{2}_[A-Z]{2})(\.[a-zA-Z0-9]+)?(\.po)$", $filename, $matches)) {
	    $locale=substr($filename,0,-3);
	    if (! in_array($locale, $languages)) $languages[]=$locale;
			
	    $lines=file("$podir/$filename");
	    $fuzzy=0;
	    $translated=0;
	    $untranslated=-1;
	    $obsolete=0;
	    foreach ($lines as $line) {	
		if(strpos($line,'msgstr') === 0) {
		    if(stristr($line,'msgstr ""')) {
			$untranslated++;
		    } else {
			$translated++;
		    }
		} elseif (strpos($line,'#, fuzzy') === 0) {
		    $fuzzy++;
		} elseif (strpos($line,'#~ ') === 0) {
		    $obsolete++;
		}
	    }
			
	    $all=$translated+$untranslated;
	    $percent_done=round(($translated-$fuzzy)/$all*100,2);
	    $rpd=round($percent_done,0);
				
	    $report[$locale][$component]=array ($color,$percent_done,$all,$translated,$fuzzy,$untranslated,$obsolete/2);
	    $total['percent_done'] = $total['percent_done'] + $percent_done;
	    $report[$locale]['tpd']+=$percent_done;;
	}
    }
    closedir($handle);
}
$total['percent_done'] = round($total['percent_done'] / (sizeof($languages)*sizeof($components)),2);

function my_usort_function ($a, $b) {
    if ($a['tpd'] > $b['tpd']) { return -1; }
    if ($a['tpd'] < $b['tpd']) { return 1; }
    return 0;
}

foreach ($report as $key => $value) {
    $keys=(array_keys($value));
    foreach ($components as $compo) {
	if ($compo == 'lib/tools') continue;
	if (! in_array($compo, $keys)) {
	    $report[$key][$compo]='missing';
	}
    }

    $rtpd=round($report[$key]['tpd']/(sizeof($components)),2);
    $report[$key]['tpd']=$rtpd;
    if($rtpd <50) {
	$color=dechex(255-$rtpd*2). "0000";
    } else {
	$color="00" . dechex(55+$rtpd*2). "00";
    }
    if (strlen($color) <6) $color="0". $color;
    $report[$key]['color']=$color;
}

uasort ($report, 'my_usort_function');


$filename="./g2-report.xml";

if (!$handle = fopen($filename, "w+")) {
    echo _("Unable to open ") . $filename ;
    exit;
}

setlocale(LC_ALL,"de_DE");
fwrite($handle,"<report date=\"".strftime("%x",time()). "\" time=\"".strftime("%X",time()) ."\">");

$i=0;
$j=0;

foreach ($report as $key => $value) {
    krsort($value);

    $i++;
    if ($i%2==0) {
	$scheme="light";
    } else {
	$scheme="dark";
    }
	
    if ($value['tpd'] != $last_value['tpd']) { 
	$lfd_nr++;
	$line=$lfd_nr;	
    } else {
	$line="";
    }

    fwrite($handle,"\n\t<locale id=\"$key\" scheme=\"$scheme\">");
    fwrite($handle,"\n\t\t<nr scheme=\"$scheme\">$line</nr>");
    fwrite($handle,"\n\t\t<tpd style=\"background-color:#". $value['color'] ."\">". $value['tpd'] ."</tpd>");
	
    foreach ($value as $subkey => $subvalue) {
	if ($subkey =="tpd" or $subkey=="cc" or $subkey=="color") continue;
	fwrite($handle,"\n\t\t<component scheme=\"$scheme\">");
	fwrite($handle,"\n\t\t\t<name scheme=\"$scheme\">". $subkey ."</name>");
	if ($subvalue != 'missing') {
	    fwrite($handle,"\n\t\t\t<percent_done style=\"background-color:#". $subvalue[0] ."\">$subvalue[1] %</percent_done>");
	    fwrite($handle,"\n\t\t\t<lines scheme=\"$scheme\">". $subvalue[2] ."</lines>");
	    fwrite($handle,"\n\t\t\t<translated scheme=\"translated_$scheme\">$subvalue[3]</translated>");
	    fwrite($handle,"\n\t\t\t<fuzzy scheme=\"fuzzy_$scheme\">$subvalue[4]</fuzzy>");
	    fwrite($handle,"\n\t\t\t<untranslated scheme=\"untranslated_$scheme\">$subvalue[5]</untranslated>");
	    fwrite($handle,"\n\t\t\t<obsolete scheme=\"obsolete_$scheme\">$subvalue[6]</obsolete>");
	} else {
	    fwrite($handle,"\n\t\t\t<percent_done style=\"background-color:#FF0000\">0 %</percent_done>");
	    fwrite($handle,"\n\t\t\t<missing style=\"background-color: pink;\" />");
	}
	fwrite($handle,"\n\t\t</component>");
    }

    fwrite($handle,"\n\t</locale>");

    $last_value=$value;	
}
fwrite($handle,"\n\t<total>");
fwrite($handle,"\n\t\t<languages>". sizeof($languages) ."</languages>");
fwrite($handle,"\n\t\t<t_percent_done align=\"right\">". $total['percent_done'] ."</t_percent_done>");
fwrite($handle,"\n\t</total>");
fwrite($handle,"\n</report>");
fclose($handle);

exec("/usr/bin/xsltproc g2-report.xslt g2-report.xml > g2-report.html");
?>