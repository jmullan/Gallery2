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
