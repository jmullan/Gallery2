<div class="gbAdmin">
  <div class="giDescription">
    {g->text text="This album is configured to use the <b>%s</b> layout. These settings only apply to the layout for this album." arg1=$ItemEditLayout.layout.name}
  </div>
  
  {if !empty($ItemEditLayout.settings)}
  <table class="gbDataTable">
    <tr>
      <th>
	{g->text text="Setting"}
      </th>
      <th>
	{g->text text="Value"}
      </th>
      <th colspan="2">
	{g->text text="Use Global"}
      </th>
    </tr>

    {foreach from=$ItemEditLayout.settings item=setting}
    {assign var="settingKey" value=$setting.key}
    <tr class="{cycle values="gbEven,gbOdd"}">
      <td>
	{g->text text=$setting.name l10Domain=$ItemEditLayout.layout.l10Domain}
      </td>
      <td>
	{if ($setting.type == 'text-field')}
	<input type="text" size="6" name="{g->formVar var="form[key][$settingKey]"}" onkeypress="javascript:changeSetting('$settingKey')" value="{$form.key.$settingKey}"/>
	{elseif ($setting.type == 'single-select')}
	<select name="{g->formVar var="form[key][$settingKey]"}" onChange="javascript:changeSetting('$settingKey')">
	    {html_options options=$setting.choices selected=$setting.value}
	</select>
	{/if}
      </td>

      <td>
	&nbsp;
      </td>

      <td>
	<input type="checkbox" name="{g->formVar var="form[useGlobal][$settingKey]"}" onclick="javascript:toggleGlobal('$settingKey')" value="{$form.useGlobal.$settingKey}"/>
      </td>
    </tr>

    {if isset($form.error.key.$settingKey.invalid)}
    <tr>
      <td colspan="2">
	<div class="giError">
	  {$form.errorMessage.$settingKey}
	</div>
      </td>
    </tr>
    {/if}
    {/foreach}
  </table>
  {else}
  <b>
    {g->text text="There are no settings for this layout"}
  </b>
  {/if}
</div>

<div class="gbAdmin">
  <script type="text/javascript">
    var isSaved = new Array;
    var savedValues = new Array;
    var globalValues = new Array;
    {foreach from=$ItemEditLayout.globalParams key=key item=value}
      globalValues['{$key}'] = '{$value}';
    {/foreach}

    function toggleGlobal(key) {ldelim}
      inputWidget = '{g->elementName name="form[key]["}' + key + ']';
      toggleWidget = '{g->elementName name="form[useGlobal]["}' + key + ']';
      if (document.forms[0].elements[toggleWidget].checked) {ldelim}
        savedValues[key] = document.forms[0].elements[inputWidget].value;
        isSaved[key] = true;
        document.forms[0].elements[inputWidget].value = globalValues[key];
      {rdelim} else {ldelim}
        if (isSaved[key]) {ldelim}
          document.forms[0].elements[inputWidget].value = savedValues[key];
        {rdelim}
      {rdelim}
    {rdelim}

    function changeSetting(key) {ldelim}
      toggleWidget = '{g->elementName name="form[useGlobal]["}' + key + ']';
      document.forms[0].elements[toggleWidget].checked = false;
    {rdelim}
  </script>

  <input type="submit" name="{g->formVar var="form[action][save]"}" value="{g->text text="Save"}"/>
  <input type="submit" name="{g->formVar var="form[action][undo]"}" value="{g->text text="Undo"}"/>
</div>
