  <table border="1" cellspacing="0" cellpadding="0" width="100%">
    <tr>
      <td valign=top>
	<table border="1" cellspacing="0" cellpadding="0">
	  {foreach from=$tabs item=tab}
	  <tr>
	    <td>
	      {if $tab.selected == 0}
	      <a href="{galleryUrl view="core:SiteAdmin" selectedTab=$tab.name}">{$tab.name}</a>
	      {else}
	      {$tab.name}
	      {/if}
	    </td>
	  </tr>
	  {/foreach}
	</table>
      </td>
      <td width="100%">
	{$moduleHtml}
      </td>
    </tr>
  </table>
