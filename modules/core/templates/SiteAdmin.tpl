    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td align="center">
	    <a href="{gallery->url view='core:SiteAdmin'}">
	      {gallery->biggestFontSize}
	      {gallery->text text="Gallery Site Administration"}
	      {/gallery->biggestFontSize}
	    </a>
	    <br>
	    <a href="{gallery->url}">
	      [{gallery->text text="Browse Gallery"}]
	    </a>
	  </td>
	</tr>
	<tr>
	  <td valign=top>
	    <br>
	    <center>
	      {gallery->heavyFrame}
	      <table border="0" cellspacing="10" cellpadding="10" width="1" height="125">
		<!-- {counter assign=index start=0 print=false} -->
		<!-- {section name=outer loop=$subViewChoices step=3} -->
		  <tr>
		    <!-- {section name=inner loop=$subViewChoices start=$index max=3} -->
		    <td align="center">
		      <a href="{gallery->url view='core:SiteAdmin' subView=$subViewChoices[$index].view}">{$subViewChoices[$index].name}</a>
		    </td>
		    <!-- {counter} -->
		    <!-- {/section} -->
		  </tr>
		  <!-- {/section} -->
	      </table>
	      {/gallery->heavyFrame}
	    </center>
	    <br>
	  </td>
	</tr>
	<tr>
	  <td>
	    {$subViewHtml}
	  </td>
	</tr>
    </table>
