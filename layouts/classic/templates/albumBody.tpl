  <table border="1" width="100%" cellspacing="0%" cellpadding="0%">
    <tr>
      <td>
	<table border="1" width="100%" cellspacing="0%" cellpadding="0%">
	  <tr>
	    <td>
	      {galleryText text="%d items in this album" arg1=$totalChildCount}
	      {if $totalPageCount > 1}
	      {galleryText text="on %d pages" arg1=$totalPageCount}
	      {/if}
	    </td>
	    <td align="right">
	      {foreach from=$moduleItemLinks item=module}
	      {foreach from=$module item=link}
	      [<a href="{$link.url}">{$link.text}</a>]
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

    {if !empty($navigator.jumprange)}
    <tr>
      <td width="100%">
	{include file="pageNavigator.tpl"}
      </td>
    </tr>
    {/if}

    {if !empty($item.description)}
    <tr>
      <td>
	{$item.description}
      </td>
    </tr>
    {/if}

    <tr>
      <td>
	<table width="100%">
	  {counter assign=child start=0 print=false}
	  {section name=outer loop=$children step=$properties.columns}
	  <tr>
	    {section name=inner loop=$children start=$child max=$properties.columns}
	    <td align="center">
	      {if $children[$child].entityType == 'galleryalbumitem'}
	      {include file="albumThumbnail.tpl"}
	      {else}
	      {include file="singleThumbnail.tpl"}
	      {/if}
	      {counter}
	    </td>
	    {/section}
	  </tr>
	  {/section}
	</table>
      </td>
    </tr>

    {if !empty($navigator.jumprange)}
    <tr>
      <td width="100%">
	{include file="pageNavigator.tpl"}
      </td>
    </tr>
    {/if}

    <tr>
      <td>
	{include file="parents.tpl"}
      </td>
    </tr>
  </table>
