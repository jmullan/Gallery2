{* Jump through hoops because "$layout.imageViews.`$layout.imageViewsIndex`" doesn't work *}
{assign var="currentIndex" value=$layout.imageViewsIndex}
{assign var="image" value=$layout.imageViews.$currentIndex}

{gallery->main}
  {include file="layouts/matrix/templates/pathbar.tpl"}
  {include file="layouts/matrix/templates/sidebar.tpl"}

  {gallery->component}
    {gallery->bannerbox}
      {gallery->title}
	{$layout.item.title}
      {/gallery->title}
      {gallery->description}
	{$layout.item.summary}
      {/gallery->description}

      {gallery->component}
	{gallery->infobox}
	  {gallery->item}
	    {capture name=creationTimestamp}
	      {gallery->date timestamp=$layout.item.creationTimestamp}
	    {/capture}
	    {gallery->text text="Date: %s" arg1=$smarty.capture.creationTimestamp}
	  {/gallery->item}

	  {gallery->item}
	    {gallery->text text="Size: "}
	    {gallery->select onChange="if (this.value) javascript:location.href=this.value"}
	      {section name=imageView loop=$layout.imageViews}
		{if $smarty.section.imageView.index != $layout.imageViewsIndex}
		  <option value="{gallery->url view="core:ShowItem" itemId=$layout.item.id imageViewsIndex=$smarty.section.imageView.index}">
		{else}
		  <option value="{gallery->url view="core:ShowItem" itemId=$layout.item.id imageViewsIndex=$smarty.section.imageView.index}" SELECTED>		  
		{/if}
		{gallery->text text="%dx%d" arg1=$layout.imageViews[imageView].width arg2=$layout.imageViews[imageView].height}
	      {/section}
	    {/gallery->select}
	  {/gallery->item}

	  {if !empty($layout.sourceImage)}
	    {gallery->item}
	      {gallery->text text="Full size: "}
	      {gallery->link url_view="core:ShowItem" url_itemId=$layout.item.id url_imageViewsIndex=$layout.sourceImageViewIndex}
		{gallery->text text="%dx%d" arg1=$layout.sourceImage.width arg2=$layout.sourceImage.height}
	      {/gallery->link}
	    {/gallery->item}
	  {/if}

	  {gallery->item}
	    {gallery->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
	  {/gallery->item}
	{/gallery->infobox}

	{include file="layouts/matrix/templates/itemNavigator.tpl"}

      {/gallery->component}
    {/gallery->bannerbox}

    {gallery->imagebox}
      {gallery->description}
	{$layout.item.description}
      {/gallery->description}
      {gallery->body}
	{if ($layout.can.viewInline.$currentIndex)}
	  {gallery->image item=$layout.item image=$image}
	{else}
	  {gallery->link url_view="core:DownloadItem" url_itemId=$image.id}
	    {gallery->text text="Download this item"} 
	  {/gallery->link}
	{/if}
      {/gallery->body}
    {/gallery->imagebox}

    {if !empty($layout.moduleItemDetailFiles)}
      {foreach from=$layout.moduleItemDetailFiles key=moduleName item=detailFile}
	{gallery->simplebox}
	  {gallery->body}
	    {include file=$detailFile l10Domain="module_$moduleName"}
	  {/gallery->body}
	{/gallery->simplebox}
      {/foreach}
    {/if}

    {gallery->bannerbox}
      {gallery->component}
	{gallery->simplebox}
	  {gallery->body}
	    {foreach from=$layout.moduleItemLinks item=itemLinks key=loopId}
	      {if ($loopId == $layout.item.id)}
		{gallery->select onChange="if (this.value) javascript:location.href=this.value"}
		  <option value=""> {gallery->text text="&laquo; edit item &raquo;"}
		  {foreach from=$itemLinks item=module}
		    {foreach from=$module item=link}
		      <option value="{$link.url}"> {$link.text}
		    {/foreach}
		  {/foreach}
		{/gallery->select}
	      {/if}
	    {/foreach}
	  {/gallery->body}
	{/gallery->simplebox}

	{include file="layouts/matrix/templates/itemNavigator.tpl"}

      {/gallery->component}
    {/gallery->bannerbox}

  {/gallery->component}
{/gallery->main}
