      {gallery->lightFrame width="100%"}
    <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
	<tr>
	  <td>
	    <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
		<tr>
		  <td>
		    {gallery->text one="%d item in this album" 
	                         many="%d items in this album"
	                         count=$totalChildCount
	                         arg1=$totalChildCount}
		    {if $totalPageCount > 1}
		    {gallery->text text="on %d pages" arg1=$totalPageCount}
		    {/if}
		  </td>
		  <td align="right">
		    {foreach from=$moduleSystemContent item=module}
		    {foreach from=$module item=content}
		    {$content}
		    {/foreach}
		    {/foreach}
		  </td>
		</tr>
		<tr>	
		  <td>
		    {foreach from=$moduleItemLinks item=itemLinks key=loopId}
		    {if ($loopId == $item.id)}
		    {foreach from=$itemLinks item=module}
		    {foreach from=$module item=link}
		    <a href="{$link.url}">[{$link.text}]</a>
		    {/foreach}
		    {/foreach}
		    {/if}
		    {/foreach}
		  </td>
		  <td align="right">
		    {foreach from=$moduleSystemLinks item=module}
		    {foreach from=$module item=link}
		    <a href="{$link.url}">[{$link.text}]</a>
		    {/foreach}
		    {/foreach}
		  </td>
		</tr>
	    </table>
	  </td>
	</tr>

    {if !empty($item.description)}
    <tr>
      <td>
	{$item.description}
      </td>
    </tr>
    {/if}

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

    <tr>
      <td>
	<table border="0" width="100%">
	  <!-- {counter assign=childIndex start=0 print=false} -->
	  <!-- {section name=outer loop=$children step=$properties.columns} -->
	    <tr>
	      <!-- {section name=inner loop=$children start=$childIndex max=$properties.columns} -->
	      <!-- {assign var=child value=$children[$childIndex]} -->
	      <td valign="center" align="center">
		{if $child.entityType == 'galleryalbumitem'}
		{include file="albumThumbnail.tpl"}
		{else}
		{include file="singleThumbnail.tpl"}
		{/if}

		{if !empty($child.title)}
		<br>
		<b>{$child.title}</b>
		{else}
		&nbsp;
		{/if}
		
		{if !empty($child.summary)}
		<br>
		<i>{$child.summary}</i>
		{else}
		&nbsp;
		{/if}

		{if !empty($child.childCount)}
		<br>
		{gallery->smallerFontSize}
		{gallery->text one="This album contains %d item"
                             many="This album contains %d items"
                             count=$child.childCount
                             arg1=$child.childCount}
		{/gallery->smallerFontSize}
		{else}
		&nbsp
		{/if}
		
		{if (!empty($child.moduleSummaries)) }
		{foreach from=$child.moduleSummaries item=summary}
		<br>
		{$summary}
		{/foreach}
		{/if}
	      </td>
	      <!-- {counter} -->
	      <!-- {/section} -->
	    </tr>
	    <!-- {/section} -->
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
    {/gallery->lightFrame}
