{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !empty($CustomFieldItemDetails.fields)}
<div class="gbCustomFields">
  <h2 class="giTitle"> {g->text text="Custom Fields"} </h2>
  <span class="giDescription">
    {foreach from=$CustomFieldItemDetails.fields key=field item=value}{$field}: {$value}<br/>
    {/foreach}
  </span>
</div>
{/if}
