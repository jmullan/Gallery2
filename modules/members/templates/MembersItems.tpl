{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsSystemLinks" class="gcBorder1">
  <ul class="gbBreadCrumb">
    <li class="firstChild">
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
</div>

<table width="100%" cellspacing="0" cellpadding="0">
  <colgroup width="1*,*"/>
  <tr valign="top"><td>
    {include file="gallery:`$Navigation.sidebar`" l10Domain=$Navigation.l10Domain}
  </td><td>

  <div id="gsContent" class="gcBorder1">
    <div class="gbBlock gcBackground1">
      <h2>
	{g->text text="Member Items for %s" arg1=`$MembersItems.user.userName`}
	<br/>
	{g->text one="%d item total" many="%d items total"
		 count=$form.list.count arg1=$form.list.count}
      </h2>
    </div>

    <div class="gbBlock">
      {if ($form.list.maxPages > 1)}
      <div style="margin-bottom: 10px"><span class="gcBackground1" style="padding: 5px">
	<input type="hidden"
	 name="{g->formVar var="form[list][page]"}" value="{$form.list.page}"/>
	<input type="hidden"
	 name="{g->formVar var="form[list][maxPages]"}" value="{$form.list.maxPages}"/>

	{if ($form.list.page > 1)}
	  <a href="{g->url arg1="view=members:MembersItems"
	   arg2="form[list][page]=1" arg3="userId=`$MembersItems.user.id`"}">
	    {g->text text="&laquo; first"}
	  </a>
	  &nbsp;
	  <a href="{g->url arg1="view=members:MembersItems"
	   arg2="form[list][page]=`$form.list.backPage`" arg3="userId=`$MembersItems.user.id`"}">
	    {g->text text="&laquo; back"}
	  </a>
	{else}
	  {g->text text="&laquo; first"}
	  &nbsp;
	  {g->text text="&laquo; back"}
	{/if}

	&nbsp;
	{g->text text="Viewing page %d of %d" arg1=$form.list.page arg2=$form.list.maxPages}
	&nbsp;

	{if ($form.list.page < $form.list.maxPages)}
	  <a href="{g->url arg1="view=members:MembersItems"
	   arg2="form[list][page]=`$form.list.nextPage`" arg3="userId=`$MembersItems.user.id`"}">
	    {g->text text="next &raquo;"}
	  </a>
	  &nbsp;
	  <a href="{g->url arg1="view=members:MembersItems"
	   arg2="form[list][page]=`$form.list.maxPages`" arg3="userId=`$MembersItems.user.id`"}">
	    {g->text text="last &raquo;"}
	  </a>
	{else}
	  {g->text text="next &raquo;"}
	  &nbsp;
	  {g->text text="last &raquo;"}
	{/if}
      </span></div>
      {/if}

      <table class="gbDataTable"><tr>
	<th> {g->text text="Type"} </th>
	<th> {g->text text="Date"} </th>
	<th> {g->text text="Time"} </th>
	<th> {g->text text="Name"} </th>
      </tr>

      {if sizeof($MembersItems.lastItems)}
	{foreach from=$MembersItems.lastItems item=item name=MembersItemsLoop}
	<tr class="{cycle values="gbEven, gbOdd"}">
	  <td>
	  {if $item.canContainChildren}
	    <img src="{g->url href="modules/members/data/directory.gif"}"
		 alt="{g->text text="Album"}" width="16" height="16"/>
	  {else}
	    <img src="{g->url href="modules/members/data/file.gif"}"
		 alt="{g->text text="Item"}" width="16" height="16"/>
	  {/if}
	  </td><td>
	    {g->date timestamp=$item.creationTimestamp format="%D"}
	  </td><td>
	    {g->date timestamp=$item.creationTimestamp format="%l:%M:%S %p %Z"}
	  </td><td>
	    <a href="{g->url arg1="view=core:ShowItem" arg2="itemId=`$item.id`"}">
	      {$item.title|default:$item.pathComponent}
	    </a>
	  </td>
	</tr>
	{/foreach}
      {else}
	<tr><td>
	  {g->text text="None"}
	</td></tr>
      {/if}
      </table>
    </div>
  </div>
  </td></tr>
</table>
