  {strip}
  <table width="1" border="0" cellspacing="0" cellpadding="0">
    <tr>
      <td rowspan="2" colspan="2" width="1" height="1">
	<table cellspacing="0" cellpadding="{$borderWidth}">
	  <tr>
	    <td width="{$width}" height="{$height}">
	      {$content}
	    </td>
	  </tr>
	</table>
      </td>
      <td width="5" height="{$borderWidth}" valign="bottom">
	<img src="{$imagesUrl}/topRight.gif" width="5" height="1">
      </td>
    </tr>

    <tr>
      <td width="5" height="{$height}">
	<img src="{$imagesUrl}/centerRight.gif" width="5" height="{$height}">
      </td>
    </tr>

    <tr>
      <td width="5" height="3">
	<img src="{$imagesUrl}/bottomLeft.gif" width="5" height="3">
      </td>
      <td width="{$width}" height="3">
	<img src="{$imagesUrl}/bottomCenter.gif" width="{$width}" height="3">
      </td>
      <td>
	<img src="{$imagesUrl}/bottomRight.gif" width="5" height="3">
      </td>
    </tr>
  </table>
  {/strip}