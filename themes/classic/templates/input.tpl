{*
 * Form input widget.  
 *
 * Variables:
 *   $params.type is one of:
 *       text, password, hidden, checkbox, radio, submit or file
 *
 *   $params.name:  the form widget name
 *   $params.value: the form widget value
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
