{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Panorama"}
  </h2>

  <p class="giDescription">
    {g->text text="Note that panorama view only applies to full size photo, not resizes."}
  </p>

  <input id="isPanorama" type="checkbox" name="{g->formVar var="form[PanoramaOption][isPanorama]"}"
         {if $form.PanoramaOption.isPanorama}checked="checked"{/if}/>
  <label for="isPanorama">
    {g->text text="Activate panorama viewer applet for this photo"}
  </label>
</div>
