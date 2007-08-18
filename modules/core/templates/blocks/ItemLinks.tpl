{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
{if !isset($links) && isset($theme.itemLinks)}
  {assign var="links" value=$theme.itemLinks}
{/if}
{if !empty($links)}
  {if empty($item)}
    {assign var="item" value=$theme.item}
  {/if}
  {if !isset($lowercase)}
    {assign var="lowercase" value=false}
  {/if}
  {if !isset($useDropdown)}
    {assign var="useDropdown" value=true}
  {/if}

  <div class="{$class}">
    {* If more than one link and $useDropdown is true, use a dropdown.  Otherwise render as links. *}
    {if count($links) > 1 && $useDropdown}
      <select onchange="var value = this.value; this.options[0].selected = true; eval(value)">
	<option value="">
	  {if $item.canContainChildren}
	    {g->text text="&laquo; album actions &raquo;"}
	  {else}
	    {g->text text="&laquo; item actions &raquo;"}
	  {/if}
	</option>
	{foreach from=$links item="link"}
	  <option value="{if isset($link.script)}{$link.script}{else}window.location = '{g->url params=$link.params options=$link.options}'{/if}"
		{if !empty($link.selected)} selected="selected"{/if}>
	    {if $lowercase}
	      {$link.text|lower}
	    {else}
	      {$link.text}
	    {/if}
	  </option>
	{/foreach}
      </select>
    {else}
      {foreach from=$links item="link"}
        <a class="gbAdminLink {g->linkid urlParams=$link.params}" href="{g->url params=$link.params options=$link.options}"{if isset($link.script)} onclick="{$link.script};return false"{/if}{if isset($link.attrs)} {$link.attrs}{/if}>{if $lowercase}{$link.text|lower}{else}{$link.text}{/if}</a>
      {/foreach}
    {/if}
  </div>
{/if}
