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
	{g->text text="URL Rewrite Setup"}
      </h2>
    </div>

  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Successfully saved mode"}
    </div>
    {/if}
    
    {if isset($status.written)}
    <div class="giStatus">
      {g->text text="Successfully wrote .htaccess file"}
    </div>
    {/if}
  </div>
  {/if}
  
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="URL Rewrite Mode"}
    </h3>

    <p class="giDescription">
      {g->text text="There's two diffrent modes URL Rewrite works in. Either you use the prefix method which will put a prefix before all URLs (ie /v/ by default for viewing items), or you may disable the prefix. Once activated, you can change the prefixes as desiered."}
    </p>
    
    <table class="gbDataTable">
      <tr>
	<td>
	  {g->text text="Use prefixes?"}
	</td>
	<td>
	  <select name="{g->formVar var="form[mode]"}">
	      {html_options options=$SetupRewrite.modes selected=$form.mode}
	  </select>
	</td>
      </tr>
      
      <tr>
	<td>
	  {g->text text="Gallery base URL:"}
	</td>
	<td>
	  <input type="text" size="40" name="{g->formVar var="form[galleryLocation]"}" value="{$form.galleryLocation}"/>
	</td>
      </tr>
    </table>
    
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  </div>
  
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Checking Gallery Configuration"}
    </h3>
    
    <p class="giDescription">
      {g->text text="URL Rewrite needs the bulk short URL style (using PathInfo) to be turned off in General settings."}
    </p>

    {if isset($form.error.shortUrls)}
    <div class="giError">
      {g->text text="Short URLs is turned on."}
    </div>
    {else}
    <div class="giSuccess">
      {g->text text="Short URLs is turned off."}
    </div>
    {/if}
  </div>
  
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Configuring your Webserver"}
    </h3>

    <p class="giDescription">
      {g->text text="Before we configure your Gallery installation to use mod_rewrite, we test to make sure that it will work properly.  If the test doesn't succeed, you can still try to continue, but you may experience problems."}
    </p>

    {assign var="showTestButton" value=false}
    {if $SetupRewrite.apacheCode == REWRITE_STATUS_OK}
    <div class="giSuccess">
      {g->text text="Apache mod_rewrite is working properly."}
    </div>
    {else}

    {if ($SetupRewrite.apacheCode == REWRITE_STATUS_APACHE_NO_MOD_REWRITE)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Apache mod_rewrite is not installed or not enabled."}
    </div>
    {/if}

    {if ($SetupRewrite.apacheCode == REWRITE_STATUS_APACHE_UNABLE_TO_TEST)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Because of your server configuration, we are unable to properly test whether mod_rewrite is properly installed."}
    </div>
    
    <div class="giDescription">
    {g->text text="This is a result of trying to install gallery in a non standard directory. You need to edit"}<br />
    {g->text text="<b>line 6</b> in <b>%s</b>" arg1=$SetupRewrite.customFile}<br />
    {g->text text="and make sure it reads"}
    <b>{$SetupRewrite.customLine}</b>
    </div>
    {/if}

    {if !empty($showTestButton)}
    <br/>
    <input type="submit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test Webserver Again"}"/>
    {/if}
    {/if}
  </div>
  
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Gallery .htaccess file"}
    </h3>

    <p class="giDescription">
      {g->text text="Gallery's URL rewriting works by creating a new file in your gallery directory called <b>.htaccess</b> which contains rules for how short urls should be interpreted.  We will try to create and maintain this file for you."}
    </p>

    {assign var="showTestButton" value=false}
    {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_OK)}
    <div class="giSuccess">
      {g->text text="Your .htaccess file is up to date.  No changes are required"}
    </div>
    {/if}

    {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_CANT_WRITE)}
    {assign var="showManualDirections" value=true}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Cannot write to the .htaccess file."}
    </div>
    {/if}

    {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_MISSING)}
    {assign var="showManualDirections" value=true}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="The .htaccess file does not exist."}
    </div>
    {/if}
    
    {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_CANT_READ)}
    {assign var="showManualDirections" value=true}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Can not read the .htaccess file."}
    </div>
    {/if}
    
    {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_READY)}
    {assign var="showUpdateButton" value=true}
    <div class="giWarning">
      {g->text text="Your .htaccess file is ready to be updated."}
    </div>
    {/if}

    {if !empty($showUpdateButton)}
    <br/>
    <input type="submit" name="{g->formVar var="form[action][write]"}" value="{g->text text="Update .htaccess"}"/>
    {/if}

    {if !empty($showTestButton)}
    <br/>
    <input type="submit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test .htaccess Again"}"/>
    {/if}
  </div>

  {if !empty($showManualDirections)}
  <div class="gbAdmin">
    <h3 class="giTitle">
      {g->text text="Manual .htaccess installation"}
    </h3>

    <p class="giDescription">
      {g->text text="If you're having problems letting Gallery to update your .htaccess file, you can do it yourself by hand.  Cut and paste the following text into <b>%s</b>" arg1=$SetupRewrite.htaccessPath}
    </p>
    <textarea rows="8" cols="60">{$SetupRewrite.htaccessContent}</textarea>
    <br/>
    <input type="submit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Verify"}"/>
  </div>
  {/if}
  
  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][done]"}" value="{g->text text="Done"}"/>
  </div>
  
</div>
