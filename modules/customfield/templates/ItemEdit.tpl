{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to ItemEdit.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<div class="gbAdmin">
  <table class="gbDataTable">
  {foreach from=$form.fields key=field item=value}
    <tr><td>{$field}</td><td>
    {if isset($form.choices[$field])}
      <select name="{g->formVar var="form[fields][$field]"}">
	<option value="">&laquo; {g->text text="No Value"} &raquo;</option>
	{foreach from=$form.choices[$field] item=choice}<option{if
	    $choice==$value} selected="selected"{/if}>{$choice}</option>{/foreach}
      </select>
    {else}
      <input type="text" name="{g->formVar var="form[fields][$field]"}" value="{$value}" size="40"/>
    {/if}
    </td></tr>
  {/foreach}
  </table>
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}" class="button"/>
  <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}" class="button"/>
</div>
