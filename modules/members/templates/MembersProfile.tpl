<div id="gsHeader">
  <div class="gbTitleBanner">
    <div class="gbBreadCrumb">
      <span class="giBreadCrumbFirst">
        <a href="{g->url}">
          {g->text text="Gallery"}
        </a>
      </span>
      <span>
        <a href="{g->url arg1="view=members:MembersList"}">
          {g->text text="Members List"}
        </a>
      </span>
      <span>
        {g->text text="Member Profile"}
      </span>
    </div>
  </div>
</div>

<div id="gsOtherContents">
  <div class="gbTopFlag">
    <div class="gbTitleBanner">
      <div class="gbTitle">
	{g->text text="User Profile for %s" arg1=$MembersProfile.user.userName}
      </div>
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
	<table>
	  {foreach from=$MembersProfile.lastItems item=item}
	  <tr>
	    <td>
	      {if $item.canContainChildren}
	      {g->text text="Album:"}
	      {/if}
	      {g->text text="&nbsp;"}
	    </td>

	    <td>
	      <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}">
		{$item.title|default:$item.pathComponent}
	      </a>
	    </td>
	  </tr>
	  {/foreach}
	</table>
	{else}
	{g->text text="None"}
	{/if}
      </td>
    </tr>	
  </table>
</div>


