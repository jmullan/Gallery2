{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ExifItemDetails.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div style="gbExif">
  <div class="giTitle">
    {g->text text="Photo Properties"}
  </div>

  {if isset($ExifItemDetails.mode)}
  <div class="giSubtitle">
    <div class="giHorizontalLinks">
      <span>
	{if ($ExifItemDetails.mode == 'summary')}
	{g->text text="summary"}
	{else}
	<a href="{g->url arg1="return=true" arg2="controller=exif:SwitchDetailMode" arg3="mode=summary"}">
	  {g->text text="summary"}
	</a>
	{/if}
      </span>

      <span>
	{if ($ExifItemDetails.mode == 'detailed')}
	{g->text text="details"}
	{else}
	<a href="{g->url arg1="return=true" arg2="controller=exif:SwitchDetailMode" arg3="mode=detailed"}">
	  {g->text text="details"}
	</a>
	{/if}
      </span>
    </div>
  </div>
  {/if}

  {if !empty($ExifItemDetails.exifData)}
  <table class="gbDataTable">
    {section name=outer loop=$ExifItemDetails.exifData step=2}
    <tr class="{cycle values="gbEven,gbOdd"}">
      {section name=inner loop=$ExifItemDetails.exifData start=$smarty.section.outer.index max=2}
      <td>
	{g->text text=$ExifItemDetails.exifData[inner].title}
      </td>
      <td>
	{$ExifItemDetails.exifData[inner].value}
      </td>
      {/section}
    </tr>
    {/section}
  </table>
  {/if}
</div>
