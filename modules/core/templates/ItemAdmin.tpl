    <table border="0" cellspacing="0" cellpadding="4" width="100%" height="100%">
	<tr>
	  <td colspan="2" align="center">
	    {galleryBiggestFont}
	    {galleryText text="Gallery Item Administration"}
	    {/galleryBiggestFont}
	  </td>
	</tr>
	
	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>
	
	<tr>
	  <td valign="top" width="200" height="100%">
	    {galleryLightFrame}
	    <center>
	      {galleryBigFont}
	      {galleryText text="Editting this item"}
	      {/galleryBigFont}
	      <br>
	      <img src="about:blank" width="200" height="150" alt="thumbnail goes here">
	    </center>
	    
	    <br>
	    
	    {galleryBigFont}
	    {galleryText text="Available Settings"}
	    {/galleryBigFont}
	    
	    <table border="0" cellspacing="0" cellpadding="0">
	      {foreach from=$subViewChoices item=choice}
		<tr>
		  <td>
		    <a href="{galleryUrl view='core:ItemAdmin' subView=$choice.view itemId=$itemId}">{$choice.name}</a>
                  </td>
		</tr>
	        {/foreach}
            </table>
            {/galleryLightFrame}
          </td>
	  <td valign="top" width="100%" height="100%">
	    {galleryLightFrame}
	    {$subViewHtml}
	    {/galleryLightFrame}
	  </td>
	</tr>
    </table>
