{if empty($item.title)}
{assign var="title" value=$item.pathComponent}
{else}
{assign var="title" value=$item.title}
{/if}

<title>
{galleryText text="Edit a comments for %s" arg1=$title}
</title>
{galleryStyle}

