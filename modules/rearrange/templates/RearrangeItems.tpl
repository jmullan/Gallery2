{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
{*
 * Precalculate the HTML that will go inside every cell in the
 * table so that we can render it twice (once in the Javascript,
 * once in the HTML itself.  We do this to avoid using the innerHTML
 * element when we swap the cells because the behavior of innerHTML
 * varies from platform to platform and on Firefox it turns ~ into %7E
 * which breaks our cookie paths.
 *}
<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="Rearrange Album"}
      </h2>
    </div>
  </div>

  {if isset($RearrangeItems.automaticOrderMessage)}
  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="This album has an automatic sort order specified, so you cannot change the order of items manually.  You must remove the automatic sort order to continue."}
      <a href="{g->url arg1="view=core:ItemAdmin" arg2="subView=core:ItemEdit" arg3="editPlugin=ItemEditAlbum" arg4="itemId=`$ItemAdmin.item.id`"}">{g->text text="[change]"}</a>
    </p>
  </div>
  {else}
<script type="text/javascript">
var sel = -1, list = new Array();
var html = new Array();
{foreach from=$RearrangeItems.children key=idx item=child}
  {capture name="html"}
  {include file="gallery:modules/rearrange/templates/RearrangeItemsCell.tpl" child=$child}
  {/capture}
  html[{$idx}] = '{$smarty.capture.html|escape:javascript}';
{/foreach}
for (var i = 0; i < {$RearrangeItems.count}; i++) {literal} {
  list[i] = i;
}
function save() {
  var s = '';
  for (var i = 0; i < list.length; i++) {
    if (i > 0) s += ',';
    s += list[i];
  }
  document.getElementById('riList').value = s;
}
function doclick(idx) {
  if (sel < 0) {
    sel = idx;
    document.getElementById('item_'+sel).getElementsByTagName('*')[0].style.borderColor = '#ff3333';
    document.getElementById('item_'+sel).parentNode.style.backgroundColor = '#ff3333';
  } else {
    var a = document.getElementById('item_'+sel);
    a.getElementsByTagName('*')[0].style.borderColor = 'black';
    a.parentNode.style.backgroundColor = 'white';
    if (idx != sel) {
      var dir = (sel < idx) ? 1 : -1, tt, ti, i, b;
      ti = list[sel];
      tt = html[sel];
      for (i = sel; i != idx; a = b, i += dir) {
        b = document.getElementById('item_' + (i+dir));
        a.innerHTML = html[i] = html[i+dir];
        list[i] = list[i+dir];
      }
      a.innerHTML = html[i] = tt;
      list[idx] = ti;
    }
    sel = -1;
  }
}
{/literal}</script>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Order saved successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Change the order of the items in this album."}
    </p>

    {if $RearrangeItems.columns > 0}
    <table class="gbDataEntry">
    {else}
    <div class="gbDataEntry">
    {/if}

    {assign var="row" value=0}
    {assign var="column" value=0}
    {foreach from=$RearrangeItems.children key=idx item=child}
      {if $RearrangeItems.columns > 0}
	{if $column == 0} <tr> {/if}
	<td>
      {else}
	<div class="riFloat"
	     style="width:{$RearrangeItems.maxWidth}px;height:{$RearrangeItems.maxHeight}px">
      {/if}

      {strip}
      {if isset($child.thumbnail)}
	<a href="#" id="item_{$idx}" onclick="doclick({$idx});return false">
          {include file="gallery:modules/rearrange/templates/RearrangeItemsCell.tpl"
                   child=$child l10Domain="modules_rearrange"}
	</a>
      {else}
	<a id="item_{$idx}" onclick="doclick({$idx});return false">
          {include file="gallery:modules/rearrange/templates/RearrangeItemsCell.tpl"
                   child=$child l10Domain="modules_rearrange"}
	</a>
      {/if}
      {/strip}

      {if $RearrangeItems.columns > 0}
	</td>
	{assign var="column" value=$column+1}
	{if $column == $RearrangeItems.columns}
	  </tr>
	  {assign var="column" value=0}
	  {assign var="row" value=$row+1}
	  {if $row == $RearrangeItems.rows}
	    <tr><td colspan="{$RearrangeItems.columns}"><hr/></td></tr>
	    {assign var="row" value=0}
	  {/if}
	{/if}
      {else}
	</div>
      {/if}
    {/foreach}

    {if $RearrangeItems.columns > 0}
    </table>
    {else}
    </div>
    {/if}
  </div>

  <div class="gbButtons">
    <input type="hidden" id="riList" name="{g->formVar var="form[list]"}" value=""/>
    <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"
           onclick="save()"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
  </div>
  {/if}
</div>
