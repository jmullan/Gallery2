{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
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
      {g->text text="Watermark added successfully"}
    </div>
    {/if}
    {if isset($status.delete)}
    <div class="giStatus">
      {g->text text="Watermark deleted successfully"}
    </div>
    {/if}
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Watermark saved successfully"}
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
    <p class="giTitle">
      {g->text text="Upload Watermarks"}
    </p>
    <p class="giDescription">
      {g->text text="Add your own personal watermarks here.  These watermarks can only be used by you."}
    </p>
    <table class="gbDataTable" width="100%">
      <tr>
        <th> {g->text text="Name"} </th>
        <th> {g->text text="Image"} </th>
        <th> {g->text text="Action"} </th>
      </tr>
      {foreach from=$UserWatermarks.watermarks item=item}
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td> {$item.name} </td>
        <td> {g->image item=$item image=$item maxSize=150} </td>
        <td>
	  <ul class="giHorizontalLinks">
            <li> 
	      <a href="{g->url arg1="view=core:UserAdmin" arg2="subView=watermark:UserWatermarkEdit" 
                               arg3="itemId=`$item.id`"}">
                {g->text text="edit"}
              </a>
            </li>
            <li> 
	      <a href="{g->url arg1="controller=watermark:UserWatermarks"
                               arg2="form[action][delete]=1" arg3="form[delete][itemId]=`$item.id`"}">
                {g->text text="delete"}
              </a>
            </li>
          </ul>
        </td>
      </tr>
      {/foreach}
    </table>
    <input type="file" name="{g->formVar var="form[1]"}" size="40"/>
    <input type="submit" name="{g->formVar var="form[action][add]"}" value="{g->text text="add"}"/>
    {if isset($form.error.missingFile)}
    <div class="giError">
      {g->text text="You must enter the path to a file to upload"}
    </div>
    {/if}
  </div>
</div>
