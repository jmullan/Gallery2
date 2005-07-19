{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !isset($item)} {assign var="item" value=$theme.item} {/if}
{if !isset($checkSidebarBlocks)} {assign var="checkSidebarBlocks" value=false} {/if}
{if !isset($checkAlbumBlocks)} {assign var="checkAlbumBlocks" value=false} {/if}
{if !isset($checkPhotoBlocks)} {assign var="checkPhotoBlocks" value=false} {/if}
{g->callback type="core.ShouldShowEmergencyEditItemLink"
             checkSidebarBlocks=$checkSidebarBlocks
             checkAlbumBlocks=$checkAlbumBlocks
             checkPhotoBlocks=$checkPhotoBlocks}

{if ($block.core.ShouldShowEmergencyEditItemLink)}
<div class="{$class}">
  <a href="{g->url arg1="view=core.ItemAdmin" arg2="subView=core.ItemEdit" arg3="itemId=`$item.id`"}"> {g->text text="Edit"} </a>
</div>
{/if}
