{foreach from=$SlideShow.itemList key=i item=it}
<div style="visibility:hidden;position:absolute">
{foreach from=$it.sources key=j item=source}
{g->link id="item_`$i`_$j" arg1="view=core:DownloadItem"
    arg2="itemId=`$source.id`"
    arg3="serialNumber=`$source.serialNumber`"}{/g->link}
{/foreach}
{g->link id="href_$i" arg1="view=core:ShowItem" arg2="itemId=`$it.id`"
}{/g->link}
<span id="title_{$i}">{$it.data.title|markup}</span>
<span id="summary_{$i}">{$it.data.summary|markup}</span>
<span id="date_{$i}">
{if isset($it.exif.DateTime)}
{$it.exif.DateTime.title}: {$it.exif.DateTime.value}
{else}
{g->text text="Date: "}{g->date timestamp=$it.data.modificationTimestamp}
{/if}</span>
<span id="description_{$i}">{$it.data.description|markup}</span>
</div>
{/foreach}
<script language="JavaScript" type="text/JavaScript">
var image = new Image(), timer, iSize = 0, bPause = 0, bShowText = 0;
var linkStop, spanPause, spanText;
var textBanner, spanTitle, spanSummary, spanDate, spanDescription;
var index = {$SlideShow.start}, count = {$SlideShow.count};
var is_cached = new Array(count), item_map = new Array(count);
{foreach from=$SlideShow.itemList key=i item=it}
item_map[{$i}] = new Array(6);
{foreach from=$it.sizeClassMap key=j item=idx}
item_map[{$i}][{$j}] = {$idx};
{/foreach}
{/foreach}
{literal}
function preload(i) {
  if (!is_cached[i]) {
    is_cached[i] = 1;
    image.src = document.getElementById('item_'+i+'_'+item_map[i][iSize]).href;
  }
}
function slide_view_start() {
  preload((index+1)%count);
  timer = setTimeout('goto_next_photo()', 15000);
}
function goto_next_photo() {
  index = (index+1)%count;
  if (bCanBlend) apply_filter();
  document.images.slide.src = document.getElementById('item_'+index+'_'+item_map[index][iSize]).href;
  linkStop.href = document.getElementById('href_'+index).href;
  if (bShowText) show_text();
  if (bCanBlend) document.images.slide.filters[0].Play();
}
function show_text() {
  spanTitle.innerHTML = document.getElementById('title_'+index).innerHTML;
  spanSummary.innerHTML = document.getElementById('summary_'+index).innerHTML;
  spanDate.innerHTML = document.getElementById('date_'+index).innerHTML;
  spanDescription.innerHTML =
    document.getElementById('description_'+index).innerHTML;
}
function text_onoff() {
  bShowText = bShowText ? 0 : 1;
  if (bShowText) show_text(); else {
    spanTitle.innerHTML = spanSummary.innerHTML =
    spanDate.innerHTML = spanDescription.innerHTML = '';
  }
  textBanner.style.visibility = bShowText ? 'visible' : 'hidden';
  spanText.innerHTML = bShowText ? {/literal}'{g->text text="Hide More Info"}'
                                 : '{g->text text="Show More Info"}'; {literal}
}
function start_stop() {
  bPause = bPause ? 0 : 1;
  if (bPause) clearTimeout(timer);
  else goto_next_photo();
  spanPause.innerHTML = bPause ? {/literal}'{g->text text="Resume"}'
                               : '{g->text text="Pause"}'; {literal}
}
function back_one() {
  if (index > 0) {
    index -= 2;
    if (bPause) start_stop(); else {
      clearTimeout(timer);
      goto_next_photo();
    }
  }
}
function apply_filter() {
  f = filters[document.getElementById('filter').selectedIndex];
  while (f == 'RANDOM') f = filters[Math.floor(Math.random()*filters.length)];
  document.images.slide.style.filter = f;
  document.images.slide.filters[0].Apply();
}
function new_size(size) {
  clearTimeout(timer);
  iSize = size;
  index--;
  goto_next_photo();
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
        {g->link onClick="start_stop();return false"}
          <span id="pause">{g->text text="Pause"}</span>
        {/g->link} &nbsp;
        {g->link onClick="back_one();return false"}
          {g->text text="Back One Image"}
        {/g->link} &nbsp;
        {g->link onClick="text_onoff();return false"}
          <span id="moreInfo">{g->text text="Show More Info"}</span>
        {/g->link} &nbsp;
        {g->text text="max size: "}<select onchange="new_size(this.value)">
          <option value=0>{g->text text="320x200"}
          <option value=1>{g->text text="640x480"}
          <option value=2>{g->text text="800x600"}
          <option value=3>{g->text text="1024x768"}
          <option value=4>{g->text text="1280x1024"}
          <option value=5>{g->text text="no limit"}
        </select>
        <script language="JavaScript" type="text/JavaScript">{literal}
          if (bCanBlend) {
            document.write('&nbsp; {/literal}{g->text
                           text="fade: "}{literal}<select id="filter">');
            for (i = 0; i < filterNames.length; i++) {
              document.write('<option>'+filterNames[i]);
            }
            document.write('<'+'/select>'); // in 2 pieces for valid HTML4.01
          }
        {/literal}</script>
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
      {g->infoset}
        {g->item}{g->title}<span id="date"></span>{/g->title}{/g->item}
        {g->item}{g->title}<span id="description"></span>{/g->title}{/g->item}
      {/g->infoset}
    {/g->banner}
    </div>{/g->element}
  {/g->pagebox}
{/g->main}
<script language="JavaScript" type="text/JavaScript">
  linkStop = document.getElementById('stop');
  spanPause = document.getElementById('pause');
  spanText = document.getElementById('moreInfo');
  textBanner = document.getElementById('textBanner');
  spanTitle = document.getElementById('title');
  spanSummary = document.getElementById('summary');
  spanDate = document.getElementById('date');
  spanDescription = document.getElementById('description');
  document.images.slide.onload = slide_view_start;
  document.images.slide.onerror = goto_next_photo;
  document.images.slide.src =
    document.getElementById('item_{$SlideShow.start}_'+item_map[{$SlideShow.start}][iSize]).href;
</script>
