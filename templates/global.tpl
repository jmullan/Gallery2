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
	    {$master.debug}
	  </td>
	</tr>
    </table>
    {/if}

    {if !empty($master.profile)}
    <!-- Profiling output -->
    <table border="1" width="100%">
	<tr>
	  <td>
	    {galleryText text="%s seconds elapsed" arg1=$master.profile.elapsed}
	  </td>
	</tr>
    </table>
    {/if}

    <a href="http://validator.w3.org/check/referer">validate this page</a>
    
  </body>
</html>
