{* 
 * input.tpl - Input widget (eg, HTML form widget)
 * 
 * Input variables:
 *
 *  $params.type (string)
 *    One of text, password, hidden, checkbox, radio, submit or file
 *
 *  $params.name (string)
 *    The widget name
 * 
 *  $params.size (string)
 *    The size of the widget (applies to text and password types)
 * 
 *  $params.onChange (string)
 *    Javascript action to take when a new option is selected
 * 
 *  $params.value (string)
 *    The initial value of the widget
 *}
<input type="{$params.type}" 
{if (!empty($params.name))}
       name="{$params.name}"
{/if}
{if !empty($params.onChange)}
       onChange="{$params.onChange}" 
{/if}
{if !empty($params.size)}
       size="{$params.size}"
{/if}

{if ! empty($params.value)}
  {if ($params.type == 'checkbox' || $params.type == 'radio')}
       CHECKED
  {else}
       value="{$params.value}"
  {/if}
{/if}
>
