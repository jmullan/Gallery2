{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Configuration Error: Missing Layout"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">
    <h2 class="giTitle">
      {g->text text="Missing Layout"}
    </h2>
  
    <p class="giDescription">
      {capture name="layoutId"}
	<b>{$ShowItemError.layoutId}</b>
      {/capture}
      {g->text text="This album is configured to use the %s layout, but it is either inactive or not installed." arg1=$smarty.capture.layoutId}
      {capture name="optionOne"}
	{if !$ShowItemError.canEdit}
	  <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=core:UserLogin" arg3="return=1"}">{g->text text="login"}</a>
	  {g->text text="and then"}
	{/if}
	<a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemEdit" arg3="editPlugin=ItemEditAlbum" arg4="itemId=`$ShowItemError.itemId`"}">{g->text text="choose a new layout for this album"}</a>
      {/capture}
      {capture name="optionTwo"}
	{if !$ShowItemError.isAdmin}
	  <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=core:UserLogin" arg3="return=1"}">{g->text text="login as a site administrator"}</a>
	  {g->text text="and then"}
	{/if}
	<a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminLayouts" arg3="mode=config"}">{g->text text="install or activate this layout"}</a>
      {/capture}
      {g->text text="To fix this problem you can either %s or %s." arg1=$smarty.capture.optionOne arg2=$smarty.capture.optionTwo}
    </p>
  </div>
</div>
