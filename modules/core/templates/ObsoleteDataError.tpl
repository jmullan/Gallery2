{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ObsoleteDataError.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsContents">
  <div id="gsAdminContents">
    <div class="gbTopFlag">
      <div class="gbTitle">
        <h1 class="giTitle">
          {g->text text="Edit Conflict!"}
        </h1>
      </div>
    </div>
    <div class="gbAdmin">
      <p class="giDescription">
        {g->text text="Your change cannot be completed because somebody else has made a conflicting change to the same item.  Use the back button in your browser to go back to the page you were on, then <b>reload that page</b> and try your change again."}
      </p>

      <a href="javascript:history.back()">
        {g->text text="Go back and try again"}
      </a>
    </div>

    <div class="gbAdmin">
      <p class="giDescription">
        {g->text text="Alternatively, you can return to the main Gallery page and resume browsing."}
      </p>

      <a href="{g->url}">
        {g->text text="Back to the Gallery"}
      </a>
    </div>
  </div>
</div>
