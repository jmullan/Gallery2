<div id="gsHeader">
  <!-- header -->
</div>

<ul class="gbBreadCrumb">
  <li class="giBreadCrumbFirst">
    <a href="{g->url}">{g->text text="Gallery"}</a>
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
    	  {g->text text="User Profile for %s" arg1=$MembersProfile.user.userName}
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
    
        {if sizeof($MembersProfile.user.email)}	
        <tr class="{cycle values="gbEven,gbOdd"}">
          <td>
            {g->text text="E-mail:"}
          </td>
          <td>
            {mailto address=$MembersProfile.user.email encode="hex"}
          </td>
        </tr>
        {/if}
    
        <tr class="{cycle values="gbEven,gbOdd"}">
          <td>
    	{g->text text="Sign-up Date:"}
          </td>
          <td>
    	{g->date timestamp=$MembersProfile.user.creationTimestamp}
          </td>
        </tr>
    
        <tr class="{cycle values="gbEven,gbOdd"}">
          <td valign="top">
    	{g->text text="Last Five Items:"}
          </td>
    
          <td>
    	{if sizeof($MembersProfile.lastItems)}
    	<ul>
    	  {foreach from=$MembersProfile.lastItems item=item}
    	  <li>
    	      {if $item.canContainChildren}
    	      {g->text text="Album:"}
    	      {/if}
    	      {g->text text="&nbsp;"}
    	      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}">
    		{$item.title|default:$item.pathComponent}
    	      </a>
    	    <br />
    	  </li>
    	  {/foreach}
    	</ul>
    	{else}
    	{g->text text="None"}
    	{/if}
          </td>
        </tr>	
      </table>
    </div>
</div>
