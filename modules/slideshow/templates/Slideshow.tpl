{foreach from=$SlideShow.itemList key=i item=it}
<a id="item_{$i}" href="{$it.src}"></a>
<a id="href_{$i}" href="{$it.href}"></a>
{/foreach}
<script language="JavaScript" type="text/JavaScript">
var index = {$SlideShow.start};
var count = {$SlideShow.count};
var is_cached = new Array;
var item_ids = new Array;
{foreach from=$SlideShow.itemList key=i item=it}
item_ids[{$i}] = '{$it.id}';
{/foreach}
var timer;

{literal}
function preload(i) {
  if (!is_cached[i]) {
    is_cached[i] = 1;
    var img = new Image();
    img.src = document.getElementById("item_"+i).href;
  }
}
function slide_view_start() {
  preload((index+1)%count);
  timer = setTimeout('goto_next_photo()', 15000);
}
function goto_next_photo() {
  index = (index+1)%count;
  document.images.slide.src = document.getElementById('item_'+index).href;
  document.getElementById("stop").href = document.getElementById("href_"+index).href;
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
            document.images.slide.onload = slide_view_start;
            document.images.slide.onerror = goto_next_photo;
            document.images.slide.src =
              '{$SlideShow.itemList[$SlideShow.start].src}';
          </script>
        {/g->media}
      {/g->itemview}
    {/g->box}
  {/g->pagebox}
{/g->main}
