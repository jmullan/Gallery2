<head>
<title>{$layout.title|markup}</title>
{g->style}
</head>
<body>
  {if !empty($layout.moduleItemDetailFiles)}
    {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
      {include file=$detailFile l10Domain="modules_$moduleId"}
    {/foreach}
  {/if}
</body>
