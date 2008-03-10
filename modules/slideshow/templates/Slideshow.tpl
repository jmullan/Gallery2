{*
 * $Revision$
 * Read this before changing templates!  http://codex.gallery2.org/Gallery2:Editing_Templates
 *}
{foreach from=$Slideshow.items item=i name=items}
<a style="display: none" href="{g->url arg1="view=core.DownloadItem" arg2="itemId=`$i.image.id`" arg3="serialNumber=`$i.image.serialNumber`"}" rel="lyteshow[s]" title="{$i.item.title|markup|escape:html} {$i.item.summary|markup|escape:html}" id="a{$smarty.foreach.items.index}">.</a>
{/foreach}

<script type="text/javascript">
{literal}
function start(startElId) {
  if (typeof myLytebox != 'undefined') {
    myLytebox.start(document.getElementById(startElId), true, false);
    setTimeout('goBackOnStop()', 1000);
  } else {
    setTimeout('start("' + startElId + '")', 1000);
  }
}
function goBackOnStop() {
  var el = document.getElementById('lbOverlay');
  if (el && el.style.display != 'none') {
    setTimeout('goBackOnStop()', 1000);
  } else {
    history.go(-1);
  }
}
{/literal}
YAHOO.util.Event.addListener(window, 'load', function() {ldelim} start("a{$Slideshow.start}"); {rdelim}, false);
</script>
