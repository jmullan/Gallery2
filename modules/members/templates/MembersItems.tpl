<ul class="gbBreadCrumb">
  <li class="giBreadCrumbFirst">
    <a href="{g->url}">{$MembersItems.rootAlbum.title}</a>
  </li>
  <li>
    <a href="{g->url arg1="view=members:MembersList"}">{g->text text="Members List"}</a>
  </li>
  <li>
    <a href="{g->url arg1="view=members:MembersProfile" 
		     arg2="userId=`$MembersItems.user.id`"}">{g->text text="Member Profile"}</a>
  </li>
  <li>
    {g->text text="Member Items"}
  </li>
</ul>

<div id="gsContents">
  {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}	    

  <div id="gsOtherContents">
  
    <div class="gbTopFlag">
      <div class="gbTitleBanner">
        <h1 class="gbTitle">
  	  {g->text text="Member Items for %s" arg1=`$MembersItems.user.userName`}
	  <br />
	  {g->text one="%d item total"
                   many="%d items total"
                   count=$form.list.count
                   arg1=$form.list.count} 
        </h1>
      </div>
    </div>
  
    <table class="gbDataTable">
      {if ($form.list.maxPages > 1)}
      <tr>
        <th colspan="4">
          <table>
            <tr>
              <th align="left">
                <input type="hidden" name="{g->formVar var="form[list][page]"}" value="{$form.list.page}"/>
                <input type="hidden" name="{g->formVar var="form[list][maxPages]"}" value="{$form.list.maxPages}"/>
                {if ($form.list.page > 1)}
                <a href="{g->url arg1="view=members:MembersItems" 
				 arg2="form[list][page]=1"
                                 arg3="userId=`$MembersItems.user.id`"}">
                  {g->text text="&laquo; first"}
                </a>
                &nbsp;
                <a href="{g->url arg1="view=members:MembersItems" 
			         arg2="form[list][page]=`$form.list.backPage`" 
				 arg3="userId=`$MembersItems.user.id`"}">
                  {g->text text="&laquo; back"}
                </a>
                {else}
                {g->text text="&laquo; first"}
                &nbsp;
                {g->text text="&laquo; back"}
                {/if}
              </th>
              <th>
                {g->text text="Viewing page %d of %d"
                         arg1=$form.list.page
                         arg2=$form.list.maxPages}
              </th>
              <th align="right">
                {if ($form.list.page < $form.list.maxPages)}
                <a href="{g->url arg1="view=members:MembersItems" 
				 arg2="form[list][page]=`$form.list.nextPage`" 
				 arg3="userId=`$MembersItems.user.id`"}">
                  {g->text text="next &raquo;"}
                </a>
                &nbsp;
                <a href="{g->url arg1="view=members:MembersItems" 
				 arg2="form[list][page]=`$form.list.maxPages`" 
				 arg3="userId=`$MembersItems.user.id`"}">
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
	  {g->text text="Type"}
	</th>
        <th>
          {g->text text="Date"}
        </th>
        <th>
          {g->text text="Time"}
        </th>
        <th>
          {g->text text="Name"}
        </th>
      </tr>
  
      {if sizeof($MembersItems.lastItems)}  	
        {foreach from=$MembersItems.lastItems item=item name=MembersItemsLoop}
  	<tr class="{cycle values="gbEven, gbOdd"}">
          <td>
            {if $item.canContainChildren}
            <img style="border: 0px"
                 src="{g->url href="modules/members/data/directory.gif"}"
                 alt="{g->text text="Album"}"
                 height="16"
                 width="16"/>
            {else}
            <img style="border: 0px"
                 src="{g->url href="modules/members/data/file.gif"}"
                 alt="{g->text text="Item"}"
                 height="16"
                 width="16"/>
            {/if}
          </td>
          <td>
            {g->date timestamp=$item.creationTimestamp format="%D"}
          </td>
          <td>
            {g->date timestamp=$item.creationTimestamp format="%l:%M:%S %p %Z"}
          </td>
	  <td>	
  	    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}">
	      {$item.title|default:$item.pathComponent}
  	    </a>
  	  </td>
	</tr>
	{/foreach}
      {else}
      <tr>
        <td>
          {g->text text="None"}
        </td>
      </tr>
      {/if}
    </table>
  </div>
</div>
