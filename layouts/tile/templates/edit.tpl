{*
 * $Revision$ $Date$
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to hybrid.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<br/>
<div class="giDescription">
  {g->text text="A tile layout consists of a background image shown as a grid of tiles with thumbnails for other images placed in any tile position over the background.  Set the size and number of tiles, select the background image and assign thumbnail positions below.  Row 1, Column 1 is the upper left corner."}
</div>
<table><tr>
<td>{g->text text="Rows"}</td>
<td><input type="text" name="{g->formVar var="form[rows]"}" value="{$layout.params.rows}" size="4"></td>
</tr><tr>
<td>{g->text text="Columns"}</td>
<td><input type="text" name="{g->formVar var="form[cols]"}" value="{$layout.params.cols}" size="4"></td>
</tr><tr>
<td>{g->text text="Cell Width"}</td>
<td><input type="text" name="{g->formVar var="form[cellWidth]"}" value="{$layout.params.cellWidth}" size="4"></td>
</tr><tr>
<td>{g->text text="Cell Height"}</td>
<td><input type="text" name="{g->formVar var="form[cellHeight]"}" value="{$layout.params.cellHeight}" size="4"></td>
</tr></table>

<table>
<tr><th colspan="2" style="text-align:right">{g->text text="Background"}</th>
<th>{g->text text="Title"}</th>
<th>{g->text text="Row"}</th>
<th>{g->text text="Column"}</th></tr>
{foreach from=$layout.children key=i item=it}
  {if isset($it.image)}
    <tr><td>
    {if isset($it.thumbnail)}
      {g->image item=$it image=$it.thumbnail maxSize=100 class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    </td><td>
    <input type="radio" name="{g->formVar var="form[backgroundId]"}" value="{$it.image.id}"
      {if $layout.params.backgroundId==$it.image.id}checked{/if}>
    </td><td>
    <span class="giTitle">{$it.title|markup}</span>
    </td><td>
    {assign var="key" value="row_`$it.image.id`"}
    <input type="text" size="3" name="{g->formVar var="form[row_`$it.image.id`]"}" value="{$layout.params[$key]|default:''}">
    </td><td>
    {assign var="key" value="col_`$it.image.id`"}
    <input type="text" size="3" name="{g->formVar var="form[col_`$it.image.id`]"}" value="{$layout.params[$key]|default:''}">
    </td></tr>
  {/if}
{/foreach}
</table>
