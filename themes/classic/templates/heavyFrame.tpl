{* 
 * heavyFrame.tpl - draw a heavy frame around the HTML content.  Heaviest
 *                  frame we have.
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
    <table border="5" cellspacing="1" 
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
      
