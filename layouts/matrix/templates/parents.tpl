  <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
    <tr>
      <td align="right">
	{section name=parent loop=$parents}
	{strip}
	<a href="{gallery->url view=core:ShowItem itemId=$parents[parent].id}">
	  {if $parents[parent].title}
	  {$parents[parent].title}
	  {else}
	  {$parents[parent].pathComponent}
	  {/if}
	</a>
	&nbsp;
	<a href="{gallery->url view=core:ShowItem itemId=$parents[parent].id}">
	  <img src="{$layoutUrl}/images/nav_home.gif" alt="{gallery->text text="up"}"
	    width="13" height="11" border="0">
	</a>
	{/strip}
	:: 
	{/section}
	{if empty($item.title)}
	{$item.pathComponent}
	{else}
	{$item.title}
	{/if}
      </td>
    </tr>
  </table>
