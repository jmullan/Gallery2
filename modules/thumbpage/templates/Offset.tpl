{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to Offset.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <div class="giDescription">
    {g->text text="Select the time offset to use for this item's thumbnail."}
  </div>

  <input id="offset" type="text" size="8"
         name="{g->formVar var="form[offset]"}" value="{$form.offset}"/>
  <label for="offset">
    {g->text text="Seconds (Max = %s)" arg1=$form.duration}
  </label>

  {if isset($form.error.offset.invalid)}
  <div class="giError">
    {g->text text="Enter a value between 0 and %s" arg1=$form.duration}
  </div>
  {/if}
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>
