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

<div id="gsContents">
  {include file="gallery:templates/sidebar.tpl" l10Domain="modules_core"} 
  
  <div id="gsAlbumContents">
    <div class="gbTopFlag">
      <table class="gbTitleBanner">
        <tr>
          <td>
            {if !empty($layout.item.title)}
            <h1 class="giTitle">
              {$layout.item.title|markup}
            </h1>
            {/if}
            {if !empty($layout.item.description)}
            <p class="giDescription">
              {$layout.item.description|markup}
            </p>
	    {/if}
          </td>
          <td>
            <ul class="giInfo">
              <li>
                {capture name=itemTimestamp}{g->date timestamp=$layout.item.originationTimestamp}{/capture}
                {g->text text="Date: %s" arg1=$smarty.capture.itemTimestamp}
              </li>
        
              {if count($layout.imageViews) > 1}
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
                {if count($layout.imageViews) > 1}
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

      {if ($layout.can.viewInline[$layout.imageViewsIndex])}
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

    {if !empty($layout.itemDetailFiles)}
    {foreach from=$layout.itemDetailFiles key=moduleId item=detailFile}
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
