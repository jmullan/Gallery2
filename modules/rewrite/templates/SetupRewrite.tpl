{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="URL Rewrite Setup"} </h2>
</div>

<div class="gbBlock">
  <h3> {g->text text="Configuring your Webserver"} </h3>

  <p class="giDescription">
    {g->text text="Before we configure your Gallery installation to use mod_rewrite, we test to make sure that it will work properly."}
  </p>

  {assign var="showTestButton" value=false}
  {if $SetupRewrite.apacheCode == REWRITE_STATUS_OK}
    <div class="giSuccess">
      {g->text text="Apache mod_rewrite is working properly."}
    </div>
  {/if}

  {if ($SetupRewrite.apacheCode == REWRITE_STATUS_APACHE_NO_MOD_REWRITE)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Apache mod_rewrite is not installed or not enabled."}
    </div>
  {/if}

  {if ($SetupRewrite.apacheCode == REWRITE_STATUS_APACHE_UNABLE_TO_TEST)}
    {assign var="showTestButton" value=true}
    {assign var="showConfig" value=true}
    <div class="giError">
      {g->text text="We are unable to properly test whether mod_rewrite is properly installed."}
    </div>
  {/if}

  {if !empty($showTestButton)}
    <br/>
    <input type="submit" class="inputTypeSubmit"
      name="{g->formVar var="form[action][test]"}" value="{g->text text="Test Webserver Again"}"/>
    <br/><br/>
  {/if}
  
  {if !empty($showConfig)}
    <h3>Manual Configuration</h3>
    
    <p class="giDescription">
      {g->text text="Gallery tries to test mod_rewrite in action. For this to work you need to edit each of these two files accordingly:"}<br/>
    </p>
    
    <p class="giDescription">
      <b>{$SetupRewrite.customFile}</b><br/>
      {g->text text="Line 6:"} {$SetupRewrite.customLine}
    </p>
    
    <p class="giDescription">
      <b>{$SetupRewrite.customFileNoOptions}</b><br/>
      {g->text text="Line 6:"} {$SetupRewrite.customLineNoOptions}
    </p>
    
    <p class="giWarning">
      {g->text text="If the test still fails chanses are slim that this module will work. However, you may procede if you are confident that it will work."}
    </p>
    
    <p class="giDescription">
      <input type="checkbox" name="{g->formVar var="form[mod_rewrite][force]"}"> {g->text text="Apache mod_rewrite works."}
    </p>
  {/if}
</div>

<div class="gbBlock">
  <h3> {g->text text="Gallery .htaccess file"} </h3>

  <p class="giDescription">
    {g->text text="Gallery's URL rewriting works by creating a new file in your gallery directory called <b>.htaccess</b> which contains rules for how short urls should be interpreted.  We need write access to this file."}
  </p>

  {assign var="showTestButton" value=false}
  {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_READY)}
    <div class="giSuccess">
      {g->text text="Your .htaccess file ok."}
    </div>
  {/if}

  {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_CANT_WRITE)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Cannot write to the .htaccess file."}
    </div>
  {/if}

  {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_MISSING)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="The .htaccess file does not exist."}
    </div>
  {/if}

  {if ($SetupRewrite.htaccessCode == REWRITE_STATUS_HTACCESS_CANT_READ)}
    {assign var="showTestButton" value=true}
    <div class="giError">
      {g->text text="Can not read the .htaccess file."}
    </div>
  {/if}
  
  {if !empty($showTestButton)}
    <br/>
    <input type="submit" class="inputTypeSubmit" name="{g->formVar var="form[action][test]"}" value="{g->text text="Test .htaccess Again"}"/>
  {/if}
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][done]"}" value="{g->text text="Done"}"/>
</div>
