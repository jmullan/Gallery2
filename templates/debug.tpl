    {if !empty($main.debug)}
    <!-- Debug output -->
    <table border="1" width="100%">
	<tr>
	  <td>
	    <b>{gallery->text text="Gallery Debug Output"}</b>
	  </td>
	</tr>
	<tr>
	  <td>
	    <pre>{$main.debug}</pre>
	  </td>
	</tr>
    </table>
    {/if}
