      {galleryLightFrame width="100%"}
    <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
	<tr>
	  <td>
	    <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
		<tr>
		  <td colspan="2" align="right">
		    {foreach from=$moduleSystemContent item=module}
		    {foreach from=$module item=content}
		    {$content}
		    {/foreach}
		    {/foreach}
		  </td>
		</tr>
		<tr>	
		  <td>
		    {foreach from=$moduleItemLinks item=module}
		    {foreach from=$module item=links}
		    {foreach from=$links item=link}
		    <a href="{$link.url}">[{$link.text}]</a>
		    {/foreach}
		    {/foreach}
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
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td>
	    <table border="0" width="100%" cellspacing="0%" cellpadding="0%">
		<tr>
		  <td align=center>
		    {strip}
		    {assign var="image" value=$imageViews.$imageViewsIndex}

		    {if ($image.inline)}
		    {galleryThinFrame}
		    <img src="{galleryUrl view=core:DownloadItem itemId=$image.id}"
		    {if ($image.width && $image.height)}
		         width="{$image.width}"
		         height="{$image.height}"
		    {/if}
		         border="0"
		    >
		    {/galleryThinFrame}
		    {else}
		    <a href="{galleryUrl view=core:DownloadItem itemId=$image.id}">
		    {galleryText text="Download this item"} 
		    </a>
		    {/if}
		    {/strip}
		  </td>
		</tr>
		<tr>
		  <td>
		    &nbsp;
		  </td>
		</tr>
		<tr>
		  <td align="center">
		    {strip}
		    {section name=imageView loop=$imageViews}
		    {if $smarty.section.imageView.index != $imageViewsIndex}
		    <a href="{galleryUrl view=core:ShowItem itemId=$item.id imageViewsIndex=$smarty.section.imageView.index}">
		      {else}
		      <b>
			{/if}

			{if $imageViews[imageView].inline}
			[
			{if empty($imageViews[imageView].width)}
			{galleryText text="??? x ???"}
			{else}
			{galleryText text="%d x %d" arg1=$imageViews[imageView].width arg2=$imageViews[imageView].height}
			{/if}
			]
			{/if}

			{if $smarty.section.imageView.index == $imageViewsIndex}
		      </b>
		      {else}
		    </a>
		    {/if}

		    {if empty($smarty.section.imageView.last)}
		    &nbsp;
		    {/if}

		    {/section}
		    {/strip}
		  </td>
		</tr>
	    </table>
	  </td>
	</tr>

	<tr>
	  <td>
	    &nbsp;
	  </td>
	</tr>

	<tr>
	  <td align="center">
	    {if !empty($item.title)}
	    <b>{$item.title}</b>
	    <p>
	      {/if}

	      {if !empty($item.description)}
	      {$item.description}
	      {/if}
	    <p>
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
