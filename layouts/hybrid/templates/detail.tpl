{*
 * $Revision$
 * If you want to customize this file, do not edit it directly since future upgrades
 * may overwrite it.  Instead, copy it into a new directory called "local" and edit that
 * version.  Gallery will look for that file first and use it if it exists.
 *}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html><head>
<title>
  {$layout.item.title|default:$layout.item.pathComponent|markup:stripBbcodeAndHtml}
</title>
{g->head}
</head>
<body class="gallery">
<div id="gallery" style="padding: 0.7em">
  <table cellspacing="0"><tr>
  {if isset($layout.thumbnail)}
    <td>{g->image item=$layout.item image=$layout.thumbnail class="giThumbnail"}</td>
  {/if}
  <td valign="top" class="giDescription" style="padding: 0.7em 0 0 0.7em">
    <strong>{$layout.item.title|markup}</strong><br/>
    {g->text text="Owner: %s" arg1=$layout.owner.fullName|default:$layout.owner.userName}<br/>
    {g->text one="Viewed: %d time" many="Viewed: %d times"
             count=$layout.viewCount arg1=$layout.viewCount}<br/>
    {g->text text="Date: "}{g->date timestamp=$layout.item.originationTimestamp}<br/>
    {if isset($layout.item.keywords)}
      {g->text text="Keywords: "}{$layout.item.keywords|markup}<br/>
    {/if}
  </td></tr></table>
  {if !empty($layout.itemDetailFiles)}
    {foreach from=$layout.itemDetailFiles key=moduleId item=detailFile}
      {include file="gallery:$detailFile" l10Domain="modules_$moduleId"}
    {/foreach}
  {/if}
</div>
</body></html>
