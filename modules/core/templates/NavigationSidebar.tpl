{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to NavigationSidebar.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsSidebar">
  {* Module links *}
  <div class="gbMenu">
    <h3 class="giTitle">
      {g->text text="Greetings, %s!" arg1=$Navigation.user.fullName|default:$Navigation.user.userName}
    </h3>

    <ul>
      {foreach from=$Navigation.moduleSystemLinks item=module}
      {foreach from=$module item=link}
      <li>
	<a href="{g->url params=$link.params}">{$link.text}</a>
      </li>
      {/foreach}
      {/foreach}
    </ul>
  </div>

  {* Extra modules system content *}
  {foreach from=$Navigation.moduleSystemContentFiles key=moduleId item=moduleFile}
  {include file="gallery:$moduleFile" l10Domain="modules_$moduleId"}
  {/foreach}
</div>
