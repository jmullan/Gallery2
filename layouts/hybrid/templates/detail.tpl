<head>
<title>{$layout.title|markup}</title>
{g->style}
<script type="text/javascript">
{literal}
function parent_check() {
 if (window == window.top)
  document.location.replace(document.getElementById('up').href);
}
{/literal}
</script>
</head>
<body onload="parent_check()">
  {g->link id="up"
   arg1="view=core:ShowItem" arg2="itemId=`$layout.item.parentId`"}{/g->link}
  {if !empty($layout.moduleItemDetailFiles)}
    {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
      {include file=$detailFile l10Domain="modules_$moduleId"}
    {/foreach}
  {/if}
</body>
