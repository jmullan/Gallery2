{* 
 * thinFrame.tpl - draw a thin frame around the HTML content
 * 
 * Input variables:
 *
 *  $params.width (int)
 *     The width of the content
 *
 *  $params.height (int)
 *     The height of the content
 *     
 *  $content (string)
 *     Any HTML content
 * 
 *}
    <table border="1" cellspacing="0" 
      {if !empty($params.width)}
      width="{$params.width}"
      {/if}
      >
	<tr>
	  <td>
	    {$content}
	  </td>
	</tr>
    </table>
      
