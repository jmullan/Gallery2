{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to RandomHighlightOption.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Random Highlight"}
  </h2>

  <div class="gbDataEntry">
    <input id="isRandomHighlight" type="checkbox" name="{g->formVar var="form[RandomHighlightOption][isRandomHighlight]"}"
           {if $form.RandomHighlightOption.isRandomHighlight}checked="checked"{/if}/>
    <label for="isRandomHighlight">
      {g->text text="Activate random highlight for this album"}
    </label>
  </div>
</div>
