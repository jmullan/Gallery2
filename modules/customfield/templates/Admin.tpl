{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<script type="text/javascript">{literal}
// <![CDATA[
function swap(set,j,k) {
 var tf,ts,td,ti;
 tf = document.getElementById(set+k).innerHTML;
 ts = document.getElementById('s.'+set+k).checked;
 td = document.getElementById('d.'+set+k).checked;
 ti = document.getElementById('i.'+set+k).value;
 document.getElementById(set+k).innerHTML = document.getElementById(set+j).innerHTML;
 document.getElementById('s.'+set+k).checked = document.getElementById('s.'+set+j).checked;
 document.getElementById('d.'+set+k).checked = document.getElementById('d.'+set+j).checked;
 document.getElementById('i.'+set+k).value = document.getElementById('i.'+set+j).value;
 document.getElementById(set+j).innerHTML = tf;
 document.getElementById('s.'+set+j).checked = ts;
 document.getElementById('d.'+set+j).checked = td;
 document.getElementById('i.'+set+j).value = ti;
}
function up(set,j) { swap(set,j,j-1); }
function down(set,j) { swap(set,j,j+1); }
function warn(btn) {
 var i = btn.form.elements[ btn.name.substring(0, btn.name.indexOf('[')) +
                            btn.name.substring(btn.name.lastIndexOf('[')) + '[goAction]' ].value;
{/literal}
 if (i=='remove') return confirm(removeWarning);
 else if (i=='album') return confirm(albumWarning);
 else if (i=='photo') return confirm(photoWarning);
{literal}
}
var pickdata = new Array();
{/literal}
{counter start=-1 print=no}
{foreach from=$form.set item=set}{foreach from=$form.fields[$set.key] item=item}
pickdata[{counter}] = '{foreach from=$item.choices item=choice}{$choice}\n{/foreach}';
{assign var="nonempty" value="1"}
{/foreach}{/foreach}
{literal}
function pickfield(s) {
 document.getElementById('pick').value = pickdata[s.selectedIndex];
}
// ]]>
{/literal}</script>

{if !empty($status)}
<div id="gsStatus">
  {if isset($status.saved)}
  <div class="giStatus">
    {g->text text="Display settings saved successfully"}
  </div>
  {/if}
  {if isset($status.added)}
  <div class="giStatus">
    {g->text text="New field added successfully"}
  </div>
  {/if}
  {if isset($status.moved)}
  <div class="giStatus">
    {g->text text="Field moved successfully"}
  </div>
  {/if}
  {if isset($status.removed)}
  <div class="giStatus">
    {g->text text="Field removed successfully"}
  </div>
  {/if}
  {if isset($status.picklist)}
  <div class="giStatus">
    {g->text text="Picklist updated successfully"}
  </div>
  {/if}
  {if isset($status.error.duplicate)}
  <div class="giError">
    {g->text text="Field name already in use"}
  </div>
  {/if}
</div>
{/if}

<div class="gbAdmin">
  <h3> {g->text text="Display"} </h3>
  <p class="giDescription">
    {g->text text="Set the display order and visibility of the fields below. Summary fields are typically displayed with thumbnails in an album view. Detail fields are usually shown when viewing the specific item."}
  </p>

  <table class="gbDataTable">
    <tr>
      {foreach from=$form.set item=set}
	<th> {$set.name} </th>
      {/foreach}
    </tr>
    <tr style="vertical-align:top">

    {foreach from=$form.set item=set}
    {cycle delimiter="|" values="gbEven,gbOdd|gbOdd,gbEven" assign="rowclass"}
    <td>
    <table class="gbDataTable">
      <tr>
	<th> {g->text text="Field"} </th>
	<th> {g->text text="Summary"} </th>
	<th> {g->text text="Detail"} </th>
	<th colspan="2"> {g->text text="Order"} </th>
      </tr>
      {foreach from=$form.fields[$set.key] key=idx item=item}
      <tr class="{cycle name=$set.key values=$rowclass}">
	<td style="white-space:nowrap">
	  <span id="{$set.key}{$idx}">{$item.field}</span>
	  <input id="i.{$set.key}{$idx}" type="hidden" name="{g->formVar var="form[`$set.key`][index][$idx]"}" value="{$idx}"/>
	</td><td style="text-align:center">
	   <input id="s.{$set.key}{$idx}" type="checkbox" name="{g->formVar var="form[`$set.key`][summary][$idx]"}"
		  {if $item.summary}checked="checked"{/if}/>
	</td><td style="text-align:center">
	   <input id="d.{$set.key}{$idx}" type="checkbox" name="{g->formVar var="form[`$set.key`][detail][$idx]"}"
		  {if $item.detail}checked="checked"{/if}/>
	</td><td>
	  {if $idx > 0}
	  <a href="" onclick="up('{$set.key}',{$idx});this.blur();return false" style="padding:0 2px">
	    {g->text text="up"}
	  </a>
	  {/if}
	</td><td>
	  {if ($idx < count($form.fields[$set.key])-1)}
	  <a href="" onclick="down('{$set.key}',{$idx});this.blur();return false" style="padding:0 2px">
	    {g->text text="down"}
	  </a>
	  {/if}
	</td>
      </tr>
      {/foreach}
    </table>
    </td>
    {/foreach}
    </tr>
  </table>
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>

<div class="gbAdmin">
  <h3> {g->text text="Add/Remove"} </h3>
  <p class="giDescription">
    {g->text text="Save any changes above before using the controls below."}
  </p>

  <table class="gbDataTable">
    <tr>
      {foreach from=$form.set item=set}
	<th> {$set.name} </th>
      {/foreach}
    </tr>
    <tr style="vertical-align:top">

    {foreach from=$form.set item=set}
    <td>
      <p>
	<input type="text" name="{g->formVar var="form[`$set.key`][newField]"}" size="20"/>
	<input type="submit" name="{g->formVar var="form[action][add][`$set.key`]"}" value="{g->text text="Add"}"/>
      </p>
      <table style="border-spacing:1px; border-top:1px dashed #ddd"><tr>
	<th> {g->text text="Field:"} </th>
	<th>
	  {if !empty($form.fields[$set.key])}
	  <select name="{g->formVar var="form[`$set.key`][goField]"}">
	  {foreach from=$form.fields[$set.key] item=item}<option>{$item.field}</option>{/foreach}
	  </select>
          {/if}
	</th>
      </tr><tr>
	<th> {g->text text="Action:"} </th>
	<th>
	  <select name="{g->formVar var="form[`$set.key`][goAction]"}">
	  <option value="remove">{g->text text="Remove"}</option>
	  {if $set.key=='common'}
	    <option value="album">{g->text text="Move to Album"}</option>
	    <option value="photo">{g->text text="Move to Photo"}</option>
	  {else}
	    <option value="common">{g->text text="Move to Common"}</option>
	  {/if}
	  </select>
	  {if !empty($form.fields[$set.key])}
	    <input type="submit" name="{g->formVar var="form[action][go][`$set.key`]"}"
		   value="{g->text text="Go"}" onclick="return warn(this)"/>
	  {/if}
	</th>
      </tr></table>
    </td>
    {/foreach}
    </tr>
  </table>
</div>

<div class="gbAdmin">
  <h3> {g->text text="Picklist Values"} </h3>
  <p class="giDescription">
    {g->text text="Custom fields allow freeform text entry by default. Enter values below to restrict field values to a specific list of choices. Enter one choice per line. Remove all choices to return to freeform text. Note that existing field values will not be changed or deleted when a picklist is added."}
  </p>

  {if isset($nonempty)}
  <table class="gbDataTable"><tr>
    <td> {g->text text="Field:"} </td>
    <td> <select name="{g->formVar var="form[pickField]"}" id="picksel"
		 onchange="pickfield(this);this.blur()">
      {foreach from=$form.set item=set}
	{foreach from=$form.fields[$set.key] item=item}<option>{$item.field}</option>{/foreach}
      {/foreach}
      </select>
    </td>
  </tr><tr>
    <td> {g->text text="Choices:"} </td>
    <td>
      <textarea id="pick" name="{g->formVar var="form[picklist]"}" cols="40" rows="4"></textarea>
    </td>
  </tr></table>
  <script type="text/javascript">
    // <![CDATA[
    if (pickdata.length>0) pickfield(document.getElementById('picksel'));
    // ]]>
  </script>
  {else}
    <p class="giInfo"> {g->text text="Add a custom field above to enable this section."} </p>
  {/if}
</div>

<div class="gbButtons">
  <input type="submit" name="{g->formVar var="form[action][picklist]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][reset]"}" value="{g->text text="Reset"}"/>
</div>
