{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="General Settings"} </h2>
</div>

{if !empty($status)}
<div class="gbBlock"><h2 class="giSuccess">
  {if isset($status.saved)}
    {g->text text="Settings saved successfully"} <br/>
  {/if}
  {if isset($status.addedDir)}
    {g->text text="Added local upload directory successfully"}
  {/if}
  {if isset($status.removedDir)}
    {g->text text="Removed local upload directory successfully"}
  {/if}
  {if isset($status.emailTestSuccess)}
    {g->text text="Test email sent successfully"}
  {/if}
</h2></div>
{/if}
{if isset($status.emailTestError) or isset($form.error.emailTest)}
<div class="gbBlock"><h2 class="giError">
  {g->text text="Error sending test email, see below for details"}
</h2></div>
{/if}

<div class="gbBlock">
  <h3> {g->text text="Language Settings"} </h3>

  <p class="giDescription">
    {g->text text="Select language defaults for Gallery. Individual users can override this setting in their personal preferences or via the language selector if activated below."}
  </p>

  {if isset($AdminCore.can.translate)}
  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Default language"}
    </td><td>
      <select name="{g->formVar var="form[default][language]"}">
	{html_options options=$AdminCore.languageList selected=$form.default.language}
      </select>
    </td>
  </tr><tr>
    <td>
      {g->text text="Language selector in sidebar"}
    </td><td>
      <select name="{g->formVar var="form[language][selector]"}">
	{html_options options=$AdminCore.languageSelectorList selected=$form.language.selector}
      </select>
    </td>
  </tr></table>
  {else}
    <div class="giWarning">
      {capture name="gettext"}
	<a href="http://php.net/gettext">{g->text text="gettext"}</a>
      {/capture}
      {g->text text="Your webserver does not support localization.  Please instruct your system administrator to reconfigure PHP with the %s option enabled." arg1=$smarty.capture.gettext}
    </div>
  {/if}
</div>

{if isset($AdminCore.can.setPermissions)}
<div class="gbBlock">
  <h3> {g->text text="Filesystem Permissions"} </h3>

  <p class="giDescription">
    {g->text text="Specify the default permissions for files and directories that Gallery creates. This doesn't apply to files/directories that Gallery has already created."}
  </p>

  <table class="gbDataTable"><tr>
    <td>
      {g->text text="New directories"}
    </td><td>
      <select name="{g->formVar var="form[permissions][directory]"}">
	{html_options values=$AdminCore.permissionsDirectoryList
	 selected=$form.permissions.directory output=$AdminCore.permissionsDirectoryList}
      </select>
    </td>
  </tr><tr>
    <td>
      {g->text text="New files"}
    </td><td>
      <select name="{g->formVar var="form[permissions][file]"}">
	{html_options values=$AdminCore.permissionsFileList
	 selected=$form.permissions.file output=$AdminCore.permissionsFileList}
      </select>
    </td>
  </tr></table>
</div>
{/if}

<div class="gbBlock">
  <h3> {g->text text="Local Server Upload Paths"} </h3>

  <p class="giDescription">
    {g->text text="Specify the legal directories on the local server where a user can store files and then upload them into Gallery using the <i>Upload from Local Server</i> feature.  The paths you enter here and all the files and directories under those paths will be available to any Gallery user who has upload privileges, so you should limit this to directories that won't contain sensitive data (eg. /tmp or /usr/ftp/incoming)"}
  </p>

  <table class="gbDataTable"><tr>
    <th> {g->text text="Path"} </th>
    <th> {g->text text="Action"} </th>
  </tr>

  {foreach from=$AdminCore.localServerDirList item=dir}
  <tr class="{cycle values="gbEven,gbOdd"}">
    <td>
      {$dir}
    </td><td>
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
      <input type="text" size="40"
       name="{g->formVar var="form[uploadLocalServer][newDir]"}"
       value="{$form.uploadLocalServer.newDir}"/>
    </td><td>
      <input type="submit" class="inputTypeSubmit"
       name="{g->formVar var="form[action][addUploadLocalServerDir]"}"
       value="{g->text text="Add"}"/>
    </td>
  </tr></table>

  {if isset($form.error.uploadLocalServer.newDir.missing)}
  <div class="giError">
    {g->text text="You must enter a directory to add."}
  </div>
  {/if}

  {if isset($form.error.uploadLocalServer.newDir.restrictedByOpenBasedir)}
  <div class="giError">
    {capture name="open_basedir"}
      <a href="http://php.net/ini_set">{g->text text="open_basedir documentation"}</a>
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

