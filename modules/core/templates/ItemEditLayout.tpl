{g->box style="admin"}
  {g->description}
    {g->text text="This album is configured to use the <b>%s</b> layout. These settings only apply to the layout for this album." arg1=$ItemEditLayout.layout.name}
  {/g->description}

  {if !empty($ItemEditLayout.settings)}
    {g->table style="admin_widgets"}
      {g->row}
	{g->column header="true"}
	  {g->text text="Setting"}
	{/g->column}
	{g->column header="true"}
	  {g->text text="Value"}
	{/g->column}
	{g->column colspan="2" header="true"}
	  {g->text text="Use Global"}
	{/g->column}
      {/g->row}

      {foreach from=$ItemEditLayout.settings item=setting}
	{assign var="settingKey" value=$setting.key}
	{g->row}
	  {g->column}
	    {g->text text=$setting.name l10Domain=$ItemEditLayout.layout.l10Domain}
	  {/g->column}
	  {g->column}
	    {if ($setting.type == 'text-field')}
	      {g->input type="text" size="6" name="form[key][$settingKey]" onKeyPress="javascript:changeSetting('$settingKey')"}{$form.key.$settingKey}{/g->input}
	    {/if}
	  {/g->column}
	  {g->column}
	    &nbsp;
	  {/g->column}
	  {g->column}
	    {g->input type="checkbox" name="form[useGlobal][$settingKey]" onClick="javascript:toggleGlobal('$settingKey')"}{$form.useGlobal.$settingKey}{/g->input}
	  {/g->column}
	{/g->row}
	{if isset($form.error.key.$settingKey.invalid)}
	  {g->row}
	    {g->column colspan="2"}
	      {g->error}
		{$form.errorMessage.$settingKey}
	      {/g->error}
	    {/g->column}
	  {/g->row}
	{/if}
      {/foreach}
    {/g->table}
  {else}
    {g->element style="emphasized"}
      {g->text text="There are no settings for this layout"}
    {/g->element}
  {/if}
{/g->box}

{g->box style="admin"}
  {g->element}
    <script type="text/javascript" language="javascript">
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

    {g->input type="submit" name="form[action][save]"}{g->text text="Save"}{/g->input}
    {g->input type="submit" name="form[action][undo]"}{g->text text="Undo"}{/g->input}
  {/g->element}
{/g->box}
