{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{*
 * This is a special template that we use to display G2 errors.
 *}
<div id="gsContents">
  <div id="gsAdminContents">
    <div class="gbTopFlag">
      <div class="gbTitle">
        <h1 class="giTitle">
	{if isset($main.error.obsoleteData)}
	  {g->text text="Edit Conflict!"}
	{elseif isset($main.error.securityViolation)}
	  {g->text text="Security Violation"}
	{elseif isset($main.error.storageFailure)}
	  {g->text text="Database Error"}
	{else}
	  {g->text text="Error"}
	{/if}
        </h1>
      </div>
    </div>

    <div class="gbAdmin">
      {if isset($main.error.obsoleteData)}
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
      {elseif isset($main.error.securityViolation)}
      <p class="giDescription">
	{g->text text="The action you attempted is not permitted."}
      </p>
      {elseif isset($main.error.storageFailure)}
      <p class="giDescription">
	{g->text text="An error has occurred while interacting with the database."}
      </p>
      {if $main.isAdmin && !isset($main.debug)}
      {g->text text="The exact nature of database errors is not captured unless Gallery debug mode is enabled in config.php.  Before seeking support for this error please enable buffered debug output and retry the operation.  Look near the bottom of the lengthy debug output to find error details."}
      {/if}
      {else}
      <p class="giDescription">
	{g->text text="An error has occurred."}
      </p>
      {/if}

      <p class="giDescription">
        <a href="{g->url}">{g->text text="Back to the Gallery"}</a>
      </p>
    </div>

    <div class="gbAdmin">
      <h3>
	{g->text text="Error Detail"}
	<span id="trace-toggle" class="giShowHideSwitch"
	      onclick="BlockToggle('giStackTrace', 'trace-toggle')"> {if $main.isAdmin}-{else}+{/if} </span>
      </h3>
      <div id="giStackTrace"{if !$main.isAdmin} style="display:none"{/if}>
	{$main.error.stackTrace}
      </div>
    </div>

    {if $main.isAdmin}
    <div class="gbAdmin">
      <h3> {g->text text="System Information"} </h3>
      <table class="gbDataTable">
        <tr>
          <td> {g->text text="Gallery version"} </td>
          <td> {$main.gallery.version} </td>
	</tr>
        <tr>
          <td> {g->text text="PHP version"} </td>
          <td> {$main.error.phpversion} {$main.error.php_sapi_name} </td>
	</tr>
        <tr>
          <td> {g->text text="Webserver"} </td>
          <td> {$main.error.webserver} </td>
	</tr>
	{if isset($main.error.dbType)}
	<tr>
          <td> {g->text text="Database"} </td>
          <td> {$main.error.dbType} {$main.error.dbVersion} </td>
	</tr>
	{/if}
	{if isset($main.error.toolkits)}
	<tr>
          <td> {g->text text="Toolkits"} </td>
          <td> {$main.error.toolkits} </td>
	</tr>
	{/if}
	<tr>
          <td> {g->text text="Operating system"} </td>
          <td> {$main.error.php_uname} </td>
	</tr>
        <tr>
          <td> {g->text text="Browser"} </td>
          <td> {$main.error.browser} </td>
        </tr>
      </table>
    </div>
    {/if}

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
