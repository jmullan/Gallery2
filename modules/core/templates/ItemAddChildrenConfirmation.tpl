
    <center>
      {if ($count)}
      {gallery->biggerFontSize}
      {gallery->successFontColor}
      {gallery->text one="Successfully added %d file."
                     many="Successfully added %d files."
                     count=$count
                     arg1=$count}
      {/gallery->successFontColor}
      {/gallery->biggerFontSize}

      <table>
	<!-- {foreach from=$status item=entry} -->
	  <tr>
	    <td>
	      {gallery->text text="Added %s" arg1=$entry.fileName}
	    </td>
	  </tr>
	<!-- {/foreach} -->
      </table>
      {else}
      {gallery->biggerFontSize}
      {gallery->warningFontColor}
      {gallery->text text="Did not add any files."}
      {/gallery->warningFontColor}
      {/gallery->biggerFontSize}
      {/if}

      <br>

      <a href="{gallery->url view="core:ItemAdmin" subView="core:ItemAddChildren" itemId=$item.id}">
	{gallery->text text="Add more files"}
      </a>
    </center>
