{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to WatermarkSiteAdmin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="Watermark Images"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.add)}
      <div class="giStatus">{g->text text="New image added successfully"}</div>
    {/if}
    {if isset($status.delete)}
      <div class="giStatus">{g->text text="Image deleted successfully"}</div>
    {/if}
    {if isset($status.add_error)}
      <div class="giError">{g->text text="Missing image file"}</div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <table class="gbDataTable" width="100%">
      <tr>
        <th> {g->text text="File"} </th>
        <th> {g->text text="Image"} </th>
        <th> {g->text text="Owner"} </th>
        <th> {g->text text="Action"} </th>
      </tr>
      {foreach from=$form.list item=item}
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td> {$item.name} </td>
        <td> {g->image item=$item image=$item maxSize=150} </td>
	<td> 
	  <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=core:AdminEditUser" arg3="userId=`$item.ownerId`"}">
	    {$WatermarkSiteAdmin.owners[$item.ownerId].fullName|default:$WatermarkSiteAdmin.owners[$item.ownerId].userName}
	  </a>
       </td>

        <td>
	  <ul class="giHorizontalLinks">
            <li> 
	      <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=watermark:WatermarkSiteAdminEdit" 
                               arg3="itemId=`$item.id`"}">
                {g->text text="edit"}
              </a>
            </li>
	    <li>
              <a href="{g->url arg1="controller=watermark:WatermarkSiteAdmin"
                               arg2="form[action][delete]=1" arg3="form[delete][itemId]=`$item.id`"}">
                {g->text text="delete"}
              </a>
            </li>
          </ul>
        </td>
      </tr>
      {/foreach}
    </table>
    <input type="file" name="{g->formVar var="form[1]"}" size="60"/>
    <input type="submit" name="{g->formVar var="form[action][add]"}" value="{g->text text="add"}"/>
  </div>
</div>
