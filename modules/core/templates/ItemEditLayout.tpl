{g->pagebox}
  {g->banner}
    {g->title}
      {g->text text="Edit Layout Settings"}
    {/g->title}
  {/g->banner}

  {if isset($status)}
    {g->success}
      {if isset($status.saved)}
	{g->text text="Successfully saved layout settings"}
      {/if}
      {if isset($status.restored)}
	{g->text text="Restored layout settings"}
      {/if}
    {/g->success}
  {/if}

  {g->box style="admin"}
    {g->title}
      {g->text text="Layout Settings" arg1=$ItemEditLayout.layout.name}
    {/g->title}

    {g->description}
      {g->text text="This album is configured to use the <b>%s</b> layout. These settings only apply to the layout for this item." arg1=$ItemEditLayout.layout.name}
    {/g->description}

    {if !empty($ItemEditLayout.settings)}
      {g->table style="admin_widgets"}
	{foreach from=$ItemEditLayout.settings item=setting}
	  {assign var="settingKey" value=$setting.key}
	  {g->row}
	    {g->column}
	      {g->text text=$setting.name l10Domain=$ItemEditLayout.layout.l10Domain}
	    {/g->column}
	    {g->column}
	      {if ($setting.type == 'text-field')}
		{g->input type="text" size="6" name="form_key_$settingKey"}{$form.key.$settingKey}{/g->input}
	      {/if}
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
      {g->input type="submit" name="form.action.save"}{g->text text="Save"}{/g->input}
      {g->input type="submit" name="form.action.undo"}{g->text text="Undo"}{/g->input}
    {/g->element}
  {/g->box}
{/g->pagebox}
