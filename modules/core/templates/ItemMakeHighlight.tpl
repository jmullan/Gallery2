{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Use As Parent&rsquo;s Thumbnail?"} </h2>
</div>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="You can make this item the thumbnail for its parent album."}
  </p>
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][makeHighlight]"}"
   value="{g->text text="Yes, highlight this item!"}"/>
</div>
