{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to CommentChangeConfirmation.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Comment change confirmation"}
      </div>
    </div>

  </div>

  {if !empty($status)}
  <div id="gsStatus">
    <div class="giStatus">
      {if isset($status.added)}
      {g->text text="Comment added successfully"}
      {/if}
      {if isset($status.deleted)}
      {g->text text="Comment deleted successfully"}
      {/if}
      {if isset($status.saved)}
      {g->text text="Comment modified successfully"}
      {/if}
    </div>
  </div>
  {/if}
</div>
