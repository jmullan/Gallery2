{*
 * If you want to customize this file, do not edit it directly.
 * Instead, copy it to detail.tpl.local and edit that version instead.
 * Gallery will look for that file first and use it if it exists
 * and when you upgrade, your changes will not get overwritten.
 *}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html><head>
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
    {g->text one="Viewed: %d time" many="Viewed: %d times"
             count=$layout.viewCount arg1=$layout.viewCount}<br>
    {g->text text="Date: "}{g->date timestamp=$layout.item.creationTimestamp}<br>
    {if isset($layout.item.keywords)}
      {g->text text="Keywords: "}{$layout.item.keywords|markup}<br>
    {/if}
  </td></tr></table>
  {if !empty($layout.moduleItemDetailFiles)}
    {foreach from=$layout.moduleItemDetailFiles key=moduleId item=detailFile}
      {include file="gallery:$detailFile" l10Domain="modules_$moduleId"}
    {/foreach}
  {/if}
</body></html>
