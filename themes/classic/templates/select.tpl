{* 
 * select.tpl - Select widget (eg, HTML form widget)
 *
 *  $params.name (string)
 *    The widget name
 *
 *  $params.size (int)
 *    How many options to show at once
 * 
 *  $content (string)
 *    A series of <option> tags
 * 
 *}
<select name="{$params.name}" 
  {if isset($params.size)}
      size="{$params.size}"
  {/if}
  >
{$content}
</select>
