{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to AdminMembers.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="Members Settings"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
      <div class="giStatus"> {g->text text="Settings saved successfully"} </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
     {g->text text="This will select who can see the members list and member profiles."}
    </p>
    
    <table style="gbDataEntry">
      <tr>
	<td>
	  <select name="{g->formVar var="form[canViewMembersModule]"}">
	    {html_options options=$Members.memberViews selected=$form.canViewMembersModule}
	  </select>
	</td>
      </tr>
    </table>
  </div>
  
  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="This will select if email addresses are displayed in the member profiles.  Administrators will always be able to see email addresses."}
    </p>
    
    <table style="gbDataEntry">
      <tr>
	<td>
	  <select name="{g->formVar var="form[canViewEmailAddress]"}">
	    {html_options options=$Members.emailViews selected=$form.canViewEmailAddress}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
    <input type="submit" name="{g->formVar var="form[action][cancel]"}" value="{g->text text="Reset"}"/>
  </div>
</div>
