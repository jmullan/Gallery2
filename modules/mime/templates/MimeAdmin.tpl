{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
        {g->text text="MIME maintenance"}
      </h2>
    </div>
  </div>
  <div class="gbAdmin">  
    <table class="gbDataTable">
      <tr>
        <th> {g->text text="MIME Types"} </th>
        <th> {g->text text="Extensions"} </th>
        <th> {g->text text="Viewable"} </th>
        <th> {g->text text="Actions"} </th>
      </tr>
      {foreach from=$MimeAdmin key=mime item=type}
      <tr class="{cycle values="gbEven,gbOdd"}">
        <td>{$mime}</td>
        <td>{$type.ext}</td>
        <td align="center">
          {if $type.viewable == 1}
          <img src="{g->url href="modules/core/data/module-active.gif"}" 
            width="13" height="13" alt="{g->text text="Viewable"}" 
            title="{g->text text="Viewable"}" />
          {else}
          &nbsp;
          {/if}
        </td>
        <td align="center">
          <a href="{g->url arg1="view=core:SiteAdmin" arg2="subView=mime:MimeEdit"
            arg3="mimeType=`$mime`"}">
          <img src="{g->url href="modules/mime/data/b_edit.png"}" 
            width="16" height="16" alt="{g->text text="edit"}" 
            title="{g->text text="edit"}" /></a>&nbsp;
          <input name="{g->formVar var="form[action][delete]"}"
            type="image" width="16" height="16" border="0"
            value="{$mime}"
            src="{g->url href="modules/mime/data/b_drop.png"}"
            alt="{g->text text="delete"}" title="{g->text text="delete"}" />
        </td>
      </tr>
      {/foreach}
    </table>
  </div>
      
  <div class="gbBottomFlag">
    <div class="gbButtons">
      <input type="submit" name="{g->formVar var="form[action][addNew]"}" 
        value="{g->text text="Add new type"}"/>
    </div>
  </div>
</div>  

