{if empty($item.title)}
{assign var="title" value=$item.pathComponent}
{else}
{assign var="title" value=$item.title}
{/if}

<title>
{galleryText text="Delete a comments for %s" arg1=$title}
</title>
{galleryStyle}

