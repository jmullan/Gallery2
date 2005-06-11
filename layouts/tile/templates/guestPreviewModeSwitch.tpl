{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if $user.isRegisteredUser}
<div style="float: right">
  <div class="gbBlock gcBackground1">
    {capture name=guestPreviewMode}
    {if ($layout.guestPreviewMode)}
    <a href="{g->url arg1="controller=core.ShowItem" arg2="guestPreviewMode=0" arg3="return=1"}">{$user.userName}</a> | <b> {g->text text="guest"} </b>
    {else}
    <b> {$user.userName} </b> | <a href="{g->url arg1="controller=core.ShowItem" arg2="guestPreviewMode=1" arg3="return=1"}">{g->text text="guest"}</a>
    {/if}
    {/capture}
    {g->text text="display mode: %s" arg1=$smarty.capture.guestPreviewMode}
  </div>
</div>
{/if}
