<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
      {if !empty($master.error)}
      <title>{gallery->text text="Error"}</title>
      {else}
      {$master.view.head}
      {/if}
  </head>
  <body>
    
    {if !empty($master.error)}
    {$master.error}
    {else}
    {$master.view.body}
    {/if}

    {if !empty($master.debug)}
    <!-- Debug output -->
    <table border="1" width="100%">
	<tr>
	  <td>
	    <b>{gallery->text text="Gallery Debug Output"}</b>
	  </td>
	</tr>
	<tr>
	  <td>
	    <pre>{$master.debug}</pre>
	  </td>
	</tr>
    </table>
    {/if}

    <!-- Profiling output -->
    {if !empty($master.profile)}
    <br>
    <center>
      <table border="1">
	  <tr>
	    <td colspan="8">
	      {gallery->bigFontSize}
	      {gallery->text text="Profiling"}
	      {/gallery->bigFontSize}
	    </td>
	  </tr>

	  <tr>
	    <th rowspan=2> {gallery->text text="Function"}
	    <th colspan=2> {gallery->text text="Combined"}
	    <th colspan=3> {gallery->text text="Internal"}
	    <th colspan=3> {gallery->text text="External"}
	  </tr>
	  <tr>
	    <th> {gallery->text text="Calls"}
	    <th> {gallery->text text="Total"}
	    <th> &lt;{gallery->text text="Total"}&gt;
	    <th> {gallery->text text="Max"}
	    <th> {gallery->text text="Average"}
	    <th> {gallery->text text="Total"}
	    <th> {gallery->text text="Max"}
	    <th> {gallery->text text="Average"}
	  </tr>

      {foreach from=$master.profile item=profileEntry}
      <tr>
	<td>
	  {$profileEntry.name}
	</td>
      {if (isset($profileEntry.error))} 
      <td colspan="7">
	{gallery->text text="Error:"} {$profileEntry.error}
      </td>
      {else}
      <td>
	{$profileEntry.count}
      </td>
      <td>
	{$profileEntry.total}
      </td>
      <td>
	{$profileEntry.internal.total}
      </td>
      <td>
	{$profileEntry.internal.max}
      </td>
      <td>
	{$profileEntry.internal.average}
      </td>
      <td>
	{$profileEntry.external.total}
	<!-- External call report for {$profileEntry.name} -->
	{foreach from=$profileEntry.external.calls item=call}
	<!-- Call: {$call.elapsed} {$call.marker} -->
	{/foreach}
      </td>
      <td>
	{$profileEntry.external.max}
      </td>
      <td>
	{$profileEntry.external.average}
      </td>
      {/if}
    </tr>
      {/foreach}
    </table>
    </center>
    {/if}

    <a href="http://validator.w3.org/check/referer">
      <img border="0" 
	   src="{gallery->url href="images/html401.gif"}"
           alt="{gallery->text text="This page is valid HTML 4.01"}" 
           height="15" width="80">
    </a>

    <a href="http://gallery.sourceforge.net">
      <img border="0" 
	   src="{gallery->url href="images/gallery.gif"}"
           alt="{gallery->text text="Powered by Gallery %s" arg1=$gallery.version}"
           height="15"  
           width="80">
    </a>

  </body>
</html>
