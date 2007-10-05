{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}

<div class="gbBlock gcBackground1">
    <h2> {g->text text="User Notification Administration"} </h2>
</div>

{if isset($status.saved)}
<div class="gbBlock">
    <h2 class="giSuccess"> {g->text text="Settings saved successfully"} </h2>
</div>
{/if}

<div class="gbBlock">
    <table class="gbDataTable">
{* Events *}
	<tr>
	    <th colspan="4"> {g->text text="Events"} </th>
	</tr>
{foreach from=$form.notifications item=notification name=notifications}
    {assign var=i value=$smarty.foreach.notifications.iteration}
    {if $i % 30 == 1}
	<tr>
	    <th> &nbsp; </th>
	    <th> {g->text text="Description"} </th>
	    <th> {g->text text="Method"} </th>
	    <th> {g->text text="Subscribe"} </th>
	</tr>
    {/if}
    {assign var="subscriptionCount" value=$notification.items|@count}
	<tr>
	    
	    <td colspan="5">
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][name]"}" value="{$notification.name}">
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][description]"}" value="{$notification.description}">
	      {$notification.description}
	    </td>
	</tr>
    {foreach from=$notification.items item=item name=items}
	{assign var="j" value=$smarty.foreach.items.iteration}
	<tr>
	    <td >&nbsp;</td>
	    <td>
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][items][$j][url]"}" value="{$item.url}"/>
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][items][$j][title]"}" value="{$item.title}"/>
		{if !empty($item.url)}
		  <a href="{$item.url}">{$item.title|markup:strip}</a>
		{else}
		  {$item.title|markup:strip}
		{/if}
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][items][$j][itemId]"}" value="{$item.itemId}"/>
	    </td>
	    <td>
	      {$notification.handlerDescription}
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][handler]"}" value="{$notification.handler}">
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][handlerDescription]"}" value="{$notification.handlerDescription}">
	    </td>
	    <td align="center">
	      <input type="hidden" name="{g->formVar var="form[notifications][$i][items][$j][oldSubscribed]"}" value="{$item.subscribed}">
	      <input type="checkbox" 
		name="{g->formVar var="form[notifications][$i][items][$j][subscribed]"}" 
		{if !empty($item.subscribed)} checked="checked"{/if}/>
	    </td>
	    {if isset($form.error.notifications[$i].notAuthorized)}
	    <td>
	      <span class="giError">
		  {g->text text="Not authorized to receive notifications"}
	      </span>
	    </td>
	    {/if}
	</tr>
    {/foreach}
{foreachelse}
	<tr>
	    <td colspan="4"> {g->text text="You are not subscribed to any available events"} </td>
	</tr>
{/foreach}
    </table>
</div>

<div class="gbBlock gcBackground1">
    <input type="submit" class="inputTypeSubmit"
	name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}" />
    <input type="reset" class="inputTypeSubmit" value="{g->text text="Reset"}"/>
</div>
