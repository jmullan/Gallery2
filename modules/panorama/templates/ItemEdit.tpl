{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEdit.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <div class="giDescription">
    {g->text text="Note that panorama view only applies to full size photo, not resizes."}
  </div>

  <input id="isPanorama" type="checkbox" name="{g->formVar var="form[isPanorama]"}" {if $form.isPanorama}checked="checked"{/if}/>
  <label for="isPanorama">
    {g->text text="Activate panorama viewer applet for this photo"}
  </label>
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
</div>
