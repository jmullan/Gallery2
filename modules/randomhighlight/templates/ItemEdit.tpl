{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEdit.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <input id="isRandomHighlight" type="checkbox" name="{g->formVar var="form[isRandomHighlight]"}"
         {if $form.isRandomHighlight}checked="checked"{/if}/>
  <label for="isRandomHighlight">
    {g->text text="Activate random highlight for this album"}
  </label>
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
</div>
