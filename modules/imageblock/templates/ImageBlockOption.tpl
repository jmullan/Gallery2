{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Image Block"}
  </h2>

  <div class="gbDataEntry">
    <input id="ImageBlockOption_setDisabled" type="checkbox" name="{g->formVar var="form[ImageBlockOption][setDisabled]"}"
	   {if $form.ImageBlockOption.setDisabled}checked="checked"{/if}/>
    <label for="ImageBlockOption_setDisabled">
      {g->text text="Prevent this album from being displayed in the Image Block"}
    </label>
    <br/>
    <input id="ImageBlockOption_setRecursive" type="checkbox" name="{g->formVar var="form[ImageBlockOption][setRecursive]"}" checked="checked"/>
    <label for="ImageBlockOption_setRecursive">
      {g->text text="Apply to sub-albums"}
    </label>
  </div>
</div>
