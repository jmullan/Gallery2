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
    {g->text text="Albums can be displayed in a simple list box or a dynamic tree.  Turn off display in sidebar if you place the selector elsewhere using a local template (see details below)."}
  </p>

  <h4> {g->text text="Selector type"} </h4>

  <input type="radio" id="rbSelect"{if $form.type=='select'} checked="checked"{/if}
   name="{g->formVar var="form[type]"}" value="select"/>
  <label for="rbSelect">
    {g->text text="List box"}
  </label>
  <br/>
  <input type="radio" id="rbTree"{if $form.type=='tree'} checked="checked"{/if}
   name="{g->formVar var="form[type]"}" value="tree"/>
  <label for="rbTree">
    {g->text text="Tree"}
  </label>
  <br/>

  <input type="checkbox" id="cbShow"{if $form.show} checked="checked"{/if}
   name="{g->formVar var="form[show]"}"/>
  <label for="cbShow">
    {g->text text="Show in sidebar"}
  </label>

  <h4> {g->text text="Sort order"} </h4>

  <input type="radio" id="rbSortManual"{if !$form.sort} checked="checked"{/if}
   name="{g->formVar var="form[sort]"}" value="0"/>
  <label for="rbSortManual">
    {g->text text="Use manual sort order of albums"}
  </label>
  <br/>

  <input type="radio" id="rbSortTitle"{if $form.sort} checked="checked"{/if}
   name="{g->formVar var="form[sort]"}" value="1"/>
  <label for="rbSortTitle">
    {g->text text="Sort albums by title"}
  </label>

  <h4> {g->text text="Tree"} </h4>

  <input type="checkbox" id="cbLines"{if $form.treeLines} checked="checked"{/if}
   name="{g->formVar var="form[treeLines]"}"/>
  <label for="cbLines">
    {g->text text="Connect tree branches with lines"}
  </label>
  <br/>

  <input type="checkbox" id="cbIcons"{if $form.treeIcons} checked="checked"{/if}
   name="{g->formVar var="form[treeIcons]"}"/>
  <label for="cbIcons">
    {g->text text="Show folder icons"}
  </label>
  <br/>

  <input type="checkbox" id="cbCookies"{if $form.treeCookies} checked="checked"{/if}
   name="{g->formVar var="form[treeCookies]"}"/>
  <label for="cbCookies">
    {g->text text="Use cookies to remember which branches are open"}
  </label>
  <br/>

  <input type="checkbox" id="cbExpandCollapse"{if $form.treeExpandCollapse} checked="checked"{/if}
   name="{g->formVar var="form[treeExpandCollapse]"}"/>
  <label for="cbExpandCollapse">
    {g->text text="Show expand-all and collapse-all options"}
  </label>
  <br/>

  <input type="checkbox" id="cbCloseSameLevel"{if $form.treeCloseSameLevel} checked="checked"{/if}
   name="{g->formVar var="form[treeCloseSameLevel]"}"/>
  <label for="cbCloseSameLevel">
    {g->text text="Only one branch within a parent can be expanded at the same time. Expand/collapse functions are disabled with this option."}
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
