{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEdit.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Image Block"}
  </h2>

  <div class="gbDataEntry">
    <input id="ImageBlockOption_isDisabled" type="checkbox" name="{g->formVar var="form[ImageBlockOption][isDisabled]"}"
	   {if $form.ImageBlockOption.isDisabled}checked="checked"{/if}/>
    <label for="ImageBlockOption_isDisabled">
      {g->text text="Prevent this album from being displayed in the Image Block"}
    </label>
    <input id="ImageBlockOption_isRecursive" type="checkbox" name="{g->formVar var="form[ImageBlockOption][isRecursive]"}" checked="checked"/>
    <label for="ImageBlockOption_isRecursive">
      {g->text text="Apply to sub-albums"}
    </label>
  </div>
</div>
