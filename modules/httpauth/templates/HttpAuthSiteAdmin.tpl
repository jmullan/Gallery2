{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="HTTP Auth Settings"} </h2>
</div>

{if isset($status.saved)}
  <div class="gbBlock">
    <h2 class="giSuccess"> {g->text text="Settings saved successfully"} </h2>
  </div>
{/if}

{if isset($HttpAuthSiteAdmin.rewriteWarning)}
  <div class="gbBlock">
    <h2 class="giWarning"> {g->text text="Rewrite rule not configured"} </h2>

    <p class="giDescription">
      {g->text text="You are running Gallery with the PHP CGI server API but the Authorization HTTP header rewrite rule isn't enabled.  HTTP authentication against Gallery's user database won't work without this rule because CGI scripts ordinarily can't access the Authorization HTTP header in which usernames and passwords are sent.  Web server authentication will still work."}
    </p>
  </div>
{/if}

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="Gallery can handle HTTP Basic authentication directly."}
  </p>

  <label for="cbHttpAuthPluginInput"> {g->text text="Use HTTP Authentication:"} </label>
  <input id="cbHttpAuthPluginInput" name="{g->formVar var="form[httpAuthPlugin]"}" type="checkbox"{if $form.httpAuthPlugin} checked="checked"{/if} onclick="BlockToggle('cbAuthName')"/>
</div>

<div class="gbBlock" id="cbAuthName"{if !$form.httpAuthPlugin} style="display: none"{/if}>
  <p class="giDescription">
    {g->text text="Gallery will prompt you to login with HTTP authentication when permission is denied.  HTTP authentication sends your client a realm to which your username belongs.  It's safe to leave the realm blank."}
  </p>
  {g->text text="HTTP Authentication Realm:"}
  <input name="{g->formVar var="form[authName]"}" type="text" value="{$form.authName}"/>
</div>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="Your web server may offer more comprehensive and more secure authentication.  If you configured your web server to authenticate requests to Gallery, you may choose to trust the username it reports in the REMOTE_USER environment variable."}
  </p>

  <label for="cbServerAuthPluginInput"> {g->text text="Use Web Server Authentication:"} </label>
  <input id="cbServerAuthPluginInput" name="{g->formVar var="form[serverAuthPlugin]"}" type="checkbox"{if $form.serverAuthPlugin} checked="checked"{/if}/>
</div>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="You may wish to trust only HTTP authentication types or HTTP usernames which match specified regular expressions - or HTTP usernames may not match your Gallery usernames; for instance if using %s authentication, the REMOTE_USER environment variable may be username@REALM.TLD.  In these cases, you may use regular expressions to filter authentication types and usernames." arg1="<a href=\"http://modauthkerb.sourceforge.net/\"> Kerberos </a>"}
  </p>

  <label for="cbRegexAuthPluginInput"> {g->text text="Use Regular Expressions:"} </label>
  <input id="cbRegexAuthPluginInput" name="{g->formVar var="form[regexAuthPlugin]"}" type="checkbox"{if $form.regexAuthPlugin} checked="checked"{/if} onclick="BlockToggle('cbAuthtypeRegex'); BlockToggle('cbUsernameRegex')"/>
</div>

<div class="gbBlock" id="cbAuthtypeRegex"{if !$form.regexAuthPlugin} style="display: none"{/if}>
  <p class="giDescription">
    {g->text text="Specify here a regular expression which the authentication type must match for authentication to proceed; for instance /Negotiate/"}
  </p>

  {g->text text="Authentication Type Pattern:"}
  <input name="{g->formVar var="form[authtypePattern]"}" type="text" value="{$form.authtypePattern}"/>

  {if !empty($form.error.authtype.regex.invalid)}
  <div class="giError"> {g->text text="You must enter a valid regular expression"} </div>
  <div class="giError"> {$status.authtypeRegexMessage} </div>
  {/if}
</div>

<div class="gbBlock" id="cbUsernameRegex" {if !$form.regexAuthPlugin} style="display: none"{/if}>
  <p class="giDescription">
    {g->text text="Specify here a regular expression which the username must match for authentication to proceed and a string with which to replace it.  See PHP %s documentation for more information." arg1="<a href=\"http://php.net/preg_replace\"> preg_replace </a>"}
  </p>

  {g->text text="Username Pattern:"}
  <input name="{g->formVar var="form[usernamePattern]"}" type="text" value="{$form.usernamePattern}"/>

  {g->text text="Username Replacement:"}
  <input name="{g->formVar var="form[usernameReplace]"}" type="text" value="{$form.usernameReplace}"/>

  {if !empty($form.error.username.regex.invalid)}
  <div class="giError"> {g->text text="You must enter a valid regular expression"} </div>
  <div class="giError"> {$status.usernameRegexMessage} </div>
  {/if}
</div>

<div class="gbBlock gcBackground1">
  <input class="inputTypeSubmit" name="{g->formVar var="form[action][save]"}" type="submit" value="{g->text text="Save"}"/>
  <input class="inputTypeSubmit" name="{g->formVar var="form[action][reset]"}" type="submit" value="{g->text text="Reset"}"/>
</div>
