{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{* Set defaults *}
{if empty($item)} {assign var=item value=$theme.item} {/if}
{g->callback type="comment.AddComment" itemId=$item.id}

{if !empty($block.comment.AddComment)}
<div class="{$class}">
      {include file="gallery:modules/comment/templates/AddComment.tpl"
	       AddComment=$block.comment.AddComment}
</div>
{/if}
