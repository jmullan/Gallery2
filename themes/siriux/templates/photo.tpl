{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !empty($theme.imageViews)}
{assign var="image" value=$theme.imageViews[$theme.imageViewsIndex]}
{/if}
<div id="gsContent">
  <div class="gbBlock">
    {if !empty($theme.item.title)}
      <h2> {$theme.item.title|markup} </h2>
    {/if}
    {if !empty($theme.item.description)}
    <p class="giDescription">
      {$theme.item.description|markup}
    </p>
    {/if}
    {g->block type="core.PhotoSizes" class="giInfo"}
  </div>

  <div id="gsImageView" class="gbBlock">
    {if !empty($theme.imageViews)}
      {capture name="fallback"}
      <a href="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$theme.item.id`"}">
	{g->text text="Download %s" arg1=$theme.sourceImage.itemTypeName.1}
      </a>
      {/capture}

      {if ($image.viewInline)}
	{g->image item=$theme.item image=$image maxSize=690 fallback=$smarty.capture.fallback}
      {else}
	{$smarty.capture.fallback}
      {/if}
    {else}
      {g->text text="There is nothing to view for this item."}
    {/if}
  </div>

  {* Download link for item in original format *}
  {if !empty($theme.sourceImage) && $theme.sourceImage.mimeType != $theme.item.mimeType}
  <div class="gbBlock">
    <a href="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$theme.item.id`"}">
      {g->text text="Download %s in original format" arg1=$theme.sourceImage.itemTypeName.1}
    </a>
  </div>
  {/if}

  {if !empty($theme.navigator)}
  <div class="gbBlock gbNavigator">
    {g->callback type="core.LoadPeers" item=$theme.item windowSize=1}
    {g->block type="core.Navigator" navigator=$theme.navigator prefix="&laquo; " suffix=" &raquo;"
     currentItem=$block.core.LoadPeers.thisPeerIndex totalItems=$block.core.LoadPeers.peerCount}
  </div>
  {/if}

  {* Show any other photo blocks (comments, exif etc) *}
  {foreach from=$theme.params.photoBlocks item=block}
    {g->block type=$block.0 params=$block.1}
  {/foreach}

  {g->block type="core.GuestPreview" class="gbBlock"}

  {* Our emergency edit link, if the user all blocks containing edit links *}
  {g->block type="core.EmergencyEditItemLink" class="gbBlock" checkPhotoBlocks=true}
</div>
