{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to SiteAdmin.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <div class="giTitle">
        {g->text text="My Watermarks"}
      </div>
    </div>
  </div>

  {if !empty($status) || !empty($form.error)}
  <div id="gsStatus">
    {if isset($status.add)}
    <div class="giStatus">
      {g->text text="New image added successfully"}
    </div>
    {/if}
    {if isset($status.delete)}
    <div class="giStatus">
      {g->text text="Image deleted successfully"}
    </div>
    {/if}
    {if isset($form.error)}
    <div class="giError">
      {g->text text="There was a problem processing your request."}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <table class="gbDataTable" width="100%">
      <tr>
        <th> {g->text text="File"} </th>
        <th> {g->text text="Image"} </th>
        <th> {g->text text="Action"} </th>
      </tr>
      {foreach from=$form.list item=item}
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td> {$item.name} </td>
        <td> {g->image item=$item image=$item maxSize=150} </td>
        <td>
          <a href="{g->url arg1="controller=watermark:UserWatermarks"
                           arg2="form[action][delete]=1" arg3="form[delete][itemId]=`$item.id`"}">
            {g->text text="delete"}
          </a>
        </td>
      </tr>
      {/foreach}
    </table>
    <input type="file" name="{g->formVar var="form[1]"}" size="60"/>
    <input type="submit" name="{g->formVar var="form[action][add]"}" value="{g->text text="add"}"/>
    {if isset($form.error.missingFile)}
    <div class="giError">
      {g->text text="You must enter the path to a file to upload"}
    </div>
    {/if}
  </div>
</div>
