{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemMakeHighlight.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Use as parent's thumbnail?"}
      </div>
    </div>

  </div>

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="You can make this item the thumbnail for its parent album."}
    </div>
    
    <input type="submit" name="{g->formVar var="form[action][makeHighlight]"}" value="{g->text text="Yes, highlight this item!"}"/>
  </div>
</div>

