  <pre>
    {counter print=false start=1 assign=lineNumber}
    <table>
      <!-- {foreach from=$lines item=line} -->
	<tr>
	  <td>
	    <a name="{$lineNumber}">
	      {if ($lineNumber == $currentLine)}
	      {gallery->successFontColor}
	      {$lineNumber}
	      {/gallery->successFontColor}
	      {else}
	      {$lineNumber}
	      {/if}
	    </a>
	  </td>
	  <td>
	    &nbsp;
	  </td>
	  <td>
	    {if ($lineNumber == $currentLine)}
	    {gallery->successFontColor}
	    {$line|escape|replace:" ":"&nbsp;"|replace:"\t":"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"}
	    {/gallery->successFontColor}
	    {else}
	    {$line|escape|replace:" ":"&nbsp;"|replace:"\t":"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"}
	    {/if}
	  </td>
	</tr>
	<!-- {counter} -->
	<!-- {/foreach} -->
    </table>
  </pre>