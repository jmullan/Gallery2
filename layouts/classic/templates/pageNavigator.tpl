  <table border="1" width="100%" cellspacing="0%" cellpadding="0%">
    <tr>
      <td width="27">
	{if isset($navigator.firstPage)}
	<a href="{galleryUrl view=core:ShowItem itemId=$item.id layoutPage=$navigator.firstPage}">
	  <img src="{$layoutUrl}/images/nav_first.gif" alt="{galleryText text="First"}" border="0"
	    width="27" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td width="72">
	{if isset($navigator.previousPage)}
	<a href="{galleryUrl view=core:ShowItem itemId=$item.id layoutPage=$navigator.previousPage}">
	  <img src="{$layoutUrl}/images/nav_prev.gif" alt="{galleryText text="Previous"}" border="0" width="72" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td align="center">
	{if $navigator.jumprange[0] != $pageNumber}
	<img src="{$layoutUrl}/images/nav_dot.gif" alt="o" border="0" width="8" height="11">
	{/if}
	
	{section name=jumprange loop=$navigator.jumprange}
	{if $navigator.jumprange[jumprange] == $pageNumber}
	<img src="{$layoutUrl}/images/nav_dot_left.gif" alt="&gt;" border="0"
	     width="8" height="11">
	<b>{$navigator.jumprange[jumprange]}</b>
	<img src="{$layoutUrl}/images/nav_dot_right.gif" alt="&lt;" border="0" width="8" height="11">
	{else}
	{strip}
	<a href="{galleryUrl view=core:ShowItem itemId=$item.id layoutPage=$navigator.jumprange[jumprange]}">
	  {$navigator.jumprange[jumprange]}
	</a>
	{/strip}
	{if $navigator.jumprange[jumprange] != $pageNumber-1}
	<img src="{$layoutUrl}/images/nav_dot.gif" alt="o" border="0"
	     width="8" height="11">
	{/if}
	{/if}
	{/section}
      </td>
      <td width=72>
	{if isset($navigator.nextPage)}
	<a href="{galleryUrl view=core:ShowItem itemId=$item.id layoutPage=$navigator.nextPage}">
	  <img src="{$layoutUrl}/images/nav_next.gif" alt="{galleryText text="Next"}" border="0"
	    width="72" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
      <td width=27>
	{if isset($navigator.lastPage)}
	<a href="{galleryUrl view=core:ShowItem itemId=$item.id layoutPage=$navigator.lastPage}">
	  <img src="{$layoutUrl}/images/nav_last.gif" alt="{galleryText text="Last"}" border="0"
	    width="27" height="11">
	</a>
	{else}
	&nbsp;
	{/if}
      </td>
    </tr>
  </table>
