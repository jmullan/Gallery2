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
	{g->text text="Album Select Settings"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Settings saved successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Turn off display in sidebar if you place the select box elsewhere using a local template (see details below).  List is sorted by each album's manual sort order unless sort by title is checked below."}
    </p>
    <ul class="gbAdminList">
      <li>
	<input id="show" type="checkbox" name="{g->formVar var="form[show]"}"
	       {if $form.show}checked="checked"{/if}/>
	<label for="show">
	  {g->text text="Show select in sidebar"}
	</label>
      </li>
      <li>
	<input id="sort" type="checkbox" name="{g->formVar var="form[sort]"}"
	       {if $form.sort}checked="checked"{/if}/>
	<label for="sort">
	  {g->text text="Sort albums by title"}
	</label>
      </li>
    </ul>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}"
     value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}"
     value="{g->text text="Reset"}"/>
  </div>

  <div class="gbAdmin">
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
</div>
