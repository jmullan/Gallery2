{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsSystemLinks" class="gcBorder1">
  <ul class="gbBreadCrumb">
    <li class="firstChild">
      <a href="{g->url}">{$MembersProfile.rootAlbum.title}</a>
    </li>
    <li>
      <a href="{g->url arg1="view=members:MembersList"}">{g->text text="Members List"}</a>
    </li>
    <li>
      {g->text text="Members Profile"}
    </li>
  </ul>
</div>

<table width="100%" cellspacing="0" cellpadding="0">
  <colgroup width="1*,*"/>
  <tr valign="top"><td>
    {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}
  </td><td>

  <div id="gsContent" class="gcBorder1">
    <div class="gbBlock gcBackground1">
      <h2> {g->text text="Member Profile for %s" arg1=$MembersProfile.user.userName} </h2>
    </div>

    <div class="gbBlock">
      <table class="gbDataTable">
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {g->text text="Name:"}
	</td><td>
	  {$MembersProfile.user.fullName}
	</td>
      </tr>
  
      {if $MembersProfile.canViewProfileEmail}	
      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {g->text text="E-mail:"}
	</td><td>
	  {if sizeof($MembersProfile.user.email)} 
	    {mailto address=$MembersProfile.user.email encode="hex"}
	  {else}
	    {g->text text="None"}
	  {/if}        
	</td>
      </tr>
      {/if}

      <tr class="{cycle values="gbEven,gbOdd"}">
	<td>
	  {g->text text="Member Since:"}
	</td><td>
	  {g->date timestamp=$MembersProfile.user.creationTimestamp}
	  {if $MembersProfile.daysSinceCreation > 0}
	    {g->text one="(%d day)" many="(%d days)"
                   count=$MembersProfile.daysSinceCreation arg1=$MembersProfile.daysSinceCreation}
	  {elseif $MembersProfile.daysSinceCreation == 0}
	    {g->text text="(today)"}                
	  {/if}                 
	</td>
      </tr>

      <tr class="{cycle values="gbEven,gbOdd"}">
	<td valign="top">
	  {g->text text="Last Items:"}
	</td><td>
	{if count($MembersProfile.lastItems)}
	  <table>
	  {foreach from=$MembersProfile.lastItems item=item}
	  <tr>
	    <td>
	    {if $item.canContainChildren}
	      <img src="{g->url href="modules/members/data/directory.gif"}"
		   alt="{g->text text="Album"}" width="16" height="16"/>
	    {else}
	      <img src="{g->url href="modules/members/data/file.gif"}"
		   alt="{g->text text="Item"}" width="16" height="16"/>
	    {/if}
	    </td><td>
	      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}">
		{$item.title|default:$item.pathComponent}
	      </a>
	    </td>
	  </tr>
	  {/foreach}
	  <tr>
	    <td colspan="2">
	      <a href="{g->url arg1="view=members:MembersItems"
	       arg2="userId=`$MembersProfile.user.id`"}">
		{g->text text="List All &raquo;"}
	      </a>
	    </td>
	  </tr></table>
	{else}
	  {g->text text="None"}
	{/if}
	</td>
      </tr></table>
    </div>
  </div>
  </td></tr>
</table>