<div class="gbBlock">
  <h3> {g->text text="Session Settings"} </h3>

  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Login Method"}
    </td><td>
      <select name="{g->formVar var="form[misc][login]"}">
	{html_options options=$AdminCore.loginMethod selected=$form.misc.login}
      </select>
    </td>
  </tr><tr>
    <td>
      {g->text text="Session Lifetime"}
    </td><td>
      <select name="{g->formVar var="form[session][lifetime]"}">
	{html_options options=$AdminCore.sessionTimeList selected=$form.session.lifetime}
      </select>
    </td>
  </tr><tr>
    <td>
      {g->text text="Inactivity Timeout"}
    </td><td>
      <select name="{g->formVar var="form[session][inactivityTimeout]"}">
	{html_options options=$AdminCore.sessionTimeList selected=$form.session.inactivityTimeout}
      </select>
    </td>
  </tr></table>
</div>

<div class="gbBlock">
  <h3> {g->text text="Embedded Markup"} </h3>

  <p class="giDescription">
    {g->text text="What kind of markup should we allow in user-entered fields?  For security reasons we do not recommend that you allow raw HTML.  BBCode is a special kind of markup that is secure and allows for simple text formatting like bold, italics, lists, images and urls."}
  </p>

  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Markup"}
    </td><td>
      <select name="{g->formVar var="form[misc][markup]"}">
	{html_options options=$AdminCore.embeddedMarkupList selected=$form.misc.markup}
      </select>
    </td>
  </tr></table>
</div>

<div class="gbBlock">
  <h3> {g->text text="Email"} </h3>

  <p class="giDescription">
    {g->text text="By default Gallery uses PHP's built in mail function to send email which requires no configuration.  To use a smtp/mail server enter the information below, including authentication information if required."}
  </p>

  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Server"}
    </td><td>
      <input type="text" size="20"
       name="{g->formVar var="form[smtp][host]"}" value="{$form.smtp.host}"/>
    </td>
  </tr><tr>
    <td>
      {g->text text="Username"}
    </td><td>
      <input type="text" size="20"
       name="{g->formVar var="form[smtp][username]"}" value="{$form.smtp.username}"/>
    </td>
  </tr><tr>
    <td>
      {g->text text="Password"}
    </td><td>
      <input type="password" size="20"
       name="{g->formVar var="form[smtp][password]"}" value="{$form.smtp.password}"/>
    </td>
  </tr><tr>
    <td>
      {g->text text="SMTP From Address"}
    </td><td>
      <input type="text" size="20"
       name="{g->formVar var="form[smtp][from]"}" value="{$form.smtp.from}"/>
    </td>
  </tr></table>

  <p class="giDescription">
    {g->text text="Send a test email to verify your settings are correct (whether using PHP mail or SMTP settings above).  Below enter a recipient email address for a test message."}
  </p>
  <p>
    <input type="text" size="30"
     name="{g->formVar var="form[emailTest][to]"}" value="{$form.emailTest.to}"/>
    &nbsp;
    <input type="submit" class="inputTypeSubmit"
     name="{g->formVar var="form[action][emailTest]"}" value="{g->text text="Send Email"}"/>
  </p>
  {if isset($form.error.emailTest.invalidTo)}
  <div class="giError">
    {g->text text="Invalid email address"}
  </div>
  {/if}
  {if isset($status.emailTestError)}
    <h4> {g->text text="Email Test Error"} </h4>
    <div class="gcBackground1 gcBorder2"
     style="border-width: 1px; border-style: dotted; padding: 4px">
      {$status.emailTestError}
      <pre>{$status.emailTestDebug}</pre>
    </div>
  {/if}
</div>

<div class="gbBlock">
  <h3> {g->text text="Locking System"} </h3>

  <p class="giDescription">
    {g->text text="Gallery uses a system of locks to prevent simultaneous changes from interfering with each other.  There are two types of locking, each with its advantages and disadvantages.  <b>File</b> based locking is fast and efficient, but won't work on NFS filesystems and will be unreliable on Windows.  <b>Database</b> locking is slower but is more reliable.  If you are unsure which to choose, we recommend using file locking.  If you're getting many lock timeouts, you can try switching to database locking instead.  It's ok to switch back and forth."}
  </p>

  <table class="gbDataTable"><tr>
    <td>
      {g->text text="Lock system"}
    </td><td>
      <select name="{g->formVar var="form[lock][system]"}">
	{html_options options=$AdminCore.lockSystemList selected=$form.lock.system}
      </select>
    </td>
  </tr></table>
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>
