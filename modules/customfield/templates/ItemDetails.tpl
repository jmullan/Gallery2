{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to CommentItemDetails.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
{if !empty($CustomFieldItemDetails.fields)}
<div id="gsCustomFields">
  <span class="giTitle"> {g->text text="Custom Fields"} </span>
  <span class="giDescription">
    {foreach from=$CustomFieldItemDetails.fields key=field item=value}{$field}: {$value}<br/>
    {/foreach}
  </span>
</div>
{/if}
