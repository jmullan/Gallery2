{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to NavigationSidebar.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsSidebar">
  {* Module links *}

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
    <div class="gbMenu">
      <h2 class="giTitle"> {g->text text="Navigation"} </h2>
          
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
