{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<form action="{g->url}" method="post" enctype="{$ItemAdmin.enctype}">
  <div>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}"/>
    <input type="hidden" name="{g->formVar var="itemId"}" value="{$ItemAdmin.item.id}"/>
  </div>

  <div id="gsSystemLinks" class="gcBorder1">
    <div>
    {foreach from=$ItemAdmin.moduleSystemLinks item=module}
      {foreach from=$module item=link}
	<span> <a href="{g->url params=$link.params}">{$link.text}</a> </span>
      {/foreach}
    {/foreach}
    </div>

    <ul class="gbBreadCrumb">
      {foreach name="parent" from=$ItemAdmin.parents item=parent}
      <li {if $smarty.foreach.parent.first}class="firstChild"{/if}>
	<a href="{g->url arg1="view=core:ShowItem"
	   arg2="itemId=`$parent.id`"}">{$parent.title|default:$parent.pathComponent|markup}</a>
      </li>
      {/foreach}

      <li {if empty($ItemAdmin.parents)}class="firstChild"{/if}>
	<a href="{g->url arg1="view=core:ShowItem"
	   arg2="itemId=`$ItemAdmin.item.id`"}">{$ItemAdmin.item.title|default:$ItemAdmin.item.pathComponent|markup}</a>
      </li>
    </ul>
  </div>

  <table width="100%" cellspacing="0" cellpadding="0">
    <tr valign="top">
    <td id="gsSidebarCol"><div id="gsSidebar" class="gcBorder1">
      {if !$ItemAdmin.isRootAlbum or !empty($ItemAdmin.thumbnail)}
      <div class="gbBlock">
	{if empty($ItemAdmin.thumbnail)}
	  {g->text text="No Thumbnail"}
	{else}
	  {g->image item=$ItemAdmin.item image=$ItemAdmin.thumbnail maxSize=130}
	{/if}
	<h3> {$ItemAdmin.item.title|markup} </h3>
      </div>
      {/if}

      <div class="gbBlock">
	<h2> {g->text text="Options"} </h2>
	<ul>
	  {foreach from=$ItemAdmin.subViewChoices key=choiceName item=choiceParams}
	    <li class="gbAdminLink" id="{g->adminlinkid arg1=$choiceParams}">
	    {if isset($choiceParams.active)}
	      {$choiceName}
	    {else}
	      <a href="{g->url params=$choiceParams}"> {$choiceName} </a>
	    {/if}
	    </li>
	  {/foreach}
	</ul>
      </div>

      <div class="gbBlock">
	<h2> {g->text text="Navigation"} </h2>
	<ul>
	  {foreach from=$ItemAdmin.navigationLinks item=link}
	    <li>
	      <a href="{$link.url}">
		{$link.name}
	      </a>
	    </li>
	  {/foreach}
	</ul>
      </div>
    </div></td>

    <td>
      <div id="gsContent" class="gcBorder1">
	{include file="gallery:`$ItemAdmin.viewBodyFile`" l10Domain=$ItemAdmin.viewL10Domain}
      </div>
    </td>
  </tr></table>
</form>
