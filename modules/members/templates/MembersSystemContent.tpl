{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to MembersSystemContent.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbMenu">

  <h3 class="giTitle">
    {g->text text="Members"}
  </h3>

  <ul>
    <li>
    {g->text one="%s member" 
	     many="%s members"
	     count=$MembersSystemContent.membersCount
	     arg1=$MembersSystemContent.membersCount}

    </li>
  {foreach from=$MembersSystemContent.links item=link}
    <li>
      <a href="{g->url params=$link.params}">
        {$link.text}
      </a>
    </li>
  {/foreach}
  </ul>

</div>
