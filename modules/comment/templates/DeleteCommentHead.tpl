{if empty($item.title)}
{assign var="title" value=$item.pathComponent}
{else}
{assign var="title" value=$item.title}
{/if}

<title>
{gallery->text text="Delete a comments for %s" arg1=$title}
</title>
{gallery->style}

