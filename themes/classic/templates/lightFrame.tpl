{* 
 * lightFrame.tpl - draw a light frame around the HTML content.  Heavier
 *                  than "thinFrame" but lighter than "heavyFrame"
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
    <table border="2" cellspacing="1" 
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
      
