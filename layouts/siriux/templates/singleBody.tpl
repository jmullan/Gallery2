{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{include file="gallery:layouts/siriux/templates/pathbar.tpl"}

<div class="gbBlock">
  <h2> {$layout.item.title|markup} </h2>

  {if !empty($layout.imageViews)}
    {capture name="fallback"}
    <a href="{g->url arg1="view=core:DownloadItem" arg2="itemId=`$layout.item.id`"}">
      {g->text text="Download this item"}
    </a>
    {/capture}

    {if ($layout.viewInline[$layout.imageViewsIndex])}
      <div class="gallery-photo">
	{g->image item=$layout.item image=$layout.imageViews[$layout.imageViewsIndex]
		  fallback=$smarty.capture.fallback class="gcBorder1"}
      </div>
    {else}
      {$smarty.capture.fallback}
    {/if}
  {else}
    {g->text text="There is nothing to view for this item."}
  {/if}

  <!-- Meta information -->
  <p class="note" style="padding: 0 50px">
    {if $layout.item.originationTimestamp}
      {g->text text="Date:"}
      {g->date timestamp=$layout.item.originationTimestamp}
    {/if}
    {if $layout.params.showImageOwner}
      {g->text text="Owner:"}
      {$layout.owner.fullName|default:$layout.owner.userName}
    {/if}
  </p>

  <!-- Description -->
  {if ($layout.item.description != $layout.item.title)}
    <p class="giDescription" style="padding: 0 50px"> {$layout.item.description|markup} </p>
  {/if}

  <!-- Download -->
  {if count($layout.imageViews) > 1}
    {if !empty($layout.sourceImage)}
      <p style="padding: 0 50px;">
	<a href="{g->url arg1="view=core:DownloadItem" arg2="itemId=`$layout.item.id`"}">
	  {g->text text="Download picture"}
	  {if !empty($layout.sourceImage.width)}
	    ({g->text text="%dx%d" arg1=$layout.sourceImage.width arg2=$layout.sourceImage.height})
	  {/if}
	</a>
      </p>
    {/if}
  {/if}
</div>

{include file="gallery:layouts/siriux/templates/itemNavigator.tpl"}

{include file="gallery:layouts/siriux/templates/itemLinks.tpl"}

