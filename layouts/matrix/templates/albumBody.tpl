{g->main}
  {include file="layouts/matrix/templates/pathbar.tpl"}
  {include file="layouts/matrix/templates/sidebar.tpl"}

  {g->pagebox}
    {g->banner}
      {g->title}
	{$layout.item.title}
      {/g->title}
      {g->description}
	{$layout.item.summary}
      {/g->description}

      {g->infoset}
	{g->item}
	  {g->title}
	    {capture name=creationTimestamp}
	      {g->date timestamp=$layout.item.creationTimestamp}
	    {/capture}
	    {g->text text="Date: %s" arg1=$smarty.capture.creationTimestamp}
	  {/g->title}
	{/g->item}

	{g->item}
	  {g->title}
	    {g->text one="Size: %d item" many="Size: %d items" count=$layout.totalChildCount arg1=$layout.totalChildCount}
	  {/g->title}
	{/g->item}
	
	{g->item}
	  {g->title}
	    {g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
	  {/g->title}
	{/g->item}
      {/g->infoset}

      {include file="layouts/matrix/templates/itemNavigator.tpl"}
    {/g->banner}

    {g->box style="canvas"}
      
      {g->element}
	{g->table style="canvas"}
	  {foreach from=$layout.childRows item=childRow}
	    {g->row}
	      {foreach from=$childRow item=child}
		{assign var="childId" value=$child.id}
		{if $child.canContainChildren} 
		  {assign var="style" value="album"}
		  {assign var="colspan" value=$layout.columnSize}
		{else}
		  {assign var="style" value="item"}
		  {assign var="colspan" value="1"}
		{/if}
		{g->column colspan=$colspan}
		  {g->itemthumbnail style=$style}
		    {g->title}
		      {if $child.canContainChildren}
			{g->text text="Album: %s" arg1=$child.title|default:$child.pathComponent}
		      {else}
			{$child.title|default:$child.pathComponent}
		      {/if}
		    {/g->title}
		    {g->description}
		      {$child.description|truncate:512}
		    {/g->description}
		    {g->media}
		      {g->link arg1="view=core:ShowItem" arg2="itemId=`$child.id`"}
			{if isset($child.thumbnail)}
			  {g->image item=$child image=$child.thumbnail}
			{else}
			  {g->text text="no thumbnail"}
			{/if}
		      {/g->link arg1="view=core:ShowItem" arg2="itemId=`$child.id`"}
		    {/g->media}
		    {g->infoset}
		      {g->item}
			{capture name=modificationTimestamp}
			  {g->date timestamp=$child.modificationTimestamp}
			{/capture}
			{g->title}
			  {g->text text="Date: %s" arg1=$smarty.capture.modificationTimestamp}
			{/g->title}
		      {/g->item}

		      {g->item}
			{g->title}
			  {assign var="ownerId" value=$child.ownerId}
			  {assign var="owner" value=$layout.owners.$ownerId}
			  {g->text text="Owner: %s" arg1=$owner.fullName|default:$owner.userName}
			{/g->title}
		      {/g->item}

		      {g->item}
			{g->title}
			  {g->text one="Size: %d item"
			  many="Size: %d items"
			  count=$child.childCount
			  arg1=$child.childCount}
			{/g->title}
		      {/g->item}

		      {g->item}
			{g->title}
			  {g->text one="Viewed: %d time"
			  many="Viewed: %d times"
			  count=$layout.viewCounts.$childId
			  arg1=$layout.viewCounts.$childId}
			{/g->title}
		      {/g->item}
		    {/g->infoset}

		    {if !empty($layout.moduleItemLinks.$childId)}
		      {g->actionset}
			{g->actionitem}
			  {g->title}
			    {if $child.canContainChildren} 
			      {g->text text="&laquo; album actions &raquo;"}
			    {else}
			      {g->text text="&laquo; item actions &raquo;"}
			    {/if}
			  {/g->title}
			  {g->value}
			    &nbsp;
			  {/g->value}
			{/g->actionitem}
			{foreach from=$layout.moduleItemLinks.$childId item=link}
			  {g->actionitem}
			    {g->title}
			      {$link.text}
			    {/g->title}
			    
			    {g->value}
			      {$link.url}
			    {/g->value}
			  {/g->actionitem}
			{/foreach}
		      {/g->actionset}
		    {/if}
		  {/g->itemthumbnail}
		{/g->column}
	      {/foreach}
	    {/g->row}
	  {foreachelse}
	    {g->row}
	      {g->column align="center"}
		{g->text text="This album is empty"}
	      {/g->column}
	    {/g->row}
	  {/foreach}
	{/g->table}
      {/g->element}
    {/g->box}

    {if !empty($layout.moduleItemDetailFiles)}
      {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
	{g->box}
	  {include file=$detailFile l10Domain="modules_$moduleId"}
	{/g->box}
      {/foreach}
    {/if}

    {g->banner}
      {assign var="id" value=$layout.item.id}
      {if isset($layout.moduleItemLinks.$id)}
	{g->actionset}
	  {g->actionitem}
	    {g->title}
	      {g->text text="&laquo; album actions &raquo;"}
	    {/g->title}
	    {g->value}
	      &nbsp;
	    {/g->value}
	  {/g->actionitem}
	  {foreach from=$layout.moduleItemLinks.$id item=link}
	    {g->actionitem}
	      {g->title}
		{$link.text}
	      {/g->title}
	      
	      {g->value}
		{$link.url}
	      {/g->value}
	    {/g->actionitem}
	  {/foreach}
	{/g->actionset}
      {/if}

      {g->linkset}
	{g->title}
	  {g->text text="Page"}
	{/g->title}
	
	{assign var="lastPage" value=0}
	{foreach name=jumprange from=$layout.jumprange item=page}
	  {if ($page - $lastPage > 1)}
	    {g->item}
	      {g->title}
		...
	      {/g->title}
	    {/g->item}
	  {/if}
	  
	  {if ($layout.currentPage == $page)}
	    {g->item}
	      {g->title}
		{$page}
	      {/g->title}
	    {/g->item}
	  {else}
	    {g->item}
	      {g->title}
		{g->link arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`" arg3="page=$page"}
		  {$page}
		{/g->link}
	      {/g->title}
	    {/g->item}
	  {/if}
	  {assign var="lastPage" value=$page}
	{/foreach}
      {/g->linkset}

    {/g->banner}
  {/g->pagebox}
{/g->main}
