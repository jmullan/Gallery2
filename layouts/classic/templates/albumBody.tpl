  {galleryLightFrame width="100%"}
  <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
    <tr>
      <td>
	<table border="0" width="100%" cellspacing="0%" cellpadding="0%">
	  <tr>
	    <td>
	      {galleryText one="%d item in this album" 
	                   many="%d items in this album"
	                   count=$totalChildCount
	                   arg1=$totalChildCount}
	      {if $totalPageCount > 1}
	      {galleryText text="on %d pages" arg1=$totalPageCount}
	      {/if}
	    </td>
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
	<table border="0" width="100%">
	  {counter assign=child start=0 print=false}
	  {section name=outer loop=$children step=$properties.columns}
	  <tr>
	    {section name=inner loop=$children start=$child max=$properties.columns}
	    <td valign="top" align="center">
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

    <!-- Module Item Details for the active item -->
    {if !empty($moduleItemDetails)}
    {foreach from=$moduleItemDetails key=moduleName item=detail}
    <tr>
      <td width="100%">
	{$detail}
      </td>
    </tr>
    {/foreach}
    {/if}

  </table>
  {/galleryLightFrame}
