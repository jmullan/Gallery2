{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<div class="gbBlock">
  <p class="giDescription">
    {g->text text="This album is configured to use the <b>%s</b> layout. These settings only apply to the layout for this album." arg1=$ItemEditLayout.layout.name}
  </p>

{if isset($ItemEditLayout.customTemplate)}

  {include file="gallery:`$ItemEditLayout.customTemplate`"
	   l10Domain=$ItemEditLayout.layout.l10Domain}

{else}
  {if !empty($ItemEditLayout.settings)}
  <table class="gbDataTable"><tr>
    <th> {g->text text="Setting"} </th>
    <th> {g->text text="Value"} </th>
    <th> {g->text text="Use Global"} </th>
  </tr>

  {foreach from=$ItemEditLayout.settings item=setting}
    {assign var="settingKey" value=$setting.key}
    <tr class="{cycle values="gbEven,gbOdd"}">
      <td>
	{g->text text=$setting.name l10Domain=$ItemEditLayout.layout.l10Domain}
      </td><td>
	{if ($setting.type == 'text-field')}
	  <input type="text" size="6" onkeypress="javascript:changeSetting('{$settingKey}')"
	   name="{g->formVar var="form[key][$settingKey]"}" value="{$form.key.$settingKey}"/>
	{elseif ($setting.type == 'single-select')}
	  <select name="{g->formVar var="form[key][$settingKey]"}"
	   onchange="javascript:changeSetting('{$settingKey}')">
	    {html_options options=$setting.choices selected=$setting.value}
	  </select>
	{elseif ($setting.type == 'checkbox')}
	  <input type="checkbox" onchange="javascript:changeSetting('{$settingKey}')"
	   name="{g->formVar var="form[key][$settingKey]"}"
	   {if !empty($setting.value)}checked="checked"{/if}/>
	{/if}
      </td>

      <td align="center">
	<input type="checkbox" onclick="javascript:toggleGlobal('{$settingKey}')"
	 name="{g->formVar var="form[useGlobal][$settingKey]"}"
	 {if (!isset($ItemEditLayout.globalParams.$settingKey))}
	   disabled="disabled"
	 {elseif ($setting.value == $ItemEditLayout.globalParams.$settingKey)}
	   checked="checked"
	 {/if}/>
      </td>
    </tr>

    {if isset($form.error.key.$settingKey.invalid)}
    <tr>
      <td colspan="2" class="giError">
	{$form.errorMessage.$settingKey}
      </td>
    </tr>
    {/if}
  {/foreach}
  </table>
  {else}
    <b> {g->text text="There are no settings for this layout"} </b>
  {/if}
</div>

<script type="text/javascript">
  // <![CDATA[
  var isSaved = new Array;
  var savedValues = new Array;
  var globalValues = new Array;
  {foreach from=$ItemEditLayout.globalParams key=key item=value}
    globalValues['{$key}'] = '{$value}';
  {/foreach}

  function toggleGlobal(key) {ldelim}
    inputWidget = '{g->formVar var="form[key]["}' + key + ']';
    toggleWidget = '{g->formVar var="form[useGlobal]["}' + key + ']';
    {literal}
    if (document.forms[0].elements[toggleWidget].checked) {
      savedValues[key] = document.forms[0].elements[inputWidget].value;
      isSaved[key] = true;
      if (document.forms[0].elements[inputWidget].type == 'checkbox') {
        if (globalValues[key] != 0) {
          document.forms[0].elements[inputWidget].checked = 'checked';
        } else {
	  document.forms[0].elements[inputWidget].checked = null;
        }
      } else {
        document.forms[0].elements[inputWidget].value = globalValues[key];
      }
    } else {
      if (document.forms[0].elements[inputWidget].type == 'checkbox') {
        if (globalValues[key] == 0) {
          document.forms[0].elements[inputWidget].checked = 'checked';
        } else {
	  document.forms[0].elements[inputWidget].checked = null;
        }
      } else if (isSaved[key]) {
        document.forms[0].elements[inputWidget].value = savedValues[key];
      }
    }
  }

  function changeSetting(key) {
    {/literal}
    toggleWidget = '{g->formVar var="form[useGlobal]["}' + key + ']';
    document.forms[0].elements[toggleWidget].checked = false;
  {rdelim}
  // ]]>
</script>
{/if}

<div class="gbBlock gcBackground1">
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" class="inputTypeSubmit"
   name="{g->formVar var="form[action][undo]"}" value="{g->text text="Reset"}"/>
</div>
