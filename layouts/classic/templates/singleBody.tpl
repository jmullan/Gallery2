  <table border="1" width="100%" cellspacing="0%" cellpadding="0%">
    <tr>
      <td>
	<table border="1" width="100%" cellspacing="0%" cellpadding="0%">
	  <tr>
	    <td align="right">
	      {foreach from=$moduleSystemLinks item=module}
	      {foreach from=$module item=link}
	      <a href="{$link.url}">[{$link.text}]</a>
	      {/foreach}
	      {/foreach}

	      {foreach from=$moduleItemLinks item=module}
	      {foreach from=$module item=link}
	      <a href="{$link.url}">[{$link.text}]</a>
	      {/foreach}
	      {/foreach}
	    </td>
	  </tr>
	</table>
      </td>
    </tr>

    <tr>
      <td>
	{include file="parents.tpl"}
      </td>
    </tr>

    <tr>
      <td width="100%">
	{include file="itemNavigator.tpl"}
      </td>
    </tr>

    <tr>
      <td>
	<table border="1" width="100%" cellspacing="0%" cellpadding="0%">
	  <tr>
	    <td align=center>
	      <a href="{galleryUrl view=core:ShowItem itemId=$item.id resizeIndex=$nextResizeIndex}">
		<img src="{galleryUrl view=core:DownloadItem itemId=$image.id}"
		  {if ($image.width && $image.height)}
		  width="{$image.width}"
		  height="{$image.height}"
		  {/if}
		  >
	      </a>
	    </td>
	  </tr>
	</table>
      </td>
    </tr>

    <tr>
      <td>
	{if empty($item.description)}
	{galleryText text="This item has no description"}
	{else}
	{$item.description}
	{/if}
      </td>
    </tr>

    <tr>
      <td width="100%">
	{include file="itemNavigator.tpl"}
      </td>
    </tr>

    <tr>
      <td>
	{include file="parents.tpl"}
      </td>
    </tr>
  </table>

