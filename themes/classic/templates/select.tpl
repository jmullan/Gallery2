{* 
 * select.tpl - Select widget (eg, HTML form widget)
 *
 *  $params.name (string)
 *    The widget name
 *
 *  $params.size (int)
 *    How many options to show at once
 * 
 *  $params.onChange (string)
 *    Javascript action to take when a new option is selected
 * 
 *  $content (string)
 *    A series of <option> tags
 * 
 *}
<select 
{if !empty($params.name)}
      name="{$params.name}" 
{/if}
{if !empty($params.onChange)}
      onChange="{$params.onChange}" 
{/if}
  {if isset($params.size)}
      size="{$params.size}"
  {/if}
  >
{$content}
</select>
