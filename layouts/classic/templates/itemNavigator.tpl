  <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
    <tr>
      <td width="27">
	{if isset($navigator.firstItem)}
	<a href="{galleryUrl view=core:ShowItem itemId=$navigator.firstItem}">
	  <img src="{$layoutUrl}/images/nav_first.gif" alt="{galleryText text="First"}" border="0"
	    width="27" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td width="72">
	{if isset($navigator.previousItem)}
	<a href="{galleryUrl view=core:ShowItem itemId=$navigator.previousItem}">
	  <img src="{$layoutUrl}/images/nav_prev.gif" alt="{galleryText text="Previous"}" border="0"
	    width="72" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td align="center">
	{$itemIndex} (of {$totalPeerCount})
      </td>
      <td width=72>
	{if isset($navigator.nextItem)}
	<a href="{galleryUrl view=core:ShowItem itemId=$navigator.nextItem}">
	  <img src="{$layoutUrl}/images/nav_next.gif" alt="{galleryText text="Next"}" border="0"
	    width="72" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td width=27>
	{if isset($navigator.lastItem)}
	<a href="{galleryUrl view=core:ShowItem itemId=$navigator.lastItem}">
	  <img src="{$layoutUrl}/images/nav_last.gif" alt="{galleryText text="Last"}" border="0"
	    width="27" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
    </tr>
  </table>
