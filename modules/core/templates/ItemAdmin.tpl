    <table border="0" cellspacing="0" cellpadding="4" width="100%" height="100%">
	<tr>
	  <td colspan="2" align="center">
	    {gallery->biggestFontSize}
	    {gallery->text text="Gallery Item Administration"}
	    {/gallery->biggestFontSize}
	  </td>
	</tr>
	
	<tr>
	  <td valign="top" width="200" height="100%">
	    {gallery->lightFrame}
	    <center>
	      {gallery->bigFontSize}
	      <nobr>
	      {if $itemType == "album"}
		{gallery->text text="Editing this album"}
	      {else} 
		{gallery->text text="Editing this item"}
	      {/if} 
	      </nobr>
	      {/gallery->bigFontSize}
	      <br>
	      <a href="{gallery->url view="core:ShowItem" itemId=$item.id}">
		{if !empty($thumbnail)} 
		<img src="{gallery->url view='core:DownloadItem' itemId=$thumbnail.id}" 
		     width="{$thumbnail.width}" 
		     height="{$thumbnail.height}" 
		     alt="{$item.title}"
		     border="0">
		{else}
		<br>
		<i>{gallery->text text="No Thumbnail"}</i>
		<br>
		{/if}
	      </a>
	    </center>
	    
	    <br>
	    
	    <nobr>
	      {gallery->bigFontSize}
	      {gallery->text text="Available Settings"}
	      {/gallery->bigFontSize}
	    </nobr>
	    
	    <table border="0" cellspacing="0" cellpadding="0">
	      {foreach from=$subViewChoices item=choice}
		<tr>
		  <td>
		    <a href="{gallery->url view='core:ItemAdmin' subView=$choice.view itemId=$item.id}">{$choice.name}</a>
                  </td>
		</tr>
	        {/foreach}
            </table>
            {/gallery->lightFrame}
          </td>
	  <td valign="top" width="100%" height="100%">
	    {gallery->lightFrame}
	    {$subViewHtml}
	    {/gallery->lightFrame}
	  </td>
	</tr>
    </table>
