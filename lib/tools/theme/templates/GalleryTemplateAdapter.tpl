    /**
     * This is a list of Smarty callback methods that contain content
     * data (eg, {ldelim}tag{rdelim} .. content .. {ldelim}/tag{rdelim}).
     *
     * (NOTE: This method is generated by TemplateTags.php -- do not edit!)
     */
    function getBlockMethods() {ldelim}
        static $_blockMethods = array(
{foreach from=$tags key=tagName item=tagInfo}
{if !isset($contracted_tag.$tagName)}
            '{$tagName}',
{/if}
{/foreach}
        );
        return $_blockMethods;
    {rdelim}

{foreach from=$tags key=tagName item=tagInfo}
    /**
     * Call the {$tagName} theme API method
     *
     * (NOTE: This method is generated by TemplateTags.php -- do not edit!)
     */
{if (isset($contracted_tag.$tagName))}
    function {$tagName}($params, &$smarty) {ldelim}
        $context = $this->_getContext($params, $smarty);
        return $this->_theme->{$tagName}($context);
    {rdelim}
{else}
    function {$tagName}($params, $content, &$smarty) {ldelim}
        if (!isset($content)) {ldelim}
{if !empty($tagInfo.children)}
            /* Allocate space for named children */
            $self = array();
            $self['_name'] = '{$tagName}';
{foreach from=$tagInfo.children key=childName item=childInfo}
            $self['{$childName}'] = array();
{if ($childInfo.isArray)}
            $self['_arrays']['{$childName}'] = 1;
{/if}
{/foreach}
            $this->stackPush($self);
{/if}
            return;
        {rdelim}
{if (empty($tagInfo.children.content))}

      	$content = trim($content);
	if (!empty($content)) {ldelim}
	    $smarty->trigger_error(sprintf('Unexpected content detected in \'{$tagName}\' tag: <pre>%s</pre>', $content));
	{rdelim}
{/if}
{if !empty($tagInfo.attributes)}

        /* Verify all attributes */
{foreach from=$tagInfo.attributes key=attributeName item=attributeDefaultValue}
        if (!isset($params['{$attributeName}'])) {ldelim}
            $params['{$attributeName}'] = {$attributeDefaultValue};
        {rdelim}
{/foreach}
{/if}

        $context = $this->_getContext($params, $smarty);
	$self = $this->stackPop();
{foreach from=$tagInfo.children key=childName item=childInfo}
{if ($childName != 'content')}
{if !$childInfo.isArray}
        /* Collapse {$childName} to a single value */
        if (sizeof($self['{$childName}']) > 1) {ldelim}
            $smarty->trigger_error(sprintf('Illegal multiple {$childName} tags inside tag {$tagName} ' .
                                           '(1 expected, %d found)', sizeof($self['{$childName}'])));
            return;
        {rdelim}
        if (sizeof($self['{$childName}']) > 0) {ldelim}
            $self['{$childName}'] = $self['{$childName}'][0];
	{rdelim}
{/if}
{else}
        $self['content'] = $content;
{/if}

{/foreach}
{if empty($attribute_tag.$tagName)}
        $content = $this->_theme->{$tagName}($context{foreach from=$tagInfo.children key=childName item=childInfo}, $self['{$childName}']{/foreach});
{/if}

{if isset($trimmed_tag.$tagName)}
        $content = trim($self['content']);
{/if}

        $tagData = array('name' => '{$tagName}', 'params' => $params, 'content' => $content);
        if ($this->stackEmpty()) {ldelim}
            return $content;
        {rdelim} else {ldelim}
            $parent =& $this->stackPeek();
            if (isset($parent['{$tagName}'])) {ldelim}
                array_push($parent['{$tagName}'], $tagData);
{if !isset($attribute_tag.$tagName)}
            {rdelim} else if (isset($parent['element'])) {ldelim}
                /* Verify all element attributes */
{foreach from=$tags.element.attributes key=attributeName item=attributeDefaultValue}
		if (!isset($tagData['params']['{$attributeName}'])) {ldelim}
		    $tagData['params']['{$attributeName}'] = {$attributeDefaultValue};
		{rdelim}
{/foreach}
                array_push($parent['element'], $tagData);
            {rdelim} else if (isset($parent['content'])) {ldelim}
	        /* Content is passed back inline */
	        return $content;
{/if}
            {rdelim} else {ldelim}
               $smarty->trigger_error(sprintf('Illegal use of tag %s inside tag %s', '{$tagName}', $parent['_name']));
               return;
            {rdelim}
        {rdelim}
    {rdelim}
{/if}

{/foreach}
