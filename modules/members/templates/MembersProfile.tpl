<ul class="gbBreadCrumb">
  <li class="giBreadCrumbFirst">
    <a href="{g->url}">{$MembersProfile.rootAlbum.title}</a>
  </li>
  <li>
    <a href="{g->url arg1="view=members:MembersList"}">{g->text text="Members List"}</a>
  </li>
  <li>
    {g->text text="Member Profile"}
  </li>
</ul>

<div id="gsContents">
  {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}	    

  <div id="gsOtherContents">
  
    <div class="gbTopFlag">
      <div class="gbTitleBanner">
        <h1 class="gbTitle">
  	  {g->text text="Member Profile for %s" arg1=$MembersProfile.user.userName}
        </h1>
      </div>
    </div>
  
    <table class="gbDataTable">
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td>
  	  {g->text text="Name:"}
        </td>
        <td>
  	  {$MembersProfile.user.fullName}
        </td>
      </tr>
  
      {if $MembersProfile.canViewProfileEmail}	
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td>
          {g->text text="E-mail:"}
        </td>
        <td>
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
        </td>
        <td>
  	  {g->date timestamp=$MembersProfile.user.creationTimestamp}
  	  {if $MembersProfile.daysSinceCreation > 0}
  	  {g->text one="(%d day)"
                   many="(%d days)"
                   count=$MembersProfile.daysSinceCreation
                   arg1=$MembersProfile.daysSinceCreation}
          {elseif $MembersProfile.daysSinceCreation == 0}
          {g->text text="(today)"}                
          {/if}                 
        </td>
      </tr>
  
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td valign="top">
  	{g->text text="Last Items:"}
        </td>
  
        <td>
	  <table>
  	  {if sizeof($MembersProfile.lastItems)}
  	  {foreach from=$MembersProfile.lastItems item=item}
  	    <tr>
              <td>
	      {if $item.canContainChildren}
  	        <img style="border: 0px"
                     src="{g->url href="modules/members/data/directory.gif"}"
                     alt="{g->text text="Album"}"
                     height="16"
                     width="16"/>
              </td>
  	      {else}
	        <img style="border: 0px"
                     src="{g->url href="modules/members/data/file.gif"}"
                     alt="{g->text text="Item"}"
                     height="16"
                     width="16"/>
              </td>
	      {/if}
  	      <td>
  	        <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}">
	          {$item.title|default:$item.pathComponent}
    	        </a>
  	        <br />
	      </td>
            </tr>
  	    {/foreach}
	    <tr>
              <td>
	        <a href="{g->url arg1="view=members:MembersItems"
                                 arg2="userId=`$MembersProfile.user.id`"}">{g->text text="List All &raquo;"}
                </a>
	      </td>
	    </tr>
    	  {else}
    	  {g->text text="None"}
  	  {/if}
	  </table>
        </td>
      </tr>	
    </table>
  </div>
</div>
