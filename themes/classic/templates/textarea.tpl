{* 
 * textarea.tpl - Multiple line text input widget 
 * 
 * Input variables:
 *
 *  $params.name (string)
 *    The widget name
 *
 *  $params.rows (int)
 *    The height in rows of the text area
 *
 *  $params.cols
 *    The width in columns of the text area
 * 
 *}
<textarea name="{$params.name}"
{if !empty($params.rows)}
      rows="{$params.rows}"
{/if}
{if !empty($params.cols)}
      cols="{$params.cols}"
{/if}
>{$content}</textarea>
