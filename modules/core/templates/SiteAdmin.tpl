  <table border="1" cellspacing="0" cellpadding="0" width="100%">
    <tr>
      <td align="center">
	<H1> <a href="{galleryUrl view='core:SiteAdmin'}">{galleryText text="Gallery Site Administration"}</a> </H1>
      </td>
    </tr>
    <tr>
      <td valign=top>
	<center>
	  <table border="1" cellspacing="10" cellpadding="10">
	    {counter assign=index start=0 print=false}
	    {section name=outer loop=$subViewChoices step=4}
	    <tr>
	      {section name=inner loop=$subViewChoices start=$index max=4}
	      <td>	
		<a href="{galleryUrl view='core:SiteAdmin' subView=$subViewChoices[$index].view}">{$subViewChoices[$index].name}</a>
	      </td>
	      {counter}
	      {/section}
	    </tr>
	    {/section}
	  </table>
	</center>
      </td>
    </tr>
    <tr>
      <td>
	{$subViewHtml}
      </td>
    </tr>
  </table>
