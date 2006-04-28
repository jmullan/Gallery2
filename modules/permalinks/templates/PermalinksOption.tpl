{*
 * $Revision: 1.3 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}

<div class="gbBlock">
  <h3> {g->text text="Permalinks"} </h3>
  <p class="giDescription">
    {g->text text="Edit the permalinks that refer to this item. You can add or delete permalinks."}
  </p>

  {if empty($PermalinksOption.aliases)}
    <p> {g->text text="You have no permalinks"} </p>
  {else}
    <p> {g->text text="Existing permalinks"} </p>

    <table class="gbDataTable">
    <tr>
      <th> {g->text text="Delete"} </th>
      <th> {g->text text="Permalink name"} </th>
    </tr>
    {foreach from=$PermalinksOption.aliases item=name}
	  <tr class="{cycle values="gbEven,gbOdd"}">
	    <td><input type="checkbox" 
	      name="{g->formVar var="form[PermalinksOption][delete][`$name`]"}"></td>
	    <td>{$name}</td>
	  </tr>
    {/foreach}
	</table>
  {/if}

  {if isset($form.error.PermalinksOption.exists)}
  <div class="giError">
    {g->text text="Permalink '%s' already exists, possibly on another item" 
      arg1=$form.PermalinksOption.aliasName}
  </div>
  {/if}

  <p><label for="Permalinks_aliasname"> {g->text text="Add a new permalink:"} </alias>
    <input type="text" name="{g->formVar var="form[PermalinksOption][aliasName]"}" 
      id="Permalinks_aliasname" />
    <a href="javascript:return false;" 
      onClick="javascript:document.forms['itemAdminForm'].Permalinks_aliasname.value='{$ItemAdmin.item.pathComponent}';">
      {g->text text="Set to '%s'" arg1="`$ItemAdmin.item.pathComponent`"}</a>
  </p>
  
</div>

