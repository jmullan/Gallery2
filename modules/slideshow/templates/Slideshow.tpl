{foreach from=$SlideShow.itemList key=i item=it}
{g->link id="item_$i" arg1="view=core:DownloadItem"
    arg2="itemId=`$it.source.id`" arg3="serialNumber=`$it.source.serialNumber`"
}{/g->link}
{g->link id="href_$i" arg1="view=core:ShowItem" arg2="itemId=`$it.id`"
}{/g->link}
<div id="title_{$i}" style="visibility:hidden;position:absolute">
{$it.data.title|markup}</div>
<div id="summary_{$i}" style="visibility:hidden;position:absolute">
{$it.data.summary|markup}</div>
<div id="description_{$i}" style="visibility:hidden;position:absolute">
{$it.data.description|markup}</div>
{/foreach}
<script language="JavaScript" type="text/JavaScript">
var image = new Image(), timer, showText = 0;
var stopLink, textLink, textBanner, titleText, summaryText, descriptionText;
var index = {$SlideShow.start}, count = {$SlideShow.count};
var is_cached = new Array(count), item_ids = new Array(count);
{foreach from=$SlideShow.itemList key=i item=it}
item_ids[{$i}] = '{$it.id}';
{/foreach}
{literal}
function preload(i) {
  if (!is_cached[i]) {
    is_cached[i] = 1;
    image.src = document.getElementById('item_'+i).href;
  }
}
function slide_view_start() {
  preload((index+1)%count);
  timer = setTimeout('goto_next_photo()', 15000);
}
function goto_next_photo() {
  index = (index+1)%count;
  document.images.slide.src = document.getElementById('item_'+index).href;
  stopLink.href = document.getElementById('href_'+index).href;
  if (showText) show_text();
}
function show_text() {
  titleText.innerHTML = document.getElementById('title_'+index).innerHTML;
  summaryText.innerHTML = document.getElementById('summary_'+index).innerHTML;
  descriptionText.innerHTML =
    document.getElementById('description_'+index).innerHTML;
}
function text_onoff() {
  showText = showText ? 0 : 1;
  if (showText) show_text(); else
  titleText.innerHTML = summaryText.innerHTML = descriptionText.innerHTML = '';
  textBanner.style.visibility = showText ? 'visible' : 'hidden';
  textLink.innerHTML = showText ? {/literal}'{g->text text="Hide More Info"}'
                                : '{g->text text="Show More Info"}'; {literal}
}
{/literal}
</script>
{g->main}
  {g->breadcrumb}
    {g->item}
      {g->title}
        {g->link id="stop" arg1="view=core:ShowItem"
                 arg2="itemId=`$SlideShow.itemList[$SlideShow.start].id`"}
          {g->text text="Stop"}
        {/g->link} &nbsp;
        {g->link onClick="text_onoff();return false"}
          <span id="textLink">{g->text text="Show More Info"}</span>
        {/g->link}
      {/g->title}
    {/g->item}
  {/g->breadcrumb}
  {g->pagebox}
    {g->box style="canvas"}
      {g->itemview}
        {g->media}
          <img name="slide" alt="" src="">
        {/g->media}
      {/g->itemview}
    {/g->box}
    {g->element}<div id="textBanner" style="visibility:hidden">
    {g->banner}
      {g->title}<span id="title"></span>{/g->title}
      {g->description}<span id="summary"></span>{/g->description}
      {g->element}<span id="description"></span>{/g->element}
    {/g->banner}
    </div>{/g->element}
  {/g->pagebox}
{/g->main}
<script language="JavaScript" type="text/JavaScript">
  stopLink = document.getElementById('stop');
  textLink = document.getElementById('textLink');
  textBanner = document.getElementById('textBanner');
  titleText = document.getElementById('title');
  summaryText = document.getElementById('summary');
  descriptionText = document.getElementById('description');
  document.images.slide.onload = slide_view_start;
  document.images.slide.onerror = goto_next_photo;
  document.images.slide.src =
    document.getElementById('item_{$SlideShow.start}').href;
</script>
