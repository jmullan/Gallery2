  <table border="1" cellspacing="0" cellpadding="0" width="100%">
    <tr>
      <td align="center">
	<a href="{galleryUrl view='core:SiteAdmin'}">
	  {galleryBiggestFont}
	  {galleryText text="Gallery Site Administration"}
	  {/galleryBiggestFont}
	</a>
      </td>
    </tr>
    <tr>
      <td valign=top>
	<br>
	<center>
	  <!-- It probably doesn't make sense to use a three-D frame here, but -->
          <!-- I wanted to put in a test case to make sure that it looks ok    -->
	  {galleryThreeDFrame width="318" height="124"}
	  <table border="1" cellspacing="10" cellpadding="10" width="300" height="125">
	    {counter assign=index start=0 print=false}
	    {section name=outer loop=$subViewChoices step=4}
	    <tr>
	      {section name=inner loop=$subViewChoices start=$index max=4}
	      <td align="center">
		<a href="{galleryUrl view='core:SiteAdmin' subView=$subViewChoices[$index].view}">{$subViewChoices[$index].name}</a>
	      </td>
	      {counter}
	      {/section}
	    </tr>
	    {/section}
	  </table>
	  {/galleryThreeDFrame}
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
