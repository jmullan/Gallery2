<head>
<title>{$layout.title|markup}</title>
{g->style}
</head>
<body>
  <table cellspacing="0"><tr>
  {if isset($layout.thumb)}
    <td>{g->image item=$layout.item image=$layout.thumb}</td>
  {/if}
  <td valign="top"><br>
    {$layout.item.title|default:$layout.item.pathComponent}<br>
    {g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}<br>
    {g->text one="Viewed: %s time" many="Viewed: %s times"
             count=$layout.viewCount arg1=$layout.viewCount}<br>
    {g->text text="Date: "}{g->date timestamp=$layout.item.creationTimestamp}
  </td></tr></table>
  {if !empty($layout.moduleItemDetailFiles)}
    {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
      {include file=$detailFile l10Domain="modules_$moduleId"}
    {/foreach}
  {/if}
</body>
