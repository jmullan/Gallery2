{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
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
