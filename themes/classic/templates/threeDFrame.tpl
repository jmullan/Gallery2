{* 
 * threeDFrame.tpl - draw a 3D frame around the content provided
 * 
 * Input variables:
 *
 *  $params.width (int)
 *     The width of the content
 *
 *  $params.height (int)
 *     The height of the content
 *     
 *  $params.borderWidth (int)
 *     The height of the content
 *
 *  $params.borderHeight (int)
 *     The height of the content
 *
 *  $content (string)
 *     Any HTML content
 * 
 *}
  {strip}
  <table width="1" border="0" cellspacing="0" cellpadding="0">
    <tr>
      <td rowspan="2" colspan="2" width="1" height="1">
	<table cellspacing="0" cellpadding="{$params.borderWidth}">
	  <tr>
	    <td width="{$params.width}" height="{$params.height}">
	      {$content}
	    </td>
	  </tr>
	</table>
      </td>
      <td width="5" height="{$params.borderWidth}" valign="bottom">
	<img src="{$theme.url}/images/topRight.gif" width="5" height="1">
      </td>
    </tr>

    <tr>
      <td width="5" height="{$params.height}">
	<img src="{$theme.url}/images/centerRight.gif" width="5" height="{$params.height}">
      </td>
    </tr>

    <tr>
      <td width="5" height="3">
	<img src="{$theme.url}/images/bottomLeft.gif" width="5" height="3">
      </td>
      <td width="{$params.width}" height="3">
	<img src="{$theme.url}/images/bottomCenter.gif" width="{$params.width}" height="3">
      </td>
      <td>
	<img src="{$theme.url}/images/bottomRight.gif" width="5" height="3">
      </td>
    </tr>
  </table>
  {/strip}