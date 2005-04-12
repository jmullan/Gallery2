{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock gcBackground1">
  <h2> {g->text text="Watermark Images"} </h2>
</div>

{if !empty($status)}
<div class="gbBlock"><h2 class="giSuccess">
  {if isset($status.saved)}
    {g->text text="Watermark updated successfully"}
  {/if}
  {if isset($status.delete)}
    {g->text text="Image deleted successfully"}
  {/if}
  {if isset($status.add_error)}
    <span class="giError">{g->text text="Missing image file"}</span>
  {/if}
</h2></div>
{/if}

<div class="gbBlock">
  <table class="gbDataTable" width="100%"><tr>
    <th> {g->text text="File"} </th>
    <th> {g->text text="Image"} </th>
    <th> {g->text text="Owner"} </th>
    <th> {g->text text="Action"} </th>
  </tr>
  {foreach from=$form.list item=item}
  <tr class="{cycle values="gbEven,gbOdd"}">
    <td>
      {$item.name}
    </td><td>
      {g->image item=$item image=$item maxSize=150}
    </td><td>
      <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminEditUser"
       arg3="userId=`$item.ownerId`"}">
	{$WatermarkSiteAdmin.owners[$item.ownerId].fullName|default:$WatermarkSiteAdmin.owners[$item.ownerId].userName}
      </a>
    </td><td>
      <a href="{g->url arg1="view=core:SiteAdmin"
       arg2="subView=watermark:WatermarkSiteAdminEdit" arg3="itemId=`$item.id`"}">
	{g->text text="edit"}
      </a>
      &nbsp;
      <a href="{g->url arg1="controller=watermark:WatermarkSiteAdmin"
       arg2="form[action][delete]=1" arg3="form[delete][itemId]=`$item.id`"}">
	{g->text text="delete"}
      </a>
    </td>
  </tr>
  {/foreach}
  </table>

  <input type="file" size="60" name="{g->formVar var="form[1]"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][add]"}" value="{g->text text="Add"}"/>
</div>
