{foreach from=$tags key=tagName item=tagInfo}
{if empty($builtin_tag.$tagName) && empty($attribute_tag.$tagName)}
    /**
     * {$tagName} theme method
     * 
     * @param array ("params" => ..., "stack" => ...)
{if isset($decorator_tag.$tagName)}
     * @param string content HTML content
{else}
{foreach from=$tagInfo.children key=childName item=childInfo}
{if ($childName == 'content')}
     * @param string HTML content 
{else}
     * @param array ("params" => array, "content" => {$childName} HTML content)
{/if}
{/foreach}
{/if}
     * @return string HTML content
     */
{if isset($contracted_tag.$tagName)}
     function {$tagName}($context) {ldelim}
{else}
{if isset($decorator_tag.$tagName)}
     function {$tagName}($context, $content) {ldelim}
{else}
     function {$tagName}($context{foreach from=$tagInfo.children key=childName item=childInfo}, ${$childName}{if $childInfo.isArray}_array{/if}{/foreach}) {ldelim}
{/if}
{/if}
         trigger_error('Undefined theme function: {$tagName}', E_USER_ERROR);
     {rdelim}

{/if}
{/foreach}
