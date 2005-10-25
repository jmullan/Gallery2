{*
 * $Revision: 1.36 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Gallery Repository Setup"} </h2>
</div>

{if !empty($errorMessage)}
<div class="gbBlock"><h2 class="giWarning">
  {g->text text="Warning: `$errorMessage`"}
</h2></div>
{/if}

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="In order to download plugins from the Gallery repository, a special directory needs to be created where Gallery will store the data."}
    {g->text text="Under your Gallery base directory, create a directory called '%s' and allow the web server to write into it by appropriately setting the permissions." arg1=$pluginsDirectoryName}
    {g->text text="Instructions for Unix-type platforms:"}
  </p>
  <p class="giDescription">
    {g->text text="$ cd %s" arg1=$galleryBaseDirectory}<br>
    {g->text text="$ mkdir %s" arg1=$pluginsDirectoryName}<br>
    {g->text text="$ chmod 777 %s" arg1=$pluginsDirectoryName}
  </p>
  <p>
    {g->text text="Refreshing this page will take you to the Repository if the directory has been successfully created."}
  </p>
</div>