{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminCore.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="General Settings"}
      </div>
    </div>

  </div>

  {if isset($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Settings saved successfully"}
    </div>
    {/if}
    {if isset($status.addedDir)}
    <div class="giStatus">
      {g->text text="Added local upload dir successfully"}
    </div>
    {/if}
    {if isset($status.removedDir)}
    <div class="giStatus">
      {g->text text="Removed local upload dir successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Defaults"}
    </div>

    <div class="giDescription">
      {g->text text="These are default values.  They can be overridden in each album."}
    </div>

    <table class="gbDataTable">
      <tr>
	<td>
	  {g->text text="Default sort order"}
	</td>
	<td>
	  <select name="{g->formVar var="form[default][orderBy]"}">
	      {html_options options=$AdminCore.orderByList selected=$form.default.orderBy}
	  </select>
	  <select name="{g->formVar var="form[default][orderDirection]"}">
	      {html_options options=$AdminCore.orderDirectionList selected=$form.default.orderDirection}
	  </select>
	</td>
      </tr>

      <tr>
	<td>
	  {g->text text="Default layout"}
	</td>

	<td>
	  <select name="{g->formVar var="form[default][layout]"}">
	      {html_options options=$AdminCore.layoutList selected=$form.default.layout}
	  </select>
	</td>
      </tr>

      <tr>
	<td>
	  {g->text text="Default theme"}
	</td>

	<td>
	  <select name="{g->formVar var="form[default][theme]"}">
	      {html_options options=$AdminCore.themeList selected=$form.default.theme}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Language settings"}
    </div>

    <div class="giDescription">
      {g->text text="Select language defaults for Gallery. Individual users can override this setting in their personal preferences."}
    </div>

    <table class="gbDataTable">
      <tr>
	<td>
	  {g->text text="Default language"}
	</td>

	<td>
	  <select name="{g->formVar var="form[default][language]"}">
	      {html_options options=$AdminCore.languageList selected=$form.default.language}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Filesystem Permissions"}
    </div>

    <div class="giDescription">
      {g->text text="Specify the default permissions for files and directories that Gallery creates. This doesn't apply to files/directories that Gallery has already created."}
    </div>

    <table class="gbDataTable">
      <tr>
	<td>
	  {g->text text="New directories"}
	</td>
	
	<td>
	  <select name="{g->formVar var="form[permissions][directory]"}">
	      {html_options values=$AdminCore.permissionsDirectoryList selected=$form.permissions.directory output=$AdminCore.permissionsDirectoryList}
	  </select>
	</td>
      </tr>

      <tr>
	<td>
	  {g->text text="New files"}
	</td>
	
	<td>
	  <select name="{g->formVar var="form[permissions][file]"}">
	      {html_options values=$AdminCore.permissionsFileList selected=$form.permissions.file output=$AdminCore.permissionsFileList}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Local Server Upload Paths"}
    </div>

    <div class="giDescription">
      {g->text text="Specify the legal directories on the local server where a user can store files and then upload them into Gallery using the <i>Upload from Local Server</i> feature.  The paths you enter here and all the files and directories under those paths will be available to any Gallery user who has upload privileges, so you should limit this to directories that won't contain sensitive data (eg. /tmp or /usr/ftp/incoming)"}
    </div>

    <table class="gbDataTable">
      <tr>
	<th> 
	  {g->text text="Path"}
	</th>
	<th>
	  {g->text text="Action"}
	</th>
      </tr>

      {foreach from=$AdminCore.localServerDirList item=dir}
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {$dir}
	</td>
	<td>
	  <a href="{g->url arg1="controller=core:AdminCore"
                           arg2="form[action][removeUploadLocalServerDir]=1"
	                   arg3="form[uploadLocalServer][selectedDir]=$dir"}">
	    {g->text text="remove"}
	  </a>
	</td>
      </tr>
      {/foreach}

      <tr>
	<td>
	  <input type="text" size="40" name="{g->formVar var="form[uploadLocalServer][newDir]"}" value="{$form.uploadLocalServer.newDir}"/>
	</td>

	<td>
	  <input type="submit" name="{g->formVar var="form[action][addUploadLocalServerDir]"}" value="{g->text text="add"}"/>
	</td>
      </tr>
    </table>

    {if isset($form.error.uploadLocalServer.newDir.missing)}
    <div class="giError">
      {g->text text="You must enter a directory to add."}
    </div>
    {/if}

    {if isset($form.error.uploadLocalServer.newDir.restrictedByOpenBasedir)}
    <div class="giError">
      {capture name="open_basedir"}
      <a href="http://php.net/ini_set">
	{g->text text="open_basedir documentation"}
      </a>
      {/capture}
      {g->text text="Your webserver is configured to prevent you from accessing that directory.  Please refer to the %s and consult your webserver administrator." arg1=$smarty.capture.open_basedir}
    </div>
    {/if}

    {if isset($form.error.uploadLocalServer.newDir.notReadable)}
    <div class="giError">
      {g->text text="The webserver does not have permissions to read that directory."}
    </div>
    {/if}

    {if isset($form.error.uploadLocalServer.newDir.notADirectory)}
    <div class="giError">
      {g->text text="The path you specified is not a valid directory."}
    </div>
    {/if}
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Session Settings"}
    </div>
    
    <div class="giDescription">
      {g->text text="Specify the lifetime of the session here."}
    </div>

    <table class="gbDataTable">
      <tr>
	<td>
	  {g->text text="Lifetime"}
	</td>
	
	<td>
	  <select name="{g->formVar var="form[session][lifetime]"}">
	      {html_options options=$AdminCore.sessionTimeList selected=$form.session.lifetime}
	  </select>
	</td>
      </tr>
      
      <tr>
	<td>
	  {g->text text="Inactivity Timeout"}
	</td>
	
	<td>
	  <select name="{g->formVar var="form[session][inactivityTimeout]"}">
	      {html_options options=$AdminCore.sessionTimeList selected=$form.session.inactivityTimeout}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="URL Style"}
    </div>
    
    <div class="giDescription">
      {capture name="acceptPathInfoLink"}
      <a href="http://httpd.apache.org/docs-2.0/mod/core.html#acceptpathinfo">
	{g->text text="AcceptPathInfo Directive."}
      </a>
      {/capture}
      {capture name="shortUrlTestLink"}
      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$AdminCore.shortUrlTestItemId`" arg3="forceShortUrls=true"}">
	{g->text text="test url"}
      </a>
      {/capture}
      {g->text text="Gallery has the option to use a compact URL format, however this format is not supported by default on all web servers.  It is enabled by default on Apache 1, but not on Apache 2.  If you're using Apache 2 and you want this feature, you must use the %s  Use this %s to find out if short URLs work for you.  If the link returns a webserver error then they don't work for you." arg1=$smarty.capture.acceptPathInfoLink arg2=$smarty.capture.shortUrlTestLink}
    </div>

    <table class="gbDataTable">
      <tr>
	<td>
	  {g->text text="Use short URLs?"}
	</td>
	
	<td>
	  <select name="{g->formVar var="form[misc][useShortUrls]"}">
	      {html_options options=$AdminCore.useShortUrlsList selected=$form.misc.useShortUrls}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbAdmin">
    <div class="giTitle">
      {g->text text="Embedded Markup"}
    </div>
    
    <div class="giDescription">
      {g->text text="What kind of markup should we allow in user-entered fields?  For security reasons we do not recommend that you allow raw HTML.  BBCode is a special kind of markup that is secure and allows for simple text formatting like bold, italics, lists, images and urls."}
    </div>

    <table class="gbDataTable">
      <tr>
	<td>
	  {g->text text="Markup: "}
	</td>
	
	<td>
	  <select name="{g->formVar var="form[misc][markup]"}">
	      {html_options options=$AdminCore.embeddedMarkupList selected=$form.misc.markup}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbBottomFlag">
    <div class="gbButtons">
      <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="save"}"/>
      <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="reset"}"/>
    </div>
  </div>
</div>

