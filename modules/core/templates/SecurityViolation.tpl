{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SecurityViolation.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsContents">
  <div id="gsAdminContents">
    <div class="gbTopFlag">
      <div class="gbTitle">
        <h1 class="giTitle">
          {g->text text="Security Violation"}
        </h1>
      </div>
    </div>
    <div class="gbAdmin">
      <p class="giDescription">
        {g->text text="The action you attempted is not permitted."}
      </p>
      <p class="giDescription">
        <a href="{g->url}">
        {g->text text="Back to the Gallery"}
        </a>
      </p>
    </div>
  </div>
</div>