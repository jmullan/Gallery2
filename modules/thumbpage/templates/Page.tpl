{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEdit.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <div class="giDescription">
    {g->text text="Select the page number to use for this item's thumbnail."}
  </div>

  <label for="page">
    {g->text text="Page"}
  </label>
  <select id="page" name="{g->formVar var="form[page]"}">
    {html_options options=$ItemEditThumbPage.pageList selected=$form.page}
  </select>
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>
