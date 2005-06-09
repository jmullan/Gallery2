{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<form action="{g->url}" method="post"
      enctype="{$UserAdmin.enctype|default:"application/x-www-form-urlencoded"}">
  <div>
    {g->hiddenFormVars}
    <input type="hidden" name="{g->formVar var="controller"}" value="{$controller}"/>
    <input type="hidden" name="{g->formVar var="form[formName]"}" value="{$form.formName}"/>
  </div>

  <div id="gsSystemLinks" class="gcBorder1">
    <div>
    {foreach from=$UserAdmin.moduleSystemLinks item=module}
      {foreach from=$module item=link}
      {if isset($link.params.view) && $link.params.view == "core.UserAdmin"}
	<span> {$link.text} </span>
      {else}
	<span> <a href="{g->url params=$link.params}">{$link.text}</a> </span>
      {/if}
      {/foreach}
    {/foreach}
    </div>

    <ul class="gbBreadCrumb">
      <li class="firstChild">
	<a href="{g->url}">{$UserAdmin.rootAlbum.title|markup:stripBbcodeAndHtml}</a>
      </li>
      <li>
	{g->text text="Your Account"}
      </li>
      {if !$user.isGuest}
      <li>
	{$user.fullName|default:$user.userName}
      </li>
      {/if}
    </ul>
  </div>

  <table width="100%" cellspacing="0" cellpadding="0">
    <tr valign="top">
    <td id="gsSidebarCol"><div id="gsSidebar" class="gcBorder1">
      <div class="gbBlock">
	<h2> {g->text text="User Options"} </h2>
	<ul>
	  {foreach from=$UserAdmin.subViewChoices item=choice}
	    <li class="gbAdminLink {g->linkId urlParams=$choice}">
	    {if ($UserAdmin.subViewName == $choice.view)}
	      {$choice.name}
	    {else}
	      <a href="{g->url arg1="view=core.UserAdmin" arg2="subView=`$choice.view`"}">
		{$choice.name}
	      </a>
	    {/if}
	    </li>
	  {/foreach}
	</ul>
      </div>

      <div class="gbBlock">
	<h2> {g->text text="Navigation"} </h2>
	<ul>
	  {foreach from=$UserAdmin.navigationLinks item=link}
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
	{include file="gallery:`$UserAdmin.viewBodyFile`" l10Domain=$UserAdmin.viewL10Domain}
      </div>
    </td>
  </tr></table>
</form>
{* Content subView wants to display outside main form/table: *}
{if isset($smarty.capture.UserAdmin_footer)} {$smarty.capture.UserAdmin_footer} {/if}
