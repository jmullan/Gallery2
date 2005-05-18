{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{if !empty($CustomFieldItemDetails.fields)}
<div id="gsCustomFields" class="gbBlock">
  <h3> {g->text text="Custom Fields"} </h3>
  <p class="giDescription">
    {foreach from=$CustomFieldItemDetails.fields key=field item=value}{$field}: {$value}<br/>
    {/foreach}
  </p>
</div>
{/if}
