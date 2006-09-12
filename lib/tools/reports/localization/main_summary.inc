<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title> Gallery 2: Localization Status Report (<?php print strftime("%x") ?>)s</title>
    <link rel="stylesheet" type="text/css" href="localization/style.css"/>
  </head>
    <body>
      <h1> Localization Status Report for Gallery 2 </h1>
      <h3> Generated: <?php print strftime("%x %X") ?> <br/>
	   Most Recent PO: <?php print strftime("%x %X", $mostRecentPoDate) ?> <br/>
	   Total Translated Strings: <?php print $totalTranslated ?> </h3>

      <center>
	View: <b> summary </b> | <a href="?type=detail"> detail </a>
	<table class="report">
	    <?php $index = 0; ?>
	    <?php foreach ($reportData as $locale => $localeData) { ?>
	    <?php if (!($index % 20)) { ?>
	    <?php include(dirname(__FILE__) . '/row_header_summary.inc'); ?>
	    <?php } ?>
	    <?php $index++; ?>
	    <tr>
	      <td class="dark">
		<?php print $index; ?> 
	      </td>
	      <td class="dark">
		<?php print $locale ?>
	      </td>
	      <td class="locale_percent" style="background-color:#<?php
		  print percentColor($localeData['percentDone']) ?>">
		<?php print round($localeData['percentDone'], $precision) ?>%
	      </td>
	      <?php $summaryData = $localeData['summary']; ?>
	      <td class="<?php print modifier('total') ?>">
		<?php print $summaryData['total'] ?>
	      </td>
	      <td class="<?php print modifier('translated') ?>">
		<?php print round($summaryData['translated'], $precision) ?>%
	      </td>
	      <td class="<?php print modifier('fuzzy') ?>">
		<?php print round($summaryData['fuzzy'], $precision) ?>%
	      </td>
	      <td class="<?php print modifier('untranslated') ?>">
		<?php
		  print '<span title="overall untranslated including missing *.po files">'
		    . round(100 - $summaryData['translated'], $precision)
		    . '%</span> (<span title="untranslated in existing *.po files">'
		    . round($summaryData['untranslated'], $precision) . '%</span>)';
		?>
	      </td>
	      <td class="<?php print modifier('obsolete') ?>">
		<?php print round($summaryData['obsolete'], $precision) ?>%
	      </td>
	    </tr>
	  <?php } ?>
	</table>
      </center>
    </body>
</html>
