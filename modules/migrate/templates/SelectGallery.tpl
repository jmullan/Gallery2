{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SelectGallery.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Import from Gallery 1"}
      </h2>

      <p class="giDescription">
      This operation takes data (images, albums, users, etc.) from <strong>Gallery 1</strong> and brings it into <strong>Gallery 2</strong>.
      </p>
      <p class="giDescription">      
	<em>
	  {g->text text="This module is unfinished.  It should not harm your Gallery 1 data, but use it at your own risk."}
	</em>
      </p>
    </div>

  </div>

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="This process will copy data from an existing Gallery 1 installation.  It won't modify your Gallery 1 data in any way.  You must enter the path to your Gallery 1 <i>albums</i> directory.  If you enter the wrong path, we'll let you know so it's safe to experiment.  Example: <i>/path/to/albums</i>"}
    </p>

    <div class="gbDataEntry">
      <h3 class="giTitle">
	{g->text text="Path"}
      </h3>

      <input type="text" size="60" name="{g->formVar var="form[albumsPath]"}" value="{$form.albumsPath}" onfocus="this.style.background='#fff';this.style.color='#000';" onblur="this.style.background='#eee';this.style.color='#333';"/>

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
      function selectPath(path) {ldelim}
        document.forms[0].elements['{g->formVar var="form[albumsPath]"}'].value = path;
      {rdelim}
    </script>

    <h4 class="giTitle">
      {g->text text="Recently Used Paths"}
    </h4>
    <ul class="gbAdminList">
      {foreach from=$SelectGallery.recentPaths key=path item=count}
      {capture name="escapedPath"}{$path|replace:"\\":"\\\\"}{/capture}
      <li>
	<a href="javascript:selectPath('{$smarty.capture.escapedPath}')">
	  {$path}
	</a>
      </li>
      {/foreach}
    </ul>
    {/if}

    <input type="submit" name="{g->formVar var="form[action][select]"}" value="{g->text text="Select"}" class="button"/>
  </div>
</div>
