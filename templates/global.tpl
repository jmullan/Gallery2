<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    {if !empty($master.error)}
    <title>{galleryText text="Error"}</title>
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
	    <b>{galleryText text="Gallery Debug Output"}</b>
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
	    <td colspan="6">
	      {galleryBigFont}
	      {galleryText text="Profiling"}
	      {/galleryBigFont}
	    </td>
	  </tr>

	  <tr>
	    <th> {galleryText text="Function"}
	    <th> {galleryText text="Average"}
	    <th> {galleryText text="Max"}
	    <th> {galleryText text="Min"}
	    <th> {galleryText text="Total"}
	    <th> {galleryText text="Count"}
	  </tr>

	{foreach from=$master.profile item=profileEntry}
	  <tr>
	    <td>
	      {$profileEntry.name}
	    </td>
	    {if (isset($profileEntry.error))} 
	    <td colspan="3">
	      {$profileEntry.error}
	    </td>
            {else}
	    <td>
	      {$profileEntry.average}
	    </td>
	    <td>
	      {$profileEntry.max}
	    </td>
	    <td>
	      {$profileEntry.min}
	    </td>
	    <td>
	      {$profileEntry.total}
	    </td>
	    <td>
	      {$profileEntry.count}
	    </td>
            {/if}
          </tr>
        {/foreach}
      </table>
    </center>
    {/if}

    <a href="http://validator.w3.org/check/referer">
      [{galleryText text="Validate this Page"}]
    </a>

    <a href="http://gallery.sourceforge.net">
      [{galleryText text="Powered by Gallery %s"
                    arg1=$gallery.version}]
    </a>
    
  </body>
</html>
