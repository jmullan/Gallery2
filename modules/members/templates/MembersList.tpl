<div id="gsHeader">
  <!-- header -->
</div>

<ul class="gbBreadCrumb">
  <li class="giBreadCrumbFirst">
    <a href="{g->url}">
      {g->text text="Gallery"}
    </a>
  </li>
  <li>
    {g->text text="Members List"}
  </li>
</ul>

<div id="gsOtherContents">
  {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}	    

  <div class="gbTopFlag">
    <div class="gbTitleBanner">
      <div class="giTitle">
        {g->text one="%d user"
                 many="%d users"
                 count=$form.list.totalUserCount
                 arg1=$form.list.totalUserCount}
      </div>
    </div>
  </div>

  <table class="gbDataTable">
    {if ($form.list.maxPages > 1)}
    <tr>
      <th colspan="3">
        <table>
          <tr>
            <th align="left">
	      <input type="hidden" name="{g->formVar var="form[list][page]"}" value="{$form.list.page}"/>
              <input type="hidden" name="{g->formVar var="form[list][maxPages]"}" value="{$form.list.maxPages}"/> 	
	      {if ($form.list.page > 1)}
	      <a href="{g->url arg1="view=members:MembersList" arg2="form[list][page]=1"}">
		{g->text text="&laquo; first"}
	      </a>
	      &nbsp;
	      <a href="{g->url arg1="view=members:MembersList" arg2="form[list][page]=`$form.list.backPage`"}">
		{g->text text="&laquo; back"}
	      </a>
	      {else}
	      {g->text text="&laquo; first"}
	      &nbsp;
	      {g->text text="&laquo; back"}
	      {/if}
            </th>
            <th align="center">
	      {g->text text="Viewing page %d of %d"
                       arg1=$form.list.page
	               arg2=$form.list.maxPages}
            </th>
            <th align="right">
	      {if ($form.list.page < $form.list.maxPages)}
	      <a href="{g->url arg1="view=members:MembersList" arg2="form[list][page]=`$form.list.nextPage`"}">
		{g->text text="next &raquo;"}
	      </a>
	      &nbsp;
	      <a href="{g->url arg1="view=members:MembersList" arg2="form[list][page]=`$form.list.maxPages`"}">
		{g->text text="last &raquo;"}
	      </a>
	      {else}
	      {g->text text="next &raquo;"}
	      &nbsp;
	      {g->text text="last &raquo;"}
	      {/if}
            </th>
          </tr>
        </table>
      </th>
    </tr>
    {/if}

    <tr>
      <th>
	{g->text text="Username"}
      </th>
      <th>
	{g->text text="Full Name"}
      </th>
    </tr>

    {foreach from=$MembersList.users item=user}
    <tr class="{cycle values="gbEven,gbOdd"}">
      <td>
        <a href="{g->url arg1="view=members:MembersProfile" arg2="userId=`$user.id`"}">
	  {$user.userName}
	</a>
      </td>
      <td>
        {$user.fullName}
      </td>
    </tr>
    {/foreach}
  </table>
</div>

