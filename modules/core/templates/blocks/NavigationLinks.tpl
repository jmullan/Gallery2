{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
{if !empty($navigationLinks)}
<div class="{$class}">
  <h3> {g->text text="Navigation"} </h3>
  <ul>
    {foreach from=$navigationLinks item=link}
      <li>
        <a href="{$link.url}">
          {$link.name}
        </a>
      </li>
    {/foreach}
  </ul>
</div>
{/if}
