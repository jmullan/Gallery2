{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to singleBody.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{* Jump through hoops because "$layout.imageViews.`$layout.imageViewsIndex`" doesn't work *}
{assign var="currentIndex" value=$layout.imageViewsIndex}
{if !empty($layout.imageViews)}
{assign var="image" value=$layout.imageViews.$currentIndex}
{/if}
      
{include file="gallery:layouts/matrix/templates/pathbar.tpl"}  

<div id="gsContents">
  {include file="gallery:layouts/matrix/templates/sidebar.tpl"} 
  
  <div id="gsAlbumContents">
    <div class="gbTopFlag">
      <table class="gbTitleBanner">
        <tr>
          <td>
            <h1 class="giTitle">
              {$layout.item.title|markup}
            </h1>
            <p class="giDescription">
              {$layout.item.description|markup}
            </p>
          </td>
          <td>
            <ul class="giInfo">
              <li>
                {if !empty($layout.useCaptureDate) && isset($layout.captureTimestamp)}
                {capture name=captureTimestamp}{g->date timestamp=$layout.captureTimestamp}{/capture}
                {g->text text="Date: %s" arg1=$smarty.capture.captureTimestamp}
                {else}
                {capture name=creationTimestamp}{g->date timestamp=$layout.item.creationTimestamp}{/capture}
                {g->text text="Date: %s" arg1=$smarty.capture.creationTimestamp}
                {/if}
              </li>
        
              {if sizeof($layout.imageViews) > 1}
              <li>
                {g->text text="Size: "}
                <select onchange="{literal}javascript:if (this.value) { newLocation = this.value; this.options[0].selected = true; location.href= newLocation; }{/literal}">
                  {section name=imageView loop=$layout.imageViews}
                  {if $smarty.section.imageView.index == $layout.imageViewsIndex}
                  {assign var="selected" value="selected=\"selected\""}
                  {else}
                  {assign var="selected" value=""}
                  {/if}
        
                  <option {$selected} value="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`" arg3="imageViewsIndex=`$smarty.section.imageView.index`"}">
                    {if empty($layout.imageViews[imageView].width)}
                      {if isset($layout.imageViews[imageView].isSource)}
                      {g->text text="Source"}
                      {else}
                      {g->text text="Unknown"}
                      {/if}
                    {else}
                    {g->text text="%dx%d" arg1=$layout.imageViews[imageView].width arg2=$layout.imageViews[imageView].height}
                    {/if}
                  </option>
                  {/section}
                </select>
              </li>
              {/if}
        
              {if !empty($layout.sourceImage)}
              <li>
                {g->text text="Full size: "}
                {capture name="fullSize"}
                {if empty($layout.sourceImage.width)}
                {$layout.sourceImage.itemTypeName.0}
                {else}
                {g->text text="%dx%d" arg1=$layout.sourceImage.width arg2=$layout.sourceImage.height}
                {/if}
                {/capture}
                {if sizeof($layout.imageViews) > 1}
                <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$layout.item.id`" arg3="imageViewsIndex=`$layout.sourceImageViewIndex`"}">{$smarty.capture.fullSize}</a>
                {else}
                {$smarty.capture.fullSize}
                {/if}
              </li>
              {/if}

              {if $layout.showImageOwner}
              <li>
                {g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}
              </li>
              {/if}
            </ul>
          </td>
        </tr>
      </table>
    </div>

    <div class="gbNavBar">
      {include file="gallery:layouts/matrix/templates/itemNavigator.tpl"}
    </div>

    <div class="gsSingleImage">
      {if !empty($layout.imageViews)}
      {capture name="fallback"}
      <a href="{g->url arg1="view=core:DownloadItem" arg2="itemId=`$layout.item.id`"}">
        {g->text text="Download this %s" arg1=`$layout.sourceImage.itemTypeName.1`} 
      </a>
      {/capture}

      {if ($layout.can.viewInline.$currentIndex)}
	{if isset($layout.frame)}
	  {include file=$layout.frame.template ImageFrame_data=$layout.frame.data
		   ImageFrame_frame=$layout.frame.photoFrame item=$layout.item image=$image}
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

    {if !empty($layout.moduleItemDetailFiles)}
    {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
    {include file="gallery:$detailFile" l10Domain="modules_$moduleId"}
    {/foreach}
    {/if}

    <div class="gbBottomFlag">
      <div class="gbNavBar">
        {include file="gallery:layouts/matrix/templates/itemNavigator.tpl"}
      </div>
    </div>
  </div>
</div>
