{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to CreateThumbnailOption.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <div class="giTitle">
    {g->text text="Thumbnails"}
  </div>

  <div class="giDescription">
    {g->text text="Gallery can create thumbnails at upload time, or create them the first time you want to see the thumbnail itself.  Either way, it will create the thumbnail once and save it, but if you create them at upload time it makes viewing albums for the first time go faster at the expense of a longer upload time."}
  </div>

  <div class="gbDataEntry">
    <input type="checkbox" name="{g->formVar var="form[CreateThumbnailOption][createThumbnail]"}" checked="checked"/>
    {g->text text="Create thumbnails now"}
  </div>
</div>
