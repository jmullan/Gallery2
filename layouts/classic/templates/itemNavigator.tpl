  <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
    <tr>
      <td width="27">
	{if isset($navigator.firstItem)}
	<a href="{gallery->url view=core:ShowItem itemId=$navigator.firstItem}">
	  <img src="{$layoutUrl}/images/nav_first.gif" alt="{gallery->text text="First"}" border="0"
	    width="27" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td width="72">
	{if isset($navigator.previousItem)}
	<a href="{gallery->url view=core:ShowItem itemId=$navigator.previousItem}">
	  <img src="{$layoutUrl}/images/nav_prev.gif" alt="{gallery->text text="Previous"}" border="0"
	    width="72" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td align="center">
	{gallery->text text="Viewing item %d (of %d)"
	             arg1=$itemIndex
	             arg2=$totalPeerCount}
      </td>
      <td width=72>
	{if isset($navigator.nextItem)}
	<a href="{gallery->url view=core:ShowItem itemId=$navigator.nextItem}">
	  <img src="{$layoutUrl}/images/nav_next.gif" alt="{gallery->text text="Next"}" border="0"
	    width="72" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td width=27>
	{if isset($navigator.lastItem)}
	<a href="{gallery->url view=core:ShowItem itemId=$navigator.lastItem}">
	  <img src="{$layoutUrl}/images/nav_last.gif" alt="{gallery->text text="Last"}" border="0"
	    width="27" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
    </tr>
  </table>
