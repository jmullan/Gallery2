{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Album Select Settings"} </h2>
</div>

{if isset($status.saved)}
<div class="gbBlock"><h2 class="giSuccess">
  {g->text text="Settings saved successfully"}
</h2></div>
{/if}

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="Turn off display in sidebar if you place the select box elsewhere using a local template (see details below).  List is sorted by each album's manual sort order unless sort by title is checked below."}
  </p>

  <input type="checkbox" id="cbShow"{if $form.show} checked="checked"{/if}
   name="{g->formVar var="form[show]"}"/>
  <label for="cbShow">
    {g->text text="Show select in sidebar"}
  </label>
  <br/>

  <input type="checkbox" id="cbSort"{if $form.sort} checked="checked"{/if}
   name="{g->formVar var="form[sort]"}"/>
  <label for="cbSort">
    {g->text text="Sort albums by title"}
  </label>
</div>

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="The album select can be too wide for the sidebar so you may wish to place it elsewhere.  Create a local template (see instructions at the top of layouts/matrix/templates/albumBody.tpl or any *.tpl file) and add a block like this:"}
  </p>
  <pre style="font-size:125%">
    {literal}{* Show AlbumSelect if available *}
    {if isset($AlbumSelectSystemContent)}
      {include file="gallery:`$AlbumSelectSystemContent.template`"}
    {/if}{/literal}
  </pre>
  <p class="giDescription">
    {g->text text="You may also include any HTML required for placing the block, like this:"}
  </p>
  <pre style="font-size:125%">
    {literal}{* Show AlbumSelect if available *}
    {if isset($AlbumSelectSystemContent)}
      &lt;tr&gt;&lt;td colspan=2&gt;
        {include file="gallery:`$AlbumSelectSystemContent.template`"}
      &lt;/td&gt;&lt;/tr&gt;
    {/if}{/literal}
  </pre>
</div>
