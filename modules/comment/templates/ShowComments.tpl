  <center>
    {if !empty($thumbnail)}
    <img src="{galleryUrl view='core:DownloadItem' itemId=$thumbnail.id}"
      {if $thumbnail.width} width="{$thumbnail.width}" {/if}
      {if $thumbnail.height} height="{$thumbnail.height}" {/if}
      >
      {else}
      {galleryBigFont}
      {galleryText text="There is no thumbnail for this item"}
      {/galleryBigFont}
    {/if}
    <br>
    <a href="{galleryUrl view="core:ShowItem" itemId=$itemId}">
    {galleryText text="Return to item view"}
    </a>
  </center>
      
  {if empty($comments)}
  {galleryText text="There are no comments for this item"}
  {else}
  <table width="100%" border="0" cellspacing="4" cellpadding="0">
    {foreach from=$comments item=comment}
    <tr>
      <td width="100%">
	{galleryLightFrame width="100%"}
	{galleryHighlight1}
	{galleryBigFont}
	{$comment.commenter.userName}
	{/galleryBigFont}
	<br>
	{galleryDate timestamp=$comment.date format="%e-%b-%Y %H:%M"}
	{/galleryHighlight1}
	{galleryHighlight2}
	{$comment.comment}
	{/galleryHighlight2}
	{/galleryLightFrame}
      </td>
    </tr>
    {/foreach}
  </table>
  {/if}
