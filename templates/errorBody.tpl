{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *
 * This is a special template that we use to display G2 errors.
 *}
<div id="gsContents">
  <div id="gsAdminContents">
    <div class="gbTopFlag">
      <div class="gbTitle">
        <h1 class="giTitle">
	{if isset($main.errorObsoleteData)}
	  {g->text text="Edit Conflict!"}
	{elseif isset($main.securityViolation)}
	  {g->text text="Security Violation"}
	{else}
	  {g->text text="Error"}
	{/if}
        </h1>
      </div>
    </div>

    <div class="gbAdmin">
    {if isset($main.errorObsoleteData)}
      <p class="giDescription">
	{g->text text="Your change cannot be completed because somebody else has made a conflicting change to the same item.  Use the back button in your browser to go back to the page you were on, then <b>reload that page</b> and try your change again."}
      </p>
      <a href="javascript:history.back()">
	{g->text text="Go back and try again"}
      </a>
      </div><div class="gbAdmin">
      <p class="giDescription">
	{g->text text="Alternatively, you can return to the main Gallery page and resume browsing."}
      </p>
    {elseif isset($main.securityViolation)}
      <p class="giDescription">
	{g->text text="The action you attempted is not permitted."}
      </p>
    {else}
      <p class="giDescription">
	{g->text text="An error has occurred."}
      </p>
    {/if}

      <p class="giDescription">
	<a href="{g->url}">
	  {g->text text="Back to the Gallery"}
	</a>
      </p>
    </div>

    <div class="gbAdmin">
      <h3>
	{g->text text="Error Detail"}
	<span id="trace-toggle" class="toggle"
	      onclick="toggle('trace', 'trace-toggle')"> {if $main.isAdmin}-{else}+{/if} </span>
      </h3>
      <div id="trace"{if !$main.isAdmin} style="display:none"{/if}>
	{$main.error}
      </div>
    </div>

    {if isset($main.debug)}
    <div class="gbAdmin">
      {include file="gallery:templates/debug.tpl"}
    </div>
    {/if}

    {if isset($main.profile)}
    <div class="gbAdmin">
      {include file="gallery:templates/profile.tpl"}
    </div>
    {/if}
  </div>
</div>
