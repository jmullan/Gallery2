{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Import from Gallery 1"} </h2>

  <p class="giDescription">
    {g->text text="This operation takes data (images, albums, users, etc.) from <strong>Gallery 1</strong> and brings it into <strong>Gallery 2</strong>."}
  </p>
  <p><strong>
    {g->text text="Before you migrate any data you must try adding an album and image through the main gallery interface first.  This will show you if your gallery is correctly set up."}
  </strong></p>
  <p><em>
    {g->text text="This module is unfinished.  It should not harm your Gallery 1 data, but use it at your own risk."}
  </em></p>
</div>

{if (!$SelectGallery.hasToolkit)}
<div class="gbBlock"><p class="giError">
  {capture name="url"}
    {g->url arg1="view=core.SiteAdmin" arg2="subView=core.AdminModules"}
  {/capture}
  {g->text text="You don't have any Graphics Toolkit activated to handle JPEG images.  If you import now, you will not have any thumbnails.  Visit the <a href=\"%s\">Modules</a> page to activate a Graphics Toolkit." arg1=$smarty.capture.url}
</p></div>
{/if}

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="This process will copy data from an existing Gallery 1 installation.  It won't modify your Gallery 1 data in any way.  You must enter the path to your Gallery 1 <i>albums</i> directory.  If you enter the wrong path, we'll let you know so it's safe to experiment.  Example: <i>/path/to/albums</i>"}
  </p>

  <div>
    <h4> {g->text text="Path"} </h4>

    <input type="text" size="60"
     name="{g->formVar var="form[albumsPath]"}" value="{$form.albumsPath}"
      id='giFormPath' autocomplete="off"/>
    {g->autoComplete element="giFormPath"}
      {g->url arg1="view=core.SimpleCallback" arg2="command=lookupDirectories" arg3="prefix=__VALUE__"
        forJavascript="true"}
    {/g->autoComplete}

    {if isset($form.error.albumsPath.missing)}
    <div class="giError">
      {g->text text="You did not enter a path."}
    </div>
    {/if}
    {if isset($form.error.albumsPath.invalid)}
    <div class="giError">
      {g->text text="The path that you entered is invalid."}
    </div>
    {/if}
  </div>

  {if !empty($SelectGallery.recentPaths)}
  <script type="text/javascript">
    // <![CDATA[
    function selectPath(path) {ldelim}
      document.forms[0].elements['{g->formVar var="form[albumsPath]"}'].value = path;
    {rdelim}
    // ]]>
  </script>

  <h4 class="giTitle">
    {g->text text="Recently Used Paths"}
  </h4>
  <p>
  {foreach from=$SelectGallery.recentPaths key=path item=count}
    {capture name="escapedPath"}{$path|replace:"\\":"\\\\"}{/capture}
    <a href="javascript:selectPath('{$smarty.capture.escapedPath}')">{$path}</a>
    <br/>
  {/foreach}
  </p>
  {/if}
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][select]"}" value="{g->text text="Select"}"/>
</div>

{if $SelectGallery.mapCount>0 || isset($status.mapDeleted)}
<div class="gbBlock">
  <h3> {g->text text="URL Redirection"} </h3>

  <p class="giDescription">
    {g->text text="Gallery can redirect old Gallery1 URLs to the new Gallery2 pages."}
  </p>

  {if $SelectGallery.mapCount>0}
    <span>
      {g->text one="There is one G1->G2 map entry" many="There are %d G1->G2 map entries"
	       count=$SelectGallery.mapCount arg1=$SelectGallery.mapCount}
    </span>
    &nbsp;
    <span>
      <a href="{g->url arg1="controller=migrate.SelectGallery" arg2="form[action][deleteMap]=1"}"
	 onclick="return confirm('{g->text text="Deleting map entries will cause old G1 URLs to produce HTTP Not Found errors instead of redirecting to G2 pages.  Delete all entries?"}')">
	{g->text text="Delete All"}
      </a>
    </span>
  {/if}
  {if isset($status.mapDeleted)}
    <p class="giError">
	{g->text text="Map entries deleted successfully"}
    </p>
  {/if}
  {include file="gallery:modules/migrate/templates/Redirect.tpl" uriBase=$SelectGallery.uriBase}
</div>
{/if}
