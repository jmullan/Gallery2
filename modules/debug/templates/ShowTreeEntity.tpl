    <table border="0" cellspacing="0" cellpadding="0">
      <!-- {foreach key=key item=value from=$entityTable[$entityId]} -->
      <!-- {if strcmp($key, '_className')} -->
	<tr>
	  <td>
	    <i>{$key}</i>
	  </td>
	  <td>
	    {$value}
	  </td>
	</tr>
	<!-- {/if} -->
	<!-- {/foreach} -->
    </table>
	  