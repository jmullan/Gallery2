{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminExif.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Custom Fields"}
      </h2>
    </div>
  </div>

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="These are the global settings for custom fields. They can be overridden at the album level. Common fields are available on all Gallery items; Album and Photo fields can be assigned only to items of the appropriate type."}
    </p>
  </div>

  <script type="text/javascript">
    var removeWarning = '{g->text text="WARNING: All values for this custom field will be deleted! (Except in albums with album-specific settings)"}';
    var albumWarning = '{g->text text="WARNING: Values for this custom field on non-album items will be deleted! (Except in albums with album-specific settings)"}';
    var photoWarning = '{g->text text="WARNING: Values for this custom field on non-photo items will be deleted! (Except in albums with album-specific settings)"}';
  </script>

  {include file="gallery:modules/customfield/templates/Admin.tpl"}

</div>
