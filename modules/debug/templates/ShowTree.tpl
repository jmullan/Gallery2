{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ShowTree.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsHeader">
  <div class="gbTitleBanner">
    <div class="giTitle">
      {g->text text="Debug Tree"}
    </div>
  </div>
</div>

<div id="gsAdminContents">
  <div class="gbAdmin">
    {include file="gallery:modules/debug/templates/ShowTreeEntity.tpl" parentIndex=0}
  </div>
</div>
