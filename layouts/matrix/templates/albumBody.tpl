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
	    {gallery->text one="Size: %d item" many="Size: %d items" count=$layout.totalChildCount arg1=$layout.totalChildCount}
	  {/gallery->item}

	  {gallery->item}
	    {gallery->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
	  {/gallery->item}
	{/gallery->infobox}

	{include file="layouts/matrix/templates/itemNavigator.tpl"}

      {/gallery->component}
    {/gallery->bannerbox}

    {gallery->simplebox}
      {gallery->body}
	{foreach from=$layout.children item=child}
	  {strip}
	    {gallery->link url_view="core:ShowItem" url_itemId=$child.id}
	      {gallery->image item=$child image=$child.thumbnail}
	    {/gallery->link url_view="core:ShowItem" url_itemId=$child.id}
	  {/strip}
	{/foreach}
      {/gallery->body}
    {/gallery->simplebox}

    {gallery->bannerbox}
      {gallery->component}
	{gallery->simplebox}
	  {gallery->body}
	    {foreach from=$layout.moduleItemLinks item=itemLinks key=loopId}
	      {if ($loopId == $layout.item.id)}
		{gallery->select onChange="if (this.value) javascript:location.href=this.value"}
		  <option value=""> {gallery->text text="&laquo; manage album &raquo;"}
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

	{gallery->linksbox}
	  {gallery->item}
	    {gallery->text text="Page"}
	  {/gallery->item}
	  
	  {foreach name=jumprange from=$layout.jumprange item=page}
	    {if ($page - $lastPage > 1)}
	      {gallery->item}
		...
	      {/gallery->item}
	    {/if}
	    
	    {if ($layout.currentPage == $page)}
	      {gallery->item}
		{$page}
	      {/gallery->item}
	    {else}
	      {gallery->item}
		{gallery->link url_view="core:ShowItem" url_itemId=$layout.item.id url_page=$page}
		  {$page}
		{/gallery->link}
	      {/gallery->item}
	    {/if}
	    {assign var="lastPage" value=$page}
	  {/foreach}
	{/gallery->linksbox}

      {/gallery->component}
    {/gallery->bannerbox}
  {/gallery->component}
{/gallery->main}
