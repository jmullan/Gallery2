{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Sort order"}
  </h2>
  <p class="giDescription">
    {g->text text="This sets the sort order for the album.  This applies to all current items, and any newly added items."}
  </p>

  <select name="{g->formVar var="form[orderBy]"}" onChange="pickOrder()">
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
    function pickOrder() {ldelim}
      var list = '{g->formVar var="form[orderBy]"}';
      var index = document.forms[0].elements[list].selectedIndex;
      list = '{g->formVar var="form[orderDirection]"}';
      document.forms[0].elements[list].disabled = (index <= 1) ?1:0;
      list = '{g->formVar var="form[presort]"}';
      document.forms[0].elements[list].disabled = (index <= 1) ?1:0;
    {rdelim}
    pickOrder();
  </script>
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Layout"}
  </h2>
  <p class="giDescription">
    {g->text text="Choose a layout for this album. (The way the album is arranged on the page)"}
  </p>

  <select name="{g->formVar var="form[layout]"}">
      {html_options options=$ItemEditAlbum.layoutList selected=$form.layout}
  </select>
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Theme"}
  </h2>
  <p class="giDescription">
    {g->text text="Choose a theme for this album.  (The look and feel of this album)"}
  </p>

  <select name="{g->formVar var="form[theme]"}">
      {html_options options=$ItemEditAlbum.themeList selected=$form.theme}
  </select>
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Thumbnails"}
  </h2>
  <p class="giDescription">
    {g->text text=" Every item requires a thumbnail. Set the default size in pixels here."}
  </p>
  
  <input type="text" size="6" name="{g->formVar var="form[thumbnail][size]"}" value="{$form.thumbnail.size}"/>
    
  {if !empty($form.error.thumbnail.size.invalid)}
  <div class="giError">
    {g->text text="You must enter a number (greater than zero)"}
  </div>
  {/if}
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Resized Images"}
  </h2>
  <p class="giDescription">
    {g->text text="Each item in your album can have multiple sizes. Define the default sizes here."}
  </p>

  <table class="gbDataTable">
    <tr>
      <th align="center">
	{g->text text="Active"}
      </th>
      <th>
	{g->text text="Target Size (pixels)"}
      </th>
    </tr>

    {counter start=0 assign=index}
    {foreach from=$form.resizes item=resize}
    <tr class="{cycle values="gbEven,gbOdd"}">
      <td align="center">
	<input type="checkbox" name="{g->formVar var="form[resizes][$index][active]"}" 
	       {if $form.resizes.$index.active}checked="checked"{/if} />
      </td>
      <td>
	{g->dimensions formVar="form[resizes][$index]" width=$form.resizes.$index.width
						       height=$form.resizes.$index.height}
      </td>
    </tr>

    {if !empty($form.error.resizes.$index.size.missing)}
    <tr>
      <td colspan="2">
	<div class="giError">
	  {g->text text="You must enter a valid size"}
	</div>
      </td>
    </tr>
    {/if}
	  
    {if !empty($form.error.resizes.$index.size.invalid)}
    <tr>
      <td colspan="2">
	<div class="giError">
	  {g->text text="You must enter a number (greater than zero)"}
	</div>
      </td>
    </tr>
    {/if}
    {counter}
    {/foreach}
  </table>
</div>

<div class="gbAdmin">
  <h2 class="giTitle">
    {g->text text="Recreate thumbnails and resizes"}
  </h2>
  <p class="giDescription">
    {g->text text="The thumbnail and resized image settings are for all new items. To apply these settings to all the items in your album, check the appropriate box."}
  </p>

  <input id="recreateThumbnails" type="checkbox" name="{g->formVar var="form[recreateThumbnails]"}"
         {if $form.recreateThumbnails}checked="checked"{/if} />
  <label for="recreateThumbnails">
    {g->text text="Recreate thumbnails"}
  </label>

  <br/>

  <input id="recreateResizes" type="checkbox" name="{g->formVar var="form[recreateResizes]"}"
         {if $form.recreateResizes}checked="checked"{/if} />
  <label for="recreateResizes">
    {g->text text="Recreate resized images"}
  </label>
</div>

{* Include our extra ItemEditOptions *}
{foreach from=$ItemEdit.options item=option}
  {include file="gallery:`$option.file`" l10Domain=$option.l10Domain}
{/foreach}

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
</div>
