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
 *  $params.value (string)
 *    The initial value of the widget
 * 
 *}
{if ($params.type == 'checkbox' || $params.type == 'radio')}
{if empty($params.value)}
<input type="{$params.type}" name="{$params.name}">
{else}
<input type="{$params.type}" name="{$params.name}" CHECKED>
{/if}
{else}
<input type="{$params.type}" name="{$params.name}" value="{$params.value}">
{/if}
