{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
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
