{*
 * $Revision: 1.34 $
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <h2> {g->text text="Sort order"} </h2>

  <p class="giDescription">
    {g->text text="This sets the sort order for the album.  This applies to all current items, and any newly added items."}
  </p>

  <select name="{g->formVar var="form[orderBy]"}" onchange="pickOrder()">
    {html_options options=$ItemEditAlbum.orderByList selected=$form.orderBy}
  </select>
  <select name="{g->formVar var="form[orderDirection]"}">
    {html_options options=$ItemEditAlbum.orderDirectionList selected=$form.orderDirection}
  </select>
  {g->text text="with"}
  <select name="{g->formVar var="form[presort]"}">
    {html_options options=$ItemEditAlbum.presortList selected=$form.presort}
  </select>
  <script type="text/javascript">
    // <![CDATA[
    function pickOrder() {ldelim}
      var list = '{g->formVar var="form[orderBy]"}';
      var frm = document.getElementById('itemAdminForm');
      var index = frm.elements[list].selectedIndex;
      list = '{g->formVar var="form[orderDirection]"}';
      frm.elements[list].disabled = (index <= 1) ?1:0;
      list = '{g->formVar var="form[presort]"}';
      frm.elements[list].disabled = (index <= 1) ?1:0;
    {rdelim}
    pickOrder();
    // ]]>
  </script>
</div>

<div class="gbBlock">
  <h3> {g->text text="Theme"} </h3>
  <p class="giDescription">
    {g->text text="Choose a theme for this album. (The way the album is arranged on the page)"}
  </p>

  <select name="{g->formVar var="form[theme]"}">
    {html_options options=$ItemEditAlbum.themeList selected=$form.theme}
  </select>
</div>

<div class="gbBlock">
  <h3> {g->text text="Thumbnails"} </h3>
  <p class="giDescription">
    {g->text text=" Every item requires a thumbnail. Set the default size in pixels here."}
  </p>

  <input type="text" size="6"
   name="{g->formVar var="form[thumbnail][size]"}" value="{$form.thumbnail.size}"/>

  {if !empty($form.error.thumbnail.size.invalid)}
  <div class="giError">
    {g->text text="You must enter a number (greater than zero)"}
  </div>
  {/if}
</div>

<div class="gbBlock">
  <h3> {g->text text="Resized Images"} </h3>
  <p class="giDescription">
    {g->text text="Each item in your album can have multiple sizes. Define the default sizes here."}
  </p>

  <table class="gbDataTable"><tr>
    <th align="center"> {g->text text="Active"} </th>
    <th> {g->text text="Target Size (pixels)"} </th>
  </tr>
  {counter start=0 assign=index}
  {foreach from=$form.resizes item=resize}
  <tr class="{cycle values="gbEven,gbOdd"}">
    <td align="center">
      <input type="checkbox"{if $form.resizes.$index.active} checked="checked"{/if}
       name="{g->formVar var="form[resizes][$index][active]"}"/>
    </td><td>
     {g->dimensions formVar="form[resizes][$index]" width=$form.resizes.$index.width
						    height=$form.resizes.$index.height}
    </td>
  </tr>

  {if !empty($form.error.resizes.$index.size.missing)}
  <tr><td colspan="2" class="giError">
    {g->text text="You must enter a valid size"}
  </td></tr>
  {/if}
  {if !empty($form.error.resizes.$index.size.invalid)}
  <tr><td colspan="2" class="giError">
    {g->text text="You must enter a number (greater than zero)"}
  </td></tr>
  {/if}
  {counter}
  {/foreach}
  </table>
</div>

<div class="gbBlock">
  <h3> {g->text text="Recreate thumbnails and resizes"} </h3>
  <p class="giDescription">
    {g->text text="The thumbnail and resized image settings are for all new items. To apply these settings to all the items in your album, check the appropriate box."}
  </p>

  <input type="checkbox" id="cbRecreateThumbs"{if $form.recreateThumbnails} checked="checked"{/if}
   name="{g->formVar var="form[recreateThumbnails]"}"/>
  <label for="cbRecreateThumbs">
    {g->text text="Recreate thumbnails"}
  </label>
  <br/>

  <input type="checkbox" id="cbRecreateResizes"{if $form.recreateResizes} checked="checked"{/if}
   name="{g->formVar var="form[recreateResizes]"}"/>
  <label for="cbRecreateResizes">
    {g->text text="Recreate resized images"}
  </label>
</div>

{* Include our extra ItemEditOptions *}
{foreach from=$ItemEdit.options item=option}
  {include file="gallery:`$option.file`" l10Domain=$option.l10Domain}
{/foreach}

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][undo]"}" value="{g->text text="Reset"}"/>
</div>
