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
	{g->text text="URL Rewrite Settings"}
      </h2>
    </div>

  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.written)}
    <div class="giStatus">
      {g->text text="Successfully wrote .htaccess file"}
    </div>
    {/if}
    
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Successfully saved settings"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="URL Rewrite utilizes the Apache module mod_rewrite in order to shorten the URLs, this way they will become easier to read and remember."}
    </p>
  </div>
  
  {if isset($form.error.shortUrls)}
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Warning"}
    </h3>
    
    <p class="giDescription">
      {g->text text="URL Rewrite needs the bulk short URL style (using PathInfo) to be turned off in General settings."}
    </p>
    
    <div class="giWarning">
      {g->text text="Short URLs is turned on."}
    </div>
  </div>
  {/if}

  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Settings"}
    </h3>
    
    <p class="giDescription">
      {g->text text="Customize your Gallery URLs. Prefix values may not be the name of existing directories in your Gallery base directory."}
    </p>
    
    {if isset($form.error.badPrefix)}
    <div class="giError">
      {g->text text="Bad prefix value."}
    </div>
    {/if}
    
    <table class="gbDataTable">
      <tr>
        <th>
          {g->text text="View"}
        </th>
        <th>
          {g->text text="Current Prefix"}
        </th>
        <th>
          {g->text text="New Prefix"}
        </th>
      </tr>
      {foreach from=$form.prefix key=view item=prefix}
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td>
          {$view}
        </td>
        <td>
          {$AdminRewrite.prefix.$view}
        </td>
        <td>
          <input type="text" name="{g->formVar var="form[prefix][$view]"}" value="{$prefix}"/>
        </td>
      </tr>
      {/foreach}
    </table>
  </div>
  
  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save Settings"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Cancel"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
  </div>

</div>
