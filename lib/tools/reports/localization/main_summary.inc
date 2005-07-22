<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title> Gallery 2: Localization Status Report (<?php print strftime("%x") ?>)s</title>
    <link rel="stylesheet" type="text/css" href="localization/style.css"/>
  </head>
    <body>
      <h1> Localization Status Report for Gallery 2 </h1>
      <h2> Generated: <?php print strftime("%x %X") ?> </h2>

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
	      <td bgcolor="<?php print percentColor($localeData['percentDone']) ?>" class="locale_percent">
		<?php print round($localeData['percentDone']) ?>%
	      </td>
	      <?php $summaryData = $localeData['summary']; ?>
	      <td class="<?php print modifier('total') ?>">
	        <?php print $summaryData['total'] ?>
	      </td>
	      <td class="<?php print modifier('translated') ?>">
		<?php print round($summaryData['translated']) ?>%
	      </td>
	      <td class="<?php print modifier('fuzzy') ?>">
		<?php print round($summaryData['fuzzy']) ?>%
	      </td>
	      <td class="<?php print modifier('untranslated') ?>">
		<?php
		  print '<span title="overall untranslated including missing *.po files">'
		    . round(100 - $summaryData['translated'])
		    . '%</span> (<span title="untranslated in existing *.po files">'
		    . round($summaryData['untranslated']) . '%</span>)';
		?>
	      </td>
	      <td class="<?php print modifier('obsolete') ?>">
		<?php print round($summaryData['obsolete']) ?>%
	      </td>
	    </tr>
	  <?php } ?>
	</table>
      </center>
    </body>
</html>
