{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<script type="text/javascript">{literal}
// <![CDATA[
function move(toRight) {
  var from = document.getElementById(toRight ? 'available' : 'selected'),
        to = document.getElementById(toRight ? 'selected' : 'available'), i;
  for (i = 0; i < from.length; i++) {
    if (from.options[i].selected) {
      to.options[to.length] = new Option(from.options[i].text, from.options[i].value);
      from.options[i--] = null;
    }
  }
}
function selectAll() {
  var s = document.getElementById('selected'), i;
  for (i = 0; i < s.length; i++) {
    s.options[i].selected = true;
  }
}
// ]]>
{/literal}</script>

<div id="gsAdminContents">
  <div class="gbTopFlag">
    <div class="gbTitle">
      <h2 class="giTitle">
	{g->text text="MultiLanguage Settings"}
      </h2>
    </div>
  </div>

  {if !empty($status)}
  <div id="gsStatus">
    {if isset($status.saved)}
    <div class="giStatus">
      {g->text text="Settings saved successfully"}
    </div>
    {/if}
  </div>
  {/if}

  <div class="gbAdmin">
    <p class="giDescription">
      {g->text text="Maintain primary language captions using the normal Gallery interface.  Here select the additional languages to support in the MultiLanguage tab."}
    </p>

    <table class="gbDataTable">
      <tr>
	<th>
	  {g->text text="Available"}
	</th>
	<th></th>
	<th>
	  {g->text text="Selected"}
	</th>
      </tr>
      <tr>
	<td>
	  <select id="available" size="20" multiple="multiple">
	    {html_options options=$MultiLangSiteAdmin.availableList}
	  </select>
	</td>
	<td>
	  <p> <input type="button" value="&gt;&gt;" onclick="move(1);return false"/> </p>
	  <p> <input type="button" value="&lt;&lt;" onclick="move();return false"/> </p>
	</td>
	<td>
	  <select id="selected" name="{g->formVar var="form[languages][]"}"
	   size="20" multiple="multiple">
	      {html_options options=$MultiLangSiteAdmin.selectedList}
	  </select>
	</td>
      </tr>
    </table>
  </div>

  <div class="gbButtons">
    <input type="submit" name="{g->formVar var="form[action][save]"}"
     value="{g->text text="Save"}" onclick="selectAll()"/>
    <input type="submit" name="{g->formVar var="form[action][reset]"}"
     value="{g->text text="Reset"}"/>
  </div>
</div>
