<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
	{g->text text="Gallery 1 to Gallery 2 Data Migration"}
      </div>

      <div class="giDescription">
	<i>
	  {g->text text="This module is unfinished.  It should not harm your Gallery 1 data, but use it at your own risk."}
	</i>
      </div>
    </div>

    <div class="spacer">
      &nbsp;
    </div>
  </div>

  <div class="gbAdmin">
    <div class="giDescription">
      {g->text text="This process will copy data from an existing Gallery 1 installation.  It won't modify your Gallery 1 data in any way.  You must enter the path to your Gallery 1 <i>albums</i> directory.  If you enter the wrong path, we'll let you know so it's safe to experiment.  Example: <i>/path/to/albums</i>"}
    </div>

    <div class="gbDataEntry">
      <div class="giTitle">
	{g->text text="Path:"}
      </div>

      <input type="text" size="60" name="{g->formVar var="form[albumsPath]"}" value="{$form.albumsPath}"/>

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

    <br />

    {g->text text="Recent paths:"}
    <ul>
      {foreach from=$SelectGallery.recentPaths key=path item=count}
      {capture name="escapedPath"}{$path|replace:"\\":"\\\\"}{/capture}
      <li>
	<a href="{g->url javascript="selectPath('`$smarty.capture.escapedPath`')"}">
	  {$path}
	</a>
      </li>
      {/foreach}
    </ul>
    {/if}

    <input type="submit" name="{g->formVar var="form[action][select]"}" value="{g->text text="Select"}"/>
  </div>
</div>
