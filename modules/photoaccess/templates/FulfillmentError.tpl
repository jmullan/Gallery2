{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to FulfillmentError.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="PhotoAccess Fulfillment Error"}
      </div>
    </div>

  </div>

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="An error occurred while sending your photos over to PhotoAccess.com for printing.  If this failure occurs more than once, please contact your system administrator for assistance."}
    </div>

    <a href="{g->url arg1="view=cart:ViewCart"}">
      {g->text text="View your cart"}
    </a>
  </div>
</div>
