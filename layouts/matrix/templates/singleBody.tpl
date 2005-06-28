{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !empty($layout.imageViews)}
{assign var="image" value=$layout.imageViews[$layout.imageViewsIndex]}
{/if}

{include file="gallery:layouts/matrix/templates/pathbar.tpl"}

<table width="100%" cellspacing="0" cellpadding="0">
  <tr valign="top"><td id="gsSidebarCol">
    {include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"}
  </td><td>

  <div id="gsContent">
    <div class="gbBlock gcBackground1">
      <table width="100%">
	<tr><td style="width: 40%">
	  {if !empty($layout.item.title)}
	    <h2> {$layout.item.title|markup} </h2>
	  {/if}
	  {if !empty($layout.item.description)}
	    <p class="giDescription">
	      {$layout.item.description|markup}
	    </p>
	  {/if}
	</td><td>
	  <p class="giInfo">
	    {capture name=itemTimestamp}
	      {g->date timestamp=$layout.item.originationTimestamp}
	    {/capture}
	    {g->text text="Date: %s" arg1=$smarty.capture.itemTimestamp}
	    <br/>

	    {if count($layout.imageViews) > 1}
	      {g->text text="Size: "}
	      <select onchange="{literal}if (this.value) { newLocation = this.value; this.options[0].selected = true; location.href= newLocation; }{/literal}">
	      {section name=imageView loop=$layout.imageViews}
		<option value="{g->url arg1="view=core.ShowItem" arg2="itemId=`$layout.item.id`"
		 arg3="imageViewsIndex=`$smarty.section.imageView.index`"}"{if
		 $smarty.section.imageView.index==$layout.imageViewsIndex} selected="selected"{/if}>
		  {if empty($layout.imageViews[imageView].width)}
		    {if isset($layout.imageViews[imageView].isSource)}
		      {g->text text="Source"}
		    {else}
		      {g->text text="Unknown"}
		    {/if}
		  {else}
		    {g->text text="%dx%d" arg1=$layout.imageViews[imageView].width
			     arg2=$layout.imageViews[imageView].height}
		  {/if}
		</option>
	      {/section}
	      </select>
	      <br/>
	    {/if}

	    {if !empty($layout.sourceImage)}
	      {g->text text="Full size: "}
	      {capture name="fullSize"}
		{if empty($layout.sourceImage.width)}
		  {$layout.sourceImage.itemTypeName.0}
		{else}
		  {g->text text="%dx%d" arg1=$layout.sourceImage.width
			   arg2=$layout.sourceImage.height}
		{/if}
	      {/capture}
	      {if count($layout.imageViews) > 1}
		<a href="{g->url arg1="view=core.ShowItem" arg2="itemId=`$layout.item.id`"
		 arg3="imageViewsIndex=`$layout.sourceImageViewIndex`"}">
		  {$smarty.capture.fullSize}
		</a>
	      {else}
		{$smarty.capture.fullSize}
	      {/if}
	      <br/>
	    {/if}

	    {if $layout.params.showImageOwner}
	      {g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
	      <br/>
	    {/if}
	  </p>
	</td></tr>
      </table>
    </div>

    {include file="gallery:layouts/matrix/templates/itemNavigator.tpl"}

    <div id="gsImageView" class="gbBlock">
    {if !empty($layout.imageViews)}
      {capture name="fallback"}
      <a href="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$layout.item.id`"}">
	{g->text text="Download %s" arg1=$layout.sourceImage.itemTypeName.1}
      </a>
      {/capture}

      {if ($layout.viewInline[$layout.imageViewsIndex])}
	{if isset($layout.photoFrame)}
	  {g->block type="imageframe" frame=$layout.photoFrame}
	    {g->image item=$layout.item image=$image id="%ID%" class="%CLASS%"}
	  {/g->block}
	{else}
	  {g->image item=$layout.item image=$image fallback=$smarty.capture.fallback}
	{/if}
      {else}
	{$smarty.capture.fallback}
      {/if}
    {else}
      {g->text text="There is nothing to view for this item."}
    {/if}
    </div>

    {* Download link for item in original format *}
    {if !empty($layout.sourceImage) && $layout.sourceImage.mimeType != $layout.item.mimeType}
    <div class="gbBlock">
      <a href="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$layout.item.id`"}">
	{g->text text="Download %s in original format" arg1=$layout.sourceImage.itemTypeName.1}
      </a>
    </div>
    {/if}

    {if !empty($layout.itemDetailFiles)}
      {foreach from=$layout.itemDetailFiles key=moduleId item=detailFile}
	{include file="gallery:$detailFile" l10Domain="modules_$moduleId"}
      {/foreach}
    {/if}

    {include file="gallery:layouts/matrix/templates/itemNavigator.tpl"}
    {include file="gallery:layouts/matrix/templates/guestPreviewModeSwitch.tpl"}
  </div>
  </td></tr>
</table>
