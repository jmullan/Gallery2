{foreach from=$SlideShow.itemList key=i item=it}
{g->link id="item_$i" arg1="view=core:DownloadItem"
    arg2="itemId=`$it.sourceId`" arg3="serialNumber=`$it.sourceSerial`"
}{/g->link}
{g->link id="href_$i" arg1="view=core:ShowItem" arg2="itemId=`$it.id`"
}{/g->link}
{/foreach}
<script language="JavaScript" type="text/JavaScript">
var image = new Image(), timer, stoplink;
var index = {$SlideShow.start}, count = {$SlideShow.count};
var is_cached = new Array(count), item_ids = new Array(count);
{foreach from=$SlideShow.itemList key=i item=it}
item_ids[{$i}] = '{$it.id}';
{/foreach}
{literal}
function preload(i) {
  if (!is_cached[i]) {
    is_cached[i] = 1;
    image.src = document.getElementById("item_"+i).href;
  }
}
function slide_view_start() {
  preload((index+1)%count);
  timer = setTimeout('goto_next_photo()', 15000);
}
function goto_next_photo() {
  index = (index+1)%count;
  document.images.slide.src = document.getElementById('item_'+index).href;
  stoplink.href = document.getElementById("href_"+index).href;
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
        {/g->link}
      {/g->title}
    {/g->item}
  {/g->breadcrumb}
  {g->pagebox}
    {g->box style="canvas"}
      {g->itemview}
        {g->media}
          <img name="slide" alt="" src="">
          <script language="JavaScript" type="text/JavaScript">
            stoplink = document.getElementById("stop");
            document.images.slide.onload = slide_view_start;
            document.images.slide.onerror = goto_next_photo;
            document.images.slide.src =
              document.getElementById('item_{$SlideShow.start}').href;
          </script>
        {/g->media}
      {/g->itemview}
    {/g->box}
  {/g->pagebox}
{/g->main}
