    <table border="0" cellspacing="0" cellpadding="0" width="100%">
	<tr>
	  <td align="center">
	    <a href="{galleryUrl view='core:SiteAdmin'}">
	      {galleryBiggestFontSize}
	      {galleryText text="Gallery Site Administration"}
	      {/galleryBiggestFontSize}
	    </a>
	    <br>
	    <a href="{galleryUrl}">
	      [{galleryText text="Browse Gallery"}]
	    </a>
	  </td>
	</tr>
	<tr>
	  <td valign=top>
	    <br>
	    <center>
	      {galleryHeavyFrame}
	      <table border="0" cellspacing="10" cellpadding="10" width="1" height="125">
		<!-- {counter assign=index start=0 print=false} -->
		<!-- {section name=outer loop=$subViewChoices step=3} -->
		  <tr>
		    <!-- {section name=inner loop=$subViewChoices start=$index max=3} -->
		    <td align="center">
		      <a href="{galleryUrl view='core:SiteAdmin' subView=$subViewChoices[$index].view}">{$subViewChoices[$index].name}</a>
		    </td>
		    <!-- {counter} -->
		    <!-- {/section} -->
		  </tr>
		  <!-- {/section} -->
	      </table>
	      {/galleryHeavyFrame}
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
