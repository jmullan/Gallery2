{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to CantActivate.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Thumbnail Page Module"}
      </h2>
    </div>
  </div>

  <div id="gsStatus">
    <div class="giError">
      {g->text text="This module requires you to have an active graphics toolkit that supports a multi-page file type such as TIFF, PDF or Postscript.  For example, ImageMagick with gs (GhostScript) support."}
    </div>
  </div>
</div>
