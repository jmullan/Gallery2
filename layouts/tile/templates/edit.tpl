{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to hybrid.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<br />
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
{foreach from=$layout.itemList key=i item=it}
  {if isset($it.image)}
    <tr><td>
    {if isset($it.thumb)}
      {g->image item=$it.data image=$it.thumb class=thumb}
    {else} {g->text text="no thumbnail"} {/if}
    </td><td>
    <input type="radio" name="{g->formVar var="form[backgroundId]"}" value="{$it.image.id}"
      {if $layout.params.backgroundId==$it.image.id}checked{/if}>
    </td><td>
    <span class="giTitle">{$it.data.title|markup}</span>
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
