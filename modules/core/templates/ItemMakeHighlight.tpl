{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Use As Parent&rsquo;s Thumbnail?"}
      </h2>
    </div>

  </div>

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="You can make this item the thumbnail for its parent album."}
    </p>
    
    <input type="submit" name="{g->formVar var="form[action][makeHighlight]"}" value="{g->text text="Yes, highlight this item!"}"/>
  </div>
</div>

