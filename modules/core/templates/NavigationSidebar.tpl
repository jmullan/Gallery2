{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsSidebar" class="gcBorder1">
  {* Core System content *}
  {if isset($Navigation.systemContent.core.core)}
    {assign var=moduleFile value=$Navigation.systemContent.core.core}
    {include file="gallery:$moduleFile" l10Domain="modules_core"}
  {/if}

  {* Search form, if module's activated *}
  {if isset($Navigation.systemContent.search.searchBox)}
    {assign var=moduleFile value=$Navigation.systemContent.search.searchBox}
    {include file="gallery:$moduleFile" l10Domain="modules_search"}
  {/if}

  {if $Navigation.navigationLinks}
    <div class="gbBlock">
      <h2> {g->text text="Navigation"} </h2>

      <ul>
      {foreach from=$Navigation.navigationLinks item=link}
	<li>
	  <a href="{$link.url}">
	    {$link.name}
	  </a>
	</li>
      {/foreach}
      </ul>
    </div>
  {/if}

  {* Extra modules system content *}
  {foreach from=$Navigation.systemContent key=moduleId item=moduleContent}
    {foreach from=$moduleContent key=moduleContentKey item=moduleFile}
      {if ($moduleId != 'search' || $moduleContentKey != 'searchBox') && ($moduleId != 'core' || $moduleContentKey != 'core')}
	{include file="gallery:$moduleFile" l10Domain="modules_$moduleId"}
      {/if}
    {/foreach}
  {/foreach}
</div>
