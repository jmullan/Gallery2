    <table border="0" cellspacing="0" cellpadding="4" width="100%" height="100%">
	<tr>
	  <td colspan="2" align="center">
	    {galleryBiggestFont}
	    {galleryText text="Gallery Item Administration"}
	    {/galleryBiggestFont}
	  </td>
	</tr>
	
	<tr>
	  <td valign="top" width="200" height="100%">
	    {galleryLightFrame}
	    <center>
	      {galleryBigFont}
	      <nobr>
		{galleryText text="Editing this item"}
	      </nobr>
	      {/galleryBigFont}
	      <br>
	      <a href="{galleryUrl view="core:ShowItem" itemId=$item.id}">
		{if !empty($thumbnail)} 
		<img src="{galleryUrl view='core:DownloadItem' itemId=$thumbnail.id}" 
		     width="{$thumbnail.width}" 
		     height="{$thumbnail.height}" 
		     alt="{$item.title}"
		     border="0">
		{else}
		<br>
		<i>{galleryText text="No Thumbnail"}</i>
		<br>
		{/if}
	      </a>
	    </center>
	    
	    <br>
	    
	    <nobr>
	      {galleryBigFont}
	      {galleryText text="Available Settings"}
	      {/galleryBigFont}
	    </nobr>
	    
	    <table border="0" cellspacing="0" cellpadding="0">
	      {foreach from=$subViewChoices item=choice}
		<tr>
		  <td>
		    <a href="{galleryUrl view='core:ItemAdmin' subView=$choice.view itemId=$item.id}">{$choice.name}</a>
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
