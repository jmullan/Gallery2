{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to index.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <style type="text/css">
      <!--
      body {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 10pt{rdelim}
      th {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 10pt; font-weight: bold; background-color: #D3DCE3{rdelim}
      td {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 10pt{rdelim}
      td.oddRow {ldelim} background-color: #EEEEEE{rdelim}
      td.evenRow {ldelim} background-color: #CCCCCC{rdelim}
      form {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 10pt{rdelim}
      h1 {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 16pt; font-weight: bold{rdelim}
      A:link {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 10pt; text-decoration: none; color: #0000ff{rdelim}
      A:visited {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 10pt; text-decoration: none; color: #0000ff{rdelim}
      A:hover {ldelim}font-family: helvetica, arial, geneva, sans-serif; font-size: 10pt; text-decoration: underline; color: #FF0000{rdelim}
      A:link.nav {ldelim}font-family: helvetica, arial, geneva, sans-serif; color: #000000{rdelim}
      A:visited.nav {ldelim}font-family: helvetica, arial, geneva, sans-serif; color: #000000{rdelim}
      A:hover.nav {ldelim}font-family: helvetica, arial, geneva, sans-serif; color: #FF0000{rdelim}
      .nav {ldelim}font-family: helvetica, arial, geneva, sans-serif; color: #000000{rdelim}
      //-->
    </style>
    <title>
      Gallery Test Harness
    </title>
  </head>
  <body>
    <center>
      <h1> <a href=index.php>Gallery Test Harness</a> </h1>
      {foreach from=$tests key=moduleId item=moduleTests}
      <h2>{$moduleId}</h2>
      <table border="1" cellspacing="0" cellpadding="5" width="100%">
	  <tr>
	    <th bgcolor="#9999CC"> Name
	    <th bgcolor="#9999CC"> Timing
	    <th bgcolor="#9999CC"> Description
	  </tr>

	  {cycle assign=rowClass values="oddRow,evenRow"}
          {foreach from=$tests[$moduleId] item=test}
          {cycle assign=rowClass}
	  <tr>
	    <td class="{$rowClass}">
	      <a href="index.php?moduleId={$test.moduleId}&testName={$test.testName}">{$test.testName}</a>
	    </td>
	    <td class="{$rowClass}">
	      {if (empty($test.iterations))}
	      &nbsp;
	      {else}
	      {foreach from=$test.iterations item=iter}
	      <a href=index.php?moduleId={$test.moduleId}&testName={$test.testName}&iterations={$iter.count}>
		{$iter.title}
	      </a>
	      {/foreach}
	      {/if}
	    </td>
	    <td class="{$rowClass}">
	      {$test.description}
	    </td>
	  </tr>
          {/foreach}
      </table>
      {/foreach}
    </center>

    {if sizeof($results) > 1}
    <hr>
    <b>Overall Status</b>
    <br>
    {if empty($rollup.error)}
    <b>Status</b>: Success
    {else}
    <b>Error</b>: {$rollup.error.html}
    {/if}
    <br>
    <b>Elapsed</b>: {$rollup.elapsed}
    {/if}

    {foreach from=$results item=result}
    <hr>
    <b>Test</b>: {$result.moduleId} :: {$result.testName} [{$result.iterations} iteration(s)]
    <br>
    <b>Timing</b>: {$result.timing.elapsed} elapsed, {$result.timing.persec} per second
    <br>
    {if empty($result.error)}
    <b>Status</b>: Success
    {else}
    <b>Error</b>: {$result.error.html}
    {/if}
    <br>

    {if !empty($result.debug)}
    <b>Debug</b>:
    <br>
    <pre>
    {foreach from=$result.debug item=line}
    {$line}<br>
    {/foreach}
    </pre>
    {/if}

    {if !empty($result.output)}
    <b>Output</b>:
    <pre>
    {foreach from=$result.output item=line}
    {$line}<br>
    {/foreach}
    </pre>
    {/if}
    {/foreach}

  </body>
</html>
